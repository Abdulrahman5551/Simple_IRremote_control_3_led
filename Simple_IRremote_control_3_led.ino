/* 
 Simple application control 3 LED by remote:
 - 3 LED
 - IR-receiver (TSOP1838)
*/


// include IR remote library 
#include <IRremote.h>

// Define sensor pin
const int RECV_PIN = 4;

// Define LED pin constants
const int ledRedPin = 7;
const int ledYellowPin = 8;
const int ledGreenPin = 9;

// Define integer to remember toggle state
int togglestate = 0;

int togglestate_g = 0;
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // Enable the IR receiver
  irrecv.enableIRIn();

  // Set LED pins as outputs
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);

}

void loop() {
  if(irrecv.decode(&results)){

    switch(results.value){

      case 0xFFC23D: // Button LED RED , Turn On For 2 Seconds
      digitalWrite(ledRedPin, HIGH);
      delay(3000);
      digitalWrite(ledRedPin, LOW);
      break;

      case 0xFFA857: // Button LED Yellow
      if(togglestate == 0){
        digitalWrite(ledYellowPin, HIGH);
        togglestate = 1;
      }
      else{
        digitalWrite(ledYellowPin, LOW);
        togglestate = 0;
      }
      break;

      case 0xFF906F: // Button LED Green
      if (togglestate_g == 0){
        digitalWrite(ledGreenPin, HIGH);
        delay(2000);
        digitalWrite(ledGreenPin, LOW);
        togglestate_g = 1;
      }
      else if (togglestate_g == 1){
        digitalWrite(ledGreenPin, HIGH);
        togglestate_g = 2;
      }
      else if (togglestate_g == 2){
        digitalWrite(ledGreenPin, LOW);
        togglestate_g = 0;

      }
    }
  }
  irrecv.resume();
}
