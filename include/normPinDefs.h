/**
 * @file pinDefs.h
 * @brief Definition for the pins used on the NORM Motor Control Board
 * (https://github.com/HBoyd255/norm-motor-control-board)
 *
 * @author Harry Boyd - https://github.com/HBoyd255
 * @date 2024-12-06
 * @copyright Copyright (c) 2024
 */

#ifndef NORM_PIN_DEFS_H
#define NORM_PIN_DEFS_H

// Motors

// Front Left (Driver 1)(Motor 1)
#define FRONT_LEFT_MOTOR_DIRECTION_PIN A0
#define FRONT_LEFT_MOTOR_SPEED_PIN D2
#define FRONT_LEFT_MOTOR_ENCODER_A_PIN D6
#define FRONT_LEFT_MOTOR_ENCODER_B_PIN D7
#define FRONT_LEFT_MOTOR_ROTATION_INVERTED false

// Front Right (Driver 1)(Motor 2)
#define FRONT_RIGHT_MOTOR_DIRECTION_PIN A1
#define FRONT_RIGHT_MOTOR_SPEED_PIN D3
#define FRONT_RIGHT_MOTOR_ENCODER_A_PIN D8
#define FRONT_RIGHT_MOTOR_ENCODER_B_PIN D9
#define FRONT_RIGHT_MOTOR_ROTATION_INVERTED true

// Back Left (Driver 2)(Motor 1)
#define BACK_LEFT_MOTOR_DIRECTION_PIN A2
#define BACK_LEFT_MOTOR_SPEED_PIN D4
#define BACK_LEFT_MOTOR_ENCODER_A_PIN D10
#define BACK_LEFT_MOTOR_ENCODER_B_PIN D11
#define BACK_LEFT_MOTOR_ROTATION_INVERTED false

// Back Right (Driver 2)(Motor 2)
#define BACK_RIGHT_MOTOR_DIRECTION_PIN A3
#define BACK_RIGHT_MOTOR_SPEED_PIN D5
#define BACK_RIGHT_MOTOR_ENCODER_A_PIN A6
#define BACK_RIGHT_MOTOR_ENCODER_B_PIN A7
#define BACK_RIGHT_MOTOR_ROTATION_INVERTED true

#endif  // NORM_PIN_DEFS_H