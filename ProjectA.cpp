//This is Group 50 Project A
#include "EEPROM.h" // This needed to work with the onboard EEPROM.

//Global variables
char Password[8]{"EEE20003"}; //The password string

//Prototypes
void WritePassword(char *);
void ReadPassword(); // Read is mostly for debugging 
bool CheckPassword(char *);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WritePassword(Password); // Password should only need to be written the first time the board is programmed, I haven't tried to test this in the simulation.
  //ReadPassword();
  Serial.println(CheckPassword("EEE20003")); //Prints to console a 1 or zero if the argument matches/(or not) to the saved data in the first 8bytes of EEEPROM memory.
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
