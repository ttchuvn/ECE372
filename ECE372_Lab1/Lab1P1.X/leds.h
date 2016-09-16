/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

//Config for testing off of the expansion board:
//#define STOPLED_TRIS TRISGbits.TRISG12
//#define STOPLED_PORT PORTGbits.RG12
//#define STOPLED_LAT LATGbits.LATG12
//#define RUNLED_TRIS TRISGbits.TRISG14
//#define RUNLED_PORT PORTGbits.RG14
//#define RUNLED_LAT LATGbits.LATG14

//Config for testing off of internal builtin LEDs (RD0 and RD1)
#define STOPLED_TRIS TRISDbits.TRISD0
#define STOPLED_PORT PORTDbits.RD0
#define STOPLED_LAT LATDbits.LATD0
#define RUNLED_TRIS TRISDbits.TRISD1
#define RUNLED_PORT PORTDbits.RD1
#define RUNLED_LAT LATDbits.LATD1

#define INPUT 1
#define OUTPUT 0

#define LED_ON 1
#define LED_OFF 0

void initLEDs();
void toggleLEDs();

#endif	/* LEDS_H */

