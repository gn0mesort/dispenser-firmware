/**
 * Firmware configuration
 * 
 * User configuration constants for dispenser
 * firmware settings.
 */
#ifndef FIRMWARE_CONFIG_HPP
#define FIRMWARE_CONFIG_HPP

/**
 * IR sensor connection configuration
 */
 const int IR_SENSOR = A0;

/**
 * Motor connection configuration
 */
 const int MOTOR = 10;

/**
 * RGB LED red connection configuration
 */
 const int RGB_RED = 11;

/**
 * RGB LED green connection configuration
 */
 const int RGB_GREEN = 6;

/**
 * RGB LED blue connection configuration
 */
 const int RGB_BLUE = 5;

/**
 * The minimum IR detection distance in centimeters.
 */
 const int DISTANCE_MIN = 4;

/**
 * The maximum IR detection distance in centimeters.
 */
 const int DISTANCE_MAX = 20;

/**
 * The duration in milliseconds that the motor should run for.
 */
const unsigned long MOTOR_TIMEOUT = 300;

#endif
