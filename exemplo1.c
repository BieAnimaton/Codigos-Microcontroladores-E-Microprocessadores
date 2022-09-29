#include <stdio.h> // incluir biblioteca para entrada e saída
#include <stdlib.h> // incluir bibiliotecas padrões
#include <xc.h> // incluir biblioteca principal para o PIC

#define _XTAL_FREQ 4000000 // definir a frequência do clock 4GHz
#define botao PORTAbits.RA2 // definir botao no terminal PortA 2
#define led PORTBbits.RB0 // definir led no terminal PortB 0

void main (void) {
    TRISAbits.TRISA2 = 1; // colocar PortA como entrada
    TRISB = 0; // colocar PortB como saída
    PORTB = 0xff; // desliga todos os LEDs

    ADCON1bits.PCFG3 = 0; // configurar PortaA como digital
    ADCON1bits.PCFG2 = 1; //
    ADCON1bits.PCFG1 = 1; //
    ADCON1bits.PCFG0 = 1; //
    ADCON0bits.ADON = 0; //

    INTCONbits.GIE = 0;

    while (1) {
        if (botao == 1) { // se botao liberado
            led = 1; // apagar led
            __delay_ms(300); // aguarda 300ms
        } else {
            led = 0; // acender led
            __delay_ms(300); // aguarda 300ms
        }
        return;
    }
}