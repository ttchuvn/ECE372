/*
 * File:   timer.c
 * Author: TEAM 207
 *
 * Created on 10/28/2015
 */
#include <xc.h>
#include "timer.h"
#include "interrupt.h"

void initTimer1(){
    TMR1 = 0x0000;      //Clear TMR1
    T1CONbits.TCKPS = 1;//Init pre-scaler 8
    T1CONbits.TCS = 0;//Setting the oscillator
    IFS0bits.T1IF = 0;//Put the flag down
    T1CONbits.ON = 0;//Turn timer off
}
//PWM uses Timer 2
void initTimer2(){
    TMR2 = 0x0000;//clear TMR2
    PR2 = 1023;
    T2CONbits.TCKPS = 0;//Init pre-scalar 
    T2CONbits.TCS = 0;//Setting the oscillator
    T2CONbits.ON = 1;//Turn timer on
}
void initTimer3(){
    TMR3 = 0x0000;//clear TMR3
    PR3 = 1023;
    T3CONbits.TCKPS = 0;//Init pre-scalar 
    T3CONbits.TCS = 0;//Setting the oscillator
    T3CONbits.ON = 1;//Turn timer on
}
//TODO: Create a delay using timer 1 for "delay" microseconds.
void delayUs(unsigned int delay){    
    if (delay == 0) return;
    TMR1 = 0x0000;               //Clear TMR1
    PR1 = delay * 8;          //prescalar to 8
    IFS0bits.T1IF = 0;      //Put flag down
    T1CONbits.ON = 1;        //Turn timer on
    while (IFS0bits.T1IF == 0); //Wait for change
    T1CONbits.ON = 0;       //Turn timer off
}
