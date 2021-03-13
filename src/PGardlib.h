#pragma once

/*
 * Includes 
 */

//#include <string.h>
#include <Arduino.h>
//#include <stdlib.h>
//#include <stdint.h> 
#include <functional>

#ifdef BLUETOOTH
#include "bluetooth.h"
#endif // BLUETOOTH

#ifdef MATRIX
#include "matrix.h"
#endif // MATRIX

/*
 * Structures & Variables 
 */
#define SP(x) Serial.print(x)
#define SPL(x) Serial.println(x)

/*
 * Functions
 */
void PGardLibSetup(void);
void PGardLibSetup(uint32_t baud);
void arrayFill(char value, char *target, uint16_t size);
bool arrayCompare(char *needle, char *haystack, uint8_t size);
void arrayCopy(char *source, char *dest, uint8_t size);
void arrayPush(char value, char *target, uint16_t size);
uint16_t freeMemory(void);
String serialInput(uint8_t max_length);

#ifdef MATRIX
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(MATRIX_W, MATRIX_H, MATRIX, MATRIX_OPTIONS, NEO_GRB + NEO_KHZ800 );
void display_scrollText(char* text, int16_t speed, uint32_t color);
void display_scrollText(String text, int16_t speed, uint32_t color);
void display_scrollText(float text, int16_t speed, uint32_t color);
#endif //MATRIX
