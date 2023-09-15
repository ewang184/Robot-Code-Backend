// PID control and reading speed sensor at same time (both sides)

#include <Arduino_FreeRTOS.h>
#include <PID_v1.h>
//#include "lm393_speed_sensor.h"

// potentiometer
#define POTENTIOMETER_PIN 14

// L298N Motor Controller
#define en1 5
#define in1 11
#define in2 10
#define en2 6
#define in3 9
#define in4 7

// LM393 Speed Sensor 1 Digital Output (left)
#define digitalPin1 3
// LM393 Speed Sensor 2 Digital Output (right)
#define digitalPin2 2

// PID Controller Variables
double Input1, Input2, Output1, Output2;

// setpoint and sensor offsets
double Setpoint1 = 600;
double Setpoint2 = 200;

double offset1 = 0; // higher = left faster
double offset2 = 0; // higher = right faster

// Specify the PID links and initial tuning parameters
double Kp=0.5, Ki=1, Kd=0;
PID myPID1(&Input1, &Output1, &Setpoint1, Kp, Ki, Kd, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, Kp, Ki, Kd, DIRECT);

//------ Read sensor 1 data. ------//
volatile int pulses1 = 0;
unsigned long lastDisplayTime1 = 0;
void countPulse1()
{
  pulses1++;
}

float read_sensor_speed1()
{
  Serial.println(",pot:" + String(analogRead(POTENTIOMETER_PIN)));
  Setpoint1 = 60 * analogRead(POTENTIOMETER_PIN) / 100;

  attachInterrupt(
    digitalPinToInterrupt(digitalPin1),
    countPulse1,
    FALLING
  );
  
  while (true) {
    unsigned long currentTime1 = millis();

    // Calculate RPM continuously
    float rpm = (float)pulses1 * (60000.0 / (currentTime1 - lastDisplayTime1)) / 20.0;

    // Display RPM every 500ms
    if (currentTime1 - lastDisplayTime1 >= 100)
    {
      lastDisplayTime1 = currentTime1; // Update the last display time
      pulses1 = 0;                    // Reset pulse count
      return rpm;
    }
  }

}
//------ SECTION END ------//

//------ Read sensor 2 data. ------//
volatile int pulses2 = 0;
unsigned long lastDisplayTime2 = 0;
void countPulse2()
{
  pulses2++;
}

float read_sensor_speed2()
{
  
  attachInterrupt(
    digitalPinToInterrupt(digitalPin2),
    countPulse2,
    FALLING
  );
  
  while (true) {
    unsigned long currentTime2 = millis();

    // Calculate RPM continuously
    float rpm = (float)pulses2 * (60000.0 / (currentTime2 - lastDisplayTime2)) / 20.0;

    // Display RPM every 500ms
    if (currentTime2 - lastDisplayTime2 >= 100)
    {
      lastDisplayTime2 = currentTime2; // Update the last display time
      pulses2 = 0;                    // Reset pulse count
      return rpm;
    }
  }

}
//------ SECTION END ------//

// define two tasks for SpinMotor1 & SpinMotor2
void TaskSpinMotor1( void *pvParameters );
void TaskSpinMotor2( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize LM393 Speed Sensor Digital Output
  //pinMode(digitalPin1, INPUT_PULLUP);
  //pinMode(digitalPin2, INPUT_PULLUP);

  // Initialize L298N motor controller
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(en2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // get initial readings from speed sensors
  Input1 = read_sensor_speed1() - offset1;
  Input2 = read_sensor_speed2() - offset2;

  // turn the PID on
  myPID1.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskSpinMotor1
    ,  "SpinMotor1"   // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskSpinMotor2
    ,  "SpinMotor2"
    ,  256  // Stack size
    ,  NULL
    ,  1  // Priority
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

void TaskSpinMotor1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    Serial.print("kp:");
    Serial.print(Kp);
    Serial.print(",kd:");
    Serial.print(Kd);
    Serial.print(",ki:");
    Serial.print(Ki);

    Input1 = read_sensor_speed1() - offset1;
    myPID1.Compute();
    
    analogWrite(en1, Output1);

    Serial.print(",output1:");
    Serial.print(Output1);
    Serial.print(",output2:");
    Serial.print(Output2);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 

    Serial.print(",wheel_speed1:");
    Serial.print(Input1);

    Serial.print(",wheel_speed2:");
    Serial.print(Input2);

    Serial.print(",Setpoint1:");
    Serial.println(Setpoint1);

    vTaskDelay(1);
  }
}

void TaskSpinMotor2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    Serial.print("kp:");
    Serial.print(Kp);
    Serial.print(",kd:");
    Serial.print(Kd);
    Serial.print(",ki:");
    Serial.print(Ki);

    Input2 = read_sensor_speed2() - offset2;
    myPID2.Compute();
    
    analogWrite(en2, Output2);

    Serial.print(",output1:");
    Serial.print(Output1);
    Serial.print(",output2:");
    Serial.print(Output2);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 

    Serial.print(",wheel_speed1:");
    Serial.print(Input1);

    Serial.print(",wheel_speed2:");
    Serial.print(Input2);

    Serial.print(",Setpoint2:");
    Serial.println(Setpoint2);

    vTaskDelay(1);
  }
}
