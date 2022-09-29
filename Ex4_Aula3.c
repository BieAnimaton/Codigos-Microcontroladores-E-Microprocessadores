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
#define botao1 PORTAbits.RA2 // define botão como o terminal PORTA2
#define botao2 PORTAbits.RA3 // define botão como o terminal PORTA2
#define led PORTBbits.RB3 // led como o terminal PORTB0

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

    while(1)                //loop infinito
   {
        if(botao1==0) //se botão pressionado
       {
           led=0; //acende led
           __delay_ms(300); //aguarda 300 ms
       }

        if(botao2==0) //se botão pressionado
       {
           led=1; //apaga led
           __delay_ms(300); //aguarda 300 ms
       }
    }

    return;
}