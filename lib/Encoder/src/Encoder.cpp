#include "Encoder.hpp"

Encoder::Encoder(PinName pinA, PinName pinB, unsigned int resolution, bool dual, unsigned int speed_calculating_frequency, int sign):
    interruptin(pinA),
    digitalin(pinB),
    speed_calculating_frequency(speed_calculating_frequency)
{
    radians_per_pulse = 2 * PI * float((dual ? 2:1) * sign) / resolution;
    count = 0;

    ticker.attach([this]{loop();}, 1000000us/speed_calculating_frequency);

    interruptin.rise([this]{interrupt(1);});
    if(dual){
        interruptin.fall([this]{interrupt(1);});
    }

}

void Encoder::interrupt(int sgn){
    if(digitalin.read() == 0){
        count += sgn;
    }else{
        count -= sgn;
    }
}

void Encoder::loop(){
    for(int i=LENGTH-1;i>0;i--){
        history[i] = history[i-1];
    }
    history[0] = count;
}

float Encoder::getRadians(){
    return count * radians_per_pulse;
}


float Encoder::getRadiansPerSecond(){
    return (history[0] - history[1]) * radians_per_pulse;
}


float Encoder::getRadiansPerSecondSquared(){
    return (history[0] -2*history[1] + history[2]) * speed_calculating_frequency * speed_calculating_frequency * radians_per_pulse;
}

