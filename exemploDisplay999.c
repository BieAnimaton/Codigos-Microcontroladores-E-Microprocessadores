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

//Inicializa os 8 primerios endereços da EEPROM com 0
//isso acontece apenas na gravação
__EEPROM_DATA(0, 0, 0, 0, 0, 0, 0, 0);

#define botao2 PORTAbits.RA2
#define botao1 PORTAbits.RA3

char
const display[] = {
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
};

void main() //Função principal
{
    TRISAbits.TRISA2 = 1; //portA2 como entrada, botão2
    TRISAbits.TRISA3 = 1; //portA3 como entrada, botão1
    TRISB = 0x00; //Ajusta portB como saídas
    TRISC = 0x00; //Ajusta portC como saídas
    PORTB = 0xFF; //Desliga todos os leds
    PORTC = 0xFF; //Desliga todos os displays
    ADCON1bits.PCFG3 = 0; //Configura portA digital
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;
    ADCON0bits.ADON = 0; //Desligando Conversores A/D
    INTCONbits.GIE = 0; //Desliga interrupções

    //Cria a variável filtro1 para o botão 1
    int filtro1 = 250;
    //Cria a variável filtro2 para o botão 2
    int filtro2 = 250;
    //Cria variáves para unidade, dezena e centena
    int unidade, dezena, centena;
    //Cria variável inteira (16 bits) para realizar
    //a contagem de 0 a 999
    int valor;
    //Cria variável da parte baixa (8 bits) dos
    //16 bits do valor da contagem
    char valor_baixo;
    //Cria variável da arte alta (8 bits) dos
    //16 bits do valor da contagem
    // *** isso é necessário porque a EEPROM armazena
    //apenas 8 bits por endereço ***
    char valor_alto;
    //Armazena a parte baixa do valor com  valor inserido
    //no endereço 1 da EEPROM
    valor_baixo = EEPROM_READ(1);
    //Armazena a parte alta do valor com  valor inserido
    //no endereço 2 da EEPROM
    valor_alto = EEPROM_READ(2);
    //Monta o valor com a parte baixa e alta(x 256)
    valor = valor_baixo + valor_alto * 256;

    while (1) //Cria loop infinito
    {
        teste1: if (botao1 == 0) {
            filtro1--; //decrementa filtro
            if (filtro1 == 0) //testa se filtro terminou
            {
                //terminou, aguarda o botao ser liberado
                do {} while (botao1 == 0);
                valor++; //Incrementa variável valor
                //Se valor for maior que 999, zera
                if (valor > 999) valor = 0;
                //armazena a parte baixa, resto da
                //divisao do valor por  256
                valor_baixo = valor % 256;
                //armazena a parte alta, valor inteiro
                //da divisao por 256
                valor_alto = valor / 256;
                //Armazena a parte baixa no endereço 1
                EEPROM_WRITE(1, valor_baixo);
                //Armazena a parte alta no endereço 2
                EEPROM_WRITE(2, valor_alto);
                filtro1 = 250;
            } else {
                //testa novamente o botão 1
                goto teste1;
            }
        }
        teste2: if (botao2 == 0) {
            filtro2--;
            if (filtro2 == 0) {
                do {} while (botao2 == 0);
                valor--;
                if (valor < 0) valor = 999;
                valor_baixo = valor % 256;
                valor_alto = valor / 256;
                EEPROM_WRITE(1, valor_baixo);
                EEPROM_WRITE(2, valor_alto);
                filtro2 = 250;
            } else {
                goto teste2;
            }

        }
        //Retira a centena do valor
        centena = valor / 100;
        //Retira a dezena do valor
        dezena = (valor - (centena * 100)) / 10;
        //Retira a unidade do valor
        unidade = (valor - ((centena * 100) + (dezena * 10)));

        //Atualiza portB para o display com a centena
        PORTB = display[centena];

        PORTCbits.RC4 = 0; //habilita  display3
        PORTCbits.RC3 = 1; //desabilita os demais
        PORTCbits.RC2 = 1;
        __delay_ms(3);

        PORTB = display[dezena];

        PORTCbits.RC4 = 1;
        PORTCbits.RC3 = 0;
        PORTCbits.RC2 = 1;
        __delay_ms(3);

        PORTB = display[unidade];

        PORTCbits.RC4 = 1;
        PORTCbits.RC3 = 1;
        PORTCbits.RC2 = 0;
        __delay_ms(3);
    }
}
