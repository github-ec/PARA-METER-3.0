#pragma once
#include "WordLists.h"
#include <Arduino.h>

class WordStorage {
  private:
    int _katID = 0;
    int _totalWords = 0;
    int _wordIndex = 0;
    int _numberOfCategories = NumberOfCategories;
    const char* _chosenList = nullptr;
    char _wordBuffer[40];

    int _countWords(const char* flashStr);
    void _getNthWord(const char* flashStr, int n, char* buffer, size_t bufferSize);
    int _calculateIndex(int data);
    void _getListData(int katID);

  public:
    WordStorage();
    int numberOfCategories() const { return _numberOfCategories; }
    int katID() const              { return _katID; }
    int totalWords() const         { return _totalWords; }
    int wordIndex() const          { return _wordIndex; }
    const char* word() const       { return _wordBuffer; }

    int totalWords(int katID);
    bool wordFromData(int data);
    bool wordFromCatEntry(int katID, int entry);
};

WordStorage::WordStorage() {}

int WordStorage::_countWords(const char* flashStr) {
  if (!flashStr) return 0;
  int count = 0;
  const char* ptr = flashStr;
  while (*ptr != '\0') {
    if (*ptr == '/') count++;
    ptr++;
  }
  return count + 1;
}

void WordStorage::_getNthWord(const char* flashStr, int n, char* buffer, size_t bufferSize) {
  if (bufferSize == 0 || !flashStr) return;
  int currentWord = 0;
  const char* ptr = flashStr;
  while (currentWord < n && *ptr != '\0') {
    if (*ptr == '/') currentWord++;
    ptr++;
  }
  size_t j = 0;
  while (j < (bufferSize - 1) && *ptr != '/' && *ptr != '\0') {
    buffer[j++] = *ptr++;
  }
  buffer[j] = '\0';
}

int WordStorage::_calculateIndex(int data) {
  int index = (data ^ (int)(millis() & 0xFF)) % _totalWords;
  return abs(index);
}

int WordStorage::totalWords(int katID) {
  _getListData(constrain(katID, 0, _numberOfCategories - 1));
  return _totalWords;
}

void WordStorage::_getListData(int katID) {
  if (katID >= 0 && katID < _numberOfCategories) {
    _katID = katID;
    _chosenList = cat_table[katID];
  } else {
    _chosenList = nullptr;
  }
  _totalWords = _countWords(_chosenList);
}

bool WordStorage::wordFromData(int data) {
  return wordFromCatEntry(abs(data) % _numberOfCategories, -data);
}

bool WordStorage::wordFromCatEntry(int katID, int entry) {
  katID = constrain(katID, 0, _numberOfCategories - 1);
  _getListData(katID);
  if (!_chosenList) return false;
  if (entry < 0) entry = _calculateIndex(-entry);
  if (entry >= 0 && entry < _totalWords) {
    _wordIndex = entry;
    _getNthWord(_chosenList, _wordIndex, _wordBuffer, sizeof(_wordBuffer));
    return true;
  }
  return false;
}
