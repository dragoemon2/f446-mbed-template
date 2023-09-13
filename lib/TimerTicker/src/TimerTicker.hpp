#pragma once
#include <mbed.h>
#include <chrono>

class TimerTicker
{
    public:
        Timer timer;
        void reset();
        void cancel();

        std::chrono::microseconds read();
        int read_s();
        int read_ms();
        int read_us();
        
        void setInternal(std::chrono::microseconds internal);
        void setInternal_s(unsigned int internal);
        void setInternal_ms(unsigned int internal);
        void setInternal_us(unsigned int internal);

        bool raised();

        TimerTicker();

    private:
        bool flag = false;
        std::chrono::microseconds next_time;
        std::chrono::microseconds _internal;
        bool setRaisement = false;
};