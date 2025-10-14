<template>
  <el-dialog
    v-model="dialogVisible"
    title="串口设置"
    width="500px"
    @close="onCancel"
  >
    <el-alert type="warning" show-icon :closable="false" style="margin-bottom: 20px;">
      请注意：此功能仅支持 Chrome、Edge 或 Opera 浏览器。
    </el-alert>
    <el-form
      ref="formRef"
      :model="form"
      label-width="80px"
    >
      <el-form-item
        label="COM口"
        prop="port"
      >
        <el-select
          v-model="form.port"
          placeholder="请点击刷新授权串口"
          :disabled="isConnected"
        >
          <el-option
            v-for="item in availablePorts"
            :key="item.id"
            :label="item.name"
            :value="item.id"
          />
        </el-select>
        <el-button
          class="refresh-button"
          :disabled="isConnected"
          @click="requestPortAccess"
        >
          刷新/授权
        </el-button>
      </el-form-item>
      <el-form-item label="波特率" prop="baudRate">
        <el-select v-model="form.baudRate" placeholder="请选择波特率" :disabled="isConnected">
          <el-option label="9600" :value="9600" />
          <el-option label="19200" :value="19200" />
          <el-option label="38400" :value="38400" />
          <el-option label="57600" :value="57600" />
          <el-option label="115200" :value="115200" />
        </el-select>
      </el-form-item>
      <el-form-item label="数据位" prop="dataBits">
        <el-select v-model="form.dataBits" placeholder="请选择数据位" :disabled="isConnected">
          <el-option label="8" :value="8" />
          <el-option label="7" :value="7" />
        </el-select>
      </el-form-item>
      <el-form-item label="校验位" prop="parity">
        <el-select v-model="form.parity" placeholder="请选择校验位" :disabled="isConnected">
          <el-option label="None" value="none" />
          <el-option label="Odd" value="odd" />
          <el-option label="Even" value="even" />
        </el-select>
      </el-form-item>
      <el-form-item label="停止位" prop="stopBits">
        <el-select v-model="form.stopBits" placeholder="请选择停止位" :disabled="isConnected">
          <el-option label="1" :value="1" />
          <el-option label="2" :value="2" />
        </el-select>
      </el-form-item>
    </el-form>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onCancel">关闭</el-button>
        <el-button type="danger" :disabled="!isConnected" @click="onDisconnect">断开</el-button>
        <el-button type="success" :disabled="isConnected" @click="onConnect">连接</el-button>
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
  },
  emits: ['update:visible', 'connect', 'disconnect', 'data-received'],
  data() {
    return {
      form: {
        port: null, baudRate: 9600, dataBits: 8, parity: 'none', stopBits: 1,
      },
      availablePorts: [],
      serialPort: null,
      reader: null,
      keepReading: false, // Flag to control the read loop
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); },
    },
  },
  watch: {
    visible(newValue) {
      if (newValue && this.checkApiSupport()) {
        this.loadGrantedPorts();
      }
    }
  },
  mounted() {
    if ('serial' in navigator) {
      navigator.serial.addEventListener('connect', this.handlePortChange);
      navigator.serial.addEventListener('disconnect', this.handlePortChange);
    }
  },
  beforeUnmount() {
    if ('serial' in navigator) {
      navigator.serial.removeEventListener('connect', this.handlePortChange);
      navigator.serial.removeEventListener('disconnect', this.handlePortChange);
    }
    this.onDisconnect();
  },
  methods: {
    checkApiSupport() {
      if (!('serial' in navigator)) {
        this.$message.error('您的浏览器不支持Web Serial API，请使用最新版的Chrome、Edge或Opera。');
        return false;
      }
      return true;
    },
    handlePortChange(e) {
      this.$message.info(`串口设备已${e.type === 'connect' ? '连接' : '断开'}，请刷新列表。`);
      this.loadGrantedPorts();
      if (e.type === 'disconnect' && this.serialPort === e.port) {
        this.onDisconnect();
      }
    },
    async requestPortAccess() {
      if (!this.checkApiSupport()) return;
      try {
        await navigator.serial.requestPort();
        await this.loadGrantedPorts();
      } catch (e) {
        if (e.name !== 'NotFoundError') this.$message.error(`请求串口权限失败: ${e.message}`);
      }
    },
    async loadGrantedPorts() {
      const ports = await navigator.serial.getPorts();
      this.availablePorts = ports.map((port, index) => {
        const info = port.getInfo();
        const id = `vid-${info.usbVendorId}-pid-${info.usbProductId}`;
        const name = `COM${index + 1} (Vendor: ${info.usbVendorId}, Product: ${info.usbProductId})`;
        return { id, name, rawPort: port };
      });
      if (!this.form.port && this.availablePorts.length > 0) {
        this.form.port = this.availablePorts[0].id;
      }
    },
    onCancel() {
      this.dialogVisible = false;
    },
    async onConnect() {
      if (this.isConnected || this.serialPort) return;
      const selectedPortInfo = this.availablePorts.find(p => p.id === this.form.port);
      if (!selectedPortInfo) {
        this.$message.error('请先选择一个有效的串口。');
        return;
      }
      this.serialPort = selectedPortInfo.rawPort;
      try {
        await this.serialPort.open({ 
          baudRate: this.form.baudRate,
          dataBits: this.form.dataBits,
          stopBits: this.form.stopBits,
          parity: this.form.parity,
        });
        this.$message.success('串口连接成功！');
        this.keepReading = true;
        this.$emit('connect', { port: this.serialPort, portName: selectedPortInfo.name.split(' ')[0] });
        this.readLoop();
      } catch (e) {
        this.$message.error(`打开串口失败: ${e.message}`);
        this.serialPort = null;
      }
    },
    async onDisconnect() {
      this.keepReading = false; // Signal the read loop to stop
      if (this.reader) {
        try {
          await this.reader.cancel(); // This will cause the read() promise to reject and exit the loop
        } catch (error) { /* Ignore cancel errors, it's expected */ }
      }
      // The readLoop's finally block will handle releasing the lock.
      // We wait a moment to ensure the loop has exited and the lock is released before closing.
      setTimeout(async () => {
        if (this.serialPort) {
          try {
            await this.serialPort.close();
          } catch (e) { /* Ignore close errors */ }
          this.serialPort = null;
        }
        if (this.isConnected) {
          this.$message.info('串口已断开');
          this.$emit('disconnect');
        }
      }, 100); // A small delay is often helpful
    },
    async readLoop() {
      while (this.serialPort && this.serialPort.readable && this.keepReading) {
        this.reader = this.serialPort.readable.getReader();
        try {
          while (this.keepReading) {
            const { value, done } = await this.reader.read();
            if (done) break; // This happens if the reader is cancelled
            if (value) this.$emit('data-received', value);
          }
        } catch (error) {
          if (this.keepReading && !error.toString().includes('The operation was cancelled')) {
            console.error('Read loop error:', error);
          }
        } finally {
          this.reader.releaseLock();
          this.reader = null;
        }
      }
    },
  },
};
</script>

<style scoped>
.refresh-button { margin-left: 10px; }
.el-select { width: 100%; }
</style>
