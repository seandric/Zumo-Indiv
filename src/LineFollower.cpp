#include "LineFollower.h"
#include <Arduino.h>

LineFollower::LineFollower(MotorController* m, LineSensor* l)
    : motorController(m), lineSensor(l),
      Kp(0.25),     // beginwaarden - rustig
      Ki(0.0005),
      Kd(4.0),
      baseSpeed(600),
      maxSpeed(850),
      lastError(0),
      integral(0) {}

void LineFollower::followLine() {
    lineSensor->detectLine();

    bool lineDetected = false;
    const unsigned int* values = lineSensor->getValues();
    for (int i = 0; i < 5; i++) {
        if (values[i] < 500) {
            lineDetected = true;
            break;
        }
    }

    if (!lineDetected) {
        // Geen lijn - zachtjes rechtdoor
        motorController->setMotorSpeeds(baseSpeed, baseSpeed);
        integral = 0;
        lastError = 0;
        return;
    }

    unsigned int position = lineSensor->readLine();
    long error = position - 2000;

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

    delay(10); // net iets trager om rust te brengen
}
