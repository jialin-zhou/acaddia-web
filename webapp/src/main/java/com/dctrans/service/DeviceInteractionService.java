package com.dctrans.service;

// import com.fazecast.jSerialComm.SerialPort; // 不再需要
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.Collections; // 用于返回空列表
import java.util.List;
import java.util.Map;
import java.util.StringJoiner;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;

/**
 * @class DeviceInteractionService
 * @brief (已修改) 负责与串口设备进行交互的核心服务类。
 * @details 由于采用 Web Serial API，此类不再处理实际的串口通信。
 * 相关的串口操作方法已被注释掉。
 * 保留框架以备将来可能添加的非串口服务逻辑。
 */
@Service
public class DeviceInteractionService {

    /* --- Web Serial API 替代了以下串口操作逻辑 --- */

    /*
    private final ReentrantLock serialOperationLock = new ReentrantLock();

    // --- Command Definitions ---
    private static final byte[] CMD_REQ_TQCS = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x23, (byte) 0xAC, 0x16};
    // ... 其他命令定义 ...
    private static final byte[] CMD_ACK = {(byte) 0xA2};

    public List<String> getAvailablePorts() {
        System.out.println("[Service] Scanning for available serial ports...");
        SerialPort[] ports = SerialPort.getCommPorts();
        List<String> portNames = Arrays.stream(ports)
                .map(SerialPort::getSystemPortName)
                .collect(Collectors.toList());
        System.out.println("[Service] Found ports: " + portNames);
        return portNames;
         return Collections.emptyList(); // 返回空列表，因为此方法不再有效
    }


    public byte[] connectAndFetchInitialData(Map<String, Object> settings) {
        // ... (原串口连接和命令序列逻辑) ...
         throw new UnsupportedOperationException("Serial operations moved to frontend (Web Serial API)");
    }


    public byte[] fetchAdCalculatedData(Map<String, Object> settings) {
        // ... (原获取 AD 数据逻辑) ...
         throw new UnsupportedOperationException("Serial operations moved to frontend (Web Serial API)");
    }


    private byte[] executeFullConnectionSequence(SerialPort port) {
       // ... (原命令序列执行逻辑) ...
        throw new UnsupportedOperationException("Serial operations moved to frontend (Web Serial API)");
    }


    private SerialPort openAndConfigurePort(Map<String, Object> settings) {
        // ... (原打开和配置串口逻辑) ...
        throw new UnsupportedOperationException("Serial operations moved to frontend (Web Serial API)");
    }


    private void closePort(SerialPort port) {
       // ... (原关闭串口逻辑) ...
        // No longer needed from backend
    }


    private byte calculateChecksum(byte[] dataBlock) {
       // 这个辅助函数如果协议解析仍在后端，可能有用，但现在在前端 acadia-protocol.js 实现
        int sum = 0;
        for (byte b : dataBlock) {
            sum = (sum + (b & 0xFF)) & 0xFF;
        }
        return (byte) sum;
    }


    private byte[] executeSingleCommand(SerialPort port, byte[] command, byte expectedResponseTelegramId) {
        // ... (原单命令执行和帧解析逻辑) ...
         throw new UnsupportedOperationException("Serial operations moved to frontend (Web Serial API)");
    }


    public byte[] sendAndReceiveData(Map<String, Object> settings, byte[] dataToSend, int readTimeoutMillis) {
       // ... (原通用收发逻辑) ...
        throw new UnsupportedOperationException("Serial operations moved to frontend (Web Serial API)");
    }

    private String toHexString(byte[] bytes) {
        // 这个辅助函数可能仍然有用，如果后端需要处理字节数组日志等
        if (bytes == null) return "null";
        StringJoiner joiner = new StringJoiner(" ");
        for (byte b : bytes) {
            joiner.add(String.format("%02X", b));
        }
        return joiner.toString();
    }
    */
    // 可以保留 toHexString 或其他非串口相关的辅助方法
    private String toHexString(byte[] bytes) {
        if (bytes == null) return "null";
        StringJoiner joiner = new StringJoiner(" ");
        for (byte b : bytes) {
            joiner.add(String.format("%02X", b));
        }
        return joiner.toString();
    }
}