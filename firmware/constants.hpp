/**
 * Firmware constants
 * 
 * Non-user configuration constants should be included here.
 */
#ifndef FIRMWARE_CONSTANTS_HPP
#define FIRMWARE_CONSTANTS_HPP

#define VOLTAGE_SCALING (5.0f / 1023.0f)

#define STATE_SEARCH 0
#define STATE_ACTIVE 1
#define  STATE_RESET 2

#define     IR_FOUND_MIN 0
#define    IR_FOUND_MAX 15
#define IR_FOUND_TARGET 10

#define IR_FRAMETIME 16

#endif
