/**
 * Acadia Telemetry Protocol Encoder/Decoder
 * Based on the C++ implementation in TeleProcess.cpp
 */

const HEADER = 0x68;
const FOOTER = 0x16;
const ACK_MASTER_TO_SLAVE = 0xA2; // 新增: 主站到从站的ACK
const ACK_SLAVE_TO_MASTER = 0xE5; // 新增: 从站到主站的ACK (短确认)


/**
 * Calculates the 8-bit checksum for a block of data.
 * @param {Uint8Array} dataBlock - The data block to be checksummed.
 * @returns {number} The 8-bit checksum.
 */
function calculateChecksum(dataBlock) {
    return dataBlock.reduce((sum, byte) => (sum + byte) & 0xFF, 0);
}

/**
 * Packs data into a full Acadia protocol frame (68 ... 16).
 * Can be used in two ways:
 * 1. Pass an object with stationAddr, funcCode1, etc. to build a frame from components.
 * 2. Pass an object with a pre-built `dataBlock` to pack it directly.
 * @param {object} options - The options for packing the frame.
 * @param {number} options.stationAddr - Station address.
 * @param {number} options.funcCode1 - Function code 1.
 * @param {number} options.funcCode2 - Function code 2.
 * @param {number} options.telegramNr - Telegram number.
 * @param {Uint8Array} [options.payload=new Uint8Array()] - Optional payload data.
 * @param {Uint8Array} [options.dataBlock] - Optional pre-built data block (overrides other component options if provided).
 * @returns {Uint8Array} The fully packed binary frame (68 ... 16).
 */
export function pack(options) {
    let dataBlock;

    if (options.dataBlock) {
        // 如果直接提供了 dataBlock
        dataBlock = options.dataBlock;
    } else {
        // 否则，根据组件构建 dataBlock
        const { stationAddr = 0, funcCode1 = 0x09, funcCode2 = 0x80, telegramNr, payload = new Uint8Array() } = options;
        if (typeof telegramNr === 'undefined') {
            throw new Error("telegramNr is required when building dataBlock from components.");
        }
        const payloadLength = payload.length;
        // 数据块长度 = 4 (地址+功能码+序列号) + payload 长度
        const blockLength = 4 + payloadLength;
        dataBlock = new Uint8Array(blockLength);
        dataBlock[0] = stationAddr;
        dataBlock[1] = funcCode1; // 注意: C++ 代码中 F1 是 (Msg_cntr << 5) | 0x09，这里简化处理，如有需要需调整
        dataBlock[2] = funcCode2;
        dataBlock[3] = telegramNr;
        if (payloadLength > 0) {
            dataBlock.set(payload, 4); // 将 payload 复制到 dataBlock 的第5个字节开始
        }
    }

    const blockLengthActual = dataBlock.length; // 实际的数据块长度
    const checksum = calculateChecksum(dataBlock); // 计算校验和

    // 完整帧长度 = 6 (帧头*2, 长度*2, 校验和, 帧尾) + 数据块长度
    const frame = new Uint8Array(6 + blockLengthActual);
    frame[0] = HEADER;         // 帧头1
    frame[1] = blockLengthActual; // 长度1
    frame[2] = blockLengthActual; // 长度 2 (与长度1相同)
    frame[3] = HEADER;         // 帧头2
    frame.set(dataBlock, 4);   // 复制数据块 (从第5个字节开始)
    frame[4 + blockLengthActual] = checksum; // 校验和 (数据块之后)
    frame[5 + blockLengthActual] = FOOTER;   // 帧尾

    return frame;
}

/**
 * @brief 创建一个 ACK (0xA2) 帧。
 * @returns {Uint8Array} 只包含 0xA2 的字节数组。
 */
export function packAck() {
    return new Uint8Array([ACK_MASTER_TO_SLAVE]);
}


/**
 * A stateful class to unpack Acadia protocol frames from a streaming data source.
 * Handles both standard data frames (68...16) and simple ACKs (E5).
 */
export class Unpacker {
    constructor() {
        this.buffer = new Uint8Array(0); // 内部缓冲区，存储未处理的数据
    }

    /**
     * Appends new data to the internal buffer.
     * @param {Uint8Array} newData - The new chunk of data received from the serial port.
     */
    addData(newData) {
        // 创建一个新的、更大的缓冲区
        const newBuffer = new Uint8Array(this.buffer.length + newData.length);
        // 复制旧数据
        newBuffer.set(this.buffer);
        // 追加新数据
        newBuffer.set(newData, this.buffer.length);
        // 替换旧缓冲区
        this.buffer = newBuffer;
        // console.log("Buffer after add:", this.buffer); // 调试日志
    }

