// Básico para o LCD funcionar
// P3.0 = SDA e P3.1=SCL

#include <msp430.h>

#define BR100K  10  //SCL operando em 100 kHz (SMCLK)
#define BR10K   21  //SCL operando em 50 kHz (SMCLK)
#define BR10K   105 //SCL operando em 10 kHz (SMCLK)

#define BIT_BL  BIT3    //Back light
#define BIT_E   BIT2    //Enable

// Dois possíveis endereços do PCF8574
#define PCF_ADR 0x27
//#define PCF_ADR   0x3F

// Protótipo das funções
void lcdQUALadr();
void config_I2C(void);
void LCD_inic(void);
void LCD_aux(char dado);
void PCF_STT_STP(void);
int PCF_read(void);
void PCF_write(char dado);
void delay(long limite);
void lcd_char(char letra);
void lcdBacklightON(void);
void lcdBacklightOFF(void);
void lcd_cursor(char);
void A0(void);
void A1(void);
void lcd_string(char x[]);
void converte(int);
void tens(int);
void lcd_hex(void);
volatile float tensao=0;
volatile int tensao1=0;
volatile int tens_ant=0;
volatile int conta, flag, voltA0=0, testa0=0, a, b, cont=0;
volatile long int soma0=0;

void main(void){
    char i;
    int cont=0;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    config_I2C();
    config_TIMER2();
    LCD_inic();
    inic_adc();
    disparo();
    lcdBacklightON();
    __enable_interrupt();
    while(1){
        if(flag==1){
            A0();
            A1();
        }
    }
}

void tensA0(void){
    tens_ant = tensao;
    tensao = (3.3*voltA0)/4095;
    tensao1 = 1000*tensao;
    int a = tensao1/1000;
    int b = (tensao1/100)%10;
    int c = (tensao1%100)/10;
    int d = (tensao1%100)%10;
    converte(a);
    lcd_char(',');
    converte(b);
    converte(c);
    converte(d);
}

void lcd_hex(void){
    int rest[4];
    int i=3;
    int k = tensao1;
    char str[4];
    for(i;i>=0;i--){
        if((k%16)<=9)
            str[i]=(k%16)+0x30;
        else
            str[i]=(k%16)+0x37;
        k = k/16;
    }
    lcd_string(str);
}

void converte(int num){
    num += 0x30;
    lcd_char(num);
}

void lcd_string(char x[]){
    int i=0;
    char a;
    for(i;x[i]!=0;i++){
        a = x[i];
        lcd_char(a);
    }
}

void A0(void){
    lcd_cursor(0x0);
    lcd_string("A0=");
    tensA0();
    lcd_string("V ");
    lcd_hex();
    lcd_cursor(0x0E);
    lcd_string(" ");
    converte(cont);
}

void A1(void){
    lcd_cursor(0x40);
    int quadrados;
    quadrados = (tensao1*16)/3300;
    int brancos = 16 - quadrados;
    int i=0;
    while(i < quadrados){
        lcd_char(0xFF);
        i++;
    }
    while(i < 16){
        lcd_char(0x20);
        i++;
    }
}


// Configurar Pinos I2C - UCSB0
// P3.0 = SDA e P3.1=SCL
void config_I2C(void){
    P3SEL |=  BIT1 | BIT0;    // Use dedicated module
    P3REN |=  BIT1 | BIT0;    // Resistor enable
    P3OUT |=  BIT1 | BIT0;    // Pull-up

    UCB0CTL1 |= UCSWRST;    // UCSI B0 em ressete

    UCB0CTL0 = UCSYNC |     //Síncrono
               UCMODE_3 |   //Modo I2C
               UCMST;       //Mestre

    //UCB0BRW = BR100K;       //100 kbps
    //UCB0BRW = BR50K;      // 20 kbps
    UCB0BRW = BR10K;      // 10 kbps
    UCB0CTL1 = UCSSEL_2;   //SMCLK e remove ressete
}



// Incializar LCD modo 4 bits
void LCD_inic(void){

    PCF_STT_STP();      //Colocar PCF em estado conhecido

    // Preparar I2C para operar
    UCB0I2CSA = PCF_ADR;    //Endereço Escravo
    UCB0CTL1 |= UCTR    |   //Mestre TX
                UCTXSTT;    //Gerar START
    while ( (UCB0IFG & UCTXIFG) == 0);          //Esperar TXIFG=1
    UCB0TXBUF = 0;                              //Saída PCF = 0;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);   //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)    //NACK?
                while(1);

    // Começar inicialização
    LCD_aux(0);     //RS=RW=0, BL=1
    delay(20000);
    LCD_aux(3);     //3
    delay(10000);
    LCD_aux(3);     //3
    delay(10000);
    LCD_aux(3);     //3
    delay(10000);
    LCD_aux(2);     //2

    // Entrou em modo 4 bits
    LCD_aux(2);     LCD_aux(8);     //0x28
    LCD_aux(0);     LCD_aux(8);     //0x08
    LCD_aux(0);     LCD_aux(1);     //0x01
    LCD_aux(0);     LCD_aux(6);     //0x06
    LCD_aux(0);     LCD_aux(0xF);   //0x0F

    while ( (UCB0IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB0CTL1 |= UCTXSTP;                           //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP
    delay(50);
}


// Auxiliar inicialização do LCD (RS=RW=0)
// * Só serve para a inicialização *
void LCD_aux(char dado){
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT_BL;          //PCF7:4 = dado;
    delay(50);
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT_BL | BIT_E;  //E=1
    delay(50);
    while ( (UCB0IFG & UCTXIFG) == 0);              //Esperar TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT_BL;          //E=0;
}


// Gerar START e STOP para colocar PCF em estado conhecido
void PCF_STT_STP(void){
    int x=0;
    UCB0I2CSA = PCF_ADR;        //Endereço Escravo

    while (x<5){
        UCB0CTL1 |= UCTR    |   //Mestre TX
                    UCTXSTT;    //Gerar START
        while ( (UCB0IFG & UCTXIFG) == 0);  //Esperar TXIFG=1
        UCB0CTL1 |= UCTXSTP;                //Gerar STOP
        delay(200);
        if ( (UCB0CTL1 & UCTXSTP) == 0)   break;   //Esperar STOP
        x++;
    }
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);   //I2C Travado (Desligar / Ligar)
}


// Ler a porta do PCF
int PCF_read(void){
    int dado;
    UCB0I2CSA = PCF_ADR;                //Endereço Escravo
    UCB0CTL1 &= ~UCTR;                  //Mestre RX
    UCB0CTL1 |= UCTXSTT;                //Gerar START
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);
    UCB0CTL1 |= UCTXSTP;                //Gerar STOP + NACK
    while ( (UCB0IFG & UCRXIFG) == 0);  //Esperar RX
    dado=UCB0RXBUF;
    delay(50);
    return dado;
}


