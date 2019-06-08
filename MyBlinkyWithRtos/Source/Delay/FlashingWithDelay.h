/*
 * FlashingWithDelay.h
 *
 *  Created on: 02-Jun-2019
 *      Author: ing12703
 */

#ifndef DELAY_FLASHINGWITHDELAY_H_
#define DELAY_FLASHINGWITHDELAY_H_

#define mainLED_TOGGLE_RATE					( ( portTickType ) 1000 / portTICK_RATE_MS )

#define partstLED1_OUTPUT		( 1 << 22 )
#define partstLED2_OUTPUT		( 1 << 4 )
/*
 * Very basic task that does nothing but use delays to flash an LED.
 */
static  void prvFlashTask( void *pvParameters );
void FlashingLEDWithDelay_Start();
#endif /* DELAY_FLASHINGWITHDELAY_H_ */
