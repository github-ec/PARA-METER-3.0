#pragma once
// Version 3.1 dated 2026/03/13 
// ec2021  
#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"

class wordPlayerClass {
private:
  DFRobotDFPlayerMini myDFPlayer;
  HardwareSerial* _serialPtr;
  bool _ready = false;
  bool _verbose = false;
  bool _doesPlay = false;
  bool _initFailed = false;
  void printDetail(uint8_t type, int value);

public:
  wordPlayerClass();
  
  // Wir übergeben die Pins jetzt hier direkt an die init-Funktion
  void init(int rx, int tx);
  
  void handlePlayerStatus();
  void playTitle(int value);
  void playTitle(int cat, int wordNo);
  bool playingTitle(int value);
  bool isReady();
  void setReady(bool value);
  bool initFailed();
  bool isPlaying();
  void messagesOn();
  void messagesOff();
  void setVolume(byte value);
  int getMaxFiles();
};

wordPlayerClass::wordPlayerClass() {
  _serialPtr = &Serial2; // ESP32 Hardware Serial 2
}

void wordPlayerClass::init(int rx, int tx) {
  _ready = false;
  _initFailed = true;

  // Die Pins werden erst hier beim Start der Hardware-Schnittstelle gesetzt
  _serialPtr->begin(9600, SERIAL_8N1, rx, tx);
  delay(500);
  bool isAck = false;
  bool doReset = true;
  // myDFPlayer.begin(serialPort, isACK, doReset);
  // 1. Parameter: Zeiger auf SoftwareSerial
  // 2. Parameter: false = keine Bestätigung vom Player abfordern, wenn ein Befehl abgearbeitet wird; true = Bestätigung abfordern
  // 3. Parameter: true = mit begin() ein Software-Reset des Players durchführen; false = kein Reset durchführen
  _initFailed = !myDFPlayer.begin(*_serialPtr, isAck, doReset);
  if (_initFailed) {
    Serial.println(F("DFPlayer init failed!"));
    return;
  }
  //************************************************************************
  Serial.print("\nWarte auf Dateisystem-Scan ");
  int fileCount = -1;
  unsigned long startWait = millis();
  // Schleife läuft, bis Dateien gefunden werden oder Timeout (hier 10s)
  // Das Zeichen | wird vor, der Punkt . nach Aufruf readFileCounts() ausgegeben,
  // damit lässt sich erkennen, ob das Programm bei readFileCounts() hängen bleibt
  while (fileCount == -1 && (millis() - startWait < 10000)) {
    Serial.print('|');
    fileCount = myDFPlayer.readFileCounts();
    delay(1000);  // Der Player-Library Zeit zur Verarbeitung zu geben ...
    Serial.print(".");
  }
  if (fileCount != -1) {
    Serial.print("\nPlayer bereit: Anzahl Dateien auf SD: ");
    Serial.println(fileCount);
  } else {
    Serial.println("\nTimeout: Player antwortet nicht auf Datenabfragen.");
    _initFailed = false;
    return;
  }

  //************************************************************************

  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(20);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  _ready = true;
}


// ... (Rest der Funktionen bleibt identisch)

bool wordPlayerClass::initFailed() { return _initFailed; }
void wordPlayerClass::setReady(bool value) { _ready = value; }
bool wordPlayerClass::isReady() { return _ready && !_initFailed; }
bool wordPlayerClass::isPlaying() { return _doesPlay; }
void wordPlayerClass::messagesOn() { _verbose = true; }
void wordPlayerClass::messagesOff() { _verbose = false; }
void wordPlayerClass::setVolume(byte value) { myDFPlayer.volume(value); }

bool wordPlayerClass::playingTitle(int value) {
  playTitle(value);
  return _doesPlay;
}

int wordPlayerClass::getMaxFiles() {
  if (_initFailed) return -1;
  return myDFPlayer.readFileCounts();
}

void wordPlayerClass::playTitle(int value) {
  if (_initFailed) return;
  if (value > 0) {
    myDFPlayer.playMp3Folder(value);
    _doesPlay = true;
    _ready = false;
  }
}

void wordPlayerClass::playTitle(int cat, int wordNo) {
  if (_initFailed) return;
   myDFPlayer.playFolder(cat, wordNo);
  _doesPlay = true;
  _ready = false;
}

void wordPlayerClass::handlePlayerStatus() {
  if (_initFailed) return;
  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();
    int value = myDFPlayer.read();
    printDetail(type, value);
    if (type == DFPlayerPlayFinished) {
        _doesPlay = false;
        _ready = true;
    }
  }
}

void wordPlayerClass::printDetail(uint8_t type, int value) {
  if (!_verbose) return;
  switch (type) {
    case TimeOut: Serial.println(F("DFP: Time Out!")); break;
    case DFPlayerPlayFinished: Serial.println(F("DFP: Finished!")); break;
    case DFPlayerError:
      Serial.print(F("DFP: Error "));
      Serial.println(value);
      break;
    default: break;
  }
}
