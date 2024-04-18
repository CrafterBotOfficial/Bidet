#include "main.h"

class PumpController {
    private:
        bool isRunning;

    public:
        void toggleRunning();

        void stop();
        void run();
        void run(int timeMS);
};