<template>
  <div class="data-parsing-view">
    <el-card class="box-card serial-io-card">
      <template #header>
        <div class="card-header">
          <span>串口数据收发 (Web Serial API)</span>
          <el-button @click="clearLog" size="small">清空日志</el-button>
        </div>
      </template>

      <div ref="serialLog" class="serial-log-display">
        <div v-for="(log, index) in serialLogs" :key="index" :class="log.type === 'in' ? 'log-in' : 'log-out'">
          <strong>{{ log.type === 'in' ? '← RECV:' : '→ SENT:' }}</strong>
          <span class="log-timestamp">{{ log.timestamp }}</span>
          <pre class="log-data">{{ log.data }}</pre>
        </div>
      </div>

      <div class="serial-send-controls">
        <el-input
            v-model="dataToSend"
            placeholder="输入文本, 或以 'HEX:' 开头的十六进制报文 (例如 HEX: 68 04...)"
            class="send-input"
            @keyup.enter="sendSerialData"
            :disabled="!isSerialConnected"
        />
        <el-checkbox v-model="interpretHexInput" label="智能识别HEX" border class="send-checkbox" :disabled="!isSerialConnected" />
        <el-button type="primary" @click="sendSerialData" :disabled="!isSerialConnected">发送</el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
// Helper function to format byte array to HEX string
function formatBytesToHex(bytes) {
  if (!bytes || bytes.length === 0) return '';
  // 如果输入已经是 number[], 直接用
  if (typeof bytes[0] === 'number') {
    return bytes.map(b => b.toString(16).padStart(2, '0').toUpperCase()).join(' ');
  }
  // 否则假定是 Uint8Array
  return Array.from(bytes).map(b => b.toString(16).padStart(2, '0').toUpperCase()).join(' ');
}

// Helper to get formatted timestamp
function getTimestamp() {
  const now = new Date();
  return now.toLocaleTimeString('en-US', { hour12: false }) + '.' + String(now.getMilliseconds()).padStart(3, '0');
}

