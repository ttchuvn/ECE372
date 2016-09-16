/* 
 * File:   led.c
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "leds.h"
#include "adc.h"
#include "switch.h"
#include "lcd.h"

void assignColors()
{     
    sensorLeft = (sensorLeftReading < THRESHOLD) ? BLACK : WHITE;//sensor reading < threshold (500) --> black else white
    sensorMiddle = (sensorMiddleReading < THRESHOLD) ? BLACK : WHITE;
    sensorRight = (sensorRightReading < THRESHOLD) ? BLACK : WHITE;
}
