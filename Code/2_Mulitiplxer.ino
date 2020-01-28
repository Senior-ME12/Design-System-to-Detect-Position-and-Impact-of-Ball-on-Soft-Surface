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
//#define TCAADDR1  0x71

Adafruit_LIS3DH lis1 = Adafruit_LIS3DH(); ; //Accelerometer 1
Adafruit_LIS3DH lis2 = Adafruit_LIS3DH(); ; //Accelerometer 2
Adafruit_LIS3DH lis3 = Adafruit_LIS3DH(); ; //Accelerometer 3
Adafruit_LIS3DH lis4 = Adafruit_LIS3DH(); ; //Accelerometer 4
Adafruit_LIS3DH lis5 = Adafruit_LIS3DH(); ; //Accelerometer 5

String time;
long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
float second =  1000; // 1000 milliseconds in a second

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
void tcaselect1(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(0x71);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


void setup(void)
{
  Serial.begin(115200);
  Wire.begin();

  // Set measurement range
  // Ga: LIS2DH12_RANGE_2GA
  // Ga: LIS2DH12_RANGE_4GA
  // Ga: LIS2DH12_RANGE_8GA
  // Ga: LIS2DH12_RANGE_16GA

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
  
  
  tcaselect1(0);
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
void loop(void)
{

  long tstamp = millis();
  int days = tstamp / day ;                                //number of days
  int hours = (tstamp % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
  int minutes = ((tstamp % day) % hour) / minute ;         //and so on...
  float seconds = (((tstamp % day) % hour) %  minute)/ second ;
  time = String(String(days)+","+String(hours)+":"+String(minutes)+":"+String(seconds));

  tcaselect(0);          /* Get a new sensor event */
  
  lis1.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis1.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis1.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis1.z); 
  sensors_event_t event1; 
  lis1.getEvent(&event1);
  
  /* Display the results (acceleration is measured in m/s^2) */
  //Serial.print("X1: "); Serial.print(event1.acceleration.x);
  //Serial.print("  \tY1: "); Serial.print(event1.acceleration.y); 
  //Serial.print("  \tZ1: "); Serial.print(event1.acceleration.z); 
  //sen1 = sqrt(pow(event1.acceleration.x,2)+pow(event1.acceleration.y,2)+pow(event1.acceleration.z,2));
  sen1 = event1.acceleration.z;

  

  tcaselect(1);
  lis2.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis2.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis2.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis2.z); 
  sensors_event_t event2; 
  lis2.getEvent(&event2);
  
  /* Display the results (acceleration is measured in m/s^2) */
  //Serial.print("X2: "); Serial.print(event2.acceleration.x);
  //Serial.print("  \tY2: "); Serial.print(event2.acceleration.y); 
  //Serial.print("  \tZ2: "); Serial.print(event2.acceleration.z); 
  //sen2 = sqrt(pow(event2.acceleration.x,2)+pow(event2.acceleration.y,2)+pow(event2.acceleration.z,2));
  sen2 = event2.acceleration.z;

  
  tcaselect(2);
  lis3.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis2.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis2.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis2.z); 
  sensors_event_t event3; 
  lis3.getEvent(&event3);
  
  /* Display the results (acceleration is measured in m/s^2) */
  //Serial.print("X3: "); Serial.print(event2.acceleration.x);
  //Serial.print("  \tY3: "); Serial.print(event2.acceleration.y); 
  //Serial.print("  \tZ3: "); Serial.print(event2.acceleration.z); 
  //sen3 = sqrt(pow(event3.acceleration.x,2)+pow(event3.acceleration.y,2)+pow(event3.acceleration.z,2));
  sen3 = event3.acceleration.z;



  tcaselect(3);
  lis4.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis4.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis4.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis4.z); 
  sensors_event_t event4; 
  lis4.getEvent(&event4);
  
  /* Display the results (acceleration is measured in m/s^2) */
  //Serial.print("X4: "); Serial.print(event2.acceleration.x);
  //Serial.print("  \tY4: "); Serial.print(event2.acceleration.y); 
  //Serial.print("  \tZ4: "); Serial.print(event2.acceleration.z); 
  //sen4 = sqrt(pow(event4.acceleration.x,2)+pow(event4.acceleration.y,2)+pow(event4.acceleration.z,2));
  sen4 = event4.acceleration.z;



  tcaselect1(0);
  lis5.read();      // get X Y and Z data at once
  // Then print out the raw data
  //Serial.print("X:  "); //Serial.print(lis4.x); 
  //Serial.print("  \tY:  "); //Serial.print(lis4.y); 
  //Serial.print("  \tZ:  "); //Serial.print(lis4.z); 
  sensors_event_t event5; 
  lis5.getEvent(&event5);
  
  /* Display the results (acceleration is measured in m/s^2) */
  //Serial.print("X4: "); Serial.print(event2.acceleration.x);
  //Serial.print("  \tY4: "); Serial.print(event2.acceleration.y); 
  //Serial.print("  \tZ4: "); Serial.print(event2.acceleration.z); 
  //sen4 = sqrt(pow(event4.acceleration.x,2)+pow(event4.acceleration.y,2)+pow(event4.acceleration.z,2));
  sen5 = event5.acceleration.z;





  //Serial.print("Accel 1,1:  ");
  //Serial.print(sen1);
  //Serial.print(" m/s^2 ");

  //Serial.print("  \tAccel 1,2:  ");
  //Serial.print("  ");
  //Serial.print(sen2);
  //Serial.println(" m/s^2 ");
  
  //Serial.print("  \tAccel 2,1:  ");
  //Serial.print("  ");
  //Serial.print(sen3);
  //Serial.println(" m/s^2 ");

  //Serial.print("  \tAccel 2,2:  ");
  //Serial.print("  ");
  //Serial.print(sen4);
  //Serial.println(" m/s^2 ");
  //sen4 = random(8,11);
  Serial.println(String(time)+","+String(sen1)+","+String(sen2)+","+String(sen3)+","+String(sen4)+","+String(sen5));
  
  delay(10);
}
