/* 
 * File:   pwm.c
 * Author: gvanhoy
 * Team: 207
 * Created on 10/28/2015
 */

#include <xc.h>
#include "pwm.h"

void initWheel(){    
    //RIGHTWHEEL
    TRI_PIN0 = OUTPUT; //
    TRI_PIN1 = OUTPUT; //
    //LEFTWHEEL
    TRI_PIN2 = OUTPUT; //  
    TRI_PIN3 = OUTPUT; //
}        
void initPWM(){    
    //Init PWM for OC2
    //RPD0Rbits.RPD0R = 0b1011; // map OC2 to RD0
    OC2CON = 0x0000; // Turn off OC2 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC2
    
    //Init PWM for OC4
    //RPD2Rbits.RPD2R = 0b1011; // map OC4 to RD2
    OC4CON = 0x0000; // Turn off OC4 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0x0000; // Initialize secondary Compare Register
    OC4CON = 0x0006; // Configure for PWM mode
    OC4CONSET = 0x8000; // Enable OC4      
}
