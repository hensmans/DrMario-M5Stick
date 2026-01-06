#include "arrayFunctions.h"

//frees everything from meory
void freeEverything(Playfield* field){
  freeLinkedList(field);
  freeArray(field);
  free(field);
}


 //makes random virus in playfield
void makeViruses(Playfield* field){
  int8_t randomM;
  int8_t randomN;
  Rect* rec;

  //makes timed viruses
  if (field->timedVirusBool){
    for (int i = 0; i<colourCount;){
      randomM = field->mCount - (rand())%(field->mCount/4) - 1;
      randomN = (rand())%(field->nCount);
      rec = getArrayEl(randomM, randomN, field);
      if (!getAlive(rec)){ //if not alive,set virus in it, doesnt removes old viruses
          changeRecValues(rec, colourCount+i, 1, 1);
          i++;
      }
    }
  }
  for (int colourIndex = 0; colourIndex<colourCount;colourIndex++){
    for (int i=0; i<field->virusCountStart;){
      randomM = field->mCount - (rand())%(field->mCount/4) - 1;
      randomN = (rand())%(field->nCount);
      rec = getArrayEl(randomM, randomN, field);
      if (!getAlive(rec)){ //if not alive,set virus in it, doesnt removes old viruses
          changeRecValues(rec, colourIndex, 1, 1);
          i++;
      }
    }
  }
}

//draws playfield
void drawScreen(Playfield* field){
  drawArray(field);
  setScreenText(field);
}

//if blocks deleted, let everything fall correctly so blocks dont float where they dont need to float.
void letEverythingFall(Playfield* field){
    struct node* head = field->linkedListOfPills;
    // Return if list is empty 
    if(head == NULL){
        return;
    }
    int8_t didSomethingFall = 1;
    while (didSomethingFall){
      didSomethingFall = 0; //if nothing falls, it keeps 0 
      struct node* temp = head;
      while(temp != NULL){
        //write here what u want to do
          Pill* currentPill = temp->pill;
          Rect* rec1 =  currentPill->recL;
          Rect* rec2 =  currentPill->recR;
          direction currentDir = currentPill->dir;
          if (getAlive(rec1) && getAlive(rec2)){ //if 2 blocks in pill are alive
              int8_t Mmax = giveMaximum(rec1->m, rec2->m); //maximum m (y) value of the pill, is to check if it's at the bottom or if it hit anything
              direction dirCurrent = currentPill->dir;
              while (checkIfEmptyDown(Mmax, rec1->n, field) && checkIfEmptyDown(Mmax,  rec2->n, field)){  //move down until its not possible anymore
                didSomethingFall = 1;
                if (dirCurrent == RIGHT){
                  switchRec(rec2, getRectAround(rec2, DOWN, field), field);
                  switchRec(rec1, getRectAround(rec1, DOWN, field), field);
                }else{
                  switchRec(rec1, getRectAround(rec1, DOWN, field), field);
                  switchRec(rec2, getRectAround(rec2, DOWN, field), field);
                }
                Mmax = giveMaximum(rec1->m, rec2->m);
              }
          } else if (getAlive(rec1) || getAlive(rec2)){ //if only 1 block in pill is alive
            if (getAlive(rec2)){
              rec1 = rec2;
            }
            while (checkIfEmptyDown(rec1->m, rec1->n, field)){  //move down until its not possible anymore
              didSomethingFall = 1;
              switchRec(rec1, getRectAround(rec1, DOWN, field), field);
            }
          }
          temp = temp->next; // Move to next node
      }
  }
  drawScreen(field);
  delayGame(1, field); //wait to see them fall
  checkFourInARow(field); //check again if new four in a row is created by falling blocks
}




//checks if there is a four or more in a row vertically and horizontally, deleted blocks if it is.
void checkFourInARow(Playfield* field){
  int8_t counter = 0;
  Rect* currentRec;
  Rect* compareRec;

  //horizontal check
  for (int8_t m = field->mCount-1; m>= 0; m--){
    compareRec = getArrayEl(m,0,field);
    counter = 0;
    for (int8_t n = 0; n<= field->nCount; n++){
      if (n == field->nCount){ //edge case of border
        if (counter >= 4){
            removeBlocks(compareRec, counter, RIGHT, field);
          }
      }else{
        currentRec = getArrayEl(m,n,field);
        if (checkIfSame(compareRec, currentRec, field)){ //if same colour and block is alive as compareRec
          counter++;
        }else{ //if not same colour block
          if (counter >= 4){
            removeBlocks(compareRec, counter, RIGHT, field);
          }
          compareRec = currentRec;
          counter = 1;
        }
      }
    }
  }
  //for vertical check
  counter = 0;
  for (int8_t n = 0; n<field->nCount; n++){
    compareRec = getArrayEl(0,n,field);
    counter = 0;
    for (int8_t m = 0; m<= field->mCount; m++){
      if (m == field->mCount){ //edge case of border
        if (counter >= 4){
            removeBlocks(compareRec, counter, DOWN, field);
          }
      }else{
        currentRec = getArrayEl(m,n,field);
        if (checkIfSame(compareRec, currentRec, field)){ //if same colour and block is alive as compareRec
          counter++;
        }else{ //if not same colour block
          if (counter >= 4){
            removeBlocks(compareRec, counter, DOWN, field);
          }
          compareRec = currentRec;
          counter = 1;
        }
      }
    }
  }
}


