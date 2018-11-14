#include <FastLED.h>

#define LED_COUNT 8
#define LED_PIN 2

#define STRENGTH_PIN A0
#define STRENGTH_MIN 50
#define STRENGTH_MAX 400

int avalue, avalues[50];
CRGB leds[LED_COUNT];

void strengthAnimation(int value);
void turnOnAmount(int amount);

void setup() {
  // Initialize WS2812B library
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
}

void loop() {
  // Treshold for triggering LEDs
  while(avalue < STRENGTH_MIN){
    avalue = analogRead(STRENGTH_PIN);
  }
  // Meassure 50 times
  for(int i = 0; i < 50; i++){
    avalues[i] = analogRead(STRENGTH_PIN);
  }
  // Take the highest value of 50 meassuring points
  for(int i = 0; i < 50; i++){
    if(avalues[i] > avalue){
      avalue = avalues[i];
    }
  }
  // Start LED animation
  strengthAnimation(avalue);
  // Reset avalue
  avalue = 0;
}

void strengthAnimation(int value) {
  // Calculate the amount of LEDs to light up
  int leds = (value * LED_COUNT) / STRENGTH_MAX;
  // Animate build up
  for (int i = 1; i <= leds; i++) {
    turnOnAmount(i);
    delay(30);
  }
  delay(500);
  // Animate down again
  for (int i = leds; i >= 0; i--) {
    turnOnAmount(i);
    delay(30);
  }
}

// Function to turn off a specific amount of LEDs
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