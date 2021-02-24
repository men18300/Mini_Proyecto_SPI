#include "USART.h"

void UART_config() {


    //Para la TRANSMISION
    TXSTAbits.TXEN = 1; //Habilitamos la transmision - La bandera TXIF se pone 1 auto.
    TXSTAbits.SYNC = 0; //Configura EUSART para operacion asincrona
    RCSTAbits.SPEN = 1; //Habilita el EUSART Y PONE TX/CK I/O pin como salida
    TRISCbits.TRISC6 = 0; //Lo ponemos como salida para asegurar
    TXSTAbits.TX9 = 0; // No usaremos los 9 bits solo 8

    //Para la RECEPCION

    RCSTAbits.CREN = 1; // Habilitamos la recepcion
    PIE1bits.RCIE=1;
    RCSTAbits.RX9 = 0; // No usaremos los 9 bits, solo 8
    TRISCbits.TRISC7 = 1; //Lo ponemos como entrada para asegurar

    //BAUD RATE
    SPBRG = ((_XTAL_FREQ / 16) / Baud_rate) - 1;
    TXSTAbits.BRGH = 1;


}

void UART_send_char(char bt) {
    while (!TXIF); // hold the program till TX buffer is free
    TXREG = bt; //Load the transmitter buffer with the received value
}

void UART_send_string(char* st_pt) {
    while (*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}

char UART_get_char() {
    if (RCSTAbits.OERR==1) // check for Error 
    {
        RCSTAbits.CREN = 0; //If error -> Reset 
        RCSTAbits.CREN = 1; //If error -> Reset 
    }

    while (!PIR1bits.RCIF); // hold the program till RX buffer is free
    return RCREG; //receive the value and send it to main function

}