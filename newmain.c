/*
 * File:   main.c
 * Author: Antonio Garcia
 *
 * Created on February 3, 2023, 2:14 PM
 */
/*M1 has step pin RD6 and DIR pin RD7 M2 has Step Pin RD4 and DIR pin RD5
 M1 needs PortE output and on with RE0 off and M2 needs PortC output and on with RC1 off*/


//One revolution 200 steps, is 32mm x axis unsure if same for y axis actually 31.86mm
//1800 steps is not enough to go from edge to edge on x axis but is large enough for an A4 sheet of paper
//32 mm on y axis for sure
//when going 45 degrees goes 22mm

#include "pins_header.h"
#include <xc.h>
#define _XTAL_FREQ 4000000

float posx = 0; // should not pass 1800 revolutions or 288 mm
float posy = 0;//need to find max amount of revolutions

void servo(int pos){//need to add a big ass for loop to make sure it pulses 
    //enough to move to the desired position then turn off
    for(int i = 0; i < 25; i++){
        if(pos == 100){//down
            PORTB |= 0x02;
            __delay_ms(1.5);
            PORTB &= ~0x02;
            __delay_ms(18.5);
        }
        if(pos == 10){//up
            PORTB |= 0x02;
            __delay_ms(0.75);
            PORTB &= ~0x02;
            __delay_ms(19.25);
        }
    }
    return;
}

void moveright(int steps){//pos x direction
    //RD4 = 0;
    //RD6 = 0;
    PORTD = 0x00;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

void moveleft(int steps){//negative x direction
    PORTD = 0xA0;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

void movedown(int steps){
    PORTD = 0x20;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

void moveup(int steps){
    PORTD = 0x80;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

void movetoPosition(float inpx, float inpy){
    float holdx, holdy = 0;
    holdx = inpx - posx;
    holdy = inpy - posy;
    if(holdx > 0){//x+ movement
        
    }
    if(holdy > 0){//y- movement 
        
    }
    return;
}

float x, y, z = 0;

void position(char arrayinput[], int arraysize){
    int i = 0;
    float posholderx = 0;
    float posholdery = 0;
    int exp = 1;
    float decimal = 0;
    int check = 0;
    while(i < arraysize){//figure out how to traverse array
        if(arrayinput[i] == 'X'){//then read inputs from char array until next space char
            while(arrayinput[i] != ' '){
                if(posholderx != 0 && check != 0){
                    posholderx *= 10;
                    posholderx += arrayinput[i];
                }
                else if(check){
                    decimal = arrayinput[i] * 10^(-exp);
                    posholderx += decimal;
                    exp++;
                }
                else if(arrayinput[i] == '.'){
                    check = 1;
                }
                else{
                    posholderx += arrayinput[i];
                }
                i++;
            }
            exp = 0;
            check = 0;
        }
        else if(arrayinput[i] == 'Y'){
            while(arrayinput[i] != ' '){
                if(posholdery != 0 && check != 0){
                    posholdery *= 10;
                    posholdery += arrayinput[i];
                }
                else if(check){
                    decimal = arrayinput[i] * 10^(-exp);
                    posholdery += decimal;
                    exp++;
                }
                else if(arrayinput[i] == '.'){
                    check = 1;
                }
                else{
                    posholdery += arrayinput[i];
                }
                i++;
            }
            exp = 0;
            check = 0;
        }
        else if(arrayinput[i] == 'Z'){//'2' is up '3' is down
            while(arrayinput[i] != ' '){
                if(arrayinput[i] == '2'){
                    servo(10);
                }
                else if(arrayinput[i] == '3'){
                    servo(100);
                }
                i++;
            }
        }
        i++;
    }
}

void main(void)
{
  // Create Bit-Shifting Variable
  //unsigned int i=0;
  // Set PORT 8-Pins To Be Output Pins
  TRISC = 0x00;
  TRISB = 0x00;
  TRISE = 0x00;
  TRISD = 0x00;//changed motor 2 when set to inputs
  /*TRISB1 = 0;
  TRISD4 = 0;
  TRISD5 = 0;
  TRISD6 = 0;
  TRISD7 = 0;*/
  //TRISA = 0x00;
  // Set All PORT Pins To Be OFF (Initially) !
  //DDRD = 0xFF;
  PORTC = 0x00;
  PORTE = 0x00;
  PORTB = 0x02;//RB1 IS PWM SIGNAL FOR SERVO MOTOR
  //RB1 = 1;
  //PORTA = 0x00;
  /*RD4 = 0;
  RD5 = 0;
  RD6 = 0;
  RD7 = 0;*/
  PORTD = 0x00;//RD5 is DIR PIN FOR MOTOR 2, 0 is CW 1 is CCW RD7 is DIR PIN M1
  // Create The System's Main Routine !
  //Test stepper motors for x-y direction
  //servo(100);
  /*for(int i = 0; i < 1800; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x50;
      __delay_ms(2);
      PORTD &= ~0x50;
      __delay_ms(1);
  }
  PORTD = 0xA0; //moves -x direction
  for(int i = 0; i < 1800; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x50;
      __delay_ms(2);
      PORTD &= ~0x50;
      __delay_ms(1);
  }*/
  /*PORTD = 0x20; // moves -y direction
  for(int i = 0; i < 200; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x10;
      __delay_ms(2);
      PORTD &= ~0x10;
      __delay_ms(1);
  }
  PORTD = 0x00;
  for(int i = 0; i < 400; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x50;
      __delay_ms(2);
      PORTD &= ~0x50;
      __delay_ms(1);
  }
  PORTD = 0xA0; //moves -x direction
  for(int i = 0; i < 200; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x50;
      __delay_ms(2);
      PORTD &= ~0x50;
      __delay_ms(1);
  }
  PORTD = 0x80;//moves +y direction
  for(int i = 0; i < 200; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x10;
      __delay_ms(2);
      PORTD &= ~0x10;
      __delay_ms(1);    
  }
  PORTD = 0x20; // moves -y direction
  for(int i = 0; i < 200; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x40;
      __delay_ms(2);
      PORTD &= ~0x40;
      __delay_ms(1);
  }
  PORTD = 0x80;//moves +y direction
  for(int i = 0; i < 200; i++){//200 because 200 steps in a revolution MOVES X+ DIRECTION
      PORTD |= 0x40;
      __delay_ms(2);
      PORTD &= ~0x40;
      __delay_ms(1);    
  }*/
  moveright(1700);
  moveleft(1695);
  movedown(1300);
  moveup(1300);
  servo(10);
  servo(100);
  while(1) {
      //servo(100);
  }
  /*while(1)
  {
      PORTD = 0x20;
      for(int i = 0; i < 200;i++){
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
      
      for(int i = 0; i < 200;i++){
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
      }*/
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
  //}
  return;
}