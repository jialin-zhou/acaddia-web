<template>
  <el-container class="main-container">
    <!-- Header -->
    <el-header class="main-header">
      <div class="title">Acaddia-Web 测控终端</div>

      <!-- Settings Buttons -->
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
          :is-serial-connected="isSerialConnected"
          :initial-ad-data="initialAdData"
        />
      </el-main>
    </el-container>

    <!-- Dialogs for settings -->
    <com-settings-dialog
      v-model:visible="dialogVisible.com"
      :is-connected="isSerialConnected"
      @connect="handleSerialConnect"
      @disconnect="handleSerialDisconnect"
    />
    <time-settings-dialog v-model:visible="dialogVisible.time" />
    <angle-vector-dialog v-model:visible="dialogVisible.angle" />
    <dim-settings-dialog v-model:visible="dialogVisible.dim" />

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

// Import Dialog Components
import ComSettingsDialog from './components/ComSettingsDialog.vue';
import TimeSettingsDialog from './components/TimeSettingsDialog.vue';
import AngleVectorDialog from './components/AngleVectorDialog.vue';
import DimSettingsDialog from './components/DimSettingsDialog.vue';

export default {
  name: 'App',
  components: {
    MainView, DataParsingView, TqcsView, AdParamsView, AdAdjustView, TqmlView, MessageView,
    ComSettingsDialog, TimeSettingsDialog, AngleVectorDialog, DimSettingsDialog,
  },
  data() {
    return {
      activeView: 'Main',
      isSerialConnected: false,
      dialogVisible: { com: false, time: false, angle: false, dim: false },
      serialPortName: '',
      initialAdData: null, // **新增**: 用于存储连接成功时获取的初始 AD 数据
    };
  },
  computed: {
    activeViewComponent() {
      const viewName = `${this.activeView}View`;
      return Object.keys(this.$options.components).includes(viewName) ? viewName : 'MainView';
    },
    serialStatus() {
      if (this.isSerialConnected && this.serialPortName) {
        return `${this.serialPortName}: 已连接`;
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
     * 处理来自 ComSettingsDialog 的连接事件。
     * 它向后端发送连接请求，并在成功后接收初始的 AD 数据。
     * @param {object} settings 连接设置 (e.g., { port, baudRate, ... }).
     */
    async handleSerialConnect(settings) {
      this.$message.info(`正在连接到 ${settings.port}...`);
      try {
        const response = await fetch('http://localhost:8080/api/device/connect', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(settings),
        });

        // 首先检查 HTTP 响应状态是否 OK
        if (!response.ok) {
          const errorResult = await response.json();
          throw new Error(errorResult.error || `服务器返回错误: ${response.status}`);
        }

        // 如果响应 OK，则后端返回的是 AD 数据的 JSON 数组
        const adData = await response.json();

        this.isSerialConnected = true;
        this.serialPortName = settings.port;
        this.initialAdData = adData; // **核心**: 保存获取到的初始数据
        this.dialogVisible.com = false;
        this.$message.success(`成功连接到 ${settings.port} 并获取到初始数据`);

      } catch (error) {
        console.error('串口连接或数据获取失败:', error);
        this.$message.error(`连接失败: ${error.message}`);
        this.isSerialConnected = false;
        this.serialPortName = '';
        this.initialAdData = null;
      }
    },

    /**
     * @vuese
     * 处理断开连接事件。
     */
    async handleSerialDisconnect() {
      try {
        await fetch('http://localhost:8080/api/device/disconnect', { method: 'POST' });
        this.$message.info('串口已断开');
      } catch (error) {
        console.error('断开连接时出错:', error);
        // 即使后端调用失败，前端也应该更新状态
      } finally {
        this.isSerialConnected = false;
        this.serialPortName = '';
        this.initialAdData = null;
      }
    },
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
