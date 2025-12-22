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
// --- 通信命令定义 (Protocol Definitions) ---
// 对应 C++: TeleProcess.cpp 中的命令处理分支
// Fetch (读取): 主机发送 0x23 (Request), 从机应答 0x22 (Response Data)
const CMD_REQ_TQCS = { stationAddr: 0, telegramNr: 0x23, expectedResponseId: 0x22 };
// Apply (应用): 主机发送 0x22 (Set Data), 从机应答 0xE5 (ACK)
const CMD_SET_TQCS = { stationAddr: 0, telegramNr: 0x22, expectedResponseId: 0xE5 };

export default {
  name: 'TqcsView',
  props: {
    /**
     * @vuese
     * 串口发送函数，由父组件 App.vue 提供。
     * @param {Object} cmdObj - 包含 commandDef 和 payload 的对象
     */
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    /**
     * @vuese
     * 原始报文数据 prop。
     * 当 App.vue 的串口监听器捕获到 expectedResponseId (0x22) 时，
     * 会将去掉报头的数据通过此 prop 传递给本组件。
     */
    tqcsRawData: { type: Array, default: null },
  },
  data() {
    return {
      // 'form' 对象用于存储所有 UI 控件的状态。
      // 结构参考了 C++ 头文件 Dlg_TQCS1.h 中的成员变量定义。
      form: {
        // --- 顶部控件状态 ---
        m_funcEnabled: true,      // 功能启用/禁用 (对应 byte offset 36)
        m_routineSelect: 1,       // 并网方式: 0=自动, 1=手动 (注意：协议中 1=自动, 0=手动)
        m_syncStyle: 0,           // 同步方式: 0=异步, 1=同期
        m_l1DeadVoltCheck: false, // 无压选择 L1
        m_l2DeadVoltCheck: false, // 无压选择 L2
        m_allDeadVoltCheck: false,// 无压选择 全部
        m_phaseSelect: 0,         // U相位: 0=A相, 1=B相, 2=C相

        // --- 详细参数 (左侧栏) ---
        // 'key' 用于关联 C++ 变量名，'unit' 为显示单位
        // 数值通过 float -> short 的倍率转换进行传输
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
        // --- 详细参数 (右侧栏) ---
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
     * 核心数据流入口。
     * 监听 `tqcsRawData` prop。当用户点击“读取”后，App.vue 收到数据并更新此 prop。
     * 此处检测到变化后，调用 `parseDataFromBuffer` 将二进制数据映射到 UI。
     */
    tqcsRawData(newData) {
      if (newData && newData.length > 0) {
        console.log("TqcsView received tqcsRawData:", newData);
        this.parseDataFromBuffer(newData);
      }
    }
  },
  created() {
    // 组件初始化时，加载默认值，确保 UI 不为空
    this.setDefaultValues();
  },
  methods: {
    // --- 核心通信方法 ---

    /**
     * @vuese
     * "应用" 按钮处理：打包 -> 发送。
     * 发送 CMD_SET_TQCS (0x22) 命令，将当前 UI 设置写入设备。
     */
    async onApply() {
      this.$message.info('正在打包并应用参数...');

      // 1. 将 UI 数据打包为字节数组 (Payload)
      const payload = this.packDataToBuffer();
      if (!payload) {
        return; // 打包失败（通常不应发生）
      }

      console.log("Applying TQCS data (payload length " + payload.length + "):", payload);

      // 2. 调用父组件接口发送命令
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
     * "读取" 按钮处理：发送请求。
     * 发送 CMD_REQ_TQCS (0x23)。注意：此函数不直接返回数据。
     * 数据通过异步响应返回，并触发 `watch: tqcsRawData`。
     */
    async onFetch() {
      this.$message.info('正在读取参数 (0x23)...');
      try {
        await this.sendCommand({ commandDef: CMD_REQ_TQCS });
        // 成功后的解析逻辑在 parseDataFromBuffer 中处理
      } catch (error) {
        console.error('读取 TQCS 参数失败:', error);
        this.$message.error(`读取参数失败: ${error?.message || error}`);
      }
    },

    // --- C++ 逻辑移植区域 ---

    /**
     * @vuese
     * 恢复默认值。
     * 仅重置界面显示，不立即写入设备。
     * 数值来源：Dlg_TQCS1.cpp::setDefaultValues
     */
    onDefault() {
      this.setDefaultValues();
      this.$message.warning('参数已在本地恢复为默认值 (未应用到设备)');
    },

    /**
     * @vuese
     * 取消操作。
     */
    onCancel() {
      this.$message.info('操作已取消');
    },

    /**
     * @vuese
     * 设置所有表单项为 C++ 代码中定义的硬编码默认值。
     */
    setDefaultValues() {
      // --- 重置控制位 ---
      this.form.m_funcEnabled = true;
      this.form.m_routineSelect = 1; // UI: 手动
      this.form.m_syncStyle = 0;     // 异步
      this.form.m_l1DeadVoltCheck = false;
      this.form.m_l2DeadVoltCheck = false;
      this.form.m_allDeadVoltCheck = false;
      this.form.m_phaseSelect = 0;   // A相

      // --- 重置数值参数 ---
      // 注意：此处直接设置的是物理值 (浮点/整数)，而非协议传输值
      this.form.paramsLeft.t_cb.value = 80;
      this.form.paramsLeft.d_amax.value = 10.0;
      this.form.paramsLeft.d_usync.value = 2.0;
      this.form.paramsLeft.d_uasync.value = 2.0;
      this.form.paramsLeft.d_fsync.value = 20.0;
      this.form.paramsLeft.d_fasync.value = 0.1;
      this.form.paramsLeft.umin.value = 52.0;
      this.form.paramsLeft.umax.value = 63.5;

      this.form.paramsRight.udead.value = 2.0;
      this.form.paramsRight.tr_u1_u2.value = 0.0;
      this.form.paramsRight.df_dt_max.value = 0.2;
      this.form.paramsRight.fmin.value = 47.5;
      this.form.paramsRight.fmax.value = 52.5;
      this.form.paramsRight.t_syn_duration.value = 30.0;
      this.form.paramsRight.t_synchron.value = 0.5;
      this.form.paramsRight.df1_f2_dt.value = 0.2;

      console.log("TqcsView form reset to C++ defaults.");
    },

    /**
     * @vuese
     * [关键解析逻辑]
     * 将串口返回的字节流 (Buffer) 解析为 UI 对象。
     * * 映射关系说明:
     * C++ `ValidData` 数组包含了报头信息，而此处的 `buffer` 是纯数据 Payload。
     * C++ ValidData[4] 对应 JS buffer[0]。
     * * @param {number[]} buffer - 0x22 响应报文的 Payload 部分
     */
    parseDataFromBuffer(buffer) {
      // 校验长度：C++ 代码读取至 ValidData[40] (即 payload[36])
      if (!buffer || buffer.length < 37) {
        console.warn("TQCS parse failed: buffer is null or too short.", buffer);
        this.$message.error('读取参数失败：设备响应数据格式不正确');
        return;
      }
      try {
        // --- 1. 解析状态位 ---
        // m_routineSelect: 协议中 1=自动, 0=手动。 UI中 0=自动, 1=手动。
        // 故 buffer[0] 为真(1)时，UI设为0; 否则设为1。
        this.form.m_routineSelect = buffer[0] ? 0 : 1;
        this.form.m_syncStyle = buffer[1];
        // 将 0/1 转换为 Boolean 给 Checkbox 使用
        this.form.m_l1DeadVoltCheck = !!buffer[2];
        this.form.m_l2DeadVoltCheck = !!buffer[3];
        this.form.m_allDeadVoltCheck = !!buffer[4];
        this.form.m_phaseSelect = buffer[5];

        // --- 2. 解析数值参数 ---
        // 定义解析规则表
        // key: C++变量名
        // offset: buffer中的起始字节索引 (对应 C++ ValidData索引 - 4)
        // div: 除数 (用于将传输的整数还原为浮点数)
        const parseMap = {
          'm_tcb': { offset: 6, div: 1 },         // ms
          'm_damax': { offset: 8, div: 100.0 },   // 角度
          'm_duMax': { offset: 10, div: 100.0 },  // V
          'm_dfMax': { offset: 12, div: 1 },      // mHz (注意这里倍率是1)
          'm_dUmax2': { offset: 14, div: 100.0 }, // V
          'm_dFmax2': { offset: 16, div: 100.0 }, // Hz
          'm_uDead': { offset: 18, div: 100.0 },  // V
          'm_trU1U2': { offset: 20, div: 100.0 }, // 角度
          'm_dfptMax': { offset: 22, div: 100.0 }, // Hz/s
          'm_uMin': { offset: 24, div: 100.0 },   // V
          'm_uMax': { offset: 26, div: 100.0 },   // V
          'm_fMin': { offset: 28, div: 100.0 },   // Hz
          'm_fMax': { offset: 30, div: 100.0 },   // Hz
          'm_tsynDuration': { offset: 32, div: 10.0 }, // s (注意倍率是10)
          'm_synchron': { offset: 34, div: 10.0 },     // s
        };

        // 遍历并执行解析
        const parseParam = (param) => {
          const info = parseMap[param.key];
          if (info) {
            // 读取 Short (16位) -> 除以系数 -> 赋值
            param.value = this.readShort(buffer, info.offset) / info.div;
          }
        };

        Object.values(this.form.paramsLeft).forEach(parseParam);
        Object.values(this.form.paramsRight).forEach(parseParam);

        // 特殊处理: m_synchron2 实际上就是 m_dfptMax 的值
        this.form.paramsRight.df1_f2_dt.value = this.form.paramsRight.df_dt_max.value;

        // --- 3. 解析全局启用开关 ---
        // 位于 Buffer 结尾 (offset 36)
        this.form.m_funcEnabled = !!buffer[36];

        this.$message.success('参数已从设备更新');

      } catch (e) {
        console.error("解析 TQCS 数据失败:", e);
        this.$message.error(`解析参数失败: ${e.message}`);
      }
    },

    /**
     * @vuese
     * [关键打包逻辑]
     * 将 UI 数据打包为二进制 Payload。
     * * [重要] 关于缓冲区长度的说明:
     * 原 C++ 代码 (TeleProcess.cpp) 存在 Bug，定义了 41 字节数组但只发送了 40 字节。
     * 为了保证与下位机的绝对兼容，此处严格模拟该行为，只生成 40 字节数据。
     * * @returns {Uint8Array} 40字节的二进制数据
     */
    packDataToBuffer() {
      // 创建 40 字节缓冲区 (模拟 C++ bug 行为)
      const buffer = new Uint8Array(40);

      try {
        // --- 1. 写入控制位 ---
        // 逻辑反转：UI(0=Auto) -> 协议(1=Auto)
        buffer[0] = this.form.m_routineSelect === 0 ? 1 : 0;
        buffer[1] = this.form.m_syncStyle;
        buffer[2] = this.form.m_l1DeadVoltCheck ? 1 : 0;
        buffer[3] = this.form.m_l2DeadVoltCheck ? 1 : 0;
        buffer[4] = this.form.m_allDeadVoltCheck ? 1 : 0;
        buffer[5] = this.form.m_phaseSelect;

        // --- 2. 写入数值参数 ---
        // 定义偏移量映射表 (Offset Map)
        const offsetMap = {
          'm_tcb': 6, 'm_damax': 8, 'm_duMax': 10, 'm_dfMax': 12, 'm_dUmax2': 14,
          'm_dFmax2': 16, 'm_uDead': 18, 'm_trU1U2': 20, 'm_dfptMax': 22, 'm_uMin': 24,
          'm_uMax': 26, 'm_fMin': 28, 'm_fMax': 30, 'm_tsynDuration': 32, 'm_synchron': 34
        };

        // 定义乘数映射表 (Multiplier Map) - 将浮点数转为整数传输
        const multiplierMap = {
          'm_damax': 100, 'm_duMax': 100, 'm_dUmax2': 100, 'm_dFmax2': 100, 'm_uDead': 100,
          'm_trU1U2': 100, 'm_dfptMax': 100, 'm_uMin': 100, 'm_uMax': 100, 'm_fMin': 100,
          'm_fMax': 100, 'm_tsynDuration': 10, 'm_synchron': 10
        };

        const packParam = (param) => {
          const offset = offsetMap[param.key];
          if (offset === undefined) return; // 跳过未映射的字段

          const multiplier = multiplierMap[param.key] || 1; // 默认为 1
          const value = parseFloat(param.value) || 0;

          // 核心转换：浮点 -> 乘系数 -> 四舍五入 -> 写入Short
          this.writeShort(buffer, offset, Math.round(value * multiplier));
        };

        Object.values(this.form.paramsLeft).forEach(packParam);
        Object.values(this.form.paramsRight).forEach(packParam);

        // --- 3. 写入启用标志 ---
        buffer[36] = this.form.m_funcEnabled ? 1 : 0;

        // 索引 37-39 自动填充为 0，总长度维持在 40

        return buffer;

      } catch (e) {
        console.error("打包 TQCS 数据失败:", e);
        this.$message.error(`打包参数失败: ${e.message}`);
        return null;
      }
    },

    // --- 辅助函数 ---

    /**
     * @vuese
     * UI 交互占位符。
     * C++ 中用于启用/禁用控件，Vue 中通过 :disabled 属性自动处理。
     */
    onControlStateChanged() {
      // UI 状态由 Vue 响应式系统自动处理，此处仅留作钩子
      console.log("Control state changed. UI bindings will update automatically.");
    },

    /**
     * @vuese
     * 读取 16 位小端整数 (Little-Endian unsigned short)。
     * 低地址存放低字节，高地址存放高字节。
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Read short: offset ${offset} out of bounds for buffer length ${buffer.length}`);
      }
      return buffer[offset] | (buffer[offset + 1] << 8);
    },

    /**
     * @vuese
     * 写入 16 位小端整数。
     * 将 value 拆分为高低字节写入 buffer。
     */
    writeShort(buffer, offset, value) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Write short: offset ${offset} out of bounds for buffer length ${buffer.length}`);
      }
      buffer[offset] = value & 0xFF;            // 低 8 位
      buffer[offset + 1] = (value >> 8) & 0xFF; // 高 8 位
    },
  },
};
</script>

<style scoped>
/* 样式部分保持不变 */
.tqcs-view { padding: 20px; background-color: #f0f2f5; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.top-settings-form { background-color: #fafafa; padding: 15px 20px 5px; border-radius: 4px; margin-bottom: 20px; }
.params-form ::v-deep(.el-input-group__append) {
  width: 70px;
  text-align: center;
}
.view-footer { display: flex; justify-content: flex-end; width: 100%; margin-top: 20px; padding-top: 20px; border-top: 1px solid #e4e7ed; }
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
.el-row.is-disabled {
  opacity: 0.6;
  pointer-events: none;
}
.checkbox-group-container.is-disabled {
  opacity: 0.6;
  pointer-events: none;
}
</style>