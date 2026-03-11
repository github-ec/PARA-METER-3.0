#pragma once
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
  _initFailed = false;
  
  // Die Pins werden erst hier beim Start der Hardware-Schnittstelle gesetzt
  _serialPtr->begin(9600, SERIAL_8N1, rx, tx);
  
  delay(500);

  if (!myDFPlayer.begin(*_serialPtr)) {
    Serial.println(F("DFPlayer init failed!"));
    _initFailed = true;
    return;
  }
  
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
