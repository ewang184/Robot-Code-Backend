# Util classes for debugging and testing new features

from pynput import keyboard

class KeyboardControl:
    def __init__(self, robot_client):
        self.robot_client = robot_client
        
        # https://pynput.readthedocs.io/en/latest/keyboard.html
        # Collect events until released
        with keyboard.Listener(
                on_press=self.on_press,
                on_release=self.on_release) as listener:
            listener.join()

    
    def on_press(self, key):
        try:
            print('\nalphanumeric key {0} pressed'.format(
                key.char))
        except AttributeError:
            print('\nspecial key {0} pressed'.format(
                key))


    def on_release(self, key):
        # WASD control, esc to exit
        try:        
            match key.char:
                case 'w':
                    self.robot_client.drive("forwards", 2000)
                case 'a':
                    self.robot_client.rotate("left", 2000)
                case 's':
                    self.robot_client.drive("backwards", 1000)
                case 'd':
                    self.robot_client.rotate("right", 1000)
                case 'e':
                    print(
                        "received sensor reading: ", 
                        self.robot_client.read_sensor_ultrasonic()
                    )
                case 'r':
                    print(
                        "received sensor reading: ", 
                        self.robot_client.read_sensor_voltage()
                    )
                case 't':
                    print(
                        "received sensor reading: ", 
                        self.robot_client.read_potentiometer_motor_offset()
                    )
        except:
            if key == keyboard.Key.esc:
                # Stop listener
                return False
