#include "PGardlib.h"

void PGardLibSetup() {
    PGardLibSetup(9600);
}

void PGardLibSetup(uint32_t baud) {
    delay(1000);
    Serial.begin(baud);
    SPL("setup()");
}

void arrayFill(char value, char *target, uint16_t size) {
  for (uint16_t i = 0; i<size; i++) {
    target[i] = value;
  }
}

bool arrayCompare(char *needle, char *haystack, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    if (needle[i] != haystack[i]) {
      return false;
    }
  }
  return true;
}

void arrayCopy(char *source, char *dest, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    dest[i] = source[i];
  }
}


void arrayPush(char value, char *target, uint16_t size) {
  for (uint16_t i = 1; i<size; i++) {
    target[i-1] = target[i];
  }
  target[size-1] = value;
}

