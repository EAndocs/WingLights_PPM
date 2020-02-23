/*
 * This function reads the PPM signal and updates the global variable ppmValues with the values for the channels that we care about.
 * After loading ppmValues this function also updates the global variable lastRead which is used to control how often this function
 * runs and also to determine if we have a valid singal.
 * 
 * This function should only run after a certain ammount of time (defined by MIN_TIME_BETWEEN_PPM_READS) has passed since the last read
 * because it takes so long to run. This makes sure that we don't spend all of our time reading PPM values and don't leave any
 * time for LED updates. It would be much more elegant to do this with interrupts vs. waiting for a complete PPM frame each time we want
 * an update, but I haven't been able to figure out how to do that with FastLED because of the way it enables / disables interrupts.
 * See https://github.com/FastLED/FastLED/wiki/Interrupt-problems for more info.
 */
void ReadSignal() {
  currentRead = millis();

  // Only run if enough time has passed since the last read
  if (currentRead - lastRead >= MIN_TIME_BETWEEN_PPM_READS) {
    int values[RC_INPUT_CHANNELS + 1], startingPos;
    for (int i = 0; i < RC_INPUT_CHANNELS + 1; i++) {
      values[i] = pulseIn(RC_INPUT_PIN,HIGH);
      if (values[i] == 0) return;   // Exit funciton if singal is invalid      
      if (values[i] > 3000) startingPos = i;  // With all channels maxed out the space between frames was ~ 3800us
    }

    // Copy values to ppmValues
    for (int i = 0; i < RC_CHANNELS_TO_MONITOR + 1; i++) {
      ppmValues[i] = values[(i + startingPos) % (RC_INPUT_CHANNELS + 1)] - 587;  // My captured values were offset by +587us
      
      // Ensure all values fall between 0 and 1000
      if (ppmValues[i] > 1000) ppmValues[i] = 1000;
      if (ppmValues[i] < 0) ppmValues[i] = 0;
    }
    
    lastRead = currentRead;
  }
}


bool ValidSignal() {
  if (millis() - lastRead > 3000) return false;
  else return true;
}


void SetOperatingMode() {
  if (!ValidSignal()) operatingMode = 0;                                                         // Mode 0 - Lost signal
  else if (ppmValues[CHANNEL_MODE] <= 333) operatingMode = 1;                                    // Mode 1 - Off     
  else if (ppmValues[CHANNEL_MODE] > 333 && ppmValues[CHANNEL_MODE] < 666) operatingMode = 2;    // Mode 2 - LOS
  else if (ppmValues[CHANNEL_MODE] >= 666) operatingMode = 3;                                    // Mode 3 - Patterns       
}


void SetPattern() {
  patternNumber = (ppmValues[CHANNEL_PATTERN] / 200) + 1;
  if (patternNumber == 6) patternNumber = 5;  // Handle values outside of the expected range
}
