<template>
  <div class="tqcs-view">
    <el-card class="box-card">
      <!-- Header -->
      <template #header>
        <div class="card-header">
          <span>同期参数设置</span>
          <el-switch v-model="form.functionEnabled" active-text="功能已启用" inactive-text="功能已禁用" />
        </div>
      </template>

      <!-- Top Settings -->
      <el-form class="top-settings-form">
        <el-row :gutter="20" align="middle">
          <el-col :span="11">
            <el-form-item label="并网方式" label-width="80px">
              <el-radio-group v-model="form.networkStyle.mode" size="small">
                <el-radio-button label="auto">自动</el-radio-button>
                <el-radio-button label="manual">手动</el-radio-button>
              </el-radio-group>
              <el-radio-group v-model="form.networkStyle.manualType" :disabled="form.networkStyle.mode !== 'manual'" size="small" style="margin-left: 10px;">
                <el-radio-button label="sync">同期</el-radio-button>
                <el-radio-button label="async">异步</el-radio-button>
              </el-radio-group>
            </el-form-item>
          </el-col>
          <el-col :span="7">
            <el-form-item label="无压选择" label-width="80px">
              <el-checkbox-group v-model="form.deadVoltSelect" size="small">
                <el-checkbox-button label="L1">L1</el-checkbox-button>
                <el-checkbox-button label="L2">L2</el-checkbox-button>
                <el-checkbox-button label="All">全部</el-checkbox-button>
              </el-checkbox-group>
            </el-form-item>
          </el-col>
          <el-col :span="6">
            <el-form-item label="U相位" label-width="60px">
              <el-radio-group v-model="form.phaseSelect" size="small">
                <el-radio-button label="A">A相</el-radio-button>
                <el-radio-button label="B">B相</el-radio-button>
                <el-radio-button label="C">C相</el-radio-button>
              </el-radio-group>
            </el-form-item>
          </el-col>
        </el-row>
      </el-form>

      <!-- Parameters -->
      <el-divider>详细参数</el-divider>
      <el-row :gutter="40">
        <!-- Left Column -->
        <el-col :span="12">
          <el-form :model="form.paramsLeft" label-width="220px" label-position="left" class="params-form">
            <el-form-item v-for="(param, key) in form.paramsLeft" :key="key" :label="param.label">
              <el-input v-model.number="param.value" type="number">
                <template #append>{{ param.unit }}</template>
              </el-input>
            </el-form-item>
          </el-form>
        </el-col>

        <!-- Right Column -->
        <el-col :span="12">
          <el-form :model="form.paramsRight" label-width="220px" label-position="left" class="params-form">
            <el-form-item v-for="(param, key) in form.paramsRight" :key="key" :label="param.label">
              <el-input v-model.number="param.value" type="number">
                <template #append>{{ param.unit }}</template>
              </el-input>
            </el-form-item>
          </el-form>
        </el-col>
      </el-row>

      <!-- Footer Actions -->
      <div class="view-footer">
        <el-button @click="onDefault">恢复默认</el-button>
        <el-button @click="onCancel">取消</el-button>
        <el-button type="primary" @click="onApply">应用</el-button>
        <el-button type="success" @click="onFetch">读取</el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
export default {
  name: 'TqcsView',
  data() {
    return {
      form: {
        functionEnabled: true,
        networkStyle: { mode: 'auto', manualType: 'sync' },
        deadVoltSelect: ['L1'],
        phaseSelect: 'A',
        paramsLeft: {
          t_cb: { label: 'T_CB (30-2000 ms)', value: 100, unit: 'ms' },
          d_amax: { label: 'Δαmax (0-50 °)', value: 10, unit: '°' },
          d_usync: { label: 'ΔUsync (2-50 V)', value: 5, unit: 'V' },
          d_uasync: { label: 'ΔUasync (2-50 V)', value: 10, unit: 'V' },
          d_fsync: { label: 'Δfsync (10-60 mHz)', value: 30, unit: 'mHz' },
          d_fasync: { label: 'Δfasync (0.1-1 Hz)', value: 0.5, unit: 'Hz' },
          umin: { label: 'Umin (20-120 V)', value: 80, unit: 'V' },
          umax: { label: 'Umax (20-120 V)', value: 110, unit: 'V' },
        },
        paramsRight: {
          udead: { label: 'Udead (2-50 V)', value: 10, unit: 'V' },
          tr_u1_u2: { label: 'Tr.U1-U2 (0-360 °)', value: 0, unit: '°' },
          df_dt_max: { label: 'dΔf/dtmax (0.1-2 Hz/s)', value: 0.5, unit: 'Hz/s' },
          fmin: { label: 'fmin (45-55 Hz)', value: 49.5, unit: 'Hz' },
          fmax: { label: 'fmax (45-55 Hz)', value: 50.5, unit: 'Hz' },
          t_syn_duration: { label: 'T-syn.Duration (2-30 s)', value: 10, unit: 's' },
          t_synchron: { label: 'T Synchron (0-60 s)', value: 20, unit: 's' },
          df1_f2_dt: { label: 'd(f1-f2)/dt (0.1-2 Hz/s)', value: 0.5, unit: 'Hz/s' },
        },
      },
    };
  },
  methods: {
    onApply() { this.$message.success('参数已应用'); },
    onFetch() { this.$message.info('正在读取参数...'); },
    onDefault() { this.$message.warning('参数已恢复为默认值'); },
    onCancel() { this.$message.error('操作已取消'); },
  },
};
</script>

<style scoped>
.tqcs-view { padding: 20px; background-color: #f0f2f5; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.top-settings-form { background-color: #fafafa; padding: 15px 20px 5px; border-radius: 4px; margin-bottom: 20px; }
.params-form ::v-deep(.el-input-group__append) {
  width: 70px;
  text-align: center;
}
.view-footer { display: flex; justify-content: flex-end; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #e4e7ed; }
</style>
