/*
 * File:   LCD.h
 * Author: Professor
 *
 * Created on 19 de Outubro de 2022, 20:46
 */

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus

extern "C" {
#endif

/* ************************* */
#define LCD_BUS         PORTB //Saída de dados para LCD
#define ENABLE_LCD      PORTCbits.RC3 //Definição do pino Enable
#define RS_LCD          PORTCbits.RC2 //Define pino RS

#define LCD_BUS_DIRECTION   TRISB //Define direção dos dados
#define ENABLE_DIRECTION    TRISCbits.TRISC3 //Define da direção
#define RS_DIRECTION        TRISCbits.TRISC2 //Define RS

    /* Função para o LCD */
    void Iniciar_LCD(void);
    void ComutarEnable_LCD(void);

    void EscreverCmd_LCD(unsigned char Cmd);
    void EscreverDado_LCD(unsigned char Data);
    void EscreverString_LCD(const char *String);

    void LimparTela_LCD(void);
    void CursorHome_LCD(void);
    void DisplayOn_LCD(void);
    void DisplayOff_LCD(void);
    void CursorOn_LCD(void);
    void CursorOff_LCD(void);
    void BlinkOn_LCD(void);
    void BlinkOff_LCD(void);
    void CursorDireita_LCD(void);
    void CursorEsquerda_LCD(void);
    void DisplayDireita_LCD(void);
    void DisplayEsquerda_LCD(void);
    void SegundaLinha_LCD(void);
/* ************************* */

#ifdef __cpluscplus
}
#endif



#endif    /* LCD_H */