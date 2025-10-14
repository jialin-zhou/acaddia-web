<template>
  <div class="main-view">
    <el-row :gutter="20" class="main-content-row">
      <el-col :span="14">
        <el-card class="box-card">
          <template #header>
            <div class="card-header">
              <span>AD计算值</span>
            </div>
          </template>

          <div class="card-body-wrapper">
            <div class="ad-container">
              <div class="ad-controls">
                <el-checkbox-group v-model="displayOptions" class="checkbox-group-vertical">
                  <el-checkbox label="line1" size="large">Line1</el-checkbox>
                  <el-checkbox label="line2" size="large">Line2</el-checkbox>
                  <el-checkbox label="dc" size="large">DC</el-checkbox>
                </el-checkbox-group>
              </div>

              <div class="ad-table-wrapper">
                <el-table :data="filteredAdData" border size="small">
                  <el-table-column prop="channel" label="Channel" width="80" />
                  <el-table-column prop="showItem" label="ShowItem" width="100" />
                  <el-table-column prop="second" label="Second" width="150" />
                  <el-table-column prop="percent" label="%" width="120" />
                  <el-table-column prop="count" label="Count" />
                </el-table>
              </div>
            </div>

            <div class="card-actions-footer">
              <el-button-group>
                <el-button @click="onFetch">获取信息</el-button>
                <el-button @click="onSave">保存参数</el-button>
                <el-button @click="onOpenFile">打开文件</el-button>
              </el-button-group>
            </div>
          </div>
        </el-card>
      </el-col>

      <el-col :span="10">
        <el-card class="box-card">
          <template #header>
            <div class="card-header">
              <span>Message List</span>
            </div>
          </template>

          <div class="msg-card-body-wrapper">
            <div class="msg-table-wrapper">
              <el-table :data="paginatedMessages" border size="small" height="100%">
                <el-table-column prop="msgId" label="MsgID" width="80" />
                <el-table-column prop="date" label="Date" width="120" />
                <el-table-column prop="time" label="Time" width="100" />
                <el-table-column prop="ms" label="ms" width="70" />
                <el-table-column prop="event" label="Event" />
              </el-table>
            </div>

            <div class="pagination-footer">
              <el-pagination
                  v-model:current-page="currentPage"
                  v-model:page-size="pageSize"
                  layout="total, prev, pager, next"
                  :total="messages.length"
                  @current-change="handleCurrentChange"
              />
            </div>
          </div>
        </el-card>
      </el-col>
    </el-row>
  </div>
</template>

