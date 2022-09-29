// CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF // FLASH Program Memory Code Protection bits
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF // Low Voltage In-Circuit Serial Programming Enable
#pragma config CPD = OFF // Data EEPROM Protection (Code Protection off)
#pragma config WRT = OFF // FLASH Program Memory Write Enable
#include <stdio.h> // adiciona a biblioteca padrão para I/Os

#include <stdlib.h> // adiciona a biblioteca padrão

#include <xc.h> // adiciona biblioteca de linguagem C

#define _XTAL_FREQ 4000000 // ajusta clock interno para 4MHz

#define botao1 PORTAbits.RA2 // define botao em PORTA2
#define botao2 PORTAbits.RA3 // define botao em PORTA2

// Variáveis
// xgfedcba
char
const display[] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
    0b11111111, // 10, tudo desligado
};

void main() { // rotina principal
    TRISAbits.TRISA2 = 1; //portA2 como entrada
    TRISB = 0x00; //ajusta portB como saídas
    TRISC = 0x00; //ajusta portC como saídas
    PORTB = 0xFF; //desliga todos os leds
    PORTC = 0xFF; //desliga todos os displays
    ADCON1bits.PCFG3 = 0; //configura portA digital
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;
    ADCON0bits.ADON = 0; //desliga conversores A/D
    INTCONbits.GIE = 0; //desliga interrupções

    int temp; //cria variável de temporizador iniciada em 0
    int filtro = 250; // cria a variável filtro para o botao

    while (1) { // loop infinito
        filtro = 250; //inicia filtro do botão
        teste: //cria marcador para teste de botao
            if (botao1 == 0) { // testa botão pressionado
                filtro--; // decrementa filtro
                if (filtro == 0) { // testa se filtro terminou
                    //do {} while (botao1 == 0); // terminou, aguarda o botão ser liberado
                    for (temp = 999; temp >= 0; temp--) { // cria loop para decrementar a contagem
                        PORTB = display[temp]; // atualiza display com o valor de temp
                        PORTCbits.RC4 = 0; // habilita display1
                        PORTCbits.RC3 = 1; // desabilita os demais
                        PORTCbits.RC2 = 1;
                        __delay_ms(1000); // aguarda 1s
                    }
                } else { // se não terminou
                    goto teste; // testa novamente o botao (marcador)
                }
            }

            if (botao2 == 0) { // testa botão pressionado -> pausar
                filtro = filtro;
                temp = temp;
            } else { // testa botão solto -> reiniciar
                filtro = 250;
                temp = 0;
            }
    }
}