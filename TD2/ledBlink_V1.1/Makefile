INCLUDES=-I.
INCLUDES+= -IarduinoLibsAndCore/cores/arduino
INCLUDES+= -IarduinoLibsAndCore/libraries/Wire/src
INCLUDES+= -IarduinoLibsAndCore/libraries/Wire/src/utility
INCLUDES+= -IarduinoLibsAndCore/variants/standard
INCLUDES+= -IFreeRTOS/Source/include
INCLUDES+= -IFreeRTOS/Source/portable/GCC/ATMega328/



vpath %.cpp arduinoLibsAndCore/libraries/Wire/src
vpath %c arduinoLibsAndCore/libraries/Wire/src/utility
# List C source files here. (C dependencies are automatically generated.)
vpath %c FreeRTOS/Source
vpath %c FreeRTOS/Source/portable/MemMang
vpath %c FreeRTOS/Source/portable/GCC/ATMega328/

# %SRC	= \
# %main.c \
# %$(SOURCE_DIR)/tasks.c \
# %$(SOURCE_DIR)/queue.c \
# %$(SOURCE_DIR)/list.c \
# %$(SOURCE_DIR)/croutine.c \
# %$(SOURCE_DIR)/portable/MemMang/heap_1.c \
# %$(PORT_DIR)/port.c

BUILD_DIR=Build

CC=avr-gcc
CPP=avr-g++

MMCU=-mmcu=atmega328p

CFLAGS= -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR
CPPFLAGS= -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -w -x c++ -CC ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR

PROGRAM=MyFreeRTOSBlinkTest


all: ${PROGRAM}.elf ${PROGRAM}.hex 
	rm -f *.d


${PROGRAM}.elf: Build/tasks.o Build/queue.o Build/list.o Build/croutine.o Build/heap_1.o Build/port.o Build/Wire.o Build/main.o Build/twi.o 
	${CPP} -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections ${INCLUDES} ${MMCU} $^ -o ${BUILD_DIR}/$@ -static -L./arduinoLibsAndCore -lres


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

PORT=/dev/ttyS3
 
upload: ${BUILD_DIR}/${PROGRAM}.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P ${PORT} -b 115200 -U flash:w:${BUILD_DIR}/${PROGRAM}.hex;

clean:
	rm -Rf ${BUILD_DIR}

monitorSerial:
	screen -S arduinoMonitor ${PORT} 9600
killMonitor:
	screen -XS arduino quit
