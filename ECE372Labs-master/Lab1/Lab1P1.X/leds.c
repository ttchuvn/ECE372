/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"

#define STOPLED_PORT PORTDbits.RD0
#define RUNLED_PORT PORTDbits.RD1

#define LED_ON 1
#define LED_OFF 0

#define INPUT 1
#define OUTPUT 0

void initLEDs(){
    TRISDbits.TRISD0 = OUTPUT; //stop LED = output
    TRISDbits.TRISD1 = OUTPUT; //run LED = output
    DDPCONbits.TROEN = 1; //enable writing to TRDx        
    LATDbits.LATD0 = LED_OFF;//stop LED off
    LATDbits.LATD1 = LED_ON;//run LED on
    return;
}

//toggle the LEDs
void toggleLEDs() {
    if (LATDbits.LATD1 == LED_ON)//if runLED is on
        LATDbits.LATD1 == LED_OFF;//set runLED is off
    else
        LATDbits.LATD1 == LED_ON;//else runLED is on    
    LATDbits.LATD0 = !LATDbits.LATD1;//stop LED = !runLED
}