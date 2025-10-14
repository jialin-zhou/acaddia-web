<template>
  <div class="tqml-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>同期命令</span>
          <div class="mode-selection">
            <el-radio-group v-model="mode" size="small">
              <el-radio-button label="received">接收到命令</el-radio-button>
              <el-radio-button label="sent">发合闸命令</el-radio-button>
              <el-radio-button label="timed">合闸时刻</el-radio-button>
            </el-radio-group>
          </div>
        </div>
      </template>

      <el-table :data="commandData" border style="width: 100%">
        <el-table-column label="信息" prop="label" width="120" />

        <el-table-column label="接收值">
          <template #default="scope">
            <el-date-picker v-if="scope.row.type === 'datetime'" v-model="scope.row.receivedValue" type="datetime" size="small" :disabled="mode !== 'received'" style="width: 100%;" value-format="YYYY-MM-DD HH:mm:ss" />
            <el-input v-else v-model="scope.row.receivedValue" size="small" :disabled="mode !== 'received'" style="width: 100%;" />
          </template>
        </el-table-column>

        <el-table-column label="发送值">
          <template #default="scope">
            <el-date-picker v-if="scope.row.type === 'datetime'" v-model="scope.row.sentValue" type="datetime" size="small" :disabled="mode !== 'sent'" style="width: 100%;" value-format="YYYY-MM-DD HH:mm:ss" />
            <el-input v-else v-model="scope.row.sentValue" size="small" :disabled="mode !== 'sent'" style="width: 100%;" />
          </template>
        </el-table-column>

        <el-table-column label="时刻值">
          <template #default="scope">
            <el-date-picker v-if="scope.row.type === 'datetime'" v-model="scope.row.timedValue" type="datetime" size="small" :disabled="mode !== 'timed'" style="width: 100%;" value-format="YYYY-MM-DD HH:mm:ss" />
            <el-input v-else v-model="scope.row.timedValue" size="small" :disabled="mode !== 'timed'" style="width: 100%;" />
          </template>
        </el-table-column>

        <el-table-column label="完成状态" width="120">
          <template #default="scope">
            <div v-if="scope.$index === 0" class="status-cell">
              <el-checkbox v-model="status.reset" label="复位" />
              <el-checkbox v-model="status.unfinished" label="未完成" />
            </div>
          </template>
        </el-table-column>
      </el-table>

      <div class="view-footer">
        <el-button @click="onFetch">信息读取</el-button>
        <el-button type="primary" @click="onExecute">同期开出</el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
export default {
  name: 'TqmlView',
  data() {
    return {
      mode: 'sent',
      commandData: [],
      status: { 
        reset: false,
        unfinished: false
      }
    };
  },
  created() { this.initializeData(); },
  methods: {
    initializeData() {
      const createRow = (label, type = 'text') => ({
        label,
        type,
        receivedValue: type === 'datetime' ? new Date() : '',
        sentValue: type === 'datetime' ? new Date() : '',
        timedValue: type === 'datetime' ? new Date() : ''
      });
      this.commandData = [
        createRow('Date', 'datetime'),
        createRow('(ms)'),
        createRow('U1(V)'),
        createRow('U2(V)'),
        createRow('f1(Hz)'),
        createRow('f2(Hz)'),
        createRow('f1/dT(Hz/S)'),
        createRow('f2/dT(Hz/S)'),
        createRow('Δu(V)'),
        createRow('Δf(Hz)'),
        createRow('df/dt(Hz/S)'),
        createRow('Δα(deg)')
      ];
    },
    onExecute() { this.$message.success('同期开出命令已发送'); },
    onFetch() { this.$message.info('信息读取命令已发送'); },
  }
};
</script>

<style scoped>
.tqml-view { padding: 20px; background: #fff; border-radius: 4px; }
.card-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 10px; }
.mode-selection { margin-left: auto; } /* Push radio group to the right */
.status-cell { display: flex; flex-direction: column; align-items: flex-start; justify-content: center; gap: 10px; padding-left: 10px;}
.view-footer { display: flex; justify-content: flex-end; gap: 10px; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #f0f2f5; }
</style>
