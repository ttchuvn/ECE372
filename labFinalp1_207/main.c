/* 
* Author: TEAM 207
*
* Created on 10/22/2015
*
*/
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "lcd.h"
#include "switch.h"
#include "math.h"

#define flag  IFS1bits.CNDIF

//4 states, 4 debouncing switch pressed
typedef enum stateTypeEnum {
    Idle1, FWD, BCKWD, Idle2, 
    dbPress_Idle2, dbRelease_Idle2, waitRelease_Idle2,
    dbPress_FWD, dbRelease_FWD, waitRelease_FWD,       
    dbPress_BCKWD, dbRelease_BCKWD, waitRelease_BCKWD,   
    dbPress_Idle1, dbRelease_Idle1, waitRelease_Idle1, 
} stateType;

volatile stateType currState = Idle1;//set the current state to Idle1
volatile int adcVal = 0;//initialize the adcVal
volatile double voltage = 0;//initialize the voltage
char str[9];

int main(void){
    int i;
    SYSTEMConfigPerformance(40000000);
    initTimer1();
    initTimer2();
    initPWM();
    initSW();
    enableInterrupts();
    initLCD();
    clearLCD();
    initADC();    
    while (1) {              
         switch (currState) 
         {
            case Idle1:
                //LAT and TRI are OUTPUT
                TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
                TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;
                LAT_PIN0 = OUTPUT;LAT_PIN1 = OUTPUT;
                LAT_PIN2 = OUTPUT;LAT_PIN3 = OUTPUT;
                //OC2 RIGHT WHEEL (unmap all the pins))
                OC_PIN0 = 0b0000;OC_PIN1 = 0b0000;            
                //OC4 LEFTWHEEL (unmap all the pins))
                OC_PIN2 = 0b0000;OC_PIN3 = 0b0000;
                AD1CON1bits.ADON = 1;//turn the ADC on
            break;              
             case FWD:
                 //TRI is OUPUT
                TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
                TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;         
                //OC2 RIGHT WHEEL
                OC_PIN0 = 0b0000;//very important
                OC_PIN1 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
                //LAT_PIN0 = 0x0000;//not really need it
                //OC4 LEFTWHEEL
                OC_PIN2 = 0b0000;//very important
                OC_PIN3 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
                //LAT_PIN2 = 0x0000;//not really need it
                AD1CON1bits.ADON = 1;//turn the ADC on
                break; 
            case BCKWD:
                TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
                TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;
                //OC2 RIGHT WHEEL flip (map and unmap) the values of PIN0 and 1 to get the right wheel moving backward
                OC_PIN0 = 0b1011;//very important
                OC_PIN1 = 0b0000;    //11 is vanhoy magic number
                //LAT_PIN1 = 0x0000;
                //OC4 LEFTWHEEL--> flip (map and unmap) the values of PIN2 and 3 to get the left wheel moving backward
                OC_PIN2 = 0b1011;//very important
                OC_PIN3 = 0b0000;//11 is vanhoy magic number
                //LAT_PIN3 = 0x0000;                 
                AD1CON1bits.ADON = 1;//turn the ADC on
            break;  
            case Idle2:
                //LAT and TRI are OUTPUT
                TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
                TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;
                LAT_PIN0 = OUTPUT;LAT_PIN1 = OUTPUT;
                LAT_PIN2 = OUTPUT;LAT_PIN3 = OUTPUT;
                //OC2 RIGHT WHEEL
                OC_PIN0 = 0b0000;OC_PIN1 = 0b0000;            
                //OC4 LEFTWHEEL
                OC_PIN2 = 0b0000;OC_PIN3 = 0b0000;
                AD1CON1bits.ADON = 1;//turn the ADC on
            break;
                
            //debouncing for the switch 
            case dbPress_FWD:
                for(i=0;i<6;i++) delayUs(150);//delay 150*5=725 
                currState = waitRelease_FWD;
            break;
            case dbRelease_FWD:
                for(i=0;i<6;i++) delayUs(150); 
                currState = FWD; 
            break;
            case waitRelease_FWD:
            break;     
                
            case dbPress_Idle2:
                for(i=0;i<6;i++) delayUs(150); 
                currState = waitRelease_Idle2;
            break;
            case dbRelease_Idle2:
                for(i=0;i<6;i++) delayUs(150); 
                currState = Idle2;
            break;
            case waitRelease_Idle2:
            break;     
                
            case dbPress_BCKWD:
                for(i=0;i<6;i++) delayUs(150); 
                currState = waitRelease_BCKWD;
            break;
            case dbRelease_BCKWD:
                for(i=0;i<6;i++) delayUs(150); 
                currState = BCKWD;
            break;
            case waitRelease_BCKWD:
            break;
                
            case dbPress_Idle1:
                for(i=0;i<6;i++) delayUs(150); 
                currState = waitRelease_Idle1;
            break;
            case dbRelease_Idle1:
                for(i=0;i<6;i++) delayUs(150); 
                currState = Idle1;
            break;
            case waitRelease_Idle1:
                break;
         }
    }
    return 0;       
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){    
    IFS0bits.AD1IF = 0;   //Turns the flag down
    adcVal = ADC1BUF0;//get ACD value from buffer
    moveCursorLCD(0,0);
    voltage = (3.3/1023)*adcVal; //Scale to 3.3 max Volts with ADC
    sprintf(str, "%1.5fV", voltage); //print voltage read from ADC to a string
    printStringLCD(str);
     if(adcVal > 511){
        //Turned pot all the way to CW, keep right wheel on, then lowering the left wheel
        RIGHTWHEEL = abs((1023-adcVal)*2);
        LEFTWHEEL = 1023;
    }
    else if(adcVal < 500){
        //Turned pot all the way to CW, keep right wheel on, then lowering the left wheel
        RIGHTWHEEL = 1023;
        LEFTWHEEL = abs(adcVal*2);
     }
    else{
        //pot on the middle, both wheel should be on max
        LEFTWHEEL = 1023;   
        RIGHTWHEEL = 1023;
    }
    
    AD1CON1bits.ADON = 0;   //Turns off the ADC.
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    
    int dummy = PORTDbits.RD6;
    //interrupted service for state machine
    if(flag)//flag is high
    {
        if (currState == Idle1) 
            currState = dbPress_FWD;
        else if (currState == waitRelease_FWD)
            currState = dbRelease_FWD;
        else if (currState == FWD) 
            currState = dbPress_Idle2;
        else if (currState == waitRelease_Idle2) 
            currState = dbRelease_Idle2;
        else if (currState == Idle2) 
            currState = dbPress_BCKWD;
        else if (currState == waitRelease_BCKWD)
            currState = dbRelease_BCKWD;
        else if (currState == BCKWD)
            currState = dbPress_Idle1;
        else if (currState == waitRelease_Idle1)
            currState = dbRelease_Idle1; 
    }
    
    flag = 0; //put the flag down
         
}

