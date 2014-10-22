#include <include/stdint.h>
#include <include/iom328p.h>
#include <include/sfr_defs.h>
//#include <stddef.h>
#include <include/string.h>
//#include <stdio.h>


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
//#define BAUD 115200
#endif
#include <include/setbaud.h>

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0); /* Enable RX and TX */
}

void uart_putchar(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

char uart_getchar() {
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void uart_sendString(char* ptrString) {
	//Send chars until we encounter a null char (end of string)
	//uart_putchar('$');
	int i = 0;

	while (ptrString[i] != 0x00) {
		//Send a single char at a time
		uart_putchar(ptrString[i]);
		//if (*ptrString == '\0') break;
		//We increment the pointer so we can read the next char
		i++;
		//uart_putchar('-');
	}

	//size_t HardwareSerial::write(uint8_t c)
	//{
	//  int i = (_tx_buffer->head + 1) % SERIAL_BUFFER_SIZE;
	//	
	//  // If the output buffer is full, there's nothing for it other than to 
	//  // wait for the interrupt handler to empty it a bit
	//  // ???: return 0 here instead?
	//  while (i == _tx_buffer->tail)
	//    ;
	//	
	//  _tx_buffer->buffer[_tx_buffer->head] = c;
	//  _tx_buffer->head = i;
	//	
	//  sbi(*_ucsrb, _udrie);
	//  // clear the TXC bit -- "can be cleared by writing a one to its bit location"
	//  transmitting = true;
	//  sbi(*_ucsra, TXC0);
	//  
	//  return 1;
	//}

}

//void uart_sendStringln(char* ptrString) {
//	size_t length = strlen(ptrString);
//	char s[length > 7 ? length + 1 : 8];
//	sprintf(s, "%s", ptrString);
//	for (int i = length; i < 8; ++i) {
//		s[i] = ' ';
//	} // for
//	s[length > 8 ? length : 8] = '\n';
//	uart_sendString(s);
//}