#include "LineFollower.h"
#include <Arduino.h>

/**
 * 
 * Stelt de PID-regelaar in met standaardwaarden en bewaart
 * de referenties naar de MotorController en LineSensor.
 * 
 * @param m Pointer naar de MotorController (voor 2 motoren)
 * @param l Pointer naar de LineSensor (voor lijnmeting)
 */
LineFollower::LineFollower(MotorController* m, LineSensor* l)
    : motorController(m),      // bestuurt links en rechts motor
      lineSensor(l),           // meet lijnpositie
      Kp(0.2),                 // proportioneel component
      Ki(0.0),                 // integraal component
      Kd(0.4),                 // differentieel component
      baseSpeed(350),          // standaard snelheid
      maxSpeed(500),           // snelheidslimiet
      lastError(0),            // vorige fout voor D-term
      integral(0) {}           // opgetelde fout voor I-term


/**
 * Voert één cyclus lijnvolgen uit.
 * 
 * - Leest sensorwaardes.
 * - Bepaalt of er een lijn is.
 * - Berekent de lijnpositie.
 * - Gebruikt PID-regeling om correctie te berekenen.
 * - Past linker- en rechtermotorsnelheden aan.
 */
void LineFollower::followLine() {
    // Vraag actuele sensorwaardes op
    lineSensor->detectLine();

    bool lineDetected = false;
    const unsigned int* values = lineSensor->getValues();

    // Debug-print slechts 1x per seconde
    static unsigned long lastPrintTime = 0;
    bool shouldPrint = (millis() - lastPrintTime >= 1000);

    if (shouldPrint) {
        Serial.print("Sensor values: ");
    }

    // Controleer of minstens 1 sensor zwart ziet
    for (int i = 0; i < 5; i++) {
        if (shouldPrint) {
            Serial.print(values[i]);
            Serial.print(" ");
        }

        if (values[i] < 700) {  // threshold zwart detectie
            lineDetected = true;
        }
    }

    if (shouldPrint) {
        Serial.println();
    }

    // Geen lijn gedetecteerd = rechtdoor rijden
    if (!lineDetected) {
        if (shouldPrint) {
            Serial.println("Geen lijn gezien - rijdt rechtdoor");
        }

        // Rij gewoon rechtdoor op basissnelheid
        motorController->setMotorSpeeds(baseSpeed, baseSpeed);

        // Reset PID geheugen
        integral = 0;
        lastError = 0;

        if (shouldPrint) {
            lastPrintTime = millis();
        }
        return;
    }

    // Lees berekende lijnpositie (0–4000)
    unsigned int position = lineSensor->readLine();

    if (shouldPrint) {
        Serial.print("Line position: ");
        Serial.println(position);
    }

    // Bepaal verschil tot ideale middenpositie
    const long MID_POINT = 2500;  // moet afgestemd worden

    long error = position - MID_POINT;

    // PID-berekening
    integral += error;                       // I-term
    long derivative = error - lastError;     // D-term
    lastError = error;

    float correction = Kp * error + Ki * integral + Kd * derivative;

    // Bereken linker- en rechtermotorsnelheid
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;

    // Beperk snelheden binnen limiet
    leftSpeed = constrain(leftSpeed, 0, maxSpeed);
    rightSpeed = constrain(rightSpeed, 0, maxSpeed);

    // Stuur de motoren met nieuwe snelheden
    motorController->setMotorSpeeds(leftSpeed, rightSpeed);

    if (shouldPrint) {
        Serial.print("Motor L: ");
        Serial.print(leftSpeed);
        Serial.print(" R: ");
        Serial.println(rightSpeed);
        lastPrintTime = millis();
    }

    delay(3); // kleine vertraging voor stabiliteit
}
