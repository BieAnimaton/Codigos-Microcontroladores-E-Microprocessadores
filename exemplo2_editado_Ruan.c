#include <stdio.h> // incluir biblioteca para entrada e saída
#include <stdlib.h> // incluir bibiliotecas padrões
#include <xc.h> // incluir biblioteca principal para o PIC


//CONFIG
#pragma config FOSC=XT //Oscillator Selection bits
#pragma config WDTE=OFF //Watchdog Timer Enable bit
#pragma config PWRTE=ON //Power-uo Timer Enable bit
#pragma config CP=OFF //Flash Program Memory Code Protection
#pragma config BOREN=ON //Brown-out Reset Enable bit
#pragma config LVP=OFF //Low Voltage In-Circuit Serial
#pragma config CPD=OFF //Data EE Memory Code Protection
#pragma config WRT=ALL //Flahs`Program Memory Write Enable

#define _XTAL_FREQ 4000000 // definir a frequência do clock 4GHz
#define botao PORTAbits.RA2 // definir botao no terminal PortA 2

#define A PORTBbits.RB0
#define B PORTBbits.RB1
#define C PORTBbits.RB2
#define D PORTBbits.RB3
#define E PORTBbits.RB4
#define F PORTBbits.RB5
#define G PORTBbits.RB6

char const display[] = {
    //A B C D E F G
    //0 0 0 0 0 0 0
    
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
    
    int i = 0;
    
        while(1)
        {
        
            PORTB = display[i]; //9
            __delay_ms(150);
            
            i++;
            if(i > 9)
                i = 0;
            
        }
        
         
}