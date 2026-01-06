#include "linkedList.h"

//checks if m and n value are still in the screen
int8_t checkInBounds(int8_t m, int8_t n, Playfield* field){
  return (m>= 0 && n>=0 && m<field->mCount && n<field->nCount);
}
//makes from 2D array coordinates a 1D cooridinate
int getArrayOffset(int8_t m, int8_t n, int rowSize){
  return m*rowSize+n;
}
//frees array from memory
void freeArray(Playfield* field){ 
  Rect **array = field->array;
  int16_t size = field->arraySize;
  Rect *rec;
  for (int i = 0; i<1; i++){
    rec = array[i];
    freeRect(rec);
  }
  free(array);
}
void setSettingsToLevel(Playfield* field){
    field->virusCountStart = giveMinimum(field->currentLevel+colourVirusCountInit-1, 11); //more viruses
    field->delayTime = giveMaximum(waitTimeInit-100*(field->currentLevel-1), 300); //faster
}

void setScreenSizeNewLevel(Playfield* field){
    if (field->currentLevel>=biggestScreenLevel){ //increase screensize, do only 1 time, otherwise screen too big, make bigger when going to level 3
        field->nCount=11;
        field->mCount=20;
    }
    else if (field->currentLevel>=biggerScreenLevel){ //increase screensize, do only 1 time, otherwise screen too big, make bigger when going to level 3
        field->nCount=9;
        field->mCount=16;
    }else{
        field->nCount=recWidthCount;
        field->mCount=recHeightCount;
    }
}

//makes array, filled with rectancles
Playfield* makeArray(int8_t currentLevel, int8_t bombBool, int8_t timeCount, int8_t newGameBool, Playfield* newPlayfield){ 
    if (newGameBool){ //if very first game
      newPlayfield = (Playfield*) malloc(sizeof(Playfield)); //allocates playfield struct
    }else{ //if new level 
      newPlayfield = playfield;
      freeArray(newPlayfield);
      freeLinkedList(newPlayfield);
    }
    newPlayfield->currentLevel = currentLevel;
    setScreenSizeNewLevel(newPlayfield);
    setSettingsToLevel(newPlayfield);
    int8_t height = newPlayfield->mCount;
    int8_t width = newPlayfield->nCount;
    int totalSize = height*width;

    Rect** newArray = (Rect**) calloc(totalSize, sizeof(Rect*)); //allocates array 
    for (int i = 0; i<height; i++){
      for (int j = 0; j<width; j++){    
          newArray[getArrayOffset(i,j,width)] = makeNewRect(i, j, -1, 0, 0);
      }
    }

    if (newGameBool){ //only initialize if it's very first game
        newPlayfield->mCount = height;
        newPlayfield->nCount = width;
        newPlayfield->bombBool = bombBool;
    }
    newPlayfield->array = newArray;
    newPlayfield->arraySize = totalSize;
    newPlayfield->linkedListOfPills = NULL;
    newPlayfield->recSizeWidth = screenWidth/width;
    newPlayfield->recSizeHeight = screenHeight/height;
    newPlayfield->bombFallingNow = 0;
    newPlayfield->timedVirusBool = timeCount;
    newPlayfield->timeLeft = timeCount;
    newPlayfield->timedVirusesLeft = colourCount;
    newPlayfield->timeCountInit = timeCount;
    newPlayfield->virusCount = newPlayfield->virusCountStart*colourCount;
    if (newPlayfield->timedVirusBool){ //if timed virus, add to viruscount
      newPlayfield->virusCount += newPlayfield->timedVirusesLeft;
    }
    
    return newPlayfield;
}
//draws whole array
void drawArray(Playfield* field){
  for (int i = 0; i<field->arraySize; i++){
      Rect* rec = field->array[i];
      drawRect(rec, field); 
    }
}

void drawArrayAlive(Playfield* field){
  for (int i = 0; i<field->arraySize; i++){
      Rect* rec = field->array[i];
      drawRectAlive(rec, field); 
    }
}

