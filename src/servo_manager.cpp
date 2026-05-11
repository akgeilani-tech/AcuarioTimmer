#include <Arduino.h>
#include <Servo.h>

#include "config.h"
#include "servo_manager.h"

Servo feederServo;

void ServoManager::begin() {

    feederServo.attach(SERVO_PIN);

    feederServo.write(0);
}

void ServoManager::feed() {

    feederServo.write(90);

    delay(1000);

    feederServo.write(0);

    delay(1000);
}