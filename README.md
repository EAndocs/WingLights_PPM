# WingLights_PPM
An Arduino-based RGB LED controller, intended for use on a radio control airplane. Uses the FastLED library - https://github.com/FastLED/FastLED

### Hardware
Tested on an Arduino Nano, TBS Crossfire RC receiver, and WS2812B individually addressable RGB LEDs.

### Input
Takes a PPM signal as input. Three channels are used to control control the sketch’s behavior:
* Operating mode selection - Allows LEDs to be turned on / off, used in a line-of-sight mode that is optimized for maintaining orientation, or pattern mode which allows the selection of different patterns / animations.
* Pattern selection - Choses a pattern / animation when in Pattern Mode
* Adjustment - Varies by operating mode / pattern. Adjusts colors, speed of animations, etc.

### Output
Outputs to two LED strips. This allows for different colors to be displayed on the top and bottom of an airplane without wiring a very long LED strip that could be affected by power sag.
