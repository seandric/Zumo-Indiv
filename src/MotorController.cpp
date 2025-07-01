#include "MotorController.h"

MotorController::MotorController(Zumo32U4Motors* m, int s) {
    motors = m;
    speed = s;
}

void MotorController::driveForward() {
    motors->setLeftSpeed(speed);
    motors->setRightSpeed(speed);
}

void MotorController::stop() {
    motors->setLeftSpeed(0);
    motors->setRightSpeed(0);
}

void MotorController::turnLeft() {
    motors->setLeftSpeed(speed / 2);
    motors->setRightSpeed(speed);
}

void MotorController::turnRight() {
    motors->setLeftSpeed(speed);
    motors->setRightSpeed(speed / 2);
}

void MotorController::setMotorSpeeds(int left, int right) {
    motors->setLeftSpeed(left);
    motors->setRightSpeed(right);
}

