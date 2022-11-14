

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ALL        // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)


#define _XTAL_FREQ 4000000

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <xc.h>
#include "lcd.h"

void main() // função principal
{

    TRISAbits.TRISA0 = 1; // Ajustar como entrada
    INTCONbits.GIE = 0;   // Desliga interrupções

    unsigned int adc = 0; // cria variavel adc
    char buffer[50];      // cria um array de variaveis de char
    
    Iniciar_LCD(); // inicia o LCD
    LimparTela_LCD();
    __delay_ms(1); // aguardar 1 ms
    EscreverString_LCD("Ruânico"); // escreva seu nome
    __delay_ms(2000); // aguarde 2 s
    
    LimparTela_LCD();
    __delay_ms(1);
    
    ADCON1bits.PCFG0 = 0; // ajusta Ra0 como analogica e as demais como digital
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;

    ADCON0bits.CHS0 = 0; // ajusta para conversao
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;

    ADCON0bits.ADCS0 = 1; // ajusta de com a frequencia
    ADCON0bits.ADCS1 = 0;

    ADCON1bits.ADFM = 1; // alinhamento dos bits a direita

    while(1)
    {
        LimparTela_LCD();
        __delay_ms(1);

        ADCON0bits.ADON = 1; // liga o conversor analogico digital
        __delay_ms(1);
        ADCON0bits.GO = 1; // inicia a conversao

        while(ADCON0bits.GO == 1); // aguarda ate o final da conversao
        ADCON0bits.ADON = 0; // desliga o conversor
        __delay_ms(1);
        adc = ADRESH; // armazena os valores na variavel
        adc = adc << 8;
        adc = adc + ADRESL;
        sprintf(buffer, "ADC=%04d", adc); // converte os valores em caracter
        EscreverString_LCD(buffer); // apresenta no display
        __delay_ms(100);

    }
}














