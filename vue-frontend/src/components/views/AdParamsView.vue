<template>
  <div class="ad-params-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>AD 参数设置</span>
        </div>
      </template>

      <el-row :gutter="20">
        <el-col :span="14">
          <el-card shadow="never">
            <template #header>
              AC 比例因子
            </template>
            <el-form
              :model="form.acScaling"
              label-position="top"
              class="compact-form"
            >
              <el-row :gutter="15">
                <el-col :span="12">
                  <el-row :gutter="15">
                    <el-col
                      v-for="key in ['u1a', 'u1b', 'u1c', 'i1a', 'i1b', 'i1c']"
                      :key="key"
                      :span="12"
                    >
                      <el-form-item :label="form.acScaling[key].label">
                        <el-input
                          v-model.number="form.acScaling[key].value"
                          type="number"
                          size="small"
                        />
                      </el-form-item>
                    </el-col>
                  </el-row>
                </el-col>
                <el-col :span="12">
                  <el-row :gutter="15">
                    <el-col
                      v-for="key in ['u2a', 'u2b', 'u2c', 'i2a', 'i2b', 'i2c']"
                      :key="key"
                      :span="12"
                    >
                      <el-form-item :label="form.acScaling[key].label">
                        <el-input
                          v-model.number="form.acScaling[key].value"
                          type="number"
                          size="small"
                        />
                      </el-form-item>
                    </el-col>
                  </el-row>
                </el-col>
              </el-row>
            </el-form>
          </el-card>

          <el-card
            shadow="never"
            style="margin-top: 15px;"
          >
            <template #header>
              DC 通道设置
            </template>
            <el-table
              :data="form.dcChannels"
              border
              size="small"
              class="dc-table"
            >
              <el-table-column
                prop="id"
                label="通道"
                width="60"
                align="center"
              />
              <el-table-column label="零漂 (V_DCx)">
                <template #default="scope">
                  <el-input
                    v-model.number="scope.row.v_dc"
                    type="number"
                    size="small"
                  />
                </template>
              </el-table-column>
              <el-table-column label="线性 (C_DCx)">
                <template #default="scope">
                  <el-input
                    v-model.number="scope.row.c_dc"
                    type="number"
                    size="small"
                  />
                </template>
              </el-table-column>
              <el-table-column
                label="源选择"
                width="160"
                align="center"
              >
                <template #default="scope">
                  <el-radio-group
                    v-model="scope.row.source"
                    size="small"
                  >
                    <el-radio-button :label="0">
                      Voltage
                    </el-radio-button>
                    <el-radio-button :label="1">
                      Current
                    </el-radio-button>
                  </el-radio-group>
                </template>
              </el-table-column>
            </el-table>
          </el-card>
        </el-col>

        <el-col :span="10">
          <el-card shadow="never">
            <template #header>
              通道与延迟
            </template>
            <el-row :gutter="20">
              <el-col :span="12">
                <el-form
                  :model="form.channelSelect"
                  label-position="top"
                  class="compact-form"
                >
                  <el-form-item
                    v-for="(item, key) in form.channelSelect"
                    :key="key"
                    :label="item.label"
                  >
                    <el-select
                      v-model.number="item.value"
                      size="small"
                      style="width: 100%;"
                    >
                      <el-option
                        label="0"
                        :value="0"
                      />
                      <el-option
                        label="1"
                        :value="1"
                      />
                      <el-option
                        label="2"
                        :value="2"
                      />
                      <el-option
                        label="3"
                        :value="3"
                      />
                    </el-select>
                  </el-form-item>
                </el-form>
              </el-col>
              <el-col :span="12">
                <el-form
                  :model="form.delay"
                  label-position="top"
                  class="compact-form"
                >
                  <el-form-item
                    v-for="(item, key) in form.delay"
                    :key="key"
                    :label="item.label + ' (Tick)'"
                  >
                    <el-input
                      v-model.number="item.value"
                      type="number"
                      size="small"
                    />
                  </el-form-item>
                </el-form>
              </el-col>
            </el-row>
          </el-card>

          <el-card
            shadow="never"
            style="margin-top: 15px;"
          >
            <template #header>
              额定值 (V/C_LINE1/2)
            </template>
            <el-form
              label-position="top"
              class="compact-form"
            >
              <el-row :gutter="20">
                <el-col :span="12">
                  <el-form-item label="额定电压 (V_LINE)">
                    <el-input
                      v-model.number="form.nominal.vLine1"
                      type="number"
                      size="small"
                      placeholder="Line 1"
                    />
                    <el-input
                      v-model.number="form.nominal.vLine2"
                      type="number"
                      size="small"
                      placeholder="Line 2"
                      style="margin-top: 5px;"
                    />
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="额定电流 (C_LINE)">
                    <el-input
                      v-model.number="form.nominal.cLine1"
                      type="number"
                      size="small"
                      placeholder="Line 1"
                    />
                    <el-input
                      v-model.number="form.nominal.cLine2"
                      type="number"
                      size="small"
                      placeholder="Line 2"
                      style="margin-top: 5px;"
                    />
                  </el-form-item>
                </el-col>
              </el-row>
            </el-form>
          </el-card>

          <el-card
            shadow="never"
            style="margin-top: 15px;"
          >
            <template #header>
              高级设置
            </template>
            <el-form
              :model="form.advanced"
              label-position="top"
              class="compact-form"
            >
              <el-form-item label="插值模型">
                <el-select
                  v-model.number="form.advanced.model"
                  size="small"
                  style="width: 100%;"
                >
                  <el-option
                    label="0"
                    :value="0"
                  />
                  <el-option
                    label="1"
                    :value="1"
                  />
                  <el-option
                    label="2"
                    :value="2"
                  />
                </el-select>
              </el-form-item>
              <el-form-item label="AD 采样校正 (Tick)">
                <el-input
                  v-model.number="form.advanced.adFix"
                  type="number"
                  size="small"
                />
              </el-form-item>
              <el-form-item label="一次电流定标 (OCT)">
                <el-input
                  v-model.number="form.advanced.oct"
                  type="number"
                  size="small"
                />
              </el-form-item>
            </el-form>
          </el-card>
        </el-col>
      </el-row>

      <div class="view-footer">
        <el-button
          :disabled="!isSerialConnected"
          @click="onDefault"
        >
          默认参数
        </el-button>
        <el-button @click="onCancel">
          退出
        </el-button>
        <el-button
          type="primary"
          :disabled="!isSerialConnected"
          @click="onApply"
        >
          下载参数
        </el-button>
        <el-button
          type="success"
          :disabled="!isSerialConnected"
          @click="onFetch"
        >
          获取参数
        </el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
