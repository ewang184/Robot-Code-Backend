// Extracts properties from JSON object received through serial and 
// sends a JSON object back.

// Allocate JSON documents.
// Use https://arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<200> command_json;

/// @brief Processes a command in JSON string format.
/// @param raw_serial_data Command in JSON string format. Example: {"command":"forwards","time of command":"2023-06-06 19:36:31"}
void process_command(String raw_serial_data) {
  // https://arduinojson.org/v6/issues/memory-leak/#solution-2-clear-the-jsondocument
  command_json.clear();

  // Deserialize the received JSON object
  DeserializationError error = deserializeJson(command_json, raw_serial_data);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Run command
  run_command(command_json);
}
