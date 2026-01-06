#include "eepromFunctions.h"

void letEverythingFall(Playfield* field);
void checkFourInARow(Playfield* field);

void makeSound(int frequency){
  M5.Beep.tone(frequency);
  delay(30);
  M5.Beep.tone(0);
}
void makeExplosionSound(){
  makeSound(300);
  makeSound(400);
  makeSound(500);
}
void makeClickSound(){
  makeSound(1000);
  delay(60);
  makeSound(2000);
}
void makeMenuSound(){
  makeSound(1000);
}
void makeMoveSound(){
  makeSound(500);
}
void make4InARowSound(){
  makeSound(750);
  delay(60);
  makeSound(850);
}
void makeWinSound(){
  makeSound(750);
  delay(150);
  makeSound(1400);
  delay(120);
  makeSound(2000);
}
void makeLoseSound(){
  makeSound(750);
  delay(100);
  makeSound(500);
  delay(150);
  makeSound(300);
}
void updateM5(){
  M5.update();
}

int CheckIfAPressed(){
  updateM5();
  return M5.BtnA.isPressed();
}
int CheckIfBPressed(){
  updateM5();
  return M5.BtnB.isPressed();
}


  direction giveTilt(){
    float minTiltMoveHorizontal = 0.25;
    float minTiltFaster = 0.97;
    float accX = 0;
    float accY = 0;
    float accZ = 0;
    M5.IMU.getAccelData(&accX, &accY, &accZ);

    if (accX>minTiltMoveHorizontal){
      return LEFT;
    }
    else if (accX<-minTiltMoveHorizontal){
      return RIGHT;
    }
    else if (accY>minTiltFaster){
      return DOWN;
    }
    return NOTHING;
  }