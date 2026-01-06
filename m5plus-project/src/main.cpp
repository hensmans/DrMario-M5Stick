#include <M5StickCPlus.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EEPROM.h"
#include "gameLogica.h"


// the setup routine runs once when M5StickC starts up
void setup() {
  // initialize the M5StickC object
  M5.begin();
  M5.IMU.Init();
  Serial.begin(115200);
  Serial.flush();
  EEPROM.begin(512);
  loadInformationFromFlash(); //loads highscore from flash memory
  setCreditScreen(); //shows made by daan hensmans
  choiceMenu(); //INITIALIZE GAME, choose gamemode
}

// the loop routine runs over and over again forever, will make new pill every loop 
void loop(){
  makeNewPill(pillStartHeight, pillStartWidth, pillStartHeight, pillStartWidth+1, playfield); //makes new pill with 2 blocks
  drawScreen(playfield);
  gameLoop(playfield); //let pill fall
  delayGame(1, playfield); //wait waittime
  M5.update();
}
