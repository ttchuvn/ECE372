// ******************************************************************************************* //
//
// File:         main.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
// Team: 207
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"


int main(void)
{    
    //printStringLCD("1000");
    //printStringLCD("distance: %$&##");
    while(1)
    {
        testLCD();
        //printStringLCD("distance: %$&##");
    }    
    return 0;
}