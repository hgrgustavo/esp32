#include <FastLED.h>
#include "tables.h"



#define NUM_COLS 60
#define NUM_ROWS 10

#define NUM_LEDS NUM_COLS * NUM_ROWS

CRGB leds[NUM_LEDS];



void setup() {
  
  FastLED.addLeds<WS2812B, 3, GRB>(leds, NUM_LEDS);
}

void loop() {
  pacman();
  FastLED.delay(120);
}


void pacman() {
  static byte frame = 0;
  static byte path = 0;
  byte virtWight = 100;
  byte next_Sprite_offset = 20;
  byte xIndex=0;
  int Leds_index;

  LEDS.clear();
  int index = frame*100;
  

  for (int i = 0; i < 3; i++) {
    for (int x = 0; x < 20; x++) {
      for (int y = 0; y < 2; y++) {
        int index = XY (x+i*20, 4+y);
        leds[index] = pgm_read_dword (Dots+y*20+(x+path)%4);
      }
    }
  }

  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
     
      int Spr_index = (y<<3)+(y<<1)+index+x;

      xIndex= (x+path)%virtWight;
      if (xIndex<60){
        Leds_index = XY (xIndex, y);
        leds[Leds_index] = pgm_read_dword (Mask11+Spr_index);
      }

      xIndex = (x+path+next_Sprite_offset)%virtWight;
      if (xIndex<60) {
        Leds_index = XY (xIndex, y);
        leds[Leds_index] = pgm_read_dword (Mask42+Spr_index);
      }

      xIndex = (x+path+next_Sprite_offset*2)%virtWight;
      if (xIndex<60) {
        Leds_index = XY (xIndex, y);
        leds[Leds_index] = pgm_read_dword (Mask41+Spr_index);
      }

      xIndex = (x+path+next_Sprite_offset*3)%virtWight;
      if (xIndex<60) {
       Leds_index = XY (xIndex, y);
       leds[Leds_index] = pgm_read_dword (Mask43+Spr_index);
      }

      xIndex = (x+path+next_Sprite_offset*4)%virtWight;
      if (xIndex<60) {
        Leds_index = XY (xIndex, y);
        leds[Leds_index] = pgm_read_dword (Mask44+Spr_index);
      }

    }
  }

 

  frame=(frame+1)%4;
  path=(path+1)%virtWight;
  
}


uint16_t XY (byte x, byte y) {
  return (y*NUM_COLS+x);
}