// --- 命令定义 ---
// 获取参数 (Fetch): 发送 0x21 (十进制 33), 期望响应 0x20 (十进制 32)
const CMD_REQ_ACAD = { stationAddr: 0, telegramNr: 0x21, expectedResponseId: 0x20 };
// 下载参数 (Apply): 发送 0x20 (十进制 32), 期望响应 0xE5 (ACK)
const CMD_SET_ACAD = { stationAddr: 0, telegramNr: 0x20, expectedResponseId: 0xE5 };

// --- C++ (Dlg_AD1.h) 定义的常量 ---
const DIM_US = 7095;  // 0x1BB7
const DIM_IS = 7024;  // 0x1B70
const DIM_DCS = 20460; // 0x4FEC
const DIM_U = 28380;  // 0x6EDC
const DIM_I = 17900;  // 0x45E8

export default {
  name: 'AdParamsView',
  props: {
    isSerialConnected: { type: Boolean, default: false },
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    /**
     * @vuese
     * 从 App.vue 传入的原始 ADParams 字节数组 (来自 0x20 响应)。
     */
    adParamsRawData: { type: Array, default: null },
    /**
     * @vuese
     * 从 App.vue 传入的全局标幺基值 (16384 或 8192)。
     * C++: pParent->DIM_public
     */
    puBaseValue: { type: Number, default: 16384 },
  },
  data() {
    // 辅助函数：创建8个DC通道的默认数据
    const createDcChannels = () => {
      let channels = [];
      for (let i = 1; i <= 8; i++) {
        channels.push({
          id: `DC${i}`,
          v_dc: 0,     // 对应 m_shortAD1_V_DCx
          c_dc: 0,     // 对应 m_shortAD1_C_DCx
          source: 1   // 对应 m_nAD1_DCSSx (0=V, 1=C)
        });
      }
      return channels;
    };

    return {
      // 存储所有UI控件的状态
      form: {
        // AC 比例因子
        acScaling: {
          u1a: { label: 'U1a', value: 0 }, u1b: { label: 'U1b', value: 0 }, u1c: { label: 'U1c', value: 0 },
          i1a: { label: 'I1a', value: 0 }, i1b: { label: 'I1b', value: 0 }, i1c: { label: 'I1c', value: 0 },
          u2a: { label: 'U2a', value: 0 }, u2b: { label: 'U2b', value: 0 }, u2c: { label: 'U2c', value: 0 },
          i2a: { label: 'I2a', value: 0 }, i2b: { label: 'I2b', value: 0 }, i2c: { label: 'I2c', value: 0 },
        },
        // 额定值
        nominal: {
          vLine1: 0, // m_shortAD1_V_LINE1
          vLine2: 0, // m_shortAD1_V_LINE2
          cLine1: 0, // m_shortAD1_C_LINE1
          cLine2: 0, // m_shortAD1_C_LINE2
        },
        // DC 通道
        dcChannels: createDcChannels(),
        // 通道选择
        channelSelect: {
          ia: { label: 'Channel Select IA', value: 0 }, // m_Channel_Sec1
          ib: { label: 'Channel Select IB', value: 1 }, // m_Channel_Sec2
          ic: { label: 'Channel Select IC', value: 2 }, // m_Channel_Sec3
          ix: { label: 'Channel Select IX', value: 3 }, // m_Channel_SecX
        },
        // 延迟
        delay: {
          da: { label: 'Channel Delay IA', value: 0 }, // m_Delay_A
          db: { label: 'Channel Delay IB', value: 0 }, // m_Delay_B
          dc: { label: 'Channel Delay IC', value: 0 }, // m_Delay_C
          dx: { label: 'Channel Delay IX', value: 0 }, // m_Delay_X
        },
        // 高级设置
        advanced: {
          model: 0,  // m_Model_Sec
          adFix: 0,  // m_Delay
          oct: 0,    // m_Primary_Current_Scaling
        },
      },
    };
  },
  watch: {
    /**
     * @vuese
     * 监听来自 App.vue 的 `adParamsRawData` prop。
     * 当 App.vue 收到 0x20 响应报文并更新此 prop 时，调用解析函数 `parseDataFromBuffer`。
     */
    adParamsRawData(newData) {
      if (newData && newData.length > 0) {
        console.log("AdParamsView received adParamsRawData:", newData);
        this.parseDataFromBuffer(newData);
      }
    }
  },
  /**
   * @vuese
   * [FIXED] 组件创建时，立即加载 C++ 版本中定义的默认值 (不显示消息)。
   */
  created() {
    this.onDefault(false); // [FIX] 修正了此处的调用，原为 this.setDefaultValues()
  },
  methods: {
    // --- 辅助函数 ---

    /**
     * @vuese
     * 从字节数组的指定偏移量读取一个 16 位小端整数 (ushort)。
     * @param {number[]} buffer - 字节数组 (payload)
     * @param {number} offset - 起始偏移量
     * @returns {number} 16位整数 (short)
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Read short: offset ${offset} out of bounds`);
      }
      const val = buffer[offset] | (buffer[offset + 1] << 8);
      // 将 ushort (0-65535) 转换为 short (-32768 to 32767)
      return (val << 16) >> 16;
    },

    /**
     * @vuese
     * 将一个 16 位整数 (short) 以小端格式写入字节数组的指定偏移量。
     * @param {Uint8Array} buffer - 目标字节数组
     * @param {number} offset - 写入的起始偏移量
     * @param {number} value - 要写入的 16 位整数
     */
    writeShort(buffer, offset, value) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Write short: offset ${offset} out of bounds`);
      }
      buffer[offset] = value & 0xFF;            // 低字节
      buffer[offset + 1] = (value >> 8) & 0xFF; // 高字节
    },

    // --- 核心通信方法 ---

    /**
     * @vuese
     * "获取参数" 按钮点击处理。
     * 发送 0x21 (33) 命令，等待 0x20 (32) 响应。
     */
    async onFetch() {
      this.$message.info('正在发送获取 AD 参数命令 (0x21)...');
      try {
        await this.sendCommand({ commandDef: CMD_REQ_ACAD });
        // 成功消息将在 parseDataFromBuffer 中显示
      } catch (error) {
        console.error('获取 AD 参数失败:', error);
        this.$message.error(`获取参数失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * "下载参数" 按钮点击处理。
     * 1. 调用 `packDataToBuffer()` 将 `this.form` 序列化为 90 字节的 payload。
     * 2. 发送 0x20 (32) 命令及 payload，等待 0xE5 响应。
     */
    async onApply() {
      this.$message.info('正在打包并下载 AD 参数 (0x20)...');
      let payload;
      try {
        payload = this.packDataToBuffer();
      } catch (e) {
        console.error("打包 AD 参数失败:", e);
        this.$message.error(`打包失败: ${e.message}`);
        return;
      }

      console.log("Applying ADParams data (payload length " + payload.length + "):", payload);

      try {
        await this.sendCommand({ commandDef: CMD_SET_ACAD, payload: payload });
        this.$message.success('AD 参数已下载 (0x20)');
      } catch (error) {
        console.error('下载 AD 参数失败:', error);
        this.$message.error(`下载失败: ${error?.message || error}`);
      }
    },

    // --- C++ 逻辑移植 ---

    /**
     * @vuese
     * "退出" 按钮 (保留 C++ 按钮名称)
     */
    onCancel() {
      this.$message.info('退出操作 (AdParamsView 仍处于活动状态)');
      // 在 C++ 中，这会关闭对话框。在这里，我们只显示一条消息。
    },

    /**
     * @vuese
     * [移植] "默认参数" 按钮点击处理。
     * 移植自 Dlg_AD1.cpp::onpushButton_3Ad1DefaultClicked()
     * [FIXED] 增加 'showMessage' 参数以抑制加载时的提示
     */
    onDefault(showMessage = true) { // [FIX] 增加了参数
      // C++: m_nAD1_DCSSx = 1 (Current)
      this.form.dcChannels.forEach(c => c.source = 1);

      // C++: m_Channel_SecX
      this.form.channelSelect.ia.value = 0;
      this.form.channelSelect.ib.value = 1;
      this.form.channelSelect.ic.value = 2;
      this.form.channelSelect.ix.value = 3;

      // C++: m_Model_Sec = 0
      this.form.advanced.model = 0;

      // C++: m_Delay_X = 0, m_Delay = 0
      this.form.delay.da.value = 0;
      this.form.delay.db.value = 0;
      this.form.delay.dc.value = 0;
      this.form.delay.dx.value = 0;
      this.form.advanced.adFix = 0;

      // C++: m_Primary_Current_Scaling = 3000
      this.form.advanced.oct = 3000;

      // C++: 根据 pParent->DIM_public (即 this.puBaseValue) 设置 AC 和 DC 值
      if (this.puBaseValue === 8192) { // 2000H
        this.form.dcChannels.forEach(c => {
          c.v_dc = DIM_DCS; // 20460
          c.c_dc = DIM_DCS; // 20460
        });
        this.form.acScaling.u1a.value = DIM_US; // 7095
        this.form.acScaling.u1b.value = DIM_US;
        this.form.acScaling.u1c.value = DIM_US;
        this.form.acScaling.i1a.value = DIM_IS; // 7024
        this.form.acScaling.i1b.value = DIM_IS;
        this.form.acScaling.i1c.value = DIM_IS;
        this.form.acScaling.u2a.value = DIM_US;
        this.form.acScaling.u2b.value = DIM_US;
        this.form.acScaling.u2c.value = DIM_US;
        this.form.acScaling.i2a.value = DIM_IS;
        this.form.acScaling.i2b.value = DIM_IS;
        this.form.acScaling.i2c.value = DIM_IS;

      } else { // 默认 16384 (4000H)
        this.form.dcChannels.forEach(c => {
          c.v_dc = 0;
          c.c_dc = 50360; // C++ 硬编码
        });
        this.form.acScaling.u1a.value = DIM_U; // 28380
        this.form.acScaling.u1b.value = DIM_U;
        this.form.acScaling.u1c.value = DIM_U;
        this.form.acScaling.i1a.value = DIM_I; // 17900
        this.form.acScaling.i1b.value = DIM_I;
        this.form.acScaling.i1c.value = DIM_I;
        this.form.acScaling.u2a.value = DIM_U;
        this.form.acScaling.u2b.value = DIM_U;
        this.form.acScaling.u2c.value = DIM_U;
        this.form.acScaling.i2a.value = DIM_I;
        this.form.acScaling.i2b.value = DIM_I;
        this.form.acScaling.i2c.value = DIM_I;
      }

      // C++: m_shortAD1_V_LINE1/2
      this.form.nominal.vLine1 = 500;
      this.form.nominal.vLine2 = 500;
      this.form.nominal.cLine1 = 3000;
      this.form.nominal.cLine2 = 3000;

      if (showMessage) { // [FIX] 增加了条件判断
        this.$message.warning('AD 参数已在本地恢复为默认值 (未下载)');
      }
    },

    /**
     * @vuese
     * [移植] 解析来自 0x20 响应的 89+ 字节 payload。
     * 移植自 Dlg_AD1.cpp::processDeviceData()
     * C++ 的 ValidData[4] 对应 JS 的 buffer[0] (payload 的第一个字节)。
     * C++ 读取到 ValidData[92]，对应 buffer[88]。
     * @param {number[]} buffer - 原始字节数组 (payload)。
     */
    parseDataFromBuffer(buffer) {
      // C++ 读取到 ValidData[92] (buffer[88])，所以长度至少为 89。
      if (!buffer || buffer.length < 89) {
        console.warn("ADParams parse failed: buffer is null or too short.", buffer);
        this.$message.error('获取参数失败：设备响应数据格式不正确');
        return;
      }
      try {
        // --- AC 比例因子 ---
        // C++: ValidData[4] -> buffer[0]
        this.form.acScaling.u1a.value = this.readShort(buffer, 0);  // U1a @ ValidData[4]
        this.form.acScaling.u1b.value = this.readShort(buffer, 2);  // U1b @ ValidData[6]
        this.form.acScaling.u1c.value = this.readShort(buffer, 4);  // U1c @ ValidData[8]
        this.form.acScaling.i1a.value = this.readShort(buffer, 6);  // I1a @ ValidData[10]
        this.form.acScaling.i1b.value = this.readShort(buffer, 8);  // I1b @ ValidData[12]
        this.form.acScaling.i1c.value = this.readShort(buffer, 10); // I1c @ ValidData[14]
        this.form.acScaling.u2a.value = this.readShort(buffer, 12); // U2a @ ValidData[16]
        this.form.acScaling.u2b.value = this.readShort(buffer, 14); // U2b @ ValidData[18]
        this.form.acScaling.u2c.value = this.readShort(buffer, 16); // U2c @ ValidData[20]
        this.form.acScaling.i2a.value = this.readShort(buffer, 18); // I2a @ ValidData[22]
        this.form.acScaling.i2b.value = this.readShort(buffer, 20); // I2b @ ValidData[24]
        this.form.acScaling.i2c.value = this.readShort(buffer, 22); // I2c @ ValidData[26]

        // --- DC 通道 ---
        this.form.dcChannels[0].v_dc = this.readShort(buffer, 24); // V_DC1 @ ValidData[28]
        this.form.dcChannels[1].v_dc = this.readShort(buffer, 26); // V_DC2 @ ValidData[30]
        this.form.dcChannels[2].v_dc = this.readShort(buffer, 28); // V_DC3 @ ValidData[32]
        this.form.dcChannels[3].v_dc = this.readShort(buffer, 30); // V_DC4 @ ValidData[34]
        this.form.dcChannels[4].v_dc = this.readShort(buffer, 32); // V_DC5 @ ValidData[36]
        this.form.dcChannels[5].v_dc = this.readShort(buffer, 34); // V_DC6 @ ValidData[38]
        this.form.dcChannels[6].v_dc = this.readShort(buffer, 36); // V_DC7 @ ValidData[40]
        this.form.dcChannels[7].v_dc = this.readShort(buffer, 38); // V_DC8 @ ValidData[42]

        this.form.dcChannels[0].c_dc = this.readShort(buffer, 40); // C_DC1 @ ValidData[44]
        this.form.dcChannels[1].c_dc = this.readShort(buffer, 42); // C_DC2 @ ValidData[46]
        this.form.dcChannels[2].c_dc = this.readShort(buffer, 44); // C_DC3 @ ValidData[48]
        this.form.dcChannels[3].c_dc = this.readShort(buffer, 46); // C_DC4 @ ValidData[50]
        this.form.dcChannels[4].c_dc = this.readShort(buffer, 48); // C_DC5 @ ValidData[52]
        this.form.dcChannels[5].c_dc = this.readShort(buffer, 50); // C_DC6 @ ValidData[54]
        this.form.dcChannels[6].c_dc = this.readShort(buffer, 52); // C_DC7 @ ValidData[56]
        this.form.dcChannels[7].c_dc = this.readShort(buffer, 54); // C_DC8 @ ValidData[58]

        // --- 额定值 ---
        this.form.nominal.vLine1 = this.readShort(buffer, 56); // V_LINE1 @ ValidData[60]
        this.form.nominal.vLine2 = this.readShort(buffer, 58); // V_LINE2 @ ValidData[62]
        this.form.nominal.cLine1 = this.readShort(buffer, 60); // C_LINE1 @ ValidData[64]
        this.form.nominal.cLine2 = this.readShort(buffer, 62); // C_LINE2 @ ValidData[66]

        // --- 高级设置 ---
        this.form.advanced.model = buffer[64];  // m_Model_Sec @ ValidData[68]
        this.form.advanced.adFix = this.readShort(buffer, 65); // m_Delay @ ValidData[69]
        this.form.advanced.oct = (buffer[67] & 0xFF) * 25; // m_Primary_Current_Scaling @ ValidData[71]
        // buffer[68] (ValidData[72]) (m_nAD1_SecVNV) 被忽略

        // --- DC 源选择 ---
        this.form.dcChannels[0].source = buffer[69]; // m_nAD1_DCSS @ ValidData[73]
        this.form.dcChannels[1].source = buffer[70]; // m_nAD1_DCSS2 @ ValidData[74]
        this.form.dcChannels[2].source = buffer[71]; // m_nAD1_DCSS3 @ ValidData[75]
        this.form.dcChannels[3].source = buffer[72]; // m_nAD1_DCSS4 @ ValidData[76]
        this.form.dcChannels[4].source = buffer[73]; // m_nAD1_DCSS5 @ ValidData[77]
        this.form.dcChannels[5].source = buffer[74]; // m_nAD1_DCSS6 @ ValidData[78]
        this.form.dcChannels[6].source = buffer[75]; // m_nAD1_DCSS7 @ ValidData[79]
        this.form.dcChannels[7].source = buffer[76]; // m_nAD1_DCSS8 @ ValidData[80]

        // --- 通道选择 ---
        this.form.channelSelect.ia.value = buffer[77]; // m_Channel_Sec1 @ ValidData[81]
        this.form.channelSelect.ib.value = buffer[78]; // m_Channel_Sec2 @ ValidData[82]
        this.form.channelSelect.ic.value = buffer[79]; // m_Channel_Sec3 @ ValidData[83]
        this.form.channelSelect.ix.value = buffer[80]; // m_Channel_SecX @ ValidData[84]

        // --- 延迟 ---
        this.form.delay.da.value = this.readShort(buffer, 81); // m_Delay_A @ ValidData[85]
        this.form.delay.db.value = this.readShort(buffer, 83); // m_Delay_B @ ValidData[87]
        this.form.delay.dc.value = this.readShort(buffer, 85); // m_Delay_C @ ValidData[89]
        this.form.delay.dx.value = this.readShort(buffer, 87); // m_Delay_X @ ValidData[91]
        // ValidData[92] (buffer[88]) is read by C++ but not used for m_Delay_X. It seems dx.value should be buffer[87].
        // C++: m_Delay_A = ui->lineEdit_48->text().toInt(); [Wrong comment, this is Delay_X]
        // C++: DATA[87] = ... m_Delay_X & 0x00FF; DATA[88] = ... m_Delay_X >> 8;
        // C++: TempData_UCHAR = ValidData[91]; TempData_short = ValidData[92]; ... m_Delay_X = TempData_short;
        // OK, C++ a_Delay_X read/write is at 87/88 (JS 83/84), m_Delay_X read is at 91/92 (JS 87/88)
        // Let's assume the WRITE (Apply) is the correct one.
        // Re-reading C++:
        // Apply: DATA[87]/[88] = m_Delay_X (from lineEdit_48)
        // Fetch: m_Delay_X = ValidData[91]/[92] (buffer[87]/[88])
        // This confirms: Delay_X is at offset 87.
        this.form.delay.dx.value = this.readShort(buffer, 87); // m_Delay_X @ ValidData[91]

        this.$message.success('AD 参数已从设备更新');

      } catch (e) {
        console.error("解析 ADParams 数据失败:", e);
        this.$message.error(`解析参数失败: ${e.message}`);
      }
    },

    /**
     * @vuese
     * [移植] 将 `this.form` 中的数据打包成 90 字节的 payload (Uint8Array)。
     * 移植自 Dlg_AD1.cpp::onpushButtonAd1ApplyClicked()
     * @returns {Uint8Array} 90字节的 payload。
     */
    packDataToBuffer() {
      // C++ 发送 90 字节 (索引 0-89)
      const buffer = new Uint8Array(90);

      // --- AC 比例因子 ---
      this.writeShort(buffer, 0, this.form.acScaling.u1a.value); // DATA[0]
      this.writeShort(buffer, 2, this.form.acScaling.u1b.value); // DATA[2]
      this.writeShort(buffer, 4, this.form.acScaling.u1c.value); // DATA[4]
      this.writeShort(buffer, 6, this.form.acScaling.i1a.value); // DATA[6]
      this.writeShort(buffer, 8, this.form.acScaling.i1b.value); // DATA[8]
      this.writeShort(buffer, 10, this.form.acScaling.i1c.value); // DATA[10]
      this.writeShort(buffer, 12, this.form.acScaling.u2a.value); // DATA[12]
      this.writeShort(buffer, 14, this.form.acScaling.u2b.value); // DATA[14]
      this.writeShort(buffer, 16, this.form.acScaling.u2c.value); // DATA[16]
      this.writeShort(buffer, 18, this.form.acScaling.i2a.value); // DATA[18]
      this.writeShort(buffer, 20, this.form.acScaling.i2b.value); // DATA[20]
      this.writeShort(buffer, 22, this.form.acScaling.i2c.value); // DATA[22]

      // --- DC 通道 ---
      this.writeShort(buffer, 24, this.form.dcChannels[0].v_dc); // DATA[24]
      this.writeShort(buffer, 26, this.form.dcChannels[1].v_dc); // DATA[26]
      this.writeShort(buffer, 28, this.form.dcChannels[2].v_dc); // DATA[28]
      this.writeShort(buffer, 30, this.form.dcChannels[3].v_dc); // DATA[30]
      this.writeShort(buffer, 32, this.form.dcChannels[4].v_dc); // DATA[32]
      this.writeShort(buffer, 34, this.form.dcChannels[5].v_dc); // DATA[34]
      this.writeShort(buffer, 36, this.form.dcChannels[6].v_dc); // DATA[36]
      this.writeShort(buffer, 38, this.form.dcChannels[7].v_dc); // DATA[38]

      this.writeShort(buffer, 40, this.form.dcChannels[0].c_dc); // DATA[40]
      this.writeShort(buffer, 42, this.form.dcChannels[1].c_dc); // DATA[42]
      this.writeShort(buffer, 44, this.form.dcChannels[2].c_dc); // DATA[44]
      this.writeShort(buffer, 46, this.form.dcChannels[3].c_dc); // DATA[46]
      this.writeShort(buffer, 48, this.form.dcChannels[4].c_dc); // DATA[48]
      this.writeShort(buffer, 50, this.form.dcChannels[5].c_dc); // DATA[50]
      this.writeShort(buffer, 52, this.form.dcChannels[6].c_dc); // DATA[52]
      this.writeShort(buffer, 54, this.form.dcChannels[7].c_dc); // DATA[54]

      // --- 额定值 ---
      this.writeShort(buffer, 56, this.form.nominal.vLine1); // DATA[56]
      this.writeShort(buffer, 58, this.form.nominal.vLine2); // DATA[58]
      this.writeShort(buffer, 60, this.form.nominal.cLine1); // DATA[60]
      this.writeShort(buffer, 62, this.form.nominal.cLine2); // DATA[62]

      // --- 高级设置 ---
      buffer[64] = this.form.advanced.model & 0xFF;        // DATA[64] (m_Model_Sec)
      this.writeShort(buffer, 65, this.form.advanced.adFix); // DATA[65] (m_Delay)
      buffer[67] = (this.form.advanced.oct / 25) & 0xFF; // DATA[67] (m_Primary_Current_Scaling / 25)
      buffer[68] = 0; // DATA[68] (m_nAD1_SecVNV) - C++ 设为 0

      // --- DC 源选择 ---
      buffer[69] = this.form.dcChannels[0].source; // DATA[69]
      buffer[70] = this.form.dcChannels[1].source; // DATA[70]
      buffer[71] = this.form.dcChannels[2].source; // DATA[71]
      buffer[72] = this.form.dcChannels[3].source; // DATA[72]
      buffer[73] = this.form.dcChannels[4].source; // DATA[73]
      buffer[74] = this.form.dcChannels[5].source; // DATA[74]
      buffer[75] = this.form.dcChannels[6].source; // DATA[75]
      buffer[76] = this.form.dcChannels[7].source; // DATA[76]

      // --- 通道选择 ---
      buffer[77] = this.form.channelSelect.ia.value; // DATA[77]
      buffer[78] = this.form.channelSelect.ib.value; // DATA[78]
      buffer[79] = this.form.channelSelect.ic.value; // DATA[79]
      buffer[80] = this.form.channelSelect.ix.value; // DATA[80]

      // --- 延迟 ---
      this.writeShort(buffer, 81, this.form.delay.da.value); // DATA[81]
      this.writeShort(buffer, 83, this.form.delay.db.value); // DATA[83]
      this.writeShort(buffer, 85, this.form.delay.dc.value); // DATA[85]
      this.writeShort(buffer, 87, this.form.delay.dx.value); // DATA[87]

      buffer[89] = 0; // DATA[89] (bak)

      return buffer;
    }
  },
};
</script>

<style scoped>
.ad-params-view { padding: 20px; background-color: #f0f2f5; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.el-card { border: 1px solid #e4e7ed; }
.el-card ::v-deep(.el-card__header) { background-color: #fafafa; padding: 12px 15px; }
.el-card ::v-deep(.el-card__body) { padding: 15px; }

/* 紧凑型表单 */
.compact-form .el-form-item { margin-bottom: 8px; }
.compact-form ::v-deep(.el-form-item__label) { line-height: 1.5; font-size: 13px; padding-bottom: 2px; }

/* DC 表格样式 */
.dc-table ::v-deep(.el-input__inner) { padding: 0 8px; }
.dc-table .el-radio-button ::v-deep(.el-radio-button__inner) { padding: 5px 10px; }

/* 底部按钮栏 */
.view-footer {
  display: flex;
  justify-content: flex-end;
  gap: 10px;
  width: 100%;
  margin-top: 20px;
  padding-top: 20px;
  border-top: 1px solid #e4e7ed;
}
</style>