#include<FastLED.h>

#define RC_INPUT_PIN 2

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define TOP_LED_OUTPUT_PIN 3
#define TOP_LED_COUNT 22

#define BOTTOM_LED_OUTPUT_PIN 4
#define BOTTOM_LED_COUNT 32

// Declare global variables
CRGB topLEDs[TOP_LED_COUNT];
CRGB bottomLEDs[BOTTOM_LED_COUNT];
bool validSignal = false;
byte operatingMode;  // 0 = solid colors, 1 = patterns
byte patternNumber;
int pwmValue;

void setup() {
  // Initialize FastLED
  FastLED.addLeds<LED_TYPE, TOP_LED_OUTPUT_PIN, COLOR_ORDER>(topLEDs, TOP_LED_COUNT);
  FastLED.addLeds<LED_TYPE, BOTTOM_LED_OUTPUT_PIN, COLOR_ORDER>(bottomLEDs, BOTTOM_LED_COUNT);

  // Initialize PWM_PIN as an input to read PWM data
  pinMode(RC_INPUT_PIN,INPUT);
  
  // Initialize random number generator seed using analog noise
  randomSeed(analogRead(0));

  // Start with all LEDs off
  fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
  fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
  FastLED.show();
  
  // Stay in a loop until we see a valid PWM signal (950 - 2050) and flash a red LED while we wait
  while (!validSignal) {
    topLEDs[0] = CRGB(255, 0, 0);
    bottomLEDs[0] = CRGB(255, 0, 0);
    FastLED.show();
    delay(100);
    topLEDs[0] = CRGB(0, 0, 0);
    bottomLEDs[0] = CRGB(0, 0, 0);
    FastLED.show();
    delay(500);

    CheckValidSignal();
  }

  // Determine operating mode - if PWM signal < 1500 then solid colors, if PWM signal > 1500 then patterns
  if (pwmValue <= 1500) {
    operatingMode = 0;

    // Flash a green LED once to indicate solid color mode
    topLEDs[0] = CRGB(0, 255, 0);
    bottomLEDs[0] = CRGB(0, 255, 0);
    FastLED.show();
    delay(200);
    topLEDs[0] = CRGB(0, 0, 0);
    bottomLEDs[0] = CRGB(0, 0, 0);
    FastLED.show();
    delay(200);
  }

  else {
    operatingMode = 1;

    // Flash a green LED twice to indicate pattern mode
    for (int i=0; i<2; i++) {
      topLEDs[0] = CRGB(0, 255, 0);
      bottomLEDs[0] = CRGB(0, 255, 0);
      FastLED.show();
      delay(200);
      topLEDs[0] = CRGB(0, 0, 0);
      bottomLEDs[0] = CRGB(0, 0, 0);
      FastLED.show();
      delay(200);
    }
  }
}

void loop() {
  if (operatingMode == 0) {
    CheckValidSignal();

    if (pwmValue < 1050) {
      topLEDs[0] = CRGB(0, 0, 0);
      bottomLEDs[0] = CRGB(0, 0, 0);
      FastLED.show();
    }
    else {
      int hue = map(pwmValue, 1050, 2000, 0, 215);
      fill_solid(topLEDs, TOP_LED_COUNT, CHSV(hue, 255, 255));
      fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CHSV(hue, 255, 255));
      FastLED.show();
    }
  }
  
  else if (operatingMode == 1) {
    UpdatePattern();
    
    if (patternNumber == 1) {
      Pattern1();
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
