#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_BluefruitLE_UART.h>
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLE.h"
#include <HardwareSerial.h>
#include "Adafruit_ATParser.h"
#include "packetParser.h"
#include <motor.h>
#include "bluetoothController.h"

#define BLUEFRUIT_HWSERIAL_NAME Serial1
#define BLUEFRUIT_UART_MODE_PIN -1
#define BLE_READPACKET_TIMEOUT 500
#define E1 5
#define M1 4
#define E2 6
#define M2 7
#define switchPin 3
#define LED 22

Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);

uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
extern uint8_t packetbuffer[];

uint8_t input = '0';
uint16_t pwm = 150;
bool bluetoothToggle = false;

Motor leftMotor = Motor(E2, M2);
Motor rightMotor = Motor(E1, M1);
void initBluetoothControl()
{
  Serial.begin(115200);
  ble.begin(115200);
  leftMotor.begin();
  rightMotor.begin();
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(switchPin), toggleMode, CHANGE);
}
// forward is 5, backwards is 6, left is 7, right is 8

// void toggleMode() {
//   bluetoothToggle = !bluetoothToggle;
//   digitalWrite(LED, !digitalRead(LED));

// }
// void manualControl()
// {
//   if (switchState == 1) {
//     Serial.println("on");
//     bluetoothToggle = true;
//     digitalWrite(LED, HIGH);
//   } else {
//     bluetoothToggle = false;
//     digitalWrite(LED, LOW);
//     Serial.println("off");
//   }
//   if (bluetoothToggle)
//   {
//     bluetoothController();
//   }
// }

bool toggleMode(bool switchState) {
    if (switchState == 1) {
    Serial.println("on");
    bluetoothToggle = true;
    digitalWrite(LED, HIGH);
  } else {
    bluetoothToggle = false;
    digitalWrite(LED, LOW);
    Serial.println("off");
  }
  return bluetoothToggle;
}

void bluetoothController() {
  getControllerInput();
  input = packetbuffer[2] - '0';
    switch (input)
    {
    case 5: // forward
      moveForward(pwm);
      waitForButtonRelease();
      Serial.println("stopped");
      stop();
      break;
    case 6: // backwards
      moveBackwards(pwm);
      waitForButtonRelease();
      stop();
      break;
    case 7: // left
      moveLeft(pwm);
      waitForButtonRelease();
      stop();
      break;
    case 8:
      moveRight(pwm);
      waitForButtonRelease();
      stop();
      break;
    }
}
void getControllerInput()
{
  uint8_t length = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  uint8_t buttonNum = 0;
  if (length == 0)
  {
    // Serial.println("nothing");
    return;
  }
  if (packetbuffer[1] == 'B')
  {
    buttonNum = packetbuffer[2] - '0';       // converts from ASCII to numerical
    boolean pressed = packetbuffer[3] - '0'; // converts from ASCII to numerical
    Serial.print("Button ");
    Serial.print(buttonNum);
    if (pressed)
    {
      Serial.println(" pressed");
    }
    else
    {
      Serial.println(" released");
    }
  }
}
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

void waitForButtonRelease()
{
  while ((packetbuffer[3] - '0') == 1)
  {
    Serial.println("looping");
    if (ble.available())
    {
      getControllerInput();
    }
  }
}

bool getSwitchState() {
    return digitalRead(switchPin);

}