void makeLevelHarder(Playfield* field){
  fillScreen(backgroundColour); //remove edge colours
  field->currentLevel++;
  field = makeArray(field->currentLevel, field->bombBool, field->timeCountInit, 0, field);
  makeViruses(field);
  drawScreen(playfield);
}

//game init, will be called at start of the game
void gameInit(int8_t bombBool, int8_t timeCount, int8_t currentLevel){
    playfield = makeArray(currentLevel, bombBool, timeCount, 1, playfield);
    playfield->currentLevel = currentLevel;
    srand(time(NULL));
    resetScore(playfield);
    makeViruses(playfield);
    drawScreen(playfield);
}

void setCreditScreen(){
  fillScreen(backgroundColour);
  uint16_t waittime = 200;
  for (int i=0; i<5;i++){
    setCreditScreenText(GREEN);
    makeSound(500);
    delay(waittime);
    setCreditScreenText(ORANGE);
    makeSound(800);
    delay(waittime);
    setCreditScreenText(YELLOW);
    makeSound(400);
    delay(waittime);
    }
}


void drawEndScreen(Playfield* field){
    drawArrayAlive(field);
    setGameOverText(field);
}
void drawWinScreen(Playfield* field){
    drawArrayAlive(field);
    setGameWonText(field);
}

//game won
void gameWon(Playfield* field){
  drawWinScreen(field);
  makeWinSound();
  delay(5000);
  makeLevelHarder(field);
}

//for choiceMenu
int getChoiceTextColour(int8_t index, int8_t currentHighlight){
  if (index==currentHighlight)
    return YELLOW;
  return WHITE;
  }

void drawChoiceMenu(){
    int8_t textSize = 1;
    int yValue = 30;
    fillScreen(backgroundColour);
    setText("DR MARIO", 10, 10, 2*textSize, RED);
    setText("CHOOSE MODE", 10, yValue, 1.5, ORANGE);
}
//draws choice menu, can select a gamemode
void choiceMenu(){
  int yValue = 30;
  int8_t currentChoice = 1;
  int8_t totalchoices = 5;
  int8_t bombBool = 1;
  int8_t timeCountInit = 20;
  int16_t waitTime = 10;
  int8_t currentLevel = 1;
  int8_t textSize = 1;
  drawChoiceMenu();
  int i = 0; //smoothness of controlls
  while (1){
    if (CheckIfAPressed() && i>20){
      if (currentChoice==totalchoices){
        currentChoice=1;
      }else{
        currentChoice++;  
      }
      makeMenuSound();
      i = 0;
    }
    else if (CheckIfBPressed() && i>20){
      makeClickSound();
      switch (currentChoice){
        case 1: 
          gameInit(0, 0, currentLevel);
          return;
        case 2: 
          gameInit(bombBool, 0, currentLevel);
          return;
        case 3: 
          gameInit(0, timeCountInit, currentLevel);
          return;
        case 4:
          gameInit(bombBool, timeCountInit, currentLevel);
          return;
        case 5:
          currentLevel = currentLevel%10 + 1;
          drawChoiceMenu();
      }
      i = 0;
    }

    setText("1) Normal", 10, yValue*3, textSize, getChoiceTextColour(1, currentChoice));
    setText("2) Bombs", 10, yValue*4, textSize, getChoiceTextColour(2, currentChoice));
    setText("3) Timed virus", 10, yValue*5, textSize, getChoiceTextColour(3, currentChoice));
    setText("4) Bombs+timed virus", 10, yValue*6, textSize, getChoiceTextColour(4, currentChoice));
    setTextInt("5) Current level %i", currentLevel, 10,yValue*7, textSize, getChoiceTextColour(5, currentChoice));
    delay(waitTime);
    i++;
  }

}
//saves highscore
void changeHighScoreIfNeeded(Playfield* field){
  if (getHighScore()<getScore(field)){
    setHighScore(getScore(field));
    saveHighScore();
  }
}
//will be called if game over
void gameOver(Playfield* field){
  int gameOverWaitTime = 5000;
  drawEndScreen(field);
  makeLoseSound();
  delay(gameOverWaitTime);
  changeHighScoreIfNeeded(field);
  freeEverything(field); //frees everything from memory 
  choiceMenu(); //restart game
}


