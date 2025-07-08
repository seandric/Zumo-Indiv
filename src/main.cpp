#include "LineSensor.h"
#include <Arduino.h>

/**
 * Initialiseert 5 lijnsensoren.
 */
LineSensor::LineSensor() {
    lineSensors.initFiveSensors();
}

/**
 * Kalibreert sensor op zwart/wit.
 */
void LineSensor::calibrate() {
    for (int i = 0; i < 100; i++) {
        lineSensors.calibrate();
        delay(20);
    }
}

/**
 * Leest actuele waarden in array.
 */
void LineSensor::detectLine() {
    lineSensors.read(lineSensorValues);
}

/**
 * Geeft lijnpositie 0–4000.
 */
unsigned int LineSensor::readLine() {
    return lineSensors.readLine(lineSensorValues);
}

/**
 * Retourneert pointer naar waarden.
 */
const unsigned int* LineSensor::getValues() const {
    return lineSensorValues;
}
