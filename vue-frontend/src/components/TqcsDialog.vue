<template>
  <el-dialog v-model="dialogVisible" title="同期参数设置" width="950px" @close="onCancel">
    <el-form :model="form" label-width="180px" label-position="right">
      <el-checkbox v-model="form.synFunctionEnable" label="Syn_Function_Enable" size="large" border class="full-width-checkbox"/>

      <el-row :gutter="20" class="settings-row">
        <!-- Synchronization Style -->
        <el-col :span="12">
          <el-card shadow="never">
            <template #header>Synchronization Subnetworks Style</template>
            <el-radio-group v-model="form.selectionMode">
              <el-radio label="auto">Routine Auto Select</el-radio>
              <el-radio label="manual">Manual Select</el-radio>
            </el-radio-group>
            <el-card shadow="inner" v-if="form.selectionMode === 'manual'" class="inner-card">
              <el-radio-group v-model="form.manualStyle">
                <el-radio label="sync">Synchronous Style</el-radio>
                <el-radio label="async">Asynchronous Networks</el-radio>
              </el-radio-group>
            </el-card>
          </el-card>
        </el-col>

        <!-- Dead Volt & U Phase Select -->
        <el-col :span="12">
          <el-row :gutter="20">
            <el-col :span="12">
              <el-card shadow="never">
                <template #header>Dead Volt Select</template>
                <el-checkbox-group v-model="form.deadVoltSelect">
                  <el-checkbox label="l1">L1 Dead Volt</el-checkbox>
                  <el-checkbox label="l2">L2 Dead Volt</el-checkbox>
                  <el-checkbox label="all">All Dead Volt</el-checkbox>
                </el-checkbox-group>
              </el-card>
            </el-col>
            <el-col :span="12">
              <el-card shadow="never">
                <template #header>U Phase Select</template>
                <el-radio-group v-model="form.phaseSelect">
                  <el-radio label="A">Phase A</el-radio>
                  <el-radio label="B">Phase B</el-radio>
                  <el-radio label="C">Phase C</el-radio>
                </el-radio-group>
              </el-card>
            </el-col>
          </el-row>
        </el-col>
      </el-row>

      <!-- Parameters Input -->
      <el-row :gutter="20">
        <el-col :span="12">
          <el-card shadow="never" header="同步条件参数">
            <el-form-item label="T_CB (30-2000 ms)">
              <el-input v-model="form.params.tcb"><template #append>ms</template></el-input>
            </el-form-item>
            <el-form-item label="Δαmax (0-50 °)">
              <el-input v-model="form.params.daMax"><template #append>°</template></el-input>
            </el-form-item>
            <el-form-item label="ΔUsync (2-50 V)">
              <el-input v-model="form.params.duSync"><template #append>V</template></el-input>
            </el-form-item>
            <el-form-item label="ΔUasync (2-50 V)">
              <el-input v-model="form.params.duAsync"><template #append>V</template></el-input>
            </el-form-item>
            <el-form-item label="Δfsync (10-60 mHz)">
              <el-input v-model="form.params.dfSync"><template #append>mHz</template></el-input>
            </el-form-item>
            <el-form-item label="Δfasync (0.1-1 Hz)">
              <el-input v-model="form.params.dfAsync"><template #append>Hz</template></el-input>
            </el-form-item>
            <el-form-item label="Umin (20-120 V)">
              <el-input v-model="form.params.uMin"><template #append>V</template></el-input>
            </el-form-item>
            <el-form-item label="Umax (20-120 V)">
              <el-input v-model="form.params.uMax"><template #append>V</template></el-input>
            </el-form-item>
          </el-card>
        </el-col>
        <el-col :span="12">
          <el-card shadow="never" header="同期过程参数">
            <el-form-item label="Udead (2-50 V)">
              <el-input v-model="form.params.uDead"><template #append>V</template></el-input>
            </el-form-item>
            <el-form-item label="Tr.U1-U2 (0-360 °)">
              <el-input v-model="form.params.trU1U2"><template #append>°</template></el-input>
            </el-form-item>
            <el-form-item label="dΔf/dtmax (0.1-2 Hz/s)">
              <el-input v-model="form.params.dfdtMax"><template #append>Hz/s</template></el-input>
            </el-form-item>
            <el-form-item label="fmin (45-55 Hz)">
              <el-input v-model="form.params.fMin"><template #append>Hz</template></el-input>
            </el-form-item>
            <el-form-item label="fmax (45-55 Hz)">
              <el-input v-model="form.params.fMax"><template #append>Hz</template></el-input>
            </el-form-item>
            <el-form-item label="T-syn.Duration (2-30 s)">
              <el-input v-model="form.params.tSynDuration"><template #append>s</template></el-input>
            </el-form-item>
            <el-form-item label="T Synchron (0-60 s)">
              <el-input v-model="form.params.tSynchron"><template #append>s</template></el-input>
            </el-form-item>
            <el-form-item label="d(f1-f2)/dt (0.1-2 Hz/s)">
              <el-input v-model="form.params.df1f2dt"><template #append>Hz/s</template></el-input>
            </el-form-item>
          </el-card>
        </el-col>
      </el-row>
    </el-form>

    <template #footer>
      <div class="dialog-footer">
        <el-button @click="onFetch">获取</el-button>
        <el-button @click="onDefault">默认</el-button>
        <div class="spacer"></div>
        <el-button @click="onCancel">取消</el-button>
        <el-button type="primary" @click="onApply">应用</el-button>
      </div>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'TqcsDialog',
  props: { visible: { type: Boolean, default: false } },
  emits: ['update:visible', 'apply', 'fetch', 'default'],
  data() {
    return {
      form: {
        synFunctionEnable: true,
        selectionMode: 'auto', // auto | manual
        manualStyle: 'sync', // sync | async
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
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    }
  },
  methods: {
    onCancel() { this.dialogVisible = false; },
    onApply() {
      this.$emit('apply', this.form);
      this.dialogVisible = false;
    },
    onFetch() { this.$emit('fetch'); },
    onDefault() { this.$emit('default'); }
  }
};
</script>

<style scoped>
.full-width-checkbox {
  width: 100%;
  margin-bottom: 15px;
}
.settings-row {
  margin-bottom: 15px;
}
.inner-card {
  margin-top: 10px;
}
.el-checkbox-group, .el-radio-group {
  display: flex;
  flex-direction: column;
  gap: 10px;
}
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
