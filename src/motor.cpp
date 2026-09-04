#include <Arduino.h>
#include "motor.h"

        Motor::Motor(uint8_t e, uint8_t m) {
            pwmPin = e;
            dirPin = m;
        }
        void Motor::begin() {
            pinMode(pwmPin, OUTPUT);
            pinMode(dirPin, OUTPUT);
            analogWrite(pwmPin, 0);
            digitalWrite(dirPin, LOW);
        }
        int Motor::getPwm() {
            return pwmValue;
        }
        void Motor::move(int pwmVal, bool direction) {
            pwmValue = constrain(abs(pwmVal), 0, 255);
            digitalWrite(pwmPin, LOW);
            digitalWrite(dirPin, direction);
            analogWrite(pwmPin, pwmValue);

        }
        void Motor::stop() {
            pwmValue = 0;
            digitalWrite(pwmPin, LOW);
            digitalWrite(dirPin, LOW);
            analogWrite(pwmPin, pwmValue);
        }

        