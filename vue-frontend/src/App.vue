<template>
  <el-container class="main-container">
    <!-- Header -->
    <el-header class="main-header">
      <div class="title">
        Acaddia-Web 测控终端
      </div>

      <!-- Settings Buttons -->
      <div class="header-actions">
        <el-button-group>
          <el-button text @click="openDialog('com')">串口设置</el-button>
          <el-button text @click="openDialog('time')">时间设置</el-button>
          <el-button text @click="openDialog('angle')">角度矢量</el-button>
          <el-button text @click="openDialog('dim')">标幺设置</el-button>
        </el-button-group>
        <el-button text type="primary" @click="handleReadStatus" style="margin-left: 10px;">读取状态</el-button>
      </div>

      <div class="spacer" />

      <div class="connection-status">
        <el-tag :type="isSerialConnected ? 'success' : 'danger'" size="large">
          {{ serialStatus }}
        </el-tag>
        <el-tag :type="isWsConnected ? 'success' : 'info'" size="large" style="margin-left: 10px;">
          服务器: {{ wsStatus }}
        </el-tag>
      </div>
    </el-header>

    <el-container>
      <!-- Side Menu -->
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

      <!-- Main Content -->
      <el-main class="main-content">
        <component
          :is="activeViewComponent"
          :stomp-client="stompClient"
          :serial-data-in="receivedSerialData"
          @send-serial-data="handleSendSerialData"
        />
      </el-main>
    </el-container>

    <!-- Dialogs for settings -->
    <com-settings-dialog
      v-model:visible="dialogVisible.com"
      :is-connected="isSerialConnected"
      @connect="handleSerialConnect"
      @disconnect="handleSerialDisconnect"
      @data-received="handleSerialDataReceived"
    />
    <time-settings-dialog
      v-model:visible="dialogVisible.time"
      @set-time="handleTimeSet"
      @fetch-time="handleTimeFetch"
    />
    <angle-vector-dialog
      v-model:visible="dialogVisible.angle"
      @fetch="handleAngleFetch"
      @apply="handleAngleApply"
    />
    <dim-settings-dialog
      v-model:visible="dialogVisible.dim"
      @confirm="handleDimConfirm"
      @default="handleDimDefault"
    />
  </el-container>
</template>

<script>
import SockJS from 'sockjs-client';
import Stomp from 'webstomp-client';
import { pack, Unpacker } from './utils/acadia-protocol.js'; // Import Unpacker

// Dialog Components
import ComSettingsDialog from './components/ComSettingsDialog.vue';
import TimeSettingsDialog from './components/TimeSettingsDialog.vue';
import AngleVectorDialog from './components/AngleVectorDialog.vue';
import DimSettingsDialog from './components/DimSettingsDialog.vue';

// View Components
import MainView from './components/views/MainView.vue';
import DataParsingView from './components/views/DataParsingView.vue';
import TqcsView from './components/views/TqcsView.vue';
import AdParamsView from './components/views/AdParamsView.vue';
import AdAdjustView from './components/views/AdAdjustView.vue';
import TqmlView from './components/views/TqmlView.vue';
import MessageView from './components/views/MessageView.vue';

