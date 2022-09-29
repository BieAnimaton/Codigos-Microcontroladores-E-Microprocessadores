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

#define botao1 PORTAbits.RA2
#define botao2 PORTAbits.RA3

char const display[] = {
    0b11000000, //0
    0b11111001, //1
    0b10100100, //2
    0b10110000, //3
    0b10011001, //4
    0b10010010, //5
    0b10000010, //6
    0b11111000, //7
    0b10000000, //8
    0b10010000, //9
};

void main() {
    // TRISAbits.TRISA2 = 1;

    TRISAbits.TRISA2 = 1; //portA2 como entrada, botão2
    TRISAbits.TRISA3 = 1; //portA3 como entrada, botão1

    TRISB = 0x00; //Ajusta portB como saídas
    TRISC = 0x00; //Ajusta portC como saídas
    PORTB = 0xFF; //Desliga todos os leds
    PORTC = 0xFF; //Desliga todos os displays
    
    ADCON1bits.PCFG3 = 0; //Configura portA digital
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;

    ADCON0bits.ADON = 0; //Desligando Conversores A/D
    INTCONbits.GIE = 0; //Desliga interrupções



    int contUnidade = 0;
    int contDezena = 0;
    int contCentena = 0;

    while(1) {
        if (botao1 == 0) {
            if (contDezena >= 9) {
                contCentena++;
                contDezena = 0;
            } else {
                contDezena++;
            }

            if (contUnidade >= 9) {
                contDezena++;
                contUnidade = 0;
            } else {
                contUnidade++;
            }

            if(contCentena == 999) {
                contCentena = 999;
            }

            __delay_ms(100);
        }

        if (botao2 == 0) {
            if (contDezena >= 9) {
                contCentena--;
                contDezena = 0;
            } else {
                contDezena--;
            }

            if (contUnidade >= 9) {
                contDezena--;
                contUnidade = 0;
            } else {
                contUnidade--;
            }

            if(contCentena == 0) {
                contCentena = 0;
            }

            __delay_ms(100);
        }

        PORTB = display[contCentena];

        PORTCbits.RC4 = 0; //habilita  display3
        PORTCbits.RC3 = 1; //desabilita os demais
        PORTCbits.RC2 = 1;
        __delay_ms(3);

        PORTB = display[contDezena];

       PORTCbits.RC4 = 1;
        PORTCbits.RC3 = 0;
        PORTCbits.RC2 = 1;
        __delay_ms(3);

       PORTB = display[contUnidade];

       PORTCbits.RC4 = 1;
        PORTCbits.RC3 = 1;
        PORTCbits.RC2 = 0;
        __delay_ms(3);

    }
}