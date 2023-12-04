#include <Adafruit_NeoPixel.h>
#define LED_COUNT 50
#define LED_PIN 3

Adafruit_NeoPixel string(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    string.begin();
    string.show();
    string.setBrightness(50);
}

void loop() {

    // chasing_expanded(250, true);
    // chasing_expanded(250, false);
    chasing_trad(250, true);
    chasing_trad(250, false);
    // rainbow(10);

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


void static_trad(uint8_t offset) {
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

void static_expanded(uint8_t offset) {
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

void chasing_trad(uint8_t wait, bool reverse){
  if (reverse){
    for (uint8_t i=4; i>0; i--) {
      static_trad(i);
      delay(wait);
    }
  } else {
    for (uint8_t i=0; i<4; i++) {
      static_trad(i);
      delay(wait);
    }
  }
}

void chasing_expanded(uint8_t wait, bool reverse){
  if (reverse){
    for (uint8_t i=7; i>0; i--) {
      static_expanded(i);
      delay(wait);
    }
  } else {
    for (uint8_t i=0; i<7; i++) {
      static_expanded(i);
      delay(wait);
    }
  }
}