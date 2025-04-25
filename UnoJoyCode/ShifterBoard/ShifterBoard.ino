#include "UnoJoy.h"

#define POT1 A0 // Camera

int leftStickX = 128; 

void setup() {
  setupPins();
  setupUnoJoy();
}

void loop() {
  dataForController_t controllerData = getControllerData();

  // Send controller data
  setControllerData(controllerData);
  delay(5);
}

void setupPins(void) {
  for (int i = 4; i <= 13; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }

  pinMode(A4, INPUT);
  digitalWrite(A4, HIGH);
  pinMode(A5, INPUT);
  digitalWrite(A5, HIGH);
}

dataForController_t getControllerData(void) {
  dataForController_t controllerData = getBlankDataForController();
  controllerData.circleOn = digitalRead(5);    // Gear splitter
  controllerData.l1On = !digitalRead(6);        // 1st
  controllerData.l2On = !digitalRead(7);        // 2nd
  controllerData.l3On = !digitalRead(8);        // 3rd
  controllerData.r1On = !digitalRead(9);        // 4th
  controllerData.r2On = !digitalRead(10);       // 5th
  controllerData.r3On = !digitalRead(11);       // 6th
  controllerData.squareOn = !digitalRead(12);   // Reverse
  return controllerData;
}
