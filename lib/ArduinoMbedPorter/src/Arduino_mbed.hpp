#pragma once

#include "TimerTicker.hpp"


#include <mbed.h>
#include <map>


#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

void pinMode(PinName pin, uint8_t mode);

void digitalWrite(PinName pin, uint8_t val);
int digitalRead(PinName pin);

int analogRead(PinName pin);
void analogWrite(uint8_t pin, int val);

//未定義
void analogReference(uint8_t mode);

unsigned long millis(void);
unsigned long micros(void);


inline void delay(unsigned long ms){
    wait_us(1000*ms);
}

inline void delayMicroseconds(unsigned int us){
    wait_us(us);
}

unsigned long pulseIn(PinName pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(PinName pin, uint8_t state, unsigned long timeout);

void shiftOut(PinName dataPin, PinName clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(PinName dataPin, PinName clockPin, uint8_t bitOrder);

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode);
void detachInterrupt(uint8_t interruptNum);


namespace ArduinoMbedConverter
{

    TimerTicker timer;
    
    std::map<PinName, uint8_t> pinmodes;
    std::map<PinName, DigitalInOut*> digital_in_outs;
    std::map<PinName, AnalogIn*> analog_ins;
    std::map<PinName, AnalogOut*> analog_outs;
    std::map<PinName, InterruptIn*> interrupt_ins;

    uint8_t analog_reference_mode;
};


