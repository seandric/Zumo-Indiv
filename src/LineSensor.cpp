#include "LineSensor.h"
#include <Arduino.h>

LineSensor::LineSensor() {
    lineSensors.initFiveSensors();
}

void LineSensor::calibrate() {
    for (int i = 0; i < 100; i++) {
        lineSensors.calibrate();
        delay(20);
    }
}

void LineSensor::detectLine() {
    lineSensors.read(lineSensorValues);
}

unsigned int LineSensor::readLine() {
    return lineSensors.readLine(lineSensorValues);
}

const unsigned int* LineSensor::getValues() const {
    return lineSensorValues;
}
