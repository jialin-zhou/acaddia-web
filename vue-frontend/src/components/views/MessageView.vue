<template>
  <div class="message-view">
    <el-row :gutter="20">
      <el-col :span="8">
        <el-card class="box-card">
          <template #header>
            额定参数 & 控制字
          </template>

          <el-form
            :model="message.control"
            label-position="left"
            label-width="100px"
            class="compact-form"
          >
            <el-form-item label="Lenth">
              <el-input v-model="message.control.Lenth" />
            </el-form-item>
            <el-form-item label="LNName">
              <el-input v-model="message.control.LNName" />
            </el-form-item>
            <el-form-item label="DataSetName">
              <el-input v-model="message.control.DataSetName" />
            </el-form-item>
            <el-form-item label="LDName">
              <el-input v-model="message.control.LDName" />
            </el-form-item>
            <el-form-item label="SmpCtr">
              <el-input v-model="message.control.SmpCtr" />
            </el-form-item>
          </el-form>

          <el-divider />

          <el-form
            :model="message.rated"
            label-position="left"
            label-width="100px"
            class="compact-form"
          >
            <el-form-item label="PhsA.Artg">
              <el-input v-model="message.rated['PhsA.Artg']" />
            </el-form-item>
            <el-form-item label="PhsA.Vrtg">
              <el-input v-model="message.rated['PhsA.Vrtg']" />
            </el-form-item>
            <el-form-item label="Neut.Artg">
              <el-input v-model="message.rated['Neut.Artg']" />
            </el-form-item>
            <el-form-item label="tdr">
              <el-input v-model="message.rated.tdr" />
            </el-form-item>
          </el-form>
        </el-card>
      </el-col>

      <el-col :span="8">
        <el-card
          class="box-card"
          header="状态字"
        >
          <el-form
            :model="message.status"
            label-position="left"
            label-width="120px"
            class="compact-form"
          >
            <el-form-item label="Status Word 1">
              <el-input v-model="message.status.word1" />
            </el-form-item>
            <el-form-item label="Status Word 2">
              <el-input v-model="message.status.word2" />
            </el-form-item>
          </el-form>

          <div class="status-flags">
            <el-checkbox
              v-for="(val, key) in message.status.flags"
              :key="key"
              :model-value="val"
              :label="key"
              disabled
            />
          </div>
        </el-card>
      </el-col>

      <el-col :span="8">
        <el-card
          class="box-card"
          header="通道数据"
        >
          <div class="display-mode-toggle">
            <el-radio-group v-model="displayMode">
              <el-radio-button label="HEX">
                HEX
              </el-radio-button>
              <el-radio-button label="DEC">
                DEC
              </el-radio-button>
            </el-radio-group>
          </div>

          <el-scrollbar class="channel-form-scrollbar">
            <el-form
              :model="message.channels"
              label-position="left"
              label-width="60px"
              class="compact-form channel-form"
            >
              <el-row :gutter="10">
                <el-col
                  v-for="i in 22"
                  :key="i"
                  :span="12"
                >
                  <el-form-item :label="`Ch ${i}`">
                    <el-input v-model="message.channels[`ch${i}`]" />
                  </el-form-item>
                </el-col>
              </el-row>
            </el-form>
          </el-scrollbar>

          <div class="card-footer">
            <el-button
              type="primary"
              :disabled="!isSerialConnected"
              @click="onFetch"
            >
              获取
            </el-button>
          </div>
        </el-card>
      </el-col>
    </el-row>
  </div>
</template>

<script>
// 对应 C++ 原型: Dlg_Message::OnBUTTONMessageFetch() -> 发送命令 49 (0x31)
// 0x31 为请求报文命令，0x32 为预期的响应报文 ID
const CMD_REQ_MESSAGE = { stationAddr: 0, telegramNr: 0x31, expectedResponseId: 0x32 };

/**
 * 辅助函数：创建 22 个通道的初始数据对象
 * 初始化为字符串 '0'
 */
function createChannelData() {
  const channels = {};
  for (let i = 1; i <= 22; i++) {
    channels[`ch${i}`] = '0';
  }
  return channels;
}

