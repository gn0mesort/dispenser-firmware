/**
 * Main program file
 */
#include "constants.hpp"
#include "config.hpp"

/**
 * Set the color of the status LED to the specified 24-bit color.
 * 
 * Actual display color will depend on LED properties.
 * 
 * @param color A 32-bit unsigned integer containing color data in the lower 24 bits.
 */
void set_led(const unsigned long color) {
  analogWrite(RGB_RED, (color & 0xff0000UL) >> 16);
  analogWrite(RGB_GREEN, (color & 0x00ff00UL) >> 8);
  analogWrite(RGB_BLUE, color & 0x0000ffUL);
}

/**
 * Search function
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_SEARCH if no transition is needed otherwise STATE_ACTIVE.
 */
int search(const unsigned long dt) {
  // TODO: implementation
  return STATE_SEARCH;
}

/**
 * Activate function
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_ACTIVE if no transition is needed otherwise STATE_RESET.
 */
int activate(const unsigned long dt) {
  // TODO: implementation
  return STATE_ACTIVE;
}

/**
 * Reset function
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_RESET if no transition is needed otherwise STATE_SEARCH.
 */
int reset(const unsigned long dt) {
  // TODO: implementation
  return STATE_RESET;
}

/**
 * Setup firmware
 * 
 * Runs only once at board power on.
 */
void setup() {
  Serial.begin(9600);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  set_led(0UL);
  // TODO: implementation
}

/**
 * Firmware loop
 * 
 * Runs once per time unit.
 */
void loop() {
  static int state = STATE_SEARCH;
  static unsigned long last = 0;
  switch (state) {
  case STATE_SEARCH:
    state = search(millis() - last);
    break;
  case STATE_ACTIVE:
    state = activate(millis() - last);
    break;
  case STATE_RESET:
    state = reset(millis() - last);
    break;
  default:
    break;
  }
  last = millis();
}
