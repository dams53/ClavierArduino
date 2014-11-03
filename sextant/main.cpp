// On inclut les fichiers headers 
#include "Applications/PS2Keyboard/PS2Keyboard.h"
//#include "lib/ST7565/ST7565.h"
// D�finition du pin
#define DATA_PIN 4

//extern "C"

// D�finication de la classe clavier
PS2Keyboard keyboard;
// D�finition de la led
 int ledPin =  13;

void setup() {
	// on lance le clavier 
  keyboard.begin(DATA_PIN);
  // d�lai de 1000
  delay(1000);
  // d�finition du mode de la pin
    pinMode(ledPin, OUTPUT);

 
}

void loop() {
	// Si le clavier est disponible
  if(keyboard.available()) {
  // C'est ici o� �a ne rentre jamais !!
	// On r�cup�re le clavier unicode
     uint8_t dat = keyboard.read();
    uint8_t val = dat - '0';

    if(val >= 0 && val <= 9) {
	// Entre 0 et 9 -> on allume la led
	 digitalWrite(ledPin, LOW);
    }else if(dat == PS2_KC_ENTER) {
	// ENTER -> on allume la led
      digitalWrite(ledPin, LOW);
    } else if(dat == PS2_KC_ESC) {
	// ESC -> on �teint la led
      digitalWrite(ledPin, HIGH); 
    } /*else{
	 digitalWrite(ledPin, HIGH); 
    }*/
  }
}

// On lance les fonctions
int main (void)
{	
	setup();  
	while(1){
	loop();
	}

}


