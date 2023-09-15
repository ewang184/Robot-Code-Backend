import time
from util import KeyboardControl

class Navigation:
    def __init__(self, robot_client=None, computer_vision=None):

        if robot_client is not None:
            self.robot_client = robot_client

        if computer_vision is not None:
            self.computer_vision = computer_vision

    def start_keyboard_control(self):
        KeyboardControl(self.robot_client)
