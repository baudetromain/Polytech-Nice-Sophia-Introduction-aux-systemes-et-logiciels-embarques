PROGRAM=Exercise2Version1
PORT=/dev/ttyS8

INCLUDES=-I.
BUILD_DIR=Build
CPP=avr-g++
MMCU=-mmcu=atmega328p

#add -Os to the following line to optimize the code
CPPFLAGS= -g -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -w -x c++ -CC ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR



all: ${PROGRAM}.elf ${PROGRAM}.hex 
	rm -f *.d

${PROGRAM}.elf: Build/main.o  
	${CPP} -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections ${INCLUDES} ${MMCU} $^ -o ${BUILD_DIR}/$@ 

Build/%.o: %.cpp
	mkdir -p ${BUILD_DIR}/
	${CPP} -c ${CPPFLAGS} ${INCLUDES} $^
	mv *.o ${BUILD_DIR}/

OBJCOPY=avr-objcopy
 
${PROGRAM}.hex: ${BUILD_DIR}/${PROGRAM}.elf
	${OBJCOPY} -O ihex -R .eeprom  ${BUILD_DIR}/${PROGRAM}.elf ${BUILD_DIR}/$@
 
upload: ${BUILD_DIR}/${PROGRAM}.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P ${PORT} -b 115200 -U flash:w:${BUILD_DIR}/${PROGRAM}.hex;

clean:
	rm -Rf ${BUILD_DIR}
