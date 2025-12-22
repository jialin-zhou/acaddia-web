<template>
  <div class="ad-adjust-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>Line 1 AC Channels (交流通道 1)</span>
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
              placeholder="请输入数值"
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
          <span>Line 2 AC Channels (交流通道 2)</span>
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
              placeholder="请输入数值"
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
          <span>DC Channels (直流通道)</span>
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
        获取校准状态 (0x28)
      </el-button>
      <el-button
        type="primary"
        :disabled="!isSerialConnected || !selectedChannel"
        @click="onCalibrate"
      >
        执行校准 (0x26)
      </el-button>
    </div>
  </div>
</template>

<script>
// [新增] 命令定义
// "执行校准" (通道校准): 0x26
const CMD_AD_ADJUST_APPLY = { stationAddr: 0, telegramNr: 0x26, expectedResponseId: 0xE5 }; // (C++: 38)
// "获取校准状态" (校准状态): 0x28
const CMD_AD_ADJUST_STATUS = { stationAddr: 0, telegramNr: 0x28, expectedResponseId: 0x29 }; // (C++: 40, 猜测响应 0x29)
// 响应 (非请求)
// 0x27 = 校准结果
// 0x29 = 状态结果

export default {
  name: 'AdAdjustView',
  props: {
    // [新增] 从 App.vue 传入 Props: 串口连接状态
    isSerialConnected: { type: Boolean, default: false },
    // [新增] 从 App.vue 传入 Props: 发送命令函数
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    // [新增] 从 App.vue 传入 Props: PU 基准值 (例如 16384)
    puBaseValue: { type: Number, default: 16384 },
    // [新增] 从 App.vue 传入 Props: 串口设置 (可能包含 currentStyle)
    currentSerialSettings: { type: Object, default: null },
    // [新增] 从 App.vue 传入 Props: 校准状态数据 (0x29 响应)
    adAdjustStatusData: { type: Array, default: null },
    // [新增] 从 App.vue 传入 Props: 校准结果数据 (0x27 响应)
    adAdjustResultData: { type: Array, default: null },
  },
  data() {
    return {
      // Line 1 AC 通道数据列表
      acChannelsLine1: [],
      // Line 2 AC 通道数据列表
      acChannelsLine2: [],
      // DC 零漂校准选择的通道号 (1-8)
      dcZeroDriftSelection: 1,
      // DC 系数校准选择的通道号 (1-8)
      dcFactorSelection: 1,
      // [新增] 用于跟踪当前选择的通道 ('L1_Ua', 'L2_Ib', 'DC_V1', 'DC_C5' 等)
      selectedChannel: null,
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

      // TODO: 需要响应协议才能解析并更新 UI (this.updateTableRow(channelId, newData, 'status');)
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

      // 假设收到结果即表示校准成功 (UI 上标记为“已校准”)
      this.updateTableRow(channelId, newData, 'result');
      // TODO: 真正的更新需要解析数据
    }
  },
  created() {
    this.initializeState();
  },
  methods: {
    /**
     * 初始化 AC 通道的表格数据
     */
    initializeState() {
      // 辅助函数：创建 AC 通道对象
      // [修改] nameKey 用于内部映射
      const createAcChannel = (name, nameKey, sourceValue) => ({ name, nameKey, sourceValue, correctionFactor: '0H', originalFactor: '0H', calculatedValue: '0H', idealValue: '4000H', calibrated: false });

      // Line 1 AC 通道初始化 (ID 1-6)
      this.acChannelsLine1 = [
        createAcChannel('Ua(V)', 'Ua', '57.74'), // 标称 57.74V
        createAcChannel('Ub(V)', 'Ub', '57.74'),
        createAcChannel('Uc(V)', 'Uc', '57.74'),
        createAcChannel('Ia(A)', 'Ia', '1'), // 标称 1A
        createAcChannel('Ib(A)', 'Ib', '1'),
        createAcChannel('Ic(A)', 'Ic', '1')
      ];
      // Line 2 AC 通道初始化 (ID 7-12)
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
     * [新增] "获取校准状态" 按钮处理函数 (发送 0x28)
     */
    async onFetchStatus() {
      const channelIndex = this.getChannelIndex(this.selectedChannel); // 获取 0-based 索引
      if (channelIndex === -1) {
        this.$message.error('内部错误：无法识别所选通道');
        return;
      }

      // Payload 是 1 字节：通道 ID (1-based)
      const payload = new Uint8Array([channelIndex + 1]);

      this.$message.info(`正在获取通道 ${this.selectedChannel} (ID: ${channelIndex + 1}) 的校准状态 (0x28)...`);
      try {
        // 发送命令，响应 (0x29) 将由 watcher(adAdjustStatusData) 接收
        await this.sendCommand({ commandDef: CMD_AD_ADJUST_STATUS, payload: payload });
      } catch (error) {
        this.$message.error(`获取状态失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * [修改] "执行校准" 按钮处理函数 (发送 0x26)
     */
    async onCalibrate() {
      const channelIndex = this.getChannelIndex(this.selectedChannel); // 0-based index
      const sourceValue = this.getSourceValue(this.selectedChannel); // 获取校准源输入值
      const { dimPublic, currentStyle } = this.getSettings();

      if (channelIndex === -1) {
        this.$message.error('内部错误：无法识别所选通道');
        return;
      }
      if (sourceValue === null || isNaN(parseFloat(sourceValue))) {
        this.$message.error('无效的校准源数值，请输入数字');
        return;
      }

      // 1. 计算 Temp_short (要发送的原始 AD 值)
      let tempShort = 0;
      const value = parseFloat(sourceValue);
      // 提取通道类型：U (电压), I (电流), V (DC 零漂), C (DC 系数)
      const type = this.selectedChannel.split('_')[1].substring(0, 1).toUpperCase();

      if (type === 'U') { // AC 电压 (Ua, Ub, Uc)
        // C++: Temp_short = (Temp_float * pParent->DIM_public) / 57.74;
        tempShort = Math.round((value * dimPublic) / 57.74);
      } else if (type === 'I') { // AC 电流 (Ia, Ib, Ic)
        // C++: Temp_short = (Temp_float * pParent->DIM_public) / (currentStyle == 0 ? 5.0 : 1.0);
        // currentStyle 0: 5A, 1: 1A
        const currentBase = currentStyle === 0 ? 5.0 : 1.0;
        tempShort = Math.round((value * dimPublic) / currentBase);
      } else if (type === 'V') { // DC 零漂 (DC_V1, V2...)
        // 零漂校准源 (sourceValue) 应该为 0。
        // C++ 514 行：Temp_short = (Temp_float * pParent->DIM_public) / 2.5; Temp_float 实际为 0
        // 如果用户在 UI 上没有输入框，这里应发送 0。
        // 但为了兼容 C++ 代码逻辑，此处发送的 Raw 值是基于 2.5 的 (尽管 value 可能是 0)
        tempShort = Math.round((value * dimPublic) / 2.5);
      } else if (type === 'C') { // DC 系数 (DC_C1, C2...)
        // 系数校准源 (sourceValue) 应该为标准值。
        // C++ 526 行：Temp_short = (Temp_float * pParent->DIM_public) / 10.0; Temp_float 实际为 0
        // 同 VDC 零漂，C++ 存在 Bug，此处逻辑上发送的 Raw 值是基于 10.0 的。
        tempShort = Math.round((value * dimPublic) / 10.0);
      }

      // 3. 构建 4 字节 Payload (基于 C++: DATA[0] to DATA[3])
      const payload = new Uint8Array(4);
      payload[0] = channelIndex + 1;  // DATA[0]: Channel ID (1-based)
      payload[1] = tempShort & 0xFF;  // DATA[1]: Value Low Byte
      payload[2] = (tempShort >> 8) & 0xFF; // DATA[2]: Value High Byte
      payload[3] = 0; // DATA[3]: C++ 始终发送 0

      this.$message.info(`正在校准通道 ${this.selectedChannel} (ID: ${channelIndex+1})，校准源值: ${value} (Raw: ${tempShort})...`);

      try {
        // 发送命令 (0x26)，期望 E5 响应 (成功发送命令)
        await this.sendCommand({ commandDef: CMD_AD_ADJUST_APPLY, payload: payload });
        this.$message.success('校准命令 (0x26) 已发送，等待设备响应 (0x27)...');
      } catch (error) {
        this.$message.error(`校准命令发送失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * [新增] 辅助函数：获取 PU 基准值和电流互感器样式
     */
    getSettings() {
      const dimPublic = this.puBaseValue || 16384; // PU 基准值 (例如 16384)
      // currentStyle 0: 5A, 1: 1A (从串口设置中获取)
      const currentStyle = this.currentSerialSettings?.currentStyle ?? 1;
      return { dimPublic, currentStyle };
    },

    /**
     * @vuese
     * [新增] 辅助函数：根据 UI key (e.g., 'L1_Ua', 'DC_V1') 获取 C++ 索引 (0-based)
     * @param {string} channelKey - UI 中选择的通道键
     * @returns {number} 0-based 通道索引，未找到返回 -1
     */
    getChannelIndex(channelKey) {
      if (!channelKey) return -1;
      const parts = channelKey.split('_');
      const group = parts[0]; // 'L1', 'L2', 'DC'
      const key = parts[1];   // 'Ua', 'V1', 'C1'

      if (group === 'L1') {
        // AC Line 1: Ua(0), Ub(1), Uc(2), Ia(3), Ib(4), Ic(5)
        const acKeys = ['Ua', 'Ub', 'Uc', 'Ia', 'Ib', 'Ic'];
        return acKeys.indexOf(key); // 0-5
      }
      if (group === 'L2') {
        // AC Line 2: Ua(6), Ub(7), Uc(8), Ia(9), Ib(10), Ic(11)
        const acKeys = ['Ua', 'Ub', 'Uc', 'Ia', 'Ib', 'Ic'];
        return 6 + acKeys.indexOf(key); // 6-11
      }
      if (group === 'DC') {
        const type = key.substring(0, 1); // 'V' (零漂) or 'C' (系数)
        const num = parseInt(key.substring(1), 10); // 1-8

        // C++ 通道 ID 映射 (0-based Index):
        // VDC1-4: 12-15; VDC5-8: 20-23 (零漂)
        // CDC1-4: 16-19; CDC5-8: 24-27 (系数)

        if (type === 'V') { // DC 零漂
          // 1-based num 转 0-based index
          return (num <= 4) ? (12 + (num - 1)) : (20 + (num - 5));
        }
        if (type === 'C') { // DC 系数
          // 1-based num 转 0-based index
          return (num <= 4) ? (16 + (num - 1)) : (24 + (num - 5));
        }
      }
      return -1; // 未找到
    },

    /**
     * @vuese
     * [新增] 辅助函数：根据 UI key 获取校准源输入值
     * @param {string} channelKey - UI 中选择的通道键
     * @returns {string|null} 校准源输入值，或 null
     */
    getSourceValue(channelKey) {
      if (!channelKey) return null;
      const parts = channelKey.split('_');
      const group = parts[0];
      const key = parts[1];

      // 获取 AC 通道输入值
      if (group === 'L1') {
        const row = this.acChannelsLine1.find(r => r.nameKey === key);
        return row ? row.sourceValue : null;
      }
      if (group === 'L2') {
        const row = this.acChannelsLine2.find(r => r.nameKey === key);
        return row ? row.sourceValue : null;
      }

      // 获取 DC 通道输入值 (UI 上没有输入框，根据 C++ 逻辑进行假设)
      if (group === 'DC') {
        const type = key.substring(0, 1);
        if (type === 'V') {
          // 零漂校准，逻辑上校准源是 0V
          // [注意] C++ 代码实际上是读取 AC 的输入值，但 AC 的 if 不满足时，变量值为 0.0f。
          return '0.0';
        }
        if (type === 'C') {
          // 系数校准，逻辑上校准源应为标准值 (如 10.0V 或 10mA)
          // 但遵循 C++ 代码的 Bug，它也发送了 0.0f 对应的 Raw 值。
          // 为避免发送错误数据，这里强制返回 null，等待用户修复 C++ 逻辑或提供正确的 DC 校准源输入方案。
          this.$message.error('DC 系数校准的校准源输入值在 UI 上缺失，请在代码中确认或提供输入框。');
          return null;
        }
      }
      return null;
    },

    /**
     * @vuese
     * [新增] 辅助函数：根据收到的数据更新 UI 表格
     * @param {number} channelId - 1-based 通道 ID
     * @param {Array<number>} data - 响应数据
     * @param {string} type - 'result' (0x27) 或 'status' (0x29)
     */
    updateTableRow(channelId, data, type) {
      // 1-based ID 转 0-based index
      const channelIndex = channelId - 1;
      let targetRow = null;

      // AC Line 1 (ID 1-6 / Index 0-5)
      if (channelIndex >= 0 && channelIndex <= 5) {
        targetRow = this.acChannelsLine1[channelIndex];
      }
      // AC Line 2 (ID 7-12 / Index 6-11)
      else if (channelIndex >= 6 && channelIndex <= 11) {
        targetRow = this.acChannelsLine2[channelIndex - 6];
      }
      // DC 通道 (ID 13-28 / Index 12-27)
      else {
        console.log(`收到 DC (ID: ${channelId}) 的响应，暂未实现 UI 更新`);
        return;
      }

      if (!targetRow) return;

      if (type === 'result') {
        // 0x27 响应 (校准结果)
        targetRow.calibrated = true; // 假设收到结果即为校准成功
        // TODO: 解析 data[1...N] 更新其他字段 (correctionFactor, originalFactor 等)
      } else if (type === 'status') {
        // 0x29 响应 (状态)
        // TODO: 解析 data[1...N] 更新所有字段
      }
    },
  }
};
</script>

<style scoped>
.ad-adjust-view {
  padding: 20px;
  background-color: #f0f2f5;
}
.box-card {
  margin-bottom: 20px;
}
.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.el-select {
  width: 100%;
}

/* [新增] 页脚样式 */
.view-footer {
  display: flex;
  justify-content: flex-end; /* 按钮靠右对齐 */
  gap: 10px; /* 按钮间距 */
  width: 100%;
  margin-top: 20px;
  padding-top: 20px;
  border-top: 1px solid #e4e7ed;
}

/* [新增] 修正单选按钮的对齐 */
/* 使用深度选择器（::v-deep 或 /deep/）来修改 Element Plus 内部样式 */
.el-table ::v-deep(td.el-table__cell) .el-radio {
  padding: 0;
  margin: 0;
  vertical-align: middle;
}
.el-table ::v-deep(th.el-table__cell) {
  background-color: #fafafa; /* 表头背景色 */
}
</style>