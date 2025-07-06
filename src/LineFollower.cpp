#include "LineFollower.h"
#include <Arduino.h>

LineFollower::LineFollower(MotorController* m, LineSensor* l)
    : motorController(m), lineSensor(l),
      Kp(0.2),          // zachtere P
      Ki(0.0),          // geen I voor lijnen
      Kd(0.4),          // zachtere D
      baseSpeed(300),   // rustiger snelheid
      maxSpeed(500),
      lastError(0),
      integral(0) {}

void LineFollower::followLine() {
    lineSensor->detectLine();

    bool lineDetected = false;
    const unsigned int* values = lineSensor->getValues();
    for (int i = 0; i < 5; i++) {
        if (values[i] < 800) {  // hoger threshold zodat hij lijn ziet
            lineDetected = true;

    }

    if (!lineDetected) {
    // Geen lijn gevonden - rijd rechtdoor
    motorController->setMotorSpeeds(baseSpeed, baseSpeed);
    // We onthouden de oude lastError en integral
    return;
}


    // Lees positie op de lijn
    unsigned int position = lineSensor->readLine();

    // 👇 BELANGRIJK! Zet jouw ECHTE middenwaarde hier in
    // Meet hem met Serial.print(position) als hij mooi op het midden staat
    const long MID_POINT = 2150;  // voorbeeld - vervang door jouw echte waarde!

    long error = position - MID_POINT;

    // PID
    integral += error;
    long derivative = error - lastError;
    lastError = error;

    float correction = Kp * error + Ki * integral + Kd * derivative;

    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;

    leftSpeed = constrain(leftSpeed, 0, maxSpeed);
    rightSpeed = constrain(rightSpeed, 0, maxSpeed);

    motorController->setMotorSpeeds(leftSpeed, rightSpeed);

    delay(3);  // kleine rustvertraging
}
