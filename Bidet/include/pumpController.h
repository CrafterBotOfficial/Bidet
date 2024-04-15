#include "main.h"

class PumpController {
    public:
        static void toggleRunning();

        static void stop();
        static void run();
        static void run(int timeMS);
};