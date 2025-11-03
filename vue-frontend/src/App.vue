<template>
  <el-container class="main-container">
    <el-header class="main-header">
      <div class="title">
        Acaddia-Web 测控终端
      </div>

      <div class="header-actions">
        <el-button-group>
          <el-button
            text
            @click="openDialog('com')"
          >
            串口设置
          </el-button>
          <el-button
            text
            @click="openDialog('time')"
          >
            时间设置
          </el-button>
          <el-button
            text
            @click="openDialog('angle')"
          >
            角度矢量
          </el-button>
          <el-button
            text
            @click="openDialog('dim')"
          >
            标幺设置
          </el-button>
        </el-button-group>
      </div>

      <div class="spacer" />

      <div class="connection-status">
        <el-tag
          :type="isSerialConnected ? 'success' : 'danger'"
          size="large"
        >
          {{ serialStatus }}
        </el-tag>
      </div>
    </el-header>

    <el-container>
      <el-aside
        width="220px"
        class="main-aside"
      >
        <el-menu
          :default-active="activeView"
          class="main-menu"
          @select="handleMenuSelect"
        >
          <el-menu-item index="Main">
            主界面
          </el-menu-item>
          <el-menu-item index="DataParsing">
            串口数据收发
          </el-menu-item>
          <el-menu-item index="Tqcs">
            同期参数
          </el-menu-item>
          <el-menu-item index="AdParams">
            AD参数
          </el-menu-item>
          <el-menu-item index="AdAdjust">
            通道校准
          </el-menu-item>
          <el-menu-item index="Tqml">
            同期命令
          </el-menu-item>
          <el-menu-item index="Message">
            通信报文
          </el-menu-item>
        </el-menu>
      </el-aside>

      <el-main class="main-content">
        <KeepAlive>
          <component
            :is="activeViewComponent"
            :is-serial-connected="isSerialConnected"
            :initial-ad-data="initialAdData"
            :message-data="messageData"
            :device-time-raw-data="deviceTimeRawData"
            :device-angle-raw-data="deviceAngleRawData"
            :tqcs-raw-data="tqcsRawData"
            :ad-params-raw-data="adParamsRawData"
            :tqml-raw-data="tqmlRawData"
            :ad-adjust-status-data="adAdjustStatusData"
            :ad-adjust-result-data="adAdjustResultData"
            :current-serial-settings="currentSerialSettings"
            :write-to-serial="writeToSerial"
            :last-received-frame="lastReceivedFrame"
            :send-command="handleSendCommand"
            :pu-base-value="puBaseValue"
            :pu-voltage-mode="puVoltageMode"
          />
        </KeepAlive>
      </el-main>
    </el-container>

    <com-settings-dialog
      v-model:visible="dialogVisible.com"
      :is-connected="isSerialConnected"
      :current-port="port"
      @connect="handleSerialConnect"
      @disconnect="handleSerialDisconnect"
    />
    <time-settings-dialog
      v-model:visible="dialogVisible.time"
      :device-time-raw-data="deviceTimeRawData"
      @fetch-time="handleFetchTime"
    />
    <angle-vector-dialog
      v-model:visible="dialogVisible.angle"
      :device-angle-raw-data="deviceAngleRawData"
      @fetch="handleFetchAngle"
    />
    <dim-settings-dialog
      v-model:visible="dialogVisible.dim"
      :current-pu-base-value="puBaseValue"
      :current-pu-voltage-mode="puVoltageMode"
      @confirm="handleSetDim"
      @default="handleDefaultDim"
    />
  </el-container>
</template>

<script>
// Import View Components
import MainView from './components/views/MainView.vue';
import DataParsingView from './components/views/DataParsingView.vue';
import TqcsView from './components/views/TqcsView.vue';
import AdParamsView from './components/views/AdParamsView.vue';
import AdAdjustView from './components/views/AdAdjustView.vue';
import TqmlView from './components/views/TqmlView.vue';
import MessageView from './components/views/MessageView.vue';
// ... import other views

