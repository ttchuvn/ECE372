/* 
 * File:   main.c
 * Author: 207
 *
 * Created on November 9, 2015, 2:02 PM
 */
#include <sys/attribs.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "interrupt.h"
#include "lcd.h"
#include "config.h"
#include "timer.h"
#include "pwm.h"
#include "switch.h"
#include "leds.h"
#define flag  IFS1bits.CNDIF
//6 states, 1 debouncing switch pressed
typedef enum stateTypeEnum
{
    IdleState, forwardState, turnLeftState, turnRightState, turnAroundState, dbPress_Idle, waitRelease_Idle, dbRelease_Idle
} stateType;

volatile stateType currState = IdleState;//set current state to IdleState
char str[16];

int main(void)
{
    SYSTEMConfigPerformance(40000000);    
    initPWM();
    //initSW();     
    enableInterrupts();
    initLCD();
    clearLCD();     
    initADC();
    initWheel();  
//    initTimer1();
//    initTimer2();
    initTimer3();
    while(1)
    {     
       robotBehaviors();  
        potADCVal = potADC(); 
        sensorLeftReading = leftSensorADC();
        sensorMiddleReading = middleSensorADC();
        sensorRightReading = rightSensorADC();               
        //moveCursorLCD(0,1);
        sprintf(str, "  %d", potADCVal); 
        //printStringLCD(str);       
        //moveCursorLCD(0,2);
        sprintf(str, "%d:%d:%d", sensorLeftReading/10, sensorMiddleReading/10, sensorRightReading/10);
        //printStringLCD(str); 
        //robotBehaviors();
       switch(currState)
       {
           case IdleState:
                IdleFunction();            
                if(!SW){currState = dbPress_Idle;}
                break;
            case dbPress_Idle:
                delayMs(10);
                currState = waitRelease_Idle;
                break;
            
            case waitRelease_Idle:
                if(!SW){currState = dbRelease_Idle;}
                break;        
            case dbRelease_Idle:
                delayMs(10);
                currState = forwardState;
                break; 
            case forwardState:
               goForward();
               //delayMs(10);
               //AD1CON1bits.ADON = 1;
               break;
            case turnRightState:
               turnRight();
               //delayMs(10);
               //AD1CON1bits.ADON = 1;
               break;
            case turnLeftState:
               turnLeft();
               //delayMs(10);
               //AD1CON1bits.ADON = 1;
               break;            
            case turnAroundState:
               turnAround();
               //delayMs(10);
               //AD1CON1bits.ADON = 1;
               break;      
       }
    }
    return 0;
}
//void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void)
robotBehaviors()
{    //Turns the flag down
    //IFS0bits.AD1IF = 0;   
    
    if(currState != IdleState)
    {
        assignColors();
        if ((!sensorLeft && sensorMiddle && !sensorRight)||(sensorLeft && sensorMiddle && !sensorRight))
        {
            clearLCD(); 
            currState = forwardState;
            moveCursorLCD(0,1);
            printStringLCD("010||110");
            moveCursorLCD(0,2);
            printStringLCD("Forward");
        }
        else if(!sensorLeft && !sensorMiddle && sensorRight) //001
        {
            clearLCD(); 
            currState = turnRightState;
            moveCursorLCD(0,1);
            printStringLCD("     001");
            moveCursorLCD(0,2);
            printStringLCD("   Right");
        }         
        else if(sensorLeft && !sensorMiddle && !sensorRight) //100 
        {
            clearLCD(); 
            currState = turnLeftState;
            moveCursorLCD(0,1);
            printStringLCD("100");
            moveCursorLCD(0,2);
            printStringLCD("Left");
        }
        else if(!sensorLeft && !sensorMiddle && !sensorRight) //000
        {
            clearLCD(); 
            delayUs(10);
            currState = turnAroundState;
            moveCursorLCD(0,1);
            printStringLCD("  000");
            moveCursorLCD(0,2);
            printStringLCD(" Around");
            //delayUs(10);
        }
        else if(sensorLeft && sensorMiddle && sensorRight) //111
        {
            clearLCD(); 
            delayUs(10);
            currState = turnAroundState;
            moveCursorLCD(0,1);
            printStringLCD("  000");
            moveCursorLCD(0,2);
            printStringLCD(" Around");
            //delayUs(10);
        }
    }
    //AD1CON1bits.ADON = 0;//turn off ADC
}
//void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
//    
//    int dummyVariable = PORTDbits.RD6;
//    if(flag)
//    {
//        if (currState == IdleState) 
//        { 
//            currState = dbPress_Idle;
//        }
//        else if (currState == waitRelease_Idle) 
//        {
//            currState = dbRelease_Idle;
//        }   
//    }
//   flag = 0;         
//}