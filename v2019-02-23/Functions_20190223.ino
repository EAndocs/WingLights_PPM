/*
   Function: SolidColorRGB
   Purpose:  Fill in all LEDs with a single RGB color
*/
void SolidColorRGB (byte redVal, byte greenVal, byte blueVal) {
  fill_solid(leds, NUM_LEDS, CRGB(redVal, greenVal, blueVal));
  FastLED.show();
}

/*
   Function: SolidColorRGB (overloaded)
   Purpose:  Clear all LEDs then fill in specified number of LEDs with a single RGB color
*/
void SolidColorRGB (byte numLEDs, byte redVal, byte greenVal, byte blueVal) {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  fill_solid(leds, numLEDs, CRGB(redVal, greenVal, blueVal));
  FastLED.show();
}

/*
   Function: SolidColorHSV
   Purpose:  Fill in all LEDs with a single HSV color at max saturation and brightness (value)
*/
void SolidColorHSV (byte hueVal) {
  fill_solid(leds, NUM_LEDS, CHSV(hueVal, 255, 255));
  FastLED.show();
}

/*
   Function: FlashRGB
   Purpose:  Make all LEDs flash a single RGB color for a specificed on and off duration in milliseconds
*/
void FlashRGB (int onDuration, int offDuration, byte redVal, byte greenVal, byte blueVal) {
  SolidColorRGB(redVal, greenVal, blueVal);
  FastLED.show();
  delay(onDuration);
  SolidColorRGB(0, 0, 0);
  delay(offDuration);
}

/*
   Function: FlashRGB (overloaded)
   Purpose:  Make specified number of LEDs flash a single RGB color for a specificed on and off duration in milliseconds
*/
void FlashRGB (byte numLEDs, int onDuration, int offDuration, byte redVal, byte greenVal, byte blueVal) {
  SolidColorRGB(0, 0, 0);
  SolidColorRGB(numLEDs, redVal, greenVal, blueVal);
  FastLED.show();
  delay(onDuration);
  SolidColorRGB(0, 0, 0);
  delay(offDuration);
}

/*
   Fuction: CheckValidSignal
   Purpose: Refresh pwmValue and check to see if we have a valid PWM signal. If we do
*/
void CheckValidSignal() {
  pwmValue = pulseIn(PWM_PIN, HIGH);
  if (pwmValue >= 950 && pwmValue <= 2050) {
    validSignal = true;
  }
  else {
    validSignal = false;
  }
}

byte UpdatePattern() {
  CheckValidSignal();
  patternNumber = ((pwmValue - 1000) * 10 / 1000) + 1;  // Choose pattern 1 through 10 based on PWM value

  if (patternNumber > 10) {  // Handle PWM values > 2000
    patternNumber = 10;
  }
  if (patternNumber < 1) {  // This shouldn't ever happen, even with PWM values < 1000
    patternNumber = 1;
  }
}
