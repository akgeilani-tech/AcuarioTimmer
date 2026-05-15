#include <Arduino.h>
#include <WiFi.h>
#include "settings.h"

#include "storage_manager.h"
#include "wifi_manager.h"
#include "rtc_manager.h"
#include "ntp_manager.h"
#include "scheduler.h"
#include "led_manager.h"
#include "servo_manager.h"
#include "webserver_manager.h"

Settings settings;

StorageManager storageManager;

WifiManager wifiManager;

RTCManager rtcManager;

NTPManager ntpManager;

Scheduler scheduler;

LEDManager ledManager;

ServoManager servoManager;

WebServerManager webServerManager;

unsigned long lastWiFiCheck = 0;

bool reconnecting = false;
bool wifiOK = false;

void setup() {

    Serial.begin(115200);

    delay(2000);

    storageManager.begin();

    memset(
        &settings,
        0,
        sizeof(settings)
    );

    storageManager.load(settings);

    rtcManager.begin();

    ledManager.begin();

    servoManager.begin();

    // Verifica si WiFI está configurado y conectado, si no, inicia el modo AP para configuración
    // Verificar si existe configuración WiFi 
    if (
        wifiManager.isConfigured()
    ) {

        Serial.println(
            "WiFi configured"
        );

    // Intentar conexión

        wifiOK =
            wifiManager.connect();

    // Verificar acceso real a internet

        if (wifiOK) {

            Serial.println(
                "Checking internet..."
            );

            wifiOK =
                wifiManager.hasInternet();
        }

    // Si falla cualquier cosa iniciar AP para configuración

        if (!wifiOK) {

            Serial.println(
                "Starting setup AP..."
            );

            wifiManager.startAP();
        }
    }
    else {

        Serial.println(
            "WiFi not configured"
        );

    // Configuración inicial de WiFi, iniciar AP para configuración

        wifiManager.startAP();
    }

    //Solo si internet OK

    if (wifiOK) {

        Serial.println(
            "Internet OK"
        );

        ntpManager.begin();

        delay(2000);

        ntpManager.update();
    }
    webServerManager.begin();

    scheduler.begin();

    Serial.println(
        "System Ready"
    );
}

void loop() {

    webServerManager.update();

    scheduler.update();

    // Sincroniza el RTC con NTP cada hora
    static unsigned long lastNTP = 0;

    if (
        millis() - lastNTP >
        3600000
    ) {
        ntpManager.update();
        lastNTP = millis();
    }
}