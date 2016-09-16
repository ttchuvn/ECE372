/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define LCD_DATA  
#define LCD_RS  
#define LCD_E   

#define TRIS_D7 
#define TRIS_D6 
#define TRIS_D5 
#define TRIS_D4 
#define TRIS_RS 
#define TRIS_E  

//These make some magic numbers into boring, magic-less words
#define OUTPUT 0
#define FUNCTION 0 //functions use RS = 0
#define CHARACTER 1 //while CHARACTERS use RS = 1


//Defines for the data pins that will send stuff to the LCD from the MCU
#define DATA7 LATBbits.LATB0
#define DATA6 LATBbits.LATB2
#define DATA5 LATBbits.LATB4
#define DATA4 LATBbits.LATB6
#define RWPIN dummy//add the RW and RS pins here 
#define RSPIN dummy


//Some LCD commands defined right here for convenience
//These are defined as DB7:DB0,commandType,delayTime(in microseconds)
#define LCD_CLEAR_CMD   1,0,82
#define LCD_HOME_CMD    2,0,40

//Some LCD Masks to be used 
#define LCD_ENTRY_MODE



/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 * Lower == 1 means you're SENDING the lower 4 bits
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    word = lower? (word & 0x0F) : ((word & 0xF0) >> 4); //now, the lower 4 bits of word are the bits to send
    RWPIN = 0;
    RSPIN = commandType;
    DATA7 = word & 1 << 7;
    DATA6 = word & 1 << 6;
    DATA5 = word & 1 << 5;
    DATA4 = word & 1 << 4;
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    writeFourBits(word, commandType, delayAfter, 1);
    writeFourBits(word, commandType, delayAfter, 0);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    writeLCD(c, CHARACTER, );
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).

    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    // Enable 4-bit interface

    // Function Set (specifies data width, lines, and font).

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
        // Turn Display (D) Off
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    
    
    //^^All that stuff is crazy
    
    //Set all the pins as OUTPUTs and set them to 0
    TRISBbits.TRISB0 = OUTPUT;  TRISBbits.TRISB2 = OUTPUT;
    TRISBbits.TRISB4 = OUTPUT;  TRISBbits.TRISB6 = OUTPUT; 
//    #error Set up the RS and RW pins as outputs
    DATA7= 0;    DATA6 = 0;    DATA5 = 0;    DATA4 = 0;
//    #error Initialize the RS and RW pins to originally output 0
    //fill in the rest..
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
}

/*
 * Clear the display.
 */
void clearLCD(){
    writeLCD(LCD_CLEAR_CMD);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}