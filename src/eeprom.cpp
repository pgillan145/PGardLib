#include "eeprom.h"

I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);
uint16_t log_current = 1;
uint16_t log_size = 0;

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Serial.println("writing eeprom data");
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Serial.println("reading eeprom data");

  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

void readMeta() {
    uint8_t initialized = ee.readByte(LOGSTART);
    if (initialized == 145) {
        uint8_t *c = (uint8_t *)&log_current;
        uint8_t *s = (uint8_t *)&log_size;
        ee.readBlock(LOGCURRENT, c, 2);
        ee.readBlock(LOGSIZE, s, 2);
        delay(1);
        if (log_size > LOGSIZEMAX) {
            //clearLog();
            log_current = 1;
            log_size = 0;
            //writeMeta();
        }
    }
    Serial.println("readMeta()");
    Serial.print("current:");
    Serial.print(log_current);
    Serial.print(" size:");
    Serial.println(log_size);
}

void clearLog() {
    return;
    Serial.println("clearLog()");
    log_current = 1;
    log_size = 0;
    ee.setBlock(LOGSTART, 0, LOGMETASIZE + LOGSIZEMAX);
    delay(1);
}

void writeMeta() {
    ee.updateByte(LOGSTART,145);
    uint8_t *c = (uint8_t *)&log_current;
    uint8_t *s = (uint8_t *)&log_size;
    ee.updateBlock(LOGCURRENT, c, 2);
    ee.updateBlock(LOGSIZE, s, 2);
    delay(1);
    Serial.println("writeMeta()");
    Serial.print("current:");
    Serial.print(log_current);
    Serial.print(" size:");
    Serial.println(log_size);
}

uint16_t writeLog(String str) {
  readMeta();
  str += "\n";
  if (str.length() > LOGSIZEMAX) {
      return 0;
  }
  if (str.length() > (LOGSIZEMAX - log_current)) {
    // string will wrap around, write it in two parts.
    uint16_t remaining = LOGSIZEMAX - log_current;
    char bytes1[remaining] = {0};
    str.toCharArray(bytes1, remaining);
    ee.writeBlock(LOGDATASTART + log_current, (uint8_t *)bytes1, remaining);
    char bytes2[str.length() - remaining] = { 0 };
    str.substring(remaining).toCharArray(bytes2, str.length() - remaining);
    ee.writeBlock(LOGDATASTART + 1, (uint8_t *)bytes2, str.length() - remaining);
    log_size = LOGSIZEMAX;
    log_current = str.length() - remaining;
  }
  else {
    char bytes[str.length()] = { 0 };
    str.toCharArray(bytes, str.length());
    ee.writeBlock(LOGDATASTART + log_current, (uint8_t *)bytes, str.length());
    if (log_size < LOGSIZEMAX) {
        log_size += str.length();
    }
    log_current += str.length();
  }
  delay(1);
  writeMeta();
}

String readLog() {
    return "FOO";
    readMeta();
    uint8_t data[log_size] = { 0 };
    if (log_size == LOGSIZEMAX) {
        uint16_t readsize = LOGSIZEMAX - log_current;
        ee.readBlock(LOGDATASTART + log_current, data, readsize);
        uint16_t remaining = LOGSIZEMAX - readsize;
        ee.readBlock(LOGDATASTART,  (uint8_t *)(data + readsize), remaining);
    }
    else {
        ee.readBlock(LOGDATASTART, data, log_size);
    }
    delay(1);
    return String((char *)data);
}

