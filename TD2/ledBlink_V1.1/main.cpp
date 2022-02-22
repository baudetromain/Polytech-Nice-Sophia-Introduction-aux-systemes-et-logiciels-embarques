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

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/


//Each task is assigned a priority from 0 to ( configMAX_PRIORITIES - 1 ), where configMAX_PRIORITIES is defined within FreeRTOSConfig.h. 
// Low priority numbers denote low priority tasks. The idle task has priority zero (tskIDLE_PRIORITY). 
#define mainLED_TASK_PRIORITY   (tskIDLE_PRIORITY)


//tasks handler defined after the main
static void vRedBlinkLed(void* pvParameters);
static void vGreenBlinkLed(void* pvParameters);

//constant to ease the reading....
const uint8_t redLed   = _BV(PD2);
const uint8_t greenLed = _BV(PD3);

int main(void)
{
    DDRD |= (redLed | greenLed); // PD2 and PD3 as outputs

    // Create task #1
    xTaskHandle redBlink_handle;
    xTaskCreate                     //documented here: https://www.freertos.org/a00125.html
    (
        vRedBlinkLed,               //pointer function to the handler
        (const char*)"redBlink",    //naming the task
        configMINIMAL_STACK_SIZE,   //stack size
        NULL,                       //parameters of the handler
        1U,                         //priority
        &redBlink_handle            //address of task handler
    );

    // Create task #2
    xTaskHandle greenBlink_handle;
    xTaskCreate
    (
        vGreenBlinkLed,
        (const char*)"greenBlink",
        configMINIMAL_STACK_SIZE,
        NULL,
        2U,
        &greenBlink_handle
    );
    
    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}


/**************************************************************************//**
 * \fn static void vGreenBlinkLed(void* pvParameters)
 *
 * \brief toggle the green led.
 *
 * \param[in]   pvParameters
 ******************************************************************************/

 static void vGreenBlinkLed(void* pvParameters)
{
    TickType_t xLastWakeUpTime = xTaskGetTickCount();
    while (1)
    {
        PORTD ^= greenLed; //PD3 on the micro controller is linked to D3 on the shield
        // vTaskDelayUntil(&xLastWakeUpTime, 500/portTICK_PERIOD_MS);  //passive Delay
    }
}

/**************************************************************************//**
 * \fn static void vRedBlinkLed(void* pvParameters)
 *
 * \brief  toggle the red led
 *
 * \param[in]   pvParameters
 ******************************************************************************/

 static void vRedBlinkLed(void* pvParameters)
{
    TickType_t xLastWakeUpTime = xTaskGetTickCount();
    while (1)
    {
        PORTD ^= redLed; //PD2 on the micro controller is linked to D2 on the shield
        // vTaskDelayUntil(&xLastWakeUpTime, 1000/portTICK_PERIOD_MS);  //passive Delay
    }
}

