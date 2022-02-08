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
    TCCR1B &= ~ _BV(WGM13);
    TCCR1B |=   _BV(WGM12);
    TCCR1A &= ~ _BV(WGM11) & _BV(WGM10);

    // set clock factor to 1024
    TCCR1B |=   _BV(CS12) | _BV(CS10);
    TCCR1B &= ~ _BV(CS11);

    // set interrupt delay
    OCR1A = 0x3D09;

    // enable timer interruptions
    TIMSK1 |= _BV(OCIE1A);

    // globally enable interrupts
    sei();


    while(true)
    {
        
    }
}

ISR(TIMER1_COMPA_vect)
{
    PORTD ^= redLed;
}

unsigned char Delay (unsigned long a) 
{
    unsigned long b;
    for(b=0;b<a;b++){
    };
    return 1;
}
