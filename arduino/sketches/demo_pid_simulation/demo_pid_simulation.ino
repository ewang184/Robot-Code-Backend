// simulation of PID motor control (may not reflect real-world implementation)

#include <Arduino_FreeRTOS.h>
#include <PID_v1.h>

// PID variables
double Setpoint, Input, Output;
double Kp=0.1, Ki=6, Kd=0; //Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// motor variables
float motor_speed = 0; // actual motor speed

void fake_digital_write(double value) {
  motor_speed = value;
}

double fake_read_sensor_speed() {
  delay(100); // simulate delay for counting speed sensor pulses
  return motor_speed;
}

// define two tasks for Debug & RampSpeed
void TaskDebug( void *pvParameters );
void TaskRampSpeed( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  xTaskCreate(
    TaskRampSpeed
    ,  "RampSpeed"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskRampSpeed(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // Initialize PID variables
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  for (;;)
  {
    if (Serial.available() > 0) {
      String incomingString = Serial.readStringUntil('\n');
      Setpoint = incomingString.toDouble();
    }

    Input = fake_read_sensor_speed();
    myPID.Compute();
    fake_digital_write(Output);

    Serial.println(
      "motor_speed:" + String(motor_speed) + "," + 
      "set_speed:" + String(Setpoint) + ","
    );
  }
}
