#include <stddef.h>
#include <xc.h>
#include "lcd.h"
#define _XTAL_FREQ 4000000

void Iniciar_LCD(void)
{
    /* Ajusta pinos como saída */
    ENABLE_DIRECTION = 0;
    RS_DIRECTION = 0;
    LCD_BUS_DIRECTION = 0;

    /* Limpa pinos */
    ENABLE_LCD = 0;
    RS_LCD = 0;
    LCD_BUS = 0;



    __delay_ms(10); /* Aguarda 10 segundos */



    /* Escreve comandos para inicialização do LCD */
    EscreverCmd_LCD(0x38);
    /* Display ON; Cursor; Blink ON */
    EscreverCmd_LCD(0x0F);
    /* Rotação do display OFF */
    EscreverCmd_LCD(0x06);
    /* Limpa Display */
    EscreverCmd_LCD(0x01);
}



void ComutarEnable_LCD(void)
{
    /* Comuta Enable para alterar/enviar comando/dado */
    ENABLE_LCD = 1;
    __delay_us(200);
    ENABLE_LCD = 0;
    __delay_us(200);
}



void EscreverCmd_LCD(unsigned char Cmd)
{
    /* Para comandos RS deve ser (0) */
    RS_LCD = 0;
    /* Mascara para variaveis de 16 bits */
    LCD_BUS &= 0xFF00;
    /* Coloca o comando na saída */
    LCD_BUS |= Cmd;



    ComutarEnable_LCD();
}



void EscreverDado_LCD(unsigned char Data)
{
    /* Para enviar um dado RS deve ser (1) */
    RS_LCD = 1;
    /* Mascara para variaveis de 16 bits */
    LCD_BUS &= 0xFF00;
    /* Coloca o dado na saída */
    LCD_BUS |= Data;



    ComutarEnable_LCD();
}



void EscreverString_LCD(const char* String)
{
    while (*String != NULL)
    {
        /* Apresnta dados até o final da string */
        EscreverDado_LCD(*String++);
    }
}



void LimparTela_LCD(void)
{
    EscreverCmd_LCD(0b00000001);
    __delay_ms(3);
}



void CursorHome_LCD(void)
{
    EscreverCmd_LCD(0b00000010);
    __delay_ms(3);
}



void DisplayOn_LCD(void)
{
    EscreverCmd_LCD(0b00001111);
    __delay_ms(3);
}

void DisplayOff_LCD(void)
{
    EscreverCmd_LCD(0b00001000);
    __delay_ms(3);
}

void CursorOn_LCD(void)
{
    EscreverCmd_LCD(0b00001111);
    __delay_ms(3);
}

void CursorOff_LCD(void)
{
    EscreverCmd_LCD(0b00001100);
    __delay_ms(3);
}

void BlinkOn_LCD(void)
{
    EscreverCmd_LCD(0b00001111);
    __delay_ms(3);
}

void BlinkOff_LCD(void)
{
    EscreverCmd_LCD(0b00001110);
    __delay_ms(3);
}

void CursorDireita_LCD(void)
{
    EscreverCmd_LCD(0b00010100);
    __delay_ms(3);
}

void CursorEsquerda_LCD(void)
{
    EscreverCmd_LCD(0b00011000);
    __delay_ms(3);
}

void DisplayDireita_LCD(void)
{
    EscreverCmd_LCD(0b00011100);
    __delay_ms(3);
}

void DisplayEsquerda_LCD(void)
{
    EscreverCmd_LCD(0b00011000);
    __delay_ms(3);
}

void SegundaLinha_LCD(void)
{
    EscreverCmd_LCD(0b11000000);
    __delay_ms(3);
}


