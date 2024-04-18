#include "main.h"
#include "pumpController.h"

#include <Arduino.h>
#include <IRremote.hpp>

int numberCommands[] = { 12, 24, 94, 8, 28, 90, 66, 82, 74};
PumpController controller;

void handleInput(uint16_t command);
bool contains(int array[], int value);

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
    controller = PumpController();
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.command);
        handleInput(IrReceiver.decodedIRData.command);
        
        IrReceiver.resume();
        delay(1000);
    }
}

void handleInput(uint16_t command) {
    switch (command)
    {
        case 69:
            Serial.println("Toggle command");   
            controller.toggleRunning();
            break;
        
        default:
            if (!contains(numberCommands, command)) return;
            
            for (int i = 0; i < sizeof(numberCommands) / sizeof(int); i++) {
                if (command == numberCommands[i]) {
                    Serial.println("Number command: " + String(i));
                    controller.run(i * 10000);
                    break;
                }
            }
            break;
    }
}

bool contains(int array[], int value) {
    for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
        if (array[i] == value) {
            Serial.println("Found value in array");
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