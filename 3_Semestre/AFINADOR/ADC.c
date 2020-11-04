/*
 * ADC.c
 *
 *  Created on: 24 de nov de 2019
 *      Author: pedro
 */

#include <msp430.h>

void inic_adc(void){
    ADC12CTL0 &= ~ADC12ENC;//Desabilita ADC para configuração

    //Controles do ADC
    ADC12CTL0 = ADC12SHT0_3 | //ADC tempo amostragem ADCMEM[0-7] - 32 ciclos
                ADC12ON | //Liga ADC
                ADC12REFON;

    ADC12CTL1 = ADC12CSTARTADD_0 | //CSTARADD define primeiro registrador da sequência, portanto, setamos como 0, para ser o primeiro regitrador.
                ADC12SHS_1 | //Define TA0.1 como timer de conversão
                ADC12SHP | //Tempo de amostragem disparador por SHI, que controla o SAMPCON
                ADC12SSEL_3 | //Usando SMCLK para conversão do ADC
                ADC12DIV_0 | //Divisor = SMCLK * 1/1
                ADC12CONSEQ_3; //Sequencia de canais

    ADC12CTL2 = ADC12TCOFF | //Desligar sensor de temperatura
                ADC12RES_2;  //RESOLUÇÃO 12 BITS (13 CLOCK)

    //Controle da memória 0
    ADC12MCTL0 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL1 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL2 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL3 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL4 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL5 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL6 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL7 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL8 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL9 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL10 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                  ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL11 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                  ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL12 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                  ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL13 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                  ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL14 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                  ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    ADC12MCTL15 = ADC12EOS    | //Fim de sequência
                  ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                  ADC12INCH_0;  //Canal A0: seleciona P6.0 para fazer conversão

    /*ADC12IE = ADC12IE0 | ADC12IE1 | ADC12IE2 | ADC12IE3 | ADC12IE4 | ADC12IE5 | ADC12IE6 | ADC12IE7 | ADC12IE8 |
              ADC12IE9 | ADC12IE10 | ADC12IE11 | ADC12IE12 | ADC12IE13 | ADC12IE14 | ADC12IE15 ; //habilita interrupção para conversão*/

    //ADC12IE = ADC12IE15; //Interrupção ADC12IFG15

    ADC12CTL0 |= ADC12ENC;// Habilita ADC

    //P6.0 - Para economizar energia
    P6SEL |= BIT0;
}

//Timer do ADC
void disparo(void){
    TA0CTL = TASSEL_2 | MC_1 | TACLR;
    TA0CCR0 = 22;  //44k amostras por segundo
    TA0CCR1 = TA0CCR0/2; //onda quadrada
    TA0CCTL1 = OUTMOD_6;
}

