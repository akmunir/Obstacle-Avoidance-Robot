#include <Arduino.h>
#include <motor.h>




extern Motor leftMotor;
extern Motor rightMotor;

void moveForward(uint16_t pwm);
void moveBackwards(uint16_t pwm);
void moveLeft(uint16_t pwm);
void moveRight(uint16_t pwm);
void stop();
void initializeMotors();

