# Main file for robot Brain (run this on a laptop or machine external to the robot)

# Discover modules from lib folder
import sys
import os
sys.path.insert(1, os.path.join(sys.path[0], '../lib'))

from computer_vision import ComputerVision
from navigation import Navigation
from robot_client import RobotClient

flower_bot_ip = 'http://raspberrypi:5000'

if __name__ == "__main__":
    flower_bot = RobotClient(flower_bot_ip)
    flower_bot_cv = ComputerVision
    flower_bot_nav = Navigation(flower_bot, flower_bot_cv)

    #flower_bot_nav.drive_to_flower()
    flower_bot_nav.start_keyboard_control()
