#include "LoRaUtil.h"

void Utils::printHex2(unsigned v) {
  v &= 0xff;
  if (v < 16) Serial.print('0');
  Serial.print(v, HEX);
}

void Utils::setHexString(String input) {
  _input = input;

  _stringVector.clear();
  _hexVectorMSB.clear();
  _hexVectorLSB.clear();

  _stringToVector();
  _stringToHex();
  _msbToLsb();
}

std::vector<int> Utils::getMSBVector() {
  return _hexVectorMSB;
}

std::vector<int> Utils::getLSBVector() {
  return _hexVectorLSB;
}

int * Utils::getMSBArray() {
  return &_hexVectorMSB[0];
} 

int * Utils::getLSBArray() {
  return &_hexVectorLSB[0];
} 

void Utils::_stringToHex() {
  int subResult;

  for (auto it = _stringVector.begin(); it < _stringVector.end(); it++) {
    subResult = 0;
    subResult = _charToHex((*it)[0]);
    subResult <<= 4;
    subResult |= _charToHex((*it)[1]);
    _hexVectorMSB.push_back(subResult);
  }
}

void Utils::_msbToLsb() {
  for (auto it = _hexVectorMSB.end() - 1; it >= _hexVectorMSB.begin(); it--) {
    _hexVectorLSB.push_back(*it);
  }
}

void Utils::_stringToVector() {
  String subString = "";

  for (int i = 0; i < _input.length(); i++) {
    subString += _input[i];

    if (i % 2) {
      _stringVector.push_back(subString);
      subString.clear();
    }
  }
}

int Utils::_charToHex(char value) {
  value = (char)tolower(value);

  switch (value) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    default:  return -1;
  }
}