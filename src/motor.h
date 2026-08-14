#ifndef MOTOR_H
#include <Arduino.h>
#define MOTOR_H

class Motor {
    public:
        Motor(uint8_t e, uint8_t m);
        void begin();
        int getPwm();
        void move(int pwmVal, bool direction);
        void stop();
    private:
        uint8_t pwmPin;
        uint8_t dirPin;
        int pwmValue;
};

#endif