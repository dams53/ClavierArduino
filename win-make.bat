:: compilation avec avr, on déplace ensuite le fichier .o dans le dossier all-o puis on compile tout et on le met dans l'arduino
avr-g++  -I. -c sextant/main.cpp -Os -DF_CPU=16000000UL -I. -mmcu=atmega328p  -o sextant/main.o
mv -f sextant/main.o build/all-o
avr-g++  -I. -c Applications/Interrupt/interrupt.c -Os -DF_CPU=16000000UL -I. -mmcu=atmega328p  -o Applications/Interrupt/interrupt.o
mv -f Applications/Interrupt/interrupt.o build/all-o
avr-g++  -I. -c Applications/PS2Keyboard/PS2Keyboard.cpp -Os -DF_CPU=16000000UL -I. -mmcu=atmega328p  -o Applications/PS2Keyboard/PS2Keyboard.o
mv -f Applications/PS2Keyboard/PS2Keyboard.o build/all-o
avr-g++  -I. -c Applications/Blink/Blink.cpp -Os -DF_CPU=16000000UL -I. -mmcu=atmega328p  -o Applications/Blink/Blink.o
mv -f Applications/Blink/Blink.o build/all-o
avr-g++  -I. -c lib/ST7565/ST7565.cpp -Os -DF_CPU=16000000UL -I. -mmcu=atmega328p  -o lib/ST7565/ST7565.o
mv -f lib/ST7565/ST7565.o build/all-o
avr-gcc -mmcu=atmega328p   -o build/boot/sextant.elf build/all-o/interrupt.o build/all-o/PS2Keyboard.o build/all-o/Blink.o build/all-o/ST7565.o build/all-o/main.o
avr-objcopy  -O ihex -R .eeprom build/boot/sextant.elf build/boot/sextant.elf.hex
avrdude -C avrdude.conf -F -V -c arduino -p ATMEGA328P -P com16 -b 115200 -U flash:w:build/boot/sextant.elf.hex
