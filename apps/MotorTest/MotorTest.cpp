#include "Arduino.h"
#include "MotorControl.h"
#include <stdint.h>

volatile uint32_t waitCounter;

ISR(TIMER0_COMPA_vect) {
    Motor.update();
    if (waitCounter > 0) {
	waitCounter--;
    }
}

void waitMillis(int millis) {
    noInterrupts();
    waitCounter = millis;
    interrupts();

    while(waitCounter > 0) {
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello");
    Motor.init();

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
}

void loop() {
    for (int16_t idx = -128; idx < 128; idx++) {
	Motor.setLeftSpeed(idx);
	Motor.setRightSpeed(-idx);
	waitMillis(100);
    }
}
