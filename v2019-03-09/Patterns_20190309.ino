// Pattern 9 - Cycle all LEDs through the HSV colors
void Pattern9() {
  for (int i = 0; i <= 255; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(i, 255, 255);
    }
    FastLED.show();
    delay(5);

    UpdatePattern();
    if (patternNumber != 9) break;
  }
}

// Pattern 8 - Three colors static (first third red, second third green, last third blue)
void Pattern8() {
  int oneThird = NUM_LEDS / 3;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < oneThird) leds[i] = CRGB(255, 0, 0);
    if (i >= oneThird) leds[i] = CRGB(0, 255, 0);
    if (i >= oneThird * 2) leds[i] = CRGB(0, 0, 255);
    if (i >= oneThird * 3) leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

// Pattern 7 - Three colors scrolling
void Pattern7() {
  int oneThird = NUM_LEDS / 3;
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      int h = (i + j) % NUM_LEDS;
      if (j < oneThird) leds[h] = CRGB(255, 0, 0);
      if (j >= oneThird) leds[h] = CRGB(0, 255, 0);
      if (j >= oneThird * 2) leds[h] = CRGB(0, 0, 255);
      if (j >= oneThird * 3) leds[h] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(80);

    UpdatePattern();
    if (patternNumber != 7) break;
  }
}

// Pattern 6 - Static rainbow that takes up the whole LED strip
void Pattern6() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((192 / (NUM_LEDS - 1)) * i, 255, 255);
  }
  FastLED.show();
}

// Pattern 5 - Scrolling rainbow, like Pattern 6 but moving
void Pattern5() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      int h = (i + j) % NUM_LEDS;
      leds[h] = CHSV((192 / (NUM_LEDS - 1)) * j, 255, 255);
    }
    FastLED.show();
    delay(80);

    UpdatePattern();
    if (patternNumber != 5) break;
  }
}

// Pattern 4 - Fade a randomly selected color in and out
void Pattern4() {
  // Chose a random color
  int hue = random(0, 256);

  // Loop once to get brighter
  for (int i = 0; i < 256; i = i + 2) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(hue, 255, 255);
    }
    FastLED.setBrightness(i);
    FastLED.show();

    UpdatePattern();
    if (patternNumber != 4) break;
  }

  // Loop again to get dimmer, but only if we're still in Pattern 6
  if (patternNumber == 4) {
    for (int i = 255; i > 0; i = i - 2) {
      for (int j = 0; j < NUM_LEDS; j++) {
        leds[j] = CHSV(hue, 255, 255);
      }
      FastLED.setBrightness(i);
      FastLED.show();

      UpdatePattern();
      if (patternNumber != 4) break;
    }
  }

  // Return to full brightness before exiting
  FastLED.setBrightness(255);
}

//Pattern 3 - Animated fill with a random color for each full pass of the LED strip
void Pattern3() {
  SolidColorRGB(0, 0, 0);
  FastLED.show();
  while (patternNumber == 3) {
    int hue = random(0, 256);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue, 255, 255);
      FastLED.show();
      delay(80);

      UpdatePattern();
      if (patternNumber != 3) break;
    }
  }
}

// Pattern 2 - Animated fill with a random color for each pixel of the LED strip
void Pattern2() {
  SolidColorRGB(0, 0, 0);
  FastLED.show();
  while (patternNumber == 2) {
    for (int i = 0; i < NUM_LEDS; i++) {
      int hue = random(0, 256);
      leds[i] = CHSV(hue, 255, 255);
      FastLED.show();
      delay(80);

      UpdatePattern();
      if (patternNumber != 2) break;
    }
  }
}

// Pattern 1 - Randomly assign a color to a random LED after a random interval between 20 and 150ms
void Pattern1() {
  // Start with all LEDs off
  SolidColorRGB(0, 0, 0);
  while (patternNumber == 1) {
    int led = random(0, NUM_LEDS);
    int hue = random(0, 256);
    int interval = random(20, 150);
    leds[led] = CHSV(hue, 255, 255);
    FastLED.show();
    delay(interval);
    UpdatePattern();
  }
}

// Pattern 10 - All LEDs off
void Pattern10() {
  SolidColorRGB(0, 0, 0);
}
