/*
 * --------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <julien.deantoni@univ-cotedazur.fr> wrote this file.
 * As long as you retain this notice you can do whatever you want with this stuff.
 * If we meet some day, and you think this stuff is worth it,
 * you can buy me a beer in return.  Julien Deantoni
 * --------------------------------------------------------------------------------
 */

/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include <semphr.h>

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/


//Each task is assigned a priority from 0 to ( configMAX_PRIORITIES - 1 ), where configMAX_PRIORITIES is defined within FreeRTOSConfig.h. 
// Low priority numbers denote low priority tasks. The idle task has priority zero (tskIDLE_PRIORITY). 
#define mainLED_TASK_PRIORITY   (tskIDLE_PRIORITY)


//tasks handler defined after the main
static void vCheckButtonPressed(void*);
static void vGreenBlinkLed(void*);

//constant to ease the reading....
const uint8_t redLed   = _BV(PD2);
const uint8_t greenLed = _BV(PD3);

SemaphoreHandle_t semaphore;

int main(void)
{
    semaphore = xSemaphoreCreateCounting(1, 0);
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


    // Create task #1
    xTaskHandle greenBlink_handle;
    xTaskCreate
    (
        vGreenBlinkLed,
        (const char*)"greenBlink",
        configMINIMAL_STACK_SIZE,
        NULL,
        0U,
        &greenBlink_handle
    );

    
    // Create task #2
    xTaskHandle button_handle;
    xTaskCreate
    (
        vCheckButtonPressed,
        (const char*)"button",
        configMINIMAL_STACK_SIZE,
        NULL,
        0U,
        &button_handle
    );

    
    vTaskStartScheduler();
}

static void vGreenBlinkLed(void* pvParameters)
{
    TickType_t xLastWakeUpTime = xTaskGetTickCount();
    while (1)
    {
        if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE)
        {
            PORTD ^= greenLed; //PD3 on the micro controller is linked to D3 on the shield
            vTaskDelayUntil(&xLastWakeUpTime, 500/portTICK_PERIOD_MS);  //passive Delay
            PORTD ^= greenLed;
            vTaskDelayUntil(&xLastWakeUpTime, 500/portTICK_PERIOD_MS);  //passive Delay
        }
    }
}

static void vCheckButtonPressed(void* pvParameters)
{
    while (1)
    {
        if (PIND & 0b00010000)
        {
            xSemaphoreGive(semaphore);
        }
    }
}