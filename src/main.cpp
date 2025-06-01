#include <Arduino.h>
#include "IRremote.h"

#define PUMP_PIN 2
#define IR_PIN 3
#define POWER_BTN 69 

#define TIME_BTN_MULTIPLIER 1000 

int timedCommands[] = { 12, 24, 94, 8, 28, 90, 66, 82, 74 }; 

bool pumpState;
int remoteInputCount = sizeof(timedCommands) / sizeof(timedCommands[0]);

void setup() {
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);
}

void loop() {
    if (!IrReceiver.decode()) return;
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) { 
        IrReceiver.resume();
        return;
    }

    int *commandPtr = &IrReceiver.decodedIRData.command;
    if (*commandPtr == POWER_BTN) {
        pumpState = !pumpState;
        digitalWrite(PUMP_PIN, pumpState);    
        goto end;
    }
    
    if (!pumpState)
        for (int index = 0; index < remoteInputCount; index ++) {
            if (timedCommands[index] != *commandPtr) continue;
            digitalWrite(PUMP_PIN, HIGH);
            delay((index + 1) * TIME_BTN_MULTIPLIER);
            digitalWrite(PUMP_PIN, LOW);
            break;
        }

end:
    IrReceiver.resume();
    delay(50);
}