    /**
     * Attempts to parse complete frames or ACKs from the internal buffer.
     * @returns {Array<object>} An array of parsed objects.
     * - For data frames: { type: 'data', stationAddr, funcCode1, funcCode2, telegramNr, payload, raw }
     * - For E5 ACK: { type: 'ack_e5', raw: Uint8Array([0xE5]) }
     */
    unpack() {
        const frames = []; // 存储解析出的帧或ACK
        let consumedBytes = 0; // 记录已处理的字节数

        while (this.buffer.length > consumedBytes) {
            const firstByte = this.buffer[consumedBytes];

            // --- 检查 E5 ACK ---
            if (firstByte === ACK_SLAVE_TO_MASTER) {
                // console.log("Found E5 ACK"); // 调试
                frames.push({
                    type: 'ack_e5',
                    raw: this.buffer.subarray(consumedBytes, consumedBytes + 1)
                });
                consumedBytes += 1; // 消耗掉 E5 字节
                continue; // 继续尝试解析缓冲区剩余部分
            }

            // --- 尝试解析 68 ... 16 数据帧 ---
            // 查找第一个帧头 0x68，从当前已消耗字节之后开始
            const frameStartIndex = this.buffer.indexOf(HEADER, consumedBytes);
            // console.log(`Searching for HEADER from offset ${consumedBytes}, found at ${frameStartIndex}`); // 调试

            if (frameStartIndex === -1) {
                // 如果在剩余的缓冲区中找不到帧头，说明没有完整帧了
                break; // 退出循环
            }

            // 如果找到的帧头不是在当前消耗位置，说明 E5 和帧头之间可能有无效数据
            if (frameStartIndex > consumedBytes) {
                console.warn(`Discarding ${frameStartIndex - consumedBytes} unexpected bytes before frame header:`, this.buffer.subarray(consumedBytes, frameStartIndex));
                consumedBytes = frameStartIndex; // 跳过无效数据
            }


            // 检查缓冲区是否有足够的字节来读取帧头和长度 (至少4字节: 68 L L 68)
            if (this.buffer.length < frameStartIndex + 4) {
                // 数据不足以判断帧结构，保留从帧头开始的部分，等待更多数据
                // console.log("Buffer too short for header + length check"); // 调试
                break;
            }

            // 检查第二个帧头是否存在于正确位置 (索引 frameStartIndex + 3)
            if (this.buffer[frameStartIndex + 3] !== HEADER) {
                // 结构错误 (不是 68 L L 68)，可能是单个 68 干扰字节
                console.warn(`Invalid frame structure: Second HEADER not found at index ${frameStartIndex + 3}. Discarding byte at ${frameStartIndex}.`);
                consumedBytes = frameStartIndex + 1; // 跳过这个错误的 68，从下一个字节继续搜索
                continue;
            }

            // 读取数据块长度 L (位于索引 frameStartIndex + 1)
            const blockLength = this.buffer[frameStartIndex + 1];
            // 检查 L1 和 L2 是否相等 (位于索引 frameStartIndex + 2)
            if (blockLength !== this.buffer[frameStartIndex + 2]) {
                // 长度字段不匹配，帧结构错误
                console.warn(`Invalid frame structure: Length bytes mismatch (${blockLength} != ${this.buffer[frameStartIndex + 2]}). Discarding byte at ${frameStartIndex}.`);
                consumedBytes = frameStartIndex + 1; // 跳过这个错误的 68
                continue;
            }

            // 计算完整的预期帧长度
            const frameLength = 4 + blockLength + 2; // 4字节头 + L字节数据块 + 校验和 + 帧尾
            // console.log(`Expected blockLength=${blockLength}, frameLength=${frameLength}`); // 调试

            // 检查缓冲区中从帧头开始是否有足够的数据容纳整个帧
            if (this.buffer.length < frameStartIndex + frameLength) {
                // 数据不足以构成完整帧，保留从帧头开始的部分，等待更多数据
                // console.log(`Buffer too short for complete frame (need ${frameLength}, have ${this.buffer.length - frameStartIndex})`); // 调试
                break;
            }

            // 提取完整的帧数据
            const frame = this.buffer.subarray(frameStartIndex, frameStartIndex + frameLength);

            // 检查帧尾是否为 0x16
            if (frame[frame.length - 1] !== FOOTER) {
                // 帧尾错误
                console.warn(`Invalid frame footer: Expected ${FOOTER}, got ${frame[frame.length - 1]}. Discarding byte at ${frameStartIndex}.`);
                consumedBytes = frameStartIndex + 1; // 跳过这个帧的起始 68
                continue;
            }

            // --- 帧结构基本正确，开始校验 ---
            // 提取数据块 (位于帧头之后，校验和之前)
            const dataBlock = frame.subarray(4, 4 + blockLength);
            // 提取接收到的校验和 (位于帧尾之前)
            const receivedChecksum = frame[frame.length - 2];
            // 计算数据块的校验和
            const calculatedChecksum = calculateChecksum(dataBlock);

            // 比较校验和
            if (receivedChecksum === calculatedChecksum) {
                // 校验成功！解析数据块内容
                // console.log("Checksum OK. Parsing frame."); // 调试
                frames.push({
                    type: 'data', // 标记为数据帧
                    stationAddr: dataBlock[0],
                    funcCode1: dataBlock[1],
                    funcCode2: dataBlock[2],
                    telegramNr: dataBlock[3], // 报文序列号/ID
                    payload: dataBlock.subarray(4), // 数据负载 (从第5个字节开始)
                    raw: frame, // 包含原始帧数据
                });
                // 消耗掉已成功解析的帧所占用的字节
                consumedBytes = frameStartIndex + frameLength;
                // console.log(`Frame parsed successfully. Consumed ${consumedBytes} bytes.`); // 调试
                // 从头继续扫描剩余缓冲区
                // (因为一个数据包里可能紧跟着下一个帧或ACK)
            } else {
                // 校验和失败
                console.warn(`Checksum mismatch: Received ${receivedChecksum}, calculated ${calculatedChecksum}. Discarding byte at ${frameStartIndex}. Frame:`, frame);
                consumedBytes = frameStartIndex + 1; // 跳过这个帧的起始 68
                continue;
            }
        } // end while

        // 处理完所有能解析的帧后，更新缓冲区，移除已消耗的字节
        if (consumedBytes > 0) {
            this.buffer = this.buffer.slice(consumedBytes);
            // console.log(`Buffer after unpack (consumed ${consumedBytes}):`, this.buffer); // 调试
        }

        return frames; // 返回解析出的帧对象数组
    }
}