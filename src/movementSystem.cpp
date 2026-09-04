#include "movementSystem.h"

const uint8_t E1 = 5;
const uint8_t M1 = 4;
const uint8_t E2 = 6;
const uint8_t M2 = 7;

Motor leftMotor(E2, M2);
Motor rightMotor(E1, M1);

void moveForward(uint16_t pwm) {
  leftMotor.move(pwm, 1);
  rightMotor.move(pwm, 1);
}

void moveBackwards(uint16_t pwm) {
  leftMotor.move(pwm, 0);
  rightMotor.move(pwm, 0);
}

void moveLeft(uint16_t pwm) {
  leftMotor.move(pwm, 0);
  rightMotor.move(pwm, 1);
}

void moveRight(uint16_t pwm) {
  leftMotor.move(pwm, 1);
  rightMotor.move(pwm, 0);
}

void stop() {
  leftMotor.stop();
  rightMotor.stop();
}

void initializeMotors() {
    leftMotor.begin();
    rightMotor.begin();
}