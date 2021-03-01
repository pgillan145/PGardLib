#include "bluetooth.h"

void bleConn(BLEDevice peripheral) {
  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }
  if (peripheral.discoverService("2220")) {
    Serial.println("Service discovered");
  }
  else {
    Serial.println("Attribute discovery failed.");
    peripheral.disconnect();
    return;
  }
  BLECharacteristic simpleKeyCharacteristic = peripheral.characteristic("2221");

  // subscribe to the simple key characteristic
  Serial.println("Subscribing to simple key characteristic ...");
  if (!simpleKeyCharacteristic) {
    Serial.println("no simple key characteristic found!");
    peripheral.disconnect();
    return;
  }
  else if (!simpleKeyCharacteristic.canSubscribe()) {
    Serial.println("simple key characteristic is not subscribable!");
    peripheral.disconnect();
    return;
  }
  else if (!simpleKeyCharacteristic.subscribe()) {
    Serial.println("subscription failed!");
    peripheral.disconnect();
    return;
  }
  else {
    Serial.println("Subscribed");
  }
  return;
}

void getBLEValue(BLEDevice peripheral, char *buf, uint8_t size) {
  BLECharacteristic dir = peripheral.characteristic("2221");

  if (dir) {
    dir.readValue(buf, size);
  } else {
    peripheral.disconnect();
  }
}

