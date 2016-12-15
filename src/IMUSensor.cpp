#include "IMUSensor.h"
#include "Arduino.h"
#include "Wire.h"

IMUSensor IMU;

void IMUSensor::init() {
    Wire.begin();
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}

void IMUSensor::update() {
    Wire.beginTransmission(0x68);
    // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.write(0x3B);  
    Wire.endTransmission(false);
      // request a total of 14 registers
    Wire.requestFrom(0x68, 14, true);
    data.accX = Wire.read()<<8 | Wire.read();
    data.accY = Wire.read()<<8 | Wire.read(); 
    data.accZ = Wire.read()<<8 | Wire.read();
    data.temp = Wire.read()<<8 | Wire.read();
    data.gyroX = Wire.read()<<8 | Wire.read();
    data.gyroY = Wire.read()<<8 | Wire.read();
    data.gyroZ = Wire.read()<<8 | Wire.read();
}
