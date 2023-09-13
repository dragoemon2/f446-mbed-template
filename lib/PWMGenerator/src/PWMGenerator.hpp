#pragma once

#include <mbed.h>
#include <chrono>

class PWMGenerator
{
    public:
        Ticker ticker;
        DigitalOut digitalout;
        PWMGenerator(PinName pin, std::chrono::microseconds pulsewidth=20ms, float dutyCycleThreshold=0.0f, bool use_cpu=true);
        void period(std::chrono::microseconds pulsewidth);
        void write(float dutyCycle);

        void start();
        void stop();

        int _s1; 

    private:
        PwmOut* pwmout;
        int _pulsewidth;
        float _dutyCycleThreshold;
        bool _use_cpu;
        int high_time;
        int low_time;
        bool running=false;
        bool using_pwmout=false;
        
        void interrupt(bool high);

};

