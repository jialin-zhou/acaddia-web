package com.dctrans.config;

import com.dctrans.controller.SerialPortWebSocketHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;

@Configuration
@EnableWebSocket
public class RawWebSocketConfig implements WebSocketConfigurer {

    @Autowired
    private SerialPortWebSocketHandler serialPortWebSocketHandler;

    @Override
    public void registerWebSocketHandlers(WebSocketHandlerRegistry registry) {
        // Registers the raw WebSocket handler for the serial port service
        // on a dedicated path to avoid conflicts with the STOMP endpoint.
        registry.addHandler(serialPortWebSocketHandler, "/serial-port").setAllowedOrigins("*");
    }
}
