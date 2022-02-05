PROGRAM=SerialExample
SERIALPORT=/dev/ttyACM0

INCLUDES=-I.
INCLUDES+= -IarduinoLibsAndCore/cores/arduino
INCLUDES+= -IarduinoLibsAndCore/libraries/Wire/src
INCLUDES+= -IarduinoLibsAndCore/libraries/Wire/src/utility
INCLUDES+= -IarduinoLibsAndCore/variants/standard

vpath %.cpp arduinoLibsAndCore/libraries/Wire/src
vpath %c arduinoLibsAndCore/libraries/Wire/src/utility

BUILD_DIR=Build

CC=avr-gcc
CPP=avr-g++

MMCU=-mmcu=atmega328p

CFLAGS= -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR
CPPFLAGS= -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -w -x c++ -CC ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR


all: ${PROGRAM}.elf ${PROGRAM}.hex 
	rm -f *.d


${PROGRAM}.elf: Build/Wire.o Build/rgb_lcd.o Build/main.o Build/twi.o  
	${CPP} -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections ${INCLUDES} ${MMCU} $^ -o ${BUILD_DIR}/$@ ./arduinoLibsAndCore/libres.a -static -L./arduinoLibsAndCore -lres


Build/%.o: %.c
	mkdir -p ${BUILD_DIR}/
	${CC} -c ${CFLAGS} ${INCLUDES} $^
	mv *.o ${BUILD_DIR}/

Build/%.o: %.cpp
	mkdir -p ${BUILD_DIR}/
	${CPP} -c ${CPPFLAGS} ${INCLUDES} $^
	mv *.o ${BUILD_DIR}/

OBJCOPY=avr-objcopy
 
${PROGRAM}.hex: ${BUILD_DIR}/${PROGRAM}.elf
	${OBJCOPY} -O ihex -R .eeprom  ${BUILD_DIR}/${PROGRAM}.elf ${BUILD_DIR}/$@
 
upload: ${BUILD_DIR}/${PROGRAM}.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P ${SERIALPORT} -b 115200 -U flash:w:${BUILD_DIR}/${PROGRAM}.hex;

clean:
	rm -Rf ${BUILD_DIR}

monitorSerial:
	python3 MySerialMonitor/MySerialMonitor.py
