#include <Arduino.h>
#include <WebServer.h>
#include <ArduinoJson.h>

#include "web_pages.h"
#include "settings.h"
#include "storage_manager.h"
#include "webserver_manager.h"
#include "rtc_manager.h"
#include "wifi_manager.h"

extern Settings settings;
extern RTCManager rtcManager;
extern StorageManager storageManager;
extern Settings settings;
extern StorageManager storageManager;
extern WifiManager wifiManager;

WebServer server(80);

static void handleSaveWifi() {

    JsonDocument doc;

    deserializeJson(
        doc,
        server.arg("plain")
    );

    strlcpy(
        settings.wifiSSID,
        doc["ssid"] | "",
        sizeof(settings.wifiSSID)
    );

    strlcpy(
        settings.wifiPassword,
        doc["password"] | "",
        sizeof(settings.wifiPassword)
    );

    storageManager.save(settings);

    server.send(
        200,
        "text/plain",
        "Saved"
    );

    delay(2000);

    rp2040.reboot();
}

static void handleTime() {

    server.send(
        200,
        "text/plain",
        rtcManager.getTimeString()
    );
}

static void handleRoot() {

    // if (
    //     !wifiManager.connected()
    // ) {

    //     server.send_P(
    //         200,
    //         "text/html",
    //         WIFI_SETUP_HTML
    //     );

    //     return;
    // }

    server.send_P(
        200,
        "text/html",
        INDEX_HTML
    );
}

static void handleSave() {

    JsonDocument doc;

    deserializeJson(
        doc,
        server.arg("plain")
    );

    strlcpy(
        settings.lightsOn,
        doc["lights_on"] | "",
        sizeof(settings.lightsOn)
    );

    strlcpy(
        settings.lightsOff,
        doc["lights_off"] | "",
        sizeof(settings.lightsOff)
    );

    strlcpy(
        settings.feed1,
        doc["feed1"] | "",
        sizeof(settings.feed1)
    );

    strlcpy(
        settings.feed2,
        doc["feed2"] | "",
        sizeof(settings.feed2)
    );

    storageManager.save(settings);

    server.send(
        200,
        "text/plain",
        "OK"
    );
}

static void handleFactoryReset() {

    Serial.println(
        "Factory Reset Requested"
    );

    server.send(
        200,
        "text/plain",
        "Device resetting..."
    );

    delay(1000);

    /*
        Limpiar configuración
    */

    storageManager.reset();

    delay(1000);

    /*
        Desconectar WiFi
    */

    WiFi.disconnect(true);

    delay(100);

    /*
        Apagar AP
    */

    WiFi.softAPdisconnect(true);

    delay(100);

    /*
        Deshabilitar WiFi
    */

    WiFi.mode(WIFI_OFF);

    delay(1000);

    /*
        Reiniciar RP2040
    */

    rp2040.restart();
}

static void handleSchedulerStatus() {

    JsonDocument doc;

    doc["lightsOn"] =
        settings.lightsOn;

    doc["lightsOff"] =
        settings.lightsOff;

    doc["feed1"] =
        settings.feed1;

    doc["feed2"] =
        settings.feed2;

    String response;

    serializeJson(
        doc,
        response
    );

    server.send(
        200,
        "application/json",
        response
    );
}

void WebServerManager::begin() {

    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );

    server.on(
        "/save",
        HTTP_POST,
        handleSave
    );
    
    server.on(
        "/time",
        HTTP_GET,
        handleTime
    );
    
    server.on(
        "/savewifi",
        HTTP_POST,
        handleSaveWifi
    );

    server.on(
        "/scheduler",
        HTTP_GET,
        handleSchedulerStatus
    );

    server.on(
        "/factoryreset",
        HTTP_POST,
        handleFactoryReset
    );

    server.begin();
}

void WebServerManager::update() {

    server.handleClient();
}