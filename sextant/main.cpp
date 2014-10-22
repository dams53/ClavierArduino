
#include "Applications/PS2Keyboard/PS2Keyboard.h"
#include "lib/ST7565/ST7565.h"
#define DATA_PIN 4

//extern "C"

PS2Keyboard keyboard;
 int ledPin =  13;

void setup() {

  keyboard.begin(DATA_PIN);
  delay(1000);
    pinMode(ledPin, OUTPUT);

 
}

void loop() {

  if(keyboard.available()) {
		 digitalWrite(ledPin, HIGH);
     uint8_t dat = keyboard.read();
    uint8_t val = dat - '0';

    if(val >= 0 && val <= 9) {
	 digitalWrite(ledPin, LOW);
    }else if(dat == PS2_KC_ENTER) {
      digitalWrite(ledPin, LOW);
    } else if(dat == PS2_KC_ESC) {
      digitalWrite(ledPin, HIGH); 
    } /*else{
	 digitalWrite(ledPin, HIGH); 
    }*/
  }
}

int main (void)
{	
	setup();
	while(1){
	loop();
	}

}


