#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 4000000

// #define botao PORTAbits.RA2
#define botao 0

char const display[] = {
    0b10111111, //0
    0b10000110, //1
    0b11011011, //2
    0b11001111, //3
    0b11100110, //4
    0b11101101, //5
    0b11111101, //6
    0b10000111, //7
    0b11111111, //8
    0b11101111, //9
    0b00000000 //10 tudo desligado
};

void main() {
    // TRISAbits.TRISA2 = 1;

    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;

    PORTA = 0xFF;
    PORTB = 0xFF;
    PORTC = 0xFF;

    ADCON1bits.PCFG3 = 0;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;

    ADCON0bits.ADON = 0;
    INTCONbits.GIE = 0;

    int contUnidade = 0;
    int contDezena = 0;

    while(1) {
        if (botao == 0) {
            if (contUnidade >= 9) {
                contDezena++;
                contUnidade = 0;
            } else {
                contUnidade++;
            }

            if (contUnidade >= 9 && contDezena >= 9) {
                contUnidade = 0;
                contDezena = 0;
            }
        }

        PORTB = display[contUnidade];
        PORTA = display[contDezena];
        PORTC = display[contDezena];

        PORTAbits.RA4 = 0;
        PORTAbits.RA3 = 0;
        PORTAbits.RA2 = 1;

        __delay_ms(500);
    }
}