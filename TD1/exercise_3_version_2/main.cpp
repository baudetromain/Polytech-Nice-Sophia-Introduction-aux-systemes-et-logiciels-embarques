/*
 * --------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <julien.deantoni@univ-cotedazur.fr> wrote this file.
 * As long as you retain this notice you can do whatever you want with this stuff.
 * If we meet some day, and you think this stuff is worth it,
 * you can buy me a beer in return.  Julien Deantoni
 * --------------------------------------------------------------------------------
 */

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char Delay (unsigned long a);

#define redLed _BV(PD3)

int main(void)
{
    DDRD=0b11101111; //D4 as input, all the other as outputs  
    
    PORTD = 0; //all outputs to 0

    PORTD |= redLed;

    // set to CTC mode
    TCCR1B &= 0b11101111;
    TCCR1B |= 0b00001000;
    TCCR1A &= 0b11111100;

    // set clock factor to 1024
    TCCR1B |= 0b00000101;
    TCCR1B &= 0b11111101;

    // set interrupt delay
    OCR1A = 0x3D09;

    // enable timer interruptions
    TIMSK1 |= 0b00000010;

    sei();
    while(true)
    {
        
    }
}

ISR(TIMER1_COMPA_vect)
{
    PORTD = 0;
}

unsigned char Delay (unsigned long a) 
{
    unsigned long b;
    for(b=0;b<a;b++){
    };
    return 1;
}
