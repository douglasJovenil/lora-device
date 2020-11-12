#include "LoRa.h"

/**
 * Extern functions and variables needed
 * **/
void os_getArtEui(u1_t* buf) { memcpy_P(buf, lora.getAppKey(), 8); }
void os_getDevEui(u1_t* buf) { memcpy_P(buf, lora.getDevEui(), 8); }
void os_getDevKey(u1_t* buf) { memcpy_P(buf, lora.getAppKey(), 16); }
void onEvent(ev_t ev) { lora.onEvent(ev); }
void do_send(osjob_t* j) { lora.doSend(j); }
 
const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = {26, 33, LMIC_UNUSED_PIN},
};

/**
 * Class LoRa
 * **/
LoRa::LoRa() {}

void LoRa::init() {
  os_init();
  LMIC_reset();
  LMIC_selectSubBand(1);
  
  LMIC_setAdrMode(0);

  doSend(&_sendJob);
}

void LoRa::connect() {
  while (!isConnected()) {
    os_runloop_once();
  }
}

void LoRa::send() {
  _isSending = true;
  while (isSending()) {
    os_runloop_once();
  }
}

void LoRa::doSend(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    // Prepare upstream data transmission at the next possible time.

    LMIC_setTxData2(1, getData(), _data.length(), 1);

    Serial.println(F("Packet queued"));
    _isSending = false;
  }
}

void LoRa::onEvent(ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");

  switch (ev) {
    case EV_SCAN_TIMEOUT: Serial.println("EV_SCAN_TIMEOUT");    break;
    case EV_BEACON_FOUND: Serial.println("EV_BEACON_FOUND");    break;
    case EV_BEACON_MISSED: Serial.println("EV_BEACON_MISSED");  break;
    case EV_BEACON_TRACKED: Serial.println("EV_BEACON_TRACKED");break;
    case EV_JOINING: Serial.println("EV_JOINING");              break;
    case EV_JOIN_FAILED: Serial.println("EV_JOIN_FAILED");      break;
    case EV_REJOIN_FAILED: Serial.println("EV_REJOIN_FAILED");  break;
    case EV_LOST_TSYNC: Serial.println("EV_LOST_TSYNC");        break;
    case EV_RESET: Serial.println("EV_RESET");                  break;
    case EV_RXCOMPLETE: Serial.println("EV_RXCOMPLETE");        break;
    case EV_LINK_DEAD: Serial.println("EV_LINK_DEAD");          break;
    case EV_LINK_ALIVE: Serial.println("EV_LINK_ALIVE");        break;
    case EV_TXCANCELED: Serial.println("EV_TXCANCELED");        break;
    case EV_JOIN_TXCOMPLETE: Serial.println(F("EV_JOIN_TXCOMPLETE: no JoinAccept")); break;
    case EV_TXSTART:  Serial.println("EV_TXSTART");  break;
    case EV_JOINED:
      Serial.println("EV_JOINED");
      {
        u4_t netid = 0;
        devaddr_t devaddr = 0;
        u1_t nwkKey[16];
        u1_t artKey[16];
        LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);
        Serial.print("netid: ");
        Serial.println(netid, DEC);
        Serial.print("devaddr: ");
        Serial.println(devaddr, HEX);
        Serial.print("AppSKey: ");
        for (size_t i = 0; i < sizeof(artKey); ++i) {
          if (i != 0) Serial.print("-");
          _LoRaUtil.printHex2(artKey[i]);
        }
        Serial.println("");
        Serial.print("NwkSKey: ");
        for (size_t i = 0; i < sizeof(nwkKey); ++i) {
          if (i != 0) Serial.print("-");
          _LoRaUtil.printHex2(nwkKey[i]);
        }
        Serial.println();
      }
      // Disable link check validation (automatically enabled
      // during join, but because slow data rates change max TX
      // size, we don't use it in this example.
      LMIC_setLinkCheckMode(0);
      _isConnected = true;
      break;
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      if (LMIC.txrxFlags & TXRX_ACK) Serial.println(F("Received ack"));
      
      if (LMIC.dataLen) {
        Serial.print(F("Received "));
        Serial.print(LMIC.dataLen);
        Serial.println(F(" bytes of payload"));
        Serial.print("The payload is: ");
        
         for (int i = 0; i < LMIC.dataLen; i++) {
          Serial.print((char)LMIC.frame[LMIC.dataBeg + i]);
        }
        Serial.println();
      }
      // Schedule next transmission
      os_setCallback(&lora._sendJob, do_send);
      break;
    default:
      Serial.print(F("Unknown event: "));
      Serial.println((unsigned)ev);
      break;
  }
}

u1_t * LoRa::getAppEui() {
  return _appEui;
}

u1_t * LoRa::getDevEui() {
  return _devEui;
}

u1_t * LoRa::getAppKey() {
  return _appKey;
}

u1_t * LoRa::getData() {
  return (xref2u1_t)_data.c_str();
}

void LoRa::setDevEui(String devEui) {
  _LoRaUtil.setHexString(devEui);

  for (int i = 0; i < 8; i++) _devEui[i] = _LoRaUtil.getLSBVector()[i];
}

void LoRa::setAppKey(String appKey) {
  _LoRaUtil.setHexString(appKey);

  for (int i = 0; i < 16; i++) _appKey[i] = _LoRaUtil.getMSBVector()[i];
}

void LoRa::setData(String data) {
  _data = data;
}

bool LoRa::isConnected() {
  return _isConnected;
};

bool LoRa::isSending() {
  return _isSending;
};

LoRa lora;