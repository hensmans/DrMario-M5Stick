#include "drawFunctions.h"

//initializes a new rectancle
Rect* makeNewRect(int8_t mInit, int8_t nInit, int8_t colourInit, int8_t aliveInit, int8_t virusInit){
  Rect* rec=(Rect*) malloc(sizeof(Rect));
  rec->m = mInit;
  rec->n = nInit;
  setColour(rec, colourInit);
  setAlive(rec, aliveInit);
  setVirus(rec, virusInit);
  return rec;
}

//update rect
void updateRect(Rect* rec, Playfield* field){
  rec->m = (rec->m + 1) % field->mCount;
  rec->n = (rec->n + 1) % field->nCount;
}

void gameWon(Playfield* field);

//removes rect ,unalives it
void removeRect(Rect* rec, Playfield* field){
  if (getVirus(rec)){ //if virus gets deleted,add 100 score
    if (getColour(rec)>=colourCount){ //if timed virus
        field->timedVirusesLeft--;
    }
    field->virusCount--; 
    if (field->virusCount<=0){
      setColour(rec, -1);
      setAlive(rec, 0);
      setVirus(rec, 0);
      gameWon(field);
    }
    addScore(100, field);
  }  
  setColour(rec, -1);
  setAlive(rec, 0);
  setVirus(rec, 0);
  drawRect(rec, field);
}
//free rect from memory
void freeRect(Rect* rec){
  free(rec);
}
//changes rec their m and n value value
void changeRecMN(int8_t mNew, int8_t nNew, Rect* rec){
  rec->m = mNew;
  rec->n = nNew;
}
//changes colour value
void changeColour(int8_t newColour, Rect* rec){
  setColour(rec,newColour);
} 
//changes virus value
void changeVirus(int8_t newVirus, Rect* rec){
  setVirus(rec, newVirus);
}
//changes alive value
void changeAlive(int8_t newAlive, Rect* rec){
  setAlive(rec, newAlive);
}

//checks if 2 rectancles have the same colour and are alive
int8_t checkIfSame(Rect* compareRec, Rect* currentRec, Playfield* field){
  return (getAlive(currentRec) && getAlive(compareRec) && (((getColourIndex(compareRec))%colourCount)==((getColourIndex(currentRec))%colourCount))); //is the same if both alive and same colour
}

void changeRecValues(Rect* rec, int8_t newColour, int8_t newAlive, int8_t newVirus){
  changeAlive(newAlive, rec);
  changeColour(newColour, rec);
  changeVirus(newVirus, rec);
}

