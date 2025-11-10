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
// C++: Dlg_Message::OnBUTTONMessageFetch() -> 49 (0x31)
const CMD_REQ_MESSAGE = { stationAddr: 0, telegramNr: 0x31, expectedResponseId: 0x32 };

/**
 * 创建 22 个通道的初始对象
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
    isSerialConnected: { type: Boolean, default: false },
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    messageViewRawData: { type: Array, default: null },
  },
  data() {
    return {
      displayMode: 'DEC',
      message: {
        control: { Lenth: '0', LNName: '0', DataSetName: '0', LDName: '0', SmpCtr: '0' },
        rated: { 'PhsA.Artg': '0', 'PhsA.Vrtg': '0', 'Neut.Artg': '0', tdr: '0' },
        status: {
          word1: '0', word2: '0',
          flags: {
            '要求检修 (PHHealth)': false,
            '试验状态 (Mode)': false,
            '唤醒时间数据无效 (DataInvalid)': false,
            '适用于插值法 (Interpolation)': false,
            '时间同步无效 (SysInvalid)': false,
            '电流互感器输出类型 (OutputType)': false,
            '比例因子 (RangeFlag)': false
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
     */
    messageViewRawData(newData) {
      if (newData && newData.length > 0) {
        console.log("MessageView received messageViewRawData:", newData);
        this.parseMessageData(newData);
      }
    },
    /**
     * @vuese
     * 监听 HEX/DEC 切换
     */
    displayMode(newMode) {
      this.convertAllValues(newMode);
    },

    /**
     * @vuese
     * [新增] 监听 "Status Word 1" 输入框的变化
     * 当用户手动编辑 Status Word 1 时，更新下面的复选框
     */
    'message.status.word1'(newWord1Str) {
      this.updateFlagsFromStatusWord(newWord1Str);
    }
  },
  methods: {
    /**
     * @vuese
     * "获取" 按钮点击处理。
     */
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.error('请先连接串口');
        return;
      }
      this.$message.info('正在发送获取报文命令 (0x31)...');
      try {
        await this.sendCommand({ commandDef: CMD_REQ_MESSAGE });
        // 响应将由 App.vue 捕获并通过 watcher(messageViewRawData) 传递回来
      } catch (error) {
        this.$message.error(`获取报文失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * 辅助函数：读取 16 位小端整数 (ushort)。
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) {
        throw new Error(`Read short: offset ${offset} out of bounds for length ${buffer.length}`);
      }
      return buffer[offset] | (buffer[offset + 1] << 8); // Little Endian
    },

    /**
     * @vuese
     * 辅助函数：格式化数字为字符串
     */
    formatHelper(value, bits, mode) {
      const modeToUse = mode || this.displayMode;
      if (modeToUse === 'HEX') {
        const mask = (bits === 16) ? 0xFFFF : 0xFF;
        return '0x' + (value & mask).toString(16).toUpperCase().padStart(bits / 4, '0');
      }
      return value.toString();
    },

    /**
     * @vuese
     * 核心解析逻辑，移植自 Dlg_Message.cpp::Fetch_data()
     */
    parseMessageData(rawData) {
      if (!rawData || rawData.length < 64) {
        this.$message.error(`报文数据长度不足 (需要 64 字节，收到 ${rawData.length})`);
        return;
      }
      try {
        // --- 控制字 ---
        this.message.control.Lenth = this.formatHelper(this.readShort(rawData, 0), 16);
        this.message.control.LNName = this.formatHelper(rawData[2], 8);
        this.message.control.DataSetName = this.formatHelper(rawData[3], 8);
        this.message.control.LDName = this.formatHelper(this.readShort(rawData, 4), 16);
        this.message.control.SmpCtr = this.formatHelper(this.readShort(rawData, 14), 16);

        // --- 额定参数 ---
        this.message.rated['PhsA.Artg'] = this.formatHelper(this.readShort(rawData, 6), 16);
        this.message.rated['Neut.Artg'] = this.formatHelper(this.readShort(rawData, 8), 16);
        this.message.rated['PhsA.Vrtg'] = this.formatHelper(this.readShort(rawData, 10), 16);
        this.message.rated.tdr = this.formatHelper(this.readShort(rawData, 12), 16);

        // --- 通道数据 (Channel1 to Channel22) ---
        for (let i = 0; i < 22; i++) {
          const offset = 16 + (i * 2);
          this.message.channels[`ch${i + 1}`] = this.formatHelper(this.readShort(rawData, offset), 16);
        }

        // --- 状态字 ---
        const word1 = this.readShort(rawData, 60);
        const word2 = this.readShort(rawData, 62);
        this.message.status.word1 = this.formatHelper(word1, 16);
        this.message.status.word2 = this.formatHelper(word2, 16);

        // --- 解析状态字 1 中的标志位 (保持不变) ---
        // [注意] watch 也会触发 updateFlagsFromStatusWord，但 parseMessageData 优先执行
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
     * 转换所有 40 个输入框的显示格式 (HEX/DEC)
     */
    convertAllValues(newMode) {
      const oldBase = (newMode === 'DEC') ? 16 : 10;

      // 辅助函数：转换一个值
      const convert = (val, bits) => {
        if (typeof val !== 'string') val = String(val);
        let num = parseInt(val, oldBase); // 从旧的进制解析
        if (isNaN(num)) num = 0;
        return this.formatHelper(num, bits, newMode); // 格式化为新的进制
      };

      try {
        // Control (16, 8, 8, 16, 16)
        this.message.control.Lenth = convert(this.message.control.Lenth, 16);
        this.message.control.LNName = convert(this.message.control.LNName, 8);
        this.message.control.DataSetName = convert(this.message.control.DataSetName, 8);
        this.message.control.LDName = convert(this.message.control.LDName, 16);
        this.message.control.SmpCtr = convert(this.message.control.SmpCtr, 16);

        // Rated (all 16)
        this.message.rated['PhsA.Artg'] = convert(this.message.rated['PhsA.Artg'], 16);
        this.message.rated['PhsA.Vrtg'] = convert(this.message.rated['PhsA.Vrtg'], 16);
        this.message.rated['Neut.Artg'] = convert(this.message.rated['Neut.Artg'], 16);
        this.message.rated.tdr = convert(this.message.rated.tdr, 16);

        // Status (all 16)
        this.message.status.word1 = convert(this.message.status.word1, 16);
        this.message.status.word2 = convert(this.message.status.word2, 16);

        // Channels (all 16)
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
     * [新增] 移植 C++: Dlg_Message.cpp line 865
     * 当 Status Word 1 的值改变时，更新 7 个只读复选框的状态
     */
    updateFlagsFromStatusWord(word1String) {
      try {
        // 1. 根据当前模式，将输入框的字符串解析为数字
        const base = this.displayMode === 'DEC' ? 10 : 16;
        let word1 = parseInt(word1String, base);
        if (isNaN(word1)) {
          word1 = 0;
        }

        // 2. 解析位
        const flags = this.message.status.flags;
        flags['要求检修 (PHHealth)'] = !!(word1 & 0x0001);
        flags['试验状态 (Mode)'] = !!(word1 & 0x0002);
        flags['唤醒时间数据无效 (DataInvalid)'] = !!(word1 & 0x0004);
        flags['适用于插值法 (Interpolation)'] = !!(word1 & 0x0008);
        flags['时间同步无效 (SysInvalid)'] = !!(word1 & 0x0010);
        flags['电流互感器输出类型 (OutputType)'] = !!(word1 & 0x1000);
        flags['比例因子 (RangeFlag)'] = !!(word1 & 0x2000);

      } catch (e) {
        console.error("Failed to update flags from Status Word 1:", e);
        // 发生错误时，重置所有标志
        Object.keys(this.message.status.flags).forEach(key => {
          this.message.status.flags[key] = false;
        });
      }
    }
  }
};
</script>

<style scoped>
.message-view {
  padding: 20px;
  background-color: #f0f2f5;
  height: 100%;
  box-sizing: border-box;
}
.el-row {
  height: 100%;
}
.el-col {
  height: 100%;
  display: flex;
  flex-direction: column;
}
.box-card {
  height: 100%; /* [修改] 恢复 100% 高度，使卡片等高 */
  display: flex;
  flex-direction: column;
}
.box-card ::v-deep(.el-card__header) {
  flex-shrink: 0;
  padding: 12px 15px;
}
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
.display-mode-toggle {
  margin-bottom: 15px;
  text-align: center;
  flex-shrink: 0;
}
.card-footer {
  display: flex;
  justify-content: flex-end;
  margin-top: 15px;
  flex-shrink: 0;
}
.compact-form .el-form-item {
  margin-bottom: 8px; /* 紧凑表单 */
}
.channel-form-scrollbar {
  flex-grow: 1;
  min-height: 0;
}
.channel-form {
  padding-right: 10px; /* 为滚动条留出空间 */
}
.el-divider {
  margin: 15px 0;
}
</style>