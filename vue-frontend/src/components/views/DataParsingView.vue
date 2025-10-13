<template>
  <div class="data-parsing-view">
    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>实时数据解析</span>
          <el-form-item label="自动解析" class="auto-parse-toggle">
            <el-switch v-model="autoParse"></el-switch>
          </el-form-item>
        </div>
      </template>

      <el-table :data="parsedPackets" border height="600" style="width: 100%">
        <el-table-column prop="id" label="标号" width="70"></el-table-column>
        <el-table-column prop="direction" label="方向" width="80">
            <template #default="scope">
                <el-tag :type="scope.row.direction === 'IN' ? 'success' : 'primary'" size="small">{{ scope.row.direction }}</el-tag>
            </template>
        </el-table-column>
        <el-table-column prop="length" label="长度" width="80"></el-table-column>
        <el-table-column prop="func" label="功能" width="150"></el-table-column>
        <el-table-column prop="dec" label="十进制" min-width="150"></el-table-column>
        <el-table-column prop="hex" label="十六进制" min-width="150"></el-table-column>
        <el-table-column prop="ascii" label="ASCII" min-width="150"></el-table-column>
      </el-table>

    </el-card>
  </div>
</template>

<script>
export default {
  name: 'DataParsingView',
  props: {
    stompClient: { type: Object, default: null },
  },
  data() {
    return {
      autoParse: true,
      parsedPackets: [],
      packetCounter: 0,
      subscription: null,
    };
  },
  watch: {
    stompClient(newClient, oldClient) {
      if (oldClient) {
        this.unsubscribe();
      }
      if (newClient && newClient.connected) {
        this.subscribeToDataTopic();
      }
    },
  },
  methods: {
    subscribeToDataTopic() {
      if (!this.stompClient || this.subscription) return;
      this.subscription = this.stompClient.subscribe('/topic/raw-data', (message) => {
        if (this.autoParse) {
            const dataPacket = JSON.parse(message.body);
            this.parseAndDisplayPacket(dataPacket.payload, dataPacket.direction);
        }
      });
      console.log("DataParsingView: Subscribed to /topic/raw-data");
    },
    unsubscribe() {
      if (this.subscription) {
        this.subscription.unsubscribe();
        this.subscription = null;
        console.log("DataParsingView: Unsubscribed from /topic/raw-data");
      }
    },
    parseAndDisplayPacket(packetBytes, direction) {
      this.packetCounter++;
      
      // This is a placeholder parsing logic. You should adapt it to your actual protocol.
      // Protocol assumption: [HEADER: 0xAA] [LENGTH: 1 byte] [FUNCTION: 1 byte] [PAYLOAD: N bytes] [FOOTER: 0x55]
      const HEADER = 0xAA;
      const FOOTER = 0x55;
      let functionCode = 0;
      let payload = packetBytes;

      if (packetBytes[0] === HEADER && packetBytes[packetBytes.length - 1] === FOOTER) {
          functionCode = packetBytes[2];
          payload = packetBytes.slice(3, -1);
      }

      const newPacket = {
        id: this.packetCounter,
        direction: direction, // 'IN' or 'OUT'
        length: packetBytes.length,
        func: this.getFunctionMeaning(functionCode),
        dec: payload.join(' '),
        hex: payload.map(b => '0x' + b.toString(16).toUpperCase().padStart(2, '0')).join(' '),
        ascii: payload.map(b => (b >= 32 && b <= 126) ? String.fromCharCode(b) : '.').join(''),
      };

      this.parsedPackets.unshift(newPacket);
      if (this.parsedPackets.length > 200) { // Keep the list from growing indefinitely
        this.parsedPackets.pop();
      }
    },
    getFunctionMeaning(code) {
        // You should expand this map with your protocol's actual function codes
        const meanings = {
            0x00: '未知/原始数据',
            0x01: '心跳',
            0x02: '状态上报',
            0x10: '设置确认',
            0x11: '连接请求'
        };
        return meanings[code] || `未知 (0x${code.toString(16).toUpperCase()})`;
    }
  },
  mounted() {
    // The watcher will automatically subscribe when the stompClient is ready.
    if (this.stompClient && this.stompClient.connected) {
        this.subscribeToDataTopic();
    }
  },
  beforeUnmount() {
    this.unsubscribe();
  }
};
</script>

<style scoped>
.data-parsing-view { height: 100%; }
.box-card { height: 100%; display: flex; flex-direction: column; }
.card-header { display: flex; justify-content: space-between; align-items: center; }
.auto-parse-toggle { margin-bottom: 0; }
.el-card__body { flex-grow: 1; }
</style>
