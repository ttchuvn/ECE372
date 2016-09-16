#include<p18f452.h>
 //#include<xlcd.h>
 #include<delays.h>
 
 
 #define KEYPORT PORTD
 #define col1 PORTCbits.RC4
 #define col2 PORTCbits.RC5
 #define col3 PORTCbits.RC6
 #define col4 PORTCbits.RC7
 #define TRUE 1
 #define FALSE 0
 
 
 void key_init(){
         TRISD=0x0F; //make Rows as o/p and cols are i/p
 }
 
 
 unsigned char get_key(){
         unsigned char i,k,key=0;
         k=1;
         for(i=0;i<4;i++){               //loop for 4 rows
                 KEYPORT =(0x08>>i) ;  //to make rows low 1 by 1
                 
                       if(col1==1){      //check if key1 is pressed
                                 key = k+0;      //set key number
                                 while(col1==1);   //wait for release
                                 return key;     //return key number
                         }
 
                         if(col2==1){      //check if key2 is pressed
                                 key = k+1;      //set key number
                                 while(col2==1);   //wait for release
                                 return key;     //return key number
                         }
 
                         if(col3==1){      //check if key3 is pressed
                                 key = k+2;      //set key number
                                 while(col3==1);   //wait for release
                                 return key;     //return key number
                         }
 
                         if(col4==1){      //check if key4 is pressed
                                 key = k+3;      //set key number
                                 while(col4==1);   //wait for release
                                 return key;     //return key number
                         }
 
                k+=4;                   //next row key number
                // KEYPORT = 0x80>>i;     //make the row high again
         }
         return FALSE;                   //return false if no key pressed
 }
 
 
 void main(void)
 {
 unsigned char key,j,k;
 TRISB=0;
 //TRISC=0;
 TRISD=0;
 
 /*PORTC=00;
 PORTD=00;
 PORTB=00;*/
 while(1)
 {
 for(j=0;j<16;j++)
 {
 key = get_key();    
 if (key ==1)
 {
   PORTBbits.RB1=0;
   Delay10KTCYx(500);
   PORTBbits.RB1=1;
   Delay10KTCYx(500);
  
 
 }
 
 if (key ==2)
 {
   for(j=0;j<2;j++)
 {
   PORTBbits.RB1=0;
   Delay10KTCYx(500);
   PORTBbits.RB1=1;
   Delay10KTCYx(500);
 }
   
 }
 
 if (key ==3)
 {
   for(j=0;j<3;j++)
 {
    PORTBbits.RB1=0;
    Delay10KTCYx(500);
    PORTBbits.RB1=1;
    Delay10KTCYx(500);
 }
   
 }