export default {
  name: 'MessageView',
  props: {
    // 串口连接状态，用于控制按钮禁用
    isSerialConnected: { type: Boolean, default: false },
    // 父组件传入的发送命令函数，返回 Promise
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    // 串口接收到的原始字节数据 (Array<Number>)
    messageViewRawData: { type: Array, default: null },
  },
  data() {
    return {
      displayMode: 'DEC', // 显示模式：'DEC' (十进制) 或 'HEX' (十六进制)
      // 页面绑定的主要数据结构
      message: {
        control: { Lenth: '0', LNName: '0', DataSetName: '0', LDName: '0', SmpCtr: '0' },
        rated: { 'PhsA.Artg': '0', 'PhsA.Vrtg': '0', 'Neut.Artg': '0', tdr: '0' },
        status: {
          word1: '0', word2: '0',
          // 对应 Status Word 1 的位定义
          flags: {
            '要求检修 (PHHealth)': false,           // bit 0
            '试验状态 (Mode)': false,               // bit 1
            '唤醒时间数据无效 (DataInvalid)': false,// bit 2
            '适用于插值法 (Interpolation)': false,  // bit 3
            '时间同步无效 (SysInvalid)': false,     // bit 4
            '电流互感器输出类型 (OutputType)': false,// bit 12
            '比例因子 (RangeFlag)': false           // bit 13
          }
        },
        channels: createChannelData()
      }
    };
  },
  watch: {
    /**
     * @vuese
     * 监听来自 App.vue 的 `messageViewRawData` prop。
     * 当串口收到新的 0x32 响应数据时触发此回调。
     */
    messageViewRawData(newData) {
      if (newData && newData.length > 0) {
        console.log("MessageView received messageViewRawData:", newData);
        this.parseMessageData(newData);
      }
    },
    /**
     * @vuese
     * 监听 HEX/DEC 显示模式切换
     * 触发所有输入框数值的进制转换
     */
    displayMode(newMode) {
      this.convertAllValues(newMode);
    },

    /**
     * @vuese
     * [新增] 监听 "Status Word 1" 输入框的变化
     * 当解析数据更新 Word1，或用户手动编辑 Word1 时，自动更新下方的 Bit 标志位复选框
     */
    'message.status.word1'(newWord1Str) {
      this.updateFlagsFromStatusWord(newWord1Str);
    }
  },
  methods: {
    /**
     * @vuese
     * "获取" 按钮点击处理。
     * 发送 0x31 命令给下位机。
     */
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.error('请先连接串口');
        return;
      }
      this.$message.info('正在发送获取报文命令 (0x31)...');
      try {
        await this.sendCommand({ commandDef: CMD_REQ_MESSAGE });
        // 成功发送后，响应数据将由 App.vue 的串口监听捕获，并通过 props (messageViewRawData) 传回
      } catch (error) {
        this.$message.error(`获取报文失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * 辅助函数：读取 16 位小端整数 (unsigned short)。
     * Little Endian: 低字节在前，高字节在后。
     * @param {Array} buffer 字节数组
     * @param {Number} offset 起始偏移量
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Read short: offset ${offset} out of bounds for length ${buffer.length}`);
      }
      return buffer[offset] | (buffer[offset + 1] << 8); // 组合高低字节
    },

    /**
     * @vuese
     * 辅助函数：根据当前模式格式化数字为字符串
     * @param {Number} value 数值
     * @param {Number} bits 位宽 (8 或 16)，用于 HEX 模式补零
     * @param {String} mode 强制使用的模式 (可选)，默认使用 this.displayMode
     */
    formatHelper(value, bits, mode) {
      const modeToUse = mode || this.displayMode;
      if (modeToUse === 'HEX') {
        // HEX 模式：应用掩码并转为大写十六进制字符串
        const mask = (bits === 16) ? 0xFFFF : 0xFF;
        return '0x' + (value & mask).toString(16).toUpperCase().padStart(bits / 4, '0');
      }
      // DEC 模式：直接转字符串
      return value.toString();
    },

    /**
     * @vuese
     * 核心解析逻辑，移植自 C++ 代码: Dlg_Message.cpp::Fetch_data()
     * 将接收到的 64 字节二进制数据映射到 UI 模型。
     */
    parseMessageData(rawData) {
      if (!rawData || rawData.length < 64) {
        this.$message.error(`报文数据长度不足 (需要 64 字节，收到 ${rawData.length})`);
        return;
      }
      try {
        // --- 控制字解析 (Control Word) ---
        // 偏移 0: Length (2 bytes)
        this.message.control.Lenth = this.formatHelper(this.readShort(rawData, 0), 16);
        // 偏移 2: LNName (1 byte)
        this.message.control.LNName = this.formatHelper(rawData[2], 8);
        // 偏移 3: DataSetName (1 byte)
        this.message.control.DataSetName = this.formatHelper(rawData[3], 8);
        // 偏移 4: LDName (2 bytes)
        this.message.control.LDName = this.formatHelper(this.readShort(rawData, 4), 16);
        // 偏移 14: SmpCtr (2 bytes) - 注意这里跳过了中间一些字节
        this.message.control.SmpCtr = this.formatHelper(this.readShort(rawData, 14), 16);

        // --- 额定参数解析 (Rated Params) ---
        // 偏移 6: PhsA.Artg (2 bytes)
        this.message.rated['PhsA.Artg'] = this.formatHelper(this.readShort(rawData, 6), 16);
        // 偏移 8: Neut.Artg (2 bytes)
        this.message.rated['Neut.Artg'] = this.formatHelper(this.readShort(rawData, 8), 16);
        // 偏移 10: PhsA.Vrtg (2 bytes)
        this.message.rated['PhsA.Vrtg'] = this.formatHelper(this.readShort(rawData, 10), 16);
        // 偏移 12: tdr (2 bytes)
        this.message.rated.tdr = this.formatHelper(this.readShort(rawData, 12), 16);

        // --- 通道数据解析 (Channel1 to Channel22) ---
        // 从偏移 16 开始，连续 22 个通道，每个通道 2 字节
        for (let i = 0; i < 22; i++) {
          const offset = 16 + (i * 2);
          this.message.channels[`ch${i + 1}`] = this.formatHelper(this.readShort(rawData, offset), 16);
        }

        // --- 状态字解析 (Status Words) ---
        // 偏移 60: Status Word 1 (2 bytes)
        const word1 = this.readShort(rawData, 60);
        // 偏移 62: Status Word 2 (2 bytes)
        const word2 = this.readShort(rawData, 62);

        this.message.status.word1 = this.formatHelper(word1, 16);
        this.message.status.word2 = this.formatHelper(word2, 16);

        // --- 解析状态字 1 中的具体标志位 ---
        // 通过位运算提取 Boolean 状态
        // [注意] 这里虽然赋值了，但 Vue 的 watch('message.status.word1') 也会触发 updateFlagsFromStatusWord
        // 在此显式解析一次以确保初始状态正确
        const flags = this.message.status.flags;
        flags['要求检修 (PHHealth)'] = !!(word1 & 0x0001);
        flags['试验状态 (Mode)'] = !!(word1 & 0x0002);
        flags['唤醒时间数据无效 (DataInvalid)'] = !!(word1 & 0x0004);
        flags['适用于插值法 (Interpolation)'] = !!(word1 & 0x0008);
        flags['时间同步无效 (SysInvalid)'] = !!(word1 & 0x0010);
        flags['电流互感器输出类型 (OutputType)'] = !!(word1 & 0x1000);
        flags['比例因子 (RangeFlag)'] = !!(word1 & 0x2000);

        this.$message.success('报文数据已更新');

      } catch (e) {
        console.error("解析报文数据失败:", e);
        this.$message.error(`解析数据失败: ${e.message}`);
      }
    },

    /**
     * @vuese
     * 批量转换所有 40+ 个输入框的显示格式 (HEX <-> DEC)
     * 该方法保证了用户切换显示模式时，所有数值能正确对应转换。
     */
    convertAllValues(newMode) {
      // 确定源进制：如果新模式是 DEC，说明之前是 HEX (16进制)，反之亦然
      const oldBase = (newMode === 'DEC') ? 16 : 10;

      // 内部转换闭包
      const convert = (val, bits) => {
        if (typeof val !== 'string') val = String(val);
        let num = parseInt(val, oldBase); // 按照旧进制解析为整数
        if (isNaN(num)) num = 0;
        return this.formatHelper(num, bits, newMode); // 格式化为新进制字符串
      };

      try {
        // 转换 Control 对象中的属性 (位数各不相同)
        this.message.control.Lenth = convert(this.message.control.Lenth, 16);
        this.message.control.LNName = convert(this.message.control.LNName, 8);
        this.message.control.DataSetName = convert(this.message.control.DataSetName, 8);
        this.message.control.LDName = convert(this.message.control.LDName, 16);
        this.message.control.SmpCtr = convert(this.message.control.SmpCtr, 16);

        // 转换 Rated 对象中的属性 (均为 16 位)
        this.message.rated['PhsA.Artg'] = convert(this.message.rated['PhsA.Artg'], 16);
        this.message.rated['PhsA.Vrtg'] = convert(this.message.rated['PhsA.Vrtg'], 16);
        this.message.rated['Neut.Artg'] = convert(this.message.rated['Neut.Artg'], 16);
        this.message.rated.tdr = convert(this.message.rated.tdr, 16);

        // 转换 Status Words (均为 16 位)
        this.message.status.word1 = convert(this.message.status.word1, 16);
        this.message.status.word2 = convert(this.message.status.word2, 16);

        // 转换所有通道数据 (均为 16 位)
        for (let i = 1; i <= 22; i++) {
          const key = `ch${i}`;
          this.message.channels[key] = convert(this.message.channels[key], 16);
        }
      } catch (e) {
        console.error("转换 HEX/DEC 失败:", e);
        this.$message.error('格式转换失败');
      }
    },

    /**
     * @vuese
     * [新增] 移植自 C++: Dlg_Message.cpp line 865
     * 根据 Status Word 1 的数值字符串更新 UI 上的 Bit 标志位。
     * * 逻辑：
     * 1. 将字符串解析为数字 (支持 Hex/Dec)
     * 2. 使用位与 (&) 操作检查特定 Bit 是否为 1
     */
    updateFlagsFromStatusWord(word1String) {
      try {
        // 1. 根据当前显示模式，将输入框字符串解析为数字
        const base = this.displayMode === 'DEC' ? 10 : 16;
        let word1 = parseInt(word1String, base);
        if (isNaN(word1)) {
          word1 = 0;
        }

        // 2. 解析位并更新 Checkbox
        const flags = this.message.status.flags;
        flags['要求检修 (PHHealth)'] = !!(word1 & 0x0001);            // Bit 0
        flags['试验状态 (Mode)'] = !!(word1 & 0x0002);                // Bit 1
        flags['唤醒时间数据无效 (DataInvalid)'] = !!(word1 & 0x0004); // Bit 2
        flags['适用于插值法 (Interpolation)'] = !!(word1 & 0x0008);   // Bit 3
        flags['时间同步无效 (SysInvalid)'] = !!(word1 & 0x0010);      // Bit 4
        flags['电流互感器输出类型 (OutputType)'] = !!(word1 & 0x1000);// Bit 12
        flags['比例因子 (RangeFlag)'] = !!(word1 & 0x2000);           // Bit 13

      } catch (e) {
        console.error("Failed to update flags from Status Word 1:", e);
        // 发生错误时，重置所有标志位为 false
        Object.keys(this.message.status.flags).forEach(key => {
          this.message.status.flags[key] = false;
        });
      }
    }
  }
};
</script>

