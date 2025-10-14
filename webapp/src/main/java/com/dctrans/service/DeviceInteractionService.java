package com.dctrans.service;

import com.dctrans.protocol.TelegramProtocolService;
import com.dctrans.serial.SerialPortService;
import com.fazecast.jSerialComm.SerialPort;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Map;

@Service
public class DeviceInteractionService {

    private final SerialPortService serialPortService;
    private final TelegramProtocolService protocolService;
    private final SimpMessagingTemplate messagingTemplate;

    @Autowired
    public DeviceInteractionService(SerialPortService serialPortService,
                                  TelegramProtocolService protocolService,
                                  SimpMessagingTemplate messagingTemplate) {
        this.serialPortService = serialPortService;
        this.protocolService = protocolService;
        this.messagingTemplate = messagingTemplate;
    }

    // ... (existing connect, disconnect, etc. methods)
    public void connect(Map<String, Object> settings) {
        try {
            String port = (String) settings.get("port");
            int baudRate = ((Number) settings.get("baudRate")).intValue();
            int dataBits = ((Number) settings.get("dataBits")).intValue();
            int stopBits = ((Number) settings.get("stopBits")).intValue();
            String parityStr = (String) settings.get("parity");
            int parity = "None".equalsIgnoreCase(parityStr) ? SerialPort.NO_PARITY :
                         "Odd".equalsIgnoreCase(parityStr) ? SerialPort.ODD_PARITY :
                         "Even".equalsIgnoreCase(parityStr) ? SerialPort.EVEN_PARITY : SerialPort.NO_PARITY;

            boolean success = serialPortService.connect(port, baudRate, dataBits, stopBits, parity, this::handleIncomingSerialData);
            sendSerialStatusUpdate(success);
        } catch (Exception e) {
            System.err.println("Error parsing connection settings: " + e.getMessage());
            sendSerialStatusUpdate(false);
        }
    }

    public void disconnect() {
        serialPortService.disconnect();
        sendSerialStatusUpdate(false);
    }

    public void fetchAndSendAvailablePorts() {
        List<String> ports = serialPortService.getAvailablePorts();
        messagingTemplate.convertAndSend("/topic/status", Map.of("type", "available-ports", "payload", ports));
    }

    /**
     * Sets the time on the device (simulated).
     * @param timePayload The time string from the frontend.
     */
    public void setTime(String timePayload) {
        System.out.println("Attempting to set device time to: " + timePayload);
        // In a real application, you would pack this command and send it via serialPortService.write()
        // byte[] setTimeCommand = protocolService.pack(Map.of("setTime", timePayload));
        // serialPortService.write(setTimeCommand);

        // For now, we'll just send a success confirmation back to the frontend.
        Map<String, Object> response = Map.of(
            "type", "time-set-response",
            "payload", Map.of("success", true, "message", "Time set to " + timePayload)
        );
        messagingTemplate.convertAndSend("/topic/status", response);
    }

    /**
     * Fetches the current time (simulated from server) and sends it to the frontend.
     */
    public void fetchTime() {
        System.out.println("Fetching device time...");
        // In a real application, you would send a command to request the time and wait for a response.
        // For now, we'll use the server's current time.
        String currentTime = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));

        Map<String, Object> response = Map.of(
            "type", "time-fetch-response",
            "payload", Map.of("deviceTime", currentTime)
        );
        messagingTemplate.convertAndSend("/topic/status", response);
    }

    public void sendCommand(Object commandData) {
        if (!serialPortService.isConnected()) {
            messagingTemplate.convertAndSend("/topic/status", Map.of("type", "error", "payload", "Port not connected"));
            return;
        }
        byte[] dataFrame = protocolService.pack(commandData);
        serialPortService.write(dataFrame);
        pushRawDataToFrontend(dataFrame, "OUT");
    }

    private void handleIncomingSerialData(byte[] data) {
        pushRawDataToFrontend(data, "IN");
    }

    private void pushRawDataToFrontend(byte[] data, String direction) {
        Map<String, Object> message = Map.of(
            "direction", direction,
            "payload", data
        );
        messagingTemplate.convertAndSend("/topic/raw-data", message);
    }

    private void sendSerialStatusUpdate(boolean isConnected) {
        Map<String, Object> statusUpdate = Map.of("type", "serial-status", "payload", Map.of("connected", isConnected));
        messagingTemplate.convertAndSend("/topic/status", statusUpdate);
    }
}
