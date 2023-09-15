import serial
import time

ser = serial.Serial('/dev/ttyUSB0', baudrate = 9600, timeout= 1)

# Send command from python to change speed of blink
while True:
    command = input()

    # y -> 200ms delay
    if command == 'y':
        ser.write(b'y')

    # n -> 1000ms delay
    elif command == 'n':
        ser.write(b'n')

    # n -> get sensor reading
    elif command == 'r':
        ser.write(b'r')
        print("send serial r")
        
        output = ser.readline()
        print(output)

    elif command == 'q':
        break
exit()
