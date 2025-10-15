package com.dctrans.service;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.StringJoiner;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;

@Service
public class DeviceInteractionService {

    private SerialPort activePort;
    private final BlockingQueue<byte[]> incomingDataQueue = new ArrayBlockingQueue<>(20);
    private final ReentrantLock serialOperationLock = new ReentrantLock();

    // --- Command Definitions ---
    private static final byte[] CMD_REQ_TQCS = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x23, (byte) 0xAC, 0x16};
    private static final byte[] CMD_REQ_ACAD = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x21, (byte) 0xAA, 0x16};
    private static final byte[] CMD_REQ_AD_CALC = {(byte) 0x68, 0x04, 0x04, (byte) 0x68, 0x00, 0x09, (byte) 0x80, 0x25, (byte) 0xAE, 0x16};
    private static final byte[] CMD_ACK = {(byte) 0xA2};

    public List<String> getAvailablePorts() {
        System.out.println("[Service] Scanning for available serial ports...");
        SerialPort[] ports = SerialPort.getCommPorts();
        List<String> portNames = Arrays.stream(ports)
                                     .map(SerialPort::getSystemPortName)
                                     .collect(Collectors.toList());
        System.out.println("[Service] Found ports: " + portNames);
        return portNames;
    }

    public byte[] connectAndFetchInitialData(Map<String, Object> settings) {
        System.out.println("[Service] Acquiring lock for connectAndFetch...");
        serialOperationLock.lock();
        try {
            System.out.println("[Service] Lock acquired. Starting connection process.");
            disconnect();

            String portName = (String) settings.get("portName");
            System.out.println("[Service] Attempting to get port: " + portName);
            SerialPort newPort = SerialPort.getCommPort(portName);

            int baudRate = settings.get("baudRate") instanceof Number ? ((Number) settings.get("baudRate")).intValue() : 9600;
            int dataBits = settings.get("dataBits") instanceof Number ? ((Number) settings.get("dataBits")).intValue() : 8;
            int stopBits = settings.get("stopBits") instanceof Number ? ((Number) settings.get("stopBits")).intValue() : 1;
            String parityStr = (String) settings.getOrDefault("parity", "None");
            int parity = "None".equalsIgnoreCase(parityStr) ? SerialPort.NO_PARITY : "Odd".equalsIgnoreCase(parityStr) ? SerialPort.ODD_PARITY : "Even".equalsIgnoreCase(parityStr) ? SerialPort.EVEN_PARITY : SerialPort.NO_PARITY;

            // **新增的详细日志**
            System.out.println("[Service] Configuring port with the following parameters:");
            System.out.println("  - Baud Rate: " + baudRate);
            System.out.println("  - Data Bits: " + dataBits);
            System.out.println("  - Stop Bits: " + stopBits);
            System.out.println("  - Parity: " + parityStr + " (" + parity + ")");

            newPort.setBaudRate(baudRate);
            newPort.setNumDataBits(dataBits);
            newPort.setNumStopBits(stopBits);
            newPort.setParity(parity);

            System.out.println("[Service] Port configured. Attempting to open...");
            if (!newPort.openPort()) {
                throw new RuntimeException("无法打开串口: " + portName);
            }
            System.out.println("[Service] Port opened successfully.");

            this.activePort = newPort;
            System.out.println("[Service] Active port assigned. Adding data listener...");

            this.activePort.addDataListener(new SerialPortDataListener() {
                @Override
                public int getListeningEvents() { return SerialPort.LISTENING_EVENT_DATA_AVAILABLE; }

                @Override
                public void serialEvent(SerialPortEvent event) {
                    if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) return;
                    SerialPort comPort = event.getSerialPort();
                    byte[] newData = new byte[comPort.bytesAvailable()];
                    comPort.readBytes(newData, newData.length);
                    System.out.println("[Listener] Data received: " + toHexString(newData));
                    incomingDataQueue.offer(newData);
                }
            });
            System.out.println("[Service] Data listener added. Fetching initial data...");
            return _internalFetchAdData();

        } finally {
            System.out.println("[Service] Releasing lock for connectAndFetch.");
            serialOperationLock.unlock();
        }
    }

    // ... (其他方法保持不变)
    public void disconnect() {
        if (this.activePort != null && this.activePort.isOpen()) {
            System.out.println("[Service] Disconnecting port: " + this.activePort.getSystemPortName());
            this.activePort.removeDataListener();
            this.activePort.closePort();
        }
        this.activePort = null;
    }

    public boolean isConnected() {
        return this.activePort != null && this.activePort.isOpen();
    }

    public byte[] fetchAdCalculatedData() {
        System.out.println("[Service] Acquiring lock for manual fetch...");
        serialOperationLock.lock();
        try {
            System.out.println("[Service] Lock acquired. Starting manual fetch.");
            if (!isConnected()) {
                throw new IllegalStateException("串口未连接。");
            }
            return _internalFetchAdData();
        } finally {
            System.out.println("[Service] Releasing lock for manual fetch.");
            serialOperationLock.unlock();
        }
    }

    private byte[] _internalFetchAdData() {
        System.out.println("[Service-Internal] Clearing data queue and starting command sequence.");
        incomingDataQueue.clear();
        System.out.println("[Service-Internal] Step 1: Requesting TQCS...");
        executeCommand(CMD_REQ_TQCS, (byte) 0x22);
        System.out.println("[Service-Internal] Step 2: Requesting ACAD...");
        executeCommand(CMD_REQ_ACAD, (byte) 0x20);
        System.out.println("[Service-Internal] Step 3: Requesting AD Calculated Data...");
        byte[] adData = executeCommand(CMD_REQ_AD_CALC, (byte) 0x24);
        System.out.println("[Service-Internal] Command sequence complete. Returning AD data.");
        return adData;
    }

    private byte[] executeCommand(byte[] command, byte expectedResponseTelegramId) {
        try {
            if (!isConnected()) {
                throw new IllegalStateException("尝试写入时发现串口未连接。");
            }
            System.out.println("  [Exec] Sending command: " + toHexString(command));
            int bytesWritten = activePort.writeBytes(command, command.length);
            if (bytesWritten != command.length) {
                throw new RuntimeException("串口写入失败。");
            }

            System.out.println("  [Exec] Waiting for response (ID: " + String.format("0x%02X", expectedResponseTelegramId) + ")...");
            byte[] response = incomingDataQueue.poll(2, TimeUnit.SECONDS);
            if (response == null) {
                throw new RuntimeException("等待响应超时");
            }
            System.out.println("  [Exec] Got response: " + toHexString(response));

            if (response.length < 4 || response[3] != expectedResponseTelegramId) {
                throw new RuntimeException("收到无效的响应报文ID。");
            }

            System.out.println("  [Exec] Response ID OK. Sending ACK (0xA2).");
            activePort.writeBytes(CMD_ACK, CMD_ACK.length);

            int payloadLength = response[1] - 1;
            if (response.length < 4 + payloadLength) {
                 throw new RuntimeException("响应包不完整。");
            }
            byte[] payload = Arrays.copyOfRange(response, 4, 4 + payloadLength);
            System.out.println("  [Exec] Command successful. Payload extracted.");
            return payload;

        } catch (Exception e) {
            System.err.println("  [Exec] ERROR during command execution: " + e.getMessage());
            throw new RuntimeException("执行指令失败: " + e.getMessage(), e);
        }
    }

    private String toHexString(byte[] bytes) {
        if (bytes == null) return "null";
        StringJoiner joiner = new StringJoiner(" ");
        for (byte b : bytes) {
            joiner.add(String.format("%02X", b));
        }
        return joiner.toString();
    }
}
