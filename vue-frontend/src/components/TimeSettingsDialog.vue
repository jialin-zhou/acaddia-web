<template>
  <el-dialog v-model="dialogVisible" title="时间设置" width="450px" @close="onCancel">
    <div class="time-display">
      <p>当前设备时间: {{ formattedDeviceTime }}</p>
    </div>
    <el-form :model="form" label-width="80px" class="time-form">
      <el-form-item label="设置日期">
        <el-date-picker
          v-model="form.date"
          type="date"
          placeholder="选择日期"
          format="YYYY-MM-DD"
          value-format="YYYY-MM-DD"
        />
      </el-form-item>
      <el-form-item label="设置时间">
        <el-time-picker
          v-model="form.time"
          placeholder="选择时间"
          format="HH:mm:ss"
          value-format="HH:mm:ss"
        />
      </el-form-item>
    </el-form>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onFetchTime">获取时间</el-button>
        <div class="spacer"></div>
        <el-button @click="onCancel">取消</el-button>
        <el-button type="primary" @click="onSetTime">设置时间</el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'TimeSettingsDialog',
  props: { visible: { type: Boolean, default: false } },
  emits: ['update:visible', 'setTime', 'fetchTime'],
  data() {
    return {
      form: {
        date: null,
        time: null,
      },
      deviceTime: new Date(), // Placeholder for time fetched from device
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    },
    formattedDeviceTime() {
        return this.deviceTime.toLocaleString();
    }
  },
  methods: {
    setCurrentTime() {
        const now = new Date();
        const yyyy = now.getFullYear();
        const mm = String(now.getMonth() + 1).padStart(2, '0');
        const dd = String(now.getDate()).padStart(2, '0');
        const hh = String(now.getHours()).padStart(2, '0');
        const min = String(now.getMinutes()).padStart(2, '0');
        const ss = String(now.getSeconds()).padStart(2, '0');
        this.form.date = `${yyyy}-${mm}-${dd}`;
        this.form.time = `${hh}:${min}:${ss}`;
    },
    onCancel() {
      this.dialogVisible = false;
    },
    onSetTime() {
      if (!this.form.date || !this.form.time) {
        this.$message.error('请先选择完整的日期和时间');
        return;
      }
      const newDateTime = `${this.form.date} ${this.form.time}`;
      this.$emit('setTime', newDateTime);
      this.dialogVisible = false;
    },
    onFetchTime() {
      this.$emit('fetchTime');
      // You would typically update `deviceTime` based on a response from the parent.
      // For now, we'll just log it.
      this.$message.info('已发送获取时间命令');
    },
  },
  watch: {
      visible(val) {
          if(val) {
              this.setCurrentTime();
          }
      }
  }
};
</script>

<style scoped>
.time-display {
    text-align: center;
    font-size: 1.2em;
    color: #606266;
    margin-bottom: 20px;
    border: 1px solid #dcdfe6;
    padding: 15px;
    border-radius: 4px;
    background-color: #f9f9f9;
}
.dialog-footer {
  display: flex;
  width: 100%;
}
.spacer {
  flex-grow: 1;
}
.el-date-picker, .el-time-picker {
    width: 100%;
}
</style>
