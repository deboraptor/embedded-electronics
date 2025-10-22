#include <Arduino.h>

#define STEP_PIN 2
#define DIR_PIN  5
#define EN_PIN   8

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN,  OUTPUT);
  pinMode(EN_PIN,   OUTPUT);

  digitalWrite(EN_PIN, LOW);     // enable
  digitalWrite(DIR_PIN, HIGH);   // sens (LOW pour inverser ?)
}

void loop() {
  digitalWrite(STEP_PIN, HIGH);
  delay(2);                      // 2 ms up -> ~250 pas/s /2 = 125 steps/s
  digitalWrite(STEP_PIN, LOW);
  delay(2);
}