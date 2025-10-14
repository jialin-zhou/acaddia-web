<template>
  <div class="ad-params-view">
    <el-form :model="form" label-width="80px">
      <el-tabs v-model="activeTab">
        <!-- AC Scaling Factors Tab -->
        <el-tab-pane label="AC 比例系数" name="acScaling">
          <el-row :gutter="20">
            <!-- Line 1 Card -->
            <el-col :span="12">
              <el-card shadow="never">
                <template #header>Line 1 Channels</template>
                <el-row :gutter="20">
                  <el-col :span="12">
                    <el-form-item v-for="chan in ['U1a', 'U1b', 'U1c']" :label="chan" :key="chan">
                      <el-input v-model="form.acScaling[chan]"></el-input>
                    </el-form-item>
                  </el-col>
                  <el-col :span="12">
                    <el-form-item v-for="chan in ['I1a', 'I1b', 'I1c']" :label="chan" :key="chan">
                      <el-input v-model="form.acScaling[chan]"></el-input>
                    </el-form-item>
                  </el-col>
                </el-row>
              </el-card>
            </el-col>
            <!-- Line 2 Card -->
            <el-col :span="12">
              <el-card shadow="never">
                <template #header>Line 2 Channels</template>
                <el-row :gutter="20">
                  <el-col :span="12">
                    <el-form-item v-for="chan in ['U2a', 'U2b', 'U2c']" :label="chan" :key="chan">
                      <el-input v-model="form.acScaling[chan]"></el-input>
                    </el-form-item>
                  </el-col>
                  <el-col :span="12">
                    <el-form-item v-for="chan in ['I2a', 'I2b', 'I2c']" :label="chan" :key="chan">
                      <el-input v-model="form.acScaling[chan]"></el-input>
                    </el-form-item>
                  </el-col>
                </el-row>
              </el-card>
            </el-col>
          </el-row>
        </el-tab-pane>

        <!-- ... (rest of the tabs) ... -->

      </el-tabs>
    </el-form>

    <div class="view-footer">
        <el-button @click="onFetch">获取参数</el-button>
        <el-button @click="onDefault">默认参数</el-button>
        <div class="spacer"></div>
        <el-button @click="onCancel">取消</el-button>
        <el-button type="primary" @click="onApply">下载参数</el-button>
    </div>
  </div>
</template>

<script>
export default {
  name: 'AdParamsView',
  data() {
    return {
      activeTab: 'acScaling',
      form: {
        acScaling: {
          U1a: '0', U1b: '0', U1c: '0', I1a: '0', I1b: '0', I1c: '0',
          U2a: '0', U2b: '0', U2c: '0', I2a: '0', I2b: '0', I2c: '0',
        },
        dcChannels: Array(8).fill(null).map(() => ({ zeroDrift: '0', linearity: '0', sourceType: 'Current' })),
        channelSelect: { IA: 1, IB: 2, IC: 3, IX: 4 },
        delayTick: { DA: '0', DB: '0', DC: '0', DX: '0' },
        interpolationModel: 0,
        adSampleFix: '0',
      }
    };
  },
  methods: {
    onCancel() { this.$message.info('取消操作'); },
    onApply() { this.$message.success('下载参数命令已发送'); },
    onFetch() { this.$message.info('获取参数命令已发送'); },
    onDefault() { this.$message.info('默认参数命令已发送'); }
  }
};
</script>

<style scoped>
.ad-params-view { padding: 20px; background: #fff; border-radius: 4px; }
.view-footer { display: flex; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #f0f2f5; }
.spacer { flex-grow: 1; }
.el-card { height: 100%; }
</style>
