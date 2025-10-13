<template>
  <div class="tqcs-view">
    <el-form :model="form" label-width="180px" label-position="right">
      <el-checkbox v-model="form.synFunctionEnable" label="Syn_Function_Enable" size="large" border class="full-width-checkbox"/>

      <el-row :gutter="20" class="settings-row">
        <!-- ... (rest of the form content is the same) ... -->
      </el-row>
    </el-form>

    <div class="view-footer">
      <el-button @click="onFetch">获取</el-button>
      <el-button @click="onDefault">默认</el-button>
      <div class="spacer"></div>
      <el-button @click="onCancel">取消</el-button>
      <el-button type="primary" @click="onApply">应用</el-button>
    </div>
  </div>
</template>

<script>
// This component's script is simplified as it's no longer a dialog
export default {
  name: 'TqcsView',
  // props: { stompClient: { type: Object, default: null } }, // Example of how to receive stomp client if needed
  data() {
    return {
      form: {
        synFunctionEnable: true,
        selectionMode: 'auto', 
        manualStyle: 'sync', 
        deadVoltSelect: ['l1'],
        phaseSelect: 'A',
        params: {
          tcb: '100', daMax: '10', duSync: '5', duAsync: '10',
          dfSync: '30', dfAsync: '0.2', uMin: '80', uMax: '110',
          uDead: '40', trU1U2: '0', dfdtMax: '0.5', fMin: '49.5',
          fMax: '50.5', tSynDuration: '10', tSynchron: '5', df1f2dt: '0.5'
        }
      }
    };
  },
  methods: {
    onCancel() { this.$message.info('取消操作'); },
    onApply() { this.$message.success('应用命令已发送'); },
    onFetch() { this.$message.info('获取命令已发送'); },
    onDefault() { this.$message.info('默认命令已发送'); }
  }
};
</script>

<style scoped>
.tqcs-view { padding: 20px; background: #fff; border-radius: 4px; }
.full-width-checkbox { width: 100%; margin-bottom: 15px; }
.settings-row { margin-bottom: 15px; }
.inner-card { margin-top: 10px; }
.el-checkbox-group, .el-radio-group { display: flex; flex-direction: column; gap: 10px; }
.view-footer { display: flex; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #f0f2f5; }
.spacer { flex-grow: 1; }
.el-card { height: 100%; }
</style>
