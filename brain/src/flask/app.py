# Forwards messages from Pi to the Arduino (execute 'flask run' on the pi)
from flask import Flask, request
import serial

serial_port = '/dev/ttyUSB0'
try:
    ser = serial.Serial(serial_port, baudrate = 115200, timeout=1.1)
except:
    ser = None

app = Flask(__name__)

@app.route("/")
def hello():
    return "<p>Connected</p>"

# each endpoint will send a unique robot command through serial to the arduino 
@app.route("/y")
def send_y():
    if ser is not None:
        ser.write(b'y')
    print("send serial y")
    return "<p>send serial y</p>"

@app.route("/n")
def send_n():
    if ser is not None:
        ser.write(b'n')
    print("send serial n")
    return "<p>send serial n</p>"

@app.route("/r")
def send_r():
    if ser is not None:
        ser.write(b'r')
        
        output = str(ser.readline())
        print(output)
        return {
            "output" : output,
        }
    print("send serial r")
    return "<p>send serial r</p>"

@app.route("/command", methods=['GET', 'POST'])
def send_command():
    # JSON string received from POST request
    content = request.get_json(silent=True)
    
    # send encoded JSON string to serial
    if ser is not None:
        ser.write(content.encode('utf-8'))
        response = ser.readline()
    
    print(f"send to serial: {content}")

    return response
