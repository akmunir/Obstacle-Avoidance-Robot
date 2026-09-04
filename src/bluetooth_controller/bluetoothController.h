#include <Arduino.h>


#define switchPin 3
#define LED 22



void getControllerInput();
//void toggleMode();
void bluetoothController();
void waitForButtonRelease();
void initBluetoothControl();
bool getSwitchState();
bool toggleMode(bool switchState);
