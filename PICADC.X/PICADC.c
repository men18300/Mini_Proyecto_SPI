//Universidad del Valle de Guatemala
//Digital 2
//Diego Mencoss 18300
//Slave 1-ADC



#define _XTAL_FREQ 8000000

#include <xc.h>
#include "ADC.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "SPI.h"


//Definimos variables
uint8_t contador;


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




//Prototipos de funciones
void setup(void);
void __interrupt() isr(void);



//Configuramos interrupciones
void __interrupt() isr(void) {

    if (PIR1bits.ADIF == 1) {
        PORTD = ADRESH;
        contador = PORTD;
        PIR1bits.ADIF = 0;
        __delay_ms(0.4);
        ADCON0bits.GO = 1;
    } else if (SSPIF == 1) {
        PORTE = spiRead();
        spiWrite(PORTD);
        SSPIF = 0;
    }
}

int main() {
    setup();
    ADC(0, 0); //Seleccionamos canal AN0 y justificado a la izquierda
    ADCON0bits.GO_nDONE = 1;
    while (1) {

    }
    return 0;
}

void setup(void) {
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISA=0b00100000;
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
    contador = 0;

 
    INTCONbits.GIE = 1; // Habilitamos interrupciones
    INTCONbits.PEIE = 1; // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0; // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1; // Habilitamos interrupción MSSP


    //Configuramos la comunicacion SPI
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}
