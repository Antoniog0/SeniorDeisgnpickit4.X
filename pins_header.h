// PIC18F46J50 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 2       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset (Disabled)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config CPUDIV = OSC4_PLL6// CPU System Clock Postscaler (CPU system clock divide by 6)
#pragma config CP0 = ON         // Code Protect (Program memory is code-protected)

// CONFIG2L
#pragma config OSC = INTOSC     // Oscillator (INTOSC)
#pragma config T1DIG = OFF      // T1OSCEN Enforcement (Secondary Oscillator clock source may not be selected)
#pragma config LPT1OSC = OFF     // Low-Power Timer1 Oscillator (Low-power operation)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2H
#pragma config WDTPS = 1        // Watchdog Postscaler (1:1)

// CONFIG3L
#pragma config DSWDTOSC = T1OSCREF// DSWDT Clock Select (DSWDT uses T1OSC/T1CKI)
#pragma config RTCOSC = INTOSCREF// RTCC Clock Select (RTCC uses INTRC)
#pragma config DSBOREN = OFF    // Deep Sleep BOR (Disabled)
#pragma config DSWDTEN = OFF    // Deep Sleep Watchdog Timer (Disabled)
#pragma config DSWDTPS = 2      // Deep Sleep Watchdog Postscaler (1:2 (2.1 ms))

// CONFIG3H
#pragma config IOL1WAY = OFF    // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set and cleared as needed)
#pragma config MSSP7B_EN = MSK5 // MSSP address masking (5 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_0    // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 0)
#pragma config WPEND = PAGE_0   // Write/Erase Protect Region Select (valid when WPDIS = 0) (Page 0 through WPFP<5:0> erase/write protected)
#pragma config WPCFG = ON       // Write/Erase Protect Configuration Region (Configuration Words page erase/write-protected)

// CONFIG4H
#pragma config WPDIS = ON       // Write Protect Disable bit (WPFP<5:0>/WPEND region erase/write protected)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

