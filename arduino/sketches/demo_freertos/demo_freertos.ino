// Change motor speed and read speed sensor at same time

#include <Arduino_FreeRTOS.h>

// L298N Motor Controller
#define en1 5
#define in1 11
#define in2 10
#define en2 3
#define in3 9
#define in4 6

// LM393 Speed Sensor Digital Output
#define digitalPin1 2

// define two tasks for MotorSpeedRamp & SpeedSensorRead
void TaskMotorSpeedRamp( void *pvParameters );
void TaskSpeedSensorRead( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize LM393 Speed Sensor Digital Output
  pinMode(digitalPin1, INPUT_PULLUP);

  // Initialize L298N motor controller 1
  pinMode(en2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskMotorSpeedRamp
    ,  "MotorSpeedRamp"   // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskSpeedSensorRead
    ,  "SpeedSensorRead"
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

void TaskMotorSpeedRamp(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    //turn motor in one direction
    analogWrite(en1, 255);
    analogWrite(en2, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 

    int i = 255;

    //slow motor down
    for (i=255; i>0; i--) {
      analogWrite(en1, i);
      analogWrite(en2, i);
      delay(20);
    }

    delay(1000);

    //slowly speed it back up
    for (i=0; i<255; i++) {
      analogWrite(en1, i);
      analogWrite(en2, i);
      delay(20);
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

//------ Read sensor data. ------//
volatile int pulses = 0;
unsigned long lastDisplayTime = 0;
void countPulse()
{
  pulses++;
}

void TaskSpeedSensorRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
/*
  SpeedSensorReadSerial
  Reads an input, prints the result to the serial monitor.
*/

  for (;;)
  {
    attachInterrupt(
      digitalPinToInterrupt(digitalPin1),
      countPulse,
      FALLING
    );
    
    while (true) {
      unsigned long currentTime = millis();

      // Calculate RPM continuously
      float rpm = (float)pulses * (60000.0 / (currentTime - lastDisplayTime)) / 20.0;

      // Display RPM every 500ms
      if (currentTime - lastDisplayTime >= 500)
      {
        Serial.print("Wheel Speed (RPM): ");
        Serial.println(rpm);

        lastDisplayTime = currentTime; // Update the last display time
        pulses = 0;                    // Reset pulse count
        break;
      }
    }

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}
//------ SECTION END ------//
