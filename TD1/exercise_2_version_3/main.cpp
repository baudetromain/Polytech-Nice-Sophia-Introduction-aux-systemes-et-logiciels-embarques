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
//#include <util/delay.h>

/**
 * an active delay function to illustrate but should not be used in real code 
 * (use _delay_ms/_delay_us from <util/delay.h> instead) 
 **/
unsigned char Delay (unsigned long a);

//usefull def to ease the reading
#define redLed _BV(PD2)

int _switch = 0;
int is_led_blinking = 0;

int main(void)
{
    //this section correspond to the setup part in arduino

    DDRD=0b11101111; //D4 as input, all the other as outputs  
    //usually we prefer the following for where only D4 is changed:
    //DDRB |= _BV(D4); // where _BV create the 0b00010000 word => 0x10 since 1|x = x and page 
    //check page 95 of the datasheets. What is the minimum manipulation of DDRD to make it correct according to our setup ?
    
    PORTD = 0; //all outputs to 0
    
    //this section correspond to the loop part in arduino
    while(true)
    {
        if (PIND & _BV(PD4))
        {
            if (!_switch)
            {
                _switch = 1;
                
                if (!is_led_blinking)
                {
                    is_led_blinking = 1;
                }
                else
                {
                    is_led_blinking = 0;
                    PORTD &= 0b11110111;
                }
                Delay(1000);
            }
        }
        else
        {
            _switch = 0;
            Delay(1000);
        }

        if (is_led_blinking)
        {
            PORTD ^= _BV(PD3);
            Delay(350000);
        }
    }
}

unsigned char Delay (unsigned long a) 
{
    unsigned long b;
    for(b=0;b<a;b++){
    };
    return 1;
}
