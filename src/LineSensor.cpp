#include "LineSensor.h"
#include <Arduino.h>

/**
 * Constructor initialiseert 5 lijnsensoren.
 * Klaar om waardes te meten.
 */
LineSensor::LineSensor() {
    lineSensors.initFiveSensors();
}

/**
 * Kalibreert de lijnsensoren.
 * Herkent verschil tussen zwart en wit.
 * Robot moet hierbij over lijn bewegen
 */
void LineSensor::calibrate() {
    for (int i = 0; i < 100; i++) {
        lineSensors.calibrate();
        delay(20); // kleine pauze voor stabiele meting
    }
}

/**
 * Leest actuele sensorwaarden in array.
 * Vul lineSensorValues met huidige meetresultaten.
 */
void LineSensor::detectLine() {
    lineSensors.read(lineSensorValues);
}

/**
 * Berekent lijnpositie (0–4000).
 * Retourneert gewogen waarde op basis van sensoren.
 */
unsigned int LineSensor::readLine() {
    return lineSensors.readLine(lineSensorValues);
}

/**
 * Geeft pointer naar laatste rauwe waarden.
 */
const unsigned int* LineSensor::getValues() const {
    return lineSensorValues;
}
