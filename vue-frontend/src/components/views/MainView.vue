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
                <el-table
                    :data="filteredAdData"
                    border size="small"
                    v-loading="isLoading"
                    element-loading-text="正在加载数据..."
                    :empty-text="tableEmptyText"
                >
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
                <el-button @click="onFetch" :disabled="!isSerialConnected || isLoading">获取信息</el-button>
                <el-button @click="onSave" :disabled="isLoading">保存参数</el-button>
                <el-button @click="onOpenFile" :disabled="isLoading">打开文件</el-button>
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
// (新增) 导入 App.vue 定义的命令
const CMD_REQ_AD_CALC = { stationAddr: 0, telegramNr: 0x25, expectedResponseId: 0x24 };

export default {
  name: 'MainView',
  props: {
    isSerialConnected: { type: Boolean, default: false },
    currentSerialSettings: { type: Object, default: null },
    initialAdData: { type: Array, default: null },
    // (新增) 从 App.vue 接收发送命令的方法
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") }
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
      isLoading: false, // 新增：加载状态
    };
  },
  computed: {
    filteredAdData() {
      if (!this.masterAdData || this.masterAdData.length === 0) return [];
      return this.masterAdData.filter(row => this.displayOptions.includes(row.type));
    },
    paginatedMessages() {
      const start = (this.currentPage - 1) * this.pageSize;
      const end = start + this.pageSize;
      return this.messages.slice(start, end);
    },
    // 新增：根据状态计算表格空文本提示
    tableEmptyText() {
      if (this.isLoading) {
        return ' '; // 加载时显示加载动画，不显示文字
      } else if (!this.isSerialConnected) {
        return '请先连接串口';
      } else {
        return '无数据 (请尝试点击 获取信息)';
      }
    }
  },
  watch: {
    /**
     * @vuese
     * 监视来自父组件的 initialAdData prop。
     * 当 App.vue 在连接成功并执行完初始序列后更新此 prop 时，会触发数据处理。
     */
    initialAdData: {
      handler(newData) {
        if (newData && newData.length > 0) {
          // console.log("MainView received initialAdData:", newData); // 调试
          // this.$message.info('正在处理初始AD数据...'); // 可能会有点烦人，暂时注释
          this.processAdData(newData);
        } else {
          // 如果连接断开或初始数据为空，清空表格
          this.masterAdData = [];
        }
      },
      // immediate: true // 移除 immediate: true, 避免在组件创建时用 null 数据处理
    },
    // 新增：监视连接状态，断开时清空数据
    isSerialConnected(newVal) {
      if (!newVal) {
        this.masterAdData = [];
      }
    }
  },
  methods: {
    /**
     * @vuese
     * (重写) 点击“获取信息”按钮时触发。
     * 现在调用 App.vue 提供的 sendCommand 方法，通过 Web Serial API 发送获取 AD 数据的命令。
     */
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.warn('请先连接串口');
        return;
      }
      this.isLoading = true; // 开始加载
      this.$message.info('正在通过 Web Serial API 获取最新信息...');

      try {
        // 调用 App.vue 传递过来的 sendCommand 方法
        // 发送获取 AD 计算值的命令 (CMD_REQ_AD_CALC)
        // sendCommand 会返回一个 Promise，在收到对应的响应 (0x24) 后 resolve
        const responseFrame = await this.sendCommand({ commandDef: CMD_REQ_AD_CALC });

        // 收到响应后，responseFrame.payload 包含了新的 AD 数据
        // processFrame 在 App.vue 中应该已经更新了 initialAdData prop，
        // watch 会自动触发 processAdData。
        // 所以这里理论上不需要手动调用 processAdData，除非 App.vue 没有更新 prop。
        // 为保险起见，可以再次处理：
        if (responseFrame && responseFrame.payload) {
          this.processAdData(Array.from(responseFrame.payload));
        } else {
          this.$message.warning('获取信息命令成功，但未收到有效数据负载');
        }
        // this.$message.success('信息获取成功'); // processAdData 中已有提示

      } catch (error) {
        console.error('通过 Web Serial 获取或处理 AD 数据失败:', error);
        this.$message.error(`获取信息失败: ${error.message}`);
        this.masterAdData = []; // 获取失败时清空
      } finally {
        this.isLoading = false; // 结束加载
      }
    },

    /**
     * @vuese
     * 封装了处理原始AD数据 (number[]) 并更新表格的公共逻辑。
     * @param {number[]} rawData - 从设备返回的原始字节数组 (已转换为 number[])。
     */
    processAdData(rawData) {
      if (!rawData || rawData.length === 0) {
        this.masterAdData = [];
        // this.$message.warning('收到的AD数据为空'); // 避免过多提示
        return;
      }
      // console.log("Processing AD data in MainView:", rawData); // 调试

      try {
        // 使用模拟的配置参数
        const config = this.getMockConfig();
        // 调用核心计算函数处理原始数据
        this.masterAdData = this.calculateAdData(rawData, config);
        this.$message.success('AD数据已更新');
      } catch (error) {
        console.error('解析AD数据失败:', error);
        this.$message.error(`解析AD数据失败: ${error.message}`);
        this.masterAdData = []; // 解析失败也清空
      }
    },


    /**
     * @vuese
     * (无修改)
     * 根据从后端获取的原始字节数组，计算出要在表格中显示的最终值。
     * 此函数完整复现了 `Dlg_zjm.cpp` 中的核心计算逻辑，并增加了排序功能。
     * @param {number[]} rawData - 从设备返回的原始字节数组 (number[]形式)。
     * @param {object} config - 包含计算所需配置的对象。
     * @returns {object[]} - 可直接用于表格渲染的、已排序的对象数组。
     */
    calculateAdData(rawData, config) {
      // console.log("calculateAdData input:", rawData); // 调试
      const { currentStyle = 1, dimLineVotStyle = 0, dcViSelect = Array(8).fill(1) } = config; // DC select length 8
      const DIM_PUBLIC = 16384.0;
      const results = [];

      const lineItemDefs = [
        { name: 'Ua',      unit: 'V',   multiplier: 57.74 }, { name: 'Ub',      unit: 'V',   multiplier: 57.74 }, { name: 'Uc',      unit: 'V',   multiplier: 57.74 },
        { name: 'Uab',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 }, { name: 'Ubc',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 }, { name: 'Uca',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 },
        { name: 'Ia',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 }, { name: 'Ib',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 }, { name: 'Ic',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 },
        { name: 'P',       unit: 'W',   multiplier: currentStyle === 0 ? 865.5 : 173.1, signed: true }, { name: 'Q',       unit: 'Var', multiplier: currentStyle === 0 ? 865.5 : 173.1, signed: true }, { name: 'S',       unit: 'VA',  multiplier: currentStyle === 0 ? 865.5 : 173.1 },
        { name: 'f',       unit: 'Hz',  multiplier: 50.0 }, { name: 'Cos phi', unit: '',    multiplier: 1.0, signed: true },
      ];

      const dcItemDefs = Array.from({ length: 8 }, (_, i) => ({
        name: `DC${i + 1}`,
        unit: dcViSelect[i] === 0 ? 'V' : 'mA',
        multiplier: dcViSelect[i] === 0 ? 5.0 : 10.0,
      }));

      const processData = (channel, itemDefs, offset) => {
        itemDefs.forEach((def, j) => {
          const dataIndex = offset + (j * 2);
          if (dataIndex + 1 >= rawData.length) {
            console.warn(`Data index out of bounds: index=${dataIndex}, length=${rawData.length}`);
            return;
          }

          // 小端模式: 低字节在前 (index), 高字节在后 (index + 1)
          let count = rawData[dataIndex] | (rawData[dataIndex + 1] << 8);
          // console.log(`Processing ${channel}-${def.name}: raw=${rawData[dataIndex]}, ${rawData[dataIndex+1]} => count=${count}`); // 调试

          let isNegative = false;
          let calculationCount = count;

          if (def.signed && count > 32767) {
            isNegative = true;
            calculationCount = (count ^ 0xFFFF) + 1; // 2's complement to absolute value
          }

          const baseValue = calculationCount / DIM_PUBLIC;
          const finalValue = baseValue * def.multiplier;
          const percent = baseValue * 100;
          const prefix = isNegative ? '-' : '';

          results.push({
            type: channel.toLowerCase().replace(' ', ''),
            channel: channel,
            showItem: def.name,
            second: `${prefix}${finalValue.toFixed(4)} ${def.unit}`.trim(),
            percent: `${prefix}${percent.toFixed(4)}%`,
            count: count,
          });
        });
      };

      // Dlg_ZJM.cpp offsets: DC[4], Line1[20], Line2[48]
      processData('DC',    dcItemDefs,   4);
      processData('Line1', lineItemDefs, 20);
      processData('Line2', lineItemDefs, 48);

      const channelSortOrder = { 'Line1': 1, 'Line2': 2, 'DC': 3 };
      results.sort((a, b) => {
        const orderA = channelSortOrder[a.channel] || 99;
        const orderB = channelSortOrder[b.channel] || 99;
        return orderA - orderB;
      });
      // console.log("calculateAdData result:", results); // 调试
      return results;
    },

    /**
     * @vuese
     * (无修改) 生成模拟的配置参数。
     */
    getMockConfig() {
      return {
        currentStyle: 1,      // 0 for 5A, 1 for 1A
        dimLineVotStyle: 0, // 0 for 100V, 1 for 57.74V
        dcViSelect: [1, 1, 1, 1, 1, 1, 1, 1], // 8 channels
      };
    },

    onSave() { this.$message.info('保存参数功能待实现'); },
    onOpenFile() { this.$message.info('打开文件功能待实现'); },
    handleCurrentChange(val) { this.currentPage = val; },
  },
};
</script>

