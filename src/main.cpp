#include <Arduino.h>
#include <Servo.h>
#include "bluetooth_controller/bluetoothController.h"

#define servoPin 23

Servo servo;
int servoPosition = -90;
bool switchState = false;
bool modeToggle = false;

void rotateServo(uint16_t angle, bool direction);

void setup() {
//servo.attach(servoPin);
//rotateServo(servoPosition, 1);
// change timer3 frequency for pwm noise
  TCCR3B = (TCCR3B & 0b11111000) | 0x01;
  // change timer4 frequency for pwm noise
  TCCR4B = (TCCR4B & 0b11111000) | 0x01;
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
initBluetoothControl();
}

void loop()
{
    switchState = getSwitchState();
    modeToggle = toggleMode(switchState);

    if (modeToggle)
    {
        bluetoothController();
    }
    else
    {

    }
    
}

void rotateServo(uint16_t pos, bool direction)
{
    if (direction)
    {
        servo.write(pos);
    }
    else
    {
        servo.write(-pos);
    }
}