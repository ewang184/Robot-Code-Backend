//www.elegoo.com
//2016.12.9

#include "IRremote.h"

#define LED_BUILTIN 13
#define en1 4
#define in1 3
#define in2 2
#define in3 6
#define in4 5
#define en2 7

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
int state = 0; //state

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{
  Serial.println("starting state is" + state);
  state = 0;
  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); 
    state = 0;
    break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); 
    state = 0;
    break;
  case 0xFF629D: Serial.println("VOL+"); state = 0;break;
  case 0xFF22DD: Serial.println("FAST BACK"); state = 0;  break;
  case 0xFF02FD: Serial.println("PAUSE");  state = 0; break;
  case 0xFFC23D: Serial.println("FAST FORWARD"); state = 0; break;
  case 0xFFE01F: Serial.println("DOWN");
    state = 2;
    break;
  case 0xFFA857: Serial.println("VOL-");  state = 0; break;
  case 0xFF906F: Serial.println("UP");    state = 1;
    break;
  case 0xFF9867: Serial.println("EQ"); state = 0;  break;
  case 0xFFB04F: Serial.println("ST/REPT"); state = 0; break;
  case 0xFF6897: Serial.println("0"); state = 0;break;
  case 0xFF30CF: Serial.println("1"); state = 0; break;
  case 0xFF18E7: Serial.println("2"); state = 0;   break;
  case 0xFF7A85: Serial.println("3"); state = 0;break;
  case 0xFF10EF: Serial.println("4"); state = 0; break;
  case 0xFF38C7: Serial.println("5"); state = 0;break;
  case 0xFF5AA5: Serial.println("6"); state = 0;  break;
  case 0xFF42BD: Serial.println("7"); state = 0; break;
  case 0xFF4AB5: Serial.println("8"); state = 0;break;
  case 0xFF52AD: Serial.println("9");    
  state = 0;break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");
  break;  

  default: 
    Serial.println(" other button : ");
    Serial.println(results.value);
    state = 0;

  }// End Case
  Serial.println("end state is" + state);

 if (state == 1){
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);   
  delay(500);
 }
 else if (state == 0){
   digitalWrite(en1, LOW);
    digitalWrite(en2, LOW);
    delay(500);
 }
 else if (state == 2){
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  
  delay(500); 
 }


} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */