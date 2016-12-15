#ifndef IMU_SENSOR_H
#define IMU_SENSOR_H

#include <stdint.h>

typedef struct {
    int16_t accX;
    int16_t accY;
    int16_t accZ;
    int16_t temp;
    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;
} IMUSensorData_t;

class IMUSensor {
public:
    void init();
    void update();
    IMUSensorData_t data;
};

extern IMUSensor IMU;

#endif // IMU_SENSOR_H
