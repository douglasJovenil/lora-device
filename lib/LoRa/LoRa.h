#ifndef __LORA__H__
#define __LORA__H__

#include <Arduino.h>
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include "LoRaUtil.h"

class LoRa {
  public:
    LoRa();
    void init();
    void doSend(osjob_t* j);
    void onEvent(ev_t ev);
    void connect();
    void send();
    bool isConnected();
    bool isSending();
    u1_t * getAppEui();
    u1_t * getDevEui();
    u1_t * getAppKey();
    u1_t * getData();
    void setDevEui(String devEui);
    void setAppKey(String appKey);
    void setData(String data);

  private:
    u1_t PROGMEM _appEui[8] = { 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00 };
    u1_t PROGMEM _devEui[8];
    u1_t PROGMEM _appKey[16];
    String _data;
    Utils _LoRaUtil = Utils();
    osjob_t _sendJob;
    bool _isConnected = false;
    bool _isSending = false;
    bool _isPackageQueued = false;
    u4_t _connectedFrequency = 0;

};

extern LoRa lora;

#endif
