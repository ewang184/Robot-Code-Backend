// Extracts properties from JSON object received through serial and 
// sends a JSON object back

// https://arduinojson.org/
#include <ArduinoJson.h>

// Allocate the JSON document
//
// Inside the brackets, 200 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<200> input_json;
StaticJsonDocument<200> output_json;

// StaticJsonObject allocates memory on the stack, it can be
// replaced by DynamicJsonDocument which allocates in the heap.
//
// DynamicJsonDocument  input_json(200);

void setup() {
  // enable debug led
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize Serial port
  Serial.begin(115200);
  while (!Serial) continue;
}

void loop() {

  while (Serial.available() == 0) {}     //wait for data available

  digitalWrite(LED_BUILTIN, HIGH); // flash debug led
  digitalWrite(LED_BUILTIN, LOW); 

  // https://arduinojson.org/v6/issues/memory-leak/
  input_json.clear();
  output_json.clear();

  String raw_serial_data = Serial.readString();  //read until timeout
  raw_serial_data.trim();                        // remove any \r \n whitespace at the end of the String

  // Deserialize the received JSON object
  DeserializationError error = deserializeJson(input_json, raw_serial_data);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Read properties from received JSON object
  const char* command = input_json["command"];
  const char* time_of_command = input_json["time of command"];

  // Add values in the output JSON document
  output_json["last received command"] = command;
  output_json["time of last received command"] = time_of_command;

  // Add an array.
  JsonArray sensor_reading = output_json.createNestedArray("sensor_reading");
  sensor_reading.add(48.756080);
  sensor_reading.add(2.302038);
  
  // Generate the minified JSON and send it to the Serial port.
  serializeJson(output_json, Serial);
  // The above line prints:
  // {"last received command":command,"sensor_reading":[48.756080,2.302038]}

  digitalWrite(LED_BUILTIN, HIGH);

}
