// Main code for the Arduino.
#include <Arduino.h>

// https://arduinojson.org/
#include <ArduinoJson.h>

// False if pack is below 3.2V x 2
bool robot_enable = true;

#include "robot_pin_definitions.h"
#include "util.h"
#include "robot_commands.h"
#include "process_command.h"

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while (!Serial) continue; // wait for serial to initialize
  
  // Initialize L298N motor controller 1
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize SR04 ultrasonic sensor 1
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Initialize LM393 Speed Sensor Digital Output
  pinMode(digitalPin1, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available() == 0) {}            // wait for data available
  String raw_serial_data = Serial.readString(); // read until timeout
  raw_serial_data.trim();                       // remove any \r \n whitespace at the end of the String

  process_command(raw_serial_data);

  // low if true
  robot_enable = get_sensor_voltage() > 6.4;
}
