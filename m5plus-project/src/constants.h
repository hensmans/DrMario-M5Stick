

const int screenWidth  = 135;
const int screenHeight = 240;
const int8_t recWidthCount =  7;
const int8_t recHeightCount =  12;
const uint8_t pillStartHeight = 0;
const uint8_t pillStartWidth = recWidthCount/2;
const int backgroundColour = M5.Lcd.color565(3, 3, 5);
const int bombColour = M5.Lcd.color565(100, 0, 100);
const int bombExplosionColour = M5.Lcd.color565(80, 0, 80);

const uint32_t textColour = M5.Lcd.color565(250, 250, 250);;
const uint16_t waitTimeInit = 700;
static uint16_t totalScore = 0;
static uint16_t highScore;

const int8_t biggerScreenLevel = 3;
const int8_t biggestScreenLevel = 5;

const int coloursVector[] = {M5.Lcd.color565(230, 10, 10), M5.Lcd.color565(10, 230, 10),  M5.Lcd.color565(10, 10, 230), M5.Lcd.color565(140, 0, 0), M5.Lcd.color565(0, 90, 0), M5.Lcd.color565(0, 0, 90)};
const uint8_t colourCount = 3;

const uint8_t colourVirusCountInit = 1;
const uint8_t bombChance = 10;