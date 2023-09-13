#include "TimerTicker.hpp"

TimerTicker::TimerTicker(){
    timer.start();
}

void TimerTicker::reset(){
    cancel();
    timer.reset();
}

void TimerTicker::cancel(){
    setRaisement = false;
    _internal = 0us;
    next_time = 0us;
}

std::chrono::microseconds TimerTicker::read(){
    return timer.elapsed_time();
}


int TimerTicker::read_s(){
    return std::chrono::duration_cast<std::chrono::seconds>(timer.elapsed_time()).count();
}

int TimerTicker::read_ms(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(timer.elapsed_time()).count();
}

int TimerTicker::read_us(){
    return std::chrono::duration_cast<std::chrono::microseconds>(timer.elapsed_time()).count();
}

void TimerTicker::setInternal(std::chrono::microseconds internal){
    _internal = internal;
    setRaisement = true;
    next_time = timer.elapsed_time();
}

void TimerTicker::setInternal_s(unsigned int internal){
    setInternal(std::chrono::seconds(internal));
}

void TimerTicker::setInternal_ms(unsigned int internal){
    setInternal(std::chrono::milliseconds(internal));
}

void TimerTicker::setInternal_us(unsigned int internal){
    setInternal(std::chrono::microseconds(internal));
}

bool TimerTicker::raised(){
    if(!setRaisement){
        return false;
    }

    if(next_time > timer.elapsed_time()){
        next_time += _internal;
        return true;
    }else{
        return false;
    }
}


