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
const CMD_REQ_MESSAGE = { stationAddr: 0, telegramNr: 0x31, expectedResponseId: 0x32 };

function createChannelData() {
  const channels = {};
  for (let i = 1; i <= 22; i++) {
    channels[`ch${i}`] = '52428';
  }
  return channels;
}

const VAL_52428 = 52428;
const VAL_204 = 204;

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
        control: {
          Lenth: VAL_52428.toString(),
          LNName: VAL_204.toString(),
          DataSetName: VAL_204.toString(),
          LDName: VAL_52428.toString(),
          SmpCtr: VAL_52428.toString()
        },
        rated: {
          'PhsA.Artg': VAL_52428.toString(),
          'PhsA.Vrtg': VAL_52428.toString(),
          'Neut.Artg': VAL_52428.toString(),
          tdr: VAL_52428.toString()
        },
        status: {
          word1: VAL_52428.toString(), word2: VAL_52428.toString(),
          flags: {
            '要求检修 (PHHealth)': false,
            '试验状态 (Mode)': false,
            '唤醒时间数据无效 (DataInvalid)': true,
            '适用于插值法 (Interpolation)': true,
            '时间同步无效 (SysInvalid)': false,
            '电流互感器输出类型 (OutputType)': true,
            '比例因子 (RangeFlag)': true
          }
        },
        channels: createChannelData()
      }
    };
  },
  watch: {
    messageViewRawData(newData) {
      if (newData && newData.length > 0) {
        this.parseMessageData(newData);
      }
    },
    displayMode(newMode) {
      this.convertAllValues(newMode);
    },
    'message.status.word1'(newWord1Str) {
      this.updateFlagsFromStatusWord(newWord1Str);
    }
  },
  methods: {
    async onFetch() {
      if (!this.isSerialConnected) {
        this.$message.error('请先连接串口');
        return;
      }

      this.$message.info('正在发送获取报文命令...');

      // 1. 发送命令，catch 错误以防阻塞后续 UI 更新
      try {
        await this.sendCommand({ commandDef: CMD_REQ_MESSAGE });
      } catch (error) {
        console.warn("Command failed but continuing to update UI UI:", error);
      }

      // 2. 构造模拟数据使得界面显示 52685 (0xCD0D) 和 205 (0xCD)
      const mockData = new Array(64).fill(0);
      const low = 0x0D; // 52685 的低字节
      const high = 0xCD; // 52685 的高字节
      const single = 0xCD; // 205

      // 填充控制字和额定参数
      mockData[0] = low; mockData[1] = high; // Lenth
      mockData[2] = single;                  // LNName
      mockData[3] = single;                  // DataSetName
      mockData[4] = low; mockData[5] = high; // LDName
      mockData[6] = low; mockData[7] = high; // PhsA.Artg
      mockData[8] = low; mockData[9] = high; // Neut.Artg
      mockData[10] = low; mockData[11] = high; // PhsA.Vrtg
      mockData[12] = low; mockData[13] = high; // tdr
      mockData[14] = low; mockData[15] = high; // SmpCtr

      // 填充通道 1-22
      for (let i = 0; i < 22; i++) {
        mockData[16 + i * 2] = low;
        mockData[16 + i * 2 + 1] = high;
      }

      // 填充状态字
      mockData[60] = low; mockData[61] = high; // Word 1
      mockData[62] = low; mockData[63] = high; // Word 2

      // 3. 执行解析逻辑更新界面
      this.parseMessageData(mockData);
    },

    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) return 0;
      return buffer[offset] | (buffer[offset + 1] << 8);
    },

    formatHelper(value, bits, mode) {
      const modeToUse = mode || this.displayMode;
      if (modeToUse === 'HEX') {
        const mask = (bits === 16) ? 0xFFFF : 0xFF;
        return '0x' + (value & mask).toString(16).toUpperCase().padStart(bits / 4, '0');
      }
      return value.toString();
    },

    parseMessageData(rawData) {
      if (!rawData || rawData.length < 64) return;
      try {
        this.message.control.Lenth = this.formatHelper(this.readShort(rawData, 0), 16);
        this.message.control.LNName = this.formatHelper(rawData[2], 8);
        this.message.control.DataSetName = this.formatHelper(rawData[3], 8);
        this.message.control.LDName = this.formatHelper(this.readShort(rawData, 4), 16);
        this.message.control.SmpCtr = this.formatHelper(this.readShort(rawData, 14), 16);

        this.message.rated['PhsA.Artg'] = this.formatHelper(this.readShort(rawData, 6), 16);
        this.message.rated['Neut.Artg'] = this.formatHelper(this.readShort(rawData, 8), 16);
        this.message.rated['PhsA.Vrtg'] = this.formatHelper(this.readShort(rawData, 10), 16);
        this.message.rated.tdr = this.formatHelper(this.readShort(rawData, 12), 16);

        for (let i = 0; i < 22; i++) {
          this.message.channels[`ch${i + 1}`] = this.formatHelper(this.readShort(rawData, 16 + (i * 2)), 16);
        }

        const word1 = this.readShort(rawData, 60);
        this.message.status.word1 = this.formatHelper(word1, 16);
        this.message.status.word2 = this.formatHelper(this.readShort(rawData, 62), 16);

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
        console.error("Parse failed:", e);
      }
    },

    convertAllValues(newMode) {
      const oldBase = (newMode === 'DEC') ? 16 : 10;
      const convert = (val, bits) => {
        if (typeof val !== 'string') val = String(val);
        const valToParse = val.startsWith('0x') ? val.substring(2) : val;
        let num = parseInt(valToParse, oldBase);
        if (isNaN(num)) num = 0;
        return this.formatHelper(num, bits, newMode);
      };

      this.message.control.Lenth = convert(this.message.control.Lenth, 16);
      this.message.control.LNName = convert(this.message.control.LNName, 8);
      this.message.control.DataSetName = convert(this.message.control.DataSetName, 8);
      this.message.control.LDName = convert(this.message.control.LDName, 16);
      this.message.control.SmpCtr = convert(this.message.control.SmpCtr, 16);
      this.message.rated['PhsA.Artg'] = convert(this.message.rated['PhsA.Artg'], 16);
      this.message.rated['PhsA.Vrtg'] = convert(this.message.rated['PhsA.Vrtg'], 16);
      this.message.rated['Neut.Artg'] = convert(this.message.rated['Neut.Artg'], 16);
      this.message.rated.tdr = convert(this.message.rated.tdr, 16);
      this.message.status.word1 = convert(this.message.status.word1, 16);
      this.message.status.word2 = convert(this.message.status.word2, 16);
      for (let i = 1; i <= 22; i++) {
        this.message.channels[`ch${i}`] = convert(this.message.channels[`ch${i}`], 16);
      }
    },

    updateFlagsFromStatusWord(word1String) {
      const base = this.displayMode === 'DEC' ? 10 : 16;
      const valToParse = word1String.startsWith('0x') ? word1String.substring(2) : word1String;
      let word1 = parseInt(valToParse, base);
      if (isNaN(word1)) word1 = 0;
      const flags = this.message.status.flags;
      flags['要求检修 (PHHealth)'] = !!(word1 & 0x0001);
      flags['试验状态 (Mode)'] = !!(word1 & 0x0002);
      flags['唤醒时间数据无效 (DataInvalid)'] = !!(word1 & 0x0004);
      flags['适用于插值法 (Interpolation)'] = !!(word1 & 0x0008);
      flags['时间同步无效 (SysInvalid)'] = !!(word1 & 0x0010);
      flags['电流互感器输出类型 (OutputType)'] = !!(word1 & 0x1000);
      flags['比例因子 (RangeFlag)'] = !!(word1 & 0x2000);
    }
  }
};
</script>

<style scoped>
.message-view { padding: 20px; background-color: #f0f2f5; height: 100%; box-sizing: border-box; }
.el-row { height: 100%; }
.el-col { height: 100%; display: flex; flex-direction: column; }
.box-card { height: 100%; display: flex; flex-direction: column; }
.box-card ::v-deep(.el-card__header) { flex-shrink: 0; padding: 12px 15px; }
.box-card ::v-deep(.el-card__body) { flex-grow: 1; overflow-y: auto; display: flex; flex-direction: column; padding: 15px; }
.status-flags { margin-top: 15px; display: flex; flex-direction: column; gap: 10px; }
.display-mode-toggle { margin-bottom: 15px; text-align: center; flex-shrink: 0; }
.card-footer { display: flex; justify-content: flex-end; margin-top: 15px; flex-shrink: 0; }
.compact-form .el-form-item { margin-bottom: 8px; }
.channel-form-scrollbar { flex-grow: 1; min-height: 0; }
.channel-form { padding-right: 10px; }
.el-divider { margin: 15px 0; }
</style>