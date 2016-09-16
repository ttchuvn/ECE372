/* 
 * File:   switch.c
* Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#define INPUT 1
#define OUTPUT 0

#define ENABLED 1 
#define DISABLED 0

void initSwitch1(){
    //TODO: Initialize switch 1\
    //TRISAbits.TRISA7 = INPUT; //TRD3/RA7
    //TRISDbits.TRISD6 = INPUT;//Initialize switch
    //PORTGbits.RG13 == INPUT
    TRISGbits.TRISG13 = INPUT;
    CNPUGbits.CNPUG13 = ENABLED;//pull up register
    IFS1bits.CNAIF = 0;        // Put down the flag
    IPC8bits.CNIP = 2;         // Configure interrupt priority
    IPC8bits.CNIS = 3;         // Configure the interrupt sub-priority
    IEC1bits.CNAIE = ENABLED;  // Enable interrupt for pin
}