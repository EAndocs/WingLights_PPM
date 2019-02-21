// Pattern 2 - Cycle all LEDs through the HSV colors
void Pattern2() {
  for (int i = 1; i <= 255; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(i, 255, 255);
    }
    FastLED.show();
    delay(20);

    UpdatePattern();
    if (patternNumber != 2) break;
  }
}
