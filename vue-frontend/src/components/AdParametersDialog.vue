<template>
  <el-dialog v-model="dialogVisible" title="AD 参数设置" width="1050px" @close="onCancel">
    <el-form :model="form" label-position="top">
      <el-tabs v-model="activeTab">
        <!-- AC Scaling Factors Tab -->
        <el-tab-pane label="AC 比例系数" name="acScaling">
          <el-row :gutter="20">
            <el-col :span="12">
              <el-card shadow="never" header="Line 1 Channels">
                <el-form-item v-for="chan in ['U1a', 'U1b', 'U1c', 'I1a', 'I1b', 'I1c']" :label="chan" :key="chan">
                  <el-input v-model="form.acScaling[chan]"></el-input>
                </el-form-item>
              </el-card>
            </el-col>
            <el-col :span="12">
              <el-card shadow="never" header="Line 2 Channels">
                <el-form-item v-for="chan in ['U2a', 'U2b', 'U2c', 'I2a', 'I2b', 'I2c']" :label="chan" :key="chan">
                  <el-input v-model="form.acScaling[chan]"></el-input>
                </el-form-item>
              </el-card>
            </el-col>
          </el-row>
        </el-tab-pane>

        <!-- DC Channels Tab -->
        <el-tab-pane label="DC 通道设置" name="dcChannels">
          <el-card shadow="never" v-for="(dc, index) in form.dcChannels" :key="index" class="dc-card">
            <template #header>DC{{ index + 1 }}</template>
            <el-row :gutter="20">
              <el-col :span="6"><el-input v-model="dc.zeroDrift" placeholder="ZeroDrift"></el-input></el-col>
              <el-col :span="6"><el-input v-model="dc.linearity" placeholder="Linearity"></el-input></el-col>
              <el-col :span="12">
                <el-radio-group v-model="dc.sourceType">
                  <el-radio-button label="Voltage">Voltage</el-radio-button>
                  <el-radio-button label="Current">Current</el-radio-button>
                </el-radio-group>
              </el-col>
            </el-row>
          </el-card>
        </el-tab-pane>

        <!-- Channel & Model Config Tab -->
        <el-tab-pane label="通道与模型配置" name="channelConfig">
          <el-row :gutter="20">
            <el-col :span="8">
              <el-card shadow="never" header="Channel Select">
                <el-form-item v-for="ch in ['IA', 'IB', 'IC', 'IX']" :label="ch" :key="ch">
                  <el-select v-model="form.channelSelect[ch]">
                    <el-option v-for="i in 22" :key="i" :label="i" :value="i"></el-option>
                  </el-select>
                </el-form-item>
              </el-card>
            </el-col>
            <el-col :span="8">
              <el-card shadow="never" header="Delay Tick (0.4us/Tick)">
                 <el-form-item v-for="ch in ['DA', 'DB', 'DC', 'DX']" :label="ch" :key="ch">
                  <el-input v-model="form.delayTick[ch]"><template #append>Tick</template></el-input>
                </el-form-item>
              </el-card>
            </el-col>
            <el-col :span="8">
              <el-card shadow="never" header="Interpolation Model">
                <el-select v-model="form.interpolationModel">
                  <el-option label="0 - Linear" :value="0"></el-option>
                  <el-option label="1 - Lagrange" :value="1"></el-option>
                  <el-option label="2 - Spline" :value="2"></el-option>
                </el-select>
              </el-card>
              <el-card shadow="never" header="AD Sample Fix (25ns/Tick)" class="top-margin-card">
                <el-form-item label="▲T">
                  <el-input v-model="form.adSampleFix"><template #append>Tick</template></el-input>
                </el-form-item>
              </el-card>
            </el-col>
          </el-row>
        </el-tab-pane>

      </el-tabs>
    </el-form>

    <template #footer>
      <div class="dialog-footer">
        <el-button @click="onFetch">获取参数</el-button>
        <el-button @click="onDefault">默认参数</el-button>
        <div class="spacer"></div>
        <el-button @click="onCancel">取消</el-button>
        <el-button type="primary" @click="onApply">下载参数</el-button>
      </div>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'AdParametersDialog',
  props: { visible: { type: Boolean, default: false } },
  emits: ['update:visible', 'apply', 'fetch', 'default'],
  data() {
    return {
      activeTab: 'acScaling',
      form: {
        acScaling: {
          U1a: '0', U1b: '0', U1c: '0', I1a: '0', I1b: '0', I1c: '0',
          U2a: '0', U2b: '0', U2c: '0', I2a: '0', I2b: '0', I2c: '0',
        },
        dcChannels: Array(8).fill(null).map(() => ({
          zeroDrift: '0',
          linearity: '0',
          sourceType: 'Current'
        })),
        channelSelect: { IA: 1, IB: 2, IC: 3, IX: 4 },
        delayTick: { DA: '0', DB: '0', DC: '0', DX: '0' },
        interpolationModel: 0,
        adSampleFix: '0',
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
.dialog-footer {
  display: flex;
  width: 100%;
}
.spacer {
  flex-grow: 1;
}
.dc-card {
  margin-bottom: 15px;
}
.top-margin-card {
  margin-top: 20px;
}
.el-select {
  width: 100%;
}
</style>
