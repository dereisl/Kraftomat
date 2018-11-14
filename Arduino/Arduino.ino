#include <FastLED.h>

#define LED_COUNT 8
#define LED_PIN 2

CRGB leds[LED_COUNT];

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
}
void loop() {
  for (int i = 0; i < LED_COUNT; i++) {
    turnOnAmount(i);
    delay(30);
  }
  for (int i = LED_COUNT - 1; i >= 0; i--) {
    turnOnAmount(i);
    delay(30);
  }
}

void turnOnAmount(int amount) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }
  for (int i = 0; i <= amount; i++) {
    leds[i] = CHSV(170 - (i * (170 / LED_COUNT + 1)), 255, 100);
  }
  FastLED.show();
}