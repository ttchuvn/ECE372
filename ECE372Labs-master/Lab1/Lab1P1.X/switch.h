/* 
 * File:   switch.h
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#ifndef SWITCH_H
#define	SWITCH_H

//Config for using the expansion board:
//Use the given PORT switch as our input toggle switch
//#define mySwitch PORTGbits.RG13
//#define mySW_TRIS TRISGbits.TRISG13
//#define mySW_PU CNPUGbits.CNPUG13
//#define mySW_CNCON CNCONGbits.ON
//#define mySW_CNEN CNENGbits.CNIEG13
//#define mySW_IEC1 IEC1bits.CNGIE
//#define mySW_IFS IFS1bits.CNGIF

//Config for using builtin switches and LEDs:


//Define INPUT and OUTPUT for configuring TRIS registers




void initSW2();

#endif	/* SWITCH_H */

