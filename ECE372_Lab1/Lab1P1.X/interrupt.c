/* 
 * File:   interrupt.c
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:15 PM
 */
#include <xc.h>

void enableInterrupts(){
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    unsigned int status = 0;
    asm volatile("ei    %0" : "=r"(status));
}
