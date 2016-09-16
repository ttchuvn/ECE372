/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"


void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
    //This code is confirmed working.
    STOPLED_TRIS = OUTPUT;          //Set the stop LED as an output
    RUNLED_TRIS = OUTPUT;           //Set the run LED as an output
    DDPCONbits.TROEN = 1;        //Enable writing to TRD0, TRD1, TRD2, TRD3, ...
    STOPLED_LAT = LED_OFF;           //Start with the stop LED off
    RUNLED_LAT = LED_ON;             //And the start LED on
    return;
}

void toggleLEDs() {
    //This code is confirmed working
    RUNLED_LAT = (RUNLED_LAT == LED_ON) ? LED_OFF : LED_ON;
    STOPLED_LAT = !RUNLED_LAT;
}