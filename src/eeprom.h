#pragma once

#define LOGSIZEMAX      512
#define LOGSTART        0xFF
#define LOGMETASIZE     32
#define LOGCURRENT      LOGSTART+1
#define LOGSIZE         LOGSTART+3
#define LOGDATASTART    LOGSTART+LOGMETASIZE

/*
 * Includes
 */
#include <Arduino.h>
#include <Wire.h>
#include <I2C_eeprom.h>

/*
 * Functions
 */

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data );
byte readEEPROM(int deviceaddress, unsigned int eeaddress );

uint16_t writeLog(String str);
String readLog();
void readMeta();
void writeMeta();
void clearLog();
