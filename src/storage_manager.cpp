#include <Arduino.h>
#include <EEPROM.h>

#include "storage_manager.h"

#define EEPROM_SIZE 512

void StorageManager::begin() {

    EEPROM.begin(EEPROM_SIZE);
}

void StorageManager::save(Settings &s) {

    EEPROM.put(0, s);

    EEPROM.commit();
}

void StorageManager::load(Settings &s) {

    EEPROM.get(0, s);
}