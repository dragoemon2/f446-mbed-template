#include "PWMGenerator.hpp"
#include <chrono>


PWMGenerator::PWMGenerator(PinName pin, std::chrono::microseconds pulsewidth, float dutyCycleThreshold, bool use_cpu)
  : digitalout(pin),
    _pulsewidth(pulsewidth.count()),
    _dutyCycleThreshold(dutyCycleThreshold),
    _use_cpu(use_cpu)
{
    if(!_use_cpu){
        pwmout = new PwmOut(pin);
    }
}

//PWM周期を設定
void PWMGenerator::period(std::chrono::microseconds pulsewidth){
    _pulsewidth = pulsewidth.count();
}

void PWMGenerator::write(float dutyCycle){
    if(dutyCycle>1.0f){dutyCycle = 1.0f;};
    if(dutyCycle<0.0f){dutyCycle = 0.0f;};

    if(dutyCycle < _dutyCycleThreshold){
        //PFM制御
        high_time = _pulsewidth * _dutyCycleThreshold;
        low_time = _pulsewidth * _dutyCycleThreshold * (1.0f / dutyCycle - 1.0f);

        if(using_pwmout){
            using_pwmout = false;
            pwmout->suspend();    
        }

        if(!running){
            start();
        }
        


    }else{
        //PWM制御
        high_time = _pulsewidth * dutyCycle;
        low_time = _pulsewidth * (1.0f - dutyCycle);

        if(!running && _use_cpu){
            start();
        }else if(running && !_use_cpu){
            stop();
        }

        if(!_use_cpu){
            if(!using_pwmout){
                using_pwmout = true;
                pwmout->resume();
            }
            pwmout->write(dutyCycle);
        }
    }

    

    
}

void PWMGenerator::start(){
    running = true;
    interrupt(0);
}

void PWMGenerator::stop(){
    running = false;
    ticker.detach();
}

void PWMGenerator::interrupt(bool high){
    _s1++;
    if(high){
        digitalout.write(1);
        ticker.attach([this]{interrupt(0);}, std::chrono::microseconds(high_time));
    }else{
        digitalout.write(0);
        ticker.attach([this]{interrupt(1);}, std::chrono::microseconds(low_time));
    }
}

