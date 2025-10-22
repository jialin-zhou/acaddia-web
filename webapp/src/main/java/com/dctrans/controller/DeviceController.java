package com.dctrans.controller;

import com.dctrans.service.DeviceInteractionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

/**
 * @class DeviceController
 * @brief 处理与串口设备交互相关的 HTTP 请求的 REST 控制器。
 * @details (已修改) 由于采用 Web Serial API，此类不再处理实际的串口通信。
 * 保留框架以备将来可能添加的非串口 API。
 */
@RestController
@RequestMapping("/api/device")
@CrossOrigin(origins = "*", allowedHeaders = "*", methods = {RequestMethod.GET, RequestMethod.POST, RequestMethod.PUT, RequestMethod.DELETE, RequestMethod.OPTIONS})
public class DeviceController {

    private final DeviceInteractionService deviceInteractionService;

    @Autowired
    public DeviceController(DeviceInteractionService deviceInteractionService) {
        // 依赖注入仍然保留，但 deviceInteractionService 可能不再被使用
        this.deviceInteractionService = deviceInteractionService;
    }

    /* --- Web Serial API 替代了以下接口 --- */

    /*
    @GetMapping("/list-ports")
    public ResponseEntity<List<String>> listPorts() {
        // 不再需要，由前端 navigator.serial 获取
        // return ResponseEntity.ok(deviceInteractionService.getAvailablePorts());
        return ResponseEntity.status(404).body(List.of("Endpoint deprecated: Use Web Serial API"));
    }

    @PostMapping("/connect")
    public ResponseEntity<?> connect(@RequestBody Map<String, Object> settings) {
        // 不再需要，由前端 port.open() 处理
        // try {
        //     byte[] initialAdData = deviceInteractionService.connectAndFetchInitialData(settings);
        //     List<Integer> jsonData = new ArrayList<>(initialAdData.length);
        //     for (byte b : initialAdData) {
        //         jsonData.add(Byte.toUnsignedInt(b));
        //     }
        //     return ResponseEntity.ok(jsonData);
        // } catch (Throwable t) {
        //     return ResponseEntity.status(500).body(Map.of("error", "操作失败: " + t.getMessage()));
        // }
         return ResponseEntity.status(404).body(Map.of("error", "Endpoint deprecated: Use Web Serial API"));
    }

    @PostMapping("/ad-data")
    public ResponseEntity<?> getAdData(@RequestBody Map<String, Object> settings) {
       // 不再需要，由前端通过 Web Serial API 发送命令获取
       // try {
       //     byte[] adData = deviceInteractionService.fetchAdCalculatedData(settings);
       //     List<Integer> jsonData = new ArrayList<>(adData.length);
       //     for (byte b : adData) {
       //         jsonData.add(Byte.toUnsignedInt(b));
       //     }
       //     return ResponseEntity.ok(jsonData);
       // } catch (Throwable t) {
       //     return ResponseEntity.status(500).body(Map.of("error", "获取 AD 数据失败: " + t.getMessage()));
       // }
        return ResponseEntity.status(404).body(Map.of("error", "Endpoint deprecated: Use Web Serial API"));
    }

    public static class SendReceiveRequest {
        public Map<String, Object> settings;
        public byte[] dataToSend;
        public int readTimeoutMillis = 500;
    }

    @PostMapping("/send-receive")
    public ResponseEntity<?> sendReceive(@RequestBody SendReceiveRequest request) {
       // 不再需要，由前端 port.writable 和 port.readable 处理
       // if (request.settings == null || request.dataToSend == null) {
       //     return ResponseEntity.badRequest().body(Map.of("error", "请求体缺少 'settings' 或 'dataToSend'"));
       // }
       // try {
       //     byte[] receivedData = deviceInteractionService.sendAndReceiveData(
       //             request.settings,
       //             request.dataToSend,
       //             request.readTimeoutMillis > 0 ? request.readTimeoutMillis : 500
       //     );
       //     List<Integer> jsonData = new ArrayList<>(receivedData.length);
       //     for (byte b : receivedData) {
       //         jsonData.add(Byte.toUnsignedInt(b));
       //     }
       //     return ResponseEntity.ok(jsonData);
       // } catch (Throwable t) {
       //     return ResponseEntity.status(500).body(Map.of("error", "发送/接收操作失败: " + t.getMessage()));
       // }
         return ResponseEntity.status(404).body(Map.of("error", "Endpoint deprecated: Use Web Serial API"));
    }
    */
}