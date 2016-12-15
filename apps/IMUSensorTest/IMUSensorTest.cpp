#include "Arduino.h"
#include "IMUSensor.h"

void setup() {
    Serial.begin(115200);
    Serial.println("MultiShield");
    Serial.println(__DATE__);
    IMU.init();
}

uint32_t count = 0;

void loop() {
    delay(100);
    IMU.update();
    Serial.print(count++); Serial.print(", ");
    Serial.print(IMU.data.accX); Serial.print(", ");
    Serial.print(IMU.data.accZ); Serial.print(", ");
    Serial.println();
}
