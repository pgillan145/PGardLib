#pragma once

/*
 * Includes
 */
#include <Arduino.h>
#include <Wire.h>

/*
 * Functions
 */
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data );
byte readEEPROM(int deviceaddress, unsigned int eeaddress );
