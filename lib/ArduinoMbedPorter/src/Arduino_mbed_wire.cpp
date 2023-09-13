#include "Arduino_mbed_wire.hpp"

TwoWire::TwoWire(PinName sda, PinName scl, int hz) : i2c(sda, scl) {
    i2c.frequency(hz);
    rxIndex = 0;
    rxLength = 0;
    txIndex = 0;
    txLength = 0;
}

void TwoWire::begin() {
    // Master mode initialization
}

void TwoWire::begin(uint8_t addr) {
    address = addr;
    // Slave mode initialization
}

void TwoWire::begin(int addr) {
    begin(static_cast<uint8_t>(addr));
}

void TwoWire::end() {
    // Cleanup if necessary
}

void TwoWire::beginTransmission(uint8_t addr) {
    address = addr;
    txIndex = 0;
}

void TwoWire::beginTransmission(int addr) {
    beginTransmission(static_cast<uint8_t>(addr));
}

uint8_t TwoWire::endTransmission(bool sendStop) {
    int ret = i2c.write((int)address, (char*)txBuffer, txIndex, !sendStop);
    return ret; 
}

uint8_t TwoWire::endTransmission(void) {
    return endTransmission(true);
}

uint8_t TwoWire::requestFrom(uint8_t addr, uint8_t quantity, bool sendStop) {
    rxLength = i2c.read(addr, (char*)rxBuffer, quantity, !sendStop);
    rxIndex = 0;
    return rxLength;
}

uint8_t TwoWire::requestFrom(uint8_t addr, uint8_t quantity) {
    return requestFrom(addr, quantity, true);
}

uint8_t TwoWire::requestFrom(int addr, int quantity) {
    return requestFrom(static_cast<uint8_t>(addr), static_cast<uint8_t>(quantity), true);
}

size_t TwoWire::write(uint8_t data) {
    if (txIndex < BUFFER_LENGTH) {
        txBuffer[txIndex++] = data;
        return 1;
    }
    return 0;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
    for(size_t i = 0; i < quantity && txIndex < BUFFER_LENGTH; i++) {
        txBuffer[txIndex++] = data[i];
    }
    return quantity;
}

size_t TwoWire::write(const char *data) {
    return write(reinterpret_cast<const uint8_t *>(data), strlen(data));
}

int TwoWire::available() {
    return rxLength - rxIndex;
}

int TwoWire::read() {
    if (rxIndex < rxLength) {
        return rxBuffer[rxIndex++];
    }
    return -1;
}

int TwoWire::peek() {
    if (rxIndex < rxLength) {
        return rxBuffer[rxIndex];
    }
    return -1;
}

void TwoWire::flush() {
    // For mbed, this can be a no-op.
}

void TwoWire::onReceive(void (*callback)(int)) {
    // Implement callback functionality if needed
}

void TwoWire::onRequest(void (*callback)(void)) {
    // Implement callback functionality if needed
}

// Default I2C instance
TwoWire Wire(I2C_SDA, I2C_SCL);
