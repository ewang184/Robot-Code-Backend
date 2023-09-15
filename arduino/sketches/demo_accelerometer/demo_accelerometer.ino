#include <Wire.h>                 // Must include Wire library for I2C'
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

MMA8452Q accel; // Default MMA8452Q object create. (Address = 0x1D)

void setup() {
  // put your setup code here, to run once:
accel.init();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
accel.read();
float xAcceleration = accel.cx;
float yAcceleration = accel.cy;
float zAcceleration = accel.cz;
zAcceleration = zAcceleration -1;
Serial.print("X Acceleration: ");
Serial.println(xAcceleration);
Serial.print("Y acceleration: ");
Serial.println(yAcceleration);
Serial.print("Z Acceleration: ");
Serial.println(zAcceleration);
delay(500);
}