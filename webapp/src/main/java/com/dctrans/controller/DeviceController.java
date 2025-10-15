package com.dctrans.controller;

import com.dctrans.service.DeviceInteractionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

/**
 * @class DeviceController
 * @brief 提供用于与硬件设备进行交互的 RESTful API 端点。
 *
 * 该控制器负责处理来自前端的 HTTP 请求，并将其委托给 DeviceInteractionService 来执行实际的串口通信操作。
 * 它遵循了将串口通信逻辑严格限制在后端的最佳实践，避免了前端直接访问硬件资源。
 */
@RestController
@RequestMapping("/api/device")
public class DeviceController {

    private final DeviceInteractionService deviceInteractionService;

    @Autowired
    public DeviceController(DeviceInteractionService deviceInteractionService) {
        this.deviceInteractionService = deviceInteractionService;
    }

    /**
     * @brief 连接到指定的串口。
     *
     * 前端通过此端点传递用户选择的串口参数（端口号、波特率等）。
     * 后端将尝试建立连接，并返回操作结果。
     *
     * @param settings 包含串口连接参数的 Map，例如：
     *                 {
     *                   "port": "COM3",
     *                   "baudRate": 9600,
     *                   "dataBits": 8,
     *                   "stopBits": 1,
     *                   "parity": "None"
     *                 }
     * @return 如果连接成功，返回 HTTP 200 OK；如果失败，返回 HTTP 500 Internal Server Error。
     */
    @PostMapping("/connect")
    public ResponseEntity<Map<String, Object>> connect(@RequestBody Map<String, Object> settings) {
        try {
            boolean success = deviceInteractionService.connect(settings);
            if (success) {
                return ResponseEntity.ok(Map.of("success", true, "message", "成功连接到 " + settings.get("port")));
            } else {
                return ResponseEntity.status(500).body(Map.of("success", false, "message", "无法连接到 " + settings.get("port")));
            }
        } catch (Exception e) {
            return ResponseEntity.status(500).body(Map.of("success", false, "message", "连接失败: " + e.getMessage()));
        }
    }

    /**
     * @brief 断开当前的串口连接。
     *
     * @return 返回操作结果。
     */
    @PostMapping("/disconnect")
    public ResponseEntity<Map<String, String>> disconnect() {
        deviceInteractionService.disconnect();
        return ResponseEntity.ok(Map.of("message", "连接已断开"));
    }

    /**
     * @brief 获取 AD (Analog-to-Digital) 计算值。
     *
     * 当被调用时，后端会通过已建立的串口连接，向设备发送一系列指令来请求 AD 数据。
     * 成功获取并解析后，将原始的字节数组作为 JSON 返回给前端。
     * 前端负责将这些原始数据进行最终的计算和格式化。
     *
     * @return 如果成功，返回包含原始 AD 数据的字节数组；如果失败（例如，串口未连接），返回错误信息。
     */
    @GetMapping("/ad-data")
    public ResponseEntity<?> getAdData() {
        if (!deviceInteractionService.isConnected()) {
            return ResponseEntity.status(400).body(Map.of("error", "串口未连接，请先连接设备。"));
        }
        try {
            byte[] adData = deviceInteractionService.fetchAdCalculatedData();
            return ResponseEntity.ok(adData);
        } catch (Exception e) {
            return ResponseEntity.status(500).body(Map.of("error", "获取 AD 数据失败: " + e.getMessage()));
        }
    }
}
