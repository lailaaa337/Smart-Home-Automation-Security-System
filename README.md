# 🏠 ESP32 Smart Home Automation & Security System

An integrated smart home system built on **ESP32 WROOM** that combines RFID access control, IoT cloud connectivity, ambient light sensing, and motion detection for comprehensive home automation and security.

---

## 📋 Project Overview

This project implements a multi-functional smart home system with the following capabilities:

- 🔐 RFID-based door lock control using RC522 module  
- ☁️ Remote LED control via Arduino IoT Cloud  
- 🌞 Ambient light monitoring using analog light sensor  
- 🚶 Motion detection with PIR sensor (HC-SR501)  
- 📶 WiFi connectivity via ESP32  

All components are integrated and controlled through an ESP32 microcontroller.

---

## 🧰 Hardware Requirements

### 🔹 Main Controller
- ESP32 WROOM  
- USB Cable (programming & power)  
- Breadboard & Jumper Wires  

### 🔹 RFID Door Lock System
- RC522 RFID Module (13.56 MHz) + Tags/Cards  
- Center-Lock Actuator  
- H-Bridge Motor Driver (L298N)  
- 7805 Voltage Regulator (12V → 5V)  
- 16x2 I2C LCD Display  
- 12V Buzzer  

### 🔹 IoT Cloud Control
- LED  
- 220Ω Resistor  

### 🔹 Light Sensing
- Light Sensor Module (KY-018 / TEMT6000 / Photoresistor)

### 🔹 Motion Detection
- PIR Motion Sensor (HC-SR501)

---

## 🔌 Wiring Configuration

### RFID RC522 (SPI Connection)

| RC522 Pin | ESP32 Pin |
|------------|------------|
| SDA/SS     | GPIO5     |
| SCK        | GPIO18    |
| MOSI       | GPIO23    |
| MISO       | GPIO19    |
| RST        | GPIO21    |

---

### I2C LCD Display

| LCD Pin | ESP32 Pin |
|----------|------------|
| SDA      | GPIO21     |
| SCL      | GPIO22     |

---

### Actuator & Buzzer

| Component | ESP32 Pin |
|------------|------------|
| IN1        | GPIO12     |
| IN2        | GPIO13     |
| Buzzer     | GPIO15     |

---

### IoT LED

| Component | ESP32 Pin |
|------------|------------|
| LED (220Ω) | GPIO2     |

---

### Light Sensor

| Sensor Pin | ESP32 Pin |
|------------|------------|
| VCC        | 3.3V       |
| GND        | GND        |
| OUT        | GPIO34     |

---

### PIR Sensor

| Sensor Pin | ESP32 Pin |
|------------|------------|
| VCC        | 5V         |
| GND        | GND        |
| OUT        | GPIO (configure in code) |

---

## 📚 Software Requirements

### 🔹 Required Libraries
Install via Arduino Library Manager:

- MFRC522
- LiquidCrystal_I2C
- SPI.h
- WiFi.h
- ArduinoIoTCloud.h
- Arduino_ConnectionHandler.h

### 🔹 Development Environment
- Arduino IDE or PlatformIO  
- ESP32 Board Package  
- Arduino IoT Cloud Account (optional)

---

## 🚀 Setup Instructions

### 1️⃣ Arduino IoT Cloud (Optional)

1. Visit https://app.arduino.cc  
2. Add Device → Select ESP32  
3. Create a Thing  
4. Add Variable:
   - Name: `Led`
   - Type: Boolean
   - Permission: Read & Write
   - Update: On change
5. Download `thingProperties.h`  
6. Add it to your project folder  

---

### 2️⃣ Code Deployment

1. Install required libraries  
2. Configure WiFi credentials in `arduino_secrets.h`  
3. Upload code to ESP32  
4. Open Serial Monitor (115200 baud)

---

## 📁 Project Structure

```
├── main.ino
├── thingProperties.h
├── arduino_secrets.h
└── README.md
```

---

## 🧠 Key Code Snippets

### Light Sensor Reading

```cpp
const int lightSensorPin = 34;
analogReadResolution(12);
int lightValue = analogRead(lightSensorPin);
```

### RFID Initialization

```cpp
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 21

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
}
```

---

## 📊 System Flow

1. System Boot – Initialize peripherals  
2. WiFi Connection – Connect to network  
3. RFID Scanning – Detect card/tag  
4. Access Validation – Control lock & display status  
5. Environmental Monitoring – Read light levels  
6. Motion Detection – Trigger events  
7. Cloud Sync – Update LED from IoT dashboard  

---

## 👥 Team Members

- Laila Tarek – 231003520  
- Hana Tariq – 231000481  
- Miran Samer – 231010991  
- Hana Mabrouk – 231002230  
- Lojaine Mohamed – 231000453  

**Supervised by:**  
Dr. Omar Shalash  
Eng. Samar  

Arab Academy for Science & Technology  
College of Computing & Information Technology  
Artificial Intelligence Department  

---

## 📜 License

This project is developed for academic purposes. All rights reserved.

---

## 🔧 Troubleshooting

| Issue | Solution |
|--------|-----------|
| RFID not reading | Check SPI wiring & 3.3V supply |
| LCD not displaying | Verify I2C address (0x27 / 0x3F) |
| WiFi not connecting | Check credentials & 2.4GHz network |
| Sensor values unstable | Verify ADC pin & add filtering capacitor |

---

## 🚧 Future Improvements

- EEPROM storage for authorized RFID tags  
- Automated home routines  
- Mobile application integration  
- Multiple user profiles  
- Cloud data logging  




## 🎥 Project Demo

<p align="center">
  <a href="vid1.gif">
    <img src="vid1.gif" width="800"/>
  </a>
</p>

<p align="center">
  <a href="vid2.gif">
    <img src="vid2.gif" width="800"/>
  </a>
</p>