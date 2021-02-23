#define _XTAL_FREQ 8000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "SPI.h"
#include "lcd.h"




uint8_t contador;
uint8_t slave1;
uint8_t slave2;
uint8_t slave3;
unsigned short S1;
unsigned short t;

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



void setup(void);
//unsigned short escribiryleer(unsigned short x);

void main() {
    setup();
    Lcd_Init();
    Lcd_Clear();

    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("S1:");
    Lcd_Set_Cursor(1, 8);
    Lcd_Write_String("S2:");
    Lcd_Set_Cursor(1, 14);
    Lcd_Write_String("S3:");


    while (1) {





        PORTCbits.RC2 = 0; //Slave Select
        __delay_ms(1);

        spiWrite(PORTB);
        slave1 = spiRead();

        __delay_ms(1);
        PORTCbits.RC2 = 1; //Slave Deselect 


        PORTCbits.RC1 = 0; //Slave Select
        __delay_ms(1);

        spiWrite(1);
        slave2 = spiRead();

        __delay_ms(1);
        PORTCbits.RC1 = 1; //Slave Deselect 


        PORTCbits.RC0 = 0; //Slave Select
        __delay_ms(1);

        spiWrite(1);
        slave3 = spiRead();

        __delay_ms(1);
        PORTCbits.RC0 = 1; //Slave Deselect 






    }
}

void setup(void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;

    PORTA = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISC = 0;
    TRISCbits.TRISC4 = 1;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
    INTCONbits.GIE = 1; //Habilitamos las interrupciones
    INTCONbits.PEIE = 1;

    contador = 0;


    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC0 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);



}
