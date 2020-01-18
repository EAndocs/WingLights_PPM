#include<FastLED.h>

#define RC_INPUT_PIN 2

#define TOP_LED_OUTPUT_PIN 3
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

    // If we made it this far we have a valid PWM signal - flash a green LED 3x to indicate that we're ready to go
    for (int i=0; i<3; i++) {
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

void loop() {
  pwmValue = pulseIn(RC_INPUT_PIN, HIGH);
  Serial.println(pwmValue);

  patternNumber = ((pwmValue - 1000) * 10 / 1000) + 1;  // Choose pattern 1 through 10 based on PWM value
  if (patternNumber > 10) {  // Handle PWM values > 2000
    patternNumber = 10;
  }
  if (patternNumber < 1) {  // This shouldn't ever happen, even with PWM values < 1000
    patternNumber = 1;
  }
  
  // Pattern 1 - All LEDs off
  if (patternNumber == 1) {
    fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
    FastLED.show();
  }

  // Pattern 2 - LOS Mode - Top LEDs blue and bottom LEDs green
  if (patternNumber == 2) {
    fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 255));
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 255, 0));
    FastLED.show();
  }

  // Pattern 3 - Cycle all LEDs through all HSV colors
  if (patternNumber == 3) {
    for (int i = 0; i <= 255; i++) {
      for (int j = 0; j < TOP_LED_COUNT; j++) {
        topLEDs[j] = CHSV(i, 255, 255);
      }
      for (int j = 0; j < BOTTOM_LED_COUNT; j++) {
        bottomLEDs[j] = CHSV(i, 255, 255);
      }
      FastLED.show();
      delay(5);
    }
  }

  // Pattern 4 - Static rainbow
  if (patternNumber == 4) {
    for (int i = 0; i < TOP_LED_COUNT; i++) {
      topLEDs[i] = CHSV((192 / (TOP_LED_COUNT - 1)) * i, 255, 255);
    }
    for (int i = 0; i < BOTTOM_LED_COUNT; i++) {
      bottomLEDs[i] = CHSV((192 / (BOTTOM_LED_COUNT - 1)) * i, 255, 255);
    }
    FastLED.show();
  }

  // Pattern 5 - Scrolling rainbow
  
  unsigned long topPreviousMillis = 0;
  unsigned long bottomPreviousMillis = 0;
  unsigned long topStepCounter = 0;
  unsigned long bottomStepCounter = 0;
  int totalDuration = 2000;  // Define how long it should take to finish the pattern once, in miliseconds
  int topLoopInterval = totalDuration / TOP_LED_COUNT;  // Calculate how long each iteration should take
  int bottomLoopInterval = totalDuration / BOTTOM_LED_COUNT;  // Calculate how long each iteration should take

  while (patternNumber == 5) {
    unsigned long currentMillis = millis();
    
    if (currentMillis - topPreviousMillis >= topLoopInterval) {
      for (int i = 0; i < TOP_LED_COUNT; i++) {
        topLEDs[(i + topStepCounter) % TOP_LED_COUNT] = CHSV((255 / (TOP_LED_COUNT - 1)) * i, 255, 255);
      }
      FastLED.show();
      topStepCounter++;
      topPreviousMillis = currentMillis;
    } 

    if (currentMillis - bottomPreviousMillis >= bottomLoopInterval) {
      for (int i = 0; i < BOTTOM_LED_COUNT; i++) {
        bottomLEDs[(i + bottomStepCounter) % BOTTOM_LED_COUNT] = CHSV((255 / (BOTTOM_LED_COUNT - 1)) * i, 255, 255);
      }
      FastLED.show();
      bottomStepCounter++;
      bottomPreviousMillis = currentMillis;
    } 
  }

  // Pattern 6 -

  // Pattern 7 -

  // Pattern 8 -

  // Pattern 9 -
  
  // Pattern 10 - All LED on white
  if (patternNumber == 10) {
    fill_solid(topLEDs, TOP_LED_COUNT, CRGB(255, 255, 255));
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(255, 255, 255));
    FastLED.show();
  }
}
