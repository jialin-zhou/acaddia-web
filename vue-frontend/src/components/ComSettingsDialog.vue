<template>
  <!-- 串口设置对话框 -->
  <el-dialog
      v-model="dialogVisible"
      title="串口设置 (Web Serial API)"
      width="500px"
      @close="onCancel"
      :close-on-click-modal="false"
  >
    <!-- 浏览器不支持 Web Serial API 时的警告 -->
    <el-alert v-if="!isWebSerialSupported" type="warning" show-icon :closable="false">
      当前浏览器不支持 Web Serial API，无法访问本地串口。请使用 Chrome, Edge 或 Opera 浏览器。
    </el-alert>

    <!-- 串口设置表单 -->
    <el-form
        ref="formRef"
        :model="form"
        label-width="80px"
        :disabled="!isWebSerialSupported"
    >
      <!-- COM口选择 -->
      <el-form-item label="COM口" prop="portName">
        <el-input v-model="selectedPortInfo" placeholder="点击选择端口" readonly :disabled="isConnected">
          <template #append>
            <el-button @click="selectPort" :disabled="isConnected">选择端口</el-button>
          </template>
        </el-input>
      </el-form-item>

      <!-- 波特率 -->
      <el-form-item label="波特率" prop="baudRate">
        <el-select v-model="form.baudRate" placeholder="请选择波特率" :disabled="isConnected" style="width: 100%;">
          <el-option label="9600" :value="9600" />
          <el-option label="19200" :value="19200" />
          <el-option label="38400" :value="38400" />
          <el-option label="57600" :value="57600" />
          <el-option label="115200" :value="115200" />
        </el-select>
      </el-form-item>
      <!-- 数据位 -->
      <el-form-item label="数据位" prop="dataBits">
        <el-select v-model="form.dataBits" placeholder="请选择数据位" :disabled="isConnected" style="width: 100%;">
          <el-option label="8" :value="8" />
          <el-option label="7" :value="7" />
        </el-select>
      </el-form-item>
      <!-- 校验位 -->
      <el-form-item label="校验位" prop="parity">
        <el-select v-model="form.parity" placeholder="请选择校验位" :disabled="isConnected" style="width: 100%;">
          <el-option label="None" value="none" />
          <el-option label="Odd" value="odd" />
          <el-option label="Even" value="even" />
        </el-select>
      </el-form-item>
      <!-- 停止位 -->
      <el-form-item label="停止位" prop="stopBits">
        <el-select v-model="form.stopBits" placeholder="请选择停止位" :disabled="isConnected" style="width: 100%;">
          <el-option label="1" :value="1" />
          <el-option label="2" :value="2" />
        </el-select>
      </el-form-item>
    </el-form>

    <!-- 底部操作按钮 -->
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onCancel">关闭</el-button>
        <el-button type="danger" :disabled="!isConnected || !isWebSerialSupported" @click="onDisconnect">断开</el-button>
        <el-button type="success" :disabled="isConnected || !port || !isWebSerialSupported" @click="onConnect">连接</el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'ComSettingsDialog',
  props: {
    /**
     * @vuese
     * 控制对话框是否显示。
     */
    visible: { type: Boolean, default: false },
    /**
     * @vuese
     * 当前串口是否已连接。
     */
    isConnected: { type: Boolean, default: false },
    /**
     * @vuese
     * (新增) 从 App.vue 传入的当前已连接的 port 对象，主要用于断开连接时的检查。
     */
    currentPort: { type: Object, default: null },
  },
  /**
   * @vuese
   * 定义组件触发的事件。
   * update:visible: 用于 v-model 双向绑定。
   * connect: 请求连接，携带 port 对象和配置。
   * disconnect: 请求断开。
   */
  emits: ['update:visible', 'connect', 'disconnect'],
  data() {
    return {
      /**
       * @vuese
       * 本地存储用户通过浏览器选择的 `SerialPort` 对象。
       */
      port: null,
      /**
       * @vuese
       * 显示在输入框中的端口信息 (例如厂商ID等)。
       */
      selectedPortInfo: '',
      /**
       * @vuese
       * 存储串口配置的表单数据。
       */
      form: {
        // portName 不再需要，由 port 对象管理
        baudRate: 9600,
        dataBits: 8,
        parity: 'none', // Web Serial API 标准使用小写 (none, odd, even)
        stopBits: 1,
        // Web Serial API 特有的流控选项
        flowControl: "none",
        bufferSize: 255, // 缓冲区大小，可选
      },
      /**
       * @vuese
       * 检测当前浏览器是否支持 Web Serial API。
       */
      isWebSerialSupported: ('serial' in navigator),
    };
  },
  computed: {
    /**
     * @vuese
     * 用于 v-model 绑定 `visible` prop 的计算属性。
     */
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); },
    },
  },
  watch: {
    /**
     * @vuese
     * 当外部的 isConnected 变为 false 时 (例如 App.vue 中处理了断开)，
     * 重置本地存储的 port 对象和显示的端口信息。
     */
    isConnected(newVal) {
      if (!newVal) {
        this.port = null;
        this.selectedPortInfo = '';
      }
    }
  },
  methods: {
    /**
     * @vuese
     * (重写) 核心功能：触发浏览器 `navigator.serial.requestPort()` API，
     * 请求用户从弹窗中选择一个串口设备。
     */
    async selectPort() {
      if (!this.isWebSerialSupported) {
        this.$message.error('当前浏览器不支持 Web Serial API');
        return;
      }
      try {
        // 弹出浏览器原生串口选择框
        this.port = await navigator.serial.requestPort();

        // (可选) 获取端口信息用于UI显示
        const info = this.port.getInfo();
        // 格式化 USB 厂商ID 和 产品ID 为十六进制
        const vendorId = info.usbVendorId?.toString(16).padStart(4, '0');
        const productId = info.usbProductId?.toString(16).padStart(4, '0');
        this.selectedPortInfo = `已选 (VID: ${vendorId}, PID: ${productId})`;

        this.$message.success('端口已选择，请点击连接');
      } catch (e) {
        // 用户可能取消了选择框
        this.$message.error(`选择端口失败: ${e.message}`);
        this.port = null;
        this.selectedPortInfo = '';
      }
    },

    /**
     * @vuese
     * 点击关闭或遮罩时调用。
     */
    onCancel() {
      this.dialogVisible = false;
    },

    /**
     * @vuese
     * (重写) 核心功能：当点击连接时，尝试打开之前选定的串口。
     * 成功后将 port 对象和设置 emit 给父组件 (App.vue)。
     */
    async onConnect() {
      if (!this.port) {
        this.$message.error('请先点击 "选择端口" 选择一个串口。');
        return;
      }
      if (this.isConnected) {
        this.$message.warning('串口已连接');
        return;
      }

      this.$message.info(`正在打开端口 ${this.selectedPortInfo || ''}...`);
      try {
        // 核心：使用用户选择的设置打开端口
        await this.port.open({
          baudRate: this.form.baudRate,
          dataBits: this.form.dataBits,
          stopBits: this.form.stopBits,
          parity: this.form.parity,
          flowControl: this.form.flowControl,
          bufferSize: this.form.bufferSize,
        });

        this.$message.success('端口打开成功');
        // 将打开的 port 对象和配置参数 emit 给 App.vue
        this.$emit('connect', { port: this.port, settings: { ...this.form } });
        // 连接成功后一般由父组件关闭对话框
        // this.dialogVisible = false;

      } catch (e) {
        // 打开失败 (例如端口被占用)
        this.$message.error(`打开端口失败: ${e.message}`);
        this.port = null; // 打开失败，重置 port 对象
        this.selectedPortInfo = '';
        this.$emit('disconnect'); // 触发断开事件以重置 App.vue 状态
      }
    },

    /**
     * @vuese
     * (重写) 核心功能：当点击断开时，仅 emit 'disconnect' 事件。
     * 实际的关闭 (close) 逻辑在父组件 App.vue 中执行，因为它持有读写锁。
     */
    async onDisconnect() {
      // 使用从 App.vue 传入的 currentPort 来确保关闭的是当前活动的端口
      if (!this.currentPort || !this.isConnected) {
        this.$message.warning('串口未连接');
        return;
      }
      try {
        // 这里仅发送断开事件，由 App.vue 处理关闭逻辑
        // App.vue 会释放读写锁并调用 port.close()
        this.$emit('disconnect');
        this.$message.info('已请求断开串口');
      } catch (e) {
        // 这个 catch 几乎不会执行，因为主要逻辑在 App.vue
        console.error('请求断开时出错:', e);
        this.$message.error(`请求断开时出错: ${e.message}`);
      }
    },
  },
};
</script>

<style scoped>
/* 确保选择框和输入框宽度一致 */
.el-select, .el-input { width: 100%; }
/* 调整“选择端口”按钮的内边距 */
.el-input-group__append { padding: 0 10px; }
</style>