/* 
 * File:   led.c
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#define OUTPUT 0
#define INPUT 1
void initLEDs(){
    //TODO: Initialize LEDs 
//    TRISDbits.TRISD0 = OUTPUT; //Set top LED to zero
//    TRISDbits.TRISD1 = OUTPUT; //Set middle LED to zero
    TRISGbits.TRISG12 = OUTPUT;
    TRISGbits.TRISG14 = OUTPUT;
    //TRISDbits.TRISD2 = OUTPUT; //Set bottom LED to zero
    //Set LAD all to zero
//    LATDbits.LATD0 = OUTPUT;   
//    LATDbits.LATD1 = OUTPUT; 
    //real board
    LATGbits.LATG12 = OUTPUT;
    LATGbits.LATG14 = OUTPUT;
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    switch (led) {
        case 0:
            LATGbits.LATG12 = 1;
            LATGbits.LATG14 = 0;
            break;
        case 1:
            LATGbits.LATG12 = 0;
            LATGbits.LATG14 = 1;
            break;
        default:
            LATGbits.LATG12 = 0;
            LATGbits.LATG14 = 0;
            
            break;
    }    
}