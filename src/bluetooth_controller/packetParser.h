#include <string.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_BluefruitLE_UART.h>
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLE.h"
#include <HardwareSerial.h>
#include "Adafruit_ATParser.h"


uint8_t readPacket(Adafruit_BluefruitLE_UART *ble_uart, uint16_t timeout);