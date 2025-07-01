#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "MotorController.h"
#include "LineSensor.h"

class LineFollower {
private:
    MotorController* motorController;
    LineSensor* lineSensor;

    float Kp;
    float Ki;
    float Kd;

    const int baseSpeed;
    const int maxSpeed;

    long lastError;
    float integral;

public:
    LineFollower(MotorController* m, LineSensor* l);

    void followLine();
};

#endif // LINEFOLLOWER_H
