<template>
  <el-dialog
    v-model="dialogVisible"
    title="时间设置"
    width="450px"
    :close-on-click-modal="false"
    @close="onCancel"
  >
    <div class="time-display">
      <p>当前设备时间: {{ formattedDeviceTime }}</p>
    </div>
    <el-form
      :model="form"
      label-width="80px"
      class="time-form"
    >
      <el-form-item label="设置日期">
        <el-date-picker
          v-model="form.date"
          type="date"
          placeholder="选择日期"
          format="YYYY-MM-DD"
          value-format="YYYY-MM-DD"
          style="width: 100%;"
        />
      </el-form-item>
      <el-form-item label="设置时间">
        <el-time-picker
          v-model="form.time"
          placeholder="选择时间"
          format="HH:mm:ss"
          value-format="HH:mm:ss"
          style="width: 100%;"
        />
      </el-form-item>
    </el-form>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onFetchTime">
          获取时间
        </el-button>
        <div class="spacer" />
        <el-button @click="onCancel">
          取消
        </el-button>
        <el-button
          type="primary"
          @click="syncFormFromDeviceTime"
        >
          同步表单
        </el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'TimeSettingsDialog',
  props: {
    visible: { type: Boolean, default: false },
    deviceTimeRawData: { type: Array, default: null },
  },
  // (修改) 移除 'setTime'
  emits: ['update:visible', 'fetchTime'],
  data() {
    return {
      form: {
        date: null,
        time: null,
      },
      deviceTime: null, // 存储解析后的设备时间 Date 对象
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    },
    formattedDeviceTime() {
      return this.deviceTime ? this.deviceTime.toLocaleString('zh-CN', { hour12: false }) : '--- (请获取)';
    }
  },
  watch: {
    visible(val) {
      if(val) {
        this.setCurrentTimeInForm(); // 打开时用系统时间填充表单
        // 不再重置 deviceTime
      }
    },
    deviceTimeRawData(newData) {
      // 检查长度 >= 5 (根据 C++ 解析逻辑，需要 payload 的前 5 个字节: indices 0-4)
      if (newData && newData.length >= 5) {
        try {
          this.parseDeviceTime(newData);
          this.$message.success('设备时间已更新');
        } catch(e) {
          console.error("解析设备时间失败:", e);
          this.$message.error(`解析设备时间失败: ${e.message}`);
          this.deviceTime = null; // 解析失败则清空
        }
      } else if (newData) { // newData 存在但长度不足 5
        console.warn("收到的设备时间数据长度不足 (需要 >= 5):", newData);
        this.$message.warning('收到的设备时间数据格式不正确');
        this.deviceTime = null;
      }
    }
  },
  methods: {
    /** @vuese 设置表单默认值为当前系统时间 */
    setCurrentTimeInForm() {
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
    /**
     * @vuese
     * (修改) 同步表单按钮点击处理。
     * 将获取到的设备时间填充到表单中。
     */
    syncFormFromDeviceTime() {
      if (!this.deviceTime) {
        this.$message.warning('请先点击 "获取时间" 获取设备当前时间');
        return;
      }
      try {
        const dt = this.deviceTime; // 使用已解析的 Date 对象
        const yyyy = dt.getFullYear();
        const mm = String(dt.getMonth() + 1).padStart(2, '0');
        const dd = String(dt.getDate()).padStart(2, '0');
        const hh = String(dt.getHours()).padStart(2, '0');
        const min = String(dt.getMinutes()).padStart(2, '0');
        const ss = String(dt.getSeconds()).padStart(2, '0');

        this.form.date = `${yyyy}-${mm}-${dd}`;
        this.form.time = `${hh}:${min}:${ss}`;
        this.$message.success('表单已同步为设备时间');

      } catch (e) {
        console.error("同步表单失败:", e);
        this.$message.error(`同步表单失败: ${e.message}`);
      }
      // 不关闭对话框 this.dialogVisible = false;
      // 不再发送事件 this.$emit('setTime', payload);
    },
    /**
     * @vuese
     * (无修改) 获取时间按钮点击处理。
     */
    onFetchTime() {
      this.$emit('fetchTime');
    },

    /**
     * @vuese
     * (无修改) 解析从设备接收到的原始时间数据。
     */
    parseDeviceTime(rawData) {
      // payload 索引 0, 1 是天数; 2, 3, 4 是毫秒
      const days_since_1984 = rawData[0] | (rawData[1] << 8);
      const msecs_since_midnight = rawData[2] | (rawData[3] << 8) | (rawData[4] << 16);

      const baseDate = new Date(Date.UTC(1984, 0, 1));
      const targetTimestamp = baseDate.getTime() + (days_since_1984 - 1) * (24 * 60 * 60 * 1000);
      const targetDateMidnight = new Date(targetTimestamp);

      const year = targetDateMidnight.getUTCFullYear();
      const month = targetDateMidnight.getUTCMonth();
      const day = targetDateMidnight.getUTCDate();

      let totalSeconds = Math.floor(msecs_since_midnight / 1000);
      let ms = msecs_since_midnight % 1000; // 保留毫秒解析，即使 C++ 可能没用到
      let hours = Math.floor(totalSeconds / 3600) % 24;
      let minutes = Math.floor((totalSeconds % 3600) / 60);
      let seconds = totalSeconds % 60;

      this.deviceTime = new Date(year, month, day, hours, minutes, seconds, ms); // 创建本地时间

      console.log("Parsed device time (local):", this.deviceTime.toLocaleString('zh-CN', { hour12: false }));
    },
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
.el-date-picker,
.el-time-picker {
  width: 100%;
}
</style>