// Import Dialog Components
import ComSettingsDialog from './components/ComSettingsDialog.vue';
import TimeSettingsDialog from './components/TimeSettingsDialog.vue';
import AngleVectorDialog from './components/AngleVectorDialog.vue';
import DimSettingsDialog from './components/DimSettingsDialog.vue';
// ... import other dialogs

// Import Protocol Utils
import { pack, packAck, Unpacker } from './utils/acadia-protocol'; // 引入打包和解包工具

// --- 命令定义 ---
// TQCS
const CMD_REQ_TQCS = { stationAddr: 0, telegramNr: 0x23, expectedResponseId: 0x22 }; // (C++: TQCS 读取 35->34)
const CMD_SET_TQCS = { stationAddr: 0, telegramNr: 0x22, expectedResponseId: 0xE5 }; // (C++: TQCS 应用 34->E5)

// ACAD (AD参数)
const CMD_REQ_ACAD = { stationAddr: 0, telegramNr: 0x21, expectedResponseId: 0x20 }; // (C++: ADParams 读取 33->32)
const CMD_SET_ACAD = { stationAddr: 0, telegramNr: 0x20, expectedResponseId: 0xE5 }; // (C++: ADParams 应用 32->E5)

// 主界面
const CMD_REQ_AD_CALC = { stationAddr: 0, telegramNr: 0x25, expectedResponseId: 0x24 }; // (C++: 主界面AD计算值 37->36)
const CMD_REQ_ANGLE = { stationAddr: 0, telegramNr: 0x2F, expectedResponseId: 0x30 }; // 获取角度 (发送 2F, 响应 30)
const CMD_REQ_MSG_HEAD = { stationAddr: 0, telegramNr: 0x0C, expectedResponseId: 0x02 };
const CMD_REQ_MSG_BODY = { stationAddr: 0, telegramNr: 0x0D, expectedResponseId: 0x03 };

// 时间
const CMD_REQ_TIME = { stationAddr: 0, telegramNr: 0x1D, expectedResponseId: 0x1C }; // 请求时间 (发送 1D, 响应 1C)

// [新增] TQML (同期命令)
// C++: Dlg_TQML::onButtonApplyClicked() -> 44 (0x2C)
const CMD_TQML_EXEC = { stationAddr: 0, telegramNr: 0x2C, expectedResponseId: 0xE5 };
// C++: Dlg_TQML::onButtonFetchClicked() -> 45 (0x2D), 响应 (猜测) 46 (0x2E)
const CMD_TQML_FETCH = { stationAddr: 0, telegramNr: 0x2D, expectedResponseId: 0x2E };

// [新增] 通道校准 (ADAdjust)
const CMD_AD_ADJUST_APPLY = { stationAddr: 0, telegramNr: 0x26, expectedResponseId: 0xE5 }; // (C++: 38) "通道校准"
const CMD_AD_ADJUST_STATUS = { stationAddr: 0, telegramNr: 0x28, expectedResponseId: 0x29 }; // (C++: 40, 猜测) "校准状态"
// (响应 0x27 是校准结果, 响应 0x29 是状态结果)