//makes new pill that will fall
void makeNewPill(int8_t mL,int8_t nL, int8_t mR,int8_t nR, Playfield* field){
  int8_t r1 = abs((rand()*7))%colourCount;
  int8_t r2 = abs((rand()*13)+1)%colourCount; //to choose random colours for pills
  
  Rect *recL = getArrayEl(mL, nL, field);
  Rect *recR = getArrayEl(mR, nR, field); 
  //for timend virus
  if (field->timedVirusBool){
    if (field->timeLeft!=0){
      field->timeLeft--; //every new make of a pill, decrement by one
    }else{
      if (field->timedVirusesLeft>0){ //if timedvirus arent elliminated before timer runs out, game over
        gameOver(field);
      }
    }
  }
  if (field->bombBool && rand()%bombChance==0){ //init bomb
    field->bombFallingNow = 1;
    changeRecValues(recL, -2, 1, 0);
    changeRecValues(recR, -1, 0, 0);
    insertInList(recL, recL, field);
  }else{
    changeRecValues(recL, r1, 1, 0);
    changeRecValues(recR, r2, 1, 0);
    insertInList(recL, recR, field);
  }
}

void pillRotates(Playfield* field){
  struct node* head = field->linkedListOfPills;
  Pill* currentPill = head->pill;
  Rect* recLeft = currentPill->recL; //leftpill will never rotate
  Rect* recRight = currentPill->recR; //this will rotate
  direction currentDir = currentPill->dir;
  switch (currentDir){
    case UP: //rotates to right, rightpill will be right of leftpill
      if (checkMovePossible(recLeft, DOWN, field)){ //check if mrightpill can be placed here (check if still in bounds)
        switchRec(getRectAround(recLeft, DOWN, field), recRight, field);
        currentPill->dir = RIGHT;
      }
      break;
    case RIGHT: //rotates to down, rightpill will be under of leftpill
      if (checkMovePossible(recLeft, LEFT, field)){
        switchRec(getRectAround(recLeft, LEFT, field), recRight, field);
        currentPill->dir = DOWN;
      }
      break;
    case DOWN: //rotates to left, rightpill will be left of leftpill
      if (checkMovePossible(recLeft, UP, field)){
        switchRec(getRectAround(recLeft, UP, field), recRight, field);
        currentPill->dir = LEFT;
      }
      break;
    case LEFT: //rotates to up, rightpill will be above of leftpill
      if (checkMovePossible(recLeft, RIGHT, field)){
        switchRec(getRectAround(recLeft, RIGHT, field), recRight, field);
        currentPill->dir = UP;
      }
      break;
  }
  
}


void movePillHorizontal(direction dirToGo, Playfield* field){
  struct node* head = field->linkedListOfPills;
  Pill* currentPill = head->pill;
  direction currentDir = currentPill->dir;
  Rect* recL = currentPill->recL;
  Rect* recR = currentPill->recR;
  Rect* recToGo;
  direction dirCurrent = currentPill->dir;
  int8_t nToGO;
  
  if (field->bombFallingNow && checkMovePossible(recL, dirToGo, field)){ //if a bomb
    switchRec(recL, getRectAround(recL, dirToGo, field), field);
  } else { //if not a bomb
    switch (dirCurrent){
      case UP: case DOWN: //if pill is horizontal
        if (checkMovePossible(recL, dirToGo, field)||checkMovePossible(recR, dirToGo, field)){
          switch (dirToGo){
            case LEFT:
              if (recL->n<recR->n){
                switchRec(recL, getRectAround(recL, dirToGo, field), field);
                switchRec(recR, getRectAround(recR, dirToGo, field), field);
              }else{
                switchRec(recR, getRectAround(recR, dirToGo, field), field);
                switchRec(recL, getRectAround(recL, dirToGo, field), field);
              }
              break;
            case RIGHT:
              if (recL->n<recR->n){
                switchRec(recR, getRectAround(recR, dirToGo, field), field);
                switchRec(recL, getRectAround(recL, dirToGo, field), field);
              }else{
                switchRec(recL, getRectAround(recL, dirToGo, field), field);
                switchRec(recR, getRectAround(recR, dirToGo, field), field);
              }
              break;
            }  
        }
        break;
      case LEFT: case RIGHT: //if pill is vertical   
        if (checkMovePossible(recL, dirToGo, field)&&checkMovePossible(recR, dirToGo, field)){
          switchRec(recL, getRectAround(recL, dirToGo, field), field);
          switchRec(recR, getRectAround(recR, dirToGo, field), field);
        }
        break;
    }
  }
}

