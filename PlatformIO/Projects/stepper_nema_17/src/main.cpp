/*
  doc : https://www.redohm.fr/download/arduino-et-moteurs-pas-a-pas-decouverte-de-la-bibliotheque-accelstepper/

  Controlling two stepper with the AccelStepper library

    by Dejan, https://howtomechatronics.com
*/

#include <AccelStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 2, 5); // (Type of driver: with 2 pins, STEP, DIR)

void setup() {
  digitalWrite(8, HIGH); // Enable the motor driver (if applicable)

  stepper1.setMaxSpeed(1000); // Set maximum speed value for the stepper
  stepper1.setAcceleration(500); // Set acceleration value for the stepper
  stepper1.setCurrentPosition(0); // Set the current position to 0 steps
}

void loop() {

  stepper1.moveTo(800); // Set desired move: 800 steps (in quater-step resolution that's one rotation)
  stepper1.runToPosition(); // Moves the motor to target position w/ acceleration/ deceleration and it blocks until is in position

  // Move back to position 0, using run() which is non-blocking - both motors will move at the same time
  stepper1.moveTo(0);
  while (stepper1.currentPosition() != 0) {
    stepper1.run();  // Move or step the motor implementing accelerations and decelerations to achieve the target position. Non-blocking function
    //
    //
  }
}