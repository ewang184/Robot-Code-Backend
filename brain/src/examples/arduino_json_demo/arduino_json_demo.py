# Demonstrates sending and receiving JSON data from Arduino.
# Run this on any device that is connected to an Arduinos
import json
import serial
import time
from datetime import datetime


# Send JSON to Arduino
def send_json(ser):
    # Build a JSON Object
    json_object = {}
    json_object["command"] = "forwards"
    json_object["time of command"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    """ 
    Here is an example of a JSON object we created in the lines above   
    {
        "command":"forwards",
        "time of command":"2023-06-06 19:36:31"
    } 
    """

    # convert JSON to string and send to arduino
    json_string = json.dumps(json_object)
    json_string_encoded = json_string.encode('utf-8')

    ser.write(json_string_encoded)


# Read JSON received from Arduino
def read_json(ser):

    # Read incoming data from Serial
    try:
        raw_serial_data = ser.readline().decode('utf-8')

        # Format and print JSON received from Arduino
        try:
            json_data = json.loads(raw_serial_data)
            json_formatted_str = json.dumps(json_data, indent=2)

            print(json_formatted_str)
        except json.decoder.JSONDecodeError:
            print(
                "JSONDecodeError: try increasing serial timeout or "
                "check if serial data is being received."
            )
    except serial.serialutil.SerialException:
        print(
            "SerialException: make sure Arduino is connected and "
            "the right port is selected."
        )


if __name__ == "__main__":

    # Start a Serial connection
    ser = serial.Serial('/dev/ttyUSB0', baudrate = 115200, timeout=1.1)
    time.sleep(2) # Serial takes a few seconds to connect
    
    try:
        while True:
            send_json(ser) # Send JSON to Arduino
            read_json(ser) # Print JSON received back from Arduino
    except KeyboardInterrupt:
        ser.close()
