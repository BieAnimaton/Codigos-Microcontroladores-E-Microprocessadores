#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

//CONFIG
#pragma config FOSC=XT //Oscillator Selection bits
#pragma config WDTE=OFF //Watchdog Timer Enable bit
#pragma config PWRTE=ON //Power-uo Timer Enable bit
#pragma config CP=OFF //Flash Program Memory Code Protection
#pragma config BOREN=ON //Brown-out Reset Enable bit
#pragma config LVP=OFF //Low Voltage In-Circuit Serial
#pragma config CPD=OFF //Data EE Memory Code Protection
#pragma config WRT=ALL //Flahs`Program Memory Write Enable

#define _XTAL_FREQ 4000000 //Frequencia de 4MHz

//Definições de teclado
#define col_1 PORTCbits.RC0
#define col_2 PORTCbits.RC1
#define col_3 PORTCbits.RC2
#define linha_A PORTCbits.RC3
#define linha_B PORTCbits.RC4
#define linha_C PORTCbits.RC5
#define linha_D PORTCbits.RC6

//Constante para ajuste dos leds do display de 7 segmentos
//Pinagem invertida gfedcba
char const display[] = {
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
    0b00000000, //10 tudo desligado
};

void blank() //Função para gerar blank nos display
{
    PORTB = 0;
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 0;
}

char tecla(void) //cria função para ler o valor da tecla
{
    char tecla=55;

    col_1=1;
    col_2=0;
    col_3=0;
    if (linha_A) tecla = 1;
    else if (linha_B) tecla = 4;
    else if (linha_C) tecla = 7;
    else if (linha_D) tecla = 22; //limpa

    col_1=0;
    col_2=1;
    col_3=0;
    if (linha_A) tecla = 2;
    else if (linha_B) tecla = 5;
    else if (linha_C) tecla = 8;
    else if (linha_D) tecla = 0;

    col_1=0;
    col_2=0;
    col_3=1;
    if (linha_A) tecla = 3;
    else if (linha_B) tecla = 6;
    else if (linha_C) tecla = 9;
    else if (linha_D) tecla = 33;

    col_1=0;
    col_2=0;
    col_3=0;

    return tecla;
}

void display1_on() //função para ligar somente o display 1
{
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 0;
}

void display2_on() //função para ligar somente o display 2
{
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 0;
}

void display3_on() //Função para ligar somente o display 3
{
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 1;
}

void main()
{
    //Ajusta PortC RC0, 1, 2 e 7 como saídas e o 
    //restante como entrada.
    TRISC = 0B01111000;
    //Ajusta portB como saída
    TRISB = 0;
    //Ajusta portA como saídas
    TRISA = 0;
    //Desliga todos os segmentos do display
    PORTB=0xFF;
    //Configura portA como I/O digital
    ADCON1bits.PCFG3=0;
    ADCON1bits.PCFG2=1;
    ADCON1bits.PCFG1=1;
    //Desliga conversores A/D
    ADCON1bits.PCFG0=0;
    INTCONbits.GIE=0; //Desliga as interrupções

    //Variaveis globais
    char n_display=1, valor_temp=0, valor_display1=0,
            valor_display2=0, valor_display3=0;

    while(1)
    {
        //Chama a função blank
        blank();
        //Gasta 1 ciclo
        _delay(1);
         //carrega segmentos do display 1 com seu valor
        PORTB=valor_display1;
        //liga display1
        display1_on();
        //Aguarda 3 ms
        __delay_ms(3);

        blank();
        _delay(1);
        PORTB=valor_display2;
        display2_on();
        __delay_ms(3);

        blank();
        _delay(1);
        PORTB=valor_display3;
        display3_on();
        __delay_ms(3);

        //Chama função e Le qual tecla foi pressiona
        valor_temp =  tecla();

        switch (valor_temp)
        {
            //Se nenhuma tecla for pressionada, não faz nada
            case 55:
                break;
            //Se foi a tecla para mudar de caracter
            case 33:
                n_display++; //incrementa o caracter
            //Se for maior que 3, volte ao primeiro
                if (n_display > 3) n_display = 1;
                __delay_ms(300);
                break;
            //Se for a tecla para limpar
            case 22:
                valor_display1 = 0,
                valor_display2 = 0,
                valor_display3 = 0;
                break;
            default: //Padrao para atualizar caracter
            {
                case 1:
                    valor_display1 = display[valor_temp];
                    break;
                case 2:
                    valor_display2 = display[valor_temp];
                    break;
                case 3:
                    valor_display3 = display[valor_temp];
                    break;
            }
        }
    }
}