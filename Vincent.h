#ifndef VINCENT_H
#define VINCENT_H

#include <Arduino.h>
#include "EEPROM.h" // This needed to work with the onboard EEPROM.
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "U8glib.h"

void WritePassword(char *pw); // password needs to be passed in as a pointer

void ReadPassword(); // for debugging

bool CheckPassword(char *pw); // Check if password is true

bool LogOn(U8GLIB_SSD1306_128X64 u8g);



#endif