<style scoped>
/* 样式保持不变 */
.main-view, .main-content-row, .el-col, .box-card { height: 100%; }
.main-view { padding: 20px; background-color: #f0f2f5; box-sizing: border-box; height: 100%; /* 确保 main-view 填充可用高度 */ }
.main-content-row { height: 100%; } /* 确保行填充高度 */
.box-card { display: flex; flex-direction: column; height: 100%; /* 让卡片填充 el-col 的高度 */ }
.box-card ::v-deep(.el-card__header) { flex-shrink: 0; }
.box-card ::v-deep(.el-card__body) { flex-grow: 1; min-height: 0; padding: 20px; display: flex; flex-direction: column; /* 让 body 内容可伸缩 */}
.card-body-wrapper { display: flex; flex-direction: column; height: 100%; }
.ad-container { display: flex; flex-direction: row; flex-grow: 1; /* 让表格容器填充剩余空间 */ min-height: 0; /* 防止无限增长 */}
.ad-controls { flex-shrink: 0; padding-right: 20px; }
.checkbox-group-vertical { display: flex; flex-direction: column; gap: 15px; }
.ad-table-wrapper { flex-grow: 1; /* 表格包装器填充空间 */ overflow-y: auto; /* 如果内容过多则滚动 */ }
.card-actions-footer { flex-shrink: 0; display: flex; justify-content: center; align-items: center; padding-top: 20px; margin-top: auto; }
.msg-card-body-wrapper { display: flex; flex-direction: column; height: 100%; }
.msg-table-wrapper { flex-grow: 1; min-height: 0; overflow-y: auto; /* 添加滚动 */}
.pagination-footer { flex-shrink: 0; display: flex; justify-content: center; padding-top: 10px; } /* 调整分页符的上边距 */
</style>