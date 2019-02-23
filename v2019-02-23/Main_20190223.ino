#include <FastLED.h>

#define LED_PIN 2
#define PWM_PIN 3
#define NUM_LEDS 10
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// Declare global variables
CRGB leds[NUM_LEDS];
bool validSignal = false;
int pwmValue;
byte operatingMode;   // 0 = solid colors, 1 = patterns
byte patternNumber;

void setup() {
  // Initialize FastLED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // The LEDs I'm using are GRB so init'ing them this way makes the RGB numbers correspond correctly

  // Initialize PWM_PIN as an input to read PWM data
  pinMode(PWM_PIN, INPUT);

  // Initialize random number generator seed using analog noise
  randomSeed(analogRead(0));
  
  // Start with all LEDs off
  SolidColorRGB(0, 0, 0);

  // Stay in a loop until we see a valid PWM signal (950 - 2050) and flash a red LED while we wait
  while (!validSignal) {
    CheckValidSignal();
    FlashRGB(1, 100, 300, 100, 0, 0);
  }

  // Determine operating mode - if PWM signal < 1500 then solid colors, if PWM signal > 1500 then patterns
  if (pwmValue <= 1500) {
    operatingMode = 0;
    FlashRGB(1, 100, 300, 0, 100, 0); // Flash a green LED once to indicate solid color mode has been set
  }
  else {
    operatingMode = 1;
    FlashRGB(1, 100, 300, 0, 100, 0); // Flash a green LED twice to indicate pattern mode has been set
    FlashRGB(1, 100, 300, 0, 100, 0);
  }

}

void loop() {
  // Normal operation as long as we have a valid PWM signal
  while (validSignal) {

    // Solid color mode
    if (operatingMode == 0) {
      if (pwmValue < 1050) {
        SolidColorRGB(0, 0, 0);
      }
      else {
        int hue = map(pwmValue, 1050, 2000, 0, 215);
        SolidColorHSV(hue);
      }
      CheckValidSignal();
    }

    // Pattern mode
    else if (operatingMode == 1) {
      UpdatePattern();

      if (patternNumber == 1) {
        SolidColorRGB(0, 0, 0);
      }
      else if (patternNumber == 2) {
        Pattern2();
      }
      else if (patternNumber == 3) {
        Pattern3();
      }
      else if (patternNumber == 4) {
        Pattern4();
      }
      else if (patternNumber == 5) {
        Pattern5();
      }
      else if (patternNumber == 6) {
        Pattern6();
      }
      else if (patternNumber == 7) {
        Pattern7();
      }
      else if (patternNumber == 8) {
        Pattern8();
      }
      else if (patternNumber == 9) {
        Pattern9();
      }
      else if (patternNumber == 10) {
        Pattern10();
      }
    }
  }

  // Emergency operation in case a valid PWM signal is lost
  while (!validSignal) {
    FlashRGB(250, 500, 255, 0, 0);
    CheckValidSignal();
  }
}
