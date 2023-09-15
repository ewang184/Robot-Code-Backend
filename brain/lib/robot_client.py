# Creates a connection to the robot.
from datetime import datetime
import requests
import urllib3
import json

# Suppress the warnings from urllib3
urllib3.disable_warnings(category=urllib3.exceptions.InsecureRequestWarning)

# Takes robot ip address and creates a new connection 
class RobotClient:
    def __init__(self, robot_ip):
        self.robot_ip = robot_ip


    # each function sends a request to a unique flask endpoint
    # each request sent to an endpoint represents a robot command
    def send_y(self):
        print('y')
        try:
            requests.get(self.robot_ip + '/y', verify = False)
        except:
            print("An exception occurred from sending y")


    def send_n(self):
        print('n')
        try:
            requests.get(self.robot_ip + '/n', verify = False)
        except:
            print("An exception occurred from sending n")


    def send_r(self):
        print('r')
        try:
            response = requests.get(self.robot_ip + '/r', verify = False)
            return(response)
        except:
            print("An exception occurred from sending r")
        return None


    def send_angle(self, angle):
        #accepts positive/negative angle
        #positive angle turn left, negative angle turn right

        print(angle)
        try:
            response = requests.get(self.robot_ip + '/'+"angle:"+str(angle), verify = False)
            return response
        except:
            print("exception from sending angle")
        return None


    def send_forward(self, distance):
        #accepts positive/negative distance
        print(distance)
        try:
            response = requests.get(self.robot_ip + '/'+"distance:"+str(distance), verify = False)
            return response
        except:
            print("exception from sending forward")
        return None


    # send a command to robot endpoint
    def send_command(self, command):
        print("SEND COMMAND:", command)
        try:
            # convert command dictionary to JSON string
            json_string = json.dumps(command)

            # send request
            response = requests.post(self.robot_ip + '/command', json = json_string)
            
            # process response
            response_decoded = response.content.decode('utf-8')
            print("RESPONSE:", response_decoded)
            return response_decoded
        except:
            print("exception from sending command")
        return None


    ## Move forwards and backwards
    # Example: drive("forwards", 10)
    def drive(self, direction, distance):
        # Build a command as dictionary
        command = {}
        command["command"] = "drive"
        command["direction"] = direction
        command["distance"] = distance
        command["time of command"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.send_command(command)


    ## Rotate clockwise or counterclockwise
    # Example: rotate("clockwise", 5)
    def rotate(self, direction, angle):
        # Build a command as dictionary
        command = {}
        command["command"] = "rotate"
        command["direction"] = direction
        command["angle"] = angle
        command["time of command"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.send_command(command)

    ## Return most recent reading from ultrasonic sensor
    def read_sensor_ultrasonic(self):
        # Build a command as dictionary
        command = {}
        command["command"] = "read_sensor_ultrasonic"
        command["time of command"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Send the command and return the response
        try:
            raw_serial_data = self.send_command(command)
            json_data = json.loads(raw_serial_data)
            return json_data["sensor_reading"]
        except:
            return None
        
    ## Return most recent reading from voltage sensor
    def read_sensor_voltage(self):
        # Build a command as dictionary
        command = {}
        command["command"] = "read_sensor_voltage"
        command["time of command"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Send the command and return the response
        try:
            raw_serial_data = self.send_command(command)
            json_data = json.loads(raw_serial_data)
            return json_data["sensor_reading"]
        except:
            return None
        
    ## Return most recent reading from potentiometer and motor offset
    def read_potentiometer_motor_offset(self):
        # Build a command as dictionary
        command = {}
        command["command"] = "read_potentiometer_motor_offset"
        command["time of command"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Send the command and return the response
        try:
            raw_serial_data = self.send_command(command)
            json_data = json.loads(raw_serial_data)
            return json_data["sensor_reading"]
        except:
            return None
