#pragma once

#include <mbed.h>

#define BUFFER_LENGTH 128

class TwoWire {
private:
    I2C i2c;
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t txBuffer[BUFFER_LENGTH];
    uint16_t rxIndex;
    uint16_t rxLength;
    uint16_t txIndex;
    uint16_t txLength;
    uint8_t address;

public:
    TwoWire(PinName sda = I2C_SDA, PinName scl = I2C_SCL, int hz = 100000);
    
    void begin();
    void begin(uint8_t);
    void begin(int);
    void end();
    
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(bool sendStop = true);
    uint8_t endTransmission(void);
    
    uint8_t requestFrom(uint8_t, uint8_t, bool sendStop = true);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    
    size_t write(uint8_t);
    size_t write(const uint8_t *, size_t);
    size_t write(const char *);
    int available();
    int read();
    int peek();
    void flush();
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));
};

extern TwoWire Wire; // Default I2C instance
