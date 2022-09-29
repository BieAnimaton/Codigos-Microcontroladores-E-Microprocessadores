//Config
#pragma config FOSC = HS //Oscillator Selection bits
#pragma config WDTE = OFF //Watchdog Timer Enable bit
#pragma config PWRTE = OFF //Power-uo Timer Enable bit
#pragma config CP = OFF //Flash Program Memory Code Protection
#pragma config BOREN = OFF //Brown-out Reset Enable bit
#pragma config LVP = OFF //Low Voltage In-Circuit Serial
#pragma config CPD = OFF //Data EE Memory Code Protection
#pragma config WRT = OFF //Flahs`Program Memory Write Enable



#include <stdio.h>
#include <stdlib.h>
#include <xc.h>



#define _XTAL_FREQ 4000000



#define botao PORTAbits.RA2



//Variaveis



char const display[] = {
    0b11000000, //0
    0b11111001, //1
    0b10100100, //2
    0b10110000, //3
    0b10011001, //4
    0b10010010, //5
    0b10000010, //6
    0b11111000, //7
    0b10000000, //8
    0b10010000, //9
    0b11111111 //10 tudo desligado
};



bit sentido;



void main()
{
    TRISAbits.TRISA2 = 1; //PortA2 como entrada
    TRISB = 0x00; //Ajusta portB como saida
    TRISC = 0X00; //Ajusta portC como saida
    PORTB = 0XFF; //Desliga todos os leds
    PORTC = 0XFF; //Desliga todos os display
    ADCON1bits.PCFG3 = 0; //Configura portA como digital //4 botoes
    ADCON1bits.PCFG2 = 1; //Permanece como analogico
    ADCON1bits.PCFG1 = 1; //Permanece como analogico
    ADCON1bits.PCFG0 = 1; //Permanece como analogico
    ADCON0bits.ADON = 0; //Desliga conversores A/D
    INTCONbits.GIE = 0; //Desliga interrupções



   int cont = 0;
    sentido = 1;



   while(1)
    {



       if(botao == 0) //testa botao pressionado
        {
            if(sentido == 1)
            { //teste de sentido



               if(cont >= 9) //se maior ou igual a 9
                {
                    cont--; //decrementa
                    sentido = 0; // inverte o sentido
                }
                else
                {
                    cont++; //incrementa
                }
            }
            else //se o sentido for inverso
            {
                if (cont <= 0) //verifica se a contagem menor ou igual a 0
                {
                    cont++; //incrementa
                    sentido = 1; //inverte o sentido
                }
                else
                {
                    cont--; //decrementa
                }
            }
        }



       PORTB = display[cont]; //atualiza PORTB com o valor
        PORTCbits.RC4 = 0; //habilita o display1
        PORTCbits.RC3 = 1; //desabilita as demais
        PORTCbits.RC2 = 1; //desabilita as demais
        __delay_ms(1000);



   }



}