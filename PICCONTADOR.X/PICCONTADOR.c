//Universidad del Valle de Guatemala
//Digital 2
//Diego Mencoss 18300
//Slave 2-Contador

#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdint.h> 
#include <stdio.h>
#include "SPI.h"

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


//******************************************************************************
//Variables
//******************************************************************************
#define incrementar PORTBbits.RB0
#define decrementar PORTBbits.RB1
uint8_t contador; //entero de 8 bits sin signo



//*****************************************************************************
//Prototipos de funciones
//******************************************************************************
void setup(void);
void __interrupt() isr(void);

//******************************************************************************
//Interrupciones
//******************************************************************************

void __interrupt() isr(void) {
    if (INTCONbits.RBIF == 1) {
        if (incrementar == 1) {
            PORTD++; //Incrementar el contador
            contador = PORTD;

        } else if (decrementar == 1) {
            PORTD--; //Decrementar el contador
            contador = PORTD;

        }
        else if (SSPIF == 1) {
            PORTE = spiRead();
            spiWrite(PORTD);
            SSPIF = 0;
        }
        INTCONbits.RBIF = 0;
    }

}




//*****************************************************************************
//Ciclo Principal
//*****************************************************************************

void main(void) {
    setup();
    while (1) {
        spiWrite(PORTD); //Estamos constantemente mandando el valor del PORTD
                        //por la comunicacion SPI
    }
    return;
}

//*****************************************************************************
//Configuracion
//****************************************************************************

void setup(void) {

    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00100000;
    PORTA = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISC = 0b00011000;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
    INTCONbits.GIE = 1; //Habilitamos las interrupciones
    INTCONbits.PEIE = 1;
    INTCONbits.RBIE = 1; //
    INTCONbits.RBIF = 0;
    IOCBbits.IOCB0 = 1; //Interrupt on change del B0
    IOCBbits.IOCB1 = 1; //iNTERUPTN ON CHANGE DEL B1

    INTCONbits.GIE = 1; // Habilitamos interrupciones
    INTCONbits.PEIE = 1; // Habilitamos interrupciones PEIE

    //Configuramos la comunicacion SPI
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}
