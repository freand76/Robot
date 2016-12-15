#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "Arduino.h"

class MotorControl {
public:
    void init();
    void setLeftSpeed(int8_t speed);
    void setRightSpeed(int8_t speed);
    void update();
private:
    uint8_t leftCounter;
    int8_t leftSpeed;
    uint8_t rightCounter;
    int8_t rightSpeed;
};

extern MotorControl Motor;

#endif // MOTOR_CONTROL_H
