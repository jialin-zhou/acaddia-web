<template>
  <div class="ad-adjust-view">
    <!-- Line 1 Card -->
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>Line 1 AC Channels</span>
          <el-button class="button" text @click="onCalibrate('line1')">执行校准</el-button>
        </div>
      </template>
      <el-table :data="acChannelsLine1" border size="small">
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

    <!-- Line 2 Card -->
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>Line 2 AC Channels</span>
          <el-button class="button" text @click="onCalibrate('line2')">执行校准</el-button>
        </div>
      </template>
      <el-table :data="acChannelsLine2" border size="small">
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

    <!-- DC Card -->
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>DC Channels</span>
          <el-button class="button" text @click="onCalibrate('dc')">执行校准</el-button>
        </div>
      </template>
      <el-form label-width="120px">
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
      </el-form>
    </el-card>
  </div>
</template>

<script>
export default {
  name: 'AdAdjustView',
  props: {
    stompClient: { type: Object, default: null },
  },
  data() {
    return {
      acChannelsLine1: [],
      acChannelsLine2: [],
      dcZeroDriftSelection: 1,
      dcFactorSelection: 1,
    };
  },
  created() {
    this.initializeState();
  },
  methods: {
    initializeState() {
      const createAcChannel = (name, sourceValue) => ({ name, sourceValue, correctionFactor: '0H', originalFactor: '0H', calculatedValue: '0H', idealValue: '4000H', calibrated: false });
      this.acChannelsLine1 = [ createAcChannel('Ua(V)', '57.74'), createAcChannel('Ub(V)', '57.74'), createAcChannel('Uc(V)', '57.74'), createAcChannel('Ia(A)', '1'), createAcChannel('Ib(A)', '1'), createAcChannel('Ic(A)', '1') ];
      this.acChannelsLine2 = [ createAcChannel('Ua(V)', '57.74'), createAcChannel('Ub(V)', '57.74'), createAcChannel('Uc(V)', '57.74'), createAcChannel('Ia(A)', '1'), createAcChannel('Ib(A)', '1'), createAcChannel('Ic(A)', '1') ];
    },
    onCalibrate(mode) {
      let payload;
      if (mode === 'line1') {
        payload = { mode, acChannels: this.acChannelsLine1 };
      } else if (mode === 'line2') {
        payload = { mode, acChannels: this.acChannelsLine2 };
      } else if (mode === 'dc') {
        payload = { mode, dcZeroDriftSelection: this.dcZeroDriftSelection, dcFactorSelection: this.dcFactorSelection };
      }

      if (this.stompClient && this.stompClient.connected) {
        this.stompClient.send('/app/send-command', JSON.stringify({ type: 'ad-adjust-calibrate', payload }), {});
        this.$message.info(`校准命令 (${mode}) 已发送`);
      } else {
        this.$message.error('发送失败：未连接到服务器');
      }
    }
  }
};
</script>

<style scoped>
.ad-adjust-view { padding: 20px; background: #fff; border-radius: 4px; }
.box-card { margin-bottom: 20px; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.el-select { width: 100%; }
</style>
