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
#include "Arduino.h"
#include <util/delay.h>

#include "rgb_lcd.h"

const uint8_t button = _BV(PD4); 

int main(void)
{
    DDRD &= ~button; //D4 as input
    sei();           //interrupts are required by the LCD lib 
    
    rgb_lcd lcd;
    lcd.begin(16,2) ;
    lcd.print("  button is ");
    bool doIt = false;

    //main infinite loop

    while(1)
    {   
      doIt = PIND & button;
      lcd.setCursor(5,1);
      if (doIt){
        lcd.print(" on ");
      }else{
        lcd.print(" off");
      }
      _delay_ms(700);
    }
}
