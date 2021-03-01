#pragma once

/*
 * Includes 
 */

#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

/*
 * Structures & Variables 
 */
#define BLACK   0

#define RED1    (3 <<  11)
#define RED2    (7 <<  11)
#define RED3    (15 << 11)
#define RED4    (31 << 11)

#define GREEN1  (1 <<  5)   
#define GREEN2  (15 << 5)  
#define GREEN3  (31 << 5)  
#define GREEN4  (63 << 5)  

#define BLUE1   3
#define BLUE2   7
#define BLUE3   15
#define BLUE4   31

#define YELLOW1 (RED1 + GREEN1)
#define YELLOW2 (RED2 + GREEN2)
#define YELLOW3 (RED3 + GREEN3)
#define YELLOW4 (RED4 + GREEN4)

#define PURPLE1 (RED1 + BLUE1)
#define PURPLE2 (RED2 + BLUE2)
#define PURPLE3 (RED3 + BLUE3)
#define PURPLE4 (RED4 + BLUE4)

#define CYAN1   (GREEN1 + BLUE1)
#define CYAN2   (GREEN2 + BLUE2)
#define CYAN3   (GREEN3 + BLUE3)
#define CYAN4   (GREEN4 + BLUE4)

#define WHITE1  (RED1 + GREEN1 + BLUE1)
#define WHITE2  (RED2 + GREEN2 + BLUE2)
#define WHITE3  (RED3 + GREEN3 + BLUE3)
#define WHITE4  (RED4 + GREEN4 + BLUE4)

#ifdef RIGID
#define MATRIX_OPTIONS NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
#else
#define MATRIX_OPTIONS NEO_MATRIX_TOP  + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG
#endif // RIGID

// animation commands:
// 1   hold for 1 seconds before going black
#define ANI_HOLD    1 << 0
// 2   fade out at the end 
//       NOT IMPLEMENTED
//#define ANI_FADE    1 << 1
// 4   repeat
#define ANI_REPEAT    1 << 2
// 8   treat black pixels as transparent (ie, dont clear the
//       screen before drawing, and don't write to 
//       these particular pixeles -- not sure how i'd do that)
//       NOT IMPLEMENTED
//#define ANI_TRANS    1 << 3
// 16  wait until all animations are complete before starting 
//       NOT IMPLEMENTED
//#define ANI_WAIT    1 << 4
// 32  terminate all existing animations
//       NOT IMPLEMENTED
//#define ANI_TERMINATE    1 << 5

typedef struct animation {
  uint8_t id;
  uint8_t frame;
  uint8_t total_frames;
  uint8_t speed;
  uint32_t time;
  struct animation *next;
  struct animation *prev;
  uint8_t commands;
  uint16_t (*data)[64];
} animation_t;

/*
animation_t *animations = NULL;

uint16_t black[][64] = {
  { 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 
  },
};
*/

//int16_t scroll_position = 1;
//uint32_t scroll_time = 0;
//char* scroll_text;
//int char_width = 7;
extern Adafruit_NeoMatrix *matrix;

/*
 * Functions
 */
void display_scrollText(char* text, int16_t speed, uint32_t color);
void display_scrollText(String text, int16_t speed, uint32_t color);
void display_scrollText(float text, int16_t speed, uint32_t color);
void addAnimation(uint16_t ani[][64], uint8_t frames, uint8_t speed, uint8_t commands);
void doAnimations(void);
animation_t *findAnimation(uint16_t ani[][64]);


