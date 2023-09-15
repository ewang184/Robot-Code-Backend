# Discover modules from lib folder
import sys
import os
sys.path.insert(1, os.path.join(sys.path[0], '../../../../lib'))

# Note: Use this script on external machine that is not on the robot (laptop, server, etc.)
import time
from robot_client import RobotClient

# Create new connection to robot
robot = RobotClient('http://raspberrypi:5000')

# repeatedly requests for sensor reading
while True:
    response = robot.send_r()
    
    # send_r() returns None when there is an exception (request failed)
    if response is not None:
        print("output:", response.json()["output"])
    time.sleep(1)
