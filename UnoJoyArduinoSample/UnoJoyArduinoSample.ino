#include "UnoJoy.h"

#define CLK 2  // Clock pin
#define DT 3   // Data pin
#define SW 13   // Button pin

#define POT1 A0  // Left Y potentiometer
#define POT2 A1  // Right Y potentiometer
#define POT3 A2  // Right X potentiometer

int lastCLKState;
int leftStickX = 128;   // Start in the middle (0-255 range)
int leftStickY = 128;   // Start in the middle (0-255 range)
int rightStickX = 128;  // Start in the middle (0-255 range)
int rightStickY = 128;  // Start in the middle (0-255 range)

void setup() {
  setupPins();
  setupUnoJoy();
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  lastCLKState = digitalRead(CLK);
}

void loop() {
  dataForController_t controllerData = getControllerData();

  // Steering (leftStickX)
  int currentCLKState = digitalRead(CLK);
  if (currentCLKState != lastCLKState) {
    if (digitalRead(DT) != currentCLKState) {
      leftStickX = min(255, leftStickX + 1);  // Turn right
    } else {
      leftStickX = max(0, leftStickX - 1);  // Turn left
    }
  }
  lastCLKState = currentCLKState;

  // Map potentiometer values to joystick Y axes
  leftStickY = map(analogRead(POT1), 0, 1023, 0, 255);   // Map left potentiometer to left Y axis
  rightStickY = map(analogRead(POT2), 0, 1023, 0, 255);  // Map right potentiometer to right Y axis
  rightStickX = map(analogRead(POT3), 0, 1023, 0, 255);

  // Assign mapped values to controllerData
  controllerData.leftStickX = leftStickX;    // Steering
  controllerData.leftStickY = leftStickY;    // Throttle
  controllerData.rightStickX = rightStickX;  // Clutch
  controllerData.rightStickY = rightStickY;  // Brake

  // Handle ON-OFF-ON

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
  controllerData.circleOn = !digitalRead(4);    // Gear splitter
  controllerData.crossOn = !digitalRead(5);     // Engine brake
  controllerData.l1On = !digitalRead(6);        // 1st
  controllerData.l2On = !digitalRead(7);        // 2nd
  controllerData.l3On = !digitalRead(8);        // 3rd
  controllerData.r1On = !digitalRead(9);        // 4th
  controllerData.r2On = !digitalRead(10);       // 5th
  controllerData.r3On = !digitalRead(11);       // 6th
  controllerData.squareOn = !digitalRead(12);   // Reverse
  return controllerData;
}
