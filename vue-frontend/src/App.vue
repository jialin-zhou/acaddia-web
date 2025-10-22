<template>
  <el-container class="main-container">
    <el-header class="main-header">
      <div class="title">Acaddia-Web 测控终端</div>

      <div class="header-actions">
        <el-button-group>
          <el-button text @click="openDialog('com')">串口设置</el-button>
          <el-button text @click="openDialog('time')">时间设置</el-button>
          <el-button text @click="openDialog('angle')">角度矢量</el-button>
          <el-button text @click="openDialog('dim')">标幺设置</el-button>
        </el-button-group>
      </div>

      <div class="spacer" />

      <div class="connection-status">
        <el-tag :type="isSerialConnected ? 'success' : 'danger'" size="large">
          {{ serialStatus }}
        </el-tag>
      </div>
    </el-header>

    <el-container>
      <el-aside width="220px" class="main-aside">
        <el-menu :default-active="activeView" class="main-menu" @select="handleMenuSelect">
          <el-menu-item index="Main">主界面</el-menu-item>
          <el-menu-item index="DataParsing">串口数据收发</el-menu-item>
          <el-menu-item index="Tqcs">同期参数</el-menu-item>
          <el-menu-item index="AdParams">AD参数</el-menu-item>
          <el-menu-item index="AdAdjust">通道校准</el-menu-item>
          <el-menu-item index="Tqml">同期命令</el-menu-item>
          <el-menu-item index="Message">通信报文</el-menu-item>
        </el-menu>
      </el-aside>

      <el-main class="main-content">
        <component
            :is="activeViewComponent"
            :is-serial-connected="isSerialConnected"
            :initial-ad-data="initialAdData"
            :current-serial-settings="currentSerialSettings"
            :write-to-serial="writeToSerial"
            :last-received-frame="lastReceivedFrame"
            @send-command="handleSendCommand"
        />
      </el-main>
    </el-container>

    <com-settings-dialog
        v-model:visible="dialogVisible.com"
        :is-connected="isSerialConnected"
        :current-port="port"
        @connect="handleSerialConnect"
        @disconnect="handleSerialDisconnect"
    />
    <time-settings-dialog v-model:visible="dialogVisible.time" @set-time="handleSetTime" @fetch-time="handleFetchTime" />
    <angle-vector-dialog v-model:visible="dialogVisible.angle" @apply="handleSetAngle" @fetch="handleFetchAngle" />
    <dim-settings-dialog v-model:visible="dialogVisible.dim" @confirm="handleSetDim" @default="handleDefaultDim" />
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

