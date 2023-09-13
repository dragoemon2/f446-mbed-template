#pragma once

#include <mbed.h>

#define PI (3.141592653589793)


class Encoder
{
    public:
        InterruptIn interruptin;
        DigitalIn digitalin;
        Ticker ticker;
        Encoder(PinName pinA=NC, PinName pinB=NC, unsigned int resolution=2048, bool dual=true, unsigned int speed_calculating_frequency=10, int sign=1);

        //位置
        float getRadians();

        //速度
        float getRadiansPerSecond();

        //加速度
        float getRadiansPerSecondSquared();



    private:
        const static int LENGTH = 10;
        void interrupt(int sgn=1);
        void loop();
        
        int count=0;

        int history[LENGTH];

        unsigned int speed_calculating_frequency;
        float radians_per_pulse;
};