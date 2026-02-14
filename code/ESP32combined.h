/*
 * Integrated ESP32 Project: RFID Door Lock, IoT Cloud, Light & Motion Sensors
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "thingProperties.h" // Ensure this file exists in your project folder

// --- PIN DEFINITIONS (ESP32-WROOM) ---
#define RST_PIN      21   // RC522 Reset
#define SS_PIN       5    // RC522 Chip Select
#define BUZZER_PIN   15   // Buzzer
#define LOCK_PIN     12   // H-Bridge IN1
#define UNLOCK_PIN   13   // H-Bridge IN2
#define LED_PIN      2    // Status LED
#define LIGHT_SENSOR_PIN 34 // Analog LDR Pin
#define PIR_SENSOR_PIN   19 // Motion Sensor Pin

// --- GLOBALS ---
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pinStateCurrent = LOW;
int pinStatePrevious = LOW;

// Authorized RFID UIDs
byte authorizedUIDs[][4] = {
  {0x01, 0xA3, 0xB2, 0xC4} // Example UID - Replace with your tag's ID
};

void setup() {
  // Serial Initialization
  Serial.begin(115200);
  delay(500);

  // RFID & SPI Initialization
  SPI.begin();
  mfrc522.PCD_Init();

  // I2C & LCD Initialization
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.print("RFID Door Lock");

  // Pin Modes
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(UNLOCK_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);

  // ADC Resolution
  analogReadResolution(12);

  // IoT Cloud Initialization
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  digitalWrite(LED_PIN, LOW);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  delay(2000);
  lcd.clear();
}

void loop() {
  ArduinoCloud.update();
  
  // 1. LIGHT SENSOR LOGIC
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  // Serial.print("Light Level: "); Serial.println(lightValue);

  // 2. MOTION SENSOR (PIR) LOGIC
  pinStatePrevious = pinStateCurrent;
  pinStateCurrent = digitalRead(PIR_SENSOR_PIN);

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {
    Serial.println("Motion detected!");
  } else if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {
    Serial.println("Motion stopped!");
  }

  // 3. RFID LOGIC
  lcd.setCursor(0, 0);
  lcd.print("Scan Tag...");

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.clear();
    lcd.print("Tag Detected");

    bool isAuthorized = false;
    for (byte i = 0; i < sizeof(authorizedUIDs) / 4; i++) {
      if (memcmp(mfrc522.uid.uidByte, authorizedUIDs[i], 4) == 0) {
        isAuthorized = true;
        break;
      }
    }

    if (isAuthorized) {
      lcd.setCursor(0, 1);
      lcd.print("Access Granted!");
      digitalWrite(UNLOCK_PIN, HIGH);
      tone(BUZZER_PIN, 1000, 500);
      delay(3000);
      digitalWrite(UNLOCK_PIN, LOW);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Access Denied!");
      tone(BUZZER_PIN, 300, 1000);
    }

    delay(2000);
    lcd.clear();
    mfrc522.PICC_HaltA();
  }
}

// 4. CLOUD CALLBACK
void onLEDChange() {
  if (lED == 1) { // 'lED' variable name from your cloud properties
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}