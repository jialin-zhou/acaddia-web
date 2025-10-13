<template>
  <el-dialog v-model="dialogVisible" title="通道校准" width="800px" @close="onCancel">
    <el-row :gutter="20">
      <!-- Left Navigation -->
      <el-col :span="4">
        <el-radio-group v-model="mode" direction="vertical">
          <el-radio-button label="line1">Line 1</el-radio-button>
          <el-radio-button label="line2">Line 2</el-radio-button>
          <el-radio-button label="dc">DC</el-radio-button>
        </el-radio-group>
      </el-col>

      <!-- Right Content -->
      <el-col :span="20">
        <!-- AC Calibration -->
        <div v-if="mode === 'line1' || mode === 'line2'">
          <el-card :header="`AC Channels - ${mode}`">
            <el-table :data="acChannels" border size="small">
              <el-table-column label="通道号" prop="name" width="80"></el-table-column>
              <el-table-column label="校准源">
                <template #default="scope">
                  <el-input v-model="scope.row.sourceValue" size="small"></el-input>
                </template>
              </el-table-column>
              <el-table-column label="修正系数" prop="correctionFactor" width="100"></el-table-column>
              <el-table-column label="原系数" prop="originalFactor" width="100"></el-table-column>
              <el-table-column label="计算值" prop="calculatedValue" width="100"></el-table-column>
              <el-table-column label="理想值" prop="idealValue" width="100"></el-table-column>
              <el-table-column label="状态" width="80">
                <template #default="scope">
                  <el-tag :type="scope.row.calibrated ? 'success' : 'warning'" size="small">
                    {{ scope.row.calibrated ? '已校准' : '未校准' }}
                  </el-tag>
                </template>
              </el-table-column>
            </el-table>
          </el-card>
        </div>

        <!-- DC Calibration -->
        <div v-if="mode === 'dc'">
          <el-card header="DC Channels">
            <el-row :gutter="20">
              <el-col :span="12">
                <el-form-item label="零漂校准选择">
                  <el-select v-model="dcZeroDriftSelection" placeholder="选择DC通道">
                    <el-option v-for="i in 8" :key="i" :label="`DC${i}`" :value="i"></el-option>
                  </el-select>
                </el-form-item>
              </el-col>
              <el-col :span="12">
                <el-form-item label="系数校准选择">
                  <el-select v-model="dcFactorSelection" placeholder="选择DC通道">
                    <el-option v-for="i in 8" :key="i" :label="`DC${i}`" :value="i"></el-option>
                  </el-select>
                </el-form-item>
              </el-col>
            </el-row>
            <!-- Additional DC calibration inputs can be added here -->
          </el-card>
        </div>
      </el-col>
    </el-row>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onCancel">取消</el-button>
        <el-button type="primary" @click="onCalibrate">执行校准</el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'AdAdjustDialog',
  props: { visible: { type: Boolean, default: false } },
  emits: ['update:visible', 'calibrate'],
  data() {
    return {
      mode: 'line1', // line1, line2, dc
      acChannels: [],
      dcZeroDriftSelection: 1,
      dcFactorSelection: 1,
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    }
  },
  methods: {
    initializeState() {
      const createAcChannel = (name, sourceValue) => ({
        name,
        sourceValue,
        correctionFactor: '0H',
        originalFactor: '0H',
        calculatedValue: '0H',
        idealValue: '4000H',
        calibrated: false,
      });
      this.acChannels = [
        createAcChannel('Ua(V)', '57.74'),
        createAcChannel('Ub(V)', '57.74'),
        createAcChannel('Uc(V)', '57.74'),
        createAcChannel('Ia(A)', '1'),
        createAcChannel('Ib(A)', '1'),
        createAcChannel('Ic(A)', '1'),
      ];
    },
    onCancel() {
      this.dialogVisible = false;
    },
    onCalibrate() {
      const payload = {
        mode: this.mode,
        acChannels: this.mode !== 'dc' ? this.acChannels : undefined,
        dcZeroDriftSelection: this.mode === 'dc' ? this.dcZeroDriftSelection : undefined,
        dcFactorSelection: this.mode === 'dc' ? this.dcFactorSelection : undefined,
      };
      this.$emit('calibrate', payload);
      this.$message.info('校准命令已发送');
    }
  },
  watch: {
    visible(newValue) {
      if (newValue) {
        this.initializeState();
      }
    }
  },
  created() {
    this.initializeState();
  }
};
</script>

<style scoped>
.el-radio-group {
  display: flex;
  flex-direction: column;
  align-items: stretch;
}
.el-radio-button {
  margin-bottom: 10px;
}
.el-radio-button:deep(.el-radio-button__inner) {
  width: 100%;
  border-radius: 4px !important;
  border: 1px solid #dcdfe6;
}
.el-select {
    width: 100%;
}
</style>
