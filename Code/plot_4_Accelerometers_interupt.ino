/*
    Edited by Best 16:09 27/01/63
*/


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

#define TCAADDR  0x70
#define TCAADDR1  0x71
#define CLICKTHRESHHOLD 60

Adafruit_LIS3DH lis1 = Adafruit_LIS3DH(); ; //Accelerometer 1
Adafruit_LIS3DH lis2 = Adafruit_LIS3DH(); ; //Accelerometer 2
Adafruit_LIS3DH lis3 ; //Accelerometer 3
Adafruit_LIS3DH lis4 ; //Accelerometer 4

void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
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
  //Serial.println("LIS3DH_1,1 test!");
  if (! lis1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  //Serial.println("LIS3DH_1,1 found!");

  lis1.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

  //Serial.print("Range = "); Serial.print(2 << lis1.getRange());
  //Serial.println("G");
  lis1.setClick(1, CLICKTHRESHHOLD);



  tcaselect(1);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  //Serial.println("LIS3DH_1,2 test!");
  if (! lis2.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  //Serial.println("LIS3DH_1,2 found!");

  lis2.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

  //Serial.print("Range = "); Serial.print(2 << lis2.getRange());
  //Serial.println("G");
  lis2.setClick(1, CLICKTHRESHHOLD);



  tcaselect(2);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  //Serial.println("LIS3DH_2,1 test!");
  if (! lis3.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  //Serial.println("LIS3DH_2,1 found!");

  lis3.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

  //Serial.print("Range = "); Serial.print(2 << lis3.getRange());
  //Serial.println("G");
  lis3.setClick(1, CLICKTHRESHHOLD);



  tcaselect(3);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  //Serial.println("LIS3DH_2,2 test!");
  if (! lis4.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  //Serial.println("LIS3DH_2,2 found!");

  lis4.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

  //Serial.print("Range = "); Serial.print(2 << lis4.getRange());
  //Serial.println("G");
  lis4.setClick(1, CLICKTHRESHHOLD);

}

float sen1, sen2, sen3, sen4;
uint8_t inter11, inter12, inter21, inter22;
uint8_t click;


void loop(void)
{
  inter = 0;
  long tstamp = millis();

  tcaselect(0);          /* Get a new sensor event */

  lis1.read();      // get X Y and Z data at once
  click = lis1.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
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
  click = lis2.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
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
  click = lis3.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
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
  click = lis4.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
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
  Serial.println(String(tstamp) + "," + String(sen1) + "," + String(sen2) + "," + String(sen3) + "," + String(sen4) + "," + String(inter));

  delay(20);
}
