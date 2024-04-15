#include "pumpController.h"

#include <Arduino.h>

bool isRunning() {
    return digitalRead(PUMP_PIN) == HIGH;
}

void PumpController::toggleRunning() {
    auto value = isRunning() ? LOW : HIGH;
    Serial.println("Toggling motor to " + String(value));
    digitalWrite(PUMP_PIN, value);
}

void PumpController::run() {
    Serial.println("Running motor");
    digitalWrite(PUMP_PIN, HIGH);
}

void PumpController::run(int timeMS) {
    if (isRunning()) return;

    run();
    delay(timeMS);
    stop();
}

void PumpController::stop() {
    Serial.println("Stopping motor");
    digitalWrite(PUMP_PIN, LOW);
}