//gives array ellement
Rect* getArrayEl(int8_t m, int8_t n, Playfield* field){
  return field->array[getArrayOffset(m,n,field->nCount)];
}
//set array ellement
void setArrayEl(int8_t m, int8_t n, Playfield* field, Rect* newRec){
  field->array[getArrayOffset(m,n,field->nCount)] = newRec;
}

//gives the rectancle that is above, under, left or right of the current rectancle
Rect* getRectAround(Rect* rec, direction dir, Playfield* field){
  int8_t mCurrent = rec->m;
  int8_t nCurrent = rec->n;
  int8_t mNew = rec->m;
  int8_t nNew = rec->n;
  switch (dir){
    case UP:
      mNew--;
      break;
    case RIGHT:
      nNew++;
      break;
    case DOWN:
      mNew++;
      break;
    case LEFT:
      nNew--;
      break;
  }
  if (mNew<0)
    mNew = 0;
  if (nNew<0)
    nNew = 0;
  mNew = mNew%field->mCount;
  nNew = nNew%field->nCount;
  return getArrayEl(mNew, nNew, field);
}
//check if the move will still be in bounds of the screen
int8_t checkMovePossible(Rect* rec, direction dir, Playfield* field){
  int8_t mCurrent = rec->m;
  int8_t nCurrent = rec->n;

  switch (dir){
    case UP:
      mCurrent--;
      break;
    case RIGHT:
      nCurrent++;
      break;
    case DOWN:
      mCurrent++;
      break;
    case LEFT:
      nCurrent--;
      break;
  }
  return (checkInBounds(mCurrent, nCurrent, field) && !(getAlive(getArrayEl(mCurrent,nCurrent,field)))); //check if rect is not alive

}
 //draws rectancles above, under, right and left of the current rectancle
void drawRecArround(Rect* rec, Playfield* field){
  int8_t m = rec->m;
  int8_t n = rec->n;
  if (checkInBounds(m-1, n ,field))
    drawRect(getRectAround(rec, UP, field), field);
  if (checkInBounds(m+1, n ,field))
    drawRect(getRectAround(rec, DOWN, field), field);
  if (checkInBounds(m, n+1 ,field))
    drawRect(getRectAround(rec, RIGHT, field), field);
  if (checkInBounds(m, n-1 ,field))
    drawRect(getRectAround(rec, LEFT, field), field);  
}
//draws all the rectancles around and in the pill
void drawPillAround(Pill* pill, Playfield* field){
  Rect* rec1 = pill->recL;
  Rect* rec2 = pill->recR;
  drawRect(rec1, field);
  drawRect(rec2, field);
  drawRecArround(rec1, field);
  drawRecArround(rec2, field);
  setScreenText(field);
  makeMoveSound(); //makes movement sound
}

// will switch 2 rect structures their values
void switchRec(Rect* rec1, Rect* rec2, Playfield* field){
  int8_t m1 = rec1->m;
  int8_t n1 = rec1->n;
  int8_t m2 = rec2->m;
  int8_t n2 = rec2->n;
  changeRecMN(m2, n2, rec1); //changes the MN values from the rec
  changeRecMN(m1, n1,rec2);
  setArrayEl(m1, n1, field, rec2);
  setArrayEl(m2, n2, field, rec1);
}

//checks if the block dwn below is empty
int8_t checkIfEmptyDown(int8_t m,int8_t n, Playfield* field){
  return ((m<field->mCount-1) && !getAlive(getArrayEl(m+1,n,field)));
}
//removes blocks x times in the direction dir
void removeBlocks(Rect* currentRec, int8_t counter, direction dir, Playfield* field){ //removes counter blocks 
  removeRect(currentRec, field);
  counter--;
  for (; counter>0; counter--){
    currentRec = getRectAround(currentRec, dir, field);
    removeRect(currentRec, field);
  }
  make4InARowSound();
  letEverythingFall(field);
}
