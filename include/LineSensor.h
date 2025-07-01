#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Arduino.h>
#include <Zumo32U4.h>

class LineSensor {
private:
    Zumo32U4LineSensors lineSensors;
    unsigned int lineSensorValues[5];

public:
    LineSensor();

    void calibrate();
    unsigned int readLine();
    void detectLine();
    const unsigned int* getValues() const;
};

#endif // LINESENSOR_H
