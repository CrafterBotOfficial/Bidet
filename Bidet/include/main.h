#include <Arduino.h>

#define IR_PIN 3
#define PUMP_PIN 2

void handleInput(uint16_t command);
bool contains(uint16_t value);