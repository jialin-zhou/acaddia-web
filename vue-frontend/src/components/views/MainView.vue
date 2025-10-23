<template>
  <div class="main-view">
    <el-row
      :gutter="20"
      class="main-content-row"
    >
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
                <el-checkbox-group
                  v-model="displayOptions"
                  class="checkbox-group-vertical"
                >
                  <el-checkbox
                    label="line1"
                    size="large"
                  >
                    Line1
                  </el-checkbox>
                  <el-checkbox
                    label="line2"
                    size="large"
                  >
                    Line2
                  </el-checkbox>
                  <el-checkbox
                    label="dc"
                    size="large"
                  >
                    DC
                  </el-checkbox>
                </el-checkbox-group>
              </div>

              <div class="ad-table-wrapper">
                <el-table
                  v-loading="isLoading"
                  :data="filteredAdData"
                  border
                  size="small"
                  element-loading-text="正在加载数据..."
                  :empty-text="tableEmptyText"
                >
                  <el-table-column
                    prop="channel"
                    label="Channel"
                    width="80"
                  />
                  <el-table-column
                    prop="showItem"
                    label="ShowItem"
                    width="100"
                  />
                  <el-table-column
                    prop="second"
                    label="Second"
                    width="150"
                  />
                  <el-table-column
                    prop="percent"
                    label="%"
                    width="120"
                  />
                  <el-table-column
                    prop="count"
                    label="Count"
                  />
                </el-table>
              </div>
            </div>

            <div class="card-actions-footer">
              <el-button-group>
                <el-button
                  :disabled="!isSerialConnected || isLoading"
                  @click="onFetch"
                >
                  获取信息
                </el-button>
                <el-button
                  :disabled="isLoading"
                  @click="onSave"
                >
                  保存参数
                </el-button>
                <el-button
                  :disabled="isLoading"
                  @click="onOpenFile"
                >
                  打开文件
                </el-button>
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
              <el-table
                :data="paginatedMessages"
                border
                size="small"
                height="100%"
              >
                <el-table-column
                  prop="msgId"
                  label="MsgID"
                  width="80"
                />
                <el-table-column
                  prop="date"
                  label="Date"
                  width="120"
                />
                <el-table-column
                  prop="time"
                  label="Time"
                  width="100"
                />
                <el-table-column
                  prop="ms"
                  label="ms"
                  width="70"
                />
                <el-table-column
                  prop="event"
                  label="Event"
                />
              </el-table>
            </div>

            <div class="pagination-footer">
              <el-pagination
                v-model:current-page="currentPage"
                v-model:page-size="pageSize"
                layout="total, prev, pager, next"
                :total="processedMessages.length"
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
// (修改) 定义用户指定流程所需的命令及其响应
const CMD_REQ_AD_CALC = { stationAddr: 0, telegramNr: 0x25, expectedResponseId: 0x24 }; // AD计算值
const CMD_REQ_ANGLE = { stationAddr: 0, telegramNr: 0x2F, expectedResponseId: 0x30 };   // 角度矢量
const CMD_REQ_MESSAGE = { stationAddr: 0, telegramNr: 0x31, expectedResponseId: 0x32 }; // 通信报文 (Command 49->0x31, Response 50->0x32)

// (保留) 旧的 Message List 命令定义 (当前 onFetch 不会使用)
// const CMD_REQ_MSG_HEAD = { stationAddr: 0, telegramNr: 0x0C, expectedResponseId: 0x02 };
// const CMD_REQ_MSG_BODY = { stationAddr: 0, telegramNr: 0x0D, expectedResponseId: 0x03 };

