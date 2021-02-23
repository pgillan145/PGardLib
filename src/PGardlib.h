#include <stdint.h> 

#define SP(x) Serial.print(x)
#define SPL(x) Serial.println(x)

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
