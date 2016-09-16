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
    while(1)
    {
        testLCD();
    }    
    return 0;
}