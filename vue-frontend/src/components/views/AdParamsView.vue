<template>
  <div class="ad-params-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>AD 参数设置</span>
        </div>
      </template>

      <el-row :gutter="20">
        <!-- Left Column -->
        <el-col :span="14">
          <el-card shadow="never">
            <template #header>AC 比例因子</template>
            <el-form :model="form.acScaling" label-position="top" class="compact-form">
              <el-row :gutter="15">
                <el-col :span="12">
                  <el-row :gutter="15">
                    <el-col :span="12" v-for="key in ['u1a', 'u1b', 'u1c', 'i1a', 'i1b', 'i1c']" :key="key">
                      <el-form-item :label="form.acScaling[key].label">
                        <el-input v-model.number="form.acScaling[key].value" type="number" size="small" />
                      </el-form-item>
                    </el-col>
                  </el-row>
                </el-col>
                <el-col :span="12">
                  <el-row :gutter="15">
                    <el-col :span="12" v-for="key in ['u2a', 'u2b', 'u2c', 'i2a', 'i2b', 'i2c']" :key="key">
                      <el-form-item :label="form.acScaling[key].label">
                        <el-input v-model.number="form.acScaling[key].value" type="number" size="small" />
                      </el-form-item>
                    </el-col>
                  </el-row>
                </el-col>
              </el-row>
            </el-form>
          </el-card>

          <el-card shadow="never" style="margin-top: 20px;">
            <template #header>DC 通道设置</template>
            <el-table :data="form.dcChannels" border size="small" class="dc-table">
              <el-table-column prop="id" label="通道" width="70" />
              <el-table-column label="零漂">
                <template #default="scope">
                  <el-input v-model.number="scope.row.zeroDrift" type="number" size="small" />
                </template>
              </el-table-column>
              <el-table-column label="线性">
                <template #default="scope">
                  <el-input v-model.number="scope.row.linearity" type="number" size="small" />
                </template>
              </el-table-column>
              <el-table-column label="源选择" width="180">
                <template #default="scope">
                  <el-radio-group v-model="scope.row.source" size="small">
                    <el-radio-button label="voltage">Voltage</el-radio-button>
                    <el-radio-button label="current">Current</el-radio-button>
                  </el-radio-group>
                </template>
              </el-table-column>
            </el-table>
          </el-card>
        </el-col>

        <!-- Right Column -->
        <el-col :span="10">
          <el-card shadow="never">
            <template #header>通道与延迟</template>
            <el-row :gutter="20">
              <el-col :span="12">
                <el-form :model="form.channelSelect" label-position="top" class="compact-form">
                  <el-form-item v-for="(item, key) in form.channelSelect" :key="key" :label="item.label">
                    <el-select v-model="item.value" size="small" style="width: 100%;">
                      <el-option v-for="n in 22" :key="n" :label="n" :value="n" />
                    </el-select>
                  </el-form-item>
                </el-form>
              </el-col>
              <el-col :span="12">
                <el-form :model="form.delay" label-position="top" class="compact-form">
                  <el-form-item v-for="(item, key) in form.delay" :key="key" :label="item.label + ' (0.4us/Tick)'">
                    <el-input v-model.number="item.value" type="number" size="small">
                      <template #append>Tick</template>
                    </el-input>
                  </el-form-item>
                </el-form>
              </el-col>
            </el-row>
          </el-card>

          <el-card shadow="never" style="margin-top: 20px;">
            <template #header>额定值</template>
            <el-form label-position="top" class="compact-form">
              <el-row :gutter="20">
                <el-col :span="12">
                  <el-form-item label="额定电压 (KV)">
                    <el-input v-model.number="form.nominalVoltage.line1" type="number" size="small" placeholder="Line 1" disabled />
                    <el-input v-model.number="form.nominalVoltage.line2" type="number" size="small" placeholder="Line 2" disabled style="margin-top: 5px;" />
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="额定电流 (A)">
                    <el-input v-model.number="form.nominalCurrent.line1" type="number" size="small" placeholder="Line 1" disabled />
                    <el-input v-model.number="form.nominalCurrent.line2" type="number" size="small" placeholder="Line 2" disabled style="margin-top: 5px;" />
                  </el-form-item>
                </el-col>
              </el-row>
            </el-form>
          </el-card>

          <el-card shadow="never" style="margin-top: 20px;">
            <template #header>高级设置</template>
            <el-form label-position="top" class="compact-form">
              <el-form-item label="插值模型">
                <el-select v-model="form.interpolation.model" size="small" style="width: 100%;">
                  <el-option label="0 - 线性 (Linear)" :value="0" />
                  <el-option label="1 - 拉格朗日 (Lagrange)" :value="1" />
                  <el-option label="2 - 样条 (Spline)" :value="2" />
                </el-select>
              </el-form-item>
              <el-form-item label="AD 采样校正 (ΔT, 25ns/Tick)">
                <el-input v-model.number="form.adSampleFix.deltaT" type="number" size="small">
                  <template #append>Tick</template>
                </el-input>
              </el-form-item>
              <el-form-item label="一次电流定标 (OCT)">
                <el-input v-model.number="form.adSampleFix.oct" type="number" size="small" />
              </el-form-item>
            </el-form>
          </el-card>
        </el-col>
      </el-row>

      <!-- Footer Actions -->
      <div class="view-footer">
        <el-button @click="onDefault">默认参数</el-button>
        <el-button @click="onCancel">退出</el-button>
        <el-button type="primary" @click="onApply">下载参数</el-button>
        <el-button type="success" @click="onFetch">获取参数</el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
