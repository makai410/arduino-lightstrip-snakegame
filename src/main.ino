#include <FastLED.h>
#include "rules.h"

#define NUM_LEDS 64
#define DATA_PIN 7
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

uint8_t max_bright = 10;

SnakeGame game;

void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(max_bright);
    game = SnakeGame();
    game.init();
}

void loop()
{
    game.loop(leds);
    delay(30);
}
