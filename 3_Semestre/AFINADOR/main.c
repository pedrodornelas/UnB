//Feito por Lucas Rabelo(18/0105442) e Pedro Henrique(18/0108140)
//Data: 09/12/2019

// Básico para o LCD funcionar
// P3.0 = SDA e P3.1=SCL

//Afinador de instrumentos musicais, que reconhece as notas tocadas com base em um circuito que liga um microfone a MSP, e assim capturamos o sinal
//que fazemos uma série de calculos para descobrir de qual frequência se trata e a mostramos no LCD.


#include <msp430.h> 
#include "ADC.h"

#define ADC12MEM0_ADR (__SFR_FARPTR) 0x0720
#define BR100K  10  //SCL operando em 100 kHz (SMCLK)
#define BR10K   21  //SCL operando em 50 kHz (SMCLK)
#define BR10K   105 //SCL operando em 10 kHz (SMCLK)

#define BIT_BL  BIT3    //Back light
#define BIT_E   BIT2    //Enable

// Dois possíveis endereços do PCF8574
#define PCF_ADR 0x27

// Protótipo das funções
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
void lcd_string(char x[]);

//Variáveis de controle, assim como vetor de dados.
float media=0;                       //Variável em que colocamos a média dos mínimos capturados pelo sinal do microfone.
int cont,i=0,j=0 ;                   //Contadores para auxiliar no programa
int x[2000];                         //Valores adquiridos pelo conversor AD, que é obtido pelo sinal do microfone.
const int n=(sizeof(x)/sizeof(int)); //Tamanho do vetor dos valores acima
int minimos[n];                    //Vetor com os mínimos obtidos da senóide de som

void main(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    inic_adc();
    disparo();

    cont=0;
    inic_dma();
    while(cont<n){   //Esperamos ser capturadas 2000 amostras, no qual são passadas por DMA do AD para a memória
        while((DMA0CTL & DMAIFG) == 0);
        cont += 16; //Para atualizar em que posição o DMA guardará os dados na memória.
        inic_dma();
    }

    //Zerar vetor dos mínimos
    for(i=0; i<n; i++){
        minimos[i]=0;
    }

    //Aqui descobrimos os pontos de mínimo de x, e guardamos no vetor de mínimos
    for(i=0; i<n ; i++){
        if((x[i] > x[i+1]) && (x[i+2] > x[i+1])){
                minimos[j]=x[i+1];
                j++;
        }
    }

    //Necessitamos descobrir o tamanho do vetor de mínimos para calcular sua média
    int tamanho=0;
    for(i=0;tamanho==0;i++){
        if((minimos[i]==0) && (minimos[i+1]==0) && (minimos[i+2]==0))
            tamanho=i-1;
    }

    float k=0;  //Necessitamos dessa variável auxiliar para o compilador fazer corretamente os calculos com float
    media=0;
    for(i=0;i<=tamanho;i++){  //Calculamos a média dos mínimos
        k= minimos[i];
        media += (k/1000);    //Reduzimos o número para previnir do overflow
    }
    media = (media/tamanho)*1000;

    //Para calcularmos uma 'densidade média' de pontos mínimos que estão abaixo da média, pegamos quantos desses pontos estão abaixo da média de mínimos
    cont=0;
    for(i=0; i<n ; i++){
        if(x[i]<=media)
            cont++;
    }
    k=cont;

    volatile float perc=0;  //Aqui calculamos a porcentagem de pontos que estão abaixo da média de mínimos, e assim obtemos uma aproximada densidade
    perc=k/2000;            //e dessa forma, pegamos algumas faixas em que tal frequência gera dessa densidade.

    config_I2C();
    LCD_inic();
    lcdBacklightON();
    lcd_cursor(0x3);

    if((perc>0.1809) && (perc<0.2004)){
        lcd_string("Nota: La(A)");
        lcd_cursor(0x45);
        lcd_string("440Hz");
    }
    else if((perc>0.2005) && (perc<0.2402)){
        lcd_string("Nota: Si(B)");
        lcd_cursor(0x45);
        lcd_string("495Hz");
    }
    else if((perc>0.2403) && (perc<0.259)){
        lcd_string("Nota: Do(C)");
        lcd_cursor(0x45);
        lcd_string("528Hz");
    }
    else if((perc>0.27) && (perc<0.296)){
        lcd_string("Nota: Re(D)");
        lcd_cursor(0x45);
        lcd_string("594Hz");
    }
    else if((perc>0.125) && (perc<0.13599)){
        lcd_string("Nota: Mi(E)");
        lcd_cursor(0x45);
        lcd_string("330Hz");
    }
    else if((perc>0.136) && (perc<0.154)){
        lcd_string("Nota: Fa(F)");
        lcd_cursor(0x45);
        lcd_string("352Hz");
    }
    else if((perc>0.1589) && (perc<0.171)){
        lcd_string("Nota: Sol(G)");
        lcd_cursor(0x45);
        lcd_string("396Hz");
    }

    while(1);
    return 0;
}

void inic_dma(void){
    DMACTL0 = DMA0TSEL_24;
    DMA0CTL = DMADT_0      | //Modo simples
              DMADSTINCR_3 | //Incrementa Destino
              DMASRCINCR_3 ; //Incrementa Origem

    DMA0SA = ADC12MEM0_ADR;  //Endereço inicial MEM0
    DMA0DA = &x[cont];      //Endereço baseado no vetor e sua posição.
    DMA0SZ = 16;

    DMA0CTL |= DMAEN;
}

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

void lcd_string(char x[]){
    int i=0;
    char a;
    for(i;x[i]!=0;i++){
        a = x[i];
        lcd_char(a);
    }
}
