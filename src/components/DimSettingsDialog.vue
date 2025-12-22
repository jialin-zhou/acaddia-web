<template>
  <el-dialog
      v-model="dialogVisible"
      title="标幺设置"
      width="500px"
      @close="onCancel"
      @open="syncFormWithProps"
  >
    <el-form
        :model="form"
        label-position="top"
    >
      <el-card
          shadow="never"
          header="全局标幺值显示设置"
      >
        <el-radio-group
            v-model="form.globalScale"
            class="vertical-radio-group"
        >
          <el-radio
              label="4000H"
              size="large"
              border
          >
            100% --> 4000H (基值: 16384)
          </el-radio>
          <el-radio
              label="2000H"
              size="large"
              border
          >
            100% --> 2000H (基值: 8192)
          </el-radio>
        </el-radio-group>
      </el-card>

      <el-card
          shadow="never"
          header="电压标幺值显示设置"
          style="margin-top: 20px;"
      >
        <el-radio-group
            v-model="form.voltageScaleMode"
            class="vertical-radio-group"
        >
          <el-radio
              label="both_100"
              size="large"
              border
          >
            相电压和线电压的标幺值都显示 100%
          </el-radio>
          <el-radio
              label="proportional"
              size="large"
              border
          >
            相电压标幺显示 100%，线电压按比例显示 (100 / √3 ≈ 57.74%)
          </el-radio>
        </el-radio-group>
      </el-card>
    </el-form>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onDefault">
          默认设置
        </el-button>
        <div class="spacer" />
        <el-button @click="onCancel">
          取消
        </el-button>
        <el-button
            type="primary"
            @click="onConfirm"
        >
          确定
        </el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'DimSettingsDialog',
  props: {
    visible: { type: Boolean, default: false },
    /**
     * @vuese
     * 从 App.vue 传入的当前全局标幺基值 (16384 或 8192)。
     */
    currentPuBaseValue: { type: Number, default: 16384 },
    /**
     * @vuese
     * 从 App.vue 传入的当前电压显示模式 (0 或 1)。
     */
    currentPuVoltageMode: { type: Number, default: 0 },
  },
  emits: ['update:visible', 'confirm', 'default'],
  data() {
    return {
      // 本地表单数据，用于绑定 radio group
      form: {
        globalScale: '4000H',      // 对应 puBaseValue
        voltageScaleMode: 'both_100' // 对应 puVoltageMode
      }
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
    }
  },
  methods: {
    /**
     * @vuese
     * 当对话框打开时，根据传入的 props 初始化本地表单状态。
     */
    syncFormWithProps() {
      this.form.globalScale = this.currentPuBaseValue === 16384 ? '4000H' : '2000H';
      this.form.voltageScaleMode = this.currentPuVoltageMode === 0 ? 'both_100' : 'proportional';
    },
    /**
     * @vuese
     * 点击取消按钮，关闭对话框。
     */
    onCancel() {
      this.dialogVisible = false;
    },
    /**
     * @vuese
     * 点击确定按钮，将当前选中的设置 emit 给父组件，并关闭对话框。
     */
    onConfirm() {
      // 发送包含当前表单值的事件给 App.vue
      this.$emit('confirm', { ...this.form });
      this.dialogVisible = false; // 关闭对话框
    },
    /**
     * @vuese
     * 点击默认设置按钮，通知父组件恢复默认设置。
     * App.vue 会处理状态重置和关闭对话框。
     */
    onDefault() {
      // 触发 default 事件，让 App.vue 处理默认值设置
      this.$emit('default');
      // 注意：这里不再直接修改本地 form 或关闭对话框，由 App.vue 响应事件后处理
      // this.form.globalScale = '4000H';
      // this.form.voltageScaleMode = 'both_100';
      // this.$emit('confirm', { ...this.form }); // 可以在 default 事件处理中做
      // this.dialogVisible = false;
    }
  }
};
</script>

<style scoped>
.vertical-radio-group {
  display: flex;
  flex-direction: column;
  gap: 10px; /* 选项之间的间距 */
}

/* 确保带边框的 radio button 宽度一致并撑满容器 */
.vertical-radio-group :deep(.el-radio) {
  width: 100%;
  margin: 0; /* 移除默认的右边距 */
  box-sizing: border-box; /* 边框包含在宽度内 */
}

.dialog-footer {
  display: flex;
  width: 100%;
}

.spacer {
  flex-grow: 1; /* 填充中间空白，将按钮推向两侧 */
}
</style>