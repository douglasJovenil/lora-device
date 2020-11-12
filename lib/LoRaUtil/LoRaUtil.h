#ifndef __LORA__UTIL__H__
#define __LORA__UTIL__H__

#include <Arduino.h>
#include <vector>

class Utils {
  public:
    void printHex2(unsigned v);
    std::vector<int> getMSBVector();
    std::vector<int> getLSBVector();
    int * getMSBArray();
    int * getLSBArray();
    void setHexString(String input);

  private:
    String _input = "";
    std::vector<String> _stringVector;
    std::vector<int> _hexVectorMSB;
    std::vector<int> _hexVectorLSB;

    void _stringToHex();
    void _msbToLsb();
    void _stringToVector();
    int _charToHex(char value);
};

#endif