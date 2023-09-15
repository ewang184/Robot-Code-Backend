// Direct control of motor (constant speed, ramp up/down)

#define en1 5
#define in1 11
#define in2 10
#define en2 6
#define in3 9
#define in4 7

// potentiometer
#define POTENTIOMETER_PIN A0

int offset_output = 100;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{

  //turn motor in one direction
  offset_output = 25 * analogRead(POTENTIOMETER_PIN) / 100;
  Serial.print("pot:" + String(analogRead(POTENTIOMETER_PIN)));
  Serial.print(",offset_output:");
  Serial.println(offset_output);
  analogWrite(en1, offset_output);
  analogWrite(en2, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  delay(10);

  int i = 255;

  //slow motor down

  /* for (i=255; i>100; i--) {
    analogWrite(en1, i);
    analogWrite(en2, i);
    Serial.println(i);
    delay(20);
  } */

  //slowly speed it back up
  
  /* for (i=100; i<255; i++) {
    analogWrite(en1, i);
    analogWrite(en2, i);
    Serial.println(i);
    delay(20);
  } */
  
}/* --(end main loop )-- */
