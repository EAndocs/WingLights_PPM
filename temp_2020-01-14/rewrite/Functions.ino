void CheckValidSignal() {
  pwmValue = pulseIn(RC_INPUT_PIN, HIGH);
  if (pwmValue >= 950 && pwmValue <= 2050) {
    validSignal = true;
  }
  else {
    validSignal = false;
  }
}

void UpdatePattern() {
  CheckValidSignal();

  patternNumber = ((pwmValue - 1000) * 10 / 1000) + 1;  // Choose pattern 1 through 10 based on PWM value

  if (patternNumber > 10) {  // Handle PWM values > 2000
    patternNumber = 10;
  }
  if (patternNumber < 1) {  // This shouldn't ever happen, even with PWM values < 1000
    patternNumber = 1;
  }
}
