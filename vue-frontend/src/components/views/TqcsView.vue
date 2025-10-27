<template>
  <div class="tqcs-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>同期参数设置</span>
          <el-switch
            v-model="form.m_funcEnabled"
            active-text="功能已启用"
            inactive-text="功能已禁用"
            @change="onControlStateChanged"
          />
        </div>
      </template>

      <el-form class="top-settings-form">
        <el-row
          :gutter="20"
          align="middle"
        >
          <el-col :span="11">
            <el-form-item
              label="并网方式"
              label-width="80px"
            >
              <el-radio-group
                v-model="form.m_routineSelect"
                size="small"
                :disabled="!form.m_funcEnabled"
                @change="onControlStateChanged"
              >
                <el-radio-button :label="0">
                  自动
                </el-radio-button>
                <el-radio-button :label="1">
                  手动
                </el-radio-button>
              </el-radio-group>
              <el-radio-group
                v-model="form.m_syncStyle"
                :disabled="!form.m_funcEnabled || form.m_routineSelect !== 1"
                size="small"
                style="margin-left: 10px;"
              >
                <el-radio-button :label="0">
                  异步
                </el-radio-button>
                <el-radio-button :label="1">
                  同期
                </el-radio-button>
              </el-radio-group>
            </el-form-item>
          </el-col>

          <el-col :span="7">
            <el-form-item
              label="无压选择"
              label-width="80px"
            >
              <div
                class="checkbox-group-container"
                :class="{ 'is-disabled': !form.m_funcEnabled }"
              >
                <el-checkbox
                  v-model="form.m_l1DeadVoltCheck"
                  label="L1"
                  :disabled="!form.m_funcEnabled"
                  size="small"
                  border
                />
                <el-checkbox
                  v-model="form.m_l2DeadVoltCheck"
                  label="L2"
                  :disabled="!form.m_funcEnabled"
                  size="small"
                  border
                />
                <el-checkbox
                  v-model="form.m_allDeadVoltCheck"
                  label="全部"
                  :disabled="!form.m_funcEnabled"
                  size="small"
                  border
                />
              </div>
            </el-form-item>
          </el-col>

          <el-col :span="6">
            <el-form-item
              label="U相位"
              label-width="60px"
            >
              <el-radio-group
                v-model="form.m_phaseSelect"
                size="small"
                :disabled="!form.m_funcEnabled"
              >
                <el-radio-button :label="0">
                  A相
                </el-radio-button>
                <el-radio-button :label="1">
                  B相
                </el-radio-button>
                <el-radio-button :label="2">
                  C相
                </el-radio-button>
              </el-radio-group>
            </el-form-item>
          </el-col>
        </el-row>
      </el-form>

      <el-divider>详细参数</el-divider>

      <el-row
        :gutter="40"
        :class="{ 'is-disabled': !form.m_funcEnabled }"
      >
        <el-col :span="12">
          <el-form
            :model="form.paramsLeft"
            label-width="220px"
            label-position="left"
            class="params-form"
            :disabled="!form.m_funcEnabled"
          >
            <el-form-item
              v-for="(param, key) in form.paramsLeft"
              :key="key"
              :label="param.label"
            >
              <el-input
                v-model.number="param.value"
                type="number"
              >
                <template #append>
                  {{ param.unit }}
                </template>
              </el-input>
            </el-form-item>
          </el-form>
        </el-col>

        <el-col :span="12">
          <el-form
            :model="form.paramsRight"
            label-width="220px"
            label-position="left"
            class="params-form"
            :disabled="!form.m_funcEnabled"
          >
            <el-form-item
              v-for="(param, key) in form.paramsRight"
              :key="key"
              :label="param.label"
            >
              <el-input
                v-model.number="param.value"
                type="number"
              >
                <template #append>
                  {{ param.unit }}
                </template>
              </el-input>
            </el-form-item>
          </el-form>
        </el-col>
      </el-row>

      <div class="view-footer">
        <el-button @click="onDefault">
          恢复默认
        </el-button>
        <el-button @click="onCancel">
          取消
        </el-button>
        <el-button
          type="primary"
          @click="onApply"
        >
          应用
        </el-button>
        <el-button
          type="success"
          @click="onFetch"
        >
          读取
        </el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
