/**
 * Firmware constants
 * 
 * Non-user configuration constants should be included here.
 */
#ifndef FIRMWARE_CONSTANTS_HPP
#define FIRMWARE_CONSTANTS_HPP

/**
 * Scaling constant that is used in calculating voltage from analog input.
 * Found on arduino.cc
 */
const float VOLTAGE_SCALING = 5.0f / 1023.0f;

/**
 * State enumeration constants.
 */
enum {
  STATE_SEARCH = 0,
  STATE_ACTIVE = 1,
  STATE_RESET = 2
};

/**
 * The minimum number of IR samples possible.
 */
const int    IR_FOUND_MIN =  0;

/**
 * The maximum number of IR samples to collect.
 */
const int    IR_FOUND_MAX = 15;

/**
 * The target number of IR samples to activate the motor.
 */
const int IR_FOUND_TARGET = 10;

/**
 * The time in milliseconds to wait inbetween IR samples.
 */
const unsigned long IR_FRAMETIME = 16;

#endif
