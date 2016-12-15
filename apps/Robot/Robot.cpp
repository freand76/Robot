#include "Arduino.h"
#include "MotorControl.h"
#include "IMUSensor.h"
#include "Kalman.h"
#include <stdint.h>

volatile uint32_t millisCounter;
uint32_t nextMillis;
Kalman kalmanX;

ISR(TIMER0_COMPA_vect) {
    Motor.update();
    millisCounter++;
}

uint32_t getCurrentMillis() {
    return millisCounter;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello");
    Motor.init();
    IMU.init();
    kalmanX.setAngle(0);

    //set timer0 interrupt at 2kHz
    TCCR0A = 0;// set entire TCCR0A register to 0
    TCCR0B = 0;// same for TCCR0B
    TCNT0  = 0;// initialize counter value to 0
    // set compare match register for 2khz increments
    OCR0A = 248;// = (16*10^6) / (1000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);

    sei();
    nextMillis = getCurrentMillis() + 10;
}

void loop() {
    while(getCurrentMillis() < nextMillis) {
	/* Just Wait */
    }
    nextMillis += 10;

    IMU.update();
    double aAngle = atan2(IMU.data.accZ, IMU.data.accX)*(180.0/3.14);
    double gAngleDiff = double(IMU.data.gyroY)*(250.0/32768.0);
    double kAngle = kalmanX.getAngle(aAngle, gAngleDiff, 0.01);

    if ((kAngle < -20) || (kAngle > 20)) {
	Motor.setLeftSpeed(0);
	Motor.setRightSpeed(0);
    } else if ((kAngle >= -3) && (kAngle <= 3)) {
	Motor.setLeftSpeed(0);
	Motor.setRightSpeed(0);
    } else if (kAngle < -3) {
	Motor.setLeftSpeed(-127);
	Motor.setRightSpeed(-127);
    } else if (kAngle > 3) {
	Motor.setLeftSpeed(127);
	Motor.setRightSpeed(127);
    }

    static int count = 0;
    if (++count == 10) {
	count = 0;
	Serial.print(kAngle);
	Serial.print(",");
	Serial.println();
    }
}
