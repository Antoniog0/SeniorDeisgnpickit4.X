/*
 * File:   main.c
 * Author: Antonio Garcia
 *
 * Created on February 3, 2023, 2:14 PM
 */
/*M1 has step pin RD6 and DIR pin RD7 M2 has Step Pin RD4 and DIR pin RD5
 M1 needs PortE output and on with RE0 off and M2 needs PortC output and on with RC1 off*/

//input in mm and need to convert mm to steps


//One revolution 200 steps, is 32mm x axis unsure if same for y axis actually 31.86mm
//1800 steps is not enough to go from edge to edge on x axis but is large enough for an A4 sheet of paper
//32 mm on y axis for sure
//when going 45 degrees goes 22mm for 200 steps

#include "pins_header.h"
#include <xc.h>
#include <math.h>
#define _XTAL_FREQ 4000000

double currposx = 0; // should not pass 1800 revolutions or 288 mm
double currposy = 0;//need to find max amount of revolutions

//200/32 step per mm = 6.25
double mmaxisconversion(double inp){//32/200 = 0.16mm/step | assuming input is in mm
    double p = 0.0;
    double out = 0;
    double remainder = 0;
    p = inp / .16; //convert mm to steps
    remainder = inp * 100;
    remainder = (int)out % 16;//data loss here from trying to find the remainder
    if(remainder>=8){//round up
        out = p + 1;
    }
    else if(remainder < 8 && remainder != 0){
        out = p - 1;
    }
    out = p;
    return out;     
}

double mmangledconversion(double inp){//22/200 = 0.11mm/step |assuming input is in mm
    double p = 0.0;
    double out = 0;
    double remainder = 0;
    p = inp / .11; //convert mm to steps
    remainder = inp * 100;
    remainder = (int)out % 11;//data loss here from trying to find the remainder
    if(remainder>=8){//round up
        out = p + 1;
    }
    else if(remainder < 8 && remainder != 0){
        out = p - 1;
    }
    out = p;
    return out; 
}

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

void moveupright(double steps){//M2 CCW
    PORTD = 0x00;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x10;
        __delay_ms(2);
        PORTD &= ~0x10;
        __delay_ms(1);
    }
    return;
}

void movedownleft(double steps){//M2 CW
    PORTD = 0x20;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x10;
        __delay_ms(2);
        PORTD &= ~0x10;
        __delay_ms(1);
    }
    return;
}

void moveupleft(double steps){//M2 CCW
    PORTD = 0x80;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x40;
        __delay_ms(2);
        PORTD &= ~0x40;
        __delay_ms(1);
    }
    return;
}

void movedownright(double steps){//M2 CW
    PORTD = 0x00;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x40;
        __delay_ms(2);
        PORTD &= ~0x40;
        __delay_ms(1);
    }
    return;
}


