
#include "constants.h"


enum direction{UP, RIGHT, DOWN, LEFT, NOTHING};

typedef struct{
  int8_t m = 0;
  int8_t n = 0;
  uint8_t colourVirusAlive = 0;
}Rect;

typedef struct{
    Rect* recL;       
    Rect* recR;
    direction dir;
}Pill;


/* Structure of a node */
struct node{
    Pill* pill;
    node* next; // Address 
};


typedef struct{
  int8_t mCount;
  int8_t nCount;
  int8_t virusCount;
  int8_t recSizeWidth;
  int8_t recSizeHeight;
  int8_t bombFallingNow;
  int8_t bombBool;
  int8_t timedVirusBool;
  int8_t timeCountInit;
  int8_t timeLeft;
  int8_t timedVirusesLeft;
  int8_t currentLevel;
  uint8_t virusCountStart;
  uint16_t delayTime; //delay time
  uint16_t score = 0;
  int16_t arraySize;
  Rect** array;
  struct node* linkedListOfPills;
}Playfield;
static Playfield* playfield;