/*
 * Blink.cpp
 *
 *  Created on: 8 Aout 2014
 *      Author: jmenaud
 */

#include "Blink.h"

void
_delay_loop_2(uint16_t __count)
{
	__asm__ volatile (
                      "1: sbiw %0,1" "\n\t"
                      "brne 1b"
                      : "=w" (__count)
                      : "0" (__count)
                      );
}



void
_delay_1s()
{
    // wait 1 s
	for (int y=0;y<1000;y++) {
        // wait 1 ms
        for (int x=0;x<10;x++) {
			// wait 1/10 ms
			_delay_loop_2(400);
        }
	}    
}


void Blink::start() {
    /* set pin 5 of PORTB for output*/
    DDRB =  0b111111;
    
    while(1) {
        /* set pin 5 high to turn led on */
        PORTB |= 0b00100000;
        _delay_1s();
        
        /* set pin 5 low to turn led off */
        PORTB &= 0b11011111;
        _delay_1s();
        
    }
};
