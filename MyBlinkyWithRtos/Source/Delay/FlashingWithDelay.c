/*
 * FlashingWithDelay.c
 *
 *  Created on: 02-Jun-2019
 *      Author: ing12703
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#endif
#include <cr_section_macros.h>
/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "FlashingWithDelay.h"

void FlashingLEDWithDelay_Start()
{
	/* Create the simple LED flash task. */
	xTaskCreate( prvFlashTask, ( const int8_t * const ) "Flash", configMINIMAL_STACK_SIZE, ( void * ) NULL, configI2C_TASK_PRIORITY, NULL );
}

void vParTestToggleLED( unsigned long ulLEDIn )
{
    unsigned long ulCurrentState;

	/* Used to toggle LEDs on FIO2. */

	if( ulLEDIn == 0 )
	{
		/* If this bit is already set, clear it, and vice versa. */
		ulCurrentState = GPIO_ReadValue(0);
		if( ulCurrentState & partstLED1_OUTPUT )
		{
			GPIO_ClearValue(0,partstLED1_OUTPUT);
		}
		else
		{
			GPIO_SetValue(0,partstLED1_OUTPUT);
		}
	}
	else if( ulLEDIn == 1 )
	{
		/* If this bit is already set, clear it, and vice versa. */
		ulCurrentState = GPIO_ReadValue(1);
		if( ulCurrentState & partstLED2_OUTPUT )
		{
			GPIO_ClearValue(1,partstLED2_OUTPUT);
		}
		else
		{
			GPIO_SetValue(1,partstLED2_OUTPUT);
		}
	}
}

static void prvFlashTask( void *pvParameters )
{
	portTickType xLastFlashTime;
	xLastFlashTime = xTaskGetTickCount();
	GPIO_SetDir(0,(uint32_t)(1<<22),1 );

	for(;;)
	{
		/* Simply toggle the LED between delays. */
		vTaskDelayUntil( &xLastFlashTime, mainLED_TOGGLE_RATE );
		vParTestToggleLED( 0 );
	}
}

