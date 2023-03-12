/*
 * File:   main.c
 * Author: Antonio Garcia
 *
 * Created on February 3, 2023, 2:14 PM
 */
/*M1 has step pin RD6 and DIR pin RD7 M2 has Step Pin RD4 and DIR pin RD5
 M1 needs PortE output and on with RE0 off and M2 needs PortC output and on with RC1 off*/


#include "pins_header.h"
#include <xc.h>
#define _XTAL_FREQ 4000000

void servo(int pos){
    if(pos == 100){
        PORTB |= 0x02;
        __delay_ms(1.5);
        PORTB &= ~0x02;
        __delay_ms(18.5);
    }
    if(pos == 10){
        PORTB |= 0x02;
        __delay_ms(0.75);
        PORTB &= ~0x02;
        __delay_ms(19.25);
    }
    return;
}

void main(void)
{
  // Create Bit-Shifting Variable
  //unsigned int i=0;
  // Set PORT 8-Pins To Be Output Pins
  TRISC = 0x00;
  //TRISB = 0x00;
  TRISE = 0x00;
  TRISD = 0x00;//changed motor 2 when set to inputs
  //TRISA = 0x00;
  // Set All PORT Pins To Be OFF (Initially) !
  //DDRD = 0xFF;
  PORTC = 0x00;
  PORTE = 0x00;
  //PORTB = 0x02;//RB1 IS PWM SIGNAL FOR SERVO MOTOR
  //PORTA = 0x00;
  PORTD = 0x20;//RD5 is DIR PIN FOR MOTOR 2, 0 is CW 1 is CCW RB7 is DIR PIN M1
  // Create The System's Main Routine !
  while(1)
  {
      PORTD = 0x20;
      for(int i = 0; i < 100;i++){
          //PORTC |= 0xFD;//0x02 might be dir pin
          //PORTC |= 0x00;
          //PORTE |= 0x02;//RE1 IS STEP PIN FOR MOTOR 1
          //PORTA |= 0xFF;
          //PORTB |= 0xFF;
          PORTD |= 0x5F;//RD4 IS STEP PIN FOR MOTOR 2
          __delay_ms(4);
          //PORTC &= ~0xFD;
          //PORTC &= ~0x02;
          //PORTE &= ~0x02;
          //PORTA &= ~0xFF;
          //PORTB &= ~0xFF;
          PORTD &= ~0x5F;
          __delay_ms(1);
      }
      PORTD = 0x80;
      
      for(int i = 0; i < 100;i++){
          //PORTC |= 0xFD;//0x02 might be dir pin
          //PORTC |= 0x00;
          //PORTE |= 0x02;//RE1 IS STEP PIN FOR MOTOR 1
          //PORTA |= 0xFF;
          //PORTB |= 0xFF;
          PORTD |= 0x5F;//RD4 IS STEP PIN FOR MOTOR 2
          __delay_ms(4);
          //PORTC &= ~0xFD;
          //PORTC &= ~0x02;
          //PORTE &= ~0x02;
          //PORTA &= ~0xFF;
          //PORTB &= ~0xFF;
          PORTD &= ~0x5F;
          __delay_ms(1);
      }
      /*PORTC = 0x00;
      for(int i = 0; i < 200;i++){
          PORTC |= 0xF0;
          __delay_ms(1);
          PORTD &= ~0xF0;
          __delay_ms(1);
      }*/
      //PORTD &= ~0x20;
    // Turn One Side
    /*for (int j=0; j<50; j++)//j<48 originally for both for loops
    {
        //PORTA = 0x00;
        PORTB = (1<<i);
        //PORTB |= (1<<i);
        //PORTC |= (1<<i);
        //PORTD |= (1<<i);
        i++;
        __delay_ms(100);  // step delay changes the speed the lower the speed the faster the stepper moves dont go to 10
        if (i==8)
            i=0;
    }*/
    // Wait For a Second !
    //__delay_ms(1000);
    // Turn The Other Side
    /*for (int j=0,i=0; j<12; j++)
    {   
        
          PORTB = (128>>i);
          //PORTB |= (8>>i);
          //PORTC |= (8>>i);
          //PORTD |= (8>>i);
          i++;
          __delay_ms(100); // StepDelay
          if (i==8)
              i=0;
    }*/
  }
  return;
}