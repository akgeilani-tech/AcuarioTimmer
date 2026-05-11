#include <Arduino.h>

#include "settings.h"
#include "scheduler.h"
#include "rtc_manager.h"
#include "led_manager.h"
#include "servo_manager.h"

extern Settings settings;

extern RTCManager rtcManager;

extern LEDManager ledManager;

extern ServoManager servoManager;

String lastFeed = "";

void Scheduler::begin() {
}

void Scheduler::update() {

    String now =
        rtcManager.getTimeString();

    if (
        now >= settings.lightsOn &&
        now < settings.lightsOff
    ) {

        ledManager.on();

    } else {

        ledManager.off();
    }

    if (
        now == settings.feed1 &&
        lastFeed != now
    ) {

        servoManager.feed();

        lastFeed = now;
    }

    if (
        now == settings.feed2 &&
        lastFeed != now
    ) {

        servoManager.feed();

        lastFeed = now;
    }
}