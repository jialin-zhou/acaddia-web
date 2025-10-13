<template>
  <el-dialog
    v-model="dialogVisible"
    title="标幺设置"
    width="500px"
    @close="onCancel"
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
            100% --> 4000H
          </el-radio>
          <el-radio
            label="2000H"
            size="large"
            border
          >
            100% --> 2000H
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
            相电压标幺显示 100%，线电压按比例显示
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
  props: { visible: { type: Boolean, default: false } },
  emits: ['update:visible', 'confirm', 'default'],
  data() {
    return {
      form: {
        globalScale: '4000H',
        voltageScaleMode: 'both_100'
      }
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    }
  },
  methods: {
    onCancel() {
      this.dialogVisible = false;
    },
    onConfirm() {
      this.$emit('confirm', this.form);
      this.dialogVisible = false;
    },
    onDefault() {
      this.$emit('default');
      this.$message.info('已发送恢复默认标幺设置命令');
    }
  }
};
</script>

<style scoped>
.vertical-radio-group {
  display: flex;
  flex-direction: column;
  align-items: stretch; /* Make radios take full width */
  gap: 10px;
}

.dialog-footer {
  display: flex;
  width: 100%;
}

.spacer {
  flex-grow: 1;
}
</style>
