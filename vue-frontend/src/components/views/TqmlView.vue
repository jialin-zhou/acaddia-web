<template>
  <div class="tqml-view">
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

      <el-table-column label="完成状态" width="120">
        <template #default="scope">
          <div v-if="scope.$index === 0" class="status-cell">
            <el-button type="primary" link @click="onResetStatus">复位</el-button>
            <el-checkbox v-model="status.unfinished" label="未完成" />
          </div>
        </template>
      </el-table-column>
    </el-table>

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
      status: { unfinished: false }
    };
  },
  created() { this.initializeData(); },
  methods: {
    initializeData() {
      const createRow = (label, type = 'text') => ({ label, type, receivedValue: type === 'datetime' ? new Date() : '', sentValue: type === 'datetime' ? new Date() : '', timedValue: type === 'datetime' ? new Date() : '' });
      this.commandData = [ createRow('Date', 'datetime'), createRow('(ms)'), createRow('U1(V)'), createRow('U2(V)'), createRow('f1(Hz)'), createRow('f2(Hz)'), createRow('f1/dT(Hz/S)'), createRow('f2/dT(Hz/S)'), createRow('Δu(V)'), createRow('Δf(Hz)'), createRow('df/dt(Hz/S)'), createRow('Δα(deg)') ];
    },
    onExecute() { this.$message.success('同期开出命令已发送'); },
    onFetch() { this.$message.info('信息读取命令已发送'); },
    onResetStatus() {
      this.status.unfinished = false;
      this.$message.success('状态已复位');
    }
  }
};
</script>

<style scoped>
.tqml-view { padding: 20px; background: #fff; border-radius: 4px; }
.status-cell { display: flex; flex-direction: column; align-items: center; justify-content: center; gap: 10px; }
.view-footer { display: flex; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #f0f2f5; }
</style>
