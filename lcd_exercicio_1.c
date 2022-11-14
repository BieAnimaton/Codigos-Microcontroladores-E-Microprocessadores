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

void main()
{
    INTCONbits.GIE = 0; // desliga interrupções

    unsigned int cont;

    Iniciar_LCD();

    int contador = 0;
    char contador_texto[10] = "";

    while(1) {
        LimparTela_LCD();
        __delay_ms(1);

        if(contador >= 9) {
            LimparTela_LCD();
            EscreverString_LCD("Contador ");
            __delay_ms(1);
            SegundaLinha_LCD();
            EscreverString_LCD("finalizado!");
            __delay_ms(500);
        } else {
            contador++;
            sprintf(contador_texto, "%d", contador);

            EscreverString_LCD("Contador: ");
            __delay_ms(1);
            SegundaLinha_LCD();
            EscreverString_LCD(contador_texto);
            __delay_ms(500);
        }
    }
}
