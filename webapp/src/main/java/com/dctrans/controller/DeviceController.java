package com.dctrans.controller;

import com.dctrans.service.DeviceInteractionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/device")
@CrossOrigin(origins = "*", allowedHeaders = "*", methods = {RequestMethod.GET, RequestMethod.POST, RequestMethod.PUT, RequestMethod.DELETE, RequestMethod.OPTIONS})
public class DeviceController {

    private final DeviceInteractionService deviceInteractionService;

    @Autowired
    public DeviceController(DeviceInteractionService deviceInteractionService) {
        this.deviceInteractionService = deviceInteractionService;
    }

    /**
     * @brief (新增) 获取系统上所有可用的串口列表。
     * @return 一个包含串口名称的字符串列表。
     */
    @GetMapping("/list-ports")
    public ResponseEntity<List<String>> listPorts() {
        return ResponseEntity.ok(deviceInteractionService.getAvailablePorts());
    }

    @PostMapping("/connect")
    public ResponseEntity<?> connect(@RequestBody Map<String, Object> settings) {
        System.out.println("[Controller] Received /connect request with settings: " + settings);
        try {
            byte[] initialAdData = deviceInteractionService.connectAndFetchInitialData(settings);
            System.out.println("[Controller] /connect successful, returning data.");
            return ResponseEntity.ok(initialAdData);
        } catch (Throwable t) {
            System.err.println("[Controller] FATAL ERROR during /connect:");
            t.printStackTrace();
            return ResponseEntity.status(500).body(Map.of("error", "操作失败: " + t.getMessage()));
        }
    }

    @PostMapping("/disconnect")
    public ResponseEntity<Map<String, String>> disconnect() {
        System.out.println("[Controller] Received /disconnect request.");
        deviceInteractionService.disconnect();
        return ResponseEntity.ok(Map.of("message", "连接已断开"));
    }

    @GetMapping("/ad-data")
    public ResponseEntity<?> getAdData() {
        System.out.println("[Controller] Received /ad-data request.");
        try {
            if (!deviceInteractionService.isConnected()) {
                System.err.println("[Controller] Error: /ad-data called but not connected.");
                return ResponseEntity.status(400).body(Map.of("error", "串口未连接，请先连接设备。"));
            }
            byte[] adData = deviceInteractionService.fetchAdCalculatedData();
            System.out.println("[Controller] /ad-data successful, returning data.");
            return ResponseEntity.ok(adData);
        } catch (Throwable t) {
            System.err.println("[Controller] FATAL ERROR during /ad-data:");
            t.printStackTrace();
            return ResponseEntity.status(500).body(Map.of("error", "获取 AD 数据失败: " + t.getMessage()));
        }
    }
}