export default {
  name: 'MainView',
  props: {
    isSerialConnected: { type: Boolean, default: false },
    currentSerialSettings: { type: Object, default: null },
    initialAdData: { type: Array, default: null },
    // messageData prop 仍然保留，但新的 onFetch 逻辑不会更新它
    messageData: { type: Object, default: null },
    // (修改) 确认 sendCommand prop 已接收
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") }
  },
  data() {
    return {
      displayOptions: ['line1', 'line2', 'dc'],
      masterAdData: [], // 用于存储处理后的 AD 计算值数据
      currentPage: 1,
      pageSize: 36, // 根据你的截图调整
      isLoading: false,
    };
  },
  computed: {
    filteredAdData() {
      if (!this.masterAdData || this.masterAdData.length === 0) return [];
      return this.masterAdData.filter(row => this.displayOptions.includes(row.type));
    },

    /**
     * @vuese
     * (无修改) 解析来自 App.vue 的 messageData prop (来自 0x02, 0x03 响应)。
     * 注意：由于 onFetch 已修改，此计算属性在新流程下不会更新。
     */
    processedMessages() {
      // 依赖 timestamp 触发更新
      if (!this.messageData || !this.messageData.timestamp) return [];

      // (基于 Dlg_ZJM.cpp 的辅助函数)
      const getDateString = (startDate, daysElapsed) => {
        const targetDate = new Date(startDate.getTime()); // 克隆日期
        targetDate.setDate(targetDate.getDate() + daysElapsed);
        const yyyy = targetDate.getFullYear();
        const mm = String(targetDate.getMonth() + 1).padStart(2, '0');
        const dd = String(targetDate.getDate()).padStart(2, '0');
        return `${yyyy}-${mm}-${dd}`;
      };
      // (基于 Dlg_ZJM.cpp 的辅助函数)
      const formatTime = (msSinceMidnight) => {
        const totalSeconds = Math.floor(msSinceMidnight / 1000);
        const ms = msSinceMidnight % 1000;
        const hours = Math.floor(totalSeconds / 3600) % 24;
        const minutes = Math.floor((totalSeconds % 3600) / 60);
        const seconds = totalSeconds % 60;
        const H = String(hours).padStart(2, '0');
        const M = String(minutes).padStart(2, '0');
        const S = String(seconds).padStart(2, '0');
        return { time: `${H}:${M}:${S}`, ms };
      };

      const baseDate1984 = new Date(1984, 0, 1); // JS 月份从0开始
      const messages = [];
      const headData = this.messageData.head; // (来自 0x02)
      const bodyData = this.messageData.body; // (来自 0x03)

      try {
        // 1. (基于 Dlg_ZJM.cpp) 处理 MsgList_h_ValidData[] (headData)
        if (headData && headData.length >= 14) {
          const msgNr = headData[13] & 0x7F; //
          for (let k = 0; k < msgNr; k++) {
            const offset = 14 + 8 * k; //
            if (headData.length < offset + 8) break; // 安全检查

            //
            const msgIDRaw = headData[offset] | (headData[offset + 1] << 8);
            const msgID = msgIDRaw - 32768; //

            //
            const daysRaw = headData[offset + 2] | (headData[offset + 3] << 8);
            const dateStr = getDateString(baseDate1984, daysRaw + 1); //

            //
            const msRaw = (headData[offset + 4] | (headData[offset + 5] << 8)) |
                ((headData[offset + 6] | (headData[offset + 7] << 8)) << 16);
            const { time, ms } = formatTime(msRaw);

            const event = (msgIDRaw > 32767) ? '+' : '-'; //

            messages.push({ msgId: msgID, date: dateStr, time, ms, event });
          }
        }

        // 2. (基于 Dlg_ZJM.cpp) 处理 MsgList_ValidData[] (bodyData)
        if (bodyData && bodyData.length >= 5 && headData) {
          const msgNrBody = bodyData[4] - 128;
          for (let kk = 0; kk < msgNrBody; kk++) {
            const bodyOffset = 5 + 8 * kk; //
            const headOffset = 6 + 8 * kk; //

            if (bodyData.length < bodyOffset + 1 || headData.length < headOffset + 7) {
              console.warn("Message list body parsing: out of bounds");
              break;
            }

            const msgIDRaw = bodyData[bodyOffset] | (headData[headOffset] << 8);
            const msgID = msgIDRaw - 32768; //

            const daysRaw = headData[headOffset + 1] | (headData[headOffset + 2] << 8);
            const dateStr = getDateString(baseDate1984, daysRaw + 1); //

            const msRaw = (headData[headOffset + 3] | (headData[headOffset + 4] << 8)) |
                ((headData[headOffset + 5] | (headData[headOffset + 6] << 8)) << 16);
            const { time, ms } = formatTime(msRaw);

            const event = (msgIDRaw > 32767) ? '+' : '-'; //

            messages.push({ msgId: msgID, date: dateStr, time, ms, event });
          }
        }
      } catch (e) {
        console.error("解析 Message List 数据失败:", e, this.messageData);
        return []; // 发生错误时返回空数组
      }

      return messages;
    },

    paginatedMessages() {
      const start = (this.currentPage - 1) * this.pageSize;
      const end = start + this.pageSize;
      // (修改) 使用 processedMessages (注意：数据源不再更新)
      return this.processedMessages.slice(start, end);
    },

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
     * (修改) 监视来自父组件的 initialAdData prop。
     * 当 App.vue 更新此 prop 时，会触发数据处理以实现初始加载。
     */
    initialAdData: {
      handler(newData) {
        if (newData && newData.length > 0) {
          console.log("MainView received initialAdData via watcher:", newData); // 调试
          // (修改) 恢复调用，用于处理初始连接时获取的数据
          this.processAdData(newData);
        } else {
          // 如果连接断开或初始数据为空，清空表格
          this.masterAdData = [];
        }
      },
      // immediate: true // 保持移除 immediate
    },
    // (无修改) 监视连接状态，断开时清空数据
    isSerialConnected(newVal) {
      if (!newVal) {
        this.masterAdData = [];
        // 清空 Message List 的数据源 (虽然 computed prop 不会自动清空显示)
        // this.messageData.head = null;
        // this.messageData.body = [];
        // this.messageData.timestamp = null;
      }
    }
  },
  methods: {
    /**
     * @vuese
     * (重写) 点击“获取信息”按钮时触发。
     * 实现用户描述的流程: 0x25 -> 0x2F -> 0x2F -> 0x31。
     * 接收到的 AD 数据 (0x24) 不更新表格，仅打印日志和注释。
     * 接收到的 Message 数据 (0x32) 打印日志和注释，不更新 Message List 表格。
     */
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.warn('请先连接串口');
        return;
      }
      // (修改) 增加检查 sendCommand 是否有效
      if (typeof this.sendCommand !== 'function' || this.sendCommand === this.$props.sendCommand) {
        this.$message.error('内部错误: sendCommand 方法未正确传递');
        console.error("sendCommand prop is not a valid function:", this.sendCommand);
        return;
      }

      this.isLoading = true; // 开始加载
      this.$message.info('正在通过 Web Serial API 获取最新信息...');

      try {
        // --- 执行用户指定的命令序列 ---

        // 1. 发送 0x25 (AD 计算值), 期望响应 0x24
        this.$message.info('1/4: 获取 AD 计算值 (0x25)...');
        const frameAd = await this.sendCommand({ commandDef: CMD_REQ_AD_CALC });
        if (frameAd && frameAd.type === 'data' && frameAd.telegramNr === CMD_REQ_AD_CALC.expectedResponseId) {
          const adPayloadArray = Array.from(frameAd.payload);
          console.log("Received AD Calc Data (0x24 Payload):", adPayloadArray);
          // ------------------------------------------------------------------
          // TODO: 用户要求暂不更新 AD 计算值表格。
          //       如果需要更新，取消下面的注释即可调用处理函数:
          // this.processAdData(adPayloadArray);
          // ------------------------------------------------------------------
          this.$message.info('AD 数据已收到 (暂不刷新表格)');
        } else {
          console.warn("Received unexpected response or ACK for AD Calc command:", frameAd);
          // 可以选择抛出错误停止序列，或者继续执行
          // throw new Error("获取 AD 计算值时收到意外响应");
        }

        // 2. 发送 0x2F (角度矢量), 期望响应 0x30
        this.$message.info('2/4: 获取角度矢量 (0x2F)...');
        const frameAngle1 = await this.sendCommand({ commandDef: CMD_REQ_ANGLE });
        if (frameAngle1 && frameAngle1.type === 'data' && frameAngle1.telegramNr === CMD_REQ_ANGLE.expectedResponseId) {
          console.log("Received Angle Data 1 (0x30 Payload):", Array.from(frameAngle1.payload));
        } else {
          console.warn("Received unexpected response or ACK for Angle command 1:", frameAngle1);
        }

        // 3. 再次发送 0x2F (角度矢量), 期望响应 0x30
        this.$message.info('3/4: 获取角度矢量 (再次发送 0x2F)...');
        const frameAngle2 = await this.sendCommand({ commandDef: CMD_REQ_ANGLE });
        if (frameAngle2 && frameAngle2.type === 'data' && frameAngle2.telegramNr === CMD_REQ_ANGLE.expectedResponseId) {
          console.log("Received Angle Data 2 (0x30 Payload):", Array.from(frameAngle2.payload));
        } else {
          console.warn("Received unexpected response or ACK for Angle command 2:", frameAngle2);
        }

        // 4. 发送 0x31 (通信报文), 期望响应 0x32
        this.$message.info('4/4: 获取通信报文 (0x31)...');
        const frameMessage = await this.sendCommand({ commandDef: CMD_REQ_MESSAGE });
        if (frameMessage && frameMessage.type === 'data' && frameMessage.telegramNr === CMD_REQ_MESSAGE.expectedResponseId) {
          const msgPayloadArray = Array.from(frameMessage.payload);
          console.log("Received Message Data (0x32 Payload):", msgPayloadArray);
          // ------------------------------------------------------------------
          // TODO: 用户希望此数据显示在 Message List，但根据 C++ 代码分析，
          //       主界面的 Message List 由 0x02/0x03 响应填充，且使用 processedMessages 计算属性。
          //       响应 0x32 的数据结构很可能不同，需要单独的解析逻辑，
          //       可能用于 "通信报文" 视图 (MessageView.vue)，而不是这里。
          //       因此，当前 Message List 表格不会被此数据显示。
          // ------------------------------------------------------------------
          this.$message.info('通信报文数据已收到 (需单独解析，不填充当前 Message List)');
        } else {
          console.warn("Received unexpected response or ACK for Message command:", frameMessage);
        }

        this.$message.success('获取信息序列执行完毕');

      } catch (error) {
        console.error('获取信息序列失败:', error);
        // (修改) 使用更健壮的错误消息显示
        this.$message.error(`获取信息失败: ${error?.message || error}`);
        // this.masterAdData = []; // 不需要清空，因为没有填充
      } finally {
        this.isLoading = false; // 结束加载
      }
    },

    /**
     * @vuese
     * (修改) 封装了处理原始AD数据 (number[]) 并更新 `masterAdData` 的逻辑。
     * 现在用于处理初始加载的数据。
     * @param {number[]} rawData - 从设备返回的原始字节数组 (已转换为 number[])。
     */
    processAdData(rawData) {
      if (!rawData || rawData.length === 0) {
        this.masterAdData = [];
        return;
      }
      try {
        const config = this.getMockConfig();
        this.masterAdData = this.calculateAdData(rawData, config);
        this.$message.success('AD数据已处理并更新表格'); // 修改提示
      } catch (error) {
        console.error('解析AD数据失败:', error);
        this.$message.error(`解析AD数据失败: ${error.message}`);
        this.masterAdData = [];
      }
    },

    /**
     * @vuese
     * (无修改) AD 数据计算核心逻辑。
     */
    calculateAdData(rawData, config) {
      const { currentStyle = 1, dimLineVotStyle = 0, dcViSelect = Array(8).fill(1) } = config;
      const DIM_PUBLIC = 16384.0;
      const results = [];
      const lineItemDefs = [ /* ... S 内容不变 ... */
        { name: 'Ua',      unit: 'V',   multiplier: 57.74 }, { name: 'Ub',      unit: 'V',   multiplier: 57.74 }, { name: 'Uc',      unit: 'V',   multiplier: 57.74 },
        { name: 'Uab',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 }, { name: 'Ubc',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 }, { name: 'Uca',     unit: 'V',   multiplier: dimLineVotStyle === 1 ? 57.74 : 100.0 },
        { name: 'Ia',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 }, { name: 'Ib',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 }, { name: 'Ic',      unit: 'A',   multiplier: currentStyle === 0 ? 5.0 : 1.0 },
        { name: 'P',       unit: 'W',   multiplier: currentStyle === 0 ? 865.5 : 173.1, signed: true }, { name: 'Q',       unit: 'Var', multiplier: currentStyle === 0 ? 865.5 : 173.1, signed: true }, { name: 'S',       unit: 'VA',  multiplier: currentStyle === 0 ? 865.5 : 173.1 },
        { name: 'f',       unit: 'Hz',  multiplier: 50.0 }, { name: 'Cos phi', unit: '',    multiplier: 1.0, signed: true },
      ];
      const dcItemDefs = Array.from({ length: 8 }, (_, i) => ({ /* ... 内容不变 ... */
        name: `DC${i + 1}`,
        unit: dcViSelect[i] === 0 ? 'V' : 'mA',
        multiplier: dcViSelect[i] === 0 ? 5.0 : 10.0,
      }));

      const processData = (channel, itemDefs, offset) => { /* ... 内容不变 ... */
        itemDefs.forEach((def, j) => {
          const dataIndex = offset + (j * 2);
          if (dataIndex + 1 >= rawData.length) { console.warn(`Data index out of bounds: index=${dataIndex}, length=${rawData.length}`); return; }
          let count = rawData[dataIndex] | (rawData[dataIndex + 1] << 8);
          let isNegative = false;
          let calculationCount = count;
          if (def.signed && count > 32767) { isNegative = true; calculationCount = (count ^ 0xFFFF) + 1; }
          const baseValue = calculationCount / DIM_PUBLIC;
          const finalValue = baseValue * def.multiplier;
          const percent = baseValue * 100;
          const prefix = isNegative ? '-' : '';
          results.push({ type: channel.toLowerCase().replace(' ', ''), channel: channel, showItem: def.name, second: `${prefix}${finalValue.toFixed(4)} ${def.unit}`.trim(), percent: `${prefix}${percent.toFixed(4)}%`, count: count, });
        });
      };

      // Dlg_ZJM.cpp offsets: DC[4], Line1[20], Line2[48]
      processData('DC',    dcItemDefs,   4);
      processData('Line1', lineItemDefs, 20);
      processData('Line2', lineItemDefs, 48);
      const channelSortOrder = { 'Line1': 1, 'Line2': 2, 'DC': 3 };
      results.sort((a, b) => { const orderA = channelSortOrder[a.channel] || 99; const orderB = channelSortOrder[b.channel] || 99; return orderA - orderB; });
      return results;
    },

    /** @vuese (无修改) */
    getMockConfig() { /* ... 内容不变 ... */
      return { currentStyle: 1, dimLineVotStyle: 0, dcViSelect: [1, 1, 1, 1, 1, 1, 1, 1], };
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
.main-view { padding: 20px; background-color: #f0f2f5; box-sizing: border-box; height: 100%; }
.main-content-row { height: 100%; }
.box-card { display: flex; flex-direction: column; height: 100%; }
.box-card ::v-deep(.el-card__header) { flex-shrink: 0; }
.box-card ::v-deep(.el-card__body) { flex-grow: 1; min-height: 0; padding: 20px; display: flex; flex-direction: column; }
.card-body-wrapper { display: flex; flex-direction: column; height: 100%; }
.ad-container { display: flex; flex-direction: row; flex-grow: 1; min-height: 0; }
.ad-controls { flex-shrink: 0; padding-right: 20px; }
.checkbox-group-vertical { display: flex; flex-direction: column; gap: 15px; }
.ad-table-wrapper { flex-grow: 1; overflow-y: auto; }
.card-actions-footer { flex-shrink: 0; display: flex; justify-content: center; align-items: center; padding-top: 20px; margin-top: auto; }
.msg-card-body-wrapper { display: flex; flex-direction: column; height: 100%; }
.msg-table-wrapper { flex-grow: 1; min-height: 0; overflow-y: auto; }
.pagination-footer { flex-shrink: 0; display: flex; justify-content: center; padding-top: 10px; }
</style>