// Pattern 2 - Cycle all LEDs through the HSV colors
void Pattern2() {
  for (int i = 0; i <= 255; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(i, 255, 255);
    }
    FastLED.show();
    delay(5);

    UpdatePattern();
    if (patternNumber != 2) break;
  }
}

// Pattern 3 - Static rainbow that takes up the whole LED strip
void Pattern3() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((192 / (NUM_LEDS - 1)) * i, 255, 255);
  }
  FastLED.show();
}

// Pattern 4 - Scrolling rainbow, like Pattern 4 but moving
void Pattern4() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      int h = (i + j) % NUM_LEDS;
      leds[h] = CHSV((255 / (NUM_LEDS - 1)) * j, 255, 255);
    }
    FastLED.show();
    delay(80);

    UpdatePattern();
    if (patternNumber != 4) break;
  }
}

// Pattern 5 - Fade a randomly selected color in and out
void Pattern5() {
  // Chose a random color
  int hue = random(0, 255);

  // Loop once to get brighter
  for (int i = 0; i < 256; i = i + 2) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(hue, 255, 255);
    }
    FastLED.setBrightness(i);
    FastLED.show();

    UpdatePattern();
    if (patternNumber != 5) break;
  }

  // Loop again to get dimmer, but only if we're still in Pattern 5
  if (patternNumber == 5) {
    for (int i = 255; i > 0; i = i - 2) {
      for (int j = 0; j < NUM_LEDS; j++) {
        leds[j] = CHSV(hue, 255, 255);
      }
      FastLED.setBrightness(i);
      FastLED.show();

      UpdatePattern();
      if (patternNumber != 5) break;
    }
  }

  // Return to full brightness before exiting
  FastLED.setBrightness(255);
}

void Pattern6() {
  SolidColorRGB(0, 0, 0);  // Placeholder
}

void Pattern7() {
  SolidColorRGB(0, 0, 0);  // Placeholder
}

void Pattern8() {
  SolidColorRGB(0, 0, 0);  // Placeholder
}

void Pattern9() {
  SolidColorRGB(0, 0, 0);  // Placeholder
}

void Pattern10() {
  SolidColorRGB(0, 0, 0);  // Placeholder
}