//lets bomb explode 
void letBombExplode(Playfield* field){
  field->bombFallingNow = 0;
  Rect* bomb = field->linkedListOfPills->pill->recL;
  Rect* temp;
  
  int8_t bombM = bomb->m;
  int8_t bombN = bomb->n;

  //set everything around bomb in bomb colour to show the explosion
  if (checkInBounds(bombM-1,bombN, field)){
    drawExplosionRect(getRectAround(bomb, UP, field), field);
  }
  if (checkInBounds(bombM,bombN+1, field)){
    drawExplosionRect(getRectAround(bomb, RIGHT, field), field);
  }
  if (checkInBounds(bombM+1,bombN, field)){
    drawExplosionRect(getRectAround(bomb, DOWN, field), field);
  }
  if (checkInBounds(bombM,bombN-1, field)){
    drawExplosionRect(getRectAround(bomb, LEFT, field), field);
  }
  drawExplosionRect(bomb, field);
  makeExplosionSound(); //explosion sound effect
  delayGame(1, field);

  //removes everything around bomb
  if (checkInBounds(bombM-1,bombN, field)){
    removeRect(getRectAround(bomb, UP, field), field);
  }
  if (checkInBounds(bombM,bombN+1, field)){
    removeRect(getRectAround(bomb, RIGHT, field), field);
  }
  if (checkInBounds(bombM+1,bombN, field)){
    removeRect(getRectAround(bomb, DOWN, field), field);
  }
  if (checkInBounds(bombM,bombN-1, field)){
    removeRect(getRectAround(bomb, LEFT, field), field);
  }
  removeRect(bomb, field); //removes bomb itself
  letEverythingFall(field);
}


//main gameloop that will loop until pill cant more vertical anymore. Wil also be possible here to move and rotate the pill while playing
void gameLoop(Playfield* field){
  struct node* head = field->linkedListOfPills;
  Pill* currentPill = head->pill;
  Rect* recL =  currentPill->recL;
  Rect* recR = currentPill->recR;
  int8_t loopCount = 100; //how higher how more times you can rotate and move the pill every time it falls. Set on 3 -> max 3 times possible to rotate and move every fall
  int8_t moveCount = 50;
  int8_t turnCount = 30;
  int8_t lastMove = 15;

  drawPillAround(currentPill, field); //draws array
  //will make it possible to move and rotate the pill each gameloop
  for (int i = 0; i<loopCount; i++){
    lastMove++;
    if (lastMove >= turnCount && CheckIfAPressed() && !field->bombFallingNow){
      pillRotates(field);
      drawPillAround(currentPill, field);
      lastMove = 0;
    }
    if (CheckIfBPressed()){ // for save
      lastMove = 0;
    }
    direction tilt = giveTilt();
    if (tilt == DOWN){
      i += loopCount/10;
      delayGame(100, field);
    }else if (lastMove >= moveCount && (tilt == RIGHT || tilt == LEFT)) {
      movePillHorizontal(tilt, field);
      drawPillAround(currentPill, field);
      delayGame(100, field);
      lastMove = 0;
    }
    else{
      delayGame(100, field);
    }
  }
  //lets the pill fall, if possible, call procedure again, if not, stop gameloop
  int8_t Mmax = giveMaximum(recL->m, recR->m); //maximum m (y) value of the pill, is to check if it's at the bottom or if it hit anything
  direction dirCurrent = currentPill->dir;
  if (field->bombFallingNow && checkIfEmptyDown(recL->m, recL->n, field)){
        switchRec(recL, getRectAround(recL, DOWN, field), field);
        gameLoop(field);
  } else if (checkIfEmptyDown(Mmax, recL->n, field) && checkIfEmptyDown(Mmax,  recR->n, field)){
    if (dirCurrent == RIGHT){
      switchRec(recR, getRectAround(recR, DOWN, field), field);
      switchRec(recL, getRectAround(recL, DOWN, field), field);
    }else{
      switchRec(recL, getRectAround(recL, DOWN, field), field);
      switchRec(recR, getRectAround(recR, DOWN, field), field);
    }
    gameLoop(field); //recursion untill pill cant fall anymore
  }
  else{ //cant fall anymore, check for 4 in a row or if gameover
    if (recL->m == pillStartHeight && recR->m == pillStartHeight){ //if true, then gameover
      gameOver(field); //gameover screen
    }else{
      if (field->bombFallingNow){
        letBombExplode(field);
      }else{
        checkFourInARow(field); //checks if 4 in a row
      }
    }
  }
}
