#include "main.h"

#include <IRremote.hpp>

uint16_t numberCommands[NUMBER_REMOTE_COUNT] = { 12, 24, 94, 8, 28, 90, 66, 82, 74}; // 9

bool isPumpRunning = false;

void setup() {
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        handleInput(IrReceiver.decodedIRData.command);
        
        delay(300);
        IrReceiver.resume();
    }
}

void handleInput(uint16_t command) {
    switch (command)
    {
        case 69: // Power
            isPumpRunning = !isPumpRunning;
            digitalWrite(PUMP_PIN, isPumpRunning ? HIGH : LOW);
            break;
        
        default:
            if (isPumpRunning || !contains(command)) 
                return;
            
            for (int i = 0; i < NUMBER_REMOTE_COUNT; i++) {
                if (command == numberCommands[i]) {                    
                    digitalWrite(PUMP_PIN, HIGH);
                    delay((i + 1) * 10000);
                    digitalWrite(PUMP_PIN, LOW);
                    isPumpRunning = false;
                    break;
                }
            }
            break;
    }
}

bool contains(uint16_t value) {
    for (int i = 0; i < NUMBER_REMOTE_COUNT; i++) { 
        if (numberCommands[i] == value) {
            return true;
        } 
    }
    return false;
}

/*
Controller mapping: 
Power: 69
Volume up: 70
func stop: 71
left arrow: 68
pause: 64
right arrow: 64
down arrow: 7
volume down 21
up arrow: 9
0: 22
EQ: 25
st/rept: 13
1: 12
2: 24
3: 94
4: 8
5: 28
6: 90
7: 66
8: 82
9: 74


*/