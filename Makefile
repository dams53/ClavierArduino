OS=$(shell uname)
COMPILATEUR=CPP_$(OS)
LIEUR=LD_$(OS)
OBCOPY=OBC_$(OS)
DOWNLOAD=D_$(OS)
COMPILATEUR_OPTION=COMPOP_$(OS)
LIEUR_OPTION=LIEUR_$(OS)

#-------------------
##Pour Mac
CPP_Darwin=./ccompil-Mac/tools/avr/bin/avr-g++
#LD_Darwin=./ccompil-Mac/tools/avr/bin/avr-ld

LD_Darwin=/Users/menaud/Developpements/Arduino/arduino/hardware/tools/avr/bin/avr-gcc

OBC_Darwin = ./ccompil-Mac/tools/avr/bin/avr-objcopy 
D_Darwin=./ccompil-Mac/tools/avr/bin/avrdude

TTY_Darwin = /dev/tty.usbmodem1411



#-------------------
##Pour Linux
CPP_Linux=./ccompil-Linux/tools/avr/bin/avr-g++
LD_Linux=./ccompil-Linux/tools/avr/bin/avr-gcc
OBC_Linux=./ccompil-Linux/tools/avr/bin/avr-objcopy
D_Linux=./ccompil-Linux/tools/avrdude -C ./ccompil-Linux/tools/avrdude.conf

TTY_Linux = /dev/ttyACM0


#-------------------
##POUR WINDOWS

 
#-------------------
## Partie commune a toutes les configurations

#CPPFLAGS = -c  -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=157 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR $($(COMPILATEUR_OPTION))  
LDFLAGS_Linux = --warn-common -T ./support/avr5.x $($(LIEUR_OPTION))


CPPFLAGS = -Os -DF_CPU=16000000UL -I. -mmcu=atmega328p 
LDFLAGS = -mmcu=atmega328p 

PWD :=.
DELE = rm
MV = mv -f


KERNEL_OBJ   = sextant.elf

# Main target
all: $(KERNEL_OBJ)


OBJECTS = 	./sextant/main.o \
			./Applications/PS2Keyboard/PS2Keyboard.o 
					
	  		
OBJ_FILES = $(wildcard build/all-o/*.o)

$(KERNEL_OBJ): $(OBJECTS)
	echo 'Votre compilateur $(COMPILATEUR) et votre lieur $(LIEUR)'
	$($(LIEUR)) $(LDFLAGS)  -o build/boot/$@ $(OBJ_FILES) 
	#support/crtm328p.o 
	$($(OBCOPY))  -O ihex -R .eeprom build/boot/$@ build/boot/$@.hex


# Create objects from CPP source code
%.o: %.cpp
	$($(COMPILATEUR))  -I$(PWD) -c $< $(CPPFLAGS) -o $@
	$(MV) $@ build/all-o
	
# Create objects from C source code
%.o: %.c
	$($(COMPILATEUR)) -I$(PWD) -c $< $(CPPFLAGS) -o $@
	$(MV) $@ build/all-o


	
# Create objects from assembler (.S) source code
%.o: %.S
	$($(COMPILATEUR)) -I$(PWD)  -c $< $(CPPFLAGS) -DASM_SOURCE=1 -o $@
	$(MV) $@ build/all-o


# Clean directory
clean:
	$(DELE) -rf build/all-o/*.o
	$(DELE) -f *.s
	$(DELE) -f build/boot/*.elf
	find . -name \*.d -exec rm \-fv {} \;
	
download:
	$($(DOWNLOAD)) -F -V -c arduino -p ATMEGA328P -P $(TTY_$(OS)) -b 115200 -U flash:w:build/boot/$(KERNEL_OBJ).hex

	
