#include "BNO055.hpp"

BNO055 gyro(D8, D2);
Ticker ticker;

int main(){
    printf("start\n");

    while(true){
        wait_us(1000);
        printf("%d %d\n", int(gyro.getYawDegrees()), int(gyro.getMagDegrees()));
    }
}