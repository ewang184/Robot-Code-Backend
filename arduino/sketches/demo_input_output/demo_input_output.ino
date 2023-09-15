// variables
const int trigPin = 9;
const int echoPin = 10;
long duration, cm;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available()>0){
    char input = Serial.read();

    // y -> led on
    if (input == 'y'){
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    }

    // n -> led off
    if (input == 'n'){
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    }

    // r -> get sensor value
    if (input == 'r'){
      // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    
      // Read the signal from the sensor: a HIGH pulse whose
      // duration is the time (in microseconds) from the sending
      // of the ping to the reception of its echo off of an object.
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
    
      // Convert the time into a distance
      cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

      Serial.print(cm);
      Serial.print("cm");
      Serial.println();
    }
  }
}
