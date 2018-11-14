#include <FastLED.h>

#define LED_COUNT 8
#define LED_PIN 2

#define STRENGTH_PIN A0
#define STRENGTH_MAX 400

int avalue, i, avalues[50];
CRGB leds[LED_COUNT];

void strengthAnimation(int value);
void turnOnAmount(int amount);

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  // Serial.begin(9600);
}

void loop() {
  while(avalue < 50){
    avalue = analogRead(STRENGTH_PIN);
  }
  for(int i = 0; i < 50; i++){
    avalues[i] = analogRead(STRENGTH_PIN);
  }
  for(int i = 0; i < 50; i++){
    if(avalues[i] > avalue){
      avalue = avalues[i];
    }
  }
  // Serial.print(avalue);
  strengthAnimation(avalue);
  avalue = 0;
}

void strengthAnimation(int value) {
  int leds = (value * LED_COUNT) / STRENGTH_MAX;
  // Serial.println(leds);
  for (int i = 1; i <= leds; i++) {
    turnOnAmount(i);
    delay(30);
  }
  delay(500);
  for (int i = leds; i >= 0; i--) {
    turnOnAmount(i);
    delay(30);
  }
}

void turnOnAmount(int amount) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }
  if (amount != 0) {
    for (int i = 0; i < amount; i++) {
      leds[i] = CHSV(170 - (i * (170 / LED_COUNT + 1)), 255, 100);
    }
  }
  FastLED.show();
}