// --- 命令定义 (参考 DeviceInteractionService.java) ---
// 注意: telegramNr 是发送命令中的 ID，expectedResponseId 是期望收到的响应帧中的 ID
const CMD_REQ_TQCS = { stationAddr: 0, telegramNr: 0x23, expectedResponseId: 0x22 };
const CMD_REQ_ACAD = { stationAddr: 0, telegramNr: 0x21, expectedResponseId: 0x20 };
const CMD_REQ_AD_CALC = { stationAddr: 0, telegramNr: 0x25, expectedResponseId: 0x24 };
const CMD_REQ_ANGLE = { stationAddr: 0, telegramNr: 0x2F, expectedResponseId: 0x30 };
// 其他命令...
// [FIX] Comment out unused command definitions until methods are implemented
// const CMD_SET_TIME = { stationAddr: 0, telegramNr: 0x1D, expectedResponseId: 0xE5 }; // 假设设置时间响应 E5
// const CMD_REQ_TIME = { stationAddr: 0, telegramNr: 0x1C, expectedResponseId: 0x1C }; // 假设获取时间响应 0x1C
// const CMD_SET_ANGLE = { stationAddr: 0, telegramNr: 0x2E, expectedResponseId: 0xE5 }; // 假设设置角度响应 E5
// ... 其他命令定义


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
      currentSerialSettings: null, // 存储当前连接的设置

      // --- Web Serial API State ---
      port: null,       // SerialPort 对象
      reader: null,     // ReadableStreamDefaultReader
      writer: null,     // WritableStreamDefaultWriter
      keepReading: false, // 控制读循环的标志
      unpacker: new Unpacker(), // 协议解包器实例
      lastReceivedFrame: null, // 存储最后收到的已解析帧 (用于传递给子组件)
      // 用于命令序列的状态管理
      commandQueue: [], // 要执行的命令队列 { command, resolve, reject, timeoutTimer }
      isExecutingCommand: false, // 标记是否正在等待命令响应
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
  methods: {
    handleMenuSelect(index) {
      this.activeView = index;
    },
    openDialog(dialogName) {
      this.dialogVisible[dialogName] = true;
    },

    /**
     * @vuese
     * (重写) 处理来自 ComSettingsDialog 的连接事件。
     * 存储 port 对象和设置，启动读循环，执行初始命令序列。
     * @param {object} connectionInfo - 包含 port 和 settings 的对象。
     */
    async handleSerialConnect({ port, settings }) {
      if (this.isConnected || !port) return;

      this.port = port;
      this.currentSerialSettings = settings;
      this.serialPortName = `VID:${port.getInfo().usbVendorId?.toString(16)}, PID:${port.getInfo().usbProductId?.toString(16)}`; // 更新显示名称

      try {
        // 获取写入器
        const writableStream = this.port.writable;
        if (!writableStream) throw new Error("Writable stream not available.");
        this.writer = writableStream.getWriter();

        // 获取读取器并开始读循环
        const readableStream = this.port.readable;
        if (!readableStream) throw new Error("Readable stream not available.");
        this.reader = readableStream.getReader();
        this.keepReading = true;
        this.readUntilClosed(); // 启动异步读循环

        this.isSerialConnected = true;
        this.dialogVisible.com = false; // 关闭对话框
        this.$message.success(`串口已连接`);

        // 连接成功后，执行初始命令序列获取数据
        this.$message.info('正在执行初始命令序列...');
        await this.executeInitialSequence();
        this.$message.success('初始命令序列执行完毕');

      } catch (error) {
        console.error('连接后初始化读写器或执行命令失败:', error);
        this.$message.error(`连接后初始化失败: ${error.message}`);
        await this.handleSerialDisconnect(false); // 尝试清理资源
      }
    },

    /**
     * @vuese
     * (重写) 处理断开连接事件。
     * 停止读循环，释放读写器，关闭端口。
     * @param {boolean} [showSuccessMsg=true] 是否显示成功断开的消息
     */
    async handleSerialDisconnect(showSuccessMsg = true) {
      this.keepReading = false; // 指示读循环停止

      // 释放写入器
      if (this.writer) {
        try {
          await this.writer.close(); // 或 writer.abort()
        } catch (e) {
          console.warn('关闭 writer 时出错:', e);
        } finally {
          this.writer = null;
        }
      }

      // 释放读取器
      if (this.reader) {
        try {
          // 重要: 先取消读取操作，否则 close() 可能卡住
          await this.reader.cancel('Disconnecting');
          this.reader.releaseLock();
        } catch (e) {
          console.warn('取消或释放 reader 时出错:', e);
        } finally {
          this.reader = null;
        }
      }


      // 关闭端口
      if (this.port && this.port.readable) { // 检查端口是否仍可访问
        try {
          await this.port.close();
        } catch (e) {
          console.error('关闭端口时出错:', e);
        } finally {
          this.port = null;
        }
      } else {
        this.port = null; // 确保 port 被重置
      }


      // 重置状态
      this.isSerialConnected = false;
      this.serialPortName = '';
      this.initialAdData = null;
      this.currentSerialSettings = null;
      this.commandQueue = [];
      this.isExecutingCommand = false;
      this.unpacker = new Unpacker(); // 重置解包器状态

      if (showSuccessMsg) {
        this.$message.info('串口已断开');
      }
    },

    /**
     * @vuese
     * (新增) 向串口写入数据。
     * @param {Uint8Array} data - 要写入的字节数据。
     */
    async writeToSerial(data) {
      if (!this.writer || !this.isSerialConnected) {
        this.$message.error('写入失败：串口未连接或写入器无效');
        return false;
      }
      try {
        await this.writer.write(data);
        // console.log('Data written:', data); // 调试日志
        return true;
      } catch (error) {
        console.error('写入串口失败:', error);
        this.$message.error(`写入失败: ${error.message}`);
        // 发生写入错误时，可能需要断开连接
        await this.handleSerialDisconnect(false);
        return false;
      }
    },

    /**
     * @vuese
     * (新增) 异步读取串口数据直到断开连接。
     * 处理收到的数据块，送入 Unpacker，处理解析结果。
     */
    async readUntilClosed() {
      while (this.port?.readable && this.keepReading) {
        try {
          // console.log("Attempting to read..."); // 调试
          const { value, done } = await this.reader.read();
          // console.log("Read result:", { value, done }); // 调试

          if (done) {
            // 读取流已关闭 (例如端口被拔出或程序调用了 reader.cancel())
            console.log("Reader stream closed.");
            break; // 退出循环
          }

          if (value) {
            // console.log('Received raw:', value); // 调试原始数据
            // --- 将数据传递给 DataParsingView ---
            // 为了简化，我们只传递解析后的帧给所有子组件
            // 如果 DataParsingView 需要原始数据，可以另行处理或修改
            // this.lastRawData = value; // 如果需要传递原始数据

            // 将收到的数据块添加到解包器
            this.unpacker.addData(value);
            // 尝试解包
            const frames = this.unpacker.unpack();
            // console.log("Unpacked frames:", frames); // 调试

            // 处理所有解析出的帧/ACK
            for (const frame of frames) {
              this.lastReceivedFrame = frame; // 更新最后收到的帧，传递给子组件
              this.processFrame(frame); // 调用帧处理逻辑
            }
          }
        } catch (error) {
          // 读取时发生错误 (例如设备断开)
          console.error('读取串口时出错:', error);
          this.$message.error(`读取错误: ${error.message}`);
          this.keepReading = false; // 停止读取循环
          // 可以在这里触发自动断开逻辑
          await this.handleSerialDisconnect(false);
          break; // 退出循环
        }
      }
      console.log("Read loop finished.");
      // 确保在循环结束后断开连接状态被正确设置
      if (this.isSerialConnected) {
        await this.handleSerialDisconnect(false);
      }
    },

    /**
     * @vuese
     * (新增) 处理从 Unpacker 解析出的单个帧或 ACK。
     * @param {object} frame - 解析出的帧对象 ({ type, ... })。
     */
    async processFrame(frame) {
      // --- 可以在这里将收到的帧信息发送给 DataParsingView ---
      // 例如，格式化后发送事件：
      // let logMsg = '';
      // if (frame.type === 'data') {
      //    logMsg = `HEX: ${Array.from(frame.raw).map(b => b.toString(16).padStart(2, '0').toUpperCase()).join(' ')}`;
      // } else if (frame.type === 'ack_e5') {
      //    logMsg = 'ACK: E5';
      // }
      // if (logMsg) {
      //   // 使用事件总线或直接调用 DataParsingView 的方法 (如果 ref 可用)
      // }

      if (frame.type === 'ack_e5') {
        // 处理 E5 ACK
        console.log("Received E5 ACK");
        // 检查是否有命令在等待 E5 响应
        if (this.isExecutingCommand && this.commandQueue.length > 0) {
          const currentCommand = this.commandQueue[0];
          if (currentCommand.command.expectedResponseId === 0xE5) {
            console.log(`Command ${currentCommand.command.telegramNr} received expected E5 ACK.`);
            clearTimeout(currentCommand.timeoutTimer);
            currentCommand.resolve({ type: 'ack_e5' }); // 解决 Promise
            this.commandQueue.shift(); // 移除已处理的命令
            this.isExecutingCommand = false;
            await this.executeNextCommand(); // 执行下一个命令
          } else {
            console.warn("Received unexpected E5 ACK while waiting for data frame.");
            // 根据协议，可能需要忽略或视为错误
          }
        }
      } else if (frame.type === 'data') {
        // 处理 68 ... 16 数据帧
        console.log(`Received data frame: Nr=${frame.telegramNr}, Payload length=${frame.payload.length}`);

        // 1. 发送 ACK (0xA2)
        await this.writeToSerial(packAck());

        // 2. 检查是否是当前等待的命令的响应
        if (this.isExecutingCommand && this.commandQueue.length > 0) {
          const currentCommand = this.commandQueue[0];
          if (frame.telegramNr === currentCommand.command.expectedResponseId) {
            console.log(`Command ${currentCommand.command.telegramNr} received expected response ${frame.telegramNr}.`);
            clearTimeout(currentCommand.timeoutTimer); // 清除超时定时器
            currentCommand.resolve(frame); // 使用解析出的帧对象解决 Promise
            this.commandQueue.shift(); // 从队列中移除已完成的命令
            this.isExecutingCommand = false; // 标记命令执行完成
            // 触发执行队列中的下一个命令 (如果还有的话)
            await this.executeNextCommand();
          } else {
            // 收到了数据帧，但 ID 与当前等待的不匹配
            console.warn(`Received unexpected data frame ${frame.telegramNr} while waiting for ${currentCommand.command.expectedResponseId}.`);
            // 根据协议，可能需要忽略这个帧，或者取消当前命令并报错
          }
        } else {
          // 收到了数据帧，但当前没有命令在等待响应 (可能是设备主动上报?)
          console.log("Received unsolicited data frame:", frame);
          // 可根据 frame.telegramNr 处理不同的主动上报数据
        }

        // 3. 特殊处理：如果收到的是 AD 计算值 (ID 0x24)，更新 initialAdData
        if (frame.telegramNr === CMD_REQ_AD_CALC.expectedResponseId) {
          console.log("Updating initialAdData with received payload.");
          // 将 Uint8Array 转换为普通的 number 数组，以便 Vue 正确处理
          this.initialAdData = Array.from(frame.payload);
        }
        // 可在此处添加对其他 telegramNr 的处理逻辑，例如更新其他视图的数据
        // else if (frame.telegramNr === CMD_REQ_TQCS.expectedResponseId) { ... }

      }
    },

    /**
     * @vuese
     * (新增) 执行初始连接时的命令序列 (TQCS -> ACAD -> AD_CALC -> ANGLE)。
     * 使用命令队列和 Promise 来确保按顺序执行并等待响应。
     */
    async executeInitialSequence() {
      try {
        console.log("Executing initial sequence...");
        await this.sendCommand(CMD_REQ_TQCS);       // 发送 TQCS 并等待 0x22
        console.log("TQCS command successful.");
        await this.sendCommand(CMD_REQ_ACAD);       // 发送 ACAD 并等待 0x20
        console.log("ACAD command successful.");
        await this.sendCommand(CMD_REQ_AD_CALC);    // 发送 AD_CALC 并等待 0x24 (这将更新 initialAdData)
        console.log("AD_CALC command successful.");
        await this.sendCommand(CMD_REQ_ANGLE);      // 发送 ANGLE 并等待 0x30
        console.log("ANGLE command successful.");
        console.log("Initial sequence completed.");
      } catch (error) {
        console.error("Error during initial command sequence:", error);
        this.$message.error(`初始命令序列失败: ${error.message || error}`);
        // 可能需要断开连接
        // await this.handleSerialDisconnect(false);
      }
    },

    /**
     * @vuese
     * (新增) 将命令添加到队列，并返回一个 Promise，该 Promise 在收到预期响应或超时后解决/拒绝。
     * @param {object} commandDef - 命令定义对象 (e.g., CMD_REQ_TQCS)。
     * @param {Uint8Array} [payload=null] - 命令的可选负载数据。
     * @param {number} [timeout=3000] - 等待响应的超时时间 (毫秒)。
     * @returns {Promise<object>} A Promise resolving with the parsed response frame or rejecting on error/timeout.
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
            // 从队列中移除超时的命令
            const index = this.commandQueue.findIndex(task => task === commandTask);
            if (index > -1) this.commandQueue.splice(index, 1);
            // 如果当前正在执行的是这个超时的命令，则标记为结束并尝试下一个
            if (this.isExecutingCommand && this.commandQueue.length === 0) { // 可能需要更精确的检查
              this.isExecutingCommand = false;
              this.executeNextCommand();
            }
            reject(new Error(`Timeout waiting for response ID ${commandDef.expectedResponseId}`));
          }, timeout)
        };
        this.commandQueue.push(commandTask);
        // 如果当前没有命令在执行，则立即开始执行队列中的第一个命令
        if (!this.isExecutingCommand) {
          this.executeNextCommand();
        }
      });
    },

    /**
     * @vuese
     * (新增) 执行命令队列中的下一个命令。
     */
    async executeNextCommand() {
      if (this.isExecutingCommand || this.commandQueue.length === 0) {
        return; // 如果正在执行或队列为空，则返回
      }

      this.isExecutingCommand = true; // 标记开始执行
      const task = this.commandQueue[0]; // 获取队列中的第一个任务

      try {
        console.log(`Executing command ${task.command.telegramNr}, expecting ${task.command.expectedResponseId}`);
        // 使用 pack 函数构建完整的命令帧
        const frameToSend = pack({
          stationAddr: task.command.stationAddr,
          telegramNr: task.command.telegramNr,
          payload: task.payload || undefined // 如果 payload 为 null 则不传递
          // funcCode1, funcCode2 可以使用 pack 中的默认值或在 commandDef 中指定
        });
        // 发送命令
        const writeSuccess = await this.writeToSerial(frameToSend);
        if (!writeSuccess) {
          // 写入失败时，清除超时，拒绝 Promise，并停止执行
          clearTimeout(task.timeoutTimer);
          task.reject(new Error('Failed to write command to serial port.'));
          this.commandQueue.shift(); // 移除失败的命令
          this.isExecutingCommand = false;
          // 停止后续命令还是尝试下一个？取决于策略，这里先停止
          this.commandQueue = []; // 清空队列
        }
        // 写入成功后，等待 readUntilClosed 中的 processFrame 来处理响应并 resolve/reject Promise
      } catch (error) {
        // 构建或发送命令时出错
        console.error(`Error executing command ${task.command.telegramNr}:`, error);
        clearTimeout(task.timeoutTimer);
        task.reject(error);
        this.commandQueue.shift(); // 移除失败的命令
        this.isExecutingCommand = false;
        await this.executeNextCommand(); // 尝试执行下一个
      }
    },

    /**
     * @vuese
     * (新增) 处理来自子组件的通用发送命令请求。
     * @param {object} event - 包含 commandDef, payload, timeout 的事件对象。
     */
    async handleSendCommand({ commandDef, payload, timeout }) {
      if (!this.isSerialConnected) {
        this.$message.error('串口未连接');
        return;
      }
      try {
        // [FIX] Comment out unused variable assignment
        /* const responseFrame = */ await this.sendCommand(commandDef, payload, timeout);
        this.$message.success(`命令 ${commandDef.telegramNr} 执行成功`);
        // 可以选择性地将 responseFrame 发送回触发的子组件，或通过 lastReceivedFrame 传递
        // console.log("Command response:", responseFrame);
      } catch (error) {
        this.$message.error(`命令 ${commandDef.telegramNr} 执行失败: ${error.message}`);
      }
    },

    // --- 处理来自特定对话框的事件 ---
    handleSetTime(dateTimeString) {
      console.log("TODO: Implement handleSetTime", dateTimeString);
      // 1. 将 dateTimeString 转换为设备需要的字节格式 payload
      // const payload = ...;
      // 2. 发送命令
      // this.handleSendCommand({ commandDef: CMD_SET_TIME, payload });
      this.$message.info("设置时间功能待实现");
    },
    handleFetchTime() {
      console.log("TODO: Implement handleFetchTime");
      // this.handleSendCommand({ commandDef: CMD_REQ_TIME });
      this.$message.info("获取时间功能待实现");
    },
    handleSetAngle(form) {
      console.log("TODO: Implement handleSetAngle", form);
      // 1. 将 form 数据转换为设备需要的字节格式 payload
      // const payload = ...;
      // 2. 发送命令
      // this.handleSendCommand({ commandDef: CMD_SET_ANGLE, payload });
      this.$message.info("设置角度功能待实现");
    },
    handleFetchAngle() {
      console.log("TODO: Implement handleFetchAngle");
      // this.handleSendCommand({ commandDef: CMD_REQ_ANGLE }); // 重复获取
      this.$message.info("获取角度功能待实现 (初始连接已获取)");
    },
    handleSetDim(form) {
      console.log("TODO: Implement handleSetDim", form);
      this.$message.info("设置标幺功能待实现");
    },
    handleDefaultDim() {
      console.log("TODO: Implement handleDefaultDim");
      this.$message.info("恢复默认标幺功能待实现");
    },

  },
  // 添加 beforeUnmount 钩子以确保在组件卸载时断开连接
  async beforeUnmount() {
    if (this.isSerialConnected) {
      await this.handleSerialDisconnect(false);
    }
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