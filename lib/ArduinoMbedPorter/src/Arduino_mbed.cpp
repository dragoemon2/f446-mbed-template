#include "Arduino_mbed.hpp"
#include <mbed.h>

using namespace ArduinoMbedConverter;

void pinMode(PinName pin, uint8_t mode){
    if(pinmodes.count(pin) == 0){
        pinmodes[pin] = mode;
        digital_in_outs[pin] = new DigitalInOut(pin);
    }

    if(mode == INPUT){
        digital_in_outs[pin]->input();
    }else if(mode == OUTPUT){
        digital_in_outs[pin]->output();
    }
}

void digitalWrite(PinName pin, uint8_t val){
    digital_in_outs[pin]->write(val);
}

int digitalRead(PinName pin){
    return digital_in_outs[pin]->read();
}

int analogRead(PinName pin){
    if(analog_ins.count(pin) == 0){
        analog_ins[pin] = new AnalogIn(pin);
    }

    return int(1024 * analog_ins[pin]->read());
}

void analogWrite(PinName pin, int val){
    if(analog_outs.count(pin) == 0){
        analog_outs[pin] = new AnalogOut(pin);
    }

    analog_outs[pin]->write(val / 256.0f);
}

void analogReference(uint8_t mode){
    analog_reference_mode = mode;

    //未定義
    /*

    for(auto it = analog_ins.begin(); it != analog_ins.end(); it++){
        it->second->set_reference_voltage(mode);
    }

    */
}

unsigned long millis(){
    return timer.read_ms();
}

unsigned long micros(){
    return timer.read_us();
}


unsigned long pulseIn(PinName pin, uint8_t state, unsigned long timeout){
    pinMode(pin, OUTPUT);

    int start = 0;
    int finish = 0;

    int timeout_start = timer.read_us();
    while(timer.read_us() - timeout_start < timeout){
        if(state == digitalRead(pin) && !start){
            start = timer.read_us();
        }else if(state != digitalRead(pin) && !start){
            finish = timer.read_us();
            return finish - start;
        }
    }

    return 0;
}


unsigned long pulseInLong(PinName pin, uint8_t state, unsigned long timeout){
    return pulseIn(pin, state, timeout);
}
