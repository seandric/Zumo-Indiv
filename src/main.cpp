#include <Arduino.h>
#include <Zumo32U4.h>
#include "MotorController.h"
#include "LineSensor.h"
#include "LineFollower.h"

Zumo32U4Motors motors;
MotorController motorController(&motors, 150);
LineSensor lineSensor;
LineFollower lineFollower(&motorController, &lineSensor);

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Starting calibration...");

  lineSensor.calibrate();

  Serial.println("Calibration complete. Waiting...");
  delay(5000); // extra 5 seconden pauze om hem neer te zetten
  Serial.println("Starting line following...");
}



void loop() {
  lineFollower.followLine();
  delay(50);  // kleine vertraging voor stabiliteit
}
