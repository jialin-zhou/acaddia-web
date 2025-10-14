/**
 * Acadia Telemetry Protocol Encoder/Decoder
 * Based on the C++ implementation in TeleProcess.cpp
 */

const HEADER = 0x68;
const FOOTER = 0x16;

/**
 * Calculates the 8-bit checksum for a block of data.
 * @param {Uint8Array} dataBlock - The data block to be checksummed.
 * @returns {number} The 8-bit checksum.
 */
function calculateChecksum(dataBlock) {
  return dataBlock.reduce((sum, byte) => (sum + byte) & 0xFF, 0);
}

/**
 * Packs data into a full Acadia protocol frame.
 * Can be used in two ways:
 * 1. Pass an object with stationAddr, funcCode1, etc. to build a frame from components.
 * 2. Pass an object with a pre-built `dataBlock` to pack it directly.
 * @param {object} options - The options for packing the frame.
 * @returns {Uint8Array} The fully packed binary frame.
 */
export function pack(options) {
  let dataBlock;

  if (options.dataBlock) {
    dataBlock = options.dataBlock;
  } else {
    const { stationAddr, funcCode1, funcCode2, telegramNr, payload = new Uint8Array() } = options;
    const payloadLength = payload.length;
    const blockLength = 4 + payloadLength;
    dataBlock = new Uint8Array(blockLength);
    dataBlock[0] = stationAddr;
    dataBlock[1] = funcCode1;
    dataBlock[2] = funcCode2;
    dataBlock[3] = telegramNr;
    dataBlock.set(payload, 4);
  }

  const blockLength = dataBlock.length;
  const checksum = calculateChecksum(dataBlock);

  const frame = new Uint8Array(6 + blockLength);
  frame[0] = HEADER;
  frame[1] = blockLength;
  frame[2] = blockLength;
  frame[3] = HEADER;
  frame.set(dataBlock, 4);
  frame[4 + blockLength] = checksum;
  frame[5 + blockLength] = FOOTER;

  return frame;
}

/**
 * A stateful class to unpack Acadia protocol frames from a streaming data source.
 */
export class Unpacker {
  constructor() {
    this.buffer = new Uint8Array(0);
  }

  /**
   * Appends new data to the internal buffer.
   * @param {Uint8Array} newData - The new chunk of data received from the serial port.
   */
  addData(newData) {
    const newBuffer = new Uint8Array(this.buffer.length + newData.length);
    newBuffer.set(this.buffer);
    newBuffer.set(newData, this.buffer.length);
    this.buffer = newBuffer;
  }

  /**
   * Attempts to parse complete frames from the internal buffer.
   * @returns {Array<object>} An array of parsed frame objects.
   */
  unpack() {
    const frames = [];
    let searchOffset = 0;

    while (this.buffer.length > searchOffset) {
      const frameStartIndex = this.buffer.indexOf(HEADER, searchOffset);
      if (frameStartIndex === -1) {
        this.buffer = new Uint8Array(0);
        return frames;
      }

      if (this.buffer.length < frameStartIndex + 4) {
        this.buffer = this.buffer.slice(frameStartIndex);
        return frames;
      }

      if (this.buffer[frameStartIndex + 3] !== HEADER) {
        searchOffset = frameStartIndex + 1;
        continue;
      }

      const blockLength = this.buffer[frameStartIndex + 1];
      if (blockLength !== this.buffer[frameStartIndex + 2]) {
        searchOffset = frameStartIndex + 1;
        continue;
      }

      const frameLength = 4 + blockLength + 2;
      if (this.buffer.length < frameStartIndex + frameLength) {
        this.buffer = this.buffer.slice(frameStartIndex);
        return frames;
      }

      const frame = this.buffer.subarray(frameStartIndex, frameStartIndex + frameLength);

      if (frame[frame.length - 1] !== FOOTER) {
        searchOffset = frameStartIndex + 1;
        continue;
      }

      const dataBlock = frame.subarray(4, 4 + blockLength);
      const receivedChecksum = frame[frame.length - 2];
      const calculatedChecksum = calculateChecksum(dataBlock);

      if (receivedChecksum === calculatedChecksum) {
        frames.push({
          stationAddr: dataBlock[0],
          funcCode1: dataBlock[1],
          funcCode2: dataBlock[2],
          telegramNr: dataBlock[3],
          payload: dataBlock.subarray(4),
          raw: frame,
        });
        this.buffer = this.buffer.slice(frameStartIndex + frameLength);
        searchOffset = 0;
      } else {
        searchOffset = frameStartIndex + 1;
      }
    }
    return frames;
  }
}
