#include "pumpController.h"

#include <Arduino.h>

void PumpController::toggleRunning() {
    if (isRunning) stop();
    else run();
}

void PumpController::run() {
    if (isRunning) return;
    Serial.println("Running motor");
    digitalWrite(PUMP_PIN, HIGH);
    isRunning = true;
}

void PumpController::run(int timeMS) {
    if (isRunning) return;

    run();
    delay(timeMS);
    stop();
}

void PumpController::stop() {
    if (!isRunning) return;
    Serial.println("Stopping motor");
    digitalWrite(PUMP_PIN, LOW);
    isRunning = false;
}