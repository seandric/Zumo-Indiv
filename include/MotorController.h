#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Zumo32U4.h>

/**
 * Stuurt 2 motoren aan.
 */
class MotorController {
private:
    Zumo32U4Motors* motors; // link+rechts motoren
    int speed;              // standaard snelheid

public:
    MotorController(Zumo32U4Motors* m, int s = 150);

    void driveForward();                     // beide vooruit
    void stop();                             // beide stop
    void turnLeft();                         // links langzamer
    void turnRight();                        // rechts langzamer
    void setMotorSpeeds(int left, int right);// aparte snelheden
};

#endif // MOTORCONTROLLER_H
