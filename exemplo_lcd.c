// CONFIG
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = ALL

#include <stdlib.h>

#include <stdio.h>

#include <stddef.h>

#include <xc.h>

#include "lcd.h"

#define _XTAL_FREQ 4000000

void main() {
    INTCONbits.GIE = 0; // desliga interrupções

    unsigned int cont;

    Iniciar_LCD();

    while (1) {
        LimparTela_LCD();
        __delay_ms(1);

        EscreverString_LCD("EEP-Escola-de-");
        __delay_ms(1);
        SegundaLinha_LCD();
        EscreverString_LCD("Eng. Piracicaba");
        __delay_ms(5000);

        LimparTela_LCD();
        __delay_ms(1);

        EscreverString_LCD("Eng. Comp.");
        __delay_ms(1);
        SegundaLinha_LCD();
        EscreverString_LCD("Ciencia Comp.");
        __delay_ms(5000);
    }

}