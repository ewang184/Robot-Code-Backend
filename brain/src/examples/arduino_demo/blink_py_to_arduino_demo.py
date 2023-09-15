import serial
import time

ser = serial.Serial('/dev/ttyUSB0', baudrate = 9600, timeout= 1)

# Alternate between fast and slow blink while python script is running
while True:
    ser.write(b'y')
    time.sleep(5) 
    
    ser.write(b'n')
    time.sleep(5)
exit()