<script>
export default {
  name: 'MainView',
  data() {
    // --- 数据初始化 ---

    // Line 1 的标准数据 (14行)
    const line1Data = [
      { type: 'line1', channel: 'Line1', showItem: 'Ua',      second: '0.6321 V',   percent: '1.0947%',   count: 185 },
      { type: 'line1', channel: 'Line1', showItem: 'Ub',      second: '0.0000 V',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Uc',      second: '0.0000 V',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Uab',     second: '0.6273 V',   percent: '0.6273%',   count: 106 },
      { type: 'line1', channel: 'Line1', showItem: 'Ubc',     second: '0.0000 V',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Uca',     second: '0.6273 V',   percent: '0.6273%',   count: 106 },
      { type: 'line1', channel: 'Line1', showItem: 'Ia',      second: '0.0000 A',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Ib',      second: '0.0000 A',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Ic',      second: '0.0000 A',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'P',       second: '0.0000 W',   percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Q',       second: '0.0000 Var', percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'S',       second: '0.0000 VA',  percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'f',       second: '0.0000 Hz',  percent: '0.0000%',   count: 0 },
      { type: 'line1', channel: 'Line1', showItem: 'Cos phi', second: '1.0000',     percent: '96.9535%',  count: 16384 },
    ];

    // Line 2 的数据通过复制 Line 1 生成
    const line2Data = [
      { type: 'line2', channel: 'line2', showItem: 'Ua',      second: '0.6321 V',   percent: '1.0947%',   count: 185 },
      { type: 'line2', channel: 'line2', showItem: 'Ub',      second: '0.0000 V',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Uc',      second: '0.0000 V',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Uab',     second: '0.6273 V',   percent: '0.6273%',   count: 106 },
      { type: 'line2', channel: 'line2', showItem: 'Ubc',     second: '0.0000 V',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Uca',     second: '0.6273 V',   percent: '0.6273%',   count: 106 },
      { type: 'line2', channel: 'line2', showItem: 'Ia',      second: '0.0000 A',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Ib',      second: '0.0000 A',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Ic',      second: '0.0000 A',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'P',       second: '0.0000 W',   percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Q',       second: '0.0000 Var', percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'S',       second: '0.0000 VA',  percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'f',       second: '0.0000 Hz',  percent: '0.0000%',   count: 0 },
      { type: 'line2', channel: 'line2', showItem: 'Cos phi', second: '1.0000',     percent: '96.9535%',  count: 16384 },
    ];

    // DC 的数据 (8行)
    const dcData = [
      { type: 'dc', channel: 'DC', showItem: 'DC1', second: '0.0000 mA', percent: '0.0000%', count: 0 },
      { type: 'dc', channel: 'DC', showItem: 'DC2', second: '0.0000 mA', percent: '0.0000%', count: 0 },
      { type: 'dc', channel: 'DC', showItem: 'DC3', second: '0.0000 mA', percent: '0.0000%', count: 0 },
      { type: 'dc', channel: 'DC', showItem: 'DC4', second: '0.0000 mA', percent: '0.0000%', count: 0 },
      { type: 'dc', channel: 'DC', showItem: 'DC5', second: '0.0000 mA', percent: '0.0000%', count: 0 },
      { type: 'dc', channel: 'DC', showItem: 'DC6', second: '0.0018 mA', percent: '0.0183%', count: 3 },
      { type: 'dc', channel: 'DC', showItem: 'DC7', second: '0.0000 mA', percent: '0.0000%', count: 0 },
      { type: 'dc', channel: 'DC', showItem: 'DC8', second: '0.0000 mA', percent: '0.0000%', count: 0 },
    ];

    const messages = Array.from({ length: 200 }, (v, i) => ({
      msgId: i % 2 === 0 ? '32717' : '2144',
      date: '2144-06-26', time: '11:04:18', ms: 125, event: i % 2 === 0 ? '+' : '-'
    }));

    return {
      // 1. 默认全部勾选
      displayOptions: ['line1', 'line2', 'dc'],
      masterAdData: [...line1Data, ...line2Data, ...dcData],
      messages,

      // 2. 分页相关状态
      currentPage: 1,
      // 默认每页行数 = Line1(14) + Line2(14) + DC(8) = 36
      pageSize: 36,
    };
  },
  computed: {
    // AD 计算值表格的数据源
    filteredAdData() {
      if (this.displayOptions.length === 0) return [];
      return this.masterAdData.filter(row => this.displayOptions.includes(row.type));
    },
    // Message List 表格的数据源，根据分页计算
    paginatedMessages() {
      const start = (this.currentPage - 1) * this.pageSize;
      const end = start + this.pageSize;
      return this.messages.slice(start, end);
    }
  },
  methods: {
    onFetch() { this.$message.info('正在获取最新信息...'); },
    onSave() { this.$message.success('参数已保存'); },
    onOpenFile() { this.$message.info('请选择要打开的文件'); },

    // 分页事件处理
    handleCurrentChange(val) {
      this.currentPage = val;
    },
  },
};
</script>

<style scoped>
.main-view, .main-content-row, .el-col, .box-card {
  height: 100%;
}

.main-view {
  padding: 20px;
  background-color: #f0f2f5;
  box-sizing: border-box;
}

.box-card {
  display: flex;
  flex-direction: column;
}

.box-card ::v-deep(.el-card__header) {
  flex-shrink: 0;
}

/* --- 左侧卡片样式 --- */
.box-card ::v-deep(.el-card__body) {
  flex-grow: 1;
  min-height: 0;
  padding: 20px;
}

.card-body-wrapper {
  display: flex;
  flex-direction: column;
  height: 100%;
}

.ad-container {
  display: flex;
  flex-direction: row;
  /* 移除 flex-grow，让其高度由内容决定 */
}

.ad-controls {
  flex-shrink: 0;
  padding-right: 20px;
}

.checkbox-group-vertical {
  display: flex;
  flex-direction: column;
  gap: 15px;
}

.ad-table-wrapper {
  width: 100%;
}

.card-actions-footer {
  flex-shrink: 0;
  display: flex;
  justify-content: center;
  align-items: center;
  padding-top: 20px;
  /* 将按钮推到底部 */
  margin-top: auto;
}

/* --- 右侧卡片样式 --- */
.msg-card-body-wrapper {
  display: flex;
  flex-direction: column;
  height: 100%;
}

.msg-table-wrapper {
  flex-grow: 1;
  min-height: 0;
}

.pagination-footer {
  flex-shrink: 0;
  display: flex;
  justify-content: center;
  padding-top: 20px;
}
</style>
