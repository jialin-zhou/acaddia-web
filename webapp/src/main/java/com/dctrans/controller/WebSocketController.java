package com.dctrans.controller;

import com.dctrans.dto.CommandDto;
import com.dctrans.service.DeviceInteractionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.stereotype.Controller;

@Controller
public class WebSocketController {

    private final DeviceInteractionService deviceInteractionService;

    @Autowired
    public WebSocketController(DeviceInteractionService deviceInteractionService) {
        this.deviceInteractionService = deviceInteractionService;
    }

    @MessageMapping("/send-command")
    public void handleCommand(CommandDto command) {
        System.out.println("Received command: " + command);

        switch (command.getType()) {
            // --- Serial Port Commands ---
            case "serial-connect":
                deviceInteractionService.connect(command.getPayload());
                break;

            case "serial-disconnect":
                deviceInteractionService.disconnect();
                break;

            case "serial-fetch-ports":
                deviceInteractionService.fetchAndSendAvailablePorts();
                break;

            // --- Time Commands ---
            case "time-set":
                if (command.getPayload() != null) {
                    // Assuming the payload for time-set is just the string value.
                    deviceInteractionService.setTime(command.getPayload().toString());
                }
                break;

            case "time-fetch":
                deviceInteractionService.fetchTime();
                break;

            // --- Settings and Data Commands (Placeholders) ---
            case "tqcs-apply":
            case "ad-params-apply":
            case "ad-adjust-calibrate":
            case "tqml-execute":
            case "angle-apply":
            case "dim-confirm":
                System.out.println("Handling settings application for: " + command.getType());
                deviceInteractionService.sendCommand(command); // Example: forward the whole command
                break;

            case "tqcs-fetch":
            case "ad-params-fetch":
            case "message-fetch":
            case "angle-fetch":
                System.out.println("Handling fetch request for: " + command.getType());
                // deviceInteractionService.fetchData(command.getType());
                break;

            case "tqcs-default":
            case "ad-params-default":
            case "dim-default":
                System.out.println("Handling default request for: " + command.getType());
                // deviceInteractionService.loadDefaults(command.getType());
                break;

            default:
                System.out.println("Unknown command type: " + command.getType());
                break;
        }
    }
}
