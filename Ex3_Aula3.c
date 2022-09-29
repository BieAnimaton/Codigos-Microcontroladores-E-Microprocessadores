// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = OFF        // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#include <stdio.h> // inclui as configurações para entradas e saídas (I/O) padrões
#include <stdlib.h> // inclui as bibliotecas padrões
#include <xc.h> // inclui a biblioteca principal

#define _XTAL_FREQ 4000000 // ajuste da freq. de Clock (conforme o hardware/placa)
#define botao PORTAbits.RA2 // define botão como o terminal PORTA2
#define led1 PORTBbits.RB0 // led como o terminal PORTB0
#define led2 PORTBbits.RB1 // led como o terminal PORTB0
#define led3 PORTBbits.RB2 // led como o terminal PORTB0
#define led4 PORTBbits.RB3 // led como o terminal PORTB0
#define led5 PORTBbits.RB4 // led como o terminal PORTB0
#define led6 PORTBbits.RB5 // led como o terminal PORTB0
#define led7 PORTBbits.RB6 // led como o terminal PORTB0
#define led8 PORTBbits.RB7 // led como o terminal PORTB0


void main(void)             //função principal
{
    TRISAbits.TRISA2=1;        //portA2 como entrada
    TRISB=0;                     //todo o portB como saída
    PORTB=0xFF;                  //desliga todos os leds

    ADCON1bits.PCFG3=0;         //configura todo o portA como digital
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG1=1;
    ADCON1bits.PCFG0=1;
    ADCON0bits.ADON=0;          //desliga conversores A/D

    INTCONbits.GIE=0;           //desliga interrupções

    int contador = 0;

    while(1)                //loop infinito
   {
        if(botao == 0) //se botão liberado
            contador = (contador % 8) + 1;

        switch(contador)
        {

            case 1:
                led1 = 0;
                led2 = 1;
                led3 = 1;
                led4 = 1;
                led5 = 1;
                led6 = 1;
                led7 = 1;
                led8 = 1;
            break;

            case 2:
                led1 = 1;
                led2 = 0;
                led3 = 1;
                led4 = 1;
                led5 = 1;
                led6 = 1;
                led7 = 1;
                led8 = 1;
            break;
            case 3:
                led1 = 1;
                led2 = 1;
                led3 = 0;
                led4 = 1;
                led5 = 1;
                led6 = 1;
                led7 = 1;
                led8 = 1;
            break;

            case 4:
                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 0;
                led5 = 1;
                led6 = 1;
                led7 = 1;
                led8 = 1;
            break;
            case 5:
                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 1;
                led5 = 0;
                led6 = 1;
                led7 = 1;
                led8 = 1;
            break;
            case 6:
                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 1;
                led5 = 1;
                led6 = 0;
                led7 = 1;
                led8 = 1;
            break;
            case 7:
                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 1;
                led5 = 1;
                led6 = 1;
                led7 = 0;
                led8 = 1;
            break;
            case 8:
                led1 = 1;
                led2 = 1;
                led3 = 1;
                led4 = 1;
                led5 = 1;
                led6 = 1;
                led7 = 1;
                led8 = 0;
            break;
        }
        __delay_ms(100);
    }

    return;
}