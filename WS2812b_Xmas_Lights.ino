#include <Adafruit_NeoPixel.h> // v 1.11.0
#define LED_COUNT 50
#define LED_PIN 3

Adafruit_NeoPixel string(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
uint32_t timerThen;
uint32_t timerNow;
uint8_t mode = 0;
uint8_t maxMode = 6;

uint32_t colWarmWhite = string.ColorHSV(3600,240);


void setup() {
    Serial.begin(115200);
    string.begin();
    string.setBrightness(255);
    string.show();
    timerThen = millis();
}

void loop() {
  demoReel(10000);
}

void rainbow(uint16_t wait) {
    for (uint32_t firstLEDHue = 0; firstLEDHue < 5 * 65536; firstLEDHue += 256) {
        for (uint16_t i = 0; i < string.numPixels(); i++) {
            uint16_t LEDHue = firstLEDHue + (i * 65536L / string.numPixels());
            string.setPixelColor(i, string.gamma32(string.ColorHSV(LEDHue)));
        }
        string.show();
        delay(wait);
    }
}


void staticTrad(uint8_t offset) {
  for (uint8_t led; led < LED_COUNT; led++) {
    switch((offset+led) % 4) {
      case 0:
        string.setPixelColor(led, 255,0,0);
        break;
      case 1:
        string.setPixelColor(led, 255,64,0);
        break;
      case 2:
        string.setPixelColor(led, 0,255,0);
        break;
      default:
        string.setPixelColor(led, 0,0,255);
    }
  }
  string.show();
}

void staticExpanded(uint8_t offset) {
  for (uint8_t led; led < LED_COUNT; led++) {
    switch((offset+led) % 7) {
      case 0:
        string.setPixelColor(led, 255,0,0);
        break;
      case 1:
        string.setPixelColor(led, 255,16,0);
        break;
      case 2:
        string.setPixelColor(led, 255,127,0);
        break;
      case 3:
        string.setPixelColor(led, 0,255,0);
        break;
      case 4:
        string.setPixelColor(led, 0,0,255);
        break;
      case 5:
        string.setPixelColor(led, 255, 0, 127);
        break;
      case 6:
        string.setPixelColor(led, 32,0,255);
    }
  }
  string.show();
}

void chasingTrad(uint8_t wait, bool reverse) {
  uint8_t start = reverse ? 4 : 0;
  uint8_t end = reverse ? 0 : 4;
  int8_t step = reverse ? -1 : 1;

  for (uint8_t i = start; i != end; i += step) {
    staticTrad(i);
    delay(wait);
  }
}

void chasingExpanded(uint8_t wait, bool reverse){
  if (reverse){
    for (uint8_t i=7; i>0; i--) {
      staticExpanded(i);
      delay(wait);
    }
  } else {
    for (uint8_t i=0; i<7; i++) {
      staticExpanded(i);
      delay(wait);
    }
  }
}

void comet(uint8_t wait, uint16_t hue){
  for (uint8_t i=0; i<LED_COUNT; i++) {
    for (uint8_t j=0; j < LED_COUNT; j++){
      string.setPixelColor(j,0);
    }
    string.setPixelColor(i % LED_COUNT,     string.ColorHSV(hue,255,30));
    string.setPixelColor((i+1) % LED_COUNT, string.ColorHSV(hue,255,50));
    string.setPixelColor((i+2) % LED_COUNT, string.ColorHSV(hue,255,70));
    string.setPixelColor((i+3) % LED_COUNT, string.ColorHSV(hue,252,90));
    string.setPixelColor((i+4) % LED_COUNT, string.ColorHSV(hue,250,110));
    string.setPixelColor((i+5) % LED_COUNT, string.ColorHSV(hue,245,150));
    string.setPixelColor((i+6) % LED_COUNT, string.ColorHSV(hue,240,150));
    string.setPixelColor((i+7) % LED_COUNT, string.ColorHSV(hue,230,160));
    string.setPixelColor((i+8) % LED_COUNT, string.ColorHSV(hue,220,160));
    string.setPixelColor((i+9) % LED_COUNT, string.ColorHSV(hue,210,180));
    string.setPixelColor((i+10) % LED_COUNT, string.ColorHSV(hue,190,200));
    string.setPixelColor((i+11) % LED_COUNT, string.ColorHSV(hue,0,255));







    string.show();
    delay(wait);
    }
  }

void twoColorsWithSpace(uint8_t color1_g, uint8_t color1_r, uint8_t color1_b, uint8_t color2_g, uint8_t color2_r, uint8_t color2_b, uint8_t offset){
    for (uint8_t led; led < LED_COUNT; led++) {
      switch((offset+led) % 4) {
        case 0:
          string.setPixelColor(led, color1_g, color1_r, color1_b);
          break;
        case 2:
          string.setPixelColor(led, color2_g, color2_r, color2_b);
          break;
        default:
          string.setPixelColor(led, 0,0,0);
      }
      string.show();
    }
}

void tradAltFlash(uint16_t wait) {
    twoColorsWithSpace(255,0,0,0,0,255,0);
    delay(wait);
    twoColorsWithSpace(0,255,0,64,255,0,1);
    delay(wait);
}

void demoReel(uint16_t timeout){
  timerNow = millis();
  switch (mode) {
    case 1:
      comet(20, 45000);
      break;
    case 0:
      string.fill(colWarmWhite);
      string.show();
      break;
    case 2:
      rainbow(5);
      break;
    case 3:
      chasingExpanded(250, false);
      break;
    case 4:
      tradAltFlash(250);
      break;
    case 5:
      chasingTrad(250, true);
      break;
    case 6:
      staticTrad(0);
      break;
    default:
      mode=0;
    }
  if (timerNow - timerThen >= timeout){
    mode++;
    timerThen = millis();
  }
}