// Escrever dado na porta
void PCF_write(char dado){
    UCB0I2CSA = PCF_ADR;        //Endereço Escravo
    UCB0CTL1 |= UCTR    |       //Mestre TX
                UCTXSTT;        //Gerar START
    while ( (UCB0IFG & UCTXIFG) == 0)   ;          //Esperar TXIFG=1
    UCB0TXBUF = dado;                              //Escrever dado
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT)   ;   //Esperar STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG)       //NACK?
                while(1);                          //Escravo gerou NACK
    UCB0CTL1 |= UCTXSTP;                        //Gerar STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   //Esperar STOP
    delay(50);
}

void delay(long limite){
    volatile long cont=0;
    while (cont++ < limite) ;
}

void lcdBacklightON(void){
    PCF_write(8);
}

void lcdBacklightOFF(void){
    PCF_write(0);
}

void lcd_char(char letra){
    volatile char porta = letra;

    porta &= 0xF0;
    porta |= BIT0 | BIT3;
    PCF_write(porta);
    porta |= BIT2;
    PCF_write(porta);
    porta &= ~BIT2;
    PCF_write(porta);


    porta = (letra & 0xF)<<4;
    porta |= BIT0 | BIT3;
    PCF_write(porta);
    porta |= BIT2;
    PCF_write(porta);
    porta &= ~BIT2;
    PCF_write(porta);

}
void lcd_cursor(char letra){
    char porta = letra | 0x80;

    porta &= 0xF0;
    porta |= BIT3;
    PCF_write(porta);
    porta |= BIT2;
    PCF_write(porta);
    porta &= ~BIT2;
    PCF_write(porta);


    porta = (letra & 0xF)<<4;
    porta |= BIT3;
    PCF_write(porta);
    porta |= BIT2;
    PCF_write(porta);
    porta &= ~BIT2;
    PCF_write(porta);

}

void inic_adc(void){
    ADC12CTL0 &= ~ADC12ENC;//Desabilita ADC para configuração

    //Controles do ADC
    ADC12CTL0 = ADC12SHT0_3 | //ADC tempo amostragem ADCMEM[0-7] - 32 ciclos
                ADC12ON     | //Liga ADC
                ADC12REFON;

    ADC12CTL1 = ADC12CSTARTADD_0 | //CSTARADD define primeiro registrador da sequência, portanto, setamos como 0, para ser o primeiro regitrador.
                ADC12SHS_1       | //Define TA0.1 como timer de conversão
                ADC12SHP         | //Tempo de amostragem disparador por SHI, que controla o SAMPCON
                ADC12SSEL_3      | //Usando SMCLK para conversão do ADC
                ADC12DIV_7       | //Divisor = SMCLK * 1/8
                ADC12CONSEQ_2;     //Modo repete sequência de canais

    ADC12CTL2 = ADC12TCOFF | //Desligar sensor de temperatura
                ADC12RES_2; //RESOLUÇÃO 12 BITS (13 CLOCK)

    //Controle da memória 0
    ADC12MCTL0 = ADC12SREF_0 | //VR+ = AVCC VR- = AVSS , referências de tensão da MSP
                 ADC12INCH_0; //Canal A0: seleciona P6.0 para fazer conversão

    ADC12IE = ADC12IE0; //habilita interrupção para conversão: ADC12IFG0 e ADC12IFG1

    ADC12CTL0 |= ADC12ENC; // Habilita ADC

    //P6.0 e P6.1 - Para economizar energia
    P6SEL |= BIT0;
}

void disparo(){
    TA0CTL = TASSEL_1 | MC_1 | TACLR;
    TA0CCR0 = 32768/16;
    TA0CCR1 = TA0CCR0;
    TA0CCTL1 = OUTMOD_6;
}

#pragma vector = ADC12_VECTOR;
__interrupt void intadc(){

    switch(__even_in_range(ADC12IV,8)){
    case 6: //ADC12MEM0 chamou interrupção
            conta++;
            int x = ADC12MEM0;
            soma0 = soma0 + x;
            if(conta >= 16){
                voltA0 = soma0/16;
                soma0 = 0;
                conta = 0;
                flag = 1;
            }
            break;
    }

}

void config_TIMER2(void){
    TA1CTL = TASSEL_1 | MC_1 | TACLR;
    TA1CCR0 = 32768;
    TA1CCTL0 = CCIE;
}

#pragma vector = 49;
__interrupt void contador(void){
    if(cont!=9)
        cont++;
    else
        cont=0;
}
