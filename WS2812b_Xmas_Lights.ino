#include <Adafruit_NeoPixel.h> // v 1.11.0
#define LED_COUNT 50
#define LED_PIN 3

Adafruit_NeoPixel string(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t timerThen;
uint32_t timerNow;
uint8_t mode = 0;
uint8_t maxMode = 5;

uint32_t colWarmWhite = string.ColorHSV(19000,240);


void setup() {
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
        string.setPixelColor(led, 0,255,0);
        break;
      case 1:
        string.setPixelColor(led, 64,255,0);
        break;
      case 2:
        string.setPixelColor(led, 255,0,0);
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
        string.setPixelColor(led, 0,255,0);
        break;
      case 1:
        string.setPixelColor(led, 16,255,0);
        break;
      case 2:
        string.setPixelColor(led, 127,255,0);
        break;
      case 3:
        string.setPixelColor(led, 255,0,0);
        break;
      case 4:
        string.setPixelColor(led, 0,0,255);
        break;
      case 5:
        string.setPixelColor(led, 0, 255, 127);
        break;
      case 6:
        string.setPixelColor(led, 0,32,255);
    }
  }
  string.show();
}

void chasingTrad(uint8_t wait, bool reverse){
  if (reverse){
    for (uint8_t i=4; i>0; i--) {
      staticTrad(i);
      delay(wait);
    }
  } else {
    for (uint8_t i=0; i<4; i++) {
      staticTrad(i);
      delay(wait);
    }
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
    case 0:
      string.fill(colWarmWhite);
      string.show();
      break;
    case 1:
      rainbow(5);
      break;
    case 2:
      chasingExpanded(250, false);
      break;
    case 3:
      tradAltFlash(250);
      break;
    case 4:
      chasingTrad(250, true);
      break;
    case 5:
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
