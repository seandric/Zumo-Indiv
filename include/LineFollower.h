#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "MotorController.h"
#include "LineSensor.h"

/**
 * Volgt lijn met PID-regeling.
 */
class LineFollower {
private:
    MotorController* motorController; // bestuurt 2 motoren
    LineSensor* lineSensor;           // leest lijnsensoren

    float Kp;  // PID P-factor
    float Ki;  // PID I-factor
    float Kd;  // PID D-factor

    const int baseSpeed; // standaard snelheid
    const int maxSpeed;  // limiet snelheid

    long lastError;      // vorige fout voor D
    float integral;      // opgetelde fout voor I

public:
    LineFollower(MotorController* m, LineSensor* l);

    void followLine(); // lees sensor, stuur motor
};

#endif // LINEFOLLOWER_H
