
# Aquarium Timer Controller - Raspberry Pi Pico W

Sistema IoT para automatización de acuarios utilizando Raspberry Pi Pico W.

Permite:

- Programar horarios de encendido/apagado de luces
- Programar horarios de alimentación automática
- Sincronización horaria mediante NTP
- Respaldo horario mediante RTC DS3231
- Configuración WiFi vía portal cautivo
- Interfaz web local
- Almacenamiento persistente de configuración
- Funcionamiento autónomo sin internet

---

## Hardware

### Microcontrolador

- Raspberry Pi Pico W

### RTC

- DS3231

### Actuadores

- LED / Relay para iluminación
- Servo motor para alimentador automático

---

## Pines utilizados

| Función | GPIO |
| --- | --- |
| RTC SDA | GP4 |
| RTC SCL | GP5 |
| Salida LED | GP9 |
| Servo | GP16 |

---

## Características

### WiFi Setup

En el primer arranque el sistema crea un Access Point:

```text
SSID: AquariumSetup
```

Desde ahí se configura:

- SSID WiFi local
- Password WiFi

Luego el dispositivo:

1. Guarda configuración
2. Reinicia automáticamente
3. Deshabilita AP
4. Se conecta a la red local
5. Habilita interfaz web local

---

## Interfaz Web

La interfaz permite:

- Configurar horarios
- Ver estado del scheduler
- Ver hora RTC actual
- Guardar configuración persistentemente

---

## Scheduler

### Luces

- Hora ON
- Hora OFF

### Alimentador

- Feed Time 1
- Feed Time 2

---

## RTC + NTP

El sistema utiliza:

- NTP para sincronización inicial
- RTC DS3231 para mantener hora durante cortes eléctricos

Zona horaria configurada:

```text
UTC -4
(Bolivia)
```

---

## Arquitectura

```text
WiFi
   ↓
NTP
   ↓
RTC DS3231
   ↓
Scheduler
   ↓
Lights + Feeder
   ↓
Web Interface
```

---

## Estructura del proyecto

```text
AcuarioTimer/
│
├── include/
│   ├── config.h
│   ├── ntp_manager.h
│   ├── rtc_manager.h
│   ├── scheduler.h
│   ├── storage_manager.h
│   ├── webserver_manager.h
│   └── wifi_manager.h
│
├── src/
│   ├── main.cpp
│   ├── ntp_manager.cpp
│   ├── rtc_manager.cpp
│   ├── scheduler.cpp
│   ├── storage_manager.cpp
│   ├── webserver_manager.cpp
│   └── wifi_manager.cpp
│
├── data/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
└── platformio.ini
```

---

## Dependencias

### PlatformIO

```ini
lib_deps =
    arduino-libraries/NTPClient
    adafruit/RTClib
    bblanchon/ArduinoJson
```

---

## Compilación

### Instalar PlatformIO

Visual Studio Code + PlatformIO IDE.

---

## Compilar

```bash
pio run
```

---

## Subir firmware

### Entrar en modo BOOTSEL

1. Mantener presionado botón BOOTSEL
2. Conectar USB
3. Soltar botón

---

### Upload

```bash
pio run -t upload
```

---

## Monitor Serial

```bash
pio device monitor
```

---

## Configuración monitor serial

```ini
monitor_speed = 115200
monitor_filters = time
```

---

## Configuración PlatformIO

### platformio.ini

```ini
[env:picow]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = rpipicow
framework = arduino
board_build.filesystem_size = 0.5m

monitor_speed = 115200

build_flags =
    -std=gnu++17

lib_deps =
    adafruit/RTClib
    bblanchon/ArduinoJson
    arduino-libraries/NTPClient
```

---

## Recomendaciones eléctricas

### Servo motor

NO alimentar servo desde:

- 3.3V del Pico
- USB directamente

Usar:

- Fuente externa 5V
- GND común
- Capacitor 470uF cercano al servo

---

## Recomendaciones de estabilidad WiFi

- Evitar delays largos
- Usar `yield()`
- Deshabilitar WiFi sleep mode
- No usar AP + STA simultáneo
- Mantener loop no bloqueante

---

## Estado del proyecto

- [x] WiFi Setup Portal
- [x] RTC DS3231
- [x] NTP Sync
- [x] Scheduler
- [x] Web Interface
- [x] EEPROM Storage
- [x] Local Dashboard
- [ ] OTA Update
- [ ] WebSocket Realtime
- [ ] Manual Override
- [ ] MQTT Support

---

## Licencia

GNU AFFERO GENERAL PUBLIC LICENSE Version 3, 19 November 2007

---

## Autor

Ing. Ahmed Kamil Geilani

>>>>>>> a2e984f21f2c81fa82ab3631926fbcb78430029b
