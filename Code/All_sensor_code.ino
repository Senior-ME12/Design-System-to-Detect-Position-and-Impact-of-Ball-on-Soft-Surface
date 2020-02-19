#include <Wire.h>
extern "C" 
{ 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define TCAADDR 0x70
#define TCAADDR1 0x71
#define CLICKTHRESHHOLD 60

//Call Sensor Function
Adafruit_LIS3DH lis1; //Accelerometer 1
Adafruit_LIS3DH lis2; //Accelerometer 2
Adafruit_LIS3DH lis3; //Accelerometer 3
Adafruit_LIS3DH lis4; //Accelerometer 4
Adafruit_LIS3DH lis5; //Accelerometer 5
Adafruit_LIS3DH lis6; //Accelerometer 6
Adafruit_LIS3DH lis7; //Accelerometer 7
Adafruit_LIS3DH lis8; //Accelerometer 8
Adafruit_LIS3DH lis9; //Accelerometer 9
Adafruit_LIS3DH lis10; //Accelerometer 10
Adafruit_LIS3DH lis11; //Accelerometer 11
Adafruit_LIS3DH lis12; //Accelerometer 12
Adafruit_LIS3DH lis13; //Accelerometer 13
Adafruit_LIS3DH lis14; //Accelerometer 14
Adafruit_LIS3DH lis15; //Accelerometer 15
Adafruit_LIS3DH lis16; //Accelerometer 16


void tcaselect(uint8_t sensor) { 
  unsigned int mask = 1 << sensor;
  Wire.beginTransmission(TCAADDR1);
  Wire.write(lowByte(mask));
  Wire.endTransmission();
  Wire.beginTransmission(TCAADDR);
  //Wire.write(highByte(mask));
  Wire.write(mask);
  Wire.endTransmission();
  delay(1);
}

void tcaselect1(uint8_t sensor1) { 
  unsigned int mask1 = 1 << sensor1;
  Wire.beginTransmission(TCAADDR);
  Wire.write(lowByte(mask1));
  Wire.endTransmission();
  Wire.beginTransmission(TCAADDR1);
  //Wire.write(highByte(mask1));
  Wire.write(mask1);
  Wire.endTransmission();
  delay(1);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();  //enabling the I2C protocol through the Wire.begin()

  //FIRST SENSOR**                
  tcaselect(0);     
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_1 test!");
  if (! lis1.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_1 found!");
  
  lis1.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis1.getRange());  
  Serial.println("G");
  lis1.setClick(1, CLICKTHRESHHOLD);
  
  //SECOND SENSOR
  tcaselect(1);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_2 test!");
  if (! lis2.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_2 found!");
  
  lis2.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis2.getRange());  
  Serial.println("G");
  lis2.setClick(1, CLICKTHRESHHOLD);
  
  //THIRD SENSOR
  tcaselect(2);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_3 test!");
  if (! lis3.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_3 found!");
  
  lis3.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis3.getRange());  
  Serial.println("G");
  lis3.setClick(1, CLICKTHRESHHOLD);
  
  //FOURTH SENSOR
  tcaselect(3);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_4 test!");
  if (! lis4.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_4 found!");
  
  lis4.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis4.getRange());  
  Serial.println("G");
  lis4.setClick(1, CLICKTHRESHHOLD);
  
  //*FIFTH SENSOR
  tcaselect(4);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_5 test!");
  if (! lis5.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_5 found!");
  
  lis5.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis5.getRange());  
  Serial.println("G");
  lis5.setClick(1, CLICKTHRESHHOLD);

  
  //*SIXTH SENSOR
  tcaselect(5);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_6 test!");
  if (! lis6.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_6 found!");
  
  lis6.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis6.getRange());  
  Serial.println("G");
  lis6.setClick(1, CLICKTHRESHHOLD);
  
  
  //*SEVENTH SENSOR
  tcaselect(6);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_7 test!");
  if (! lis7.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_7 found!");
  
  lis7.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis7.getRange());  
  Serial.println("G");
  lis7.setClick(1, CLICKTHRESHHOLD);
  
  //*EIGHTH SENSOR
  tcaselect(7);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_8 test!");
  if (! lis8.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_8 found!");
  
  lis8.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis8.getRange());  
  Serial.println("G");
  lis8.setClick(1, CLICKTHRESHHOLD);

  Wire.beginTransmission(TCAADDR);
  Wire.write(0);
  Wire.endTransmission();
  
  
  //*NINETH SENSOR
  tcaselect1(0);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_9 test!");
  if (! lis9.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_9 found!");
  
  lis9.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis9.getRange());  
  Serial.println("G");
  lis9.setClick(1, CLICKTHRESHHOLD);

  
  //*TENTH SENSOR
  tcaselect1(1);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_10 test!");
  if (! lis10.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_10 found!");
  
  lis10.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis10.getRange());  
  Serial.println("G");
  lis10.setClick(1, CLICKTHRESHHOLD);


  //*11TH SENSOR
  tcaselect1(2);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_11 test!");
  if (! lis11.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_11 found!");
  
  lis11.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis11.getRange());  
  Serial.println("G");
  lis11.setClick(1, CLICKTHRESHHOLD);
  
  
  //*12TH SENSOR
  tcaselect1(3);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_12 test!");
  if (! lis12.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_12 found!");
  
  lis12.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis12.getRange());  
  Serial.println("G");
  lis12.setClick(1, CLICKTHRESHHOLD);
  
  //*13TH SENSOR
  tcaselect1(4);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_13 test!");
  if (! lis13.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_13 found!");
  
  lis13.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis13.getRange());  
  Serial.println("G");
  lis13.setClick(1, CLICKTHRESHHOLD);
  
  
  //*14TH SENSOR
  tcaselect1(5);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_14 test!");
  if (! lis14.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_14 found!");
  
  lis14.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis14.getRange());  
  Serial.println("G");
  lis14.setClick(1, CLICKTHRESHHOLD);
  
  
  //*15TH SENSOR
  tcaselect1(6);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_15 test!");
  if (! lis15.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_15 found!");
  
  lis15.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis15.getRange());  
  Serial.println("G");
  lis15.setClick(1, CLICKTHRESHHOLD);
  
  
  //*16TH SENSOR
  tcaselect1(7);  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("LIS3DH_16 test!");
  if (! lis16.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH_16 found!");
  
  lis16.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis16.getRange());  
  Serial.println("G");
  lis16.setClick(1, CLICKTHRESHHOLD);
  
  Wire.beginTransmission(TCAADDR1);
  Wire.write(0);
  Wire.endTransmission();
  
}

float sen1,sen2,sen3,sen4,sen5,sen6,sen7,sen8,sen9,sen10,sen11,sen12,sen13,sen14,sen15,sen16;
uint8_t inter;
uint8_t click;
void loop() 
{
  inter = 0;
  long tstamp = millis();
  
  //*SENSOR-FIRST
  tcaselect(0);          // Get a new sensor event
  lis1.read();      // get X Y and Z data at once
  click = lis1.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event1; 
  lis1.getEvent(&event1);
  sen1 = event1.acceleration.z;
  
  //*SENSOR-SECOND
  lis2.read();      // get X Y and Z data at once
  click = lis2.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event2; 
  lis2.getEvent(&event2);
  sen2 = event2.acceleration.z;

  
  //**SENSOR-THIRD
  lis3.read();      // get X Y and Z data at once
  click = lis3.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event3; 
  lis3.getEvent(&event3);
  sen3 = event3.acceleration.z;

  
  //*SENSOR-FOURTH
  lis4.read();      // get X Y and Z data at once
  click = lis4.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event4; 
  lis4.getEvent(&event4);
  sen4 = event4.acceleration.z;


  //*SENSOR-FIFTH
  lis5.read();      // get X Y and Z data at once
  click = lis5.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event5; 
  lis5.getEvent(&event5);
  sen5 = event5.acceleration.z;

  //*SENSOR-SIXTH
  lis6.read();      // get X Y and Z data at once
  click = lis6.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event6; 
  lis6.getEvent(&event6);
  sen6 = event6.acceleration.z;

  //*SENSOR-SEVENTH
  lis7.read();      // get X Y and Z data at once
  click = lis7.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event7; 
  lis7.getEvent(&event7);
  sen7 = event7.acceleration.z;

  //*SENSOR-8TH
  lis8.read();      // get X Y and Z data at once
  click = lis8.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event8; 
  lis8.getEvent(&event8);
  sen8 = event8.acceleration.z;
  

  
  Wire.beginTransmission(TCAADDR);
  Wire.write(0);
  Wire.endTransmission();


  //*SENSOR-9TH
  tcaselect1(0);
  lis9.read();      // get X Y and Z data at once
  click = lis9.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event9; 
  lis9.getEvent(&event9);
  sen9 = event9.acceleration.z;

  //*SENSOR-10TH
  tcaselect1(1);
  lis10.read();      // get X Y and Z data at once
  click = lis10.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event10; 
  lis10.getEvent(&event10);
  sen10 = event10.acceleration.z;

  //*SENSOR-11TH
  tcaselect1(2);
  lis11.read();      // get X Y and Z data at once
  click = lis11.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event11; 
  lis11.getEvent(&event11);
  sen11 = event11.acceleration.z;

  //*SENSOR-12TH
  tcaselect1(3);
  lis12.read();      // get X Y and Z data at once
  click = lis12.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event12; 
  lis12.getEvent(&event12);
  sen12 = event12.acceleration.z;

  //*SENSOR-13TH
  tcaselect1(4);
  lis13.read();      // get X Y and Z data at once
  click = lis13.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event13; 
  lis13.getEvent(&event13);
  sen13 = event13.acceleration.z;

  //*SENSOR-14TH
  tcaselect1(5);
  lis14.read();      // get X Y and Z data at once
  click = lis14.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event14; 
  lis14.getEvent(&event14);
  sen14 = event14.acceleration.z;

  //*SENSOR-15TH
  tcaselect1(6);
  lis15.read();      // get X Y and Z data at once
  click = lis16.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event15; 
  lis15.getEvent(&event15);
  sen15 = event15.acceleration.z;

  //*SENSOR-16TH
  tcaselect1(7);
  lis16.read();      // get X Y and Z data at once
  click = lis16.getClick();
  if (click & 0x10) {
    inter = 1;
  }
  else {
    inter = 0;
  }
  sensors_event_t event16; 
  lis16.getEvent(&event16);
  sen16 = event16.acceleration.z;
  Wire.beginTransmission(TCAADDR1);
  Wire.write(0);
  Wire.endTransmission();
  
  //Serial.println(String(tstamp)+","+String(sen1)+","+String(sen2)+","+String(sen3)+","+String(sen4)+","+String(sen5)+","+String(sen6)+","+String(sen7)+","+String(sen8)+","+String(sen9)+","+String(sen10)+","+String(sen11)+","+String(sen12)+","+String(sen13)+","+String(sen14)+","+String(sen15)+","+String(sen16)+"," + String(inter));
  Serial.println(String(sen1)+","+String(sen2)+","+String(sen3)+","+String(sen4)+","+String(sen5)+","+String(sen6)+","+String(sen7)+","+String(sen8)+","+String(sen9)+","+String(sen10)+","+String(sen11)+","+String(sen12)+","+String(sen13)+","+String(sen14)+","+String(sen15)+","+String(sen16)+"," + String(inter));
  //Serial.println(String(sen1)+","+String(sen2)+","+String(sen3)+","+String(sen4)+","+String(sen9)+","+String(sen10)+","+String(sen11)+","+String(sen12));
  //Serial.println(String(sen9)+","+String(sen10)+","+String(sen11)+","+String(sen12)+String(sen13)+","+String(sen14)+","+String(sen15)+","+String(sen16));
  delay(50);

}
