/* 
 * File:   wiring_digital.h
 * Author: Alexandre Garnier <alexandre.garnier at mines-nantes.fr>
 *
 * Created on 19 septembre 2014, 11:16
 */

#ifndef WIRING_DIGITAL_H
#define	WIRING_DIGITAL_H

#include "stdint.h"
#include "common.h"
#ifndef _AVR_IOXXX_H_
#include "iom328p.h"
#endif

#define NOT_A_PIN 0
#define NOT_A_PORT 0

#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER2  5
#define TIMER2A 6
#define TIMER2B 7
#define TIMER3A 8
#define TIMER3B 9
#define TIMER3C 10
#define TIMER4A 11
#define TIMER4B 12
#define TIMER4C 13
#define TIMER4D 14	
#define TIMER5A 15
#define TIMER5B 16
#define TIMER5C 17

#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5
#define PF 6
#define PG 7
#define PH 8
#define PJ 10
#define PK 11
#define PL 12

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define LSBFIRST 0
#define MSBFIRST 1

#define PROGMEM __attribute__((__progmem__))

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

#define cli()  __asm__ __volatile__ ("cli" ::: "memory")

#define __LPM_enhanced__(addr)  \
(__extension__({                \
    uint16_t __addr16 = (uint16_t)(addr); \
    uint8_t __result;           \
    __asm__ __volatile__        \
    (                           \
        "lpm %0, Z" "\n\t"      \
        : "=r" (__result)       \
        : "z" (__addr16)        \
    );                          \
    __result;                   \
}))

#define __LPM_word_enhanced__(addr)         \
(__extension__({                            \
    uint16_t __addr16 = (uint16_t)(addr);   \
    uint16_t __result;                      \
    __asm__ __volatile__                    \
    (                                       \
        "lpm %A0, Z+"   "\n\t"              \
        "lpm %B0, Z"    "\n\t"              \
        : "=r" (__result), "=z" (__addr16)  \
        : "1" (__addr16)                    \
    );                                      \
    __result;                               \
}))

#define __LPM(addr)         __LPM_enhanced__(addr)
#define pgm_read_byte_near(address_short) __LPM((uint16_t)(address_short))
#define pgm_read_byte(address_short)    pgm_read_byte_near(address_short)

#define __LPM_word(addr)    __LPM_word_enhanced__(addr)
#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))
#define pgm_read_word(address_short)    pgm_read_word_near(address_short)

#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) )

#define portOutputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_output_PGM + (P))) )
#define portModeRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_mode_PGM + (P))) )

#ifdef	__cplusplus
extern "C" {
#endif

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
    _BV(0), /* 0, port D */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
    _BV(6),
    _BV(7),
    _BV(0), /* 8, port B */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
    _BV(0), /* 14, port C */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
};

const uint16_t PROGMEM port_to_mode_PGM[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &DDRB,
    (uint16_t) &DDRC,
    (uint16_t) &DDRD,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
    PD, /* 0 */
    PD,
    PD,
    PD,
    PD,
    PD,
    PD,
    PD,
    PB, /* 8 */
    PB,
    PB,
    PB,
    PB,
    PB,
    PC, /* 14 */
    PC,
    PC,
    PC,
    PC,
    PC,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &PORTB,
    (uint16_t) &PORTC,
    (uint16_t) &PORTD,
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
    NOT_ON_TIMER, /* 0 - port D */
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    // on the ATmega168, digital pin 3 has hardware pwm
#if defined(__AVR_ATmega8__)
    NOT_ON_TIMER,
#else
    TIMER2B,
#endif
    NOT_ON_TIMER,
    // on the ATmega168, digital pins 5 and 6 have hardware pwm
#if defined(__AVR_ATmega8__)
    NOT_ON_TIMER,
    NOT_ON_TIMER,
#else
    TIMER0B,
    TIMER0A,
#endif
    NOT_ON_TIMER,
    NOT_ON_TIMER, /* 8 - port B */
    TIMER1A,
    TIMER1B,
#if defined(__AVR_ATmega8__)
    TIMER2,
#else
    TIMER2A,
#endif
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER, /* 14 - port C */
    NOT_ON_TIMER,
    NOT_ON_TIMER,
	NOT_ON_TIMER, /* 0 - port D */
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    // on the ATmega168, digital pin 3 has hardware pwm
#if defined(__AVR_ATmega8__)
    NOT_ON_TIMER,
#else
    TIMER2B,
#endif
    NOT_ON_TIMER,
    // on the ATmega168, digital pins 5 and 6 have hardware pwm
#if defined(__AVR_ATmega8__)
    NOT_ON_TIMER,
    NOT_ON_TIMER,
#else
    TIMER0B,
    TIMER0A,
#endif
    NOT_ON_TIMER,
    NOT_ON_TIMER, /* 8 - port B */
    TIMER1A,
    TIMER1B,
#if defined(__AVR_ATmega8__)
    TIMER2,
#else
    TIMER2A,
#endif
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER, /* 14 - port C */
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
};

	void pinMode(uint8_t, uint8_t);
	void digitalWrite(uint8_t, uint8_t);


#ifdef	__cplusplus
}
#endif

#endif	/* WIRING_DIGITAL_H */

