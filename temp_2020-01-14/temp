#include<FastLED.h>

#define RC_INPUT_PIN 2

#define TOP_LED_OUTPUT_PIN 12
#define TOP_LED_COUNT 22

#define BOTTOM_LED_OUTPUT_PIN 4
#define BOTTOM_LED_COUNT 32

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// Declare global variables
int pwmValue;
CRGB topLEDs[TOP_LED_COUNT];
CRGB bottomLEDs[BOTTOM_LED_COUNT];

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<LED_TYPE, TOP_LED_OUTPUT_PIN, COLOR_ORDER>(topLEDs, TOP_LED_COUNT);
  FastLED.addLeds<LED_TYPE, BOTTOM_LED_OUTPUT_PIN, COLOR_ORDER>(bottomLEDs, BOTTOM_LED_COUNT);
  
  pinMode(RC_INPUT_PIN,INPUT);

  

}

void loop() {
  pwmValue = pulseIn(RC_INPUT_PIN, HIGH);
  Serial.println(pwmValue);

  if (pwmValue >= 1500) {
    topLEDs[0] = CRGB(0, 0, 0);
    topLEDs[1] = CRGB(0, 0, 255);
    FastLED.show();
  }
  
  if (pwmValue <= 1500) {
    topLEDs[0] = CRGB(0, 0, 255);
    topLEDs[1] = CRGB(0, 0, 0);
    FastLED.show();
  }
  
 }
