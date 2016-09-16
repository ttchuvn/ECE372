// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "config.h"

typedef enum stateTypeEnum {
    waitPush, waitRelease
} stateType;

volatile stateType state = waitPush;
volatile long long int myInt = 0;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    SYSTEMConfigPerformance(8000000);//clock at 8MHZ
    disableInterrupts();
    
    //initTestLEDs();
    initTimer2();
    initSW2();
    initLEDs();
    TRISDbits.TRISD0 = 0;
    enableInterrupts();
    while(1)
    {
//        delayUs(500);
//        toggleLEDs();
//        switch(state){
//            case waitPush:
//                if(IFS1bits.CNDIF == 1){
//                    state = waitRelease;
//                }
//                break;
//            case waitRelease:
//                If()
//                
//        }
        
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        //Pretty sure we don't really need to do anything in here
//        delayUs(500);
//        toggleLEDs();
        //delayUs(5000);                  //Delay 5mS as specified in procedures

//    switch (state) {                //And deal with updating the current state
//        case waitPush:
//            state = waitRelease;
//            break;
//        case waitRelease:
//            state = waitPush;
//            toggleLEDs();
//            break;
//    }
    }   
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button    
    int i = PORTDbits.RD6;
    IFS1bits.CNDIF = 0;             //Put the flag down    
    toggleLEDs();
    LATDbits.LATD0 = 1;
}
