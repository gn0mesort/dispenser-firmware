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
 * Filters IR input data.
 * 
 * Analog voltage is read from the sensor and used to calculate distance.
 * 
 * @return True if the distance is within the range [DISTANCE_MIN, DISTANCE_MAX]
 */
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
 * When IR_FOUND_TARGET positive samples are recorded from the IR sensor this state transitions
 * into the active state.
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @param found The number of positive IR sensor samples. This value is shared between search and reset.
 * @return STATE_SEARCH if no transition is needed otherwise STATE_ACTIVE.
 */
int search(const unsigned long dt, int& found) {
  static auto acc = 0UL;
  
  set_led(0x003300UL);
  acc += dt;
  if (acc < IR_FRAMETIME)
  {
    Serial.println("Search");
    return STATE_SEARCH;
  }
  acc -= IR_FRAMETIME;
  found += ir_detect() ? 1 : -1;
  found = constrain(found, IR_FOUND_MIN, IR_FOUND_MAX);
  if (found >= IR_FOUND_TARGET)
  {
    Serial.println("Active");
    return STATE_ACTIVE;
  }
  Serial.println("Search");
  return STATE_SEARCH;
}

/**
 * Activate function
 * 
 * When MOTOR_TIMEOUT milliseconds have elapsed this state transitions to the
 * reset state.
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @return STATE_ACTIVE if no transition is needed otherwise STATE_RESET.
 */
int activate(const unsigned long dt) {
  static auto acc = 0UL;
  
  acc += dt;
  if (acc >= MOTOR_TIMEOUT)
  {
    digitalWrite(MOTOR, LOW);
    acc = 0;
    Serial.println("Reset");
    return STATE_RESET;  
  }
  set_led(0x000033UL);
  digitalWrite(MOTOR, HIGH);
  Serial.println("Active");
  return STATE_ACTIVE;
}

/**
 * Reset function
 * 
 * Works like the search state in reverse. Once the number of found samples reaches
 * IR_FOUND_MIN this state transistions back into the search state.
 * 
 * @param dt Delta time between the current tick and the last tick.
 * @param found The number of positive IR sensor samples. This value is shared between search and reset.
 * @return STATE_RESET if no transition is needed otherwise STATE_SEARCH.
 */
int reset(const unsigned long dt, int& found) {
  static auto acc = 0UL;
  
  set_led(0x330000UL);
  acc += dt;
  if (acc < IR_FRAMETIME)
  {
    Serial.println("Reset");
    return STATE_RESET;
  }
  acc -= IR_FRAMETIME;
  found += ir_detect() ? 1 : -1;
  found = constrain(found, IR_FOUND_MIN, IR_FOUND_MAX);
  if (found <= IR_FOUND_MIN)
  {
    Serial.println("Search");
    return STATE_SEARCH;
  }
  Serial.println("Reset");
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
}

/**
 * Firmware loop
 * 
 * Runs once per time unit.
 */
void loop() {
  static auto state = STATE_SEARCH;
  static auto found = 0;
  static auto last = 0UL;
  static auto dt = 0UL;
  
  switch (state) {
  case STATE_SEARCH:
    state = search(dt, found);
    break;
  case STATE_ACTIVE:
    state = activate(dt);
    break;
  case STATE_RESET:
    state = reset(dt, found);
    break;
  default:
    break;
  }
  
  dt = millis() - last;
  last = millis();
}
