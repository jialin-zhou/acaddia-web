<template>
  <div class="tqml-view">
    <div class="view-header-controls">
      <el-radio-group
        v-model="mode"
        size="small"
      >
        <el-radio-button label="received">
          接收到命令
        </el-radio-button>
        <el-radio-button label="sent">
          发合闸命令
        </el-radio-button>
        <el-radio-button label="timed">
          合闸时刻
        </el-radio-button>
      </el-radio-group>
    </div>

    <el-card class="box-card">
      <template #header>
        <div class="card-header">
          <span>同期命令</span>
        </div>
      </template>

      <div class="status-bar">
        <span>完成状态:</span>
        <el-checkbox
          v-model="status.rec_ok"
          label="接收OK"
          disabled
        />
        <el-checkbox
          v-model="status.sent_ok"
          label="发送OK"
          disabled
        />
        <el-checkbox
          v-model="status.time_ok"
          label="时刻OK"
          disabled
        />
        <el-checkbox
          v-model="status.reset"
          label="复位"
          disabled
        />
        <el-checkbox
          v-model="status.unfinished"
          label="未完成"
          disabled
        />
      </div>

      <el-table
        :data="tableData"
        border
        style="width: 100%"
      >
        <el-table-column
          label="信息"
          prop="label"
          width="120"
        />

        <el-table-column label="接收值 (Mode: Rec)">
          <template #default="scope">
            <el-date-picker
              v-if="scope.row.type === 'datetime'"
              v-model="scope.row.receivedValue"
              type="datetime"
              size="small"
              readonly
              placeholder=""
              style="width: 100%;"
              format="YYYY-MM-DD HH:mm:ss"
            />
            <el-input
              v-else
              v-model="scope.row.receivedValue"
              size="small"
              readonly
              style="width: 100%;"
            />
          </template>
        </el-table-column>

        <el-table-column label="发送值 (Mode: Sent)">
          <template #default="scope">
            <el-date-picker
              v-if="scope.row.type === 'datetime'"
              v-model="scope.row.sentValue"
              type="datetime"
              size="small"
              readonly
              placeholder=""
              style="width: 100%;"
              format="YYYY-MM-DD HH:mm:ss"
            />
            <el-input
              v-else
              v-model="scope.row.sentValue"
              size="small"
              readonly
              style="width: 100%;"
            />
          </template>
        </el-table-column>

        <el-table-column label="时刻值 (Mode: Time)">
          <template #default="scope">
            <el-date-picker
              v-if="scope.row.type === 'datetime'"
              v-model="scope.row.timedValue"
              type="datetime"
              size="small"
              readonly
              placeholder=""
              style="width: 100%;"
              format="YYYY-MM-DD HH:mm:ss"
            />
            <el-input
              v-else
              v-model="scope.row.timedValue"
              size="small"
              readonly
              style="width: 100%;"
            />
          </template>
        </el-table-column>
      </el-table>

      <div class="view-footer">
        <el-button
          :disabled="!isSerialConnected"
          @click="onFetch"
        >
          信息读取
        </el-button>
        <el-button
          type="primary"
          :disabled="!isSerialConnected"
          @click="onExecute"
        >
          同期开出
        </el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
// --- 命令定义 (基于 Dlg_TQML.cpp 和您的描述) ---
// "同期开出" (复位)
const CMD_TQML_EXEC = { stationAddr: 0, telegramNr: 0x2C, expectedResponseId: 0xE5 }; // (C++: 44)
// "信息读取"
const CMD_TQML_FETCH = { stationAddr: 0, telegramNr: 0x2D, expectedResponseId: 0x2E }; // (C++: 45, 响应 46/0x2E)

