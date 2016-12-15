#include "MotorControl.h"

#define LEFT_FORWARD_PIN  2
#define LEFT_REVERSE_PIN  3
#define RIGHT_FORWARD_PIN 4
#define RIGHT_REVERSE_PIN 5

MotorControl Motor;

void MotorControl::init() {
    leftCounter = 0;
    rightCounter = 0;
    leftSpeed = 0;
    rightSpeed = 0;

    pinMode(LEFT_FORWARD_PIN, INPUT);
    pinMode(LEFT_REVERSE_PIN, INPUT);
    pinMode(RIGHT_FORWARD_PIN, INPUT);
    pinMode(RIGHT_REVERSE_PIN, INPUT);

    digitalWrite(LEFT_FORWARD_PIN, LOW);
    digitalWrite(LEFT_REVERSE_PIN, LOW);
    digitalWrite(RIGHT_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_REVERSE_PIN, LOW);
}

void MotorControl::setLeftSpeed(int8_t speed) {
    leftSpeed = speed;
}

void MotorControl::setRightSpeed(int8_t speed) {
    rightSpeed = speed;
}

void MotorControl::update() {
    uint16_t tmp = leftCounter;
    
    if (leftSpeed == 0) {
	pinMode(LEFT_FORWARD_PIN, INPUT);
	pinMode(LEFT_REVERSE_PIN, INPUT);
    } else if (leftSpeed > 0) {
	tmp += leftSpeed;  
	pinMode(LEFT_REVERSE_PIN, INPUT);
	if (tmp > 127) {
	    pinMode(LEFT_FORWARD_PIN, OUTPUT);
	} else {
	    pinMode(LEFT_FORWARD_PIN, INPUT);
	}
	leftCounter = tmp & 0x7f;
    } else {	
	tmp -= leftSpeed;  
	pinMode(LEFT_FORWARD_PIN, INPUT);
	if (tmp > 127) {
	    pinMode(LEFT_REVERSE_PIN, OUTPUT);
	} else {
	    pinMode(LEFT_REVERSE_PIN, INPUT);
	}
	leftCounter = tmp & 0x7f;
    }

    tmp = rightCounter;
    
    if (rightSpeed == 0) {
	pinMode(RIGHT_FORWARD_PIN, INPUT);
	pinMode(RIGHT_REVERSE_PIN, INPUT);
    } else if (rightSpeed > 0) {
	tmp += rightSpeed;  
	pinMode(RIGHT_REVERSE_PIN, INPUT);
	if (tmp > 127) {
	    pinMode(RIGHT_FORWARD_PIN, OUTPUT);
	} else {
	    pinMode(RIGHT_FORWARD_PIN, INPUT);
	}
	rightCounter = tmp & 0x7f;
    } else {	
	tmp -= rightSpeed;  
	pinMode(RIGHT_FORWARD_PIN, INPUT);
	if (tmp > 127) {
	    pinMode(RIGHT_REVERSE_PIN, OUTPUT);
	} else {
	    pinMode(RIGHT_REVERSE_PIN, INPUT);
	}
	rightCounter = tmp & 0x7f;
    }

}
