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
// --- 命令定义 (基于 C++: Dlg_TQML.cpp 协议) ---
// "同期开出" (复位/执行): 发送 0x2C (44), 期望响应 0xE5 (ACK)
const CMD_TQML_EXEC = { stationAddr: 0, telegramNr: 0x2C, expectedResponseId: 0xE5 };
// "信息读取": 发送 0x2D (45), 期望响应 0x2E (46, 数据报文)
const CMD_TQML_FETCH = { stationAddr: 0, telegramNr: 0x2D, expectedResponseId: 0x2E };

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
     * 当父组件接收到 0x2E 响应时，会更新这个 prop，触发 watch。
     */
    tqmlRawData: { type: Array, default: null },
  },
  data() {
    return {
      // 对应 C++: m_nTQML_REC 变量 (0=Rec, 1=Sent, 2=Time).
      // 1. 控制 RadioButton 的选中状态
      // 2. 决定 "信息读取" 时发送的 Payload (1, 2, 或 3)
      // 3. 决定解析后的数据归属
      mode: 'received',

      // 对应 C++: m_BOOL... 系列标志位
      // 控制状态栏复选框的显示
      status: {
        reset: false,      // 复位
        unfinished: false, // 未完成
        rec_ok: false,     // 接收数据有效
        sent_ok: false,    // 发送数据有效
        time_ok: false,    // 时刻数据有效
      },

      // 对应 C++: m_floatTQML_... 系列数组
      // 核心数据存储，按“列”存储三组浮点数数据
      dataStore: {
        received: this.createDataGroup(),
        sent: this.createDataGroup(),
        timed: this.createDataGroup(),
      },

      // 对应 C++: m_DateTimeTQML_... 系列变量
      // 存储三组数据对应的时间对象
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
     * [核心数据转换]
     * 将 dataStore (按列存储: received/sent/timed) 转换为 el-table 所需的行数据格式。
     * 每一行包含：标签(Label)、单位、以及该参数在三种模式下的具体数值。
     */
    tableData() {
      // 定义表格行的元数据 (键名、显示标签、类型)
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

      // 映射生成每一行的数据对象
      return labels.map(item => {
        // 特殊处理日期行
        if (item.type === 'datetime') {
          return {
            ...item,
            receivedValue: this.dateTimeStore.received,
            sentValue: this.dateTimeStore.sent,
            timedValue: this.dateTimeStore.timed,
          }
        }
        // 处理普通数值行
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
     * 监听来自 App.vue 的 `tqmlRawData` (0x2E 响应报文)。
     * 这是设备数据的入口点。
     */
    tqmlRawData(newData) {
      if (newData && newData.length > 0) {
        console.log("TqmlView received tqmlRawData (0x2E):", newData);
        // 执行数据解析
        this.parseTqmlData(newData);
      }
    }
  },
  methods: {
    /**
     * @vuese
     * "同期开出" 按钮点击事件。
     * 功能：向设备发送复位指令。
     * 协议：CMD 0x2C, Payload 0x55 0xAA
     */
    async onExecute() {
      this.$message.info('正在发送 "同期开出" (复位) 命令 (0x2C)...');

      // 对应 C++: ValidDataToPack[0]=0x55, ValidDataToPack[1]=0xaa
      // 这是一个协议规定的固定魔数 (Magic Number)
      const payload = new Uint8Array([0x55, 0xAA]);

      try {
        await this.sendCommand({ commandDef: CMD_TQML_EXEC, payload: payload });
        // 注意：E5 (ACK) 响应由 App.vue 全局处理，此处不触发 data update
        this.$message.success('"同期开出" 命令已发送，等待 E5 确认');
      } catch (error) {
        this.$message.error(`"同期开出" 命令发送失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * "信息读取" 按钮点击事件。
     * 功能：根据当前选中的模式，读取对应的数据记录。
     * 协议：CMD 0x2D, Payload [1|2|3]
     */
    async onFetch() {
      let payloadByte;
      // 将 UI 模式映射为协议需要的 ID
      // 1: 接收到的命令数据 (Received)
      // 2: 发出的合闸命令数据 (Sent)
      // 3: 合闸时刻数据 (Timed)
      switch (this.mode) {
        case 'received': payloadByte = 1; break;
        case 'sent': payloadByte = 2; break;
        case 'timed': payloadByte = 3; break;
        default: payloadByte = 1;
      }

      this.$message.info(`正在读取 "Mode: ${this.mode}" (ID: ${payloadByte}) 的信息 (0x2D)...`);

      // 构造 1 字节负载
      const payload = new Uint8Array([payloadByte]);

      try {
        await this.sendCommand({ commandDef: CMD_TQML_FETCH, payload: payload });
        // 发送成功后，等待设备返回 0x2E 报文，触发 watch.tqmlRawData
      } catch (error) {
        this.$message.error(`"信息读取" 命令发送失败: ${error?.message || error}`);
      }
    },

    /**
     * @vuese
     * [核心解析逻辑]
     * 解析 0x2E 响应报文 Payload。
     * 移植自 C++: Dlg_TQML::parseData()
     * * 逻辑分支：
     * 1. Type 4 (Reset): 仅 1 字节 payload，表示复位成功。
     * 2. Type 5 (Unfinished): 仅 1 字节 payload，表示操作未完成。
     * 3. Type 1/2/3: 完整数据包 (约 27 字节)，包含日期、时间及各项电气参数。
     * * @param {number[]} buffer - 响应数据的 Payload 部分
     */
    parseTqmlData(buffer) {
      // 1. 基础校验
      if (!buffer || buffer.length < 1) {
        console.warn(`TQML parse failed: buffer is null or empty.`, buffer);
        this.$message.error('解析 TQML 数据失败：收到空响应');
        return;
      }

      try {
        // 2. 获取记录类型 (Payload 的第 0 字节)
        // C++ 对应 ValidData[4]
        const recordType = buffer[0];

        // 每次解析前重置所有状态标志
        this.status.reset = false;
        this.status.unfinished = false;
        this.status.rec_ok = false;
        this.status.sent_ok = false;
        this.status.time_ok = false;

        // 3. 处理特殊状态响应 (Type 4 & 5)
        // 这是一个重要的修复：C++ 原代码可能忽略了这里的长度差异
        if (recordType === 4) { // 复位确认
          this.status.reset = true;
          this.resetDataFields(); // 清空界面显示
          this.$message.info('收到设备复位确认 (无数据)');
          return;
        }
        if (recordType === 5) { // 未完成
          this.status.unfinished = true;
          this.resetDataFields(); // 清空界面显示
          this.$message.warning('设备报告：未完成 (无数据)');
          return;
        }

        // 4. 处理数据响应 (Type 1, 2, 3) - 校验长度
        // 需要至少 27 字节 (C++ ValidData 5~31)
        if (buffer.length < 27) {
          console.warn(`TQML parse failed: buffer length ${buffer.length} < 27 for data record type ${recordType}.`, buffer);
          this.$message.error('解析 TQML 数据失败：响应数据格式不正确');
          return;
        }

        // 5. 解析数据字段
        // 注意：readFloat 的第三个参数是除数，用于将整数还原为浮点数

        // 解析日期和毫秒 (Offset 1: Days, Offset 3: MS)
        const dt = this.parseDateTime(buffer, 1, 3);

        const u1 = this.readFloat(buffer, 7, 100.0);   // U1 电压
        const u2 = this.readFloat(buffer, 9, 100.0);   // U2 电压
        const f1 = this.readFloat(buffer, 11, 1000.0); // f1 频率
        const f2 = this.readFloat(buffer, 13, 1000.0); // f2 频率
        const f1_dt = this.readFloat(buffer, 15, 100.0); // f1 变化率
        const f2_dt = this.readFloat(buffer, 17, 100.0); // f2 变化率
        const du = this.readFloat(buffer, 19, 100.0);  // 电压差
        const df = this.readFloat(buffer, 21, 1000.0); // 频率差
        const df_dt = this.readFloat(buffer, 23, 100.0); // 滑差
        const da = this.readFloat(buffer, 25, 100.0);  // 相角差

        // 组装用于 UI 显示的数据对象 (保留小数位)
        const dataGroup = {
          ms: dt.ms, // 毫秒部分单独显示
          u1: u1.toFixed(2), f2: f2.toFixed(3), f1_dt: f1_dt.toFixed(2),
          u2: u2.toFixed(2), df: df.toFixed(3), f2_dt: f2_dt.toFixed(2),
          f1: f1.toFixed(3), da: da.toFixed(2), df_dt: df_dt.toFixed(2),
          du: du.toFixed(2),
        };

        // 6. 根据类型更新对应的数据槽位
        if (recordType === 1) { // 接收(Rec)
          this.dataStore.received = dataGroup;
          this.dateTimeStore.received = dt.date;
          this.status.rec_ok = true;
          this.mode = 'received'; // 自动切换 UI Tab
          this.$message.success('已更新 "接收(Rec)" 数据');
        } else if (recordType === 2) { // 发送(Sent)
          this.dataStore.sent = dataGroup;
          this.dateTimeStore.sent = dt.date;
          this.status.sent_ok = true;
          this.mode = 'sent';
          this.$message.success('已更新 "发送(Sent)" 数据');
        } else if (recordType === 3) { // 时刻(Time)
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
     * 重置所有 UI 数据字段为初始状态 (0 或 null)
     */
    resetDataFields() {
      this.dataStore.received = this.createDataGroup();
      this.dataStore.sent = this.createDataGroup();
      this.dataStore.timed = this.createDataGroup();
      this.dateTimeStore.received = null;
      this.dateTimeStore.sent = null;
      this.dateTimeStore.timed = null;
    },

    /**
     * @vuese
     * 创建一组全 0 的初始数据结构
     */
    createDataGroup() {
      return {
        ms: 0, u1: 0, u2: 0, f1: 0, f2: 0, f1_dt: 0, f2_dt: 0,
        du: 0, df: 0, df_dt: 0, da: 0
      };
    },

    /**
     * @vuese
     * [时间解析算法]
     * 协议使用自定义的时间格式：
     * 1. 天数：基于 1984-01-01 的天数偏移量 (Days Offset)。
     * 2. 毫秒：当天的毫秒数 (0 - 86,400,000)。
     * * @param {number[]} buffer - payload 缓冲区
     * @param {number} dayOffset - 天数起始索引
     * @param {number} msOffset - 毫秒数起始索引
     */
    parseDateTime(buffer, dayOffset, msOffset) {
      // 1. 读取天数 (2字节 short)
      const days = this.readShort(buffer, dayOffset);

      // 2. 读取毫秒数 (4字节 int)
      const ms = buffer[msOffset] |
          (buffer[msOffset + 1] << 8) |
          (buffer[msOffset + 2] << 16) |
          (buffer[msOffset + 3] << 24);

      // 3. 计算基准日期 (1984-01-01 UTC)
      const baseDate = new Date(Date.UTC(1984, 0, 1));

      // 4. 加上天数偏移 (Days * ms/day)
      const targetTimestamp = baseDate.getTime() + days * (24 * 60 * 60 * 1000);

      // 5. 构造最终 Date 对象
      const date = new Date(targetTimestamp);
      date.setUTCHours(0, 0, 0, 0); // 重置到当天 0点 UTC
      date.setUTCMilliseconds(ms);  // 加上协议中的毫秒数
      // 注意：生成的 date 对象在 UI 显示时会自动根据浏览器时区转换为本地时间

      return {
        date: date,     // 完整 Date 对象，给 el-date-picker
        ms: ms % 1000   // 提取毫秒部分 (0-999)，给 'ms' 列
      };
    },

    /**
     * @vuese
     * 读取 16 位小端整数 (Little-Endian Short)
     */
    readShort(buffer, offset) {
      if (offset + 1 >= buffer.length) throw new Error("Read short: offset out of bounds");
      return buffer[offset] | (buffer[offset + 1] << 8);
    },

    /**
     * @vuese
     * 读取定点小数：读取 Short 整数并除以指定系数转换为 Float
     */
    readFloat(buffer, offset, divisor) {
      const val = this.readShort(buffer, offset);
      return val / divisor;
    }
  }
};
</script>

<style scoped>
/* 样式部分保持不变，增加了布局说明注释 */

/* 根容器 */
.tqml-view { padding: 20px; background-color: #f0f2f5; }

/* 顶部控制栏 (单选按钮组) */
.view-header-controls {
  display: flex;
  justify-content: flex-end;
  margin-bottom: 15px;
}

.box-card { margin-bottom: 20px; }
.card-header { display: flex; justify-content: space-between; align-items: center; }

/* 状态栏 (复选框组) */
.status-bar {
  display: flex;
  flex-wrap: wrap;
  gap: 20px;
  padding: 10px;
  background-color: #f8f8f8;
  border: 1px solid #e4e7ed;
  border-bottom: none; /* 与表格顶部无缝连接 */
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

/* 表格微调 */
.el-table {
  border-top-left-radius: 0; /* 移除圆角以贴合状态栏 */
  border-top-right-radius: 0;
}

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