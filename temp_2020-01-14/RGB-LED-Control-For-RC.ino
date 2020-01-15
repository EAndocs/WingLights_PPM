#include<FastLED.h>

#define RC_INPUT_PIN 2

#define TOP_LED_OUTPUT_PIN 12
#define TOP_LED_COUNT 22

#define BOTTOM_LED_OUTPUT_PIN 4
#define BOTTOM_LED_COUNT 32

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// Declare global variables

CRGB topLEDs[TOP_LED_COUNT];
CRGB bottomLEDs[BOTTOM_LED_COUNT];
bool validSignal = false;
int pwmValue;
byte patternNumber;

void setup() {
  Serial.begin(9600);

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

    pwmValue = pulseIn(RC_INPUT_PIN, HIGH);
    if (pwmValue >= 950 && pwmValue <= 2050) {
      validSignal = true;
    }
    else {
      validSignal = false;
    }
  }

    // If we made it this far we have a valid PWM signal - flash a green LED to indicate that we're ready to go
    topLEDs[0] = CRGB(0, 255, 0);
    bottomLEDs[0] = CRGB(0, 255, 0);
    FastLED.show();
    delay(200);
    topLEDs[0] = CRGB(0, 0, 0);
    bottomLEDs[0] = CRGB(0, 0, 0);
    FastLED.show();
}

void loop() {
  Serial.println(pwmValue);
 }
