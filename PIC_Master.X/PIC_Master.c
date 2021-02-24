//Universidad del Valle de Guatemala
//Digital 2
//Diego Mencoss 18300
//Master



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
#include "USART.h"



//Definicion de variables
uint8_t slave1;
uint8_t slave2;
int8_t slave3;

uint16_t valor;
unsigned char valorRX;

char unidadV;
char decenaV;
char centenaV;

char unidadVcontador;
char decenaVcontador;
char centenaVcontador;

char unidadVtemperatura;
char decenaVtemperatura;
char centenaVtemperatura;
char signo;

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


//Prototipo de FUnciones
void setup(void);
void __interrupt() isr(void);
void conv_Numero_A_String(uint8_t x);
void conv_Numero_A_StringContador(uint8_t x);
void conv_Numero_A_StringTemperatura(uint8_t x);



//Interrupciones

void __interrupt() isr(void) {

    if (PIR1bits.RCIF == 1) {
        valorRX = UART_get_char(); //Aqui recibimos el dato de la recepcion
        __delay_ms(0.4);
        PIR1bits.RCIF = 0;
    }
}

void main() {
    setup(); //Llamamos a la configuracion
    Lcd_Init(); //Inicializamos el LCD
    Lcd_Clear(); //Limpiamos el LCD
    UART_config(); //Configuramos la transmision y recepcion USART

    //Menu cual nos da la opcion de seleccinar que variable queremos ver

    UART_send_string("PRESIONE: ");
    UART_send_char(13);
    UART_send_string(" 'a'- Para mostrar el ADC");
    UART_send_char(13);
    UART_send_string(" 'b'- Para mostrar el contador");
    UART_send_char(13);
    UART_send_string(" 'c'- Para mostrar el Termometro");
    UART_send_char(13);

    //Mostramos en la LCD los comando S1,S2,S3
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("S1:");
    Lcd_Set_Cursor(1, 8);
    Lcd_Write_String("S2:");
    Lcd_Set_Cursor(1, 14);
    Lcd_Write_String("S3:");


    while (1) {



        //Llamamos al primer SLAVE 1-ADC
        PORTCbits.RC2 = 0; //Slave Select 1
        __delay_ms(1);

        spiWrite(PORTB);
        slave1 = spiRead(); //Copiamos a la variable el ADC

        __delay_ms(1);
        PORTCbits.RC2 = 1; //Slave Deselect 1

        //Convertimos el valor en distintos char para poder desplegarlos en la 
        //LCD
        conv_Numero_A_String(slave1);
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Char(unidadV);

        Lcd_Set_Cursor(2, 2);
        Lcd_Write_String(".");

        Lcd_Set_Cursor(2, 3);
        Lcd_Write_Char(decenaV);

        Lcd_Set_Cursor(2, 4);
        Lcd_Write_Char(centenaV);


        //Llamamos al segundo SLAVE 2-Contador
        PORTCbits.RC1 = 0; //Slave Select 2-Contador
        __delay_ms(1);

        spiWrite(1);
        slave2 = spiRead();

        __delay_ms(1);
        PORTCbits.RC1 = 1; //Slave Deselect 2



        //Convertimos el valor en distintos char para poder desplegarlos en la 
        //LCD
        conv_Numero_A_StringContador(slave2);
        Lcd_Set_Cursor(2, 8);
        Lcd_Write_Char(unidadVcontador);

        Lcd_Set_Cursor(2, 9);
        Lcd_Write_Char(decenaVcontador);

        Lcd_Set_Cursor(2, 10);
        Lcd_Write_Char(centenaVcontador);


        //Llamamos al tercer SLAVE 3-Termometro
        PORTCbits.RC0 = 0; //Slave Select 3-Termometro
        __delay_ms(1);

        spiWrite(1);
        slave3 = spiRead();

        __delay_ms(1);
        PORTCbits.RC0 = 1; //Slave Deselect 3



        //Convertimos el valor en distintos char para poder desplegarlos en la 
        //LCD
        conv_Numero_A_StringTemperatura(slave3);
        Lcd_Set_Cursor(2, 13);
        Lcd_Write_Char(signo);

        Lcd_Set_Cursor(2, 14);
        Lcd_Write_Char(unidadVtemperatura);

        Lcd_Set_Cursor(2, 15);
        Lcd_Write_Char(decenaVtemperatura);

        Lcd_Set_Cursor(2, 16);
        Lcd_Write_Char(centenaVtemperatura);


        //Ya que en la interrupcion recibimos el valor de la terminal virtual
        //vamos a ver que valor quiere desplegar el usuario y lo mandaremos
        //gracias a la transmision
        if (valorRX == 'a') {
            UART_send_string("Valor del ADC:");
            UART_send_char(32);
            UART_send_char(unidadV); //Copiamos los mismos valores que en la LCD
            UART_send_char(46);
            UART_send_char(decenaV);
            UART_send_char(centenaV);
            RCREG = 0; //Ponemos en 0 para que no vuelva a entrar al if
            valorRX = 0;
            UART_send_char(13);
            UART_send_char(13);

            UART_send_string("PRESIONE: ");
            UART_send_char(13);
            UART_send_string(" 'a'- Para mostrar el ADC");
            UART_send_char(13);
            UART_send_string(" 'b'- Para mostrar el contador");
            UART_send_char(13);
            UART_send_string(" 'c'- Para mostrar el Termometro");
            UART_send_char(13);



        } else if (valorRX == 'b') {

            UART_send_string("Valor del Contador:");
            UART_send_char(32);
            UART_send_char(unidadVcontador);
            UART_send_char(decenaVcontador);
            UART_send_char(centenaVcontador);
            RCREG = 0;
            valorRX = 0;

            UART_send_char(13);
            UART_send_char(13);

            UART_send_string("PRESIONE: ");
            UART_send_char(13);
            UART_send_string(" 'a'- Para mostrar el ADC");
            UART_send_char(13);
            UART_send_string(" 'b'- Para mostrar el contador");
            UART_send_char(13);
            UART_send_string(" 'c'- Para mostrar el Termometro");
            UART_send_char(13);


        } else if (valorRX == 'c') {

            UART_send_string("Valor del Termometro:");
            UART_send_char(32);
            UART_send_char(signo);
            UART_send_char(unidadVtemperatura);
            UART_send_char(decenaVtemperatura);
            UART_send_char(centenaVtemperatura);
            RCREG = 0;
            valorRX = 0;

            UART_send_char(13);
            UART_send_char(13);

            UART_send_string("PRESIONE: ");
            UART_send_char(13);
            UART_send_string(" 'a'- Para mostrar el ADC");
            UART_send_char(13);
            UART_send_string(" 'b'- Para mostrar el contador");
            UART_send_char(13);
            UART_send_string(" 'c'- Para mostrar el Termometro");
            UART_send_char(13);


        }



    }
}

