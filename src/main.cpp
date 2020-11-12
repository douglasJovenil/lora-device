#include <Arduino.h>
#include <SPI.h>
#include "LoRa.h"

#define BUTTON 0 
#define LED 25

void setup() {
  Serial.begin(115200);

  lora.setDevEui("7eacbc0768eb39fc");
  lora.setAppKey("54cbc3c94431f85f9b7fd894c1dd9955");
  lora.setData("Hello World!");
  lora.init();
  lora.connect();

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(LED, LOW);
}

void loop() { 
  static bool ledState = false;

  if (!digitalRead(BUTTON) && !lora.isSending()) {
    ledState = !ledState;
    digitalWrite(LED, ledState);
    lora.send();
    while(!digitalRead(BUTTON));
  }
}