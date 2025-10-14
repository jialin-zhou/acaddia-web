package com.dctrans.controller;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fazecast.jSerialComm.SerialPort;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Component
public class SerialPortWebSocketHandler extends TextWebSocketHandler {

    private final ObjectMapper objectMapper = new ObjectMapper();

    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        System.out.println("WebSocket connection established from " + session.getRemoteAddress());
    }

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        try {
            JsonNode jsonNode = objectMapper.readTree(message.getPayload());
            String messageType = jsonNode.get("type").asText();

            if ("getPorts".equals(messageType)) {
                SerialPort[] commPorts = SerialPort.getCommPorts();
                List<String> portNames = new ArrayList<>();
                for (SerialPort port : commPorts) {
                    portNames.add(port.getSystemPortName());
                }

                Map<String, Object> response = new HashMap<>();
                response.put("type", "ports");
                response.put("ports", portNames);

                session.sendMessage(new TextMessage(objectMapper.writeValueAsString(response)));
            }
        } catch (IOException e) {
            System.err.println("Error processing WebSocket message: " + e.getMessage());
        }
    }
}
