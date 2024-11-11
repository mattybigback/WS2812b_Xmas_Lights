#include <Adafruit_NeoPixel.h>
#define LED_COUNT 60
#define LED_PIN 16

Adafruit_NeoPixel string(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
uint32_t timerThen;
uint32_t timerNow;
uint8_t mode = 0;

uint32_t colWarmWhite = string.ColorHSV(3600, 240, 255);

void setup() {
    analogReadResolution(8);
    uint8_t seed = analogRead(26);
    randomSeed(seed);
    string.begin();
    string.setBrightness(50);
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
        switch ((offset + led) % 4) {
        case 0:
            string.setPixelColor(led, 255, 0, 0);
            break;
        case 1:
            string.setPixelColor(led, 255, 64, 0);
            break;
        case 2:
            string.setPixelColor(led, 0, 255, 0);
            break;
        default:
            string.setPixelColor(led, 0, 0, 255);
        }
    }
    string.show();
}

void staticExpanded(uint8_t offset) {
    for (uint8_t led; led < LED_COUNT; led++) {
        switch ((offset + led) % 7) {
        case 0:
            string.setPixelColor(led, 255, 0, 0);
            break;
        case 1:
            string.setPixelColor(led, 255, 16, 0);
            break;
        case 2:
            string.setPixelColor(led, 255, 127, 0);
            break;
        case 3:
            string.setPixelColor(led, 0, 255, 0);
            break;
        case 4:
            string.setPixelColor(led, 0, 0, 255);
            break;
        case 5:
            string.setPixelColor(led, 255, 0, 127);
            break;
        case 6:
            string.setPixelColor(led, 32, 0, 255);
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

void chasingExpanded(uint8_t wait, bool reverse) {
    if (reverse) {
        for (uint8_t i = 7; i > 0; i--) {
            staticExpanded(i);
            delay(wait);
        }
    } else {
        for (uint8_t i = 0; i < 7; i++) {
            staticExpanded(i);
            delay(wait);
        }
    }
}

void comet(uint8_t wait, uint16_t hue1, uint16_t hue2) {
    const uint8_t saturationValues[] = {255, 255, 255, 252, 250, 248, 242, 238, 230, 220, 200, 0};
    const uint8_t brightnessValues[] = {30, 50, 70, 90, 110, 150, 150, 160, 160, 180, 200, 255};

    for (uint32_t hue = hue1; hue <= hue2; hue = hue) {
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            for (uint8_t j = 0; j < LED_COUNT; j++) {
                string.setPixelColor(j, 0);
            }

            for (uint8_t k = 0; k < 12; k++) {
                string.setPixelColor((i + k) % LED_COUNT, string.ColorHSV(hue, saturationValues[k], brightnessValues[k]));
                hue += 100;
            }
            string.show();
            delay(wait);
        }
    }
}

void twoColorsWithSpace(uint8_t color1_g, uint8_t color1_r, uint8_t color1_b, uint8_t color2_g, uint8_t color2_r, uint8_t color2_b, uint8_t offset) {
    for (uint8_t led; led < LED_COUNT; led++) {
        switch ((offset + led) % 4) {
        case 0:
            string.setPixelColor(led, color1_r, color1_g, color1_b);
            break;
        case 2:
            string.setPixelColor(led, color2_r, color2_g, color2_b);
            break;
        default:
            string.setPixelColor(led, 0, 0, 0);
        }
    }
    string.show();
}

void tradAltFlash(uint16_t wait) {
    twoColorsWithSpace(255, 0, 0, 0, 0, 255, 0);
    delay(wait);
    twoColorsWithSpace(0, 255, 0, 64, 255, 0, 1);
    delay(wait);
}

void monoRainbow(uint8_t increment, uint8_t wait) {
    for (uint32_t hue = 0; hue < 65535; hue += increment) {
        for (uint8_t led = 0; led < LED_COUNT; led++) {
            string.setPixelColor(led, string.ColorHSV(hue, 255, 255));
            delay(wait);
        }
        string.show();
    }
}

void demoReel(uint16_t timeout) {
    timerNow = millis();
    uint16_t cometHue = random(0, 65535);

    switch (mode) {
    case 1:
        comet(25, cometHue, cometHue);
        break;
    case 3:
        monoRainbow(1000, 1);
        break;
    case 2:
        comet(12, 1, 65534);
        break;
    case 0:
        string.fill(string.ColorHSV(3600, 240, 255), 0, LED_COUNT-1);
        string.show();
        break;
    case 4:
        rainbow(5);
        break;
    case 5:
        chasingExpanded(250, false);
        break;
    case 6:
        tradAltFlash(250);
        break;
    case 7:
        chasingTrad(250, true);
        break;
    case 8:
        staticTrad(0);
        break;
    default:
        mode = 0;
    }
    if (timerNow - timerThen >= timeout) {
        mode++;
        timerThen = millis();
    }
}