export default {
  name: 'App',
  components: {
    ComSettingsDialog, TimeSettingsDialog, AngleVectorDialog, DimSettingsDialog,
    MainView, DataParsingView, TqcsView, AdParamsView, AdAdjustView, TqmlView, MessageView,
  },
  data() {
    return {
      activeView: 'Main',
      isWsConnected: false,
      isSerialConnected: false,
      stompClient: null,
      dialogVisible: { com: false, time: false, angle: false, dim: false },
      serialPort: null,
      serialPortName: '',
      receivedSerialData: null,
      msgCounter: 0, // Counter for F1 field generation, mimics Msg_cntr
      serialUnpacker: new Unpacker(), // Create an instance of the unpacker
    };
  },
  computed: {
    activeViewComponent() {
      return `${this.activeView}View`;
    },
    wsStatus() { return this.isWsConnected ? '已连接' : '已断开'; },
    serialStatus() {
      if (this.isSerialConnected && this.serialPortName) {
        return `${this.serialPortName}: 已连接`;
      }
      return '串口: 已断开';
    },
  },
  created() {
    this.connectWs();
  },
  methods: {
    handleMenuSelect(index) { this.activeView = index; },
    log(content, type = 'info') { console.log(`[${type}] ${content}`); },
    connectWs() {
      this.log('开始连接到服务器...');
      const socket = new SockJS('http://localhost:8080/ws');
      this.stompClient = Stomp.over(socket);
      this.stompClient.connect({}, frame => {
        this.isWsConnected = true;
        this.log(`服务器连接成功: ${frame}`, 'success');
        this.stompClient.subscribe('/topic/status', tick => this.handleBackendMessage(tick.body));
      }, error => {
        this.isWsConnected = false;
        this.log(`服务器连接失败: ${error}`, 'error');
        setTimeout(() => this.connectWs(), 5000);
      });
    },
    handleBackendMessage(message) {
      try {
        const msg = JSON.parse(message);
        if (msg.type === 'some-other-status') { /* ... */ }
      } catch (e) { /* Ignore */ }
    },
    sendCommand(command) {
      if (this.stompClient && this.stompClient.connected) {
        this.stompClient.send('/app/send-command', JSON.stringify(command), {});
      } else {
        this.$message.error('发送失败：未连接到服务器');
      }
    },
    openDialog(dialogName) {
      if (Object.prototype.hasOwnProperty.call(this.dialogVisible, dialogName)) {
        this.dialogVisible[dialogName] = true;
      } else {
        this.$message.error(`未知的对话框: ${dialogName}`);
      }
    },

    // --- Protocol-based Write Operation ---
    handleReadStatus() {
      if (!this.isSerialConnected) {
        this.$message.error('请先连接串口');
        return;
      }

      // Generate F1 field based on the message counter, mimicking C++ logic
      const f1 = (this.msgCounter << 5) | 0x09;

      // Use the correct, discovered function codes
      const command = pack({
        stationAddr: 0x01,       // Example station address
        funcCode1: f1,           // Generated F1
        funcCode2: 0x80,         // Correct F2 for this command
        telegramNr: 37,          // Correct Telegram Number for reading main AD data
        payload: new Uint8Array(), // No payload for this command
      });

      this.handleSendSerialData(command);
      this.$message.info('读取状态命令(NR=37)已发送');

      // Increment the message counter for the next command, ensuring it stays within 3 bits (0-7)
      this.msgCounter = (this.msgCounter + 1) & 0x07;
    },

    // --- Web Serial API Handlers ---
    handleSerialConnect(connection) {
      this.isSerialConnected = true;
      this.serialPort = connection.port;
      this.serialPortName = connection.portName;
      this.serialUnpacker = new Unpacker(); // Reset unpacker on new connection
      this.dialogVisible.com = false;
    },
    handleSerialDisconnect() {
      this.isSerialConnected = false;
      this.serialPort = null;
      this.serialPortName = '';
    },
    handleSerialDataReceived(data) {
      this.serialUnpacker.addData(data);
      const frames = this.serialUnpacker.unpack();
      if (frames.length > 0) {
        this.receivedSerialData = frames;
      }
    },
    async handleSendSerialData(data) {
      if (!this.serialPort || !this.serialPort.writable) {
        this.$message.error('发送失败：串口未连接或不可写。');
        return;
      }
      const writer = this.serialPort.writable.getWriter();
      try {
        await writer.write(data);
      } catch (error) {
        console.error('Error writing to serial port:', error);
        this.$message.error(`发送数据失败: ${error.message}`);
      } finally {
        writer.releaseLock();
      }
    },

    // --- STOMP-based Dialog Handlers ---
    handleTimeSet(newTime) { this.sendCommand({ type: 'time-set', payload: newTime }); },
    handleTimeFetch() { this.sendCommand({ type: 'time-fetch' }); },
    handleAngleFetch() { this.sendCommand({ type: 'angle-fetch' }); },
    handleAngleApply(settings) { this.sendCommand({ type: 'angle-apply', payload: settings }); },
    handleDimConfirm(settings) { this.sendCommand({ type: 'dim-confirm', payload: settings }); },
    handleDimDefault() { this.sendCommand({ type: 'dim-default' }); },
  },
};
</script>

<style>
html, body, #app, .main-container { height: 100%; margin: 0; padding: 0; background-color: #f0f2f5; }
.main-header { display: flex; align-items: center; background-color: #fff; border-bottom: 1px solid #dcdfe6; padding: 0 20px; }
.title { font-size: 24px; font-weight: bold; color: #303133; }
.header-actions { margin-left: 40px; }
.spacer { flex-grow: 1; }
.main-aside { background-color: #fff; border-right: 1px solid #dcdfe6; display: flex; flex-direction: column; }
.main-menu { border-right: none; flex-grow: 1; }
.main-content { padding: 20px; }
</style>