// --- 通信命令定义 ---
// Fetch (读取): 发送 0x23 (十进制 35), 期望响应 0x22 (十进制 34)
const CMD_REQ_TQCS = { stationAddr: 0, telegramNr: 0x23, expectedResponseId: 0x22 };
// Apply (应用): 发送 0x22 (十进制 34), 期望响应 0xE5 (ACK)
const CMD_SET_TQCS = { stationAddr: 0, telegramNr: 0x22, expectedResponseId: 0xE5 };

export default {
  name: 'TqcsView',
  props: {
    /**
     * @vuese
     * 从 App.vue 传入的 `handleSendCommand` 方法，用于发送命令到串口。
     * @see App.vue
     */
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    /**
     * @vuese
     * 从 App.vue 传入的原始 TQCS 字节数组 (来自 0x22 响应)。
     * 当 App.vue 收到 0x22 报文时，会更新这个 prop。
     * @see App.vue
     */
    tqcsRawData: { type: Array, default: null },
  },
  data() {
    return {
      // 'form' 对象用于存储所有UI控件的状态。
      // 其结构和默认值基于 C++ 版本 (Dlg_TQCS1.h 和 Dlg_TQCS1.cpp::setDefaultValues)。
      form: {
        // --- 顶部控件 ---
        m_funcEnabled: true,    // "功能已启用" (C++: m_funcEnabled)
        m_routineSelect: 1, // "并网方式" 1: 手动 (C++: m_routineSelect = 1)
        m_syncStyle: 0,     // "同步方式" 0: 异步 (C++: m_syncStyle = 0)
        m_l1DeadVoltCheck: false, // "无压选择 L1"
        m_l2DeadVoltCheck: false, // "无压选择 L2"
        m_allDeadVoltCheck: false, // "无压选择 全部"
        m_phaseSelect: 0,   // "U相位" 0: A相 (C++: m_phaseSelect = 0)

        // --- 详细参数 (左侧) ---
        // 'key' 属性是至关重要的，它用于在 pack/parse 期间映射 C++ 成员变量名。
        paramsLeft: {
          t_cb: { label: 'T_CB (30-2000 ms)', value: 80, unit: 'ms', key: 'm_tcb' },
          d_amax: { label: 'Δαmax (0-50 °)', value: 10.0, unit: '°', key: 'm_damax' },
          d_usync: { label: 'ΔUsync (2-50 V)', value: 2.0, unit: 'V', key: 'm_duMax' },
          d_uasync: { label: 'ΔUasync (2-50 V)', value: 2.0, unit: 'V', key: 'm_dUmax2' },
          d_fsync: { label: 'Δfsync (10-60 mHz)', value: 20.0, unit: 'mHz', key: 'm_dfMax' },
          d_fasync: { label: 'Δfasync (0.1-1 Hz)', value: 0.1, unit: 'Hz', key: 'm_dFmax2' },
          umin: { label: 'Umin (20-120 V)', value: 52.0, unit: 'V', key: 'm_uMin' },
          umax: { label: 'Umax (20-120 V)', value: 63.5, unit: 'V', key: 'm_uMax' },
        },
        // --- 详细参数 (右侧) ---
        paramsRight: {
          udead: { label: 'Udead (2-50 V)', value: 2.0, unit: 'V', key: 'm_uDead' },
          tr_u1_u2: { label: 'Tr.U1-U2 (0-360 °)', value: 0.0, unit: '°', key: 'm_trU1U2' },
          df_dt_max: { label: 'dΔf/dtmax (0.1-2 Hz/s)', value: 0.2, unit: 'Hz/s', key: 'm_dfptMax' },
          fmin: { label: 'fmin (45-55 Hz)', value: 47.5, unit: 'Hz', key: 'm_fMin' },
          fmax: { label: 'fmax (45-55 Hz)', value: 52.5, unit: 'Hz', key: 'm_fMax' },
          t_syn_duration: { label: 'T-syn.Duration (2-30 s)', value: 30.0, unit: 's', key: 'm_tsynDuration' },
          t_synchron: { label: 'T Synchron (0-60 s)', value: 0.5, unit: 's', key: 'm_synchron' },
          df1_f2_dt: { label: 'd(f1-f2)/dt (0.1-2 Hz/s)', value: 0.2, unit: 'Hz/s', key: 'm_synchron2' },
        },
      }
    };
  },
  watch: {
    /**
     * @vuese
     * 监听从 App.vue 传入的 `tqcsRawData` prop。
     * 这是数据从设备->App.vue->本组件的入口点。
     * 当 `tqcsRawData` (0x22 响应报文) 发生变化时，调用解析函数 `parseDataFromBuffer` 来更新 UI。
     */
    tqcsRawData(newData) {
      if (newData && newData.length > 0) {
        console.log("TqcsView received tqcsRawData:", newData);
        this.parseDataFromBuffer(newData);
      }
    }
  },
  created() {
    // 组件实例创建时，立即加载 C++ 版本中定义的默认值。
    this.setDefaultValues();
  },
  methods: {
    // --- 核心通信方法 ---

    /**
     * @vuese
     * "应用" 按钮点击处理函数。
     * 1. 调用 `packDataToBuffer()` 将当前 `this.form` 状态序列化为字节数组 (payload)。
     * 2. 检查 payload 是否有效。
     * 3. 调用父组件传入的 `sendCommand` 方法，发送 "设置" 命令 (CMD_SET_TQCS, 0x22) 和 payload。
     * @see packDataToBuffer
     */
    async onApply() {
      this.$message.info('正在打包并应用参数...');

      // 1. 打包数据
      const payload = this.packDataToBuffer();
      if (!payload) {
        // packDataToBuffer 内部会显示错误信息
        return;
      }

      console.log("Applying TQCS data (payload length " + payload.length + "):", payload);

      // 3. 发送命令
      try {
        await this.sendCommand({ commandDef: CMD_SET_TQCS, payload: payload });
        this.$message.success('参数已应用 (0x22)');
      } catch (error) {
        console.error('应用 TQCS 参数失败:', error);
        this.$message.error(`应用参数失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * "读取" 按钮点击处理函数。
     * 1. 调用父组件传入的 `sendCommand` 方法，发送 "请求" 命令 (CMD_REQ_TQCS, 0x23)。
     * 2. (后续): App.vue 收到 0x22 响应后，会更新 `tqcsRawData` prop。
     * 3. (后续): `watch.tqcsRawData` 侦听器被触发，调用 `parseDataFromBuffer` 更新 UI。
     * @see watch.tqcsRawData
     * @see parseDataFromBuffer
     */
    async onFetch() {
      this.$message.info('正在读取参数 (0x23)...');
      try {
        // 仅发送 "请求" 命令。
        await this.sendCommand({ commandDef: CMD_REQ_TQCS });
        // 成功消息将在 parseDataFromBuffer 方法中显示，因为那是数据真正被解析的地方。
      } catch (error) {
        console.error('读取 TQCS 参数失败:', error);
        this.$message.error(`读取参数失败: ${error?.message || error}`);
      }
    },

    // --- C++ 逻辑移植 ---

    /**
     * @vuese
     * [移植] "恢复默认" 按钮点击处理。
     * C++: Dlg_TQCS1::onButtonDefaultClicked() -> setDefaultValues()
     * 注意：这只会重置浏览器前端的 `form` 数据，并不会向设备发送任何命令。
     */
    onDefault() {
      this.setDefaultValues();
      this.$message.warning('参数已在本地恢复为默认值 (未应用到设备)');
    },

    /**
     * @vuese
     * "取消" 按钮点击处理 (保留原逻辑)。
     * 目前仅显示提示信息。
     */
    onCancel() {
      this.$message.info('操作已取消');
      // 可以在此处选择是否重新 onFetch() 来丢弃未应用的更改，
      // 但当前保留为简单提示。
    },

    /**
     * @vuese
     * [移植] 将所有参数恢复为出厂默认值 (基于 Dlg_TQCS1.cpp::setDefaultValues)。
     * C++: Dlg_TQCS1::setDefaultValues()
     */
    setDefaultValues() {
      // --- 重置顶部控件 ---
      this.form.m_funcEnabled = true;
      this.form.m_routineSelect = 1; // 1: 手动
      this.form.m_syncStyle = 0;     // 0: 异步 (ASYN)
      this.form.m_l1DeadVoltCheck = false;
      this.form.m_l2DeadVoltCheck = false;
      this.form.m_allDeadVoltCheck = false;
      this.form.m_phaseSelect = 0;   // 0: A

      // --- 重置详细参数 (C++ 默认值) ---
      this.form.paramsLeft.t_cb.value = 80;
      this.form.paramsLeft.d_amax.value = 10.0;
      this.form.paramsLeft.d_usync.value = 2.0;    // m_duMax
      this.form.paramsLeft.d_uasync.value = 2.0;   // m_dUmax2
      this.form.paramsLeft.d_fsync.value = 20.0;   // m_dfMax
      this.form.paramsLeft.d_fasync.value = 0.1;   // m_dFmax2
      this.form.paramsLeft.umin.value = 52.0;      // m_uMin
      this.form.paramsLeft.umax.value = 63.5;      // m_uMax

      this.form.paramsRight.udead.value = 2.0;        // m_uDead
      this.form.paramsRight.tr_u1_u2.value = 0.0;     // m_trU1U2
      this.form.paramsRight.df_dt_max.value = 0.2;  // m_dfptMax
      this.form.paramsRight.fmin.value = 47.5;      // m_fMin
      this.form.paramsRight.fmax.value = 52.5;      // m_fMax
      this.form.paramsRight.t_syn_duration.value = 30.0; // m_tsynDuration
      this.form.paramsRight.t_synchron.value = 0.5;   // m_synchron
      // C++ 中 m_synchron2 = m_dfptMax
      this.form.paramsRight.df1_f2_dt.value = 0.2;

      console.log("TqcsView form reset to C++ defaults.");
    },

    /**
     * @vuese
     * [移植] 从 `tqcsRawData` (0x22 响应 payload) 字节数组中解析数据，填充到 `this.form`。
     * C++: Dlg_TQCS1::parseDataFromBuffer()
     * 注意: C++ 的 ValidData[4] 对应 JS 的 buffer[0] (即 payload 的第一个字节)。
     * @param {number[]} buffer - 原始字节数组 (payload)。
     */
    parseDataFromBuffer(buffer) {
      // 检查 payload 长度是否足够。C++ 中读取到索引 40 (payload 索引 36)，因此长度至少为 37。
      if (!buffer || buffer.length < 37) {
        console.warn("TQCS parse failed: buffer is null or too short.", buffer);
        this.$message.error('读取参数失败：设备响应数据格式不正确');
        return;
      }
      try {
        // --- 解析顶部控件 ---
        // C++: m_routineSelect = !ValidData[4]; (协议中 1=Auto, 0=Manual)
        // JS UI: (0=Auto, 1=Manual)
        // 所以 buffer[0] 为 1 (Auto) 时，设置 form.m_routineSelect = 0
        this.form.m_routineSelect = buffer[0] ? 0 : 1;
        this.form.m_syncStyle = buffer[1];     // C++: ValidData[5]
        this.form.m_l1DeadVoltCheck = !!buffer[2]; // C++: ValidData[6] (转为布尔值)
        this.form.m_l2DeadVoltCheck = !!buffer[3]; // C++: ValidData[7]
        this.form.m_allDeadVoltCheck = !!buffer[4]; // C++: ValidData[8]
        this.form.m_phaseSelect = buffer[5];     // C++: ValidData[9]

        // --- 解析详细参数 ---
        // 定义 C++ 结构体成员 (key) 与 payload 偏移量 (offset) 和换算系数 (div) 的映射
        const parseMap = {
          // key: { offset: C++ ValidData 索引 - 4, div: 换算系数 }
          'm_tcb': { offset: 6, div: 1 },         // C++: ValidData[10]
          'm_damax': { offset: 8, div: 100.0 },   // C++: ValidData[12]
          'm_duMax': { offset: 10, div: 100.0 },  // C++: ValidData[14]
          'm_dfMax': { offset: 12, div: 1 },      // C++: ValidData[16]
          'm_dUmax2': { offset: 14, div: 100.0 }, // C++: ValidData[18]
          'm_dFmax2': { offset: 16, div: 100.0 }, // C++: ValidData[20]
          'm_uDead': { offset: 18, div: 100.0 },  // C++: ValidData[22]
          'm_trU1U2': { offset: 20, div: 100.0 }, // C++: ValidData[24]
          'm_dfptMax': { offset: 22, div: 100.0 }, // C++: ValidData[26]
          'm_uMin': { offset: 24, div: 100.0 },  // C++: ValidData[28]
          'm_uMax': { offset: 26, div: 100.0 },  // C++: ValidData[30]
          'm_fMin': { offset: 28, div: 100.0 },  // C++: ValidData[32]
          'm_fMax': { offset: 30, div: 100.0 },  // C++: ValidData[34]
          'm_tsynDuration': { offset: 32, div: 10.0 }, // C++: ValidData[36]
          'm_synchron': { offset: 34, div: 10.0 }, // C++: ValidData[38]
        };

        // 辅助函数：用于解析单个参数
        const parseParam = (param) => {
          const info = parseMap[param.key];
          if (info) {
            // 读取 16 位小端整数，然后除以系数
            param.value = this.readShort(buffer, info.offset) / info.div;
          }
        };

        // 遍历左右两边的参数列表并解析
        Object.values(this.form.paramsLeft).forEach(parseParam);
        Object.values(this.form.paramsRight).forEach(parseParam);

        // C++: m_synchron2 = m_dfptMax; (同步2的值等于df/dtmax)
        this.form.paramsRight.df1_f2_dt.value = this.form.paramsRight.df_dt_max.value;

        // --- 解析功能启用标志 ---
        this.form.m_funcEnabled = !!buffer[36]; // C++: ValidData[40]

        this.$message.success('参数已从设备更新');

      } catch (e) {
        console.error("解析 TQCS 数据失败:", e);
        this.$message.error(`解析参数失败: ${e.message}`);
      }
    },

    /**
     * @vuese
     * [移植] 将 `this.form` 中的数据打包成字节流 (Uint8Array) 以便发送。
     * C++: Dlg_TQCS1::packDataToBuffer()
     * [重要] C++ 版本 (TeleProcess.cpp) 中存在一个 bug，导致实际只发送 40 字节。
     * 此处创建 40 字节的 buffer 来 *匹配* 该 bug 行为，确保设备能正确接收。
     * @returns {Uint8Array} 40字节的 payload。
     */
    packDataToBuffer() {
      // C++: uchar dataToSend[41]; ... memset(dataBuffer + 37, 0, 4);
      // C++ 意图是 41 字节，但 TeleProcess.cpp 的实现 bug 导致实际只发送 40 字节。
      // 我们在此创建 40 字节 (索引 0-39) 来匹配 C++ 的实际行为。
      const buffer = new Uint8Array(40);

      try {
        // --- 写入顶部控件 ---
        // JS UI: (0=Auto, 1=Manual) -> 协议: (1=Auto, 0=Manual)
        buffer[0] = this.form.m_routineSelect === 0 ? 1 : 0;
        buffer[1] = this.form.m_syncStyle;
        buffer[2] = this.form.m_l1DeadVoltCheck ? 1 : 0; // 布尔转 1/0
        buffer[3] = this.form.m_l2DeadVoltCheck ? 1 : 0;
        buffer[4] = this.form.m_allDeadVoltCheck ? 1 : 0;
        buffer[5] = this.form.m_phaseSelect;

        // --- 写入详细参数 ---
        // 映射 param key (C++ 成员变量名) 到 payload 缓冲区偏移量
        const offsetMap = {
          'm_tcb': 6, 'm_damax': 8, 'm_duMax': 10, 'm_dfMax': 12, 'm_dUmax2': 14,
          'm_dFmax2': 16, 'm_uDead': 18, 'm_trU1U2': 20, 'm_dfptMax': 22, 'm_uMin': 24,
          'm_uMax': 26, 'm_fMin': 28, 'm_fMax': 30, 'm_tsynDuration': 32, 'm_synchron': 34
          // C++: m_synchron2 不会被打包发送
        };
        // 映射 param key 到 C++ 存储时的乘数
        const multiplierMap = {
          'm_damax': 100, 'm_duMax': 100, 'm_dUmax2': 100, 'm_dFmax2': 100, 'm_uDead': 100,
          'm_trU1U2': 100, 'm_dfptMax': 100, 'm_uMin': 100, 'm_uMax': 100, 'm_fMin': 100,
          'm_fMax': 100, 'm_tsynDuration': 10, 'm_synchron': 10
        };

        // 辅助函数：用于打包单个参数
        const packParam = (param) => {
          const offset = offsetMap[param.key];
          if (offset === undefined) return; // 跳过 m_synchron2 等

          const multiplier = multiplierMap[param.key] || 1; // 默认为 1 (e.g., m_tcb)
          const value = parseFloat(param.value) || 0;
          // 将浮点数乘以系数，四舍五入，然后作为 16 位小端整数写入 buffer
          this.writeShort(buffer, offset, Math.round(value * multiplier));
        };

        // 遍历并打包所有参数
        Object.values(this.form.paramsLeft).forEach(packParam);
        Object.values(this.form.paramsRight).forEach(packParam);

        // --- 写入功能启用标志 ---
        buffer[36] = this.form.m_funcEnabled ? 1 : 0;
        // 索引 37, 38, 39 默认为 0 (Uint8Array 自动填充)
        // 索引 40 不存在 (为了匹配 C++ bug)

        return buffer;

      } catch (e) {
        console.error("打包 TQCS 数据失败:", e);
        this.$message.error(`打包参数失败: ${e.message}`);
        return null;
      }
    },

    // --- C++ UI 逻辑移植 ---

    /**
     * @vuese
     * [移植] C++: Dlg_TQCS1::onControlStateChanged()
     * 在 Vue 中，这部分逻辑由模板中的 `:disabled` 属性动态绑定实现。
     * 例如 `:disabled="!form.m_funcEnabled || form.m_routineSelect !== 1"`
     * 此函数保留为空，仅用于响应事件（如果未来需要）。
     */
    onControlStateChanged() {
      console.log("Control state changed. UI bindings will update automatically.");
    },

    // --- 辅助函数 ---

    /**
     * @vuese
     * [移植] 从指定的字节缓冲区和偏移量读取一个 ushort (16位小端)。
     * C++: Dlg_TQCS1::readShort
     * @param {number[]} buffer - 字节数组
     * @param {number} offset - 起始偏移量
     * @returns {number} 16位无符号整数
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Read short: offset ${offset} out of bounds for buffer length ${buffer.length}`);
      }
      // C++ (Little-Endian): (buffer[offset + 1] << 8) | buffer[offset];
      return buffer[offset] | (buffer[offset + 1] << 8);
    },

    /**
     * @vuese
     * [移植] 将一个 ushort 值写入指定的字节缓冲区和偏移量 (16位小端)。
     * C++: Dlg_TQCS1::writeShort
     * @param {Uint8Array} buffer - 目标字节数组
     * @param {number} offset - 写入的起始偏移量
     * @param {number} value - 要写入的 16 位整数
     */
    writeShort(buffer, offset, value) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Write short: offset ${offset} out of bounds for buffer length ${buffer.length}`);
      }
      buffer[offset] = value & 0xFF;            // 低字节
      buffer[offset + 1] = (value >> 8) & 0xFF; // 高字节
    },
  },
};
</script>

<style scoped>
/* 视图根元素样式 */
.tqcs-view { padding: 20px; background-color: #f0f2f5; }
/* 卡片头部样式 */
.card-header { display: flex; justify-content: space-between; align-items: center; }
/* 顶部设置表单的背景和内边距 */
.top-settings-form { background-color: #fafafa; padding: 15px 20px 5px; border-radius: 4px; margin-bottom: 20px; }
/* 详细参数输入框的后缀样式 */
.params-form ::v-deep(.el-input-group__append) {
  width: 70px;
  text-align: center;
}
/* 底部按钮栏样式 */
.view-footer { display: flex; justify-content: flex-end; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #e4e7ed; }

/* "无压选择" Checkbox 组的自定义样式，使其看起来像一个 RadioButton 组 */
.checkbox-group-container {
  display: inline-flex;
  border-radius: 4px;
  overflow: hidden;
}
.checkbox-group-container .el-checkbox.is-bordered {
  border-radius: 0;
  border-left-width: 0;
  margin: 0;
}
.checkbox-group-container .el-checkbox.is-bordered:first-child {
  border-left-width: 1px;
  border-top-left-radius: 4px;
  border-bottom-left-radius: 4px;
}
.checkbox-group-container .el-checkbox.is-bordered:last-child {
  border-top-right-radius: 4px;
  border-bottom-right-radius: 4px;
}

/* 当 "功能启用" 关闭时，用于禁用详细参数整行的样式 */
.el-row.is-disabled {
  opacity: 0.6;
  pointer-events: none;
}
/* 当 "功能启用" 关闭时，用于禁用 Checkbox 组的样式 */
.checkbox-group-container.is-disabled {
  opacity: 0.6;
  pointer-events: none;
}
</style>