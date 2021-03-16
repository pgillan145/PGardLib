#pragma once

/*
 * Includes 
 */

#include <Arduino.h>
#ifdef RFDUINO
#include <RFduinoBLE.h>
RFduinoBLEClass BLE = RFduinoBLE;
#else
#include <ArduinoBLE.h>
#endif

/*
 * Functions
 */
void bleConn(BLEDevice peripheral);
void getBLEValue(BLEDevice peripheral, char *buf, uint8_t size);

