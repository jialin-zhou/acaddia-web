package com.dctrans.service;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @class DeviceInteractionService
 * @brief 负责管理与硬件设备的串口通信的核心服务。
 *
 * 该服务实现了与设备交互的完整协议，包括连接、断开以及执行“请求-响应-确认”的指令序列。
 * 它使用线程锁来保证串口操作的原子性，并使用阻塞队列来同步处理传入的串口数据，确保在 web 环境下稳定可靠。
 */
@Service
public class DeviceInteractionService {

    private SerialPort activePort;
    private final BlockingQueue<byte[]> incomingDataQueue = new ArrayBlockingQueue<>(20);
    private final ReentrantLock serialOperationLock = new ReentrantLock();

    // --- 指令字节码定义 ---
    // 根据 C++ 源代码分析得出的固定指令。校验和已预先计算。
    private static final byte[] CMD_REQ_TQCS = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x23, (byte) 0xAC, 0x16};
    private static final byte[] CMD_REQ_ACAD = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x21, (byte) 0xAA, 0x16};
    private static final byte[] CMD_REQ_AD_CALC = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x25, (byte) 0xAE, 0x16};
    private static final byte[] CMD_ACK = {(byte) 0xA2};

    /**
     * @brief 连接到指定的串口。
     * @param settings 包含串口配置的 Map (port, baudRate, etc.)。
     * @return 如果成功建立连接并设置监听器，返回 true；否则返回 false。
     */
    public boolean connect(Map<String, Object> settings) {
        // 确保任何先前的连接都已关闭
        disconnect();

        String portName = (String) settings.get("port");
        SerialPort newPort = SerialPort.getCommPort(portName);

        // 从 settings Map 中解析参数
        newPort.setBaudRate(((Number) settings.get("baudRate")).intValue());
        newPort.setNumDataBits(((Number) settings.get("dataBits")).intValue());
        newPort.setNumStopBits(((Number) settings.get("stopBits")).intValue());

        String parityStr = (String) settings.get("parity");
        int parity = "None".equalsIgnoreCase(parityStr) ? SerialPort.NO_PARITY :
                     "Odd".equalsIgnoreCase(parityStr) ? SerialPort.ODD_PARITY :
                     "Even".equalsIgnoreCase(parityStr) ? SerialPort.EVEN_PARITY : SerialPort.NO_PARITY;
        newPort.setParity(parity);

        // 设置读取超时，以非阻塞模式工作
        newPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);

        if (newPort.openPort()) {
            newPort.addDataListener(new SerialPortDataListener() {
                @Override
                public int getListeningEvents() {
                    return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
                }

                @Override
                public void serialEvent(SerialPortEvent event) {
                    if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) return;
                    byte[] newData = new byte[activePort.bytesAvailable()];
                    activePort.readBytes(newData, newData.length);
                    // 将收到的数据块放入队列，供消费者线程处理
                    incomingDataQueue.offer(newData);
                }
            });
            this.activePort = newPort;
            return true;
        }
        return false;
    }

    /**
     * @brief 断开当前活动的串口连接。
     */
    public void disconnect() {
        if (this.activePort != null && this.activePort.isOpen()) {
            this.activePort.removeDataListener();
            this.activePort.closePort();
        }
        this.activePort = null;
    }

    /**
     * @brief 检查串口是否已连接。
     * @return 如果端口对象存在且已打开，返回 true。
     */
    public boolean isConnected() {
        return this.activePort != null && this.activePort.isOpen();
    }

    /**
     * @brief 获取 AD 计算值。
     * 此方法执行一个完整的指令序列来从设备获取数据。
     * @return 包含 AD 计算结果的原始字节数组。
     * @throws RuntimeException 如果任何步骤失败或超时。
     */
    public byte[] fetchAdCalculatedData() {
        // 使用锁确保此序列操作的原子性，防止多线程冲突
        if (!serialOperationLock.tryLock()) {
            throw new IllegalStateException("串口正在执行其他操作，请稍后再试。");
        }
        try {
            // 在开始新的指令序列前，清空队列中可能存在的旧数据
            incomingDataQueue.clear();

            // 步骤 1: 请求 TQCS 参数 (报文号 35 -> 响应 34/0x22)
            executeCommand(CMD_REQ_TQCS, (byte) 0x22);

            // 步骤 2: 请求 ACAD 参数 (报文号 33 -> 响应 32/0x20)
            executeCommand(CMD_REQ_ACAD, (byte) 0x20);

            // 步骤 3: 请求 AD 计算值 (报文号 37 -> 响应 36/0x24)
            byte[] adDataPayload = executeCommand(CMD_REQ_AD_CALC, (byte) 0x24);

            // 返回我们真正需要的数据负载
            return adDataPayload;

        } finally {
            serialOperationLock.unlock();
        }
    }

    /**
     * @brief 执行单次“发送-等待-确认”的命令。
     * @param command 要发送的指令字节数组。
     * @param expectedResponseTelegramId 期望收到的响应报文中的报文ID（通常是第4个字节）。
     * @return 从响应中提取的数据负载 (payload)。
     * @throws RuntimeException 如果写入失败、超时或收到意外的响应。
     */
    private byte[] executeCommand(byte[] command, byte expectedResponseTelegramId) {
        // 1. 发送指令
        int bytesWritten = activePort.writeBytes(command, command.length);
        if (bytesWritten != command.length) {
            throw new RuntimeException("串口写入失败，指令未完全发送。");
        }

        // 2. 等待响应
        try {
            // 从队列中获取数据，最多等待2秒
            byte[] response = incomingDataQueue.poll(2, TimeUnit.SECONDS);
            if (response == null) {
                throw new RuntimeException("等待响应超时 (指令: " + command[7] + ")");
            }

            // 3. 验证响应 (这是一个简化的验证，实际协议可能更复杂)
            // C++ 代码显示响应报文的第4个字节 (index 3) 是报文ID。
            if (response.length < 4 || response[3] != expectedResponseTelegramId) {
                throw new RuntimeException("收到无效的响应。期望报文ID: " + expectedResponseTelegramId + ", 收到: " + (response.length > 3 ? response[3] : "N/A"));
            }

            // 4. 发送确认 (ACK)
            activePort.writeBytes(CMD_ACK, CMD_ACK.length);

            // 5. 提取并返回数据负载
            // 根据 C++ 代码分析，数据负载位于固定的偏移量之后。
            // 响应格式: [start, len, len, id, ...payload..., checksum, end]
            // 负载从索引 4 开始，长度为 len - 1 (len 在索引 1 和 2)。
            int payloadLength = response[1] - 1;
            if (response.length < 4 + payloadLength) {
                 throw new RuntimeException("响应包不完整，无法提取数据负载。");
            }
            return Arrays.copyOfRange(response, 4, 4 + payloadLength);

        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException("等待串口响应时被中断", e);
        }
    }
}
