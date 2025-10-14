<template>
  <div class="data-parsing-view">
    <!-- Existing Card for Parsed Packets from Server -->
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>实时数据解析 (来自服务器)</span>
          <el-form-item label="自动解析" class="auto-parse-toggle">
            <el-switch v-model="autoParse" />
          </el-form-item>
        </div>
      </template>
      <el-table :data="parsedPackets" border height="250" style="width: 100%">
        <el-table-column prop="id" label="标号" width="70" />
        <el-table-column prop="direction" label="方向" width="80">
          <template #default="scope">
            <el-tag :type="scope.row.direction === 'IN' ? 'success' : 'primary'" size="small">
              {{ scope.row.direction }}
            </el-tag>
          </template>
        </el-table-column>
        <el-table-column prop="length" label="长度" width="80" />
        <el-table-column prop="func" label="功能" width="150" />
        <el-table-column prop="dec" label="十进制" min-width="150" />
        <el-table-column prop="hex" label="十六进制" min-width="150" />
        <el-table-column prop="ascii" label="ASCII" min-width="150" />
      </el-table>
    </el-card>

    <!-- New Card for Raw Serial I/O -->
    <el-card class="box-card serial-io-card">
      <template #header>
        <div class="card-header">
          <span>串口原始数据收发</span>
        </div>
      </template>

      <div ref="serialLog" class="serial-log-display">
        <div v-for="(log, index) in serialLogs" :key="index" :class="log.type === 'in' ? 'log-in' : 'log-out'">
          <strong>{{ log.type === 'in' ? '← RECV:' : '→ SENT:' }}</strong>
          <span style="margin-left: 5px;">{{ log.data }}</span>
        </div>
      </div>

      <div class="serial-send-controls">
        <el-input
          v-model="dataToSend"
          placeholder="输入要发送的数据"
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
    stompClient: { type: Object, default: null },
    serialDataIn: { type: Uint8Array, default: null },
  },
  data() {
    return {
      autoParse: true,
      parsedPackets: [],
      packetCounter: 0,
      subscription: null,
      // New data for serial I/O
      serialLogs: [],
      dataToSend: '',
      sendAsHex: false,
    };
  },
  watch: {
    stompClient(newClient, oldClient) {
      if (oldClient) this.unsubscribe();
      if (newClient && newClient.connected) this.subscribeToDataTopic();
    },
    serialDataIn(newData) {
      if (newData) {
        const hexString = Array.from(newData).map(b => b.toString(16).padStart(2, '0').toUpperCase()).join(' ');
        const asciiString = Array.from(newData).map(b => (b >= 32 && b <= 126) ? String.fromCharCode(b) : '.').join('');
        this.addSerialLog(`HEX: ${hexString} | ASCII: ${asciiString}`, 'in');
      }
    },
  },
  mounted() {
    if (this.stompClient && this.stompClient.connected) {
      this.subscribeToDataTopic();
    }
  },
  beforeUnmount() {
    this.unsubscribe();
  },
  methods: {
    addSerialLog(data, type) {
      this.serialLogs.push({ data, type });
      if (this.serialLogs.length > 200) {
        this.serialLogs.shift();
      }
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
        if (this.sendAsHex) {
          const hex = this.dataToSend.replace(/\s+/g, '');
          if (!/^[0-9A-Fa-f]*$/.test(hex) || hex.length % 2 !== 0) {
            this.$message.error('HEX格式错误: 请输入偶数长度的十六进制字符。');
            return;
          }
          const bytes = [];
          for (let i = 0; i < hex.length; i += 2) {
            bytes.push(parseInt(hex.substr(i, 2), 16));
          }
          dataBuffer = new Uint8Array(bytes);
          logMessage = `HEX: ${this.dataToSend.toUpperCase()}`;
        } else {
          dataBuffer = new TextEncoder().encode(this.dataToSend);
          logMessage = `ASCII: ${this.dataToSend}`;
        }

        this.$emit('send-serial-data', dataBuffer);
        this.addSerialLog(logMessage, 'out');
        this.dataToSend = '';
      } catch (e) {
        this.$message.error(`创建发送数据失败: ${e.message}`);
      }
    },

    // --- Existing Methods for STOMP data ---
    subscribeToDataTopic() {
      if (!this.stompClient || this.subscription) return;
      this.subscription = this.stompClient.subscribe('/topic/raw-data', (message) => {
        if (this.autoParse) {
          const dataPacket = JSON.parse(message.body);
          this.parseAndDisplayPacket(dataPacket.payload, dataPacket.direction);
        }
      });
    },
    unsubscribe() {
      if (this.subscription) {
        this.subscription.unsubscribe();
        this.subscription = null;
      }
    },
    parseAndDisplayPacket(packetBytes, direction) {
      this.packetCounter++;
      const HEADER = 0xAA, FOOTER = 0x55;
      let functionCode = 0, payload = packetBytes;

      if (packetBytes[0] === HEADER && packetBytes[packetBytes.length - 1] === FOOTER) {
        functionCode = packetBytes[2];
        payload = packetBytes.slice(3, -1);
      }

      this.parsedPackets.unshift({
        id: this.packetCounter,
        direction: direction,
        length: packetBytes.length,
        func: this.getFunctionMeaning(functionCode),
        dec: payload.join(' '),
        hex: payload.map(b => '0x' + b.toString(16).toUpperCase().padStart(2, '0')).join(' '),
        ascii: payload.map(b => (b >= 32 && b <= 126) ? String.fromCharCode(b) : '.').join(''),
      });
      if (this.parsedPackets.length > 200) this.parsedPackets.pop();
    },
    getFunctionMeaning(code) {
      const meanings = { 0x00: '未知/原始数据', 0x01: '心跳', 0x02: '状态上报', 0x10: '设置确认', 0x11: '连接请求' };
      return meanings[code] || `未知 (0x${code.toString(16).toUpperCase()})`;
    }
  }
};
</script>

<style scoped>
.data-parsing-view { height: 100%; display: flex; flex-direction: column; }
.box-card { margin-bottom: 20px; }
.box-card:last-child { margin-bottom: 0; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.auto-parse-toggle { margin-bottom: 0; }

.serial-io-card .el-card__body { flex-grow: 1; display: flex; flex-direction: column; }
.serial-log-display { flex-grow: 1; border: 1px solid #dcdfe6; border-radius: 4px; padding: 10px; overflow-y: auto; background-color: #fafafa; font-family: 'Courier New', Courier, monospace; font-size: 14px; margin-bottom: 15px; }
.log-in { color: #67c23a; }
.log-out { color: #409eff; }
.serial-send-controls { display: flex; align-items: center; }
.send-input { flex-grow: 1; }
.send-checkbox { margin-left: 15px; margin-right: 15px; }
</style>
