#include <Arduino.h>

#include "config.h"
#include "led_manager.h"

void LEDManager::begin() {

    pinMode(LED_PIN, OUTPUT);
}

void LEDManager::on() {

    digitalWrite(LED_PIN, HIGH);
}

void LEDManager::off() {

    digitalWrite(LED_PIN, LOW);
}