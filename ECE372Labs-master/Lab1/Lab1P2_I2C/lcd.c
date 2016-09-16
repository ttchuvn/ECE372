/* 
 * File:   lcd.c
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:32 PM
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define OUTPUT 0
#define INPUT 1

#define UPPER 1
#define LOWER 0

#define CHARACTER 1

#define TRIS_RS   TRISGbits.TRISG14
#define TRIS_RW   TRISGbits.TRISG12 
#define TRIS_E    TRISGbits.TRISG15

#define TRIS_D4   TRISCbits.TRISC1
#define TRIS_D5   TRISDbits.TRISD10
#define TRIS_D6   TRISDbits.TRISD4
#define TRIS_D7   TRISEbits.TRISE0

#define LCD_DATA  LATB         // board
#define LCD_RS    LATGbits.LATG14 //4    4 on LCD
#define LCD_RW    LATGbits.LATG12 //3    5 on LCD 
#define LCD_E     LATGbits.LATG15 //1    6 on LCD

#define LCD_D4    LATCbits.LATC1 //18    11 on LCD
#define LCD_D5    LATDbits.LATD10 //16   12 on LCD
#define LCD_D6    LATDbits.LATD4 //14    13 on LCD  
#define LCD_D7    LATEbits.LATE0 //12    14 on LCD

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 * Lower == 1 means you're SENDING the lower 4 bits
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    word = (!lower) ? word>>4 : word;//write upper
    LCD_RS = (commandType) ? INPUT : OUTPUT; //set commandType
    delayUs(1);
    LCD_D7 = (word>>3) & 1; 
    LCD_D6 = (word>>2) & 1;
    LCD_D5 = (word>>1) & 1;
    LCD_D4 = word & 1; //and  with 1 to get left most bit        
    LCD_E = INPUT;
    delayUs(1);
    LCD_E = OUTPUT; 
    delayUs(delayAfter);
}
/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    writeFourBits(word, commandType, delayAfter,LOWER); //write lower
    writeFourBits(word, commandType, delayAfter,UPPER); //write upper
}
/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c,CHARACTER, 40);
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).    
    TRIS_D7 = OUTPUT;TRIS_D6 = OUTPUT;TRIS_D5 = OUTPUT; TRIS_D4 = OUTPUT;
    TRIS_RS = OUTPUT;TRIS_E = OUTPUT; 
    TRIS_RW = OUTPUT; LCD_RW = OUTPUT;

    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    int i;
    for(i=0;i<3;i++)
        delayUs(5000); //3*5000=15000 delay 15ms   
    writeFourBits(0b000011, 0, 40, 1); //000011
    delayUs(4100); // wait for 4.1ms or more
    writeFourBits(0b000011, 0, 40, 1); //000011
    delayUs(100); //wait 100us or more
    writeFourBits(0b000011, 0, 40, 1); //000011 functioni set 4 bits
    writeFourBits(0b000010, 0, 40, 1); //000010 functioni set 4 bits 
    
    writeLCD(0b101011, 0, 40);
    writeLCD(0b001000, 0, 40);    
    clearLCD();
    writeLCD(0b000110, 0, 40);
    writeLCD(0b001100, 0, 40);
    

    // Function Set (specifies data width, lines, and font.

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
        // Turn Display (D) Off
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
    while(*s != '\0')
    {
        printCharLCD(*s);
        s+=1;        
    }    
}
/*
 * Clear the display.
 */
void clearLCD(){
    writeLCD(0b000001, 0, 1640);
}
/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    if (y == 2)
        writeLCD(x+0x80+0x40,0, 40);//write the second line
    else     
        writeLCD(x+0x80,0, 40);//write the first line
}
/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    //printCharLCD('distance');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("distance");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("!!$%&*!!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}
