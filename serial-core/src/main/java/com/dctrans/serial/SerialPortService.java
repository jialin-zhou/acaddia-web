package com.dctrans.serial;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

import java.util.Arrays;
import java.util.List;
import java.util.function.Consumer;
import java.util.stream.Collectors;

/**
 * A plain Java service class to manage serial port interactions.
 */
public class SerialPortService {

    private SerialPort activePort;

    public List<String> getAvailablePorts() {
        return Arrays.stream(SerialPort.getCommPorts())
                .map(SerialPort::getSystemPortName)
                .collect(Collectors.toList());
    }

    /**
     * Connects to a specified serial port and adds a data listener.
     * @param dataConsumer A callback function to handle incoming byte arrays.
     * @return true if the port was opened successfully, false otherwise.
     */
    public boolean connect(String portDescriptor, int baudRate, int dataBits, int stopBits, int parity, Consumer<byte[]> dataConsumer) {
        if (activePort != null && activePort.isOpen()) {
            System.out.println("An active port is already open. Please disconnect first.");
            return false;
        }

        activePort = SerialPort.getCommPort(portDescriptor);
        if (activePort.getSystemPortName().equalsIgnoreCase("dummy")) {
            System.err.println("Port not found: " + portDescriptor);
            return false;
        }

        activePort.setComPortParameters(baudRate, dataBits, stopBits, parity);
        activePort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 100, 0);

        if (activePort.openPort()) {
            System.out.println("Successfully opened port: " + portDescriptor);
            activePort.addDataListener(new SerialPortDataListener() {
                @Override
                public int getListeningEvents() {
                    return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
                }

                @Override
                public void serialEvent(SerialPortEvent event) {
                    if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
                        return;
                    }
                    int bytesAvailable = activePort.bytesAvailable();
                    if (bytesAvailable > 0) {
                        byte[] newData = new byte[bytesAvailable];
                        activePort.readBytes(newData, newData.length);
                        // Pass the received data to the consumer
                        dataConsumer.accept(newData);
                    }
                }
            });
            return true;
        } else {
            System.err.println("Failed to open port: " + portDescriptor);
            activePort = null;
            return false;
        }
    }

    public void disconnect() {
        if (activePort != null && activePort.isOpen()) {
            String portName = activePort.getSystemPortName();
            activePort.removeDataListener();
            if (activePort.closePort()) {
                System.out.println("Successfully closed port: " + portName);
            } else {
                System.err.println("Failed to close port: " + portName);
            }
        }
        activePort = null;
    }

    public void write(byte[] data) {
        if (activePort == null || !activePort.isOpen()) {
            System.err.println("Cannot write, port is not open.");
            return;
        }
        activePort.writeBytes(data, data.length);
        // We can also push the sent data to the frontend for display
    }

    public boolean isConnected() {
        return activePort != null && activePort.isOpen();
    }
}
