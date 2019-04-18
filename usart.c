#include <xc.h>
#include "usart.h"

void serial_init(void)
{
    TRISCbits.TRISC6 = 0;   // TX pin
    TRISCbits.TRISC7 = 1;   // RX pin
     
   
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    SPBRG = 25;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;

    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void serial_write(char data)
{
    while (!TRMT)
        ;
    TXREG = data;
}

void serial_print(const char *buffer)
{
    int i;
    for (i = 0; buffer[i] != '\0'; i++)
    {
        serial_write(buffer[i]);
    }
}

void serial_println(const char *buffer)
{
    serial_print(buffer);
    serial_write(0x0D);    //ascii value for '\r'
    serial_write(0x0A);    //ascii value for '\n'
}

