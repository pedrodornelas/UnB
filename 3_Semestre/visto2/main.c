#include <msp430.h>

int mede(){
    unsigned int x1=0,x2=0,dif=0;
    unsigned volatile int i=0;
    unsigned int medidas[5];
    unsigned int soma=0;

    for(i; i<=4 ; i++){
        x1=x2;
        while((TA0CCTL1 & CCIFG) == 0);
        //R5=TA0CCR1;
        x2=TA0CCR1;
        if(x2 < x1){
            dif = x1-x2;
            dif -= 65534;
        }
        else
            dif=x2-x1;
        medidas[i]=dif;
        TA0CCTL1 &= ~CCIFG;
    }
    i=1;
    for(i; i<=4; i++){
        soma += medidas[i];
    }
    soma = soma/4;

    return soma;
}

void acende(int cor){
    switch(cor){
        case (0):                      //Vermelho
                P1OUT |= BIT0;
                P4OUT &= ~BIT7;
        break;

        case (1):                      //Verde
                P1OUT &= ~BIT0;
                P4OUT |= BIT7;
        break;

        case (2):                      //Azul
                P1OUT |= BIT0;
                P4OUT |= BIT7;
        break;
    }
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TA0CTL = TASSEL_1 | MC_2;
    TA0CCTL1 = CM_1 | SCS | CAP;

    P6DIR |= BIT0 | BIT1 | BIT2 | BIT3;  //Configurando porta 6 para controlar S3,S2,S1,S0

    P1DIR &= ~BIT2;     //Ligando pino como entrada do sinal que indica a cor
    P1REN |= BIT2;
    P1OUT |= BIT2;
    P1SEL |= BIT2;

    P1DIR |=  BIT0;    //Configurando LEDS como saída
    P4DIR |=  BIT7;

    P6OUT |= BIT0;     //Setando S0 = 1 , S1 = 0
    P6OUT &= ~BIT1;


    while(1){

        P6OUT &= ~BIT2;
        P6OUT &= ~BIT3;
        unsigned int VM = mede();

        P6OUT &= ~BIT2;
        P6OUT |= BIT3;
        unsigned int AZ = mede();

        P6OUT |= BIT2;
        P6OUT |= BIT3;
        unsigned int VD = mede();

        if(VM < AZ){
            if(VM < VD)
                acende(0);     //Vermelho
            else
                acende(1);     //Verde
        }
        else{
            if(AZ < VD)
                acende(2);     //Azul
            else
                acende(1);     //Verde
        }

    }
    return 0;
}
