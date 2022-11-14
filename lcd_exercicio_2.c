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

#define botaoRA2 PORTAbits.RA2 // define botão como o terminal PORTA2
#define botaoRA3 PORTAbits.RA3 // define botão como o terminal PORTA2
#define botaoRA4 PORTAbits.RA4 // define botão como o terminal PORTA2

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

        if(botaoRA2 == 0) {
            LimparTela_LCD();
            sprintf(contador_texto, "%d", contador);
            EscreverString_LCD("Motor horário");
            __delay_ms(1);
            SegundaLinha_LCD();
            EscreverString_LCD("Crescente: ");
            EscreverString_LCD(contador_texto);
            __delay_ms(500);
            contador = (contador + 1) % 10;
        } else {
            LimparTela_LCD();
            __delay_ms(500);
        }

        if(botaoRA3 == 0) {
            LimparTela_LCD();
            if (contador <= 0)
                contador = 9;
            sprintf(contador_texto, "%d", contador);
            EscreverString_LCD("Motor anti-horário");
            __delay_ms(1);
            SegundaLinha_LCD();
            EscreverString_LCD("Descrescente: ");
            EscreverString_LCD(contador_texto);
            __delay_ms(500);
            contador = contador--;
        } else {
            LimparTela_LCD();
            __delay_ms(500);
        }

        if(botaoRA4 == 0) {
            LimparTela_LCD();
            contador = 0;
            sprintf(contador_texto, "%d", contador);
            EscreverString_LCD("Motor desligado");
            __delay_ms(1);
            SegundaLinha_LCD();
            EscreverString_LCD("Pausado: ");
            EscreverString_LCD(contador_texto);
            __delay_ms(500);
        } else {
            LimparTela_LCD();
            __delay_ms(500);
        }
    }
}
