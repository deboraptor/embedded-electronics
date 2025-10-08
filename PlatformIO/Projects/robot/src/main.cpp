#include <Arduino.h>
#include "eyes.h"

Eyes eyes(22, 21, 400000, 0x3D, 0x3C);

void setup() {
  eyes.begin();
}

void loop() {
  eyes.animateStep();
}