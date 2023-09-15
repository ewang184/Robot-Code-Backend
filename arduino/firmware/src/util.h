// Classes and functions for debugging and accessing hardware on Arduino
void blink_once() {
   pinMode(LED_BUILTIN, OUTPUT);

   digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(100);                      // wait
   digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
   delay(100);
}

void blink_twice() {
   pinMode(LED_BUILTIN, OUTPUT);

   for(int i{0}; i < 2; ++i) {
      digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(100);                      // wait
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
      delay(100);
   }
}

void blink_delay(bool double_blink = false, int delay_duration = 1000) {
   pinMode(LED_BUILTIN, OUTPUT);

   for(int i{0}; i < 4; ++i) {
      double_blink ? blink_twice() : blink_once(); // blink
      delay(delay_duration);                       // wait
   }
}

void blink_fast() {
   pinMode(LED_BUILTIN, OUTPUT);

   for(int i{0}; i < 4; ++i) {
      digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(100);                      // wait
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
      delay(100);
   }
}

void blink_slow() {
   pinMode(LED_BUILTIN, OUTPUT);

   for(int i{0}; i < 4; ++i) {
      digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(500);                      // wait
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
      delay(500);
   }
}
