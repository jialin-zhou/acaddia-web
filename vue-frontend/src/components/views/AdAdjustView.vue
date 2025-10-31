<template>
  <div class="ad-adjust-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>Line 1 AC Channels</span>
        </div>
      </template>
      <el-table
        :data="acChannelsLine1"
        border
        size="small"
      >
        <el-table-column
          width="50"
          label="选择"
          align="center"
        >
          <template #default="scope">
            <el-radio
              v-model="selectedChannel"
              :label="`L1_${scope.row.nameKey}`"
            >
              &nbsp;
            </el-radio>
          </template>
        </el-table-column>
        <el-table-column
          label="通道号"
          prop="name"
          width="80"
        />
        <el-table-column label="校准源">
          <template #default="scope">
            <el-input
              v-model="scope.row.sourceValue"
              size="small"
            />
          </template>
        </el-table-column>
        <el-table-column
          label="修正系数"
          prop="correctionFactor"
          width="100"
        />
        <el-table-column
          label="原系数"
          prop="originalFactor"
          width="100"
        />
        <el-table-column
          label="计算值"
          prop="calculatedValue"
          width="100"
        />
        <el-table-column
          label="理想值"
          prop="idealValue"
          width="100"
        />
        <el-table-column
          label="状态"
          width="80"
          align="center"
        >
          <template #default="scope">
            <el-tag
              :type="scope.row.calibrated ? 'success' : 'warning'"
              size="small"
            >
              {{ scope.row.calibrated ? '已校准' : '未校准' }}
            </el-tag>
          </template>
        </el-table-column>
      </el-table>
    </el-card>

    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>Line 2 AC Channels</span>
        </div>
      </template>
      <el-table
        :data="acChannelsLine2"
        border
        size="small"
      >
        <el-table-column
          width="50"
          label="选择"
          align="center"
        >
          <template #default="scope">
            <el-radio
              v-model="selectedChannel"
              :label="`L2_${scope.row.nameKey}`"
            >
              &nbsp;
            </el-radio>
          </template>
        </el-table-column>
        <el-table-column
          label="通道号"
          prop="name"
          width="80"
        />
        <el-table-column label="校准源">
          <template #default="scope">
            <el-input
              v-model="scope.row.sourceValue"
              size="small"
            />
          </template>
        </el-table-column>
        <el-table-column
          label="修正系数"
          prop="correctionFactor"
          width="100"
        />
        <el-table-column
          label="原系数"
          prop="originalFactor"
          width="100"
        />
        <el-table-column
          label="计算值"
          prop="calculatedValue"
          width="100"
        />
        <el-table-column
          label="理想值"
          prop="idealValue"
          width="100"
        />
        <el-table-column
          label="状态"
          width="80"
          align="center"
        >
          <template #default="scope">
            <el-tag
              :type="scope.row.calibrated ? 'success' : 'warning'"
              size="small"
            >
              {{ scope.row.calibrated ? '已校准' : '未校准' }}
            </el-tag>
          </template>
        </el-table-column>
      </el-table>
    </el-card>

    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>DC Channels</span>
        </div>
      </template>
      <el-form label-width="120px">
        <el-row :gutter="20">
          <el-col :span="12">
            <el-form-item label="零漂校准选择">
              <el-select
                v-model="dcZeroDriftSelection"
                placeholder="选择DC通道"
                @change="val => selectedChannel = `DC_V${val}`"
              >
                <el-option
                  v-for="i in 8"
                  :key="i"
                  :label="`DC${i}`"
                  :value="i"
                />
              </el-select>
            </el-form-item>
          </el-col>
          <el-col :span="12">
            <el-form-item label="系数校准选择">
              <el-select
                v-model="dcFactorSelection"
                placeholder="选择DC通道"
                @change="val => selectedChannel = `DC_C${val}`"
              >
                <el-option
                  v-for="i in 8"
                  :key="i"
                  :label="`DC${i}`"
                  :value="i"
                />
              </el-select>
            </el-form-item>
          </el-col>
        </el-row>
      </el-form>
    </el-card>

    <div class="view-footer">
      <el-button
        :disabled="!isSerialConnected || !selectedChannel"
        @click="onFetchStatus"
      >
        获取校准状态
      </el-button>
      <el-button
        type="primary"
        :disabled="!isSerialConnected || !selectedChannel"
        @click="onCalibrate"
      >
        执行校准
      </el-button>
    </div>
  </div>
</template>

<script>
// [新增] 命令定义
// "执行校准" (通道校准)
const CMD_AD_ADJUST_APPLY = { stationAddr: 0, telegramNr: 0x26, expectedResponseId: 0xE5 }; // (C++: 38)
// "获取校准状态" (校准状态)
const CMD_AD_ADJUST_STATUS = { stationAddr: 0, telegramNr: 0x28, expectedResponseId: 0x29 }; // (C++: 40, 猜测响应 0x29)
// 响应 (非请求)
// 0x27 = 校准结果
// 0x29 = 状态结果

export default {
  name: 'AdAdjustView',
  props: {
    // [新增] 从 App.vue 传入 Props
    isSerialConnected: { type: Boolean, default: false },
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    puBaseValue: { type: Number, default: 16384 },
    currentSerialSettings: { type: Object, default: null },
    adAdjustStatusData: { type: Array, default: null }, // (0x29)
    adAdjustResultData: { type: Array, default: null }, // (0x27)
  },
  data() {
    return {
      acChannelsLine1: [],
      acChannelsLine2: [],
      dcZeroDriftSelection: 1,
      dcFactorSelection: 1,
      selectedChannel: null, // [新增] 用于跟踪当前选择的通道
    };
  },
  watch: {
    /**
     * @vuese
     * [新增] 监听来自 App.vue 的状态数据 (0x29 响应)
     */
    adAdjustStatusData(newData) {
      if (!newData || newData.length < 1) return;

      const channelId = newData[0]; // 1-based ID
      console.log(`[AdAdjustView] 收到状态 (0x29) for Channel ID ${channelId}:`, newData);
      this.$message.success(`已收到通道 ${channelId} 的校准状态`);

      // TODO: 需要响应协议才能解析
      // this.updateTableRow(channelId, newData, 'status');
    },
    /**
     * @vuese
     * [新增] 监听来自 App.vue 的结果数据 (0x27 响应)
     */
    adAdjustResultData(newData) {
      if (!newData || newData.length < 1) return;

      const channelId = newData[0]; // 1-based ID
      console.log(`[AdAdjustView] 收到结果 (0x27) for Channel ID ${channelId}:`, newData);
      this.$message.success(`已收到通道 ${channelId} 的校准结果`);

      // 假设结果表示校准成功
      this.updateTableRow(channelId, newData, 'result');
    }
  },
  created() {
    this.initializeState();
  },
  methods: {
    initializeState() {
      // [修改] nameKey 用于内部映射
      const createAcChannel = (name, nameKey, sourceValue) => ({ name, nameKey, sourceValue, correctionFactor: '0H', originalFactor: '0H', calculatedValue: '0H', idealValue: '4000H', calibrated: false });
      this.acChannelsLine1 = [
        createAcChannel('Ua(V)', 'Ua', '57.74'),
        createAcChannel('Ub(V)', 'Ub', '57.74'),
        createAcChannel('Uc(V)', 'Uc', '57.74'),
        createAcChannel('Ia(A)', 'Ia', '1'),
        createAcChannel('Ib(A)', 'Ib', '1'),
        createAcChannel('Ic(A)', 'Ic', '1')
      ];
      this.acChannelsLine2 = [
        createAcChannel('Ua(V)', 'Ua', '57.74'),
        createAcChannel('Ub(V)', 'Ub', '57.74'),
        createAcChannel('Uc(V)', 'Uc', '57.74'),
        createAcChannel('Ia(A)', 'Ia', '1'),
        createAcChannel('Ib(A)', 'Ib', '1'),
        createAcChannel('Ic(A)', 'Ic', '1')
      ];
    },

    /**
     * @vuese
     * [新增] "获取校准状态" 按钮 (0x28)
     */
    async onFetchStatus() {
      const channelIndex = this.getChannelIndex(this.selectedChannel); // 0-based index
      if (channelIndex === -1) {
        this.$message.error('内部错误：无法识别所选通道');
        return;
      }

      // Payload 是 1 字节 (基于用户 0x0D 示例)
      const payload = new Uint8Array([channelIndex + 1]); // 1-based ID

      this.$message.info(`正在获取通道 ${this.selectedChannel} (ID: ${channelIndex + 1}) 的校准状态 (0x28)...`);
      try {
        // 发送命令，响应将由 App.vue 捕获并通过 watcher(adAdjustStatusData) 传递回来
        await this.sendCommand({ commandDef: CMD_AD_ADJUST_STATUS, payload: payload });
      } catch (error) {
        this.$message.error(`获取状态失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * [修改] "执行校准" 按钮 (0x26)
     */
    async onCalibrate() {
      const channelIndex = this.getChannelIndex(this.selectedChannel); // 0-based index
      const sourceValue = this.getSourceValue(this.selectedChannel);
      const { dimPublic, currentStyle } = this.getSettings();

      if (channelIndex === -1) {
        this.$message.error('内部错误：无法识别所选通道');
        return;
      }
      if (sourceValue === null || isNaN(parseFloat(sourceValue))) {
        this.$message.error('无效的校准源数值，请输入数字');
        return;
      }

      // 1. 计算 Temp_short (基于 C++: onButtonApplyClicked)
      let tempShort = 0;
      const value = parseFloat(sourceValue);
      const type = this.selectedChannel.split('_')[1].substring(0, 1).toUpperCase();

      if (type === 'U') { // Ua, Ub, Uc
        tempShort = Math.round((value * dimPublic) / 57.74);
      } else if (type === 'I') { // Ia, Ib, Ic
        tempShort = Math.round((value * dimPublic) / (currentStyle === 0 ? 5.0 : 1.0));
      } else if (type === 'V') { // VDC (零漂)
        // C++: Temp_short = (Temp_float * pParent->DIM_public) / 2.5;
        // Dlg_ADAdjust1.cpp 514行，Temp_float 未初始化，假设是 0？
        // 零漂校准源的值应该是 0
        // 让我们假设 VDC 的校准源值 (sourceValue) *不是* 0，而是 C++ 514 行的 2.5
        // [修正] C++ 514-537 行的 Temp_float 变量未被赋值，它使用的是 490-512 (AC) 行的 Temp_float，这是个 Bug。
        // [修正] C++ 490 行的 Temp_float 来自 m_floatADAdjust_Ua_1 等，即 lineEdit 的值 (校准源)。
        // 因此，DC 零漂的计算 (VDC1-4, 8-11) 使用 (value * dimPublic) / 2.5
        // DC 系数 (CDC1-4, 12-15) 使用 (value * dimPublic) / 10.0
        tempShort = Math.round((value * dimPublic) / 2.5);
      } else if (type === 'C') { // CDC (系数)
        tempShort = Math.round((value * dimPublic) / 10.0);
      }

      // 2. 构建 4 字节 Payload (基于 C++: DATA[0] to DATA[3])
      const payload = new Uint8Array(4);
      payload[0] = channelIndex + 1;  // Channel ID (1-based)
      payload[1] = tempShort & 0xFF;  // Value Low
      payload[2] = (tempShort >> 8) & 0xFF; // Value High
      payload[3] = 0; // C++ 发送第 4 字节为 0

      this.$message.info(`正在校准通道 ${this.selectedChannel} (ID: ${channelIndex+1})，值: ${value} (Raw: ${tempShort})...`);

      try {
        // 发送命令 (0x26)，期望 E5 响应
        await this.sendCommand({ commandDef: CMD_AD_ADJUST_APPLY, payload: payload });
        this.$message.success('校准命令 (0x26) 已发送，等待设备响应...');
        // E5 将由 App.vue 处理。
        // 随后的 0x27 (结果) 响应将由 watcher(adAdjustResultData) 捕获。
      } catch (error) {
        this.$message.error(`校准命令发送失败: ${error?.message || error}`);
      }
    },

    // [修改] 移除了 onCancel() 方法

    /**
     * @vuese
     * [新增] 辅助函数：获取当前设置
     */
    getSettings() {
      const dimPublic = this.puBaseValue || 16384;
      // currentStyle 需要从 currentSerialSettings 获取, Dlg_ADAdjust1.cpp 510行
      // 暂时假设 currentStyle 在 currentSerialSettings 中
      const currentStyle = this.currentSerialSettings?.currentStyle ?? 1; // 默认为 1A
      return { dimPublic, currentStyle };
    },

    /**
     * @vuese
     * [新增] 辅助函数：根据 UI key (e.g., 'L1_Ua') 获取 C++ 索引 (0-based)
     */
    getChannelIndex(channelKey) {
      if (!channelKey) return -1;
      const parts = channelKey.split('_');
      const group = parts[0]; // 'L1', 'L2', 'DC'
      const key = parts[1];   // 'Ua', 'V1', 'C1'

      if (group === 'L1') {
        const acKeys = ['Ua', 'Ub', 'Uc', 'Ia', 'Ib', 'Ic'];
        return acKeys.indexOf(key); // 0-5
      }
      if (group === 'L2') {
        const acKeys = ['Ua', 'Ub', 'Uc', 'Ia', 'Ib', 'Ic'];
        return 6 + acKeys.indexOf(key); // 6-11
      }
      if (group === 'DC') {
        const type = key.substring(0, 1); // 'V' or 'C'
        const num = parseInt(key.substring(1), 10); // 1-8

        if (type === 'V') {
          // C++ 映射: VDC1-4 -> 12-15; VDC5-8 -> 20-23
          return (num <= 4) ? (12 + (num - 1)) : (20 + (num - 5)); // 1-based to 0-based
        }
        if (type === 'C') {
          // C++ 映射: CDC1-4 -> 16-19; CDC5-8 -> 24-27
          return (num <= 4) ? (16 + (num - 1)) : (24 + (num - 5));
        }
      }
      return -1; // 未找到
    },

    /**
     * @vuese
     * [新增] 辅助函数：根据 UI key 获取校准源输入值
     */
    getSourceValue(channelKey) {
      if (!channelKey) return null;
      const parts = channelKey.split('_');
      const group = parts[0];
      const key = parts[1];

      if (group === 'L1') {
        const row = this.acChannelsLine1.find(r => r.nameKey === key);
        return row ? row.sourceValue : null;
      }
      if (group === 'L2') {
        const row = this.acChannelsLine2.find(r => r.nameKey === key);
        return row ? row.sourceValue : null;
      }
      if (group === 'DC') {
        // DC 通道没有 "校准源" 输入框，它们使用固定的测试值
        // 零漂 (V) 校准源应为 0, 系数 (C) 校准源应为某个标准值
        // C++ (514, 526) 假定使用 2.5V 和 10mA/V
        // 让我们假设 DC 校准时，我们从 UI 读取的值是 0
        // [修正] C++ 代码显示它读取的是 AC 的输入值... 这是一个 Bug。
        // 让我们遵循 AC 的逻辑：DC 也应该有一个输入框，但 UI 上没有。
        // [妥协] 零漂校准发送 0，系数校准... 我没有输入框。
        // 让我们假设 DC 的 sourceValue 也是 0 (用于零漂) 或 1 (用于系数)，但这不合理。
        // [再次修正] C++ Dlg_ADAdjust1.cpp 490-512 行，Temp_float 是从 lineEdit (Ua1...Ic1) 获取的。
        // DC 部分 (514-537) *复用* 了这个 Temp_float 值，但 *没有* 重新赋值。
        // 这绝对是一个 Bug。
        // 唯一的例外是 490-512 行的 if 条件 (m_nADAdjust_ACChannel == 0..5) 不满足时（即 DC 被选中时），Temp_float 保持为 0.0f (在 Dlg_ADAdjust1.h 中初始化)。
        // 因此，对于 DC 校准，C++ 代码 *总是* 发送 0.0f。

        const type = key.substring(0, 1);
        if (type === 'V') return '0.0'; // 零漂校准，发送 0
        if (type === 'C') {
          // 系数校准。C++ 代码也发送 0...
          // 这不合理，但这是代码的写法。
          // 让我们假设系数校准时，用户应该在 *AC 通道* 的某个输入框里输入一个值？
          // 这太混乱了。
          // 让我们返回 null，强制报错。
          this.$message.error('DC 系数校准暂不支持 (C++ 逻辑不明确)');
          return null;
        }
      }
      return null;
    },

    /**
     * @vuese
     * [新增] 辅助函数：根据收到的数据更新 UI 表格
     */
    updateTableRow(channelId, data, type) {
      // 1-based ID 转 0-based index
      const channelIndex = channelId - 1;
      let targetRow = null;

      if (channelIndex >= 0 && channelIndex <= 5) {
        targetRow = this.acChannelsLine1[channelIndex];
      } else if (channelIndex >= 6 && channelIndex <= 11) {
        targetRow = this.acChannelsLine2[channelIndex - 6];
      } else {
        // DC 暂不处理
        console.log(`收到 DC (ID: ${channelId}) 的响应，暂未实现 UI 更新`);
        return;
      }

      if (!targetRow) return;

      if (type === 'result') {
        // 0x27 响应 (校准结果)
        targetRow.calibrated = true;
        // TODO: 解析 data[1...N] 更新其他字段 (correctionFactor 等)
        // 示例：targetRow.correctionFactor = `0x${data[1].toString(16)}`;
      } else if (type === 'status') {
        // 0x29 响应 (状态)
        // TODO: 解析 data[1...N] 更新所有字段
        // 示例：targetRow.calibrated = (data[10] === 1);
        // 示例：targetRow.correctionFactor = `0x...`;
      }
    },
  }
};
</script>

<style scoped>
.ad-adjust-view { padding: 20px; background-color: #f0f2f5; }
.box-card { margin-bottom: 20px; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.el-select { width: 100%; }

/* [新增] 页脚样式 */
.view-footer {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
  width: 100%;
  margin-top: 20px;
  padding-top: 20px;
  border-top: 1px solid #e4e7ed;
}

/* [新增] 修正单选按钮的对齐 */
.el-table ::v-deep(td.el-table__cell) .el-radio {
  padding: 0;
  margin: 0;
  vertical-align: middle;
}
.el-table ::v-deep(th.el-table__cell) {
  background-color: #fafafa;
}
</style>