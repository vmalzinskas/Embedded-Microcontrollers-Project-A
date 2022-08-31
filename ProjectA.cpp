// Group 50 Project A
#include "Vincent.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g; // initializing the OLED screen

//Global variables
char Password[8]{"EEE20003"}; //The password string
float * AccVec();
float * Vadd{};
float forceVec[3]{};
bool pass{false};

void setup() 
{
  Serial.begin(115200);
  u8g.setFont(u8g_font_tpss); //setting the text font
  u8g.setColorIndex(1); // setting colour to white

  WritePassword(Password); // Password should only need to be written the first time the board is programmed, I haven't tried to test this in the simulation.
  
  while(!pass)
  {
  pass = LogOn(u8g);
  } 


}

void loop() {

Vadd=AccVec();
forceVec[0]=*Vadd;
forceVec[1]=*(Vadd+1);
forceVec[2]=*(Vadd+2);
/*
Serial.print("x= "); 
Serial.println(*Vadd);
Serial.print("y= ");
Serial.println(forceVec[1]);
Serial.print("z= ");
Serial.println(forceVec[2]);
*/
  u8g.firstPage();  
  do {
    //changing screen colour if ACC is too high (possible fall) doesnt work
    if(abs(forceVec[0]) > 19 || abs(forceVec[1]) > 19 || abs(forceVec[2]) > 19 ){
      u8g.setColorIndex(3);
    }
    else{
      u8g.setColorIndex(1);
    }
    
    u8g.drawFrame(64, 0, 64, 64);
    u8g.drawStr(0, 10, "X =");
    String strX = String(*Vadd);
    char charX[7];
    strX.toCharArray(charX, 7);
    u8g.drawStr(30, 10, charX);

    u8g.drawStr(0,38, "Y =");
    String strY = String(*(Vadd+1));
    char charY[7];
    strY.toCharArray(charY, 7);
    u8g.drawStr(30, 38, charY);

    u8g.drawStr(0, 64, "Z =");
    String strZ = String(*(Vadd+2));
    char charZ[7];
    strZ.toCharArray(charZ, 7);
    u8g.drawStr(30, 64, charZ);
    
    u8g.drawDisc(96 + forceVec[0] * 0.8, 32 + forceVec[1] * 0.8, (22 + forceVec[2]) * 0.3);

    

  } while( u8g.nextPage() );

}

////////////////////////////
float * AccVec()
{
  Adafruit_MPU6050 gyro;
  while (!gyro.begin()) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }
  sensors_event_t event;

  float vector[3]{};
  float * vecPt{vector};

  gyro.getAccelerometerSensor()->getEvent(&event);

  vector[0]=static_cast<float>(event.acceleration.x);
  vector[1]=static_cast<float>(event.acceleration.y);
  vector[2]=static_cast<float>(event.acceleration.z);


  return vecPt;
  
}


///////////////////////////