export default {
  name: 'App',
  components: {
    MainView, DataParsingView, TqcsView, AdParamsView, AdAdjustView, TqmlView, MessageView,
    ComSettingsDialog, TimeSettingsDialog, AngleVectorDialog, DimSettingsDialog,
    // ... other components
  },
  data() {
    return {
      activeView: 'Main',
      isSerialConnected: false,
      dialogVisible: { com: false, time: false, angle: false, dim: false /*, ... other dialogs */ },
      serialPortName: '', // 用于显示
      initialAdData: null, // 存储连接时获取的 AD 数据 (来自 0x24)
      // Message List (主界面)
      messageData: { head: null, body: [], timestamp: null },
      // 设备时间原始数据 (用于 TimeSettingsDialog)
      deviceTimeRawData: null,
      // 设备角度原始数据 (用于 AngleVectorDialog)
      deviceAngleRawData: null,
      tqcsRawData: null, // 存储 TQCS (0x22) 响应的 payload
      adParamsRawData: null, // 存储 ADParams (0x20) 响应的 payload
      tqmlRawData: null, // [新增] 存储 TQML (0x2E) 响应的 payload

      // [新增] 通道校准数据
      adAdjustStatusData: null, // 存储 (0x29) 状态响应
      adAdjustResultData: null, // 存储 (0x27) 结果响应

      currentSerialSettings: null, // 存储当前连接的设置

      // --- 标幺设置状态 ---
      puBaseValue: 16384, // 对应 Qt 的 DIM_public, 默认 4000H -> 16384
      puVoltageMode: 0,   // 对应 Qt 的 DIM_Line_Vot_style, 默认 0 -> 都显示100%

      // --- Web Serial API State ---
      port: null,
      reader: null,
      writer: null,
      keepReading: false,
      unpacker: new Unpacker(),
      lastReceivedFrame: null,
      // 命令队列
      commandQueue: [],
      isExecutingCommand: false,
    };
  },
  computed: {
    activeViewComponent() {
      // 根据 activeView 动态选择要渲染的视图组件
      const viewName = `${this.activeView}View`;
      // 确保组件已注册，否则回退到 MainView
      return Object.keys(this.$options.components).includes(viewName) ? viewName : 'MainView';
    },
    serialStatus() {
      // 根据连接状态和端口信息生成状态文本
      if (this.isSerialConnected && this.port) {
        try {
          // 尝试获取更友好的端口信息
          const info = this.port.getInfo();
          if (info.usbVendorId && info.usbProductId) {
            return `串口: 已连接 (VID:${info.usbVendorId.toString(16)}, PID:${info.usbProductId.toString(16)})`;
          }
        } catch(e) {/* ignore if getInfo fails */}
        return `串口: 已连接`; // 备用信息
      }
      return '串口: 已断开';
    },
  },
  // 添加 beforeUnmount 钩子以确保在组件卸载时断开连接
  async beforeUnmount() {
    if (this.isSerialConnected) {
      await this.handleSerialDisconnect(false);
    }
  },
  methods: {
    handleMenuSelect(index) {
      this.activeView = index;
    },
    openDialog(dialogName) {
      this.dialogVisible[dialogName] = true;
    },

    /**
     * @vuese
     * 处理连接。
     */
    async handleSerialConnect({ port, settings }) {
      if (this.isConnected || !port) return;

      this.port = port;
      this.currentSerialSettings = settings;
      this.serialPortName = `VID:${port.getInfo().usbVendorId?.toString(16)}, PID:${port.getInfo().usbProductId?.toString(16)}`;

      try {
        const writableStream = this.port.writable;
        if (!writableStream) throw new Error("Writable stream not available.");
        this.writer = writableStream.getWriter();

        const readableStream = this.port.readable;
        if (!readableStream) throw new Error("Readable stream not available.");
        this.reader = readableStream.getReader();
        this.keepReading = true;
        this.readUntilClosed();

        this.isSerialConnected = true;
        this.dialogVisible.com = false;
        this.$message.success(`串口已连接`);

        this.$message.info('正在执行初始命令序列...');
        await this.executeInitialSequence();
        this.$message.success('初始命令序列执行完毕');

      } catch (error) {
        console.error('连接后初始化读写器或执行命令失败:', error);
        this.$message.error(`连接后初始化失败: ${error.message}`);
        await this.handleSerialDisconnect(false);
      }
    },

    /**
     * @vuese
     * 处理断开连接。
     */
    async handleSerialDisconnect(showSuccessMsg = true) {
      this.keepReading = false;

      if (this.writer) {
        try {
          // [重要] 尝试中止正在进行的写入操作
          await this.writer.abort('Disconnecting').catch(e => console.warn('Abort writer failed:', e));
          // [修改] 先释放锁再关闭似乎更安全
          try { this.writer.releaseLock(); } catch(e) {/* ignore */}
          // await this.writer.close(); // 关闭流可能在某些情况下挂起
        } catch (e) { console.warn('关闭/中止 writer 时出错:', e); }
        finally { this.writer = null; }
      }
      if (this.reader) {
        try {
          // 取消读取操作
          await this.reader.cancel('Disconnecting').catch(e => console.warn('Cancel reader failed:', e));
          try { this.reader.releaseLock(); } catch(e) {/* ignore */}
        } catch (e) { console.warn('取消/释放 reader 时出错:', e); }
        finally { this.reader = null; }
      }

      // [修改] 增加 port?.close() 调用，并捕获错误
      if (this.port) {
        try {
          // 确保在关闭前所有操作已取消
          await Promise.race([
            new Promise(resolve => setTimeout(resolve, 500)), // 设置超时
            (async () => {
              // 再次确保读写器已取消/中止
              if (this.writer) await this.writer.abort('Closing port').catch(()=>{});
              if (this.reader) await this.reader.cancel('Closing port').catch(()=>{});
            })()
          ]);
          await this.port.close();
          console.log("Serial port closed.");
        } catch (e) {
          console.error('关闭串口时出错:', e);
          // 根据错误类型可能需要特定处理，例如设备已拔出
          if (e.name === 'NetworkError') {
            console.warn('Port likely disconnected physically.');
          }
        } finally {
          this.port = null;
        }
      }

      // 重置状态
      this.isSerialConnected = false;
      this.serialPortName = '';
      this.initialAdData = null;
      this.currentSerialSettings = null;
      this.messageData = { head: null, body: [], timestamp: null };
      this.deviceTimeRawData = null;
      this.deviceAngleRawData = null;
      this.tqcsRawData = null;
      this.adParamsRawData = null;
      this.tqmlRawData = null; // [新增]
      // [新增] 重置 ADAdjust 数据
      this.adAdjustStatusData = null;
      this.adAdjustResultData = null;

      this.commandQueue = [];
      this.isExecutingCommand = false;
      this.unpacker = new Unpacker(); // 重置解包器状态
      this.lastReceivedFrame = null; // 清空最后接收帧

      if (showSuccessMsg) { this.$message.info('串口已断开'); }
    },

    /**
     * @vuese
     * 向串口写入数据。
     */
    async writeToSerial(data) {
      if (!this.writer || !this.isSerialConnected) {
        console.warn('Attempted to write but writer is null or port disconnected.');
        this.$message.error('写入失败：串口未连接或写入器无效');
        return false;
      }
      try {
        await this.writer.write(data);
        return true;
      } catch (error) {
        console.error('写入串口失败:', error);
        this.$message.error(`写入失败: ${error.message}`);
        // 写入失败通常意味着连接有问题，尝试断开
        await this.handleSerialDisconnect(false);
        return false;
      }
    },

    /**
     * @vuese
     * 异步读取串口数据。
     */
    async readUntilClosed() {
      // 增加检查，确保 reader 存在
      while (this.port?.readable && this.reader && this.keepReading) {
        try {
          const { value, done } = await this.reader.read();
          if (done) {
            console.log("Reader stream closed.");
            break; // 读取器已关闭
          }
          if (value && value.length > 0) { // 确保 value 非空
            this.unpacker.addData(value);
            const frames = this.unpacker.unpack();
            if (frames.length > 0) { // 仅在解出帧时处理
              for (const frame of frames) {
                this.lastReceivedFrame = frame; // 更新最后接收帧（包括 junk）
                if (frame.type !== 'junk') {
                  await this.processFrame(frame); // 处理有效帧
                } else {
                  console.log("Received junk data:", frame.raw);
                }
              }
            }
          }
        } catch (error) {
          // 根据错误类型判断是否是用户取消或设备断开
          if (error.name === 'AbortError' || error.message.includes('cancel')) {
            console.log('Reading aborted:', error.message);
          } else if (error.name === 'NetworkError') {
            console.error('Device disconnected during read:', error);
            this.$message.error('设备已断开连接');
          } else {
            console.error('读取串口时发生未知错误:', error);
            this.$message.error(`读取错误: ${error.message}`);
          }
          this.keepReading = false; // 发生任何错误都停止读取
          // [修改] 不再立即断开，让 handleSerialDisconnect 处理
          // await this.handleSerialDisconnect(false);
          break; // 退出循环
        }
      }
      console.log("Read loop finished or exited due to error/disconnect.");
      // [修改] 如果循环结束但仍处于连接状态（例如 done=true），则执行断开
      if (this.isSerialConnected) {
        await this.handleSerialDisconnect(false);
      }
    },

    /**
     * @vuese
     * 处理协议帧。
     */
    async processFrame(frame) {
      if (frame.type === 'ack_e5') {
        console.log("Received E5 ACK");
        if (this.isExecutingCommand && this.commandQueue.length > 0) {
          const currentCommand = this.commandQueue[0];
          // [修改] 检查 E5 是否是 TQCS, ADParams, ADAdjust apply 或 TQML exec 命令的预期响应
          if (currentCommand.command.expectedResponseId === 0xE5) {
            console.log(`Command ${currentCommand.command.telegramNr} received expected E5 ACK.`);
            clearTimeout(currentCommand.timeoutTimer);
            currentCommand.resolve({ type: 'ack_e5' });
            this.commandQueue.shift();
            this.isExecutingCommand = false;
            await this.executeNextCommand();
          } else {
            console.warn("Received unexpected E5 ACK while waiting for data frame.");
            // 不处理意外的 ACK，继续等待预期响应
          }
        } else {
          console.log("Received unsolicited E5 ACK."); // 收到未请求的 E5
        }
      } else if (frame.type === 'data') {
        console.log(`Received data frame: Nr=${frame.telegramNr}, Payload length=${frame.payload.length}`);

        // 发送 A2 (Master ACK)
        const ackSuccess = await this.writeToSerial(packAck());
        if (!ackSuccess) {
          console.error("Failed to send A2 ACK.");
          // ACK 发送失败可能表示连接问题，可以考虑断开
          // await this.handleSerialDisconnect(false);
          return; // 停止处理此帧
        }

        const payloadArray = Array.from(frame.payload); // 转换一次即可

        // --- 根据响应 ID 更新具体数据 ---
        // 注意：将数据更新移到命令响应处理之前，确保数据总是被更新，即使是意外帧
        const responseId = frame.telegramNr;
        switch(responseId) {
          case CMD_REQ_ACAD.expectedResponseId: // 0x20
            console.log("Updating adParamsRawData with received payload.");
            this.adParamsRawData = payloadArray;
            break;
          case CMD_REQ_TQCS.expectedResponseId: // 0x22
            console.log("Updating tqcsRawData with received payload.");
            this.tqcsRawData = payloadArray;
            break;
          case CMD_REQ_AD_CALC.expectedResponseId: // 0x24
            console.log("Updating initialAdData with received payload.");
            this.initialAdData = payloadArray;
            break;
          case CMD_REQ_MSG_HEAD.expectedResponseId: // 0x02
            console.log("Updating messageData.head with received payload.");
            this.messageData.head = payloadArray;
            this.messageData.body = []; // 清空 body
            this.messageData.timestamp = Date.now();
            break;
          case CMD_REQ_MSG_BODY.expectedResponseId: // 0x03
            console.log("Updating messageData.body with received payload.");
            // 检查 head 是否存在，防止孤立的 body 帧
            if (this.messageData.head) {
              this.messageData.body.push(...payloadArray);
              this.messageData.timestamp = Date.now();
            } else {
              console.warn("Received message body frame (0x03) without preceding head frame (0x02).");
            }
            break;
          case CMD_REQ_TIME.expectedResponseId: // 0x1C
            console.log("Updating deviceTimeRawData with received payload.");
            this.deviceTimeRawData = payloadArray;
            break;
          case CMD_REQ_ANGLE.expectedResponseId: // 0x30
            console.log("Updating deviceAngleRawData with received payload.");
            this.deviceAngleRawData = payloadArray;
            break;

            // [新增] TQML 响应
          case CMD_TQML_FETCH.expectedResponseId: // 0x2E
            console.log("Updating tqmlRawData with received payload (0x2E).");
            this.tqmlRawData = payloadArray;
            break;

            // [新增] ADAdjust 响应
          case 0x27: // AD Adjust Result (Unsolicited)
            console.log("Updating adAdjustResultData with received payload (0x27).");
            this.adAdjustResultData = payloadArray;
            break;
          case CMD_AD_ADJUST_STATUS.expectedResponseId: // 0x29
            console.log("Updating adAdjustStatusData with received payload (0x29).");
            this.adAdjustStatusData = payloadArray;
            break;

          default:
            console.log(`Received data frame with unhandled ID: ${responseId}`);
        }

        // 处理命令响应
        if (this.isExecutingCommand && this.commandQueue.length > 0) {
          const currentCommand = this.commandQueue[0];
          if (frame.telegramNr === currentCommand.command.expectedResponseId) {
            console.log(`Command ${currentCommand.command.telegramNr} received expected response ${frame.telegramNr}.`);
            clearTimeout(currentCommand.timeoutTimer); // 清除超时定时器
            currentCommand.resolve(frame); // 用收到的帧解决 Promise
            this.commandQueue.shift(); // 从队列移除已完成的命令
            this.isExecutingCommand = false; // 标记命令执行结束
            await this.executeNextCommand(); // 尝试执行下一个命令
          } else {
            console.warn(`Received unexpected data frame ${frame.telegramNr} while waiting for ${currentCommand.command.expectedResponseId}.`);
            // 不解决 Promise，让它超时或等待正确的响应
          }
        } else {
          console.log("Received unsolicited data frame (not waiting for specific response):", frame);
          // 可以根据需要处理这些未请求的数据帧
        }
      }
    },


    /**
     * @vuese
     * 执行初始连接命令序列。
     */
    async executeInitialSequence() {
      try {
        console.log("Executing initial sequence...");
        // [修改] 移除 await，让 sendCommand 顺序加入队列
        this.sendCommand(CMD_REQ_TQCS); // 0x23 -> 0x22
        this.sendCommand(CMD_REQ_ACAD); // 0x21 -> 0x20
        this.sendCommand(CMD_REQ_AD_CALC); // 0x25 -> 0x24
        this.sendCommand(CMD_REQ_ANGLE); // 0x2F -> 0x30
        console.log("Initial sequence commands queued.");
        // 注意：这里不再等待所有命令完成，命令将在后台按顺序执行
      } catch (error) {
        // 这个 catch 块不太可能被触发，因为 sendCommand 现在不直接抛错
        console.error("Error queuing initial command sequence:", error);
        this.$message.error(`初始命令序列排队失败: ${error.message || error}`);
      }
    },


    /**
     * @vuese
     * 将命令加入队列。
     */
    sendCommand(commandDef, payload = null, timeout = 3000) {
      // [修改] 确保返回 Promise
      return new Promise((resolve, reject) => {
        // 检查串口连接状态
        if (!this.isSerialConnected) {
          const errorMsg = '无法发送命令：串口未连接';
          console.error(errorMsg);
          this.$message.error(errorMsg);
          return reject(new Error(errorMsg)); // 直接拒绝 Promise
        }

        // [新增] 检查是否是 Apply (SET) 命令
        const isApplyCommand = (
            commandDef.telegramNr === CMD_SET_TQCS.telegramNr ||
            commandDef.telegramNr === CMD_SET_ACAD.telegramNr ||
            commandDef.telegramNr === CMD_AD_ADJUST_APPLY.telegramNr || // [新增]
            commandDef.telegramNr === CMD_TQML_EXEC.telegramNr // [新增]
        );

        const commandTask = {
          command: commandDef,
          payload: payload,
          resolve: resolve,
          reject: reject,
          timeoutTimer: null // 初始化 timeoutTimer
        };

        // 设置超时定时器
        commandTask.timeoutTimer = setTimeout(() => {
          console.error(`Timeout waiting for response to command ${commandDef.telegramNr} (expected ${commandDef.expectedResponseId})`);

          // [修改] 从队列中移除超时的任务
          const index = this.commandQueue.indexOf(commandTask);
          if (index > -1) {
            this.commandQueue.splice(index, 1);
          }

          // [修改] 检查当前执行的任务是否是超时的任务
          // [BUG修复] 原代码中 `this.commandQueue[0] === commandTask` 的比较在 splice 之后可能是错的
          // 应该比较的是 `this.isExecutingCommand` 并且 *当前任务* 是 `commandTask`
          // 一个更简单的方法是：如果超时的任务是队首任务，才重置 isExecutingCommand
          if (index === 0 && this.isExecutingCommand) {
            this.isExecutingCommand = false; // 如果是，则允许下一个命令执行
            this.executeNextCommand();
          } else if (!this.isExecutingCommand && this.commandQueue.length > 0) {
            // 如果当前没有命令在执行，且队列不为空（意味着超时的是非队首任务，理论上不应发生）
            this.executeNextCommand(); // 尝试启动下一个
          }
          // [修改] 确保 reject 被调用
          commandTask.reject(new Error(`Timeout waiting for response ID ${commandDef.expectedResponseId}`));
        }, timeout);


        // [修改] 如果是 Apply (SET) 命令，将其插入到队首
        if (isApplyCommand) {
          this.commandQueue.unshift(commandTask);
          console.log(`Apply Command ${commandDef.telegramNr} inserted at front of queue. Length: ${this.commandQueue.length}`);
        } else {
          this.commandQueue.push(commandTask); // 普通命令加入队尾
          console.log(`Command ${commandDef.telegramNr} queued. Queue length: ${this.commandQueue.length}`);
        }


        // 如果当前没有命令在执行，则启动执行流程
        if (!this.isExecutingCommand) {
          this.executeNextCommand();
        }
      });
    },

    /**
     * @vuese
     * 执行队列中的下一个命令。
     */
    async executeNextCommand() {
      if (this.isExecutingCommand || this.commandQueue.length === 0 || !this.isSerialConnected) {
        if (this.commandQueue.length > 0 && !this.isSerialConnected) {
          console.warn("Cannot execute next command: Serial port disconnected. Clearing queue.");
          // 清空队列并拒绝所有待处理的 Promise
          this.commandQueue.forEach(task => {
            clearTimeout(task.timeoutTimer);
            task.reject(new Error("Serial port disconnected"));
          });
          this.commandQueue = [];
        }
        return; // 如果正在执行、队列为空或未连接，则不执行
      }

      this.isExecutingCommand = true; // 标记开始执行
      const task = this.commandQueue[0]; // 获取队首任务

      try {
        console.log(`Executing command ${task.command.telegramNr}, expecting ${task.command.expectedResponseId}`);
        const frameToSend = pack({
          stationAddr: task.command.stationAddr,
          telegramNr: task.command.telegramNr,
          payload: task.payload || undefined
        });

        // 异步写入，不阻塞后续逻辑
        this.writeToSerial(frameToSend).then(writeSuccess => {
          if (!writeSuccess) {
            console.error(`Failed to write command ${task.command.telegramNr} to serial port.`);
            clearTimeout(task.timeoutTimer);
            task.reject(new Error(`Failed to write command ${task.command.telegramNr}`));
            this.commandQueue.shift(); // 移除失败的任务
            this.isExecutingCommand = false; // 标记执行结束
            this.executeNextCommand(); // 尝试下一个
          } else {
            console.log(`Command ${task.command.telegramNr} sent successfully.`);
            // 发送成功，等待 processFrame 处理响应或超时
          }
        }).catch(error => {
          // writeToSerial 内部的 catch 应该已经处理了错误和断开
          console.error(`Unexpected error during writeToSerial promise for command ${task.command.telegramNr}:`, error);
          clearTimeout(task.timeoutTimer);
          task.reject(error);
          this.commandQueue.shift();
          this.isExecutingCommand = false;
          this.executeNextCommand(); // 尝试下一个
        });

      } catch (packError) { // 捕获 pack 函数可能抛出的错误
        console.error(`Error packing command ${task.command.telegramNr}:`, packError);
        clearTimeout(task.timeoutTimer);
        task.reject(packError);
        this.commandQueue.shift(); // 移除打包失败的任务
        this.isExecutingCommand = false;
        await this.executeNextCommand(); // 尝试执行下一个命令
      }
    },


    /**
     * @vuese
     * 处理通用发送命令请求 (由子组件调用)。
     */
    async handleSendCommand({ commandDef, payload, timeout }) {
      // 不再检查 isSerialConnected，让 sendCommand 内部处理
      try {
        // [修改] 直接调用 sendCommand 并返回其 Promise
        const responseFrame = await this.sendCommand(commandDef, payload, timeout);
        return responseFrame; // 返回从 processFrame 收到的响应帧
      } catch (error) {
        // sendCommand 的 Promise 被拒绝时会进入这里
        // this.$message.error(`命令 ${commandDef.telegramNr} 执行失败: ${error?.message || error}`); // sendCommand 内部或调用者应处理消息
        console.error(`handleSendCommand caught error for command ${commandDef.telegramNr}:`, error);
        throw error; // 将错误重新抛出，让调用者处理
      }
    },


    // --- 处理来自特定对话框的事件 ---

    /**
     * @vuese
     * 处理获取时间事件。
     */
    async handleFetchTime() {
      // [修改] 使用 sendCommand，错误处理已包含
      this.$message.info('正在发送获取时间命令 (0x1D)...');
      try {
        // 不需要 await，响应在 processFrame 中处理并更新 data
        this.sendCommand(CMD_REQ_TIME);
      } catch (error) {
        // sendCommand 内部会处理错误消息，这里只记录日志
        console.error(`发送获取时间命令失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * 处理获取角度事件。
     */
    async handleFetchAngle() {
      // [修改] 使用 sendCommand
      this.$message.info('正在发送获取角度命令 (0x2F)...');
      try {
        this.sendCommand(CMD_REQ_ANGLE);
      } catch (error) {
        console.error(`发送获取角度命令失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * [修改] 处理标幺设置确认事件。
     * 更新 App.vue 中的标幺状态。
     */
    handleSetDim(settings) {
      console.log("Applying Per Unit Settings:", settings);
      // 将对话框传来的字符串值转换为内部状态值
      this.puBaseValue = settings.globalScale === '4000H' ? 16384 : 8192;
      this.puVoltageMode = settings.voltageScaleMode === 'both_100' ? 0 : 1;
      this.$message.success(`标幺设置已应用: 基值 ${settings.globalScale}, 电压模式 ${settings.voltageScaleMode}`);
      // 不需要关闭对话框，v-model 会处理
    },

    /**
     * @vuese
     * [修改] 处理恢复默认标幺设置事件。
     * 重置 App.vue 中的标幺状态并关闭对话框。
     */
    handleDefaultDim() {
      console.log("Restoring Default Per Unit Settings");
      this.puBaseValue = 16384; // 默认 4000H
      this.puVoltageMode = 0;   // 默认都显示 100%
      this.$message.info('标幺设置已恢复为默认值 (4000H, 电压均100%)');
      this.dialogVisible.dim = false; // 关闭对话框
    },

  },
};
</script>

<style>
/* 全局样式 */
html, body, #app, .main-container { height: 100%; margin: 0; padding: 0; background-color: #f0f2f5; }
.main-header { display: flex; align-items: center; background-color: #fff; border-bottom: 1px solid #dcdfe6; padding: 0 20px; }
.title { font-size: 24px; font-weight: bold; color: #303133; }
.header-actions { margin-left: 40px; }
.spacer { flex-grow: 1; }
.connection-status { margin-left: 20px;}
.main-aside { background-color: #fff; border-right: 1px solid #dcdfe6; display: flex; flex-direction: column; }
.main-menu { border-right: none; flex-grow: 1; }
.main-content { padding: 0; /* 移除内边距，让子视图控制 */ }
/* 确保 el-container 能正确填充高度 */
.el-container { height: 100%; }
.el-header { height: 60px; /* 固定头部高度 */ flex-shrink: 0; }
.el-container:not(.is-vertical) { height: calc(100% - 60px); /* 计算剩余高度 */}
.el-main { height: 100%; overflow-y: auto; box-sizing: border-box; padding: 20px; /* 为视图内容添加内边距 */}
</style>