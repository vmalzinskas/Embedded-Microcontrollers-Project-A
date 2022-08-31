#include "EEPROM.h" // This needed to work with the onboard EEPROM.
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "U8glib.h"

void WritePassword(char *pw) // password needs to be passed in as a pointer
{
	for(int i=0;i<8;i++) //write 8 bytes from *pw (password) to the EEEPROM
	{
	EEPROM.write(i,*(pw+i)); //The first argument is the byte on the EEEPROM that is being written to (Address 0-1020 I think), second argument is the password char being written.
	}
}

void ReadPassword() // for debugging
{

  char password[8]{};
  	for(int i=0;i<8;i++) //write 8 bytes from *pw (password) to the EEEPROM
	{
	  password[i]=EEPROM.read(0+i);
	}
  Serial.print(password); // We can print to the screen the password saved in the EEEPROM so we can manually check it is correct.

}

bool CheckPassword(char *pw) // Check if password is true
{
    char password[8]{};
  	for(int i=0;i<8;i++) //write 8 bytes from *pw (password) to the EEEPROM
    {
      if(*(pw+i)!=EEPROM.read(0+i)) return false; // if all bytes match then it will exit this if and return true, if bytes don't match false is returned.
    }
    return true;
}

bool LogOn(U8GLIB_SSD1306_128X64 u8g) // take an entered password
{
  char password[8]{};
  char inputBuff[64]{};
  Serial.println("Enter Password: ");
  u8g.firstPage();  
  do {
    u8g.drawStr(20,20,"Enter password ");
  } while( u8g.nextPage() );
 
  
  while(Serial.available()<1);
  Serial.readBytesUntil('\n', inputBuff, 64);

 
  password[0] = inputBuff[0];
  
  password[1] = inputBuff[1];
  
  password[2] = inputBuff[2];
 
  password[3] = inputBuff[3];
 
  password[4] = inputBuff[4];
  
  password[5] = inputBuff[5];
  
  password[6] = inputBuff[6];
  
  password[7] = inputBuff[7];


  //Serial.println(password);

  return CheckPassword(password);

}
