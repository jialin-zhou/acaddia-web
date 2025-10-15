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
                <el-button @click="onFetch" :disabled="!isSerialConnected">获取信息</el-button>
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
  props: {
    /**
     * @vuese
     * 由父组件(App.vue)传入，指示串口是否已连接。
     * 用于控制“获取信息”按钮的可用状态。
     */
    isSerialConnected: {
      type: Boolean,
      default: false,
    },
  },
  data() {
    // 伪造的 Message List 数据，用于占位
    const messages = Array.from({ length: 200 }, (v, i) => ({
      msgId: i % 2 === 0 ? '32717' : '2144',
      date: '2144-06-26', time: '11:04:18', ms: 125, event: i % 2 === 0 ? '+' : '-'
    }));

    return {
      displayOptions: ['line1', 'line2', 'dc'],
      masterAdData: [],
      messages,
      currentPage: 1,
      pageSize: 36,
    };
  },
  computed: {
    filteredAdData() {
      if (this.displayOptions.length === 0) return [];
      return this.masterAdData.filter(row => this.displayOptions.includes(row.type));
    },
    paginatedMessages() {
      const start = (this.currentPage - 1) * this.pageSize;
      const end = start + this.pageSize;
      return this.messages.slice(start, end);
    }
  },
  methods: {
    /**
     * @vuese
     * 点击“获取信息”按钮时触发。
     * 该函数向后端发起一个 HTTP GET 请求来获取 AD 原始数据，
     * 然后调用 calculateAdData 方法处理数据并更新表格。
     */
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.warn('请先连接串口');
        return;
      }
      this.$message.info('正在获取最新信息...');

      try {
        // 向后端发起真实请求
        const response = await fetch('http://localhost:8080/api/device/ad-data');
        const result = await response.json();

        if (!response.ok) {
          throw new Error(result.error || `HTTP 错误! 状态: ${response.status}`);
        }

        // 后端返回的是一个字节数组 (e.g., [1, 185, ...])
        const rawData = result;
        
        // 使用模拟的配置参数，这部分未来可以从其他后端接口获取
        const config = this.getMockConfig();

        // 调用核心计算函数处理原始数据
        this.masterAdData = this.calculateAdData(rawData, config);
        this.$message.success('信息获取成功');

      } catch (error) {
        console.error('获取或处理AD数据失败:', error);
        this.$message.error(`获取信息失败: ${error.message}`);
      }
    },

    /**
     * @vuese
     * 根据从后端获取的原始字节数组，计算出要在表格中显示的最终值。
     * 此函数完整复现了 `Dlg_zjm.cpp` 中的核心计算逻辑，并增加了排序功能。
     * @param {number[]} rawData - 从设备返回的原始字节数组。
     * @param {object} config - 包含计算所需配置的对象。
     * @returns {object[]} - 可直接用于表格渲染的、已排序的对象数组。
     */
    calculateAdData(rawData, config) {
      const { currentStyle = 1, dimLineVotStyle = 0, dcViSelect = Array(12).fill(1) } = config;
      const DIM_PUBLIC = 16384.0;
      const results = [];

      const lineItemDefs = [
        { name: 'Ua',      unit: 'V',   multiplier: 57.74 },
        { name: 'Ub',      unit: 'V',   multiplier: 57.74 },
        { name: 'Uc',      unit: 'V',   multiplier: 57.74 },
        { name: 'Uab',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 },
        { name: 'Ubc',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 },
        { name: 'Uca',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 },
        { name: 'Ia',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 },
        { name: 'Ib',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 },
        { name: 'Ic',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 },
        { name: 'P',       unit: 'W',   multiplier: currentStyle === 0 ? 865.5 : 173.1, signed: true },
        { name: 'Q',       unit: 'Var', multiplier: currentStyle === 0 ? 865.5 : 173.1, signed: true },
        { name: 'S',       unit: 'VA',  multiplier: currentStyle === 0 ? 865.5 : 173.1 },
        { name: 'f',       unit: 'Hz',  multiplier: 50.0 },
        { name: 'Cos phi', unit: '',    multiplier: 1.0, signed: true },
      ];

      const dcItemDefs = Array.from({ length: 12 }, (_, i) => ({
        name: `DC${i + 1}`,
        unit: dcViSelect[i] === 0 ? 'V' : 'mA',
        multiplier: dcViSelect[i] === 0 ? 5.0 : 10.0,
      }));

      const processData = (channel, itemDefs, offset) => {
        itemDefs.forEach((def, j) => {
          const dataIndex = offset + (j * 2);
          if (dataIndex + 1 >= rawData.length) return;

          let count = rawData[dataIndex] | (rawData[dataIndex + 1] << 8);

          let isNegative = false;
          if (def.signed && count > 32767) {
            isNegative = true;
            count = (count ^ 0xFFFF) + 1;
          }

          const baseValue = count / DIM_PUBLIC;
          const finalValue = baseValue * def.multiplier;
          const percent = baseValue * 100;

          results.push({
            type: channel.toLowerCase().replace(' ', ''),
            channel: channel,
            showItem: def.name,
            second: `${isNegative ? '-' : ''}${finalValue.toFixed(4)} ${def.unit}`.trim(),
            percent: `${isNegative ? '-' : ''}${percent.toFixed(4)}%`,
            count: count,
          });
        });
      };

      // 根据C++代码分析，各个数据块在 `ADCacul_ValidData` 数组中的起始偏移量如下：
      processData('DC',    dcItemDefs,   4);
      processData('Line1', lineItemDefs, 28);
      processData('Line2', lineItemDefs, 56);

      // **新增排序逻辑**：确保表格数据按 Line1 -> Line2 -> DC 的顺序显示
      const channelSortOrder = { 'Line1': 1, 'Line2': 2, 'DC': 3 };
      results.sort((a, b) => {
        const orderA = channelSortOrder[a.channel] || 99;
        const orderB = channelSortOrder[b.channel] || 99;
        return orderA - orderB;
      });

      return results;
    },

    /**
     * @vuese
     * 生成模拟的配置参数，用于前端调试。
     * 在真实场景中，这些参数也应该通过后端接口从设备获取。
     */
    getMockConfig() {
      return {
        currentStyle: 1,      // 0 for 5A, 1 for 1A
        dimLineVotStyle: 0, // 0 for 100V, 1 for 57.74V
        dcViSelect: [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], // 0 for V, 1 for mA
      };
    },

    onSave() { this.$message.success('参数已保存'); },
    onOpenFile() { this.$message.info('请选择要打开的文件'); },
    handleCurrentChange(val) { this.currentPage = val; },
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
  margin-top: auto;
}

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
