#include "MotorController.h"

/**
 * Constructor zet motors en snelheid.
 * m: verwijzing naar Zumo32U4Motors
 * s: standaard snelheid
 */
MotorController::MotorController(Zumo32U4Motors* m, int s) {
    motors = m;
    speed = s;
}

/**
 * Beide motoren vooruit op standaard snelheid.
 */
void MotorController::driveForward() {
    motors->setLeftSpeed(speed);
    motors->setRightSpeed(speed);
}

/**
 * Beide motoren stoppen.
 */
void MotorController::stop() {
    motors->setLeftSpeed(0);
    motors->setRightSpeed(0);
}

/**
 * Bocht links maken.
 * Linkermotor langzamer.
 */
void MotorController::turnLeft() {
    motors->setLeftSpeed(speed / 2);
    motors->setRightSpeed(speed);
}

/**
 * Bocht rechts maken.
 * Rechtermotor langzamer.
 */
void MotorController::turnRight() {
    motors->setLeftSpeed(speed);
    motors->setRightSpeed(speed / 2);
}

/**
 * Stel beide motorsnelheden apart in.
 */
void MotorController::setMotorSpeeds(int left, int right) {
    motors->setLeftSpeed(left);
    motors->setRightSpeed(right);
}
