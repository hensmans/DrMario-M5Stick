#include "M5stickFunctions.h"


//draw bomb explosion
void drawExplosionRect(Rect* rec, Playfield* field){
  M5.Lcd.drawRect(getXcoo(rec, field), getYcoo(rec, field), getRecSizeWidth(field), getRecSizeHeight(field), bombExplosionColour);
  M5.Lcd.fillRect(getXcoo(rec, field), getYcoo(rec, field), getRecSizeWidth(field), getRecSizeHeight(field), bombExplosionColour);
}



//draw rectancle 
void drawRect(Rect* rec, Playfield* field){
  int recHeight = getRecSizeHeight(field);
  int recWidth = getRecSizeWidth(field);
  if (getColour(rec) == bombColour){
    M5.Lcd.drawEllipse(getXcoo(rec, field)+recWidth/2, getYcoo(rec, field)+recHeight/2, recWidth/2-1, recHeight/2-1, getColour(rec));
    M5.Lcd.fillEllipse(getXcoo(rec, field)+recWidth/2, getYcoo(rec, field)+recHeight/2, recWidth/2-1, recHeight/2-1, getColour(rec));
  }else if (getVirus(rec)){ //if rec is a virus, draw virus
    M5.Lcd.fillRect(getXcoo(rec, field), getYcoo(rec, field), recWidth, recHeight, backgroundColour);
    M5.Lcd.drawRect(getXcoo(rec, field), getYcoo(rec, field), recWidth, recHeight, getColour(rec));
    M5.Lcd.fillRect(getXcoo(rec, field)+recWidth/2-recWidth/4, getYcoo(rec, field)+recHeight/2-recHeight/4, recWidth/2, recHeight/2, getColour(rec));    
  }else{ //not a virus
    
    M5.Lcd.fillRect(getXcoo(rec, field), getYcoo(rec, field), recWidth, recHeight, getColour(rec));
    M5.Lcd.drawRect(getXcoo(rec, field), getYcoo(rec, field), recWidth, recHeight, getColour(rec));
  }
}
//draw rectancle alive part for debugfing
void drawRectAlive(Rect* rec, Playfield* field){
  if (getAlive(rec)){
    M5.Lcd.drawRect(getXcoo(rec, field), getYcoo(rec, field), getRecSizeWidth(field), getRecSizeHeight(field), RED);
    M5.Lcd.fillRect(getXcoo(rec, field), getYcoo(rec, field), getRecSizeWidth(field), getRecSizeHeight(field), RED);
  }else{
    M5.Lcd.drawRect(getXcoo(rec, field), getYcoo(rec, field), getRecSizeWidth(field), getRecSizeHeight(field), BLACK);
    M5.Lcd.fillRect(getXcoo(rec, field), getYcoo(rec, field), getRecSizeWidth(field), getRecSizeHeight(field), BLACK);
  }
}
