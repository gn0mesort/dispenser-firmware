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

bool ir_detect() {
  const auto volts = analogRead(IR_SENSOR) * VOLTAGE_SCALING;
  const auto distance = 13 * (1.0f / volts);
  if (distance <= DISTANCE_MAX && distance >= DISTANCE_MIN)
  {
    return true;
  }
  return false;
}


/**
 * Search function
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_SEARCH if no transition is needed otherwise STATE_ACTIVE.
 */
int search(const unsigned long dt, unsigned long& acc, int& found) {
  set_led(0x003300UL);
  acc += dt;
  if (acc < IR_FRAMETIME)
  {
    return STATE_SEARCH;
  }
  acc -= IR_FRAMETIME;
  found += ir_detect() ? 1 : -1;
  found = constrain(found, IR_FOUND_MIN, IR_FOUND_MAX);
  if (found >= IR_FOUND_TARGET)
  {
    return STATE_ACTIVE;
  }
  return STATE_SEARCH;
}

/**
 * Activate function
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_ACTIVE if no transition is needed otherwise STATE_RESET.
 */
int activate(const unsigned long dt, unsigned long& acc) {
  acc += dt;
  if (acc >= MOTOR_TIMEOUT)
  {
    digitalWrite(MOTOR, LOW);
    acc = 0;
    return STATE_RESET;  
  }
  set_led(0x000033UL);
  digitalWrite(MOTOR, HIGH);
  return STATE_ACTIVE;
}

/**
 * Reset function
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_RESET if no transition is needed otherwise STATE_SEARCH.
 */
int reset(const unsigned long dt, unsigned long& acc, int& found) {
  set_led(0x330000UL);
  acc += dt;
  if (acc < IR_FRAMETIME)
  {
    return STATE_RESET;
  }
  acc -= IR_FRAMETIME;
  found += ir_detect() ? 1 : -1;
  found = constrain(found, IR_FOUND_MIN, IR_FOUND_MAX);
  if (found <= IR_FOUND_MIN)
  {
    return STATE_SEARCH;
  }
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
  pinMode(MOTOR, OUTPUT);
  // TODO: implementation
}

/**
 * Firmware loop
 * 
 * Runs once per time unit.
 */
void loop() {
  auto state = STATE_SEARCH;
  unsigned long acc[STATE_COUNT];
  auto found = 0;
  auto last = 0UL;
  switch (state) {
  case STATE_SEARCH:
    state = search(millis() - last, acc[STATE_SEARCH], found);
    break;
  case STATE_ACTIVE:
    state = activate(millis() - last, acc[STATE_ACTIVE]);
    break;
  case STATE_RESET:
    state = reset(millis() - last, acc[STATE_RESET], found);
    break;
  default:
    break;
  }
  last = millis();
}
