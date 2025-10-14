<template>
  <div class="data-parsing-view">
    <!-- Card for Raw/Parsed Serial I/O -->
    <el-card class="box-card serial-io-card">
      <template #header>
        <div class="card-header">
          <span>串口数据收发</span>
        </div>
      </template>

      <div ref="serialLog" class="serial-log-display">
        <div v-for="(log, index) in serialLogs" :key="index" :class="log.type === 'in' ? 'log-in' : 'log-out'">
          <strong>{{ log.type === 'in' ? '← RECV:' : '→ SENT:' }}</strong>
          <pre class="log-data">{{ log.data }}</pre>
        </div>
      </div>

      <div class="serial-send-controls">
        <el-input
          v-model="dataToSend"
          placeholder="输入文本, 或以 'HEX:' 开头的十六进制报文 (例如 HEX: 68 04...)"
          class="send-input"
          @keyup.enter="sendSerialData"
        />
        <el-checkbox v-model="sendAsHex" label="十六进制发送" border class="send-checkbox" />
        <el-button type="primary" @click="sendSerialData">发送</el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
export default {
  name: 'DataParsingView',
  props: {
    serialDataIn: { type: Array, default: () => [] }, // Expect an array of parsed frames
  },
  data() {
    return {
      serialLogs: [],
      dataToSend: '',
      sendAsHex: false,
    };
  },
  watch: {
    serialDataIn(newFrames) {
      if (newFrames && newFrames.length > 0) {
        newFrames.forEach(frame => {
          const payloadAsHex = Array.from(frame.payload).map(b => b.toString(16).padStart(2, '0').toUpperCase()).join(' ');
          const formattedFrame =
`{
  stationAddr: ${frame.stationAddr},
  funcCode1: ${frame.funcCode1},
  funcCode2: ${frame.funcCode2},
  telegramNr: ${frame.telegramNr},
  payload: [${payloadAsHex}]
}`;
          this.addSerialLog(formattedFrame, 'in');
        });
      }
    },
  },
  methods: {
    addSerialLog(data, type) {
      this.serialLogs.push({ data, type });
      if (this.serialLogs.length > 200) this.serialLogs.shift();
      this.$nextTick(() => {
        const logEl = this.$refs.serialLog;
        if (logEl) logEl.scrollTop = logEl.scrollHeight;
      });
    },
    sendSerialData() {
      if (!this.dataToSend) return;
      let dataBuffer;
      let logMessage = this.dataToSend;

      try {
        const input = this.dataToSend.trim();
        // Smart HEX detection: check for 'HEX:' prefix
        if (input.toUpperCase().startsWith('HEX:')) {
          const hex = input.substring(4).replace(/\s+/g, '');
          if (!/^[0-9A-Fa-f]*$/.test(hex) || hex.length % 2 !== 0) {
            this.$message.error('HEX格式错误: 请输入偶数长度的十六进制字符。');
            return;
          }
          const bytes = [];
          for (let i = 0; i < hex.length; i += 2) bytes.push(parseInt(hex.substr(i, 2), 16));
          dataBuffer = new Uint8Array(bytes);
          logMessage = `HEX: ${hex.toUpperCase()}`;
        } else if (this.sendAsHex) {
          // Legacy HEX mode (without spaces)
          const hex = input.replace(/\s+/g, '');
           if (!/^[0-9A-Fa-f]*$/.test(hex) || hex.length % 2 !== 0) {
            this.$message.error('HEX格式错误: 请输入偶数长度的十六进制字符。');
            return;
          }
          const bytes = [];
          for (let i = 0; i < hex.length; i += 2) bytes.push(parseInt(hex.substr(i, 2), 16));
          dataBuffer = new Uint8Array(bytes);
          logMessage = `HEX: ${hex.toUpperCase()}`;
        } else {
          // Plain text mode
          dataBuffer = new TextEncoder().encode(input);
          logMessage = `ASCII: ${input}`;
        }

        this.$emit('send-serial-data', dataBuffer);
        this.addSerialLog(logMessage, 'out');
        this.dataToSend = '';
      } catch (e) {
        this.$message.error(`创建发送数据失败: ${e.message}`);
      }
    },
  }
};
</script>

<style scoped>
.data-parsing-view { height: 100%; display: flex; flex-direction: column; }
.box-card { margin-bottom: 20px; }
.box-card:last-child { margin-bottom: 0; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.serial-io-card .el-card__body { flex-grow: 1; display: flex; flex-direction: column; }
.serial-log-display { flex-grow: 1; border: 1px solid #dcdfe6; border-radius: 4px; padding: 10px; overflow-y: auto; background-color: #f8f9fa; }
.log-in { color: #198754; }
.log-out { color: #0d6efd; }
.log-data { white-space: pre-wrap; margin: 0; font-family: 'Courier New', Courier, monospace; font-size: 14px; }
.serial-send-controls { display: flex; align-items: center; margin-top: 15px; }
.send-input { flex-grow: 1; }
.send-checkbox { margin-left: 15px; margin-right: 15px; }
</style>