<style scoped>
/* 页面整体容器 */
.message-view {
  padding: 20px;
  background-color: #f0f2f5;
  height: 100%;
  box-sizing: border-box;
}

/* 布局调整：确保列高度填满 */
.el-row {
  height: 100%;
}
.el-col {
  height: 100%;
  display: flex;
  flex-direction: column;
}

/* 卡片样式：Flex 布局以支持内部滚动 */
.box-card {
  height: 100%;
  display: flex;
  flex-direction: column;
}
/* 固定卡片头部 */
.box-card ::v-deep(.el-card__header) {
  flex-shrink: 0;
  padding: 12px 15px;
}
/* 卡片内容区域可滚动 */
.box-card ::v-deep(.el-card__body) {
  flex-grow: 1;
  overflow-y: auto;
  display: flex;
  flex-direction: column;
  padding: 15px;
}

.status-flags {
  margin-top: 15px;
  display: flex;
  flex-direction: column;
  gap: 10px;
}

/* HEX/DEC 切换按钮居中 */
.display-mode-toggle {
  margin-bottom: 15px;
  text-align: center;
  flex-shrink: 0;
}

/* 底部按钮容器 */
.card-footer {
  display: flex;
  justify-content: flex-end;
  margin-top: 15px;
  flex-shrink: 0;
}

/* 紧凑表单样式 */
.compact-form .el-form-item {
  margin-bottom: 8px;
}

/* 通道数据滚动条处理 */
.channel-form-scrollbar {
  flex-grow: 1;
  min-height: 0;
}
.channel-form {
  padding-right: 10px; /* 防止滚动条遮挡内容 */
}
.el-divider {
  margin: 15px 0;
}
</style>