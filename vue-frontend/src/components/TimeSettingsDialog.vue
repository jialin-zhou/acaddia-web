<template>
  <!-- 时间设置对话框 -->
  <el-dialog
      v-model="dialogVisible"
      title="时间设置"
      width="450px"
      :close-on-click-modal="false"
      @close="onCancel"
  >
    <!-- 显示从设备获取的当前时间 -->
    <div class="time-display">
      <p>当前设备时间: {{ formattedDeviceTime }}</p>
    </div>

    <!-- 设置新时间的表单 -->
    <el-form
        :model="form"
        label-width="80px"
        class="time-form"
    >
      <!-- 日期选择器 -->
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
      <!-- 时间选择器 -->
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

    <!-- 底部操作按钮 -->
    <template #footer>
      <span class="dialog-footer">
        <!-- 获取时间按钮 -->
        <el-button @click="onFetchTime">
          获取时间
        </el-button>
        <div class="spacer" />
        <!-- 取消按钮 -->
        <el-button @click="onCancel">
          取消
        </el-button>
        <!-- 同步表单按钮 -->
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
    /**
     * @vuese
     * 控制对话框是否显示。
     */
    visible: { type: Boolean, default: false },
    /**
     * @vuese
     * 从父组件传入的设备原始时间字节数组 (来自 0x22 响应)。
     */
    deviceTimeRawData: { type: Array, default: null },
  },
  /**
   * @vuese
   * 定义组件触发的事件。
   * update:visible: 用于 v-model 双向绑定。
   * fetchTime: 通知父组件执行“获取时间”操作。
   */
  // (修改) 移除 'setTime'，因为设置时间功能已移除
  emits: ['update:visible', 'fetchTime'],
  data() {
    return {
      // 存储表单数据（日期和时间）
      form: {
        date: null,
        time: null,
      },
      /**
       * @vuese
       * 存储从设备获取并解析后的 `Date` 对象。
       */
      deviceTime: null,
    };
  },
  computed: {
    /**
     * @vuese
     * 用于 v-model 绑定 `visible` prop 的计算属性。
     */
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    },
    /**
     * @vuese
     * 格式化 `deviceTime` (Date 对象) 为易读的本地时间字符串。
     */
    formattedDeviceTime() {
      // 如果 deviceTime 为 null，则显示提示信息
      return this.deviceTime
          ? this.deviceTime.toLocaleString('zh-CN', { hour12: false })
          : '--- (请获取)';
    }
  },
  watch: {
    /**
     * @vuese
     * 监听对话框打开 (visible 变为 true)。
     * 当打开时，自动用当前电脑的系统时间填充表单。
     */
    visible(val) {
      if(val) {
        this.setCurrentTimeInForm(); // 打开时用系统时间填充表单
        // (修改) 打开对话框时不再重置 deviceTime
      }
    },
    /**
     * @vuese
     * 监听从父组件传入的原始时间数据。
     * 当数据更新且合法时，调用解析方法。
     */
    deviceTimeRawData(newData) {
      // (修改) 检查长度 >= 5 (根据 C++ 解析逻辑，需要 payload 的前 5 个字节: 索引 0-4)
      if (newData && newData.length >= 5) {
        try {
          // 调用解析方法
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
        this.deviceTime = null; // 数据格式错误，清空
      }
    }
  },
  methods: {
    /** * @vuese
     * 设置表单默认值为当前电脑的系统时间。
     */
    setCurrentTimeInForm() {
      const now = new Date();
      const yyyy = now.getFullYear();
      const mm = String(now.getMonth() + 1).padStart(2, '0'); // 月份从0开始
      const dd = String(now.getDate()).padStart(2, '0');
      const hh = String(now.getHours()).padStart(2, '0');
      const min = String(now.getMinutes()).padStart(2, '0');
      const ss = String(now.getSeconds()).padStart(2, '0');

      this.form.date = `${yyyy}-${mm}-${dd}`;
      this.form.time = `${hh}:${min}:${ss}`;
    },
    /**
     * @vuese
     * 点击取消或关闭按钮时调用。
     */
    onCancel() {
      this.dialogVisible = false;
    },
    /**
     * @vuese
     * (修改) “同步表单”按钮点击处理。
     * 将获取到的 `deviceTime` (设备时间) 填充到表单中。
     * (注意：此版本不再发送设置时间命令)
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

        // 更新表单
        this.form.date = `${yyyy}-${mm}-${dd}`;
        this.form.time = `${hh}:${min}:${ss}`;
        this.$message.success('表单已同步为设备时间');

      } catch (e) {
        console.error("同步表单失败:", e);
        this.$message.error(`同步表单失败: ${e.message}`);
      }
    },
    /**
     * @vuese
     * (无修改) “获取时间”按钮点击处理。
     * 通知父组件 (App.vue) 发送获取时间的命令。
     */
    onFetchTime() {
      this.$emit('fetchTime');
    },

    /**
     * @vuese
     * (无修改) 核心逻辑：解析从设备接收到的原始时间数据。
     * 协议：
     * 索引 0-1: 16位小端, 自 1984-01-01 以来的天数 (从1开始)
     * 索引 2-4: 24位小端, 自午夜以来的毫秒数
     * @param {number[]} rawData - 原始字节数组 (payload)。
     */
    parseDeviceTime(rawData) {
      // payload 索引 0, 1 是天数; 2, 3, 4 是毫秒
      // 组合天数 (小端)
      const days_since_1984 = rawData[0] | (rawData[1] << 8);
      // 组合毫秒数 (小端)
      const msecs_since_midnight = rawData[2] | (rawData[3] << 8) | (rawData[4] << 16);

      // 基准日期 (1984年1月1日 UTC)
      const baseDate = new Date(Date.UTC(1984, 0, 1)); // 月份从0开始

      // 计算目标日期的午夜时间戳
      // (days_since_1984 - 1) 是因为天数从1开始
      const targetTimestamp = baseDate.getTime() + (days_since_1984 - 1) * (24 * 60 * 60 * 1000);
      const targetDateMidnight = new Date(targetTimestamp);

      // 获取目标日期的 UTC 年、月、日
      const year = targetDateMidnight.getUTCFullYear();
      const month = targetDateMidnight.getUTCMonth();
      const day = targetDateMidnight.getUTCDate();

      // 从毫秒数中解析出时、分、秒
      let totalSeconds = Math.floor(msecs_since_midnight / 1000);
      let ms = msecs_since_midnight % 1000;
      let hours = Math.floor(totalSeconds / 3600) % 24;
      let minutes = Math.floor((totalSeconds % 3600) / 60);
      let seconds = totalSeconds % 60;

      // 使用解析出的 年,月,日,时,分,秒 创建一个本地时间 Date 对象
      // (注意: new Date(Y,M,D,h,m,s) 会使用本地时区)
      this.deviceTime = new Date(year, month, day, hours, minutes, seconds, ms);

      console.log("解析后的设备时间 (本地):", this.deviceTime.toLocaleString('zh-CN', { hour12: false }));
    },
  }
};
</script>

<style scoped>
/* 设备时间显示区域样式 */
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
/* 底部按钮布局 */
.dialog-footer {
  display: flex;
  width: 100%;
}
/* 弹性空白 */
.spacer {
  flex-grow: 1;
}
/* 确保日期和时间选择器占满宽度 */
.el-date-picker,
.el-time-picker {
  width: 100%;
}
</style>