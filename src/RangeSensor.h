#ifndef RANGE_SENSOR_H
#define RANGE_SENSOR_H

#include "Arduino.h"

class RangeSensor {
public:
    void init();
    int getRange();
};

extern RangeSensor Range;

#endif // RANGE_SENSOR_H
