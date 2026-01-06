#include "abstractFunctions.h"

//fils screen in a colour
void fillScreen(int colour){
  M5.Lcd.fillScreen(colour);
}

//set text
void setText(const char* text, int x, int y, int textSize, int colour){
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextColor(colour);
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.printf(text);
  M5.update();
}
//set text with an int value
void setTextInt(const char* text, int i, int x, int y, int size, int colour){
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextColor(colour);
  M5.Lcd.setTextSize(size);
  M5.Lcd.printf(text,i);
  M5.update();
}
//for error testing
void setTextIntAndWait(int i, int ms){
  fillScreen(WHITE);
  setTextInt("ERROR testing: %i",i, 2, 100, 1, PURPLE);
  delay(ms);
}
//sets highscore text
void setHighScoreText(Playfield* field){
  setTextInt("HSCORE %i", getHighScore(), 2, 5, 1, textColour);
}
void setScoreText(Playfield* field){
  setTextInt("SCORE:%i", getScore(field), 2, 15, 1, textColour);
}
void setGameOverText(Playfield* field){
  setScoreText(field);
  setHighScoreText(field);
  setText("GAMEOVER", 15, screenHeight/2, 2, WHITE);
}
void setGameWonText(Playfield* field){
  setScoreText(field);
  setHighScoreText(field);
  setText("GAME WON!", 15, screenHeight/2, 2, GREEN);
  setText("loading next level", 15, screenHeight/2+20, 1, YELLOW);
}

void setCreditScreenText(int colour){
  uint8_t  xoffset1 = 45;
  uint8_t xoffset2 = 27;
  uint8_t size = 1;
  setText("MADE BY", xoffset1, screenHeight/2-10, size, colour);
  setText("DAAN HENSMANS", xoffset2, screenHeight/2+10, size, colour);
}


void setTimerText(Playfield* field){
  if (field->timedVirusBool)
    setTextInt("TIMER:%i", field->timeLeft, screenWidth-50, 15, 1, textColour);
}
void setLevelText(Playfield* field){
  setTextInt("LEVEL:%i", field->currentLevel, screenWidth-50, 5, 1, textColour);
}
void setScreenText(Playfield* field){
  setHighScoreText(field);
  setScoreText(field);
  setLevelText(field);
  setTimerText(field);
}
