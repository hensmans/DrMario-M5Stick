
#include "structs.h"

int giveMaximum(int a, int b){
  if (a<b)
    return b;
  return a;
}
int giveMinimum(int a, int b){
  if (a>b)
    return b;
  return a;
}
void delayGame(uint16_t factor, Playfield* field){
  delay(field->delayTime/factor);
}

//get rectancle size
int8_t getRecSizeWidth(Playfield* field){
  return field->recSizeWidth;
}
int8_t getRecSizeHeight(Playfield* field){
  return field->recSizeHeight;
}
//get x coordinates from rect
int getXcoo(Rect* rec, Playfield* field){
  return ((rec->n) * getRecSizeWidth(field));
}
//get y coordinates from rect
int getYcoo(Rect* rec, Playfield* field){
  return  ((rec->m) * getRecSizeHeight(field));
}
//set alive for rect
void setAlive(Rect* rec, int8_t alive){
  rec->colourVirusAlive = rec->colourVirusAlive&0b11111110|alive;
}
//get alive from rect
uint8_t getAlive(Rect* rec){
  return rec->colourVirusAlive&0b00000001;
}
//set virus for rect
void setVirus(Rect* rec, int8_t virus){
  rec->colourVirusAlive=rec->colourVirusAlive&0b111111101|(virus<<1);
}
//get virus from rect
int8_t getVirus(Rect* rec){
  return (rec->colourVirusAlive&0b00000010)>>1;
}

//sets colour for rect
void setColour(Rect* rec, int8_t colour){
  colour += 2;
  rec->colourVirusAlive = (colour<<2)|(rec->colourVirusAlive&0b00000011);
}
int getColourIndex(Rect* rec){
  int col = rec->colourVirusAlive>>2;
  col -=2;
  return col;
}
//get colour value fromr rect
int getColour(Rect* rec){
  int col = getColourIndex(rec);
  if (col == -1)
    return backgroundColour;
  else if (col == -2)
    return bombColour;
  return coloursVector[col%(colourCount*2)];
}


//set highscore
void setHighScore(uint16_t newScore){
  highScore = newScore;
}
//gives highscore
uint16_t getHighScore(){
  return highScore;
}

//adds score
void addScore(int8_t score, Playfield* field){
  field->score += score;
}
//gets score
uint16_t getScore(Playfield* field){
  return field->score;
}
//reset score
void resetScore(Playfield* field){
  field->score = 0;
}
