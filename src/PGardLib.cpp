#include "PGardlib.h"

void PGardLibSetup() {
    PGardLibSetup(9600);
}

void PGardLibSetup(uint32_t baud) {
    delay(1000);
    Serial.begin(baud);
    delay(1000);
    SPL("setup()");
    pinMode(LED_BUILTIN, OUTPUT);
#ifdef OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED)) {
    SPL("SSD1306 allocation failed");
    errorBlink();  
  }
#endif
}

void arrayFill(uint32_t value, volatile uint32_t *target, uint16_t size) {
  for (uint16_t i = 0; i<size; i++) {
    target[i] = value;
  }
}
void arrayFill(String value, String *target, uint16_t size) {
  for (uint16_t i = 0; i<size; i++) {
    target[i] = value;
  }
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

char arrayPop(char *target, uint16_t size) {
  char c = target[size-1];

  for (uint16_t i = size-1; i>0; i--) {
    target[i] = target[i-1];
  }
  target[0] = 0;
  return c;
}

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

uint16_t freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

String serialInput() {
    return serialInput(10);
}

String serialInput(uint8_t max_length) {
  String stringText = "";
  if (Serial.available()) {
    delay(10);
    while(Serial.available()) {
      char c = Serial.read();
      stringText += c;
      if(stringText.length() >= max_length) {
        break; 
      }
    }
    Serial.flush();
  }
  return stringText;
}

void errorBlink() {
  while(1) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}
