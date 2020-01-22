// Pattern 1 - All LEDs off
void Pattern1() {
  fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
  fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
  FastLED.show();
}

//Pattern 2 - LOS Mode - Top LEDs blue and bottom LEDs green
void Pattern2() {
  fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 255));
  fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 255, 0));
  FastLED.show();
}

// Pattern 3 - Cycle all LEDs through all HSV colors
void Pattern3() {
  for (int i = 0; i <= 255; i++) {
    for (int j = 0; j < TOP_LED_COUNT; j++) {
      topLEDs[j] = CHSV(i, 255, 255);
    }
    for (int j = 0; j < BOTTOM_LED_COUNT; j++) {
      bottomLEDs[j] = CHSV(i, 255, 255);
    }
    FastLED.show();
    delay(5);

    UpdatePattern();
    if (patternNumber != 3) break;
  }
}

// Pattern 4 - Static rainbow
void Pattern4() {
  for (int i = 0; i < TOP_LED_COUNT; i++) {
    topLEDs[i] = CHSV((192 / (TOP_LED_COUNT - 1)) * i, 255, 255);
  }
  for (int i = 0; i < BOTTOM_LED_COUNT; i++) {
    bottomLEDs[i] = CHSV((192 / (BOTTOM_LED_COUNT - 1)) * i, 255, 255);
  }
  FastLED.show();
}

void Pattern5() {
  
}

void Pattern6() {
  
}

void Pattern7() {
  
}

void Pattern8() {
  
}

void Pattern9() {
  
}

void Pattern10() {
  
}
