#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define NUM_LEDS 20

CRGB leds[NUM_LEDS];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  rainbowEffect(20); // Speed control: lower value -> faster animation
}

void rainbowEffect(int wait) {
  uint8_t j;

  for (j = 0; j < 256; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Wheel((i + j) & 255);
      pixels.setPixelColor(i, pixels.Color(leds[i].r, leds[i].g, leds[i].b));
    }
    FastLED.show();
    pixels.show();
    delay(wait);
  }
}

CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
