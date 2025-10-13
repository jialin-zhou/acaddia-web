<template>
  <div class="tqml-view">
    <div class="main-content">
      <!-- Command Table -->
      <el-table :data="commandData" border style="width: 100%">
        <el-table-column label="信息" prop="label" width="120" />

        <el-table-column label="接收到命令">
          <template #header>
            <el-radio v-model="mode" label="received">接收到命令</el-radio>
          </template>
          <template #default="scope">
            <el-date-picker v-if="scope.row.type === 'datetime'" v-model="scope.row.receivedValue" type="datetime" size="small" :disabled="mode !== 'received'" />
            <el-input v-else v-model="scope.row.receivedValue" size="small" :disabled="mode !== 'received'" />
          </template>
        </el-table-column>

        <el-table-column label="发合闸命令">
          <template #header>
            <el-radio v-model="mode" label="sent">发合闸命令</el-radio>
          </template>
          <template #default="scope">
            <el-date-picker v-if="scope.row.type === 'datetime'" v-model="scope.row.sentValue" type="datetime" size="small" :disabled="mode !== 'sent'" />
            <el-input v-else v-model="scope.row.sentValue" size="small" :disabled="mode !== 'sent'" />
          </template>
        </el-table-column>

        <el-table-column label="合闸时刻">
          <template #header>
            <el-radio v-model="mode" label="timed">合闸时刻</el-radio>
          </template>
          <template #default="scope">
            <el-date-picker v-if="scope.row.type === 'datetime'" v-model="scope.row.timedValue" type="datetime" size="small" :disabled="mode !== 'timed'" />
            <el-input v-else v-model="scope.row.timedValue" size="small" :disabled="mode !== 'timed'" />
          </template>
        </el-table-column>
      </el-table>

      <!-- Status Section -->
      <el-card shadow="never" header="完成状态" class="status-card">
        <el-checkbox v-model="status.reset">复归</el-checkbox>
        <el-checkbox v-model="status.unfinished">未完成</el-checkbox>
      </el-card>
    </div>

    <div class="view-footer">
      <el-button type="primary" @click="onExecute">同期开出</el-button>
      <el-button @click="onFetch">信息读取</el-button>
    </div>
  </div>
</template>

<script>
export default {
  name: 'TqmlView',
  data() {
    return {
      mode: 'sent',
      commandData: [],
      status: { reset: false, unfinished: false }
    };
  },
  created() { this.initializeData(); },
  methods: {
    initializeData() {
      const createRow = (label, type = 'text') => ({ label, type, receivedValue: type === 'datetime' ? new Date() : '', sentValue: type === 'datetime' ? new Date() : '', timedValue: type === 'datetime' ? new Date() : '' });
      this.commandData = [ createRow('Date', 'datetime'), createRow('(ms)'), createRow('U1(V)'), createRow('U2(V)'), createRow('f1(Hz)'), createRow('f2(Hz)'), createRow('f1/dT(Hz/S)'), createRow('f2/dT(Hz/S)'), createRow('Δu(V)'), createRow('Δf(Hz)'), createRow('df/dt(Hz/S)'), createRow('Δα(deg)') ];
    },
    onExecute() { this.$message.success('同期开出命令已发送'); },
    onFetch() { this.$message.info('信息读取命令已发送'); }
  }
};
</script>

<style scoped>
.tqml-view { padding: 20px; background: #fff; border-radius: 4px; }
.main-content { display: flex; gap: 20px; }
.status-card { width: 200px; flex-shrink: 0; }
.el-checkbox-group, .el-radio-group { display: flex; flex-direction: column; gap: 15px; }
.view-footer { display: flex; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #f0f2f5; }
</style>