void moveright(double steps){//pos x direction
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

void moveleft(double steps){//negative x direction
    PORTD = 0xA0;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

void movedown(double steps){
    PORTD = 0x20;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

void moveup(double steps){
    PORTD = 0x80;
    for(int i = 0; i < steps; i++){
        PORTD |= 0x50;
        __delay_ms(2);
        PORTD &= ~0x50;
        __delay_ms(1);
    }
    return;
}

/*void movetoPosition(float inpx, float inpy){
    float holdx, holdy = 0;
    holdx = inpx - posx;
    holdy = inpy - posy;
    if(holdx > 0){//x+ movement
        
    }
    if(holdy > 0){//y- movement 
        
    }
    return;
}*/

//float x, y, z = 0;
//char gcode[] = {'X','1','0','.','0',' ','Y','1','5','.','5'};
//char gcode[] = {'X', '9', ' '};



//int size = 3;
void position(char arrayinput[], int arraysize){
    int i = 0;
    double posholderx = 0;
    double posholdery = 0;
    int exp = 1;
    double positive = 0;
    double remainder = 0;
    double decimaleq = 0;
    double decimaleqy = 0;
    double decimaly = 0;
    double decimal = 0;
    int decimalcheck = 0;
    int xcheck = 0;
    int ycheck = 0;
    int zcheck = 0;
    double j = 0;
    int t = -1;
    for(int o = 0; o < arraysize; o++){
        if(arrayinput[o] == 'X'){
            //movedown(mmaxisconversion(10));
            xcheck = 1;
            //ycheck = 0;
        }
        else if(arrayinput[o] == 'Y'){
            ycheck = 1;
            //xcheck = 0;
            //moveup(mmaxisconversion(10));
        }
        else if (arrayinput[o] == 'Z'){
            zcheck = 1;
        }
        else if (arrayinput[o] == '2' && zcheck){//2 is up 3 is down
            servo(10);
            zcheck = 0;
        }
        else if (arrayinput[o] == '3' && zcheck){
            servo(100);
            zcheck = 0;
        }
        else if(arrayinput[o] == '.'){
            decimalcheck = 1;
            //moveup(mmaxisconversion(10));
        }
        else if((arrayinput[o] != ';' && decimalcheck == 0)&& arrayinput[o] != ' '){
        //else if(arrayinput[o] != ' '){
            //t = o;
            if(xcheck){
                posholderx = arrayinput[o] - '0';
                //decimal = posholderx - currposx;
                if(decimaleq > 0){
                    decimaleq = decimaleq * 10;
                }
                decimaleq += posholderx;
            }
            if(ycheck){
                posholdery = arrayinput[o] - '0';
                //decimal = posholderx - currposx;
                if(decimaleqy > 0){
                    decimaleqy = decimaleqy * 10;
                }
                decimaleqy += posholdery;
            }
            
        }
        
        else if((arrayinput[o] != ';' && decimalcheck == 1) && arrayinput[o] != ' '){
            if(xcheck){
                posholderx = arrayinput[o] - '0';
                for(int p = 0; p < exp; p++){
                    posholderx = posholderx / 10.0;
                }
                //posholderx = posholderx * 10^(-exp);
                exp++;
                decimaleq += posholderx;
            }
            else if(ycheck){
                posholdery = arrayinput[o] - '0';
                for(int p = 0; p < exp; p++){
                    posholdery = posholdery / 10.0;
                }
                //posholderx = posholderx * 10^(-exp);
                exp++;
                decimaleqy += posholdery;
            }
        }
        else if(arrayinput[o] == ';' || arrayinput[o] == ' '){
            //moveup(mmaxisconversion(20));
            decimalcheck = 0;
            exp = 1;
            decimal = decimaleq;
            decimaly = decimaleqy;
            decimaleq = 0;
            decimaleqy = 0;
            
            remainder = fmod(decimal,1.0);
            decimal = decimal - remainder;
            if(remainder >= 0.5){
                //decimal = decimal/1;
                decimal++;
            }
            remainder = fmod(decimaly,1.0);
            decimaly = decimaly - remainder;
            if(remainder >= 0.5){
                //decimal = decimal/1;
                decimaly++;
            }
            /*else{
                decimal = decimal/1;
            }*/
            double holds = 0;
            if(xcheck){//16 -> 79 63
                holds = 0;
                holds = decimal;
                decimal = decimal - currposx;
                if(decimal > 0){//check to see if xpos is out of bounds
                    moveright(mmaxisconversion(decimal));
                    currposx = holds;
                }
                else if(decimal < 0){
                    moveleft(mmaxisconversion(abs(decimal)));
                    currposx = currposx + holds;
                }
            }
            if(ycheck){
                holds = decimaly;
                decimaly = decimaly - currposy;
                if(decimaly > 0){//check to see if ypos is out of bounds
                    movedown(mmaxisconversion(decimaly));
                    currposy = holds;
                }
                else if(decimaly < 0){
                    moveup(mmaxisconversion(abs(decimaly)));
                    currposy = currposy + holds;
                }
            }
            xcheck = 0;
            ycheck = 0;
        }
    }
    
    
        /*decimal = posholderx - currposx;
            if(decimal > 0){//check to see if xpos is out of bounds
                moveright(mmaxisconversion(decimal));
            }
            else if(decimal < 0){
                moveleft(mmaxisconversion(decimal));
            }
        i++;*/
    /*while(i < arraysize){
        char currentchar = arrayinput[i];
        if(currentchar == 'X'){
            i++;
            currentchar = arrayinput[i];
            currentchar = currentchar - '0';
            posholderx += currentchar;
            while(arrayinput[j] != ' '){
                currentchar = arrayinput[j] - '0';
                posholderx += currentchar;
                j++;
            }
        }
        posholderx = arrayinput[1] - '0';
        decimal = posholderx - currposx;
            if(decimal > 0){//check to see if xpos is out of bounds
                moveright(mmaxisconversion(decimal));
            }
            else if(decimal < 0){
                moveleft(mmaxisconversion(decimal));
            }
        i++;
        
    }*/
    /*while(i < arraysize){//figure out how to traverse array
        if(arrayinput[i] == 'X'){//then read inputs from char array until next space char
            i++;
            while(arrayinput[i] != ' '){
                if((posholderx != 0) && (check != 0)){
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
            i++;
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
            decimal = posholderx - currposx;
            if(decimal > 0){//check to see if xpos is out of bounds
                moveright(mmaxisconversion(decimal));
            }
            else if(decimal < 0){
                moveleft(mmaxisconversion(decimal));
            }
            decimal = posholdery - currposy;
            if(decimal > 0){//check to see if ypos is out of bounds
                moveup(mmaxisconversion(decimal));
            }
            else if(decimal < 0){
                movedown(mmaxisconversion(decimal));
            }
            exp = 0;
            check = 0;
        }
        else if(arrayinput[i] == 'Z'){//'2' is up '3' is down
            i++;
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
    }*/
    return;
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
  //testing functions
  /*moveright(1700);//x axis limit 1700 steps (edges are assuming 0,0 is near corner)
  moveleft(1695);
  movedown(1300);//y axis limit 1300 
  moveup(1300);
  servo(10);
  servo(100);*/
  //testing mm converstion with motor movement functions above
  //moveright(mmaxisconversion(64));
  //moveleft(mmaxisconversion(64));
  //char gcode[] = "X10.2; Y10.5; ";
  char gcode[] = "G90; G1 X16.139583 Y46.831250; G91; G1 Z3.000000 G90; G1 X15.875000 Y47.095833; G1 X16.139583 Y46.831250; G1 X78.845833 Y46.831250; G1 X79.110417 Y47.095833; G1 X78.845833 Y46.831250; G91; G1 Z2.000000 G90; G91; G1 Z2.000000 G90;";
  //char gcode[] = "G90; G1 X16.139583 Y46.831250; G91; G1 Z3.000000 G90; G1 X15.875000 Y47.095833; G1 X16.139583 Y46.831250; G1 X78.845833 Y46.831250; G1 X79.110417 Y47.095833;";
  //char gcode[] = " G1 X78.845833 Y46.831250; G1 X79.110417 Y47.095833";
  //int size = (sizeof gcode) / (sizeof gcode[0]);
  int size = sizeof(gcode) / sizeof(char);
  size = size - 1;
  //int size = 5;
  position(gcode,size);
  //moveright(mmaxisconversion(78));
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