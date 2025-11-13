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
                  :disabled="isLoading || !adParamsRawData || adParamsRawData.length === 0"
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

// [新增] "下载参数" (Apply) 命令定义, 0x20 -> E5
// 对应 Dlg_AD1.cpp::onpushButtonAd1ApplyClicked()
// const CMD_SET_ACAD = { stationAddr: 0, telegramNr: 0x20, expectedResponseId: 0xE5 };

export default {
  name: 'MainView',
  props: {
    isSerialConnected: { type: Boolean, default: false },
    currentSerialSettings: { type: Object, default: null },
    initialAdData: { type: Array, default: null }, // 0x24
    messageData: { type: Object, default: null }, // 0x02, 0x03
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    /**
     * @vuese
     * [新增] 从 App.vue 传入的 ADParams 原始字节数组 (来自 0x20 响应)。
     * 用于 "保存参数" 功能。
     */
    adParamsRawData: { type: Array, default: null },
    /**
     * @vuese
     * [新增] 从 App.vue 传入的全局标幺基值 (16384 或 8192)。
     */
    puBaseValue: { type: Number, default: 16384 },
    /**
     * @vuese
     * [新增] 从 App.vue 传入的电压显示模式 (0 或 1)。
     */
    puVoltageMode: { type: Number, default: 0 },
  },
  /**
   * @vuese
   * [新增] 定义组件触发的事件。
   * load-params-from-file: 当 "打开文件" 成功读取文件时触发，携带 payload 数组。
   */
  emits: ['load-params-from-file'],
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
    /**
     * @vuese
     * [修改] 将 filteredAdData 改为计算属性。
     * 它现在依赖 masterAdData 和 displayOptions。
     * masterAdData 本身会在 initialAdData, puBaseValue, puVoltageMode 变化时被 watcher 重新计算。
     */
    filteredAdData() {
      if (!this.masterAdData || this.masterAdData.length === 0) return [];
      // 过滤逻辑保持不变
      return this.masterAdData.filter(row => this.displayOptions.includes(row.type));
    },

    /**
     * @vuese
     * (无修改) 解析来自 App.vue 的 messageData prop (来自 0x02, 0x03 响应)。
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

      // 按日期和时间降序排序
      messages.sort((a, b) => {
        const dateA = new Date(`${a.date}T${a.time}.${String(a.ms).padStart(3, '0')}`);
        const dateB = new Date(`${b.date}T${b.time}.${String(a.ms).padStart(3, '0')}`);
        return dateB - dateA; // 降序
      });

      return messages;
    },

    paginatedMessages() {
      const start = (this.currentPage - 1) * this.pageSize;
      const end = start + this.pageSize;
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
     * 监视来自父组件的 initialAdData prop。
     * 当 App.vue 更新此 prop 时，会触发数据处理。
     */
    initialAdData: {
      handler(newData) {
        if (newData && newData.length > 0) {
          console.log("MainView received initialAdData via watcher:", newData);
          this.processAdData(newData);
        } else {
          this.masterAdData = [];
        }
      },
      // immediate: true // 移除 immediate，避免在 pu props 未就绪时执行
    },
    /**
     * @vuese
     * [新增] 监视标幺基值变化，重新处理 AD 数据。
     */
    puBaseValue: {
      handler() {
        console.log("MainView puBaseValue changed, reprocessing AD data.");
        if (this.initialAdData && this.initialAdData.length > 0) {
          this.processAdData(this.initialAdData);
        }
      }
    },
    /**
     * @vuese
     * [新增] 监视电压显示模式变化，重新处理 AD 数据。
     */
    puVoltageMode: {
      handler() {
        console.log("MainView puVoltageMode changed, reprocessing AD data.");
        if (this.initialAdData && this.initialAdData.length > 0) {
          this.processAdData(this.initialAdData);
        }
      }
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
     * 点击“获取信息”按钮时触发。
     * 实现用户描述的流程: 0x25 -> 0x2F -> 0x2F -> 0x31。
     */
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.warn('请先连接串口');
        return;
      }
      if (typeof this.sendCommand !== 'function') {
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
        await this.sendCommand({ commandDef: CMD_REQ_AD_CALC }); // App.vue 的 processFrame 会处理 0x24 并更新 initialAdData

        // 2. 发送 0x2F (角度矢量), 期望响应 0x30
        this.$message.info('2/4: 获取角度矢量 (0x2F)...');
        await this.sendCommand({ commandDef: CMD_REQ_ANGLE }); // App.vue 的 processFrame 会处理 0x30 并更新 deviceAngleRawData

        // 3. 再次发送 0x2F (角度矢量), 期望响应 0x30
        this.$message.info('3/4: 获取角度矢量 (再次发送 0x2F)...');
        await this.sendCommand({ commandDef: CMD_REQ_ANGLE }); // 同上

        // 4. 发送 0x31 (通信报文), 期望响应 0x32
        this.$message.info('4/4: 获取通信报文 (0x31)...');
        await this.sendCommand({ commandDef: CMD_REQ_MESSAGE }); // App.vue 的 processFrame 会处理 0x32 (如果已添加逻辑)

        this.$message.success('获取信息序列执行完毕');

      } catch (error) {
        console.error('获取信息序列失败:', error);
        this.$message.error(`获取信息失败: ${error?.message || error}`);
      } finally {
        this.isLoading = false; // 结束加载
      }
    },

    /**
     * @vuese
     * 处理原始AD数据 (number[]) 并更新 `masterAdData` 的逻辑。
     * @param {number[]} rawData - 从设备返回的原始字节数组 (已转换为 number[])。
     */
    processAdData(rawData) {
      if (!rawData || rawData.length === 0) {
        this.masterAdData = [];
        return;
      }
      try {
        // [修改] 不再使用 mock config，直接使用 props
        // const config = this.getMockConfig();
        const config = {
          currentStyle: this.currentSerialSettings?.currentStyle ?? 1, // 需要从串口设置或AD参数获取，暂时假设为1
          dimLineVotStyle: this.puVoltageMode,
          dcViSelect: this.currentSerialSettings?.dcViSelect ?? Array(8).fill(1) // 需要从AD参数获取，暂时假设全为Current(1)
        };
        this.masterAdData = this.calculateAdData(rawData, config);
        // this.$message.success('AD数据已处理并更新表格'); // 频繁调用时可能干扰用户
      } catch (error) {
        console.error('解析AD数据失败:', error);
        this.$message.error(`解析AD数据失败: ${error.message}`);
        this.masterAdData = [];
      }
    },

    /**
     * @vuese
     * [修改] AD 数据计算核心逻辑，使用传入的标幺设置。
     */
    calculateAdData(rawData, config) {
      // 从 config 获取设置，并提供默认值
      const { currentStyle = 1, dimLineVotStyle = 0, dcViSelect = Array(8).fill(1) } = config;
      // [修改] 使用 prop 中的 puBaseValue
      const DIM_PUBLIC = parseFloat(this.puBaseValue); // 确保是浮点数

      // --- 输入检查 ---
      if (isNaN(DIM_PUBLIC) || DIM_PUBLIC <= 0) {
        console.error("Invalid puBaseValue:", this.puBaseValue);
        throw new Error("无效的标幺基值");
      }
      if (typeof dimLineVotStyle !== 'number' || (dimLineVotStyle !== 0 && dimLineVotStyle !== 1)) {
        console.error("Invalid puVoltageMode:", this.puVoltageMode);
        throw new Error("无效的电压标幺模式");
      }
      // ---(检查 currentStyle 和 dcViSelect 也可以添加)---


      const results = [];
      const lineItemDefs = [
        { name: 'Ua',      unit: 'V',   multiplier: 57.74 },
        { name: 'Ub',      unit: 'V',   multiplier: 57.74 },
        { name: 'Uc',      unit: 'V',   multiplier: 57.74 },
        // [修改] 使用 dimLineVotStyle (来自 puVoltageMode prop)
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
      const dcItemDefs = Array.from({ length: 8 }, (_, i) => ({
        name: `DC${i + 1}`,
        // [修改] 确保 dcViSelect[i] 有效，提供默认值
        unit: (dcViSelect[i] ?? 1) === 0 ? 'V' : 'mA',
        multiplier: (dcViSelect[i] ?? 1) === 0 ? 5.0 : 10.0,
      }));

      const processData = (channel, itemDefs, offset) => {
        itemDefs.forEach((def, j) => {
          const dataIndex = offset + (j * 2);
          if (dataIndex + 1 >= rawData.length) { console.warn(`Data index out of bounds: index=${dataIndex}, length=${rawData.length}`); return; }

          let count = rawData[dataIndex] | (rawData[dataIndex + 1] << 8);
          let isNegative = false;
          let calculationCount = count; // 用于计算的计数值

          // 处理有符号数 (P, Q, Cos phi)
          if (def.signed && count > 32767) {
            isNegative = true;
            calculationCount = (count ^ 0xFFFF) + 1; // 二补数转绝对值
            // 如果 calculationCount 仍然是负数或零（理论上不应发生），修正它
            if (calculationCount <= 0) {
              console.warn(`Signed conversion resulted in non-positive value for count ${count}. Using 32768.`);
              calculationCount = 32768; // 使用最大负数的绝对值作为近似
            }
          }

          // [修改] 确保 calculationCount 是非负数才进行除法
          const baseValue = calculationCount >= 0 ? (calculationCount / DIM_PUBLIC) : 0;
          const finalValue = baseValue * def.multiplier;
          const percent = baseValue * 100;

          const prefix = isNegative ? '-' : '';

          // 构造结果对象
          results.push({
            type: channel.toLowerCase().replace(' ', ''),
            channel: channel,
            showItem: def.name,
            // [修改] 格式化时应用前缀
            second: `${prefix}${finalValue.toFixed(4)} ${def.unit}`.trim(),
            percent: `${prefix}${percent.toFixed(4)}%`,
            count: count, // 显示原始计数值
          });
        });
      };

      // Dlg_ZJM.cpp offsets: DC[4], Line1[20], Line2[48]
      processData('DC',    dcItemDefs,   4);
      processData('Line1', lineItemDefs, 20);
      processData('Line2', lineItemDefs, 48);

      // 排序结果 (可选，保持原有逻辑)
      const channelSortOrder = { 'Line1': 1, 'Line2': 2, 'DC': 3 };
      results.sort((a, b) => {
        const orderA = channelSortOrder[a.channel] || 99;
        const orderB = channelSortOrder[b.channel] || 99;
        if (orderA !== orderB) return orderA - orderB;
        // 如果通道相同，可以按 ShowItem 排序 (可选)
        const itemOrder = lineItemDefs.findIndex(def => def.name === a.showItem);
        const itemOrderB = lineItemDefs.findIndex(def => def.name === b.showItem);
        if (itemOrder !== -1 && itemOrderB !== -1) return itemOrder - itemOrderB;
        // DC 的排序 (可选)
        const dcOrderA = parseInt(a.showItem.replace('DC', '')) || 99;
        const dcOrderB = parseInt(b.showItem.replace('DC', '')) || 99;
        return dcOrderA - dcOrderB;
      });
      return results;
    },


    /** @vuese (无修改) */
    getMockConfig() {
      console.warn("getMockConfig is deprecated. Settings should come from props.");
      return {
        currentStyle: 1, // 假设 1A
        dimLineVotStyle: 0, // 假设都显示 100%
        dcViSelect: Array(8).fill(1) // 假设都是 Current
      };
    },

    /**
     * @vuese
     * [修改] "保存参数" 按钮点击处理。
     * 将 App.vue 传入的 `adParamsRawData` (0x20 响应) 保存为 .bin 文件。
     * 这与 C++ Dlg_ZJM::OnButtonZjmSave() 功能对应。
     */
    async onSave() {
      if (!this.adParamsRawData || this.adParamsRawData.length === 0) {
        this.$message.error('没有 AD 参数数据可保存。请先连接设备或在 "AD参数" 页面点击 "获取参数"。');
        return;
      }

      // [修改] 验证：接受 93 字节 (标准) 或 89 字节 (设备固件)
      if (this.adParamsRawData.length !== 93 && this.adParamsRawData.length !== 89) {
        console.warn(`保存参数：adParamsRawData 长度为 ${this.adParamsRawData.length}，而不是预期的 93 或 89。仍将继续保存。`);

        // [BUG 修复] Element Plus 的方法是 'warning' 而不是 'warn'
        this.$message.warning(`参数数据长度 ( ${this.adParamsRawData.length} 字节) 与预期 (93 或 89 字节) 不符，但仍将保存。`);
      }

      // 1. 转换数据
      const dataBuffer = new Uint8Array(this.adParamsRawData);

      // 2. [新增] 使用 File System Access API (现代浏览器)
      if (window.showSaveFilePicker) {
        try {
          const fileHandle = await window.showSaveFilePicker({
            suggestedName: 'acaddia_ad_params.bin',
            types: [{
              description: 'AD Parameter File',
              accept: { 'application/octet-stream': ['.bin'] },
            }],
          });
          const writable = await fileHandle.createWritable();
          await writable.write(dataBuffer);
          await writable.close();
          this.$message.success('参数已保存 (acaddia_ad_params.bin)');
        } catch (e) {
          if (e.name !== 'AbortError') {
            console.error('保存文件失败:', e);
            this.$message.error(`保存失败: ${e.message}`);
          } else {
            this.$message.info('保存操作已取消');
          }
        }
      } else {
        // 3. [新增] 备用下载方法 (传统浏览器)
        try {
          const blob = new Blob([dataBuffer], { type: 'application/octet-stream' });
          const url = URL.createObjectURL(blob);
          const a = document.createElement('a');
          a.href = url;
          a.download = 'acaddia_ad_params.bin';
          document.body.appendChild(a);
          a.click();
          document.body.removeChild(a);
          URL.revokeObjectURL(url);
          this.$message.success('参数文件已开始下载');
        } catch (e) {
          console.error('备用保存方法失败:', e);
          this.$message.error(`保存失败: ${e.message}`);
        }
      }
    },

    /**
     * @vuese
     * [修改] "打开文件" 按钮点击处理。
     * 读取 .bin 文件, 并将其*加载*到 App.vue 的 adParamsRawData 状态中。
     * 这与 C++ Dlg_ZJM::OnButtonZjmOpen() 功能对应 (只加载，不发送)。
     */
    async onOpenFile() {
      // [修改] 打开文件不需要连接串口，C++ 版本也不需要
      // if (!this.isSerialConnected) {
      //   this.$message.warn('请先连接串口才能"打开"并下载参数');
      //   return;
      // }

      // 1. [新增] 使用 File System Access API (现代浏览器)
      if (window.showOpenFilePicker) {
        try {
          const [fileHandle] = await window.showOpenFilePicker({
            types: [{
              description: 'AD Parameter File',
              // [BUG 修复] 移除 '.*'
              accept: { 'application/octet-stream': ['.bin'] },
            }],
            multiple: false,
          });
          const file = await fileHandle.getFile();
          // 调用辅助方法
          await this.loadAndApplyFile(file);
        } catch (e) {
          if (e.name !== 'AbortError') {
            console.error('打开文件失败:', e);
            this.$message.error(`打开失败: ${e.message}`);
          } else {
            this.$message.info('打开操作已取消');
          }
        }
      } else {
        // 2. [新增] 备用 <input> 方法 (传统浏览器)
        const input = document.createElement('input');
        input.type = 'file';
        input.accept = '.bin,application/octet-stream';
        input.onchange = (e) => {
          const file = e.target.files[0];
          if (file) {
            // 调用辅助方法
            this.loadAndApplyFile(file);
          }
        };
        input.click();
      }
    },

    /**
     * @vuese
     * [修改] 辅助方法：读取 File 对象, 验证并*发送事件*
     * @param {File} file - The file object to read.
     */
    async loadAndApplyFile(file) {
      try {
        const arrayBuffer = await file.arrayBuffer();
        const payload = new Uint8Array(arrayBuffer);

        // [修改] 验证: 期望的 payload 是 93 字节 (标准) 或 89 字节 (固件)
        if (payload.length !== 93 && payload.length !== 89) {
          this.$message.error(`文件格式错误：期望 93 或 89 字节，但文件为 ${payload.length} 字节。`);
          return;
        }

        // [修改] C++ 逻辑: 打开文件只是加载数据，不发送
        // 触发事件，通知 App.vue 更新 adParamsRawData
        this.$message.info(`文件 "${file.name}" (${payload.length} 字节) 已加载。`);
        this.$emit('load-params-from-file', Array.from(payload)); // 转换为普通数组


      } catch (e) {
        console.error('读取或应用文件时出错:', e);
        this.$message.error(`读取或应用文件失败: ${e.message}`);
      }
    },

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