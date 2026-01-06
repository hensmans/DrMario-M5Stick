#include "EEPROM.h"

#include "textFunctions.h"
//to commit saved data in flash memory
void commitEeprom(){
  EEPROM.commit();
}

//resets flash memory to zero
void deleteFlashMemory(int from, int to){
    for (int i = from; i<=to; i++){
        EEPROM.put(1, 0);
    }
    commitEeprom();
}
//saves highscore in flash memory
void saveHighScore(){
  uint16_t highscoretemp = getHighScore();
  EEPROM.put(1, highscoretemp); //reserved for highscore
  commitEeprom();
}
//loads highscore from memory
void loadHighScore(){
    uint16_t highscoretemp = 0;
    EEPROM.get(1, highscoretemp);
    setHighScore(highscoretemp); 
}

//loads highscore
void loadInformationFromFlash(){
  uint8_t doneInit = EEPROM.read(0); 
  if (doneInit==1){ //there is data written i nthe flash memory
    loadHighScore();
  }else{ //no data written in flash memory yet
    EEPROM.write(0, 1);
    //highscore init
    uint16_t highscoretemp = 0;
    EEPROM.put(1, highscoretemp); //reserved for highscore
    setHighScore(highscoretemp);
    //commit
    commitEeprom();
  }
}
