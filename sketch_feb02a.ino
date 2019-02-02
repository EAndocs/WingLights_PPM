#include <FastLED.h>   // Library to control LEDs

// Define constants
#define LED_PIN 2
#define PWM_PIN 3
#define NUM_LEDS 3  // Testing with a short LED strip

// Declare variables
int pwm_value;
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB(leds, NUM_LEDS);  // Init like this (GRB) to make RGB numbers correspond correctly to RGB
  pinMode(PWM_PIN, INPUT);
  Serial.begin(9600);

  // Start with all LEDs off
  leds[0] = CRGB(0,0,0);
  leds[1] = CRGB(0,0,0);
  leds[2] = CRGB(0,0,0);
  FastLED.show();
}

void loop() {
  // Get PWM value and print to console for debugging
  pwm_value = pulseIn(PWM_PIN, HIGH);
  Serial.println(pwm_value);

  if (pwm_value < 1333) {
    // All LEDs off
    leds[0] = CRGB(0,0,0);
    leds[1] = CRGB(0,0,0);
    leds[2] = CRGB(0,0,0);
    FastLED.show();
  }
}
