// Using the FastLED library to control LEDs
#include<FastLED.h>


// Define constants - everything that may need to be changed to port this to a different setup should be here
#define MIN_TIME_BETWEEN_PPM_READS 250  // Minimum time between PPM signal reads in milliseconds

#define RC_INPUT_PIN 2
#define RC_INPUT_CHANNELS 8              // Pulling a PPM output from a Crossfire receiver in 8 channel mode
#define RC_CHANNELS_TO_MONITOR 6         // We will only need to monitor the first 6 channels

#define CHANNEL_THROTTLE 1   // The RC channel that has the motor throttle value
#define CHANNEL_MODE 4       // The RC channel that defines the operating mode
#define CHANNEL_PATTERN 5    // The RC channel that chooses a pattern in pattern mode
#define CHANNEL_ADJUST 6     // The RC channel that adjusts LED parameters in whatever mode is being displayed (color, speed, etc.)

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define TOP_LED_OUTPUT_PIN 3
#define TOP_LED_COUNT 25   // Last 3 LEDs are actually mounted on the endplate
#define BOTTOM_LED_OUTPUT_PIN 4
#define BOTTOM_LED_COUNT 32


// Global variables for reading / storing the PPM signal, operaing mode, and which pattern we are in
unsigned long int currentRead, lastRead, lastValidSignal;
int ppmValues[RC_INPUT_CHANNELS + 1];
byte operatingMode, patternNumber;


// Declare the objects that define the two LED arrays that'll be addressed
CRGB topLEDs[TOP_LED_COUNT];
CRGB bottomLEDs[BOTTOM_LED_COUNT];


void setup() {
  // Initialize PPM input pin
  pinMode(2, INPUT_PULLUP);

  // Initialize FastLED
  FastLED.addLeds<LED_TYPE, TOP_LED_OUTPUT_PIN, COLOR_ORDER>(topLEDs, TOP_LED_COUNT);
  FastLED.addLeds<LED_TYPE, BOTTOM_LED_OUTPUT_PIN, COLOR_ORDER>(bottomLEDs, BOTTOM_LED_COUNT);

  // Initialize random number generator seed using analog noise
  randomSeed(analogRead(0));

  // Start with all LEDs off
  fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
  fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
  FastLED.show();

  // Stay in a loop until we see a valid signal and flash a red LED while we wait
  while (!ValidSignal()) {
    topLEDs[0] = CRGB(255, 0, 0);
    bottomLEDs[0] = CRGB(255, 0, 0);
    FastLED.show();
    delay(100);
    topLEDs[0] = CRGB(0, 0, 0);
    bottomLEDs[0] = CRGB(0, 0, 0);
    FastLED.show();
    
    ReadSignal();
  }

  // If we made it this far we know we have a valid signal and we're ready to start normal operation. Set operating mode.
  SetOperatingMode();
}


void loop() {
  // Operating mode 0 - Lost signal, flash all LEDs red to aid recovery and conserve battery
  if (operatingMode == 0) {
    fill_solid(topLEDs, TOP_LED_COUNT, CRGB(255, 0, 0));
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(255, 0, 0));
    FastLED.show();
    delay(250);
    fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
    FastLED.show();
    delay(500);
  }

  // Operating mode 1 - All LEDs off
  if (operatingMode == 1) {
    fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
    FastLED.show();
  }

  // Operating mode 2 - LOS mode, top LEDs blue, bottom LEDs green, endplate LEDs red
  if (operatingMode == 2) {
    // Handle the fact that the last 3 LEDs in topLEDs are actually on the wing endplates
    for (int i = 0; i < TOP_LED_COUNT; i++) {
      if (i < TOP_LED_COUNT - 3) topLEDs[i] = CRGB(0, 0, 255);
      else topLEDs[i] = CRGB(255, 0, 0);
    }
    
    fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 255, 0));
    FastLED.show();
  }

  // Operating Mode 3 - Patterns
  if (operatingMode == 3) {
    SetPattern();
    if (patternNumber == 1) { Pattern1(); }
    else if (patternNumber == 2) { Pattern2(); }
    else if (patternNumber == 3) { Pattern3(); }
    else if (patternNumber == 4) { Pattern4(); }
    else if (patternNumber == 5) { Pattern5(); }
  }
  
  ReadSignal();
  SetOperatingMode();
}
