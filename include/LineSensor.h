#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Arduino.h>
#include <Zumo32U4.h>

/**
 * Leest lijnsensoren onder robot.
 */
class LineSensor {
private:
    Zumo32U4LineSensors lineSensors;     // 5 sensoren module
    unsigned int lineSensorValues[5];    // laatste gemeten waarden

public:
    LineSensor();

    void calibrate();                     // kalibreer zwart/wit
    unsigned int readLine();               // lijnpositie 0–4000
    void detectLine();                      // vul sensorValues
    const unsigned int* getValues() const;   // leest rauwe waardes
};

#endif // LINESENSOR_H
