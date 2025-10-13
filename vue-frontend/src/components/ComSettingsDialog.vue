<template>
  <el-dialog
    v-model="dialogVisible"
    title="串口设置"
    width="500px"
    @close="onCancel"
  >
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
          placeholder="请选择串口"
          :disabled="isConnected"
        >
          <el-option
            v-for="item in availablePorts"
            :key="item"
            :label="item"
            :value="item"
          />
        </el-select>
        <el-button
          class="refresh-button"
          :disabled="isConnected"
          @click="fetchAvailablePorts"
        >
          刷新
        </el-button>
      </el-form-item>
      <el-form-item
        label="波特率"
        prop="baudRate"
      >
        <el-select
          v-model="form.baudRate"
          placeholder="请选择波特率"
          :disabled="isConnected"
        >
          <el-option
            label="9600"
            :value="9600"
          />
          <el-option
            label="19200"
            :value="19200"
          />
          <el-option
            label="38400"
            :value="38400"
          />
          <el-option
            label="57600"
            :value="57600"
          />
          <el-option
            label="115200"
            :value="115200"
          />
        </el-select>
      </el-form-item>
      <el-form-item
        label="数据位"
        prop="dataBits"
      >
        <el-select
          v-model="form.dataBits"
          placeholder="请选择数据位"
          :disabled="isConnected"
        >
          <el-option
            label="8"
            :value="8"
          />
          <el-option
            label="7"
            :value="7"
          />
        </el-select>
      </el-form-item>
      <el-form-item
        label="校验位"
        prop="parity"
      >
        <el-select
          v-model="form.parity"
          placeholder="请选择校验位"
          :disabled="isConnected"
        >
          <el-option
            label="None"
            value="None"
          />
          <el-option
            label="Odd"
            value="Odd"
          />
          <el-option
            label="Even"
            value="Even"
          />
        </el-select>
      </el-form-item>
      <el-form-item
        label="停止位"
        prop="stopBits"
      >
        <el-select
          v-model="form.stopBits"
          placeholder="请选择停止位"
          :disabled="isConnected"
        >
          <el-option
            label="1"
            :value="1"
          />
          <el-option
            label="1.5"
            :value="1.5"
          />
          <el-option
            label="2"
            :value="2"
          />
        </el-select>
      </el-form-item>
    </el-form>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onCancel">
          关闭
        </el-button>
        <el-button
          type="danger"
          :disabled="!isConnected"
          @click="onDisconnect"
        >
          断开
        </el-button>
        <el-button
          type="success"
          :disabled="isConnected"
          @click="onConnect"
        >
          连接
        </el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'ComSettingsDialog',
  props: {
    visible: {
      type: Boolean,
      default: false,
    },
    isConnected: {
      type: Boolean,
      default: false,
    },
    availablePorts: {
      type: Array,
      default: () => [],
    }
  },
  emits: ['update:visible', 'connect', 'disconnect', 'fetchPorts'],
  data() {
    return {
      form: {
        port: '',
        baudRate: 115200,
        dataBits: 8,
        parity: 'None',
        stopBits: 1,
      },
    };
  },
  computed: {
    dialogVisible: {
      get() {
        return this.visible;
      },
      set(value) {
        this.$emit('update:visible', value);
      },
    },
  },
  watch: {
    // When the dialog becomes visible, if no port is selected and there are available ports, select the first one.
    visible(newValue) {
      if (newValue && !this.form.port && this.availablePorts.length > 0) {
        this.form.port = this.availablePorts[0];
      }
    }
  },
  methods: {
    fetchAvailablePorts() {
      this.$emit('fetchPorts');
    },
    onCancel() {
      this.dialogVisible = false;
    },
    onConnect() {
      if (!this.form.port) {
        this.$message.error('请先选择一个COM口');
        return;
      }
      this.$emit('connect', this.form);
    },
    onDisconnect() {
      this.$emit('disconnect');
    }
  }
};
</script>

<style scoped>
.refresh-button {
  margin-left: 10px;
}
.el-select {
  width: 100%;
}
</style>
