#include "RangeSensor.h"

#define TRIG_PIN 7
#define ECHO_PIN 8

RangeSensor Range;

void RangeSensor::init() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

int RangeSensor::getRange() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    return (pulseIn(ECHO_PIN, HIGH, 12000) / (2*29.1));
}
