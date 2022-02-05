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

const uint8_t greenLed = _BV(PD3);
const uint8_t redLed = _BV(PD2);
const uint8_t button = _BV(PD4); 

int main(void)
{
    //this section correspond to the setup part in arduino
    DDRD |= (redLed | greenLed);    //D2 and D3 as output, all the others as inputs, see page 95 of the datasheets.
    PORTD &= ~(redLed & greenLed);  //all outputs to 0
    init();                       //unfortunately, Serial is based on Stream and readString requires "millis()" which is configured by this arduino function..
    //sei();                          //the simple read does not require the millis function so no need to call init

    Serial.begin(9600);
    _delay_ms(1000);
    Serial.println("Serial is started");
    
    bool doIt = false; 

    //main infinite loop
    while(true)
    {   
      while(Serial.available() == 0){
        _delay_ms(500);
      }

      String res = Serial.readString(); //warning, not the classical C++ String.
      Serial.print("received:");
      Serial.println(res.c_str());
      if (res.compareTo("on") == 0){
        PORTD |= greenLed; 
      }
      else if (res.compareTo("off") == 0){
        PORTD &= ~(greenLed); 
      }
      else{
        Serial.println("error: not a correct command");
        for(int i = 0; i < 10; i++){
          PORTD ^= redLed;
          _delay_ms(250);
        }
      }
    }
}