export default {
  name: 'TqmlView',
  props: {
    /**
     * @vuese
     * 串行端口是否连接，由父组件 (App.vue) 传入，用于控制按钮的可用状态
     */
    isSerialConnected: { type: Boolean, default: false },
    /**
     * @vuese
     * 发送命令的函数，由父组件 (App.vue) 注入
     * @arg {object} { commandDef, payload }
     */
    sendCommand: { type: Function, default: () => Promise.reject("sendCommand function not provided") },
    /**
     * @vuese
     * 从 App.vue 传入的 TQML 响应字节数组 (来自 0x2E 响应)。
     * 当父组件接收到 0x2E 响应时，会更新这个 prop。
     */
    tqmlRawData: { type: Array, default: null },
  },
  data() {
    return {
      // C++: m_nTQML_REC (0=Rec, 1=Sent, 2=Time).
      // 对应顶部 RadioButton 的 V-model，控制当前UI显示和“信息读取”时发送的负载
      mode: 'received',
      // C++: m_BOOL... 标志
      // 对应状态栏的 Checkbox，用于UI显示
      status: {
        reset: false,
        unfinished: false,
        rec_ok: false,
        sent_ok: false,
        time_ok: false,
      },
      // C++: m_floatTQML_...
      // 核心数据存储，用于存储三组（接收、发送、时刻）的浮点数数据
      dataStore: {
        received: this.createDataGroup(),
        sent: this.createDataGroup(),
        timed: this.createDataGroup(),
      },
      // C++: m_DateTimeTQML_...
      // 存储三组数据的时间对象
      dateTimeStore: {
        received: null,
        sent: null,
        timed: null,
      }
    };
  },
  computed: {
    /**
     * @vuese
     * [核心] 计算属性，将 dataStore 和 dateTimeStore 中存储的数据“旋转”为 el-table 所需的行格式。
     * el-table 需要的是一个数组，数组中每个对象是一“行”数据。
     * 而我们的 dataStore 是按“列”存储的 (received, sent, timed)。
     * 这个计算属性就是做这个数据转换的。
     */
    tableData() {
      // 定义表格的“行”结构
      const labels = [
        { key: 'date', label: 'Date', type: 'datetime' },
        { key: 'ms', label: '(ms)', type: 'text' },
        { key: 'u1', label: 'U1(V)', type: 'text' },
        { key: 'u2', label: 'U2(V)', type: 'text' },
        { key: 'f1', label: 'f1(Hz)', type: 'text' },
        { key: 'f2', label: 'f2(Hz)', type: 'text' },
        { key: 'f1_dt', label: 'f1/dT(Hz/S)', type: 'text' },
        { key: 'f2_dt', label: 'f2/dT(Hz/S)', type: 'text' },
        { key: 'du', label: 'Δu(V)', type: 'text' },
        { key: 'df', label: 'Δf(Hz)', type: 'text' },
        { key: 'df_dt', label: 'df/dt(Hz/S)', type: 'text' },
        { key: 'da', label: 'Δα(deg)', type: 'text' }
      ];

      // 遍历 labels，为表格的每一行生成一个对象
      return labels.map(item => {
        // 如果是日期行
        if (item.type === 'datetime') {
          return {
            ...item,
            receivedValue: this.dateTimeStore.received,
            sentValue: this.dateTimeStore.sent,
            timedValue: this.dateTimeStore.timed,
          }
        }
        // 如果是普通数据行
        return {
          ...item,
          receivedValue: this.dataStore.received[item.key],
          sentValue: this.dataStore.sent[item.key],
          timedValue: this.dataStore.timed[item.key],
        }
      });
    }
  },
  watch: {
    /**
     * @vuese
     * 监听来自 App.vue 的 `tqmlRawData` (0x2E 响应)
     * 这是数据传入的主要入口点。
     */
    tqmlRawData(newData) {
      // 当父组件通过 prop 传入新的数据时 (且数据不为空)
      if (newData && newData.length > 0) {
        console.log("TqmlView received tqmlRawData (0x2E):", newData);
        // 调用解析函数处理这批新数据
        this.parseTqmlData(newData);
      }
    }
  },
  methods: {
    /**
     * @vuese
     * "同期开出" 按钮点击事件 (C++: onButtonApplyClicked)
     * 发送 0x2C (44) 命令，带 0x55AA 负载，执行复位。
     */
    async onExecute() {
      this.$message.info('正在发送 "同期开出" (复位) 命令 (0x2C)...');

      // C++: pParent->Connect_Telegram.ValidDataToPack[0] = 0x55;
      // C++: pParent->Connect_Telegram.ValidDataToPack[1] = 0xaa;
      // 固定的负载 0x55AA
      const payload = new Uint8Array([0x55, 0xAA]);

      try {
        // 调用父组件注入的 sendCommand 方法
        await this.sendCommand({ commandDef: CMD_TQML_EXEC, payload: payload });
        // E5 确认是在父组件 (App.vue) 的响应处理中完成的，
        // E5 响应 *不会* 触发 tqmlRawData (那是 0x2E)，
        // 但如果 E5 确认了复位，设备可能会在下次读取时返回 Type 4
        this.$message.success('"同期开出" 命令已发送，等待 E5 确认');
      } catch (error) {
        this.$message.error(`"同期开出" 命令发送失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * "信息读取" 按钮点击事件 (C++: onButtonFetchClicked)
     * 发送 0x2D (45) 命令，负载为 [1], [2] 或 [3]
     */
    async onFetch() {
      let payloadByte;
      // 根据当前UI选择的 mode，决定发送的负载 (1, 2, 或 3)
      switch (this.mode) {
        case 'received': payloadByte = 1; break; // C++: m_nTQML_REC = 0 -> 0+1=1
        case 'sent': payloadByte = 2; break;     // C++: m_nTQML_REC = 1 -> 1+1=2
        case 'timed': payloadByte = 3; break;    // C++: m_nTQML_REC = 2 -> 2+1=3
        default: payloadByte = 1;
      }

      this.$message.info(`正在读取 "Mode: ${this.mode}" (ID: ${payloadByte}) 的信息 (0x2D)...`);

      // C++: pParent->Connect_Telegram.ValidDataToPack[0] = (uchar)(m_nTQML_REC + 1);
      // 负载为 [1] 或 [2] 或 [3]
      const payload = new Uint8Array([payloadByte]);

      try {
        // 调用父组件的 sendCommand 方法
        await this.sendCommand({ commandDef: CMD_TQML_FETCH, payload: payload });
        // 成功发送后，等待 App.vue 接收 0x2E 响应，
        // 然后 App.vue 会更新 tqmlRawData prop，
        // 接着触发 watch.tqmlRawData -> parseTqmlData -> UI 更新。
      } catch (error) {
        this.$message.error(`"信息读取" 命令发送失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * [移植] C++: Dlg_TQML::parseData()
     * [!!!BUG FIX!!!] 修正了解析逻辑，使其能处理 1 字节的状态响应 (Type 4, 5)
     * @param {number[]} buffer - 原始字节数组 (payload of 0x2E)。
     */
    parseTqmlData(buffer) {
      // [FIX] 1. 检查 buffer 是否为空或长度为 0
      if (!buffer || buffer.length < 1) {
        console.warn(`TQML parse failed: buffer is null or empty.`, buffer);
        this.$message.error('解析 TQML 数据失败：收到空响应');
        return;
      }

      try {
        // [FIX] 2. 立即读取记录类型 (响应的第一个字节)
        const recordType = buffer[0]; // C++: ValidData[4] (在C++代码中，4是payload的起始索引)

        // 每次解析前，重置所有状态标志 (C++: parseData 每次都会重置)
        this.status.reset = false;
        this.status.unfinished = false;
        this.status.rec_ok = false;
        this.status.sent_ok = false;
        this.status.time_ok = false;

        // [FIX] 3. 优先处理 1 字节的状态响应 (Type 4, 5)
        // 这是C++代码中可能存在的逻辑缺陷，它可能总是期望27字节
        if (recordType === 4) { // 复位(Reset)
          this.status.reset = true;
          this.resetDataFields(); // 清空 UI 字段
          this.$message.info('收到设备复位确认 (无数据)');
          return; // 解析成功
        }
        if (recordType === 5) { // 未完成(Unfinish)
          this.status.unfinished = true;
          this.resetDataFields(); // 清空 UI 字段
          this.$message.warning('设备报告：未完成 (无数据)');
          return; // 解析成功
        }

        // [FIX] 4. 如果不是 Type 4 或 5，才检查 27 字节的完整数据长度
        // (C++: m_nLength == 31, 31-4 = 27 字节 payload)
        if (buffer.length < 27) {
          console.warn(`TQML parse failed: buffer length ${buffer.length} < 27 for data record type ${recordType}.`, buffer);
          this.$message.error('解析 TQML 数据失败：响应数据格式不正确');
          return;
        }

        // --- 解析完整数据 (C++: 偏移量从 5 开始, JS payload 偏移量从 1 开始) ---
        // 注意：JS payload (buffer) 的索引 0 是 C++ ValidData[4] (即 recordType)
        // C++ ValidData[5] 对应 JS buffer[1]

        // 解析日期和毫秒
        const dt = this.parseDateTime(buffer, 1, 3); // C++: ValidData[5] (day), ValidData[7] (ms)
        // 解析浮点数
        const u1 = this.readFloat(buffer, 7, 100.0);   // C++: ValidData[11]
        const u2 = this.readFloat(buffer, 9, 100.0);   // C++: ValidData[13]
        const f1 = this.readFloat(buffer, 11, 1000.0); // C++: ValidData[15]
        const f2 = this.readFloat(buffer, 13, 1000.0); // C++: ValidData[17]
        const f1_dt = this.readFloat(buffer, 15, 100.0); // C++: ValidData[19]
        const f2_dt = this.readFloat(buffer, 17, 100.0); // C++: ValidData[21]
        const du = this.readFloat(buffer, 19, 100.0);  // C++: ValidData[23]
        const df = this.readFloat(buffer, 21, 1000.0); // C++: ValidData[25]
        const df_dt = this.readFloat(buffer, 23, 100.0); // C++: ValidData[27]
        const da = this.readFloat(buffer, 25, 100.0);  // C++: ValidData[29]

        // 将解析出的浮点数格式化为字符串，用于UI显示
        const dataGroup = {
          ms: dt.ms, // 毫秒部分 (用于 'ms' 行)
          u1: u1.toFixed(2), f2: f2.toFixed(3), f1_dt: f1_dt.toFixed(2),
          u2: u2.toFixed(2), df: df.toFixed(3), f2_dt: f2_dt.toFixed(2),
          f1: f1.toFixed(3), da: da.toFixed(2), df_dt: df_dt.toFixed(2),
          du: du.toFixed(2),
        };

        // 根据记录类型，将数据存入 dataStore 和 dateTimeStore 的对应位置
        if (recordType === 1) { // 接收(Rec)
          this.dataStore.received = dataGroup;
          this.dateTimeStore.received = dt.date; // 完整的 Date 对象
          this.status.rec_ok = true;
          this.mode = 'received'; // 自动切换UI到收到的数据模式
          this.$message.success('已更新 "接收(Rec)" 数据');
        } else if (recordType === 2) { // 发送(Sent)
          this.dataStore.sent = dataGroup;
          this.dateTimeStore.sent = dt.date;
          this.status.sent_ok = true;
          this.mode = 'sent';
          this.$message.success('已更新 "发送(Sent)" 数据');
        } else if (recordType === 3) { // 时间(Time)
          this.dataStore.timed = dataGroup;
          this.dateTimeStore.timed = dt.date;
          this.status.time_ok = true;
          this.mode = 'timed';
          this.$message.success('已更新 "时刻(Time)" 数据');
        }

      } catch (e) {
        console.error("解析 TQML 数据失败:", e);
        this.$message.error(`解析 TQML 数据失败: ${e.message}`);
      }
    },

    // --- 辅助函数 ---

    /**
     * @vuese
     * [移植] C++: Dlg_TQML::resetDataFields()
     * 重置(清空)所有UI上显示的数据
     */
    resetDataFields() {
      // 重新创建空的数据组
      this.dataStore.received = this.createDataGroup();
      this.dataStore.sent = this.createDataGroup();
      this.dataStore.timed = this.createDataGroup();
      // 清空日期
      this.dateTimeStore.received = null;
      this.dateTimeStore.sent = null;
      this.dateTimeStore.timed = null;
    },

    /**
     * @vuese
     * 创建一组空的默认数据对象
     */
    createDataGroup() {
      // 使用 0 而不是 ""，因为 C++ 中是 float，
      // 并且 .toFixed() 在 0 上工作正常，在 "" 上会报错
      return {
        ms: 0, u1: 0, u2: 0, f1: 0, f2: 0, f1_dt: 0, f2_dt: 0,
        du: 0, df: 0, df_dt: 0, da: 0
      };
    },

    /**
     * @vuese
     * [移植] C++: Dlg_TQML::parseDateTimeFromData (偏移量已调整为 payload)
     * @param {number[]} buffer - payload 缓冲区
     * @param {number} dayOffset - payload 中天数的起始偏移量 (C++: ValidData[5])
     * @param {number} msOffset - payload 中毫秒数的起始偏移量 (C++: ValidData[7])
     */
    parseDateTime(buffer, dayOffset, msOffset) {
      // 1. 解析天数 (2字节, 小端)
      const days = this.readShort(buffer, dayOffset);

      // 2. 解析毫秒数 (4字节, 小端)
      // C++: *((long*)(ValidData+7))
      const ms = buffer[msOffset] |
          (buffer[msOffset + 1] << 8) |
          (buffer[msOffset + 2] << 16) |
          (buffer[msOffset + 3] << 24);

      // 3. 计算日期 (JS 月份从 0 开始)
      const baseDate = new Date(Date.UTC(1984, 0, 1)); // 基准日期 1984-01-01 UTC

      // Dlg_TQML.cpp::parseDateTimeFromData 使用 addDays(days)
      // 计算从基准日期过了 'days' 天后的时间戳
      const targetTimestamp = baseDate.getTime() + days * (24 * 60 * 60 * 1000);

      // 组合日期和时间
      // C++ 中 COleDateTime::operator= (double) 似乎是本地时间，
      // 但这里为了保险起见，我们先按 UTC 计算
      const date = new Date(targetTimestamp);
      date.setUTCHours(0, 0, 0, 0); // 重置到 UTC 午夜
      date.setUTCMilliseconds(ms); // 添加当天的毫秒数

      // 构造函数或 setTime 会将 UTC 时间戳转换为本地时区
      // 返回本地时间 Date 对象
      return {
        date: date, // 完整的 Date 对象，用于 el-date-picker
        ms: ms % 1000 // 仅毫秒部分，用于 'ms' 行
      };
    },

    /**
     * @vuese
     * 从字节数组读取 16 位小端整数 (unsigned short)。
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) throw new Error("Read short: offset out of bounds");
      // 小端: 低位在前, 高位在后
      return buffer[offset] | (buffer[offset + 1] << 8);
    },

    /**
     * @vuese
     * 从字节数组读取 16 位 ushort，转为 float 并除以系数。
     * (C++: (float)(*((ushort*)(ValidData+11)))/100.0)
     */
    readFloat(buffer, offset, divisor) {
      // 读取原始 ushort 值
      const val = this.readShort(buffer, offset);
      // 按系数缩放
      return val / divisor;
    }
  }
};
</script>

<style scoped>
/* 根容器样式 */
.tqml-view { padding: 20px; background-color: #f0f2f5; }

/* [新增] 视图顶部控制栏，用于放置按钮组 */
.view-header-controls {
  display: flex;
  justify-content: flex-end; /* 使按钮组靠右 */
  margin-bottom: 15px;      /* 与下方卡片的间距 */
}

.box-card { margin-bottom: 20px; }
.card-header { display: flex; justify-content: space-between; align-items: center; }

/* 状态栏样式 (保持不变) */
.status-bar {
  display: flex;
  flex-wrap: wrap;
  gap: 20px;
  padding: 10px;
  background-color: #f8f8f8;
  border: 1px solid #e4e7ed;
  border-bottom: none; /* 移除底部边框，使其与表格无缝连接 */
  border-top-left-radius: 4px;
  border-top-right-radius: 4px;
}
.status-bar span {
  font-weight: bold;
  color: #606266;
  margin-right: 10px;
}
.status-bar .el-checkbox {
  margin: 0;
}

/* 表格样式 (保持不变) */
.el-table {
  /* 移除表格的顶部圆角，使其与状态栏贴合 */
  border-top-left-radius: 0;
  border-top-right-radius: 0;
}

/* 底部按钮栏 (保持不变) */
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