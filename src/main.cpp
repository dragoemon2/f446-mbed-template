#include <mbed.h>
#include "PWMGenerator.hpp"
#include "Units.hpp"


PWMGenerator pwm(D8, 20ms, 0.3f, false);


int main(){
    pwm.write(0.3f);
    while(true){
        wait_us(1000000);
        printf("%d\n", pwm._s1);
    }
}

