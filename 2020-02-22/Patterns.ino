// Pattern 1 - Set all LEDs to a solid color
void Pattern1() {
  int hue = map(ppmValues[CHANNEL_ADJUST], 0, 1000, 0, 215);
  fill_solid(topLEDs, TOP_LED_COUNT, CHSV(hue, 255, 255));
  fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CHSV(hue, 255, 255));
  FastLED.show();
}

// Pattern 2 - Cycle all LEDs through all HSV colors
void Pattern2() {
  for (int i = 0; i <= 255; i++) {
    for (int j = 0; j < TOP_LED_COUNT; j++) {
      topLEDs[j] = CHSV(i, 255, 255);
    }
    for (int j = 0; j < BOTTOM_LED_COUNT; j++) {
      bottomLEDs[j] = CHSV(i, 255, 255);
    }
    FastLED.show();

    if (ppmValues[CHANNEL_ADJUST] > 0) {
      int waitTime = map(ppmValues[CHANNEL_ADJUST], 0, 1000, 0, 20);
      delay(waitTime);
    }
    
    ReadSignal();
    SetOperatingMode();
    SetPattern();

    if (operatingMode != 3 || patternNumber != 2) break;
  }
}

// Pattern 3 - Static Rainbow
void Pattern3() {
  // Handle the fact that the last 3 LEDs in topLEDs are actually on the wing endplates
  for (int i = 0; i < TOP_LED_COUNT; i++) {
    if (i < TOP_LED_COUNT - 3) topLEDs[i] = CHSV((192 / (TOP_LED_COUNT - 4)) * i, 255, 255);
    else topLEDs[i] = CRGB(0,0,0);
  }

  for (int i = 0; i < BOTTOM_LED_COUNT; i++) {
    bottomLEDs[i] = CHSV((192 / (BOTTOM_LED_COUNT - 1)) * i, 255, 255);
  }
  FastLED.show();
}

// Pattern 4 - Scrolling Rainbow
void Pattern4() {
  unsigned long topPreviousMillis = 0;
  unsigned long bottomPreviousMillis = 0;
  unsigned long topStepCounter = 0;
  unsigned long bottomStepCounter = 0;
  int totalDuration = 1000;  // Define how long it should take to finish the pattern once, in miliseconds
  int topLoopInterval = totalDuration / TOP_LED_COUNT;
  int bottomLoopInterval = totalDuration / BOTTOM_LED_COUNT;

  while (operatingMode == 3 && patternNumber == 4) {
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

    if (ppmValues[CHANNEL_ADJUST] > 0) {
      int waitTime = map(ppmValues[CHANNEL_ADJUST], 0, 1000, 0, 100);
      delay(waitTime);
    }
    
    ReadSignal();
    SetOperatingMode();
    SetPattern();
  }
}

// Pattern 5 - Dazzling flashing LEDs
void Pattern5() {
  // Start with all LEDs off
  fill_solid(topLEDs, TOP_LED_COUNT, CRGB(0, 0, 0));
  fill_solid(bottomLEDs, BOTTOM_LED_COUNT, CRGB(0, 0, 0));
  FastLED.show();
  
  while (operatingMode == 3 && patternNumber == 5) {
    for (int i = 0; i < TOP_LED_COUNT; i++) {
      // Determine hue
      int hue = random(0, 256);

      // Determine if LED will be on or off - 25% chance of being off
      int rnd = random(0,100);
      int value = 255;
      if (rnd < 25) value = 0;
      
      topLEDs[i] = CHSV(hue, 255, value);
    }

    for (int i = 0; i < BOTTOM_LED_COUNT; i++) {
      // Determine hue
      int hue = random(0, 256);

      // Determine if LED will be on or off - 25% chance of being off
      int rnd = random(0,100);
      int value = 255;
      if (rnd < 25) value = 0;
      bottomLEDs[i] = CHSV(hue, 255, value);
    }

    FastLED.show();
    
    int waitTime = map(ppmValues[CHANNEL_ADJUST], 0, 1000, 20, 60);
    delay(waitTime);

    ReadSignal();
    SetOperatingMode();
    SetPattern();
  }
}
