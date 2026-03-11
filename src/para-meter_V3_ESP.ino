/* 
 * DIY "PARA"-METER SYSTEM (ESP32 EDITION)
 * Version 3.0 mit Hardware-Serial & ADC-Optimierung
 * Datum: 2026/03/11
 */

#include <Arduino.h>

// --- LCD VORBEREITUNG ---
#include "GermanLCD.h"

// --- WORTLISTEN HANDLING (ESP32 FLASH-MAPPING) ---
#include "WordStorage.h"
WordStorage wordStore;

// --- DFROBOT PLAYER MINI HANDLING ---
#include "WordPlayer.h"

// ESP32 Pin-Definitionen
// Pin 16/17 sind Standard für Serial2 (DFPlayer)
// Pin 34/35 sind gute Analog-Eingänge (ADC1), da sie kein WiFi-Interferenzen haben
constexpr int EMF_PIN = 34;   // Analog In (ehemals A0)
constexpr int SEED_PIN = 35;  // Offener Pin für Random Seed (ehemals A1)
constexpr byte RXPin = 16;
constexpr byte TXPin = 17;

// Objekt-Instanziierung
wordPlayerClass wordPlayer;

// --- HAUPTPROGRAMM VARIABLEN ---
unsigned long lastTime = 0;
bool verbose = true;  // Auf true gesetzt für Debugging am PC

// Prototypen
void lcdZeile2(const char* buf);
void lcdWortAusgabe();
void serielleAusgabe(int Idx, int data);

void setup() {
  // ESP32 nutzt 12-Bit Auflösung (0-4095), wir kalibrieren den Seed
  analogReadResolution(12);
  randomSeed(analogRead(SEED_PIN) + micros());

  Serial.begin(115200);
  delay(1000);  // Zeit für Serial Monitor

  // LCD Initialisierung (über Noiasca oder LiquidCrystal_I2C)
  InitLCDGerman();
  lcd.setCursor(0, 0);
  lcd.print("PARA-METER 3.0");
  lcdZeile2("Initialisieren");

  // DFPlayer initialisieren
  wordPlayer.init(RXPin, TXPin);
  wordPlayer.messagesOff();

  Serial.println(F("\n--- PARA-METER DIY GESTARTET (ESP32) ---"));
  Serial.printf("Warte auf EMF-Ausschlag an Pin %d...\n", EMF_PIN);

  lcd.setCursor(0, 1);
  lcd.print("      Bereit      ");
  delay(1000);
}

void loop() {
  int currentRead = analogRead(EMF_PIN);

  // Alle 3 Sekunden bei Schwellenwert reagieren
  // Hinweis: 250 auf 8-Bit (Arduino) entspricht ca. 1000 auf 12-Bit (ESP32)
  if (millis() - lastTime > 3000) {
    if (currentRead > 800) {  // Schwellenwert angepasst für ESP32 ADC
      lastTime = millis();

      if (wordStore.wordFromData(currentRead)) {
        int cat = wordStore.katID()+1;
        int idx = wordStore.wordIndex()+1;
        serielleAusgabe(currentRead);
        lcdWortAusgabe();
        wordPlayer.playTitle(cat,idx);
      }
    }
  }

  // Überprüft, ob der Player fertig ist und setzt Status zurück
  wordPlayer.handlePlayerStatus();

  delay(50);  // Kleiner Delay zur Entlastung der CPU
}

void lcdWortAusgabe() {
  lcdZeile2(wordStore.word());
}

void lcdZeile2(const char* buf) {
  lcd.setCursor(0, 1);
  lcd.print("                ");  // Zeile löschen (16 Zeichen)
  lcd.setCursor(0, 1);
  lcd.print(buf);
}

void serielleAusgabe(int data) {
  Serial.print(F("[EVENT] Energie: "));
  Serial.print(data);
  if (verbose) {
    Serial.print(F(" | Kat: "));
    Serial.print(wordStore.katID());
    Serial.print(F(" ("));
    // Erste Wort im Puffer ist oft der Kategoriename (siehe WordLists)
    Serial.print(F(") | Idx: "));
    Serial.print(wordStore.wordIndex());
  }
  Serial.print(F(" | Wort: "));
  Serial.println(wordStore.word());
}
