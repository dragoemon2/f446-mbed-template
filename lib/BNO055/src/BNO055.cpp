#include "BNO055.hpp"

BNO055::BNO055(PinName tx, PinName rx, std::chrono::milliseconds internal): serial(tx, rx)
{
    serial.baud(115200);
    
    serial.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );

    write(0x3D, 0x0C);

    requestValueContinuous(getRegister(VECTOR_TYPE::EULER, DIRECTION::X));
    requestValueContinuous(getRegister(VECTOR_TYPE::MAG, DIRECTION::X));
    requestValueContinuous(getRegister(VECTOR_TYPE::MAG, DIRECTION::Y));
    //requestValueContinuous(getRegister(VECTOR_TYPE::EULER, DIRECTION::X));

    ticker.attach([this]{loop();}, internal);
}

int8_t BNO055::getRegister(VECTOR_TYPE vec_type, DIRECTION direction){
    return char(vec_type) + 2*int(direction);
}


void BNO055::write(unsigned char reg_add, unsigned char value){
    char data[] = {START_BYTE, WRITE_BYTE, reg_add, 0x01, value};
    serial.write(data, 5);
}

void BNO055::requestValue(unsigned char reg_add){
    requested_reg = reg_add;
    char data[] = {START_BYTE, READ_BYTE, requested_reg, 0x02};
    serial.write(data, 4);
    serial.attach([this]{interrupt();});
    requesting = true;
}

void BNO055::requestValueContinuous(unsigned char reg_add){
    continuousRequesting[reg_add] = true;
}

void BNO055::stopRequestValueContinuous(unsigned char reg_add){
    continuousRequesting[reg_add] = false;
}

void BNO055::interrupt(){
    char c;
    serial.read(&c, 1);

    switch (process)
    {
    case STARTING:
        if(c == RESPONSE_BYTE){
            process = SET_LENGTH;
        }
        break;
    
    case SET_LENGTH:
        length = c;
        index = 0;
        process = RECEIVING;
        break;

    case RECEIVING:
        buffer[index] = c;
        index++;

        if(index == length){
            process = STARTING;
            onReceive(length);
        }
        break;
    
    default:
        break;
    }
}

void BNO055::loop(){
    /*
    if(requesting){
        return;
    }
    */

   
    unsigned int reg = (current_continuous_requesting_reg + 1) % 64;
    while(reg != current_continuous_requesting_reg){
        reg = (reg+1)%64;
        if(continuousRequesting[reg]){
            current_continuous_requesting_reg = reg;
            requestValue(reg);
            return;
        }
    }
}

float BNO055::getYawDegrees(){
    return getValue(getRegister(VECTOR_TYPE::EULER, DIRECTION::X)) / 16 - 180;
}

float BNO055::getMagDegrees(){
    //return 180 / PI * atan2(getRegister(VECTOR_TYPE::MAG, DIRECTION::X), getRegister(VECTOR_TYPE::MAG, DIRECTION::Y));
    return 180 / PI * atan2(-getValue(getRegister(VECTOR_TYPE::MAG, DIRECTION::Y)), -getValue(getRegister(VECTOR_TYPE::MAG, DIRECTION::X)));
}


void BNO055::onReceive(int length){
    values[requested_reg] = (int16_t(buffer[1]) << 8) | int16_t(buffer[0]);
    requesting = false;
}

int16_t BNO055::getValue(unsigned char reg_add){
    return values[reg_add];
}