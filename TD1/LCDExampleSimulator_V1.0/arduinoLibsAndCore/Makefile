CC = avr-gcc
CXX= avr-g++

INCLUDES = -I. -Ivariants/standard -Icores/arduino
INCLUDES += -I/usr/avr/include/

LDFLAGS += -Wl,-rpath
LDLIBS +=  -lrtdm -lnative -lm 


MMCU=-mmcu=atmega328p
CFLAGS= -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR
CPPFLAGS= -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -w -x c++ -CC ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR
ASMFLAGS= -g -x assembler-with-cpp -flto -MMD ${MMCU} -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR


SRCS = cores/arduino/abi.cpp cores/arduino/CDC.cpp cores/arduino/HardwareSerial0.cpp cores/arduino/HardwareSerial1.cpp cores/arduino/HardwareSerial2.cpp cores/arduino/HardwareSerial3.cpp cores/arduino/HardwareSerial.cpp cores/arduino/IPAddress.cpp cores/arduino/main.cpp cores/arduino/new.cpp cores/arduino/PluggableUSB.cpp cores/arduino/Print.cpp cores/arduino/Stream.cpp cores/arduino/Tone.cpp cores/arduino/USBCore.cpp cores/arduino/WMath.cpp cores/arduino/WString.cpp
SRCCS = cores/arduino/hooks.c cores/arduino/WInterrupts.c cores/arduino/wiring_analog.c cores/arduino/wiring.c cores/arduino/wiring_digital.c cores/arduino/wiring_pulse.c cores/arduino/wiring_shift.c
SRCASM = cores/arduino/wiring_pulse.S
# La generation des dependances est ici : on donne une regle de "pattern" qui decrit
# comment fabriquer un .dep a partir d'un .c. (la ligne de sed est utile dans certains
# cas mais je ne me rappelle plus lesquels :-) ).

%.dep: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) ${INCLUDES} $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.dep: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) ${INCLUDES} $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.dep: %.S
	@set -e; rm -f $@; \
	$(CXX) -MM $(ASMFLAGS) ${INCLUDES} $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$	

# et pour finir on inclut ces .dep ce qui force leur regeneration si le sourceassocie
# a change. Par contre, le .dep lui-meme ne depend pas des fichiers inclus parle .c, c'est
# une limite a ce systeme.

include $(SRCS:.cpp=.dep)
include $(SRCCS:.c=.dep)
#On en deduit la liste des fichiers objets a produire :

OBJS = $(patsubst %.cpp,%.o,$(SRCS))
OBJCS = $(patsubst %.c,%.o,$(SRCCS))
OBJASMS = $(patsubst %.S,%.o,$(SRCASM))
#Ensuite, on utilise la tournure "make" pour designer un membre de librairie sous la forme libtruc.a(toto.o)

LIBARDUINO = libres.a

LIBOBJS = $(foreach o,$(OBJS),$(LIBARDUINO)($o))
LIBOBJCS = $(foreach o,$(OBJCS),$(LIBARDUINO)($o))
LIBOBJASMS = $(foreach o,$(OBJCASMS),$(LIBARDUINO)($o))
# "-c" means compile but don't link
.cpp.o:
	$(RM) $@
	$(CXX) -c $(CPPFLAGS) $(INCLUDES) $*.cpp -o $@

.c.o:
	$(RM) $@
	$(CC) -c $(CFLAGS) $(INCLUDES) $*.c -o $@
.S.o:
	$(RM) $@
	$(CC) -c $(ASMFLAGS) $(INCLUDES) $*.c -o $@

all: libarduino

#La, la target est dependante des objets mais avec la forme syntaxique speciale
# que make reconnait pour fabriquer une librairie. Ca repose sur des reglesbuiltin
# de make (voir "make -p -f/dev/null"). Si l'archiveur a utiliser n'est pas aril faut,
# si mes souvenirs sont bons, redefinir la variable AR et eventuellementARFLAGS.

AR=avr-gcc-ar
ARFLAGS= rcs

libarduino: $(LIBOBJS) $(LIBOBJCS) ${LIBOBJASMS}
$(LIBARDUINO): libarduino


# Pour l'exemple, cet include n'a que peut d'interet : il definissait quelques
# variables pour l'installation de la librairie.
# 
# include ../Makefile.inc

install:
	$(INSTALL) -d $(libdir)
	$(INSTALL) $(LIBARDUINO) $(libdir)

clean:
	rm -f $(LIBARDUINO) $(OBJS) $(OBJCS)

