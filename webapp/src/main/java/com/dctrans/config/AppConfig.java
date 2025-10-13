package com.dctrans.config;

import com.dctrans.protocol.TelegramProtocolService;
import com.dctrans.serial.SerialPortService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class AppConfig {

    @Bean
    public SerialPortService serialPortService() {
        return new SerialPortService();
    }

    @Bean
    public TelegramProtocolService telegramProtocolService() {
        return new TelegramProtocolService();
    }
}
