#include "Arduino.h"
#include "RangeSensor.h"
void setup() {
    Serial.begin(115200);
    Range.init();
}

void loop() {
    delay(20); // Update @ 20Hz
        
    int pulseLen = Range.getRange();
    
    if ((pulseLen > 0) && (pulseLen < 200)) {
	Serial.print(pulseLen);
	Serial.println(",");
    }    
}