void setup(void) {

    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    PORTA = 0;
    TRISB = 0b00000011;
    PORTB = 0;
    TRISC = 0b10010000;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
    INTCONbits.GIE = 1; //Habilitamos las interrupciones
    INTCONbits.PEIE = 1; //Habilitamos las interrupciones perifericas

    PORTCbits.RC2 = 1; //Desabilitamos los SS
    PORTCbits.RC1 = 1;
    PORTCbits.RC0 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    //Configuracion de la comunicacion SPI


    PIR1bits.RCIF = 0; //Apagamos la bandera del RX


}

//Funcion para convertir en char los valores del slave 1

void conv_Numero_A_String(uint8_t x) {

    valor = x * 2;
    unidadV = valor / 100;
    valor = valor - (unidadV * 100);
    decenaV = valor / 10;
    valor = valor - (decenaV * 10);
    centenaV = valor + 48;
    unidadV = unidadV + 48;
    decenaV = decenaV + 48;
}


//Funcion para convertir en char los valores del slave 2

void conv_Numero_A_StringContador(uint8_t x) {

    valor = x;
    unidadVcontador = valor / 100;
    valor = valor - (unidadVcontador * 100);
    decenaVcontador = valor / 10;
    valor = valor - (decenaVcontador * 10);
    centenaVcontador = valor + 48;
    unidadVcontador = unidadVcontador + 48;
    decenaVcontador = decenaVcontador + 48;
}


//Funcion para convertir en char los valores del slave 3

void conv_Numero_A_StringTemperatura(uint8_t x) {


    if (x < 68) {
        //68 es el "0" del termometro
        signo = 45; //Para poner un - en la LCD y la terminal
        valor = x * 0.80;
        valor = valor - 55;
        valor = valor*-1;

        unidadVtemperatura = valor / 100;
        valor = valor - (unidadVtemperatura * 100);
        decenaVtemperatura = valor / 10;
        valor = valor - (decenaVtemperatura * 10);
        centenaVtemperatura = valor + 48;
        unidadVtemperatura = unidadVtemperatura + 48;
        decenaVtemperatura = decenaVtemperatura + 48;

    } else if (x == 68) {
        signo = 32;
        unidadVtemperatura = 48;
        decenaVtemperatura = 48;
        centenaVtemperatura = 48;

    } else {
        signo = 43; //Para poner un + en la LCD y la terminal
        valor = x;
        valor = valor * 0.80;
        valor = valor - 55;
        unidadVtemperatura = valor / 100;
        valor = valor - (unidadVtemperatura * 100);
        decenaVtemperatura = valor / 10;
        valor = valor - (decenaVtemperatura * 10);
        centenaVtemperatura = valor + 48;
        unidadVtemperatura = unidadVtemperatura + 48;
        decenaVtemperatura = decenaVtemperatura + 48;


    }

}