export default {
  name: 'AdParamsView',
  data() {
    const createDcChannels = () => {
      let channels = [];
      for (let i = 1; i <= 8; i++) {
        channels.push({ id: `DC${i}`, zeroDrift: 0, linearity: 0, source: 'current' });
      }
      return channels;
    };

    return {
      form: {
        acScaling: {
          u1a: { label: 'U1a', value: 0 }, u1b: { label: 'U1b', value: 0 }, u1c: { label: 'U1c', value: 0 },
          i1a: { label: 'I1a', value: 0 }, i1b: { label: 'I1b', value: 0 }, i1c: { label: 'I1c', value: 0 },
          u2a: { label: 'U2a', value: 0 }, u2b: { label: 'U2b', value: 0 }, u2c: { label: 'U2c', value: 0 },
          i2a: { label: 'I2a', value: 0 }, i2b: { label: 'I2b', value: 0 }, i2c: { label: 'I2c', value: 0 },
        },
        nominalVoltage: { line1: 0, line2: 0 },
        nominalCurrent: { line1: 0, line2: 0 },
        dcChannels: createDcChannels(),
        channelSelect: {
          ia: { label: 'IA', value: 1 }, ib: { label: 'IB', value: 2 },
          ic: { label: 'IC', value: 3 }, ix: { label: 'IX', value: 4 },
        },
        delay: {
          da: { label: 'DA', value: 0 }, db: { label: 'DB', value: 0 },
          dc: { label: 'DC', value: 0 }, dx: { label: 'DX', value: 0 },
        },
        interpolation: { model: 0 },
        adSampleFix: { deltaT: 0, oct: 0 },
      },
    };
  },
  methods: {
    onApply() { this.$message.success('参数已下载'); },
    onFetch() { this.$message.info('正在获取参数...'); },
    onDefault() { this.$message.warning('参数已恢复为默认值'); },
    onCancel() { this.$message.info('已退出'); },
  },
};
</script>

<style scoped>
.ad-params-view { padding: 20px; background-color: #f0f2f5; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.el-card { border: 1px solid #e4e7ed; }
.el-card ::v-deep(.el-card__header) { background-color: #fafafa; padding: 10px 15px; }
.compact-form .el-form-item { margin-bottom: 8px; }
.compact-form ::v-deep(.el-form-item__label) { line-height: 1.5; font-size: 13px; }
.dc-table .el-input__inner { padding: 0 8px; }
.view-footer { display: flex; justify-content: flex-end; gap: 10px; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #e4e7ed; }
</style>
