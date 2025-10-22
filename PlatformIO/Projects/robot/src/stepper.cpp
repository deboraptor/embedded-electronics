/*   
 *   Basic example code for controlling a stepper with the AccelStepper library
 *      
 *   by Dejan, https://howtomechatronics.com
 */

#include <AccelStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 2, 5); // (Type of driver: with 2 pins, STEP, DIR)

void setup() {
  // Set maximum speed value for the stepper
  stepper1.setMaxSpeed(1000);
}

void loop() {
  stepper1.setSpeed((analogRead(A0));
  // Step the motor with a constant speed previously set by setSpeed();
  stepper1.runSpeed();
}