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
          串口: {{ serialStatus }}
        </el-tag>
        <el-tag
          :type="isWsConnected ? 'success' : 'info'"
          size="large"
          style="margin-left: 10px;"
        >
          服务器: {{ wsStatus }}
        </el-tag>
      </div>
    </el-header>

    <el-container>
      <!-- Side Menu -->
      <el-aside
        width="220px"
        class="main-aside"
      >
        <el-menu
          :default-active="activeView"
          class="main-menu"
          @select="handleMenuSelect"
        >
          <el-menu-item index="DataParsing">
            数据解析
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

      <!-- Main Content -->
      <el-main class="main-content">
        <component
          :is="activeViewComponent"
          :stomp-client="stompClient"
        />
      </el-main>
    </el-container>

    <!-- Dialogs for settings -->
    <com-settings-dialog
      v-model:visible="dialogVisible.com"
      :is-connected="isSerialConnected"
      :available-ports="availablePorts"
      @connect="handleSerialConnect"
      @disconnect="handleSerialDisconnect"
      @fetch-ports="handleFetchPorts"
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

// Dialog Components
import ComSettingsDialog from './components/ComSettingsDialog.vue';
import TimeSettingsDialog from './components/TimeSettingsDialog.vue';
import AngleVectorDialog from './components/AngleVectorDialog.vue';
import DimSettingsDialog from './components/DimSettingsDialog.vue';

// View Components
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
    DataParsingView, TqcsView, AdParamsView, AdAdjustView, TqmlView, MessageView,
  },
  data() {
    return {
      activeView: 'DataParsing',
      isWsConnected: false,
      isSerialConnected: false,
      stompClient: null,
      dialogVisible: {
        com: false, time: false, angle: false, dim: false,
      },
      availablePorts: [],
    };
  },
  computed: {
    activeViewComponent() {
      return `${this.activeView}View`;
    },
    wsStatus() { return this.isWsConnected ? '已连接' : '已断开'; },
    serialStatus() { return this.isSerialConnected ? '已连接' : '已断开'; },
  },
  created() {
    this.connectWs();
  },
  methods: {
    handleMenuSelect(index) {
      this.activeView = index;
    },
    log(content, type = 'info') { console.log(`[${type}] ${content}`); },
    connectWs() {
      this.log('开始连接到服务器...');
      const socket = new SockJS('/ws');
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
        switch (msg.type) {
          case 'serial-status':
            this.isSerialConnected = msg.payload.connected;
            this.log(`串口状态更新: ${this.isSerialConnected ? '已连接' : '已断开'}`, 'success');
            if (this.isSerialConnected) this.dialogVisible.com = false;
            break;
          case 'available-ports':
            this.availablePorts = msg.payload;
            this.log(`获取可用串口列表: ${this.availablePorts.join(', ')}`, 'info');
            break;
          default:
            // This is now less important as logs are handled in DataParsingView
        }
      } catch (e) {
        // console.error("Failed to parse backend message", e);
      }
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
        if (dialogName === 'com') this.handleFetchPorts();
      } else {
        this.$message.error(`未知的对话框: ${dialogName}`);
      }
    },
    // Dialog Handlers
    handleSerialConnect(settings) { this.sendCommand({ type: 'serial-connect', payload: settings }); },
    handleSerialDisconnect() { this.sendCommand({ type: 'serial-disconnect' }); },
    handleFetchPorts() { this.sendCommand({ type: 'serial-fetch-ports' }); },
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
