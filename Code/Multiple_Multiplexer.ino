#include <Wire.h>
extern "C" 
{ 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

//extern "C"
//uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
//{
//        if (!wait) return 4;
//        Wire.beginTransmission(2address);
//        while (length) {
//                Wire.write(*data++);
//                length--;
//        }
//        return Wire.endTransmission(sendStop);
//}

#define TCAADDR 0x70

#define TCAADDR1 0x71

Adafruit_LIS3DH lis1; //Accelerometer 1
Adafruit_LIS3DH lis2; //Accelerometer 2
Adafruit_LIS3DH lis3; //Accelerometer 3
Adafruit_LIS3DH lis4; //Accelerometer 4
Adafruit_LIS3DH lis5; //Accelerometer 5

String time;
long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
float second =  1000; // 1000 milliseconds in a second

void tcaselect(uint8_t sensor) { 
  unsigned int mask = 1 << sensor;
  Wire.beginTransmission(TCAADDR);
  Wire.write(lowByte(mask));
  Wire.endTransmission();
  Wire.beginTransmission(TCAADDR1);
  Wire.write(highByte(mask));
  Wire.endTransmission();
  delay(1);
}

void tcaselect1(uint8_t sensor) { 
  unsigned int mask = 1 << sensor;
  Wire.beginTransmission(TCAADDR);
  Wire.write(lowByte(mask));
  Wire.endTransmission();
  Wire.beginTransmission(TCAADDR1);
  Wire.write(highByte(mask));
  Wire.endTransmission();
  delay(1);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();  //enabling the I2C protocol through the Wire.begin()

  //FIRST SENSOR**                
  tcaselect(0);    /* Display some basic information on this sensor */
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_1,1 test!");
  if (! lis1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_1,1 found!");
  
  lis1.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis1.getRange());  
  Serial.println("G");


  //SECOND SENSOR
  tcaselect(1);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_1,2 test!");
  if (! lis2.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_1,2 found!");
  
  lis2.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis2.getRange());  
  Serial.println("G");

  //THIRD SENSOR
   tcaselect(2);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_2,1 test!");
  if (! lis3.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_2,1 found!");
  
  lis3.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis3.getRange());  
  Serial.println("G");

  
  //FOURTH SENSOR
  tcaselect(3);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_2,2 test!");
  if (! lis4.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_2,2 found!");
  
  lis4.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis4.getRange());  
  Serial.println("G");


  Wire.beginTransmission(TCAADDR);
  Wire.write(0);
  Wire.endTransmission();

  //*FIFTH SENSOR
  tcaselect1(2);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_0,0 test!");
  if (! lis5.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_0,0 found!");
  
  lis5.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis5.getRange());  
  Serial.println("G");
  
}
float sen1,sen2,sen3,sen4,sen5;
void loop() 
{
  long tstamp = millis();
  int days = tstamp / day ;                                //number of days
  int hours = (tstamp % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
  int minutes = ((tstamp % day) % hour) / minute ;         //and so on...
  float seconds = (((tstamp % day) % hour) %  minute)/ second ;
  time = String(String(days)+","+String(hours)+":"+String(minutes)+":"+String(seconds));

  //SENSOR-FIRST
  tcaselect(0);          /* Get a new sensor event */
  lis1.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis1.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis1.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis1.z); 
  sensors_event_t event1; 
  lis1.getEvent(&event1);
  sen1 = event1.acceleration.z;
  
  //*SENSOR-SECOND
  lis2.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis2.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis2.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis2.z); 
  sensors_event_t event2; 
  lis2.getEvent(&event2);
  sen2 = event2.acceleration.z;

  
  //**SENSOR-THIRD
  lis3.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis2.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis2.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis2.z); 
  sensors_event_t event3; 
  lis3.getEvent(&event3);
  sen3 = event3.acceleration.z;

  
  //*SENSOR-FOURTH
  lis4.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis4.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis4.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis4.z); 
  sensors_event_t event4; 
  lis4.getEvent(&event4);
  sen4 = event4.acceleration.z;

  Wire.beginTransmission(TCAADDR);
  Wire.write(0);
  Wire.endTransmission();


  //*SENSOR-FIFTH
  tcaselect1(2);
  lis5.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis5.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis5.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis5.z); 
  sensors_event_t event5; 
  lis5.getEvent(&event5);
  sen5 = event5.acceleration.z;

  
  Serial.println(String(time)+","+String(sen1)+","+String(sen2)+","+String(sen3)+","+String(sen4)+","+String(sen5));
  //Serial.println(String(time)+","+String(sen5));
  delay(20);

}
