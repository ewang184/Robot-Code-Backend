// Code to control the robot (functions to read/write to pins on the Arduino)

// Allocate JSON document for return values
StaticJsonDocument<200> output_json;

void drive(String direction, int distance) {
  output_json.clear();

  // Add values in the output JSON document
  output_json["command result"] = "drive " + String(distance) + " " + direction;

  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {"command result":command}

  // Run the code to drive the robot  
  //turn motor in one direction
  int offset_output = 25 * analogRead(potentiometer1) / 100;
  if(direction == "forwards") {
    analogWrite(en1, offset_output);
    analogWrite(en2, 200);
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 

  } else {
    analogWrite(en1, offset_output);
    analogWrite(en2, 200);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
   
  delay(distance);

  // stop motor
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}

void rotate(String direction, int angle) {
  output_json.clear();

  // Add values in the output JSON document
  output_json["command result"] = "rotate " + String(angle) + " " + direction;
  
  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {"command result":command}

  // Run the code to rotate the robot
  //turn motor in one direction
  if(direction == "left") {
    analogWrite(en1, 200);
    analogWrite(en2, 200);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else {
    analogWrite(en1, 200);
    analogWrite(en2, 200);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
   
  delay(angle);

  // stop motor
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}

void read_sensor_ultrasonic() {
  output_json.clear();

  // Add values in the output JSON document
  output_json["command result"] = "read ultrasonic sensor";

  //------ Read sensor data and add it to response object. ------//

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  long duration, cm;
  duration = pulseIn(echoPin1, HIGH);

  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  output_json["sensor_reading"] = cm;
  output_json["sensor_reading_units"] = "cm";

  //------ SECTION END ------//


  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {"command result":"read ultrasonic sensor","sensor_reading":0,"sensor_reading_units":"cm"}
}

volatile int pulses = 0;
unsigned long lastDisplayTime = 0;
void countPulse()
{
  pulses++;
}

void read_sensor_speed() {
  output_json.clear();

  // Add values in the output JSON document
  output_json["command result"] = "read speed sensor";

  // Read dummy sensor data and add it to an array.
  int reading_1 = 48.756080; // TODO: replace this with actual readings from a sensor
  int reading_2 = 2.302038;  // maybe add a parameter to specify sensor pin
  JsonArray sensor_reading = output_json.createNestedArray("dummy_hardcoded_sensor_reading");
  sensor_reading.add(reading_1);
  sensor_reading.add(reading_2);

  //------ Read sensor data and add it to response object. ------//
  
  attachInterrupt(
    digitalPinToInterrupt(digitalPin1),
    countPulse,
    FALLING
  );
  
  while (true) {
    unsigned long currentTime = millis();

    // Calculate RPM continuously
    float rpm = (float)pulses * (60000.0 / (currentTime - lastDisplayTime)) / 20.0;

    // Display RPM every 500ms
    if (currentTime - lastDisplayTime >= 500)
    {
      output_json["sensor_reading_units"] = "RPM";
      output_json["sensor_reading"] = rpm;

      lastDisplayTime = currentTime; // Update the last display time
      pulses = 0;                    // Reset pulse count
      break;
    }
  }

  //------ SECTION END ------//

  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {sensor_reading":[48.756080,2.302038]}
}

double get_sensor_voltage() {
  // Floats for ADC voltage & Input voltage
  float adc_voltage = 0.0;
  float in_voltage = 0.0;
  
  // Floats for resistor values in divider (in ohms)
  float R1 = 30000.0;
  float R2 = 7500.0; 
  
  // Float for Reference Voltage
  float ref_voltage = 5.0;
  
  // Integer for ADC value
  int adc_value = 0;

  // Read the Analog Input
  adc_value = analogRead(voltageSensor1);
  
  // Determine voltage at ADC input
  adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
  
  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2/(R1+R2)) ; 
  
  // Append voltage rounded to 2 decimal places
  in_voltage = (int)(in_voltage * 100 + .5); // convert to integer to cut off decimals
  return (float)in_voltage / 100;
}

void read_sensor_voltage() {
  output_json.clear();

  // Add values in the output JSON document
  output_json["command result"] = "read voltage sensor";

  //------ Read sensor data and add it to response object. ------//
  output_json["sensor_reading"] = get_sensor_voltage();
  output_json["sensor_reading_units"] = "V";
  output_json["robot_enable"] = robot_enable;

  //------ SECTION END ------//

  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {"command result":"read voltage sensor","sensor_reading":0,"sensor_reading_units":"V"}
}

void read_potentiometer_motor_offset() {
  output_json.clear();

  // Add values in the output JSON document
  output_json["command result"] = "read potentiometer and motor offset";

  //------ Read sensor data and add it to response object. ------//
  output_json["sensor_reading"] = analogRead(potentiometer1);
  output_json["offset_output"] = offset_output;

  //------ SECTION END ------//

  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {"command result":"read motor offset","potentiometer_reading":0,"offset_output":"0"}
}

/// @brief Calls the corresponding function given a command in JSON.
/// @param commandJson Command in JSON.
void run_command(StaticJsonDocument<200> commandJson) {
  // Extract the command value from the JSON object
  String command = commandJson["command"];

  // Call the corresponding function.
  if(command == "drive") drive(
    commandJson["direction"],
    commandJson["distance"]
  );
  if(command == "rotate") rotate(
    commandJson["direction"],
    commandJson["angle"]
  );
  if(command == "read_sensor_ultrasonic") read_sensor_ultrasonic();
  if(command == "read_sensor_speed") read_sensor_speed();
  if(command == "read_sensor_voltage") read_sensor_voltage();
  if(command == "read_potentiometer_motor_offset") read_potentiometer_motor_offset();
}
