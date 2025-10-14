<template>
  <div class="message-view">
    <el-row :gutter="20">
      <!-- Column 1: Rated Parameters & Control Word -->
      <el-col :span="8">
        <el-card class="box-card" header="额定参数 & 控制字">
          <el-form :model="message.rated" label-position="left" label-width="100px" disabled>
            <el-form-item v-for="(val, key) in message.rated" :label="key" :key="key">
              <el-input :model-value="val" />
            </el-form-item>
          </el-form>
          <el-divider />
          <el-form :model="message.control" label-position="left" label-width="100px" disabled>
            <el-form-item v-for="(val, key) in message.control" :label="key" :key="key">
              <el-input :model-value="val" />
            </el-form-item>
          </el-form>
        </el-card>
      </el-col>

      <!-- Column 2: Status Word -->
      <el-col :span="8">
        <el-card class="box-card" header="状态字">
          <el-form :model="message.status" label-position="left" label-width="100px" disabled>
            <el-form-item label="Status Word 1">
              <el-input v-model="message.status.word1" />
            </el-form-item>
            <el-form-item label="Status Word 2">
              <el-input v-model="message.status.word2" />
            </el-form-item>
          </el-form>
          <div class="status-flags">
            <el-checkbox v-for="(val, key) in message.status.flags" :model-value="val" :label="key" :key="key" disabled />
          </div>
        </el-card>
      </el-col>

      <!-- Column 3: Channel Data -->
      <el-col :span="8">
        <el-card class="box-card" header="通道数据">
          <div class="display-mode-toggle">
             <el-radio-group v-model="displayMode">
                <el-radio-button label="HEX">HEX</el-radio-button>
                <el-radio-button label="DEC">DEC</el-radio-button>
              </el-radio-group>
          </div>
          <el-table :data="message.channelData" border size="small" height="290">
            <el-table-column type="index" label="Ch" width="50" />
            <el-table-column label="Value 1">
                <template #default="scope">{{ formatValue(scope.row.val1) }}</template>
            </el-table-column>
            <el-table-column label="Value 2">
                <template #default="scope">{{ formatValue(scope.row.val2) }}</template>
            </el-table-column>
          </el-table>
          <div class="card-footer">
            <el-button type="primary" @click="onFetch">获取</el-button>
          </div>
        </el-card>
      </el-col>
    </el-row>
  </div>
</template>

<script>
export default {
  name: 'MessageView',
  data() {
    return {
      displayMode: 'DEC',
      message: {
        control: { Lenth: 'cccc', LNName: 'cc', DataSetName: 'cc', LDName: 'cccc', SmpCtr: 'cccc' },
        rated: { 'PhsA.Artg': 'cccc', 'PhsA.Vrtg': 'cccc', 'Neut.Artg': 'cccc', tdr: 'cccc' },
        status: {
          word1: 'cccc', word2: 'cccc',
          flags: { '要求检修': false, '试验状态': false, '唤醒时间数据无效': true, '适用于插值法': true, '时间同步无效': false, '电流互感器输出类型': false, '比例因子': false }
        },
        channelData: Array(22).fill(null).map(() => ({ val1: Math.floor(Math.random() * 65535), val2: Math.floor(Math.random() * 65535) }))
      }
    };
  },
  methods: {
    formatValue(val) {
        if (this.displayMode === 'HEX') {
            return '0x' + val.toString(16).toUpperCase().padStart(4, '0');
        }
        return val;
    },
    onFetch() { this.$message.info('已发送报文获取命令'); }
  }
};
</script>

<style scoped>
.message-view { padding: 20px; background: #fff; border-radius: 4px; }
.box-card { height: auto; }
.status-flags { margin-top: 15px; display: flex; flex-direction: column; gap: 10px; }
.display-mode-toggle { margin-bottom: 15px; text-align: center; }
.card-footer { display: flex; justify-content: flex-end; margin-top: 15px; }
</style>
