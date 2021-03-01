#include "matrix.h"

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

int16_t scroll_position = 1;
uint32_t scroll_time = 0;
char* scroll_text;
int char_width = 7;

void display_scrollText(char* text, int16_t speed, uint32_t color) {
  boolean scroll_right = false;
  if (strlen(text) == 0  && strlen(scroll_text) == 0 ) {
    // nothing to print
    return;
  }
  
  // if speed is negative, scroll the opposite direction
  if (speed < 0) {
    scroll_right = true;
    speed *= -1;
  }
  
  if (millis() > scroll_time + speed) {
    int len = strlen(text);
    if (strlen(scroll_text) == 0 || ((len + 1) * char_width) < scroll_position) {
      scroll_position = 1;
    }

    if (strcmp(text, scroll_text)) {
      // copy the text into our own private buffer so we can handle changes gracefully.
      free(scroll_text);
      scroll_text = (char*)malloc(len + 1);
      strcpy(scroll_text, text);
    }

    if (scroll_right) {
      if (--scroll_position < 1) {
        scroll_position = ((len + 1) * char_width) ;
      }
    }
    else {
      if (++scroll_position > ((len + 1) * char_width) ) {
        scroll_position = 1;
      }
    }
    scroll_time = millis();
  }
  int16_t cursor_pos = 8 - scroll_position;

  // set up the matrix and output
  matrix->clear();
  matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely   
  matrix->setTextSize(1);
  matrix->setRotation(0);
  matrix->setCursor(cursor_pos,0);
  matrix->setTextColor(color);
  matrix->print(scroll_text);
  matrix->show();
}

void display_scrollText(String text, int16_t speed, uint32_t color) {
  char buf[15];
  text.toCharArray(buf, 15);
  display_scrollText(buf, speed, color);  
}

void display_scrollText(float text, int16_t speed, uint32_t color) {
  char buf[15];
  snprintf (buf, sizeof(buf), "%.1f", text);
  display_scrollText(buf, speed, color);
}

// Animations
animation_t *findAnimation(uint16_t ani[][64]) {
  animation_t *a = animations;
  while (a) {
    if (a->data == &ani[0]) {
      return a;
    }
    a = a->next;
  }
  return 0;
}

void addAnimation(uint16_t ani[][64], uint8_t frames, uint8_t speed, uint8_t commands) {
  /*
  for (uint8_t i = 0; i<frames; i++) {
    Serial.print("frame ");
    Serial.print(i+1);
    Serial.println(":");
    for (uint8_t j=0; j<8; j++) {
      Serial.print("  ");
      Serial.println(ani[i][j], HEX);
    }
  }
  */
  if (commands & 4) {
    animation_t *a = findAnimation(ani);
    if (a) {
      Serial.println("FOUND MATCHING ANIMATION");
      a->commands &= ~(1 << 2);
      return;
    }
  }

  animation_t *a = (animation_t *)malloc(sizeof(animation_t));
  a->data = &ani[0];//&rectangle[0];
  a->frame = 0;
  a->speed = speed;
  a->time = millis();
  a->prev = NULL;
  a->next = NULL;
  a->commands = commands;
  a->total_frames = frames;
  
  if (animations == NULL) {
    a->id = 1;
    animations = a;
  }
  else {
    Serial.println("traversing animations");
    animation_t *b = animations;
    while (b->next) {
      b = b->next;
    }
    a->id = b->id + 1;
    a->prev = b;
    b->next = a;
  }
}

void doAnimations() {
  animation_t *a = animations;
  while (a) {
    uint32_t now = millis();

#ifdef CEREAL
    Serial.print(" animation ");
    Serial.print(a->id);
    Serial.print(" frame ");
    Serial.println(a->frame);
#endif
    matrix->drawRGBBitmap(0,0,a->data[a->frame],8,8);
    matrix->show();
    if (now >= a->time) {
      a->frame++;
      a->time = now + (1000/a->speed);
    }

    uint8_t total_frames = a->total_frames;
    if (a->frame >= total_frames) {
      if (a->commands & ANI_HOLD) {
        // hold for 1 second
        a->frame = 0;
        a->data = &black[0];
        a->total_frames = 1;
        a->time = now + 1000;
        a->commands &= ~(1 << 0);
      }
      else if (a->commands & ANI_REPEAT) {
        // repeat
        a->frame = 0;
        a->time = now + (1000/a->speed);
      }
      else {
        // adjust the linked list prior to deleting this item
        if (a->prev) {
          a->prev->next = a->next;
        } 
        if (a->next) {
          a->next->prev = a->prev;
        }
 
        // repoint the head, if necessary
        if (a->next && !a->prev) {
          animations = a->next;
        }
        else if (!a->next && !a->prev) {
          animations = NULL;
        }
        free(a);
      }
    }
    a = a->next;
  }
}

