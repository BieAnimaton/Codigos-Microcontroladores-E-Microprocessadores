// CONFIG
#pragma config FOSC = XT     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low Voltage In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = OFF        // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)

#include <stdio.h> // inclui as configura��es para entradas e sa�das (I/O) padr�es
#include <stdlib.h> // inclui as bibliotecas padr�es
#include <xc.h> // inclui a biblioteca principal

#define _XTAL_FREQ 4000000 // ajuste da freq. de Clock (conforme o hardware/placa)
#define botao1 PORTAbits.RA2 // define bot�o como o terminal PORTA2
#define botao2 PORTAbits.RA3 // define bot�o como o terminal PORTA2
#define led PORTBbits.RB3 // led como o terminal PORTB0

void main(void)             //fun��o principal
{
    TRISAbits.TRISA2=1;        //portA2 como entrada
    TRISB=0;                     //todo o portB como sa�da
    PORTB=0xFF;                  //desliga todos os leds

    ADCON1bits.PCFG3=0;         //configura todo o portA como digital
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG1=1;
    ADCON1bits.PCFG0=1;
    ADCON0bits.ADON=0;          //desliga conversores A/D

    INTCONbits.GIE=0;           //desliga interrup��es

    while(1)                //loop infinito
   {
        if(botao1==0) //se bot�o pressionado
       {
           led=0; //acende led
           __delay_ms(300); //aguarda 300 ms
       }

        if(botao2==0) //se bot�o pressionado
       {
           led=1; //apaga led
           __delay_ms(300); //aguarda 300 ms
       }
    }

    return;
}