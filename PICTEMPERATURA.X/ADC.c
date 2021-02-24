
#include "ADC.h"

void ADC(uint8_t ANA, uint8_t justificado) {


    ADCON0bits.ADON = 1; //ADC esta habilitado
    ADCON0bits.ADCS = 0b10; // Clock Fosc/32

    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    ADCON1bits.VCFG1 = 1; //Voltaje de referencia a VSS
    ADCON1bits.VCFG0 = 1; //Voltaje de referencia a VDD

    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;

    if (justificado == 0) {
        ADCON1bits.ADFM = 0;
        switch (ANA) {
            case 0:
                TRISAbits.TRISA0 = 1;
                ANSELbits.ANS0 = 1;
                ADCON0bits.CHS = 0b0000; //Seleccionamos canal AN0
                break;
            case 1:
                TRISAbits.TRISA1 = 1;
                ANSELbits.ANS1 = 1;
                ADCON0bits.CHS = 0b0001; //Seleccionamos canal AN1
                break;
            case 2:
                TRISAbits.TRISA2 = 1;
                ANSELbits.ANS2 = 1;
                ADCON0bits.CHS = 0b0010; //Seleccionamos canal AN2
                break;
            case 3:
                TRISAbits.TRISA3 = 1;
                ANSELbits.ANS3 = 1;
                ADCON0bits.CHS = 0b0011; //Seleccionamos canal AN3
                break;
            case 4:
                TRISAbits.TRISA5 = 1;
                ANSELbits.ANS4 = 1;
                ADCON0bits.CHS = 0b0100; //Seleccionamos canal AN4
                break;
            case 5:
                TRISEbits.TRISE0 = 1;
                ANSELbits.ANS5 = 1;
                ADCON0bits.CHS = 0b0101; //Seleccionamos canal AN5
                break;
            case 6:
                TRISEbits.TRISE1 = 1;
                ANSELbits.ANS6 = 1;
                ADCON0bits.CHS = 0b0110; //Seleccionamos canal AN6
            case 7:
                TRISEbits.TRISE2 = 1;
                ANSELbits.ANS7 = 1;
                ADCON0bits.CHS = 0b0111; //Seleccionamos canal AN7
                break;
            case 8:
                TRISBbits.TRISB2 = 1;
                ANSELHbits.ANS8 = 1;
                ADCON0bits.CHS = 0b1000; //Seleccionamos canal AN8
                break;
            case 9:
                TRISBbits.TRISB3 = 1;
                ANSELHbits.ANS9 = 1;
                ADCON0bits.CHS = 0b1001; //Seleccionamos canal AN9
                break;
            case 10:
                TRISBbits.TRISB1 = 1;
                ANSELHbits.ANS10 = 1;
                ADCON0bits.CHS = 0b1010; //Seleccionamos canal AN10
                break;
            case 11:
                TRISBbits.TRISB4 = 1;
                ANSELHbits.ANS11 = 1;
                ADCON0bits.CHS = 0b1011; //Seleccionamos canal AN11
                break;
            case 12:
                TRISBbits.TRISB0 = 1;
                ANSELHbits.ANS12 = 1;
                ADCON0bits.CHS = 0b1100; //Seleccionamos canal AN12
                break;
            case 13:
                TRISBbits.TRISB5 = 1;
                ANSELHbits.ANS13 = 1;
                ADCON0bits.CHS = 0b1101; //Seleccionamos canal AN13
                break;


        }
    } else if (justificado == 1) {
        ADCON1bits.ADFM = 1;
        switch (ANA) {
                switch (ANA) {
                    case 0:
                        TRISAbits.TRISA0 = 1;
                        ANSELbits.ANS0 = 1;
                        ADCON0bits.CHS = 0b0000; //Seleccionamos canal AN0
                        break;
                    case 1:
                        TRISAbits.TRISA1 = 1;
                        ANSELbits.ANS1 = 1;
                        ADCON0bits.CHS = 0b0001; //Seleccionamos canal AN1
                        break;
                    case 2:
                        TRISAbits.TRISA2 = 1;
                        ANSELbits.ANS2 = 1;
                        ADCON0bits.CHS = 0b0010; //Seleccionamos canal AN2
                        break;
                    case 3:
                        TRISAbits.TRISA3 = 1;
                        ANSELbits.ANS3 = 1;
                        ADCON0bits.CHS = 0b0011; //Seleccionamos canal AN3
                        break;
                    case 4:
                        TRISAbits.TRISA5 = 1;
                        ANSELbits.ANS4 = 1;
                        ADCON0bits.CHS = 0b0100; //Seleccionamos canal AN4
                        break;
                    case 5:
                        TRISEbits.TRISE0 = 1;
                        ANSELbits.ANS5 = 1;
                        ADCON0bits.CHS = 0b0101; //Seleccionamos canal AN5
                        break;
                    case 6:
                        TRISEbits.TRISE1 = 1;
                        ANSELbits.ANS6 = 1;
                        ADCON0bits.CHS = 0b0110; //Seleccionamos canal AN6
                    case 7:
                        TRISEbits.TRISE2 = 1;
                        ANSELbits.ANS7 = 1;
                        ADCON0bits.CHS = 0b0111; //Seleccionamos canal AN7
                        break;
                    case 8:
                        TRISBbits.TRISB2 = 1;
                        ANSELHbits.ANS8 = 1;
                        ADCON0bits.CHS = 0b1000; //Seleccionamos canal AN8
                        break;
                    case 9:
                        TRISBbits.TRISB3 = 1;
                        ANSELHbits.ANS9 = 1;
                        ADCON0bits.CHS = 0b1001; //Seleccionamos canal AN9
                        break;
                    case 10:
                        TRISBbits.TRISB1 = 1;
                        ANSELHbits.ANS10 = 1;
                        ADCON0bits.CHS = 0b1010; //Seleccionamos canal AN10
                        break;
                    case 11:
                        TRISBbits.TRISB4 = 1;
                        ANSELHbits.ANS11 = 1;
                        ADCON0bits.CHS = 0b1011; //Seleccionamos canal AN11
                        break;
                    case 12:
                        TRISBbits.TRISB0 = 1;
                        ANSELHbits.ANS12 = 1;
                        ADCON0bits.CHS = 0b1100; //Seleccionamos canal AN12
                        break;
                    case 13:
                        TRISBbits.TRISB5 = 1;
                        ANSELHbits.ANS13 = 1;
                        ADCON0bits.CHS = 0b1101; //Seleccionamos canal AN13
                        break;
                }
        }
    }

}

