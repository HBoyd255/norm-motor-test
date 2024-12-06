/**
 * @file main.cpp
 * @brief The main file and entry point of the project.
 *
 * @author Harry Boyd - https://github.com/HBoyd255
 * @date 30/10/2024
 * @copyright Copyright (c) 2024
 */

//  ██████╗ ██████╗  ██████╗      ██╗███████╗ ██████╗████████╗
//  ██╔══██╗██╔══██╗██╔═══██╗     ██║██╔════╝██╔════╝╚══██╔══╝
//  ██████╔╝██████╔╝██║   ██║     ██║█████╗  ██║        ██║
//  ██╔═══╝ ██╔══██╗██║   ██║██   ██║██╔══╝  ██║        ██║
//  ██║     ██║  ██║╚██████╔╝╚█████╔╝███████╗╚██████╗   ██║
//  ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚════╝ ╚══════╝ ╚═════╝   ╚═╝
//
//  ███╗   ██╗    ██████╗    ██████╗    ███╗   ███╗
//  ████╗  ██║   ██╔═══██╗   ██╔══██╗   ████╗ ████║
//  ██╔██╗ ██║   ██║   ██║   ██████╔╝   ██╔████╔██║
//  ██║╚██╗██║   ██║   ██║   ██╔══██╗   ██║╚██╔╝██║
//  ██║ ╚████║██╗╚██████╔╝██╗██║  ██║██╗██║ ╚═╝ ██║██╗
//  ╚═╝  ╚═══╝╚═╝ ╚═════╝ ╚═╝╚═╝  ╚═╝╚═╝╚═╝     ╚═╝╚═╝

// (Neat Omnidirectional Robotic Module)

// Ascii text generated at https://patorjk.com/software/taag/
// Font used - ANSI Shadow

#include <Arduino.h>

#define SERIAL_BAUD_RATE 9600

#include <NESControllerInterface.h>

#include "errorIndicator.h"
#include "motor.h"
#include "normPinDefs.h"

int max(int a, int b, int c, int d) {
    {
        // checking if a is largest
        if (a >= b && a >= c && a >= d) {
            return a;
        }

        // checking if b is largest
        else if (b >= a && b >= c && b >= d) {
            return b;
        }
        // checking if c is largest
        else if (c >= a && c >= b && c >= d) {
            return c;
        }
        return d;
    }
}

void normalize(int *a, int *b, int *c, int *d) {
    int aABS = abs(*a);
    int bABS = abs(*b);
    int cABS = abs(*c);
    int dABS = abs(*d);

    int denominator = max(aABS, bABS, cABS, dABS) / 100;

    *a /= denominator;
    *b /= denominator;
    *c /= denominator;
    *d /= denominator;
}
Motor frontLeftMotor(FRONT_LEFT_MOTOR_DIRECTION_PIN, FRONT_LEFT_MOTOR_SPEED_PIN,
                     FRONT_LEFT_MOTOR_ENCODER_A_PIN,
                     FRONT_LEFT_MOTOR_ENCODER_B_PIN,
                     FRONT_LEFT_MOTOR_ROTATION_INVERTED);

Motor frontRightMotor(FRONT_RIGHT_MOTOR_DIRECTION_PIN,
                      FRONT_RIGHT_MOTOR_SPEED_PIN,
                      FRONT_RIGHT_MOTOR_ENCODER_A_PIN,
                      FRONT_RIGHT_MOTOR_ENCODER_B_PIN,
                      FRONT_RIGHT_MOTOR_ROTATION_INVERTED);

Motor backLeftMotor(BACK_LEFT_MOTOR_DIRECTION_PIN, BACK_LEFT_MOTOR_SPEED_PIN,
                    BACK_LEFT_MOTOR_ENCODER_A_PIN,
                    BACK_LEFT_MOTOR_ENCODER_B_PIN,
                    BACK_LEFT_MOTOR_ROTATION_INVERTED);

Motor backRightMotor(BACK_RIGHT_MOTOR_DIRECTION_PIN, BACK_RIGHT_MOTOR_SPEED_PIN,
                     BACK_RIGHT_MOTOR_ENCODER_A_PIN,
                     BACK_RIGHT_MOTOR_ENCODER_B_PIN,
                     BACK_RIGHT_MOTOR_ROTATION_INVERTED);

NESControllerInterface nes(A5, A4, D12);

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);

    // ErrorIndicator should be initialised first
    ErrorIndicator_G.begin(SERIAL_BAUD_RATE, LED_BUILTIN);

    // Add a callback to the ErrorIndicator to stop the motors if an error
    // occurs.
    ErrorIndicator_G.addHaltCallback([]() {
        frontLeftMotor.stop();
        frontRightMotor.stop();
        backLeftMotor.stop();
        backRightMotor.stop();
    });

    frontLeftMotor.setup([]() { frontLeftMotor.isr(); });
    frontRightMotor.setup([]() { frontRightMotor.isr(); });
    backLeftMotor.setup([]() { backLeftMotor.isr(); });
    backRightMotor.setup([]() { backRightMotor.isr(); });

    // Because I forgot to put breakouts on the driver board, use pin 13 as a
    // voltage source.
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
}

void loop() {
    NESInput input = nes.getNESInput();

    if (input.anyButtonPressed()) {
        int FL = 0;
        int FR = 0;
        int BL = 0;
        int BR = 0;

        if (input.buttonUp) {
            FL += 100;
            FR += -100;
            BL += 100;
            BR += -100;
        }
        if (input.buttonDown) {
            FL += -100;
            FR += 100;
            BL += -100;
            BR += 100;
        }
        if (input.buttonLeft) {
            FL += -100;
            FR += -100;
            BL += 100;
            BR += 100;
        }
        if (input.buttonRight) {
            FL += 100;
            FR += 100;
            BL += -100;
            BR += -100;
        }
        if (input.buttonB) {
            FL += -100;
            FR += -100;
            BL += -100;
            BR += -100;
        }
        if (input.buttonA) {
            FL += 100;
            FR += 100;
            BL += 100;
            BR += 100;
        }

        normalize(&FL, &FR, &BL, &BR);

        frontLeftMotor.setVelocity(FL);
        frontRightMotor.setVelocity(FR);
        backLeftMotor.setVelocity(BL);
        backRightMotor.setVelocity(BR);

    } else {
        frontLeftMotor.stop();
        frontRightMotor.stop();
        backLeftMotor.stop();
        backRightMotor.stop();
    }
}