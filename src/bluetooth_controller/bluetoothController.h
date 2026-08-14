#include <Arduino.h>

#define E1 5
#define M1 4
#define E2 6
#define M2 7
#define switchPin 3
#define LED 22



void getControllerInput();
void moveForward(uint16_t pwm);
void moveBackwards(uint16_t pwm);
void moveLeft(uint16_t pwm);
void moveRight(uint16_t pwm);
void stop();
//void toggleMode();
void bluetoothController();
void waitForButtonRelease();
void initBluetoothControl();
bool getSwitchState();
bool toggleMode(bool switchState);
