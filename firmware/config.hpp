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
#define IR_SENSOR A0

/**
 * Motor connection configuration
 */
#define MOTOR 10

/**
 * RGB LED red connection configuration
 */
#define RGB_RED 11

/**
 * RGB LED green connection configuration
 */
#define RGB_GREEN 6

/**
 * RGB LED blue connection configuration
 */
#define RGB_BLUE 5

/**
 * The minimum IR detection distance in centimeters.
 */
#define DISTANCE_MIN  4

/**
 * The maximum IR detection distance in centimeters.
 */
#define DISTANCE_MAX 20

#define MOTOR_TIMEOUT 100

#endif
