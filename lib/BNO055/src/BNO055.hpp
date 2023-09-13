#pragma once

#include <map>
#include <mbed.h>
#include <chrono>

#define PI (3.141592653589793)

class BNO055{
    public:
        //方位
        enum class DIRECTION : int
        {
            X,
            Y,
            Z
        };

        //値
        enum class VECTOR_TYPE : unsigned char
        {
            ACCEL=0x08,
            MAG=0x0E,
            GYRO=0x14,
            EULER=0x1A,
            QUATERNION=0x20,
            LINEAR_ACCEL=0x28,
            GRAVITY=0x2E
        };

        Ticker ticker;

        const char WRITE_BYTE = 0x00;
        const char READ_BYTE = 0x01;

        const char START_BYTE = 0xAA; 
        const char RESPONSE_BYTE = 0xBB; 

        UnbufferedSerial serial;
        BNO055(PinName tx=USBTX, PinName rx=USBRX, std::chrono::milliseconds internal=20ms);

        int8_t getRegister(VECTOR_TYPE vec_type, DIRECTION direction);

        float getYawDegrees();
        float getMagDegrees();

        void init();
        
        void write(unsigned char reg_add, unsigned char value);

        void requestValueContinuous(unsigned char reg_add);
        void stopRequestValueContinuous(unsigned char reg_add);

        int16_t getValue(unsigned char reg_add);

        void interrupt();
    
        int _s1;


    private:

        enum PROCESS{
            STARTING,
            SET_LENGTH,
            RECEIVING
        };

        unsigned int index = 0;
        unsigned int length = 0;

        unsigned char requested_reg;

        void requestValue(unsigned char reg_add);
        void onReceive(int length);
        void loop();

        char buffer[16];
        //unsigned int index = 0;
        int process = STARTING;

        //std::map<unsigned char, int8_t> values;
        bool requesting = false;
        int16_t values[64];
        bool continuousRequesting[64];
        unsigned int current_continuous_requesting_reg;
};