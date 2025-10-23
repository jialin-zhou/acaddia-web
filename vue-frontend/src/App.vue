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
              :current-serial-settings="currentSerialSettings"
              :write-to-serial="writeToSerial"
              :last-received-frame="lastReceivedFrame"
              :send-command="sendCommand"
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
const CMD_REQ_TQCS = { stationAddr: 0, telegramNr: 0x23, expectedResponseId: 0x22 };
const CMD_REQ_ACAD = { stationAddr: 0, telegramNr: 0x21, expectedResponseId: 0x20 };
const CMD_REQ_AD_CALC = { stationAddr: 0, telegramNr: 0x25, expectedResponseId: 0x24 };
const CMD_REQ_ANGLE = { stationAddr: 0, telegramNr: 0x2F, expectedResponseId: 0x30 }; // 获取角度 (发送 2F, 响应 30)
// Message List (用于主界面 MessageList 表格)
const CMD_REQ_MSG_HEAD = { stationAddr: 0, telegramNr: 0x0C, expectedResponseId: 0x02 };
const CMD_REQ_MSG_BODY = { stationAddr: 0, telegramNr: 0x0D, expectedResponseId: 0x03 };
// 时间设置相关命令
const CMD_REQ_TIME = { stationAddr: 0, telegramNr: 0x1D, expectedResponseId: 0x1C }; // 请求时间 (发送 1D, 响应 1C)


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
      initialAdData: null, // 存储连接时获取的 AD 数据
      // Message List (主界面)
      messageData: { head: null, body: [], timestamp: null },
      // 设备时间原始数据 (用于 TimeSettingsDialog)
      deviceTimeRawData: null,
      // (新增) 设备角度原始数据 (用于 AngleVectorDialog)
      deviceAngleRawData: null,
      currentSerialSettings: null, // 存储当前连接的设置

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
     * (无修改) 处理连接。
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
     * (修改) 处理断开连接，增加 deviceAngleRawData 重置。
     */
    async handleSerialDisconnect(showSuccessMsg = true) {
      this.keepReading = false;

      if (this.writer) {
        try {
          await this.writer.close();
        } catch (e) { console.warn('关闭/中止 writer 时出错:', e); }
        finally { try { this.writer.releaseLock(); } catch(e) {/* ignore */} this.writer = null; }
      }
      if (this.reader) {
        try {
          await this.reader.cancel('Disconnecting');
        } catch (e) { console.warn('取消 reader 时出错:', e); }
        finally { try { this.reader.releaseLock(); } catch(e) {/* ignore */} this.reader = null; }
      }
      if (this.port && this.port.readable) {
        try { await this.port.close(); }
        catch (e) { console.error('关闭端口时出错:', e); }
        finally { this.port = null; }
      } else { this.port = null; }

      this.isSerialConnected = false;
      this.serialPortName = '';
      this.initialAdData = null;
      this.currentSerialSettings = null;
      this.messageData = { head: null, body: [], timestamp: null };
      this.deviceTimeRawData = null;
      this.deviceAngleRawData = null; // (新增) 重置设备角度数据
      this.commandQueue = [];
      this.isExecutingCommand = false;
      this.unpacker = new Unpacker();

      if (showSuccessMsg) { this.$message.info('串口已断开'); }
    },

    /**
     * @vuese
     * (无修改) 向串口写入数据。
     */
    async writeToSerial(data) {
      if (!this.writer || !this.isSerialConnected) {
        this.$message.error('写入失败：串口未连接或写入器无效');
        return false;
      }
      try {
        await this.writer.write(data);
        return true;
      } catch (error) {
        console.error('写入串口失败:', error);
        this.$message.error(`写入失败: ${error.message}`);
        await this.handleSerialDisconnect(false);
        return false;
      }
    },

    /**
     * @vuese
     * (无修改) 异步读取串口数据。
     */
    async readUntilClosed() {
      while (this.port?.readable && this.keepReading) {
        try {
          const { value, done } = await this.reader.read();
          if (done) break;
          if (value) {
            this.unpacker.addData(value);
            const frames = this.unpacker.unpack();
            for (const frame of frames) {
              this.lastReceivedFrame = frame;
              if (frame.type !== 'junk') {
                this.processFrame(frame);
              }
            }
          }
        } catch (error) {
          console.error('读取串口时出错:', error);
          this.$message.error(`读取错误: ${error.message}`);
          this.keepReading = false;
          await this.handleSerialDisconnect(false);
          break;
        }
      }
      console.log("Read loop finished.");
      if (this.isSerialConnected) {
        await this.handleSerialDisconnect(false);
      }
    },

    /**
     * @vuese
     * (修改) 处理协议帧，增加对角度响应 (0x30) 的处理。
     */
    async processFrame(frame) {
      if (frame.type === 'ack_e5') {
        console.log("Received E5 ACK");
        if (this.isExecutingCommand && this.commandQueue.length > 0) {
          const currentCommand = this.commandQueue[0];
          if (currentCommand.command.expectedResponseId === 0xE5) {
            console.log(`Command ${currentCommand.command.telegramNr} received expected E5 ACK.`);
            clearTimeout(currentCommand.timeoutTimer);
            currentCommand.resolve({ type: 'ack_e5' });
            this.commandQueue.shift();
            this.isExecutingCommand = false;
            await this.executeNextCommand();
          } else {
            console.warn("Received unexpected E5 ACK while waiting for data frame.");
          }
        }
      } else if (frame.type === 'data') {
        console.log(`Received data frame: Nr=${frame.telegramNr}, Payload length=${frame.payload.length}`);
        await this.writeToSerial(packAck()); // 发送 A2

        // 处理命令响应
        if (this.isExecutingCommand && this.commandQueue.length > 0) {
          const currentCommand = this.commandQueue[0];
          if (frame.telegramNr === currentCommand.command.expectedResponseId) {
            console.log(`Command ${currentCommand.command.telegramNr} received expected response ${frame.telegramNr}.`);
            clearTimeout(currentCommand.timeoutTimer);
            currentCommand.resolve(frame);
            this.commandQueue.shift();
            this.isExecutingCommand = false;
            await this.executeNextCommand();
          } else {
            console.warn(`Received unexpected data frame ${frame.telegramNr} while waiting for ${currentCommand.command.expectedResponseId}.`);
          }
        } else {
          console.log("Received unsolicited data frame:", frame);
        }

        // --- 根据响应 ID 更新具体数据 ---
        const responseId = frame.telegramNr;
        const payloadArray = Array.from(frame.payload);

        switch(responseId) {
          case CMD_REQ_AD_CALC.expectedResponseId: // 0x24
            console.log("Updating initialAdData with received payload.");
            this.initialAdData = payloadArray;
            break;
          case CMD_REQ_MSG_HEAD.expectedResponseId: // 0x02
            console.log("Updating messageData.head with received payload.");
            this.messageData.head = payloadArray;
            this.messageData.body = [];
            this.messageData.timestamp = Date.now();
            break;
          case CMD_REQ_MSG_BODY.expectedResponseId: // 0x03
            console.log("Updating messageData.body with received payload.");
            this.messageData.body.push(...payloadArray);
            this.messageData.timestamp = Date.now();
            break;
          case CMD_REQ_TIME.expectedResponseId: // 0x1C
            console.log("Updating deviceTimeRawData with received payload.");
            this.deviceTimeRawData = payloadArray;
            break;
          case CMD_REQ_ANGLE.expectedResponseId: // (新增) 0x30
            console.log("Updating deviceAngleRawData with received payload.");
            this.deviceAngleRawData = payloadArray;
            break;
          default:
            console.log(`Received data frame with unhandled ID: ${responseId}`);
        }
      }
    },

    /**
     * @vuese
     * (无修改) 执行初始连接命令序列。
     */
    async executeInitialSequence() {
      try {
        console.log("Executing initial sequence...");
        await this.sendCommand(CMD_REQ_TQCS);
        console.log("TQCS command successful.");
        await this.sendCommand(CMD_REQ_ACAD);
        console.log("ACAD command successful.");
        await this.sendCommand(CMD_REQ_AD_CALC);
        console.log("AD_CALC command successful.");
        await this.sendCommand(CMD_REQ_ANGLE); // 初始序列已包含获取角度
        console.log("ANGLE command successful.");
        console.log("Initial sequence completed.");
      } catch (error) {
        console.error("Error during initial command sequence:", error);
        this.$message.error(`初始命令序列失败: ${error.message || error}`);
      }
    },

    /**
     * @vuese
     * (无修改) 将命令加入队列。
     */
    sendCommand(commandDef, payload = null, timeout = 3000) {
      return new Promise((resolve, reject) => {
        const commandTask = {
          command: commandDef,
          payload: payload,
          resolve: resolve,
          reject: reject,
          timeoutTimer: setTimeout(() => {
            console.error(`Timeout waiting for response to command ${commandDef.telegramNr} (expected ${commandDef.expectedResponseId})`);
            const index = this.commandQueue.findIndex(task => task === commandTask);
            if (index > -1) this.commandQueue.splice(index, 1);
            if (this.isExecutingCommand && this.commandQueue.length === 0) {
              this.isExecutingCommand = false;
              this.executeNextCommand();
            }
            reject(new Error(`Timeout waiting for response ID ${commandDef.expectedResponseId}`));
          }, timeout)
        };
        this.commandQueue.push(commandTask);
        if (!this.isExecutingCommand) {
          this.executeNextCommand();
        }
      });
    },

    /**
     * @vuese
     * (无修改) 执行队列中的下一个命令。
     */
    async executeNextCommand() {
      if (this.isExecutingCommand || this.commandQueue.length === 0) {
        return;
      }
      this.isExecutingCommand = true;
      const task = this.commandQueue[0];

      try {
        console.log(`Executing command ${task.command.telegramNr}, expecting ${task.command.expectedResponseId}`);
        const frameToSend = pack({
          stationAddr: task.command.stationAddr,
          telegramNr: task.command.telegramNr,
          payload: task.payload || undefined
        });
        const writeSuccess = await this.writeToSerial(frameToSend);
        if (!writeSuccess) {
          clearTimeout(task.timeoutTimer);
          task.reject(new Error('Failed to write command to serial port.'));
          this.commandQueue.shift();
          this.isExecutingCommand = false;
          this.commandQueue = []; // 清空队列
        }
      } catch (error) {
        console.error(`Error executing command ${task.command.telegramNr}:`, error);
        clearTimeout(task.timeoutTimer);
        task.reject(error);
        this.commandQueue.shift();
        this.isExecutingCommand = false;
        await this.executeNextCommand();
      }
    },

    /**
     * @vuese
     * (无修改) 处理通用发送命令请求。
     */
    async handleSendCommand({ commandDef, payload, timeout }) {
      if (!this.isSerialConnected) {
        this.$message.error('串口未连接');
        throw new Error('串口未连接');
      }
      try {
        const responseFrame = await this.sendCommand(commandDef, payload, timeout);
        return responseFrame;
      } catch (error) {
        this.$message.error(`命令 ${commandDef.telegramNr} 执行失败: ${error?.message || error}`);
        throw error;
      }
    },

    // --- 处理来自特定对话框的事件 ---

    /**
     * @vuese
     * (无修改) 处理获取时间事件。
     */
    async handleFetchTime() {
      if (!this.isSerialConnected) {
        this.$message.error('串口未连接');
        return;
      }
      this.$message.info('正在发送获取时间命令 (0x1D)...');
      try {
        this.sendCommand(CMD_REQ_TIME);
      } catch (error) {
        console.error(`发送获取时间命令失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * (移除) 处理设置角度事件。
     */
    // handleSetAngle(form) { ... } // 移除此方法

    /**
     * @vuese
     * (修改) 处理获取角度事件。
     */
    async handleFetchAngle() {
      if (!this.isSerialConnected) {
        this.$message.error('串口未连接');
        return;
      }
      this.$message.info('正在发送获取角度命令 (0x2F)...');
      try {
        // (修改) 不需要 await，响应在 processFrame 中处理
        this.sendCommand(CMD_REQ_ANGLE);
      } catch (error) {
        console.error(`发送获取角度命令失败: ${error?.message || error}`);
      }
    },

    // ... (其他对话框的处理方法保持不变) ...
    handleSetDim(form) { console.log("TODO: Implement handleSetDim", form); this.$message.info("设置标幺功能待实现"); },
    handleDefaultDim() { console.log("TODO: Implement handleDefaultDim"); this.$message.info("恢复默认标幺功能待实现"); },

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