package com.dctrans;

import com.fazecast.jSerialComm.SerialPort;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        // ** 诊断代码: 在 Spring 启动前强制加载 jSerialComm **
        System.out.println("--- [jSerialComm Pre-flight Check] ---");
        try {
            System.out.println("Attempting to list available serial ports directly...");
            SerialPort[] ports = SerialPort.getCommPorts();
            System.out.println("Found " + ports.length + " ports.");
            for (SerialPort port : ports) {
                System.out.println("  - " + port.getSystemPortName());
            }
            System.out.println("[jSerialComm Pre-flight Check] SUCCESS: Native library seems to be loaded correctly.");
        } catch (Throwable t) {
            System.err.println("[jSerialComm Pre-flight Check] FATAL ERROR: Failed to load or initialize jSerialComm native library.");
            t.printStackTrace();
            System.err.println("--- [jSerialComm Pre-flight Check] Application will now exit. ---");
            // 直接退出，因为没有原生库，后续所有操作都将失败。
            System.exit(1);
        }
        System.out.println("--- [Pre-flight Check Complete] ---");

        // 原有的 Spring Boot 启动代码
        SpringApplication.run(Application.class, args);
    }

}
