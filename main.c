/* 
 * File:   main.c
 * Author: Mahendra
 *
 * Created on September 5, 2018, 4:39 AM
 */
// PIC18F452 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1H
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bit (Brown-out Reset enabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "port.h"
#include "usart.h"
#include "adc.h"
/*
 * 
 */



char serialAvailable(void);

char tx_tick = 1;
char rx_temp, state, flag;
int advalue;

void main(void)
{
    port_Init();
    serial_init();
    ADC_init();
    PORTD = 0xFF;
    while (1)
    {
        if (serialAvailable())
        {
            switch (state)
            {
            case 'A':
                PORTBbits.RB0 = 0; // Light 1 on
                serial_println("Light 1 On");
                state = 0;
                break;
            case 'B': // Motor Reverse
                PORTBbits.RB0 = 1; // Light 1 off
                serial_println("Light 1 Off");
                state = 0;
                break;
            case 'C': // Motor Turn Right 
                PORTBbits.RB1 = 0; //Light 2 on
                serial_println("Light 2 On");
                state = 0;
                break;
            case 'D': // Motor Turn Left
                PORTBbits.RB1 = 1; //Light 2 Off 
                serial_println("Light 2 Off");
                state = 0;
                break;
            case 'E':
                PORTBbits.RB2 = 1; // Door Open
                serial_println("Door Open");
                state = 0;
                break;
            case 'F':
                PORTBbits.RB2 = 0; // Door Off
                serial_println("Door Off");
                state = 0;
                break;
            case 'W':
                advalue = AD_read();
                advalue = (advalue / 1024)*5; // Map function....
                if (advalue >= 1.25)
                {
                    serial_println("High Water Level");
                }
                else
                {
                    serial_println("Low Water Level");
                }
                state = 0;
                break;

            default:
                PORTDbits.RD0 = 0; // Stop 
                PORTDbits.RD1 = 0; // Stop 
                PORTDbits.RD2 = 0; // Stop
                PORTDbits.RD3 = 0; // Stop
                break;

            }
        }
    }
}

void __interrupt() isr(void)
{


    if (RCIF)
    {
        rx_temp = RCREG;
        if (RCSTAbits.OERR)
        {
            RCSTAbits.CREN = 0;
            NOP();
            NOP();
            RCSTAbits.CREN = 1;
        }

        flag = 1;
    }
}

char serialAvailable(void)
{
    flag = 0;
    state = rx_temp;
    return state;
}

