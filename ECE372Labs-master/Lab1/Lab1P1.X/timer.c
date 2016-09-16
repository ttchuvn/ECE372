/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

//Initialize timer2's functionality
void initTimer2() {
    TMR2 = 0x0000;          //Clear timer 2
    T2CONbits.TCKPS = 0;    //Initialize the prescalar
    PR2 = 7;               //(8MHz)/1 * 1uS - 1 => 1uS timer
    T2CONbits.TCS = 0;      //TCS = "Timer Clock Source". Set to Peripheral Clock
    IEC0bits.T2IE = 0;      //Enable the interrupt
    IPC2bits.T2IP = 3;      //Configure the interrupt priority
    IFS0bits.T2IF = 0;      //Put the interrupt flag down
    T2CONbits.ON = 0;       //Don't enable the timer
    
}

//Uses timer 2
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR2 = 0x0000;              //Clear the timer
    IFS0bits.T2IF = 0;          //Put the flag down
    PR2 = 7*delay;         //Set the PR value
    T2CONbits.ON = 1;           //Enable the timer
    while (IFS0bits.T2IF == 0); //Wait
    T2CONbits.ON = 0;           //Turn the timer off and return
    IFS0bits.T2IF = 0;          //Put the flag down again
    return;
}