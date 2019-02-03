#include <FastLED.h>   // Library to control LEDs

// Define constants
#define LED_PIN 2
#define PWM_PIN 3
#define NUM_LEDS 3  // Currently testing with a short LED strip

// Declare global variables
int pwm_value;
int disp_mode;
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);  // Init like this (GRB) to make RGB numbers correspond correctly to RGB
  pinMode(PWM_PIN, INPUT);
  // Serial.begin(9600);
  DisplayMode1();  // Start with Display Mode 1 - all LEDs off
}

void loop() {
  UpdateDisplayMode();
  // Serial.println(disp_mode);

  if (disp_mode == 1) {
    DisplayMode1();
  }
  else if (disp_mode == 2) {
    DisplayMode2();
  }
  else if (disp_mode == 3) {
    DisplayMode3();
  }
  else if (disp_mode == 4) {
    DisplayMode4();
  }
  else if (disp_mode == 5) {
    DisplayMode5();
  }
  else if (disp_mode == 6) {
    DisplayMode6();
  }
  else if (disp_mode == 7) {
    DisplayMode7();
  }
  else if (disp_mode == 8) {
    DisplayMode8();
  }
  else if (disp_mode == 9) {
    DisplayMode9();
  }
  else if (disp_mode == 10) {
    DisplayMode10();
  }
}

// Function to get PWM value (1K - 2K microseconds) and map it to a display mode (1 - 10) stored in global variable disp_mode
void UpdateDisplayMode() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  disp_mode = ((pwm_value - 1000) * 10 / 1000) + 1;  // Set display mode 1 through 10 based on PWM value
  
  if (disp_mode > 10) {  // Handle PWM values > 2000
    disp_mode = 10;
  }
  if (disp_mode < 1) {  // This shouldn't ever happen, even with PWM values < 1000
    disp_mode = 1;
  }
}

// Display Mode 1 - All LEDs off
void DisplayMode1() {
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

// Display Mode 2 - Cycle all LEDs through the HSV rainbow
void DisplayMode2() {
  for (int i = 1; i <= 255; i++){
    for (int j = 0; j < NUM_LEDS; j++){
      leds[j] = CHSV(i,255,255);
    }
    FastLED.show();

    UpdateDisplayMode();
    if (disp_mode != 2) break;
    delay(20);
  }
}

// Display Mode 3
void DisplayMode3() {
  DisplayMode1();  // Placeholder
}

// Display Mode 4
void DisplayMode4() {
  DisplayMode1();  // Placeholder
}

// Display Mode 5
void DisplayMode5() {
  DisplayMode1();  // Placeholder
}

// Display Mode 6
void DisplayMode6() {
  DisplayMode1();  // Placeholder
}

// Display Mode 7
void DisplayMode7() {
  DisplayMode1();  // Placeholder
}

// Display Mode 8
void DisplayMode8() {
  DisplayMode1();  // Placeholder
}

// Display Mode 9
void DisplayMode9() {
  DisplayMode1();  // Placeholder
}

// Display Mode 10
void DisplayMode10() {
  DisplayMode1();  // Placeholder
}
