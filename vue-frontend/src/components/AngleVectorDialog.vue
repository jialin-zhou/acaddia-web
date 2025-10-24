<template>
  <el-dialog
      v-model="dialogVisible"
      title="角度矢量设置"
      width="550px"
      @close="onCancel"
  >
    <el-form
        :model="form"
        label-width="80px"
        label-position="left"
    >
      <el-row :gutter="20">
        <el-col :span="12">
          <el-card
              shadow="never"
              header="Line 1"
          >
            <el-form-item
                v-for="(label, key) in line1Labels"
                :key="key"
                :label="label"
            >
              <el-input v-model="form.line1[key]">
                <template #append>
                  °
                </template>
              </el-input>
            </el-form-item>
          </el-card>
        </el-col>

        <el-col :span="12">
          <el-card
              shadow="never"
              header="Line 2"
          >
            <el-form-item
                v-for="(label, key) in line2Labels"
                :key="key"
                :label="label"
            >
              <el-input v-model="form.line2[key]">
                <template #append>
                  °
                </template>
              </el-input>
            </el-form-item>
          </el-card>
        </el-col>
      </el-row>

      <el-row
          justify="center"
          style="margin-top: 20px;"
      >
        <el-col :span="12">
          <el-form-item label="▲α">
            <el-input v-model="form.deltaAlpha">
              <template #append>
                °
              </template>
            </el-input>
          </el-form-item>
        </el-col>
      </el-row>
    </el-form>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="onFetch">
          获取角度
        </el-button>
        <div class="spacer" />
        <el-button @click="onCancel">
          退出
        </el-button>
        </span>
    </template>
  </el-dialog>
</template>

<script>
export default {
  name: 'AngleVectorDialog',
  props: {
    visible: { type: Boolean, default: false },
    /**
     * @vuese
     * (新增) 从 App.vue 传入的设备角度原始字节数组 (来自 0x30 响应)。
     * 期望格式: number[] 或 null
     */
    deviceAngleRawData: { type: Array, default: null },
  },
  emits: ['update:visible', 'fetch'],
  data() {
    return {
      form: {
        line1: { ua: '0', ub: '0', uc: '0', ia: '0', ib: '0', ic: '0' },
        line2: { ua: '0', ub: '0', uc: '0', ia: '0', ib: '0', ic: '0' },
        deltaAlpha: '0'
      },
      line1Labels: { ua: 'UA', ub: 'UB', uc: 'UC', ia: 'IA', ib: 'IB', ic: 'IC' },
      line2Labels: { ua: 'UA', ub: 'UB', uc: 'UC', ia: 'IA', ib: 'IB', ic: 'IC' },
    };
  },
  computed: {
    dialogVisible: {
      get() { return this.visible; },
      set(value) { this.$emit('update:visible', value); }
    }
  },
  watch: {
    /**
     * @vuese
     * (新增) 监听来自 App.vue 的原始角度数据。
     */
    deviceAngleRawData(newData) {
      // (修改) 检查 payload 长度 >= 26 (根据 C++ 代码，需要读取到索引 25)
      if (newData && newData.length >= 26) {
        try {
          this.parseDeviceAngleData(newData);
          this.$message.success('设备角度已更新');
        } catch(e) {
          console.error("解析设备角度失败:", e);
          this.$message.error(`解析设备角度失败: ${e.message}`);
          this.resetForm(); // 解析失败则重置表单
        }
      } else if (newData) { // newData 存在但长度不足 26
        console.warn("收到的设备角度数据长度不足 (需要 >= 26):", newData);
        this.$message.warning('收到的设备角度数据格式不正确'); // 现在这个消息只会在长度确实不足时显示
        this.resetForm();
      }
    }
  },
  methods: {
    onCancel() {
      this.dialogVisible = false;
    },
    onFetch() {
      this.$emit('fetch');
    },

    /**
     * @vuese
     * (修改) 解析从设备接收到的原始角度数据 (number[])。
     * @param {number[]} rawData - 包含角度信息的字节数组 (来自 0x30 响应的 payload)。
     */
    parseDeviceAngleData(rawData) {
      console.log("rawData");
      console.log(rawData);
      // 辅助函数：从 payload 指定偏移量读取2字节小端数据并计算角度值
      const getValue = (offset) => {
        // (新增) 边界检查
        if (offset < 0 || offset + 1 >= rawData.length) {
          console.error(`Angle parse error: Index out of bounds. Offset=${offset}, Length=${rawData.length}`);
          throw new Error(`解析角度数据时索引越界 (offset=${offset})`);
          // return 'ERR'; // 或者返回错误标记
        }
        const lowByte = rawData[offset];
        const highByte = rawData[offset + 1];
        // 确保是数字
        if (typeof lowByte !== 'number' || typeof highByte !== 'number') {
          console.error(`Angle parse error: Invalid data type at offset ${offset}. low=${lowByte}, high=${highByte}`);
          throw new Error(`解析角度数据时遇到非数字类型 (offset=${offset})`);
          // return 'ERR';
        }
        const rawValue = lowByte | (highByte << 8);
        return (rawValue / 100.0).toFixed(2); // 保留两位小数
      };

      // 提取数据 (payload 索引 = C++ ValidData 索引 - 4)
      this.form.line1.ua = getValue(0);  // C++ index 4
      this.form.line1.ub = getValue(2);  // C++ index 6
      this.form.line1.uc = getValue(4);  // C++ index 8
      this.form.line1.ia = getValue(6);  // C++ index 10
      this.form.line1.ib = getValue(8);  // C++ index 12
      this.form.line1.ic = getValue(10); // C++ index 14

      this.form.line2.ua = getValue(12); // C++ index 16
      this.form.line2.ub = getValue(14); // C++ index 18
      this.form.line2.uc = getValue(16); // C++ index 20
      this.form.line2.ia = getValue(18); // C++ index 22
      this.form.line2.ib = getValue(20); // C++ index 24
      this.form.line2.ic = getValue(22); // C++ index 26

      this.form.deltaAlpha = getValue(24); // C++ index 28

      console.log("Parsed device angles:", JSON.parse(JSON.stringify(this.form)));
    },
    /**
     * @vuese
     * (新增) 重置表单为初始值。
     */
    resetForm() {
      this.form = {
        line1: { ua: '0', ub: '0', uc: '0', ia: '0', ib: '0', ic: '0' },
        line2: { ua: '0', ub: '0', uc: '0', ia: '0', ib: '0', ic: '0' },
        deltaAlpha: '0'
      };
    }
  }
};
</script>

<style scoped>
.dialog-footer {
  display: flex;
  width: 100%;
}
.spacer {
  flex-grow: 1;
}
.el-card {
  height: 100%;
}
/* 调整 Form Item 间距使其更紧凑 */
.el-form-item {
  margin-bottom: 10px;
}
</style>