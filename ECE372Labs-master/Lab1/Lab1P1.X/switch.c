/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#include <proc/p32mx470f512l.h>

#include "switch.h"
#define INPUT 1
#define OUTPUT 0

//Define pressed and not-pressed
#define SW_ON  0
#define SW_OFF 1

void initSW2(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
 
    TRISDbits.TRISD6 = INPUT;//Configure the switch as an input     
    CNCONDbits.ON = 1;   //Enable the overall CN interrupt     
    CNENDbits.CNIED6 = 1;//Enable the interrupt for our        
    CNPUDbits.CNPUD6 = 1;//Enable internal pull-up resistor
                        //=> reading a "0" from this means it's pressed     
    IFS1bits.CNDIF = 0;//Put flag down
    IPC8bits.CNIP = 2;  //Priority
    //IPC8bits.CNIS = 3;  //Subpriority     
    IEC1bits.CNDIE = 1;//Enable the interrupt for our switch's group of pins
}

