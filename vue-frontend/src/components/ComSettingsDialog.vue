<template>
  <el-dialog
      v-model="dialogVisible"
      title="串口设置 (Web Serial API)"
      width="500px"
      @close="onCancel"
      :close-on-click-modal="false"
  >
    <el-alert v-if="!isWebSerialSupported" type="warning" show-icon :closable="false">
      当前浏览器不支持 Web Serial API，无法访问本地串口。请使用 Chrome, Edge 或 Opera 浏览器。
    </el-alert>

    <el-form
        ref="formRef"
        :model="form"
        label-width="80px"
        :disabled="!isWebSerialSupported"
    >
      <el-form-item label="COM口" prop="portName">
        <el-input v-model="selectedPortInfo" placeholder="点击选择端口" readonly :disabled="isConnected">
          <template #append>
            <el-button @click="selectPort" :disabled="isConnected">选择端口</el-button>
          </template>
        </el-input>
      </el-form-item>

      <el-form-item label="波特率" prop="baudRate">
        <el-select v-model="form.baudRate" placeholder="请选择波特率" :disabled="isConnected" style="width: 100%;">
          <el-option label="9600" :value="9600" />
          <el-option label="19200" :value="19200" />
          <el-option label="38400" :value="38400" />
          <el-option label="57600" :value="57600" />
          <el-option label="115200" :value="115200" />
        </el-select>
      </el-form-item>
      <el-form-item label="数据位" prop="dataBits">
        <el-select v-model="form.dataBits" placeholder="请选择数据位" :disabled="isConnected" style="width: 100%;">
          <el-option label="8" :value="8" />
          <el-option label="7" :value="7" />
        </el-select>
      </el-form-item>
      <el-form-item label="校验位" prop="parity">
        <el-select v-model="form.parity" placeholder="请选择校验位" :disabled="isConnected" style="width: 100%;">
          <el-option label="None" value="none" />
          <el-option label="Odd" value="odd" />
          <el-option label="Even" value="even" />
        </el-select>
      </el-form-item>
      <el-form-item label="停止位" prop="stopBits">
        <el-select v-model="form.stopBits" placeholder="请选择停止位" :disabled="isConnected" style="width: 100%;">
          <el-option label="1" :value="1" />
          <el-option label="2" :value="2" />
        </el-select>
      </el-form-item>
    </el-form>
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
    visible: { type: Boolean, default: false },
    isConnected: { type: Boolean, default: false },
    // 新增: 从 App.vue 传入的 port 对象，用于断开连接
    currentPort: { type: Object, default: null },
  },
  emits: ['update:visible', 'connect', 'disconnect'],
  data() {
    return {
      port: null, // 本地存储用户选择的 port 对象
      selectedPortInfo: '', // 显示给用户看的端口信息
      form: {
        // portName 不再需要，由 port 对象管理
        baudRate: 9600,
        dataBits: 8,
        parity: 'none', // Web Serial API 使用小写
        stopBits: 1,
        // Web Serial API 特有的流控选项
        flowControl: "none",
        bufferSize: 255, // 可选，默认即可
      },
      isWebSerialSupported: ('serial' in navigator), // 检测浏览器是否支持 Web Serial
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); },
    },
  },
  watch: {
    // 当外部的 isConnected 变为 false 时 (例如 App.vue 中处理了断开)，重置本地状态
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
     * (重写) 触发浏览器请求用户选择串口。
     */
    async selectPort() {
      if (!this.isWebSerialSupported) {
        this.$message.error('当前浏览器不支持 Web Serial API');
        return;
      }
      try {
        // 请求用户选择串口
        this.port = await navigator.serial.requestPort();
        // 获取端口信息用于显示 (可选)
        const info = this.port.getInfo();
        this.selectedPortInfo = `已选择端口 (Vendor: ${info.usbVendorId?.toString(16)}, Product: ${info.usbProductId?.toString(16)})`;
        this.$message.success('端口已选择，请点击连接');
      } catch (e) {
        this.$message.error(`选择端口失败: ${e.message}`);
        this.port = null;
        this.selectedPortInfo = '';
      }
    },

    onCancel() {
      // 如果用户取消时选择了端口但未连接，最好也清除选择
      // if (!this.isConnected) {
      //   this.port = null;
      //   this.selectedPortInfo = '';
      // }
      this.dialogVisible = false;
    },

    /**
     * @vuese
     * (重写) 当点击连接时，尝试打开之前选定的串口。
     * 成功后将 port 对象和设置 emit 给父组件。
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
        // 使用用户选择的设置打开端口
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
        // this.dialogVisible = false; // 由 App.vue 控制关闭

      } catch (e) {
        this.$message.error(`打开端口失败: ${e.message}`);
        this.port = null; // 打开失败，重置 port 对象
        this.selectedPortInfo = '';
        this.$emit('disconnect'); // 触发断开事件以重置 App.vue 状态
      }
    },

    /**
     * @vuese
     * (重写) 当点击断开时，关闭端口并 emit 事件。
     */
    async onDisconnect() {
      // 使用从 App.vue 传入的 currentPort 来确保关闭的是当前活动的端口
      if (!this.currentPort || !this.isConnected) {
        this.$message.warning('串口未连接');
        return;
      }
      try {
        // 在关闭之前，可能需要取消正在进行的读写操作 (见 App.vue 实现)
        // 这里仅发送断开事件，由 App.vue 处理关闭逻辑
        this.$emit('disconnect');
        this.$message.info('已请求断开串口');
      } catch (e) {
        // 这个 catch 可能不会执行，因为主要逻辑在 App.vue
        console.error('请求断开时出错:', e);
        this.$message.error(`请求断开时出错: ${e.message}`);
      }
    },
  },
};
</script>

<style scoped>
.el-select, .el-input { width: 100%; }
.el-input-group__append { padding: 0 10px; } /* 调整按钮内边距 */
</style>