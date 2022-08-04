//This is Group 50 Project A
#include "EEPROM.h" // This needed to work with the onboard EEPROM.

//Global variables
char Password[8]{"EEE20003"};

//Prototypes
void WritePassword(char *);
void ReadPassword();
bool CheckPassword(char *);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
  WritePassword(Password);
  //ReadPassword();
  Serial.println(CheckPassword("EEE20003"));
}

void loop() {
  // put your main code here, to run repeatedly:

}

///////////
//Functions
///////////

void WritePassword(char *pw) // password needs to be passed in as a pointer
{
	for(int i=0;i<8;i++) //write 8 bytes from *pw (password) to the EEEPROM
	{
	EEPROM.write(i,*(pw+i));
	}
}

void ReadPassword() // for debugging
{
  char password[8]{};
  	for(int i=0;i<8;i++) //write 8 bytes from *pw (password) to the EEEPROM
	{
	  password[i]=EEPROM.read(0+i);
	}
  Serial.print(password);
}
bool CheckPassword(char *pw) // Check if password is true
{
    char password[8]{};
  	for(int i=0;i<8;i++) //write 8 bytes from *pw (password) to the EEEPROM
    {
      if(*(pw+i)!=EEPROM.read(0+i)) return false;
    }
    return true;
}