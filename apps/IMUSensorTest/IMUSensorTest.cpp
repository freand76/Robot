#include "Arduino.h"
#include "IMUSensor.h"
#include "Kalman.h"

Kalman kalmanX;
double gyroX = 0;

void setup() {
    Serial.begin(115200);
    IMU.init();
    kalmanX.setAngle(90);
}

int count = 0;

void loop() {
    delay(10); // Update @ 100Hz
    IMU.update();
    double aAngle = atan2(IMU.data.accZ, IMU.data.accX)*(180.0/3.14) + 90;
    double gAngleDiff = double(IMU.data.gyroY)*(250.0/32768.0);
    double kAngle = kalmanX.getAngle(aAngle, gAngleDiff, 0.01);

    /* Send data @ 20Hz */
    if (++count == 5) {
	Serial.print(kAngle);
	Serial.print(",");
	Serial.println();
	count = 0;
    }
}
