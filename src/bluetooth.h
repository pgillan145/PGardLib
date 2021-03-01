#pragma once

/*
 * Includes 
 */

#include <Arduino.h>
#include <ArduinoBLE.h>

/*
 * Functions
 */
void bleConn(BLEDevice peripheral);
void getBLEValue(BLEDevice peripheral, char *buf, uint8_t size);

