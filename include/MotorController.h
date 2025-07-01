#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Zumo32U4.h>

class MotorController {
private:
    Zumo32U4Motors* motors;
    int speed;

public:
    MotorController(Zumo32U4Motors* m, int s = 150);

    void driveForward();
    void stop();
    void turnLeft();
    void turnRight();
    void setMotorSpeeds(int left, int right);

};

#endif // MOTORCONTROLLER_H
