/*
  PS2Keyboard.h - PS2Keyboard library
  Copyright (c) 2007 Free Software Foundation.  All right reserved.
  Written by Christian Weichel <info@32leaves.net>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef PS2Keyboard_h
#define PS2Keyboard_h

#ifndef _AVR_IO_H_
#define _AVR_IO_H_
#include "include/iom328p.h"
#endif

#include <lib/ST7565/ST7565.h>
#include "Applications/Interrupt/interrupt.h"
#include <include/pgmspace.h>

/*
 * PS2 keyboard "make" codes to check for certain keys.
 */
#define PS2_KC_BREAK  0xf0
#define PS2_KC_ENTER  0x5a
#define PS2_KC_ESC    0x76
#define PS2_KC_KPLUS  0x79
#define PS2_KC_KMINUS 0x7b
#define PS2_KC_KMULTI 0x7c
#define PS2_KC_NUM    0x77
#define PS2_KC_BKSP   0x66

/*
 * This PIN is hardcoded in the init routine later on. If you change this
 * make sure you change the interrupt initialization as well.
 */
#define PS2_INT_PIN 3

/**
 * Purpose: Provides an easy access to PS2 keyboards
 * Author:  Christian Weichel
 */
class PS2Keyboard {
  
  private:
    int  m_dataPin;
    uint8_t m_charBuffer;
  
  public:
  	/**
  	 * This constructor does basically nothing. Please call the begin(int)
  	 * method before using any other method of this class.
  	 */
  	PS2Keyboard();
    
    /**
     * Starts the keyboard "service" by registering the external interrupt.
     * setting the pin modes correctly and driving those needed to high.
     * The propably best place to call this method is in the setup routine.
     */
    void begin(int dataPin);
    
    /**
     * Returns true if there is a char to be read, false if not.
     */
    bool available();
    
    /**
     * Returns the char last read from the keyboard. If the user has pressed two
     * keys between calls to this method, only the later one will be availble. Once
     * the char has been read, the buffer will be cleared.
     * If there is no char availble, 0 is returned.
     */
    uint8_t read();
    
};

#endif