export default {
  name: 'DataParsingView',
  props: {
    /**
     * @vuese
     * 由父组件传入，指示串口是否连接。
     */
    isSerialConnected: { type: Boolean, default: false },
    /**
     * @vuese
     * (新增) 从 App.vue 传入的写入串口方法。
     * @param {Uint8Array} data - The data to write.
     * @returns {Promise<boolean>} Promise indicating write success.
     */
    writeToSerial: { type: Function, default: () => Promise.resolve(false) },
    /**
     * @vuese
     * (新增) 从 App.vue 传入的最后接收到的已解析帧。
     * { type: 'data'|'ack_e5', raw: Uint8Array, ...otherProps }
     */
    lastReceivedFrame: { type: Object, default: null }
  },
  data() {
    return {
      serialLogs: [],
      dataToSend: '',
      interpretHexInput: true, // 默认启用智能 HEX 识别
    };
  },
  watch: {
    /**
     * @vuese
     * (新增) 监视来自 App.vue 的新接收帧，并将其添加到日志中。
     */
    lastReceivedFrame(newFrame) {
      if (newFrame) {
        let logMessage = '';
        if (newFrame.type === 'data' && newFrame.raw) {
          logMessage = `HEX: ${formatBytesToHex(newFrame.raw)}`;
        } else if (newFrame.type === 'ack_e5') {
          logMessage = 'ACK: E5';
        }
        // 可选：添加对其他类型帧或原始数据的处理
        // else if (newFrame.type === 'raw_bytes' && newFrame.data) {
        //    logMessage = `RAW: ${formatBytesToHex(newFrame.data)}`;
        // }

        if (logMessage) {
          this.addSerialLog(logMessage, 'in');
        }
      }
    }
  },
  methods: {
    addSerialLog(data, type) {
      this.serialLogs.push({ data, type, timestamp: getTimestamp() });
      // 限制日志数量，防止内存占用过大
      if (this.serialLogs.length > 200) {
        this.serialLogs.shift();
      }
      // 自动滚动到日志底部
      this.$nextTick(() => {
        const logEl = this.$refs.serialLog;
        if (logEl) {
          logEl.scrollTop = logEl.scrollHeight;
        }
      });
    },

    clearLog() {
      this.serialLogs = [];
      this.$message.success('日志已清空');
    },

    /**
     * @vuese
     * (重写) 发送串口数据。
     * 解析输入（文本或HEX），然后调用 App.vue 的 writeToSerial 方法。
     */
    async sendSerialData() {
      if (!this.isSerialConnected) {
        this.$message.error('请先连接串口');
        return;
      }
      if (!this.dataToSend) return;

      let dataBuffer; // Uint8Array
      let logMessage; // String for logging

      try {
        const input = this.dataToSend.trim();

        // 智能识别 HEX 或处理普通文本
        if (this.interpretHexInput && input.toUpperCase().startsWith('HEX:')) {
          const hex = input.substring(4).replace(/\s+/g, '');
          if (!/^[0-9A-Fa-f]*$/.test(hex) || hex.length % 2 !== 0) {
            throw new Error('HEX 格式错误: 请输入偶数长度的十六进制字符 (0-9, A-F)。');
          }
          const bytes = [];
          for (let i = 0; i < hex.length; i += 2) {
            bytes.push(parseInt(hex.substr(i, 2), 16));
          }
          dataBuffer = new Uint8Array(bytes);
          logMessage = `HEX: ${formatBytesToHex(dataBuffer)}`; // 记录格式化后的 HEX
        } else {
          // 作为普通文本发送
          dataBuffer = new TextEncoder().encode(input);
          logMessage = `ASCII: ${input}`;
        }

        // 记录将要发送的内容
        this.addSerialLog(logMessage, 'out');

        // 调用 App.vue 传入的写入方法
        const success = await this.writeToSerial(dataBuffer);

        if (success) {
          this.dataToSend = ''; // 发送成功后清空输入框
        } else {
          // writeToSerial 内部应该已经提示错误了
          // this.$message.error('发送失败，请检查连接');
        }

      } catch (e) {
        console.error("发送数据准备失败:", e);
        this.$message.error(`发送准备失败: ${e.message}`);
        // 记录错误到日志
        this.addSerialLog(`ERROR preparing send: ${e.message}`, 'out');
      }
    },
  }
};
</script>

<style scoped>
.data-parsing-view { height: 100%; display: flex; flex-direction: column; padding: 20px; background-color: #f0f2f5; box-sizing: border-box; }
.box-card { margin-bottom: 0; flex-grow: 1; display: flex; flex-direction: column; } /* 让卡片填满空间 */
.serial-io-card ::v-deep(.el-card__body) { flex-grow: 1; display: flex; flex-direction: column; padding: 15px; } /* 调整内边距 */
.card-header { display: flex; justify-content: space-between; align-items: center; }
.serial-log-display {
  flex-grow: 1; /* 占据大部分空间 */
  border: 1px solid #dcdfe6;
  border-radius: 4px;
  padding: 10px;
  overflow-y: auto; /* 垂直滚动 */
  background-color: #fff; /* 白色背景 */
  margin-bottom: 15px; /* 与发送控件的间距 */
  min-height: 200px; /* 最小高度 */
  font-size: 13px; /* 稍小字体 */
}
.log-in { color: #67C23A; /* Element Plus Success Green */ }
.log-out { color: #409EFF; /* Element Plus Primary Blue */ }
.log-timestamp {
  color: #909399; /* Element Plus Info Grey */
  font-size: 0.8em;
  margin-left: 10px;
}
.log-data {
  white-space: pre-wrap; /* 自动换行 */
  word-break: break-all; /* 强制断词 */
  margin: 2px 0 8px 0; /* 微调间距 */
  font-family: 'Consolas', 'Monaco', 'Courier New', Courier, monospace; /* 等宽字体 */
  line-height: 1.4;
}
.serial-send-controls { display: flex; align-items: center; flex-shrink: 0; /* 防止发送控件被压缩 */ }
.send-input { flex-grow: 1; margin-right: 10px; }
.send-checkbox { margin-right: 10px; }
</style>