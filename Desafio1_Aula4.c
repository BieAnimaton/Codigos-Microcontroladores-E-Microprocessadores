#include <stdlib.h>

#include <stdio.h>

#include <xc.h>

//CONFIG
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = ALL

#define _XTAL_FREQ 4000000

#define led1 PORTBbits.RB0 // led como o terminal PORTB0
#define led2 PORTBbits.RB1 // led como o terminal PORTB0
#define led3 PORTBbits.RB2 // led como o terminal PORTB0
#define led4 PORTBbits.RB3 // led como o terminal PORTB0
#define led5 PORTBbits.RB4 // led como o terminal PORTB0
#define led6 PORTBbits.RB5 // led como o terminal PORTB0
#define led7 PORTBbits.RB6 // led como o terminal PORTB0
#define led8 PORTBbits.RB7 // led como o terminal PORTB0

void AcenderLed(int contador) {
    switch (contador) {

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
    __delay_ms(300);
}

void main() // cria função principal
{
    TRISAbits.TRISA2 = 1; //portA2 como entrada
    TRISB = 0; //todo o portB como saída
    PORTB = 0xFF; //desliga todos os leds

    AcenderLed(1);

    ADCON1bits.PCFG3 = 0; //configura todo o portA como digital
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;
    ADCON0bits.ADON = 0; //desliga conversores A/D

    INTCONbits.GIE = 0; //desliga interrupções

    int cont = 0; //cria variável de contador iniciada em 0
    int sentido = 1; // inicializa sentido
    int botao = 0;
    while (1) {
        if (botao == 0) // testa botão pressionado/lógica invertida
        {
            if (sentido == 1) // testa o sentido da contagem
            {
                if (cont >= 8) // se maior ou igual a 9
                {
                    cont--; // decrementa
                    sentido = 0; // inverte o sentido
                    AcenderLed(cont+1);
                } else // se menor que 9
                {
                    AcenderLed(cont+1);
                    cont++; // incrementa
                }
            } else // se o sentido for inverso
            {
                if (cont <= 0) // verifica se a contagem está menor ou igual a 0
                {
                    cont++; // incrementa
                    sentido = 1; // inverte o sentido
                    AcenderLed(cont+1);
                } else // se maior que 0
                {
                    cont--; // decrementa
                    AcenderLed(cont+1);
                }
            }

        } else // se não pressionou o botão
        {
            // não faz nada
        }
    }
}