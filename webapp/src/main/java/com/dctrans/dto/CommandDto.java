package com.dctrans.dto;

import java.util.Map;

/**
 * Data Transfer Object for incoming WebSocket commands from the frontend.
 */
public class CommandDto {
    private String type;
    private Map<String, Object> payload;

    // Standard getters and setters

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Map<String, Object> getPayload() {
        return payload;
    }

    public void setPayload(Map<String, Object> payload) {
        this.payload = payload;
    }

    @Override
    public String toString() {
        return "CommandDto{" +
                "type='" + type + '\'' +
                ", payload=" + payload +
                '}';
    }
}
