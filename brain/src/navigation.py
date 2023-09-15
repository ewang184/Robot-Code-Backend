import time
from util import KeyboardControl

class Navigation:
    def __init__(self, robot_client=None, computer_vision=None):

        if robot_client is not None:
            self.robot_client = robot_client

        if computer_vision is not None:
            self.computer_vision = computer_vision


    def drive_to_flower(self):
        # blink the led
        if self.robot_client is not None:
            while True:
                self.robot_client.send_y()
                self.robot_client.send_forward(12)
                self.robot_client.send_forward(-12)
                time.sleep(1)
                self.robot_client.send_n()
                self.robot_client.send_angle(11)
                self.robot_client.send_angle(-11)
                time.sleep(1)


    def start_keyboard_control(self):
        KeyboardControl(self.robot_client)
