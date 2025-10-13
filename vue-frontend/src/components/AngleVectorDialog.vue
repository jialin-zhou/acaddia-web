<template>
  <el-dialog
    v-model="dialogVisible"
    title="角度矢量设置"
    width="550px"
    @close="onCancel"
  >
    <el-form
      :model="form"
      label-width="80px"
      label-position="left"
    >
      <el-row :gutter="20">
        <!-- Line 1 -->
        <el-col :span="12">
          <el-card
            shadow="never"
            header="Line 1"
          >
            <el-form-item
              v-for="(_, key) in form.line1"
              :key="key"
              :label="key.toUpperCase()"
            >
              <el-input v-model="form.line1[key]">
                <template #append>
                  °
                </template>
              </el-input>
            </el-form-item>
          </el-card>
        </el-col>

        <!-- Line 2 -->
        <el-col :span="12">
          <el-card
            shadow="never"
            header="Line 2"
          >
            <el-form-item
              v-for="(_, key) in form.line2"
              :key="key"
              :label="key.toUpperCase()"
            >
              <el-input v-model="form.line2[key]">
                <template #append>
                  °
                </template>
              </el-input>
            </el-form-item>
          </el-card>
        </el-col>
      </el-row>

      <!-- Delta Angle -->
      <el-row
        justify="center"
        style="margin-top: 20px;"
      >
        <el-col :span="12">
          <el-form-item label="▲α">
            <el-input v-model="form.deltaAlpha">
              <template #append>
                °
              </template>
            </el-input>
          </el-form-item>
        </el-col>
      </el-row>
    </el-form>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onFetch">
          获取角度
        </el-button>
        <div class="spacer" />
        <el-button @click="onCancel">
          退出
        </el-button>
        <el-button
          type="primary"
          @click="onApply"
        >
          应用
        </el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'AngleVectorDialog',
  props: { visible: { type: Boolean, default: false } },
  emits: ['update:visible', 'fetch', 'apply'],
  data() {
    return {
      form: {
        line1: { ua: '0', ub: '0', uc: '0', ia: '0', ib: '0', ic: '0' },
        line2: { ua: '0', ub: '0', uc: '0', ia: '0', ib: '0', ic: '0' },
        deltaAlpha: '0'
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
    onFetch() {
      this.$emit('fetch');
      this.$message.info('已发送获取角度命令');
    },
    onApply() {
      this.$emit('apply', this.form);
      this.$message.success('应用角度设置命令已发送');
      this.dialogVisible = false;
    }
  }
};
</script>

<style scoped>
.dialog-footer {
  display: flex;
  width: 100%;
}
.spacer {
  flex-grow: 1;
}
.el-card {
  height: 100%;
}
</style>
