#include "UnoJoy.h"

#define CLK 2  // Clock pin
#define DT 3   // Data pin
#define SW 13  // Button pin (not used)

#define POT1 A0  // Left Y potentiometer
#define POT2 A1  // Right Y potentiometer
#define POT3 A2  // Right X potentiometer

#define RANGE 800

int leftStickX = 128;   // Start in the middle (0-255 range)
int leftStickY = 128;   // Start in the middle (0-255 range)
int rightStickX = 128;  // Start in the middle (0-255 range)
int rightStickY = 128;  // Start in the middle (0-255 range)

// Variables for the rotary encoder
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile int lastMSB = 0;
volatile int lastLSB = 0;

int readPedal(int pin) {
    float reading = map(analogRead(pin), 0, 1023, 0, 255) * 2;
    return constrain(reading, 0, 255);
}

void setup() {
  setupPins();
  setupUnoJoy();
  
  // Set up rotary encoder pins
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  
  // Attach interrupts for rotary encoder
  attachInterrupt(digitalPinToInterrupt(CLK), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT), updateEncoder, CHANGE);
  
  // Initialize lastEncoded value
  lastEncoded = (digitalRead(CLK) << 1) | digitalRead(DT);
}

void loop() {
  dataForController_t controllerData = getControllerData();
  
  // Convert encoder value to leftStickX (steering)
  // Map the encoder value to the joystick range
  leftStickX = map(encoderValue, -RANGE, RANGE, -255, 255);

  // Assign mapped values to controllerData
  controllerData.leftStickX = leftStickX;    // Steering
  controllerData.leftStickY = readPedal(POT1);
  controllerData.rightStickX = readPedal(POT2);
  controllerData.rightStickY = readPedal(POT3);

  // Send controller data
  setControllerData(controllerData);
  delay(5);
}

void updateEncoder() {
  int MSB = digitalRead(CLK);  // Most significant bit
  int LSB = digitalRead(DT);   // Least significant bit
  
  int encoded = (MSB << 1) | LSB;          // Converting the 2 pin values to a single number
  int sum = (lastEncoded << 2) | encoded;  // Adding it to the previous encoded value
  
  // Update encoder value based on the rotation
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue--;  // Clockwise rotation
  }
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue++;  // Counter-clockwise rotation
  }
  
  // Limit the encoder value to prevent overflow
  encoderValue = constrain(encoderValue, -RANGE, RANGE);
  
  // Store the encoded value for next time
  lastEncoded = encoded;
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
  controllerData.crossOn = !digitalRead(6);
  controllerData.circleOn = !digitalRead(7);
  controllerData.squareOn = !digitalRead(8);
  controllerData.triangleOn = !digitalRead(9);

  return controllerData;
}