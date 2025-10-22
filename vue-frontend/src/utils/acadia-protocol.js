/**
 * Acadia Telemetry Protocol Encoder/Decoder
 * Based on the C++ implementation in TeleProcess.cpp
 *
 * (MODIFIED) Unpacker.unpack() has been rewritten to handle and report
 * non-protocol ("junk") data, in addition to 'data' and 'ack_e5' frames.
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
    frame[1] = blockLengthActual; // 长度 1
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
 * Handles standard data frames (68...16), simple ACKs (E5), and junk data.
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
     * (MODIFIED)
     * Attempts to parse complete frames, ACKs, and junk data from the internal buffer.
     * @returns {Array<object>} An array of parsed objects.
     * - For data frames: { type: 'data', stationAddr, ..., payload, raw }
     * - For E5 ACK: { type: 'ack_e5', raw: Uint8Array([0xE5]) }
     * - For non-protocol: { type: 'junk', raw: Uint8Array[...] }
     */
    unpack() {
        const frames = []; // 存储解析出的帧或ACK
        let consumedBytes = 0; // 记录已处理的字节数
        let searchOffset = 0; // 记录当前在缓冲区中搜索的位置

        while (this.buffer.length > searchOffset) {
            const firstByte = this.buffer[searchOffset];

            // --- 1. 检查 E5 ACK ---
            if (firstByte === ACK_SLAVE_TO_MASTER) {
                // 发现 E5。
                // 首先，将在它之前的所有字节报告为 "junk"。
                if (searchOffset > consumedBytes) {
                    frames.push({
                        type: 'junk',
                        raw: this.buffer.subarray(consumedBytes, searchOffset)
                    });
                }
                // 报告 E5 帧
                frames.push({
                    type: 'ack_e5',
                    raw: this.buffer.subarray(searchOffset, searchOffset + 1)
                });
                // 更新已消耗字节和搜索偏移
                consumedBytes = searchOffset + 1;
                searchOffset = consumedBytes;
                continue; // 继续从下一个字节开始搜索
            }

            // --- 2. 检查 68 帧头 ---
            if (firstByte === HEADER) {
                // 发现 68。尝试解析完整帧。

                // 检查是否有足够的字节读取头 (68 L L 68)
                if (this.buffer.length < searchOffset + 4) {
                    break; // 数据不足，停止解析，等待更多数据
                }
                // 检查第二个 68 是否在正确位置
                if (this.buffer[searchOffset + 3] !== HEADER) {
                    searchOffset++; // 结构错误，跳过这个 68，继续搜索
                    continue;
                }
                // 检查长度 L1 和 L2 是否一致
                const blockLength = this.buffer[searchOffset + 1];
                if (blockLength !== this.buffer[searchOffset + 2]) {
                    searchOffset++; // 长度不匹配，跳过这个 68
                    continue;
                }
                // 检查缓冲区是否有足够的字节容纳完整帧
                const frameLength = 4 + blockLength + 2; // 4(头) + L(数据) + 2(校验+尾)
                if (this.buffer.length < searchOffset + frameLength) {
                    break; // 数据不足，停止解析，等待更多数据
                }

                // 提取完整帧进行验证
                const frame = this.buffer.subarray(searchOffset, searchOffset + frameLength);

                // 检查帧尾
                if (frame[frame.length - 1] !== FOOTER) {
                    searchOffset++; // 帧尾错误，跳过这个 68
                    continue;
                }

                // --- 帧结构正确，校验 Checksum ---
                const dataBlock = frame.subarray(4, 4 + blockLength);
                const receivedChecksum = frame[frame.length - 2];
                const calculatedChecksum = calculateChecksum(dataBlock);

                if (receivedChecksum === calculatedChecksum) {
                    // 校验成功！这是一个有效帧
                    // 首先，报告在它之前的所有 "junk" 数据
                    if (searchOffset > consumedBytes) {
                        frames.push({
                            type: 'junk',
                            raw: this.buffer.subarray(consumedBytes, searchOffset)
                        });
                    }
                    // 报告有效数据帧
                    frames.push({
                        type: 'data', // 标记为数据帧
                        stationAddr: dataBlock[0],
                        funcCode1: dataBlock[1],
                        funcCode2: dataBlock[2],
                        telegramNr: dataBlock[3], // 报文序列号/ID
                        payload: dataBlock.subarray(4), // 数据负载 (从第5个字节开始)
                        raw: frame, // 包含原始帧数据
                    });
                    // 更新已消耗字节和搜索偏移
                    consumedBytes = searchOffset + frameLength;
                    searchOffset = consumedBytes;
                    continue; // 继续从下一个字节开始搜索
                } else {
                    // 校验和失败
                    console.warn(`Checksum mismatch: Received ${receivedChecksum}, calculated ${calculatedChecksum}. Discarding header.`);
                    searchOffset++; // 跳过这个 68
                    continue;
                }
            } // end if (firstByte === HEADER)

            // --- 3. 既不是 E5 也不是 68 ---
            // 这是一个 "junk" 字节，继续向后搜索
            searchOffset++;

        } // end while

        // 循环结束后，检查是否在末尾遗留了未处理的 "junk" 数据
        // (即 searchOffset 走到了缓冲区末尾，但 consumedBytes 没跟上)
        if (searchOffset > consumedBytes && searchOffset === this.buffer.length) {
            frames.push({
                type: 'junk',
                raw: this.buffer.subarray(consumedBytes, searchOffset)
            });
            consumedBytes = searchOffset;
        }

        // 处理完所有能解析的帧后，更新缓冲区，移除已消耗的字节
        if (consumedBytes > 0) {
            this.buffer = this.buffer.slice(consumedBytes);
            // console.log(`Buffer after unpack (consumed ${consumedBytes}):`, this.buffer); // 调试
        }

        return frames; // 返回解析出的帧对象数组
    }
}