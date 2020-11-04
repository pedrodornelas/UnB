#include <msp430.h> 

volatile int pwm = 50; //50%
volatile int cont=0,x1=0,x2=0;  //x1 e x2 - variáveis de controle das chaves

#pragma vector = 53;
__interrupt void pisca(void){
    if(cont<pwm)
        P1OUT |= BIT0;
    else
        P1OUT &= ~(BIT0);
    if(cont<=99)
        cont++;
    else
        cont=0;
}

void check_S1(void){               //x1=0 :abriu ; x1=1 :fechou ;x1=2 :continuou fechada
    if( ((P2IN & BIT1) == 0) && (x1==0) )  //chave está fechada e estava aberta
        x1=1;
    else if( ((P2IN & BIT1) == 0) && (x1==1))  //chave está fechada e estava fechada
        x1=2;
    else if( ((P2IN & BIT1) == 0) && (x1==2))  //chave está fechada e estava fechada
        x1=2;
    else                         //demais casos da chave
        x1=0;
}

void check_S2(void){               //x2=0 :abriu ; x2=1 :fechou ;x2=2 :continuou fechada
    if( ((P1IN & BIT1) == 0) && (x2==0) )  //chave está fechada e estava aberta
        x2=1;
    else if( ((P1IN & BIT1) == 0) && (x2==1))  //chave está fechada e estava fechada
        x2=2;
    else if( ((P1IN & BIT1) == 0) && (x2==2))  //chave está fechada e estava fechada
        x2=2;
    else                         //demais casos da chave
        x2=0;
}

void debounce(void){
    volatile int x = 1000;
    for(x;x>=0;x--);
    return;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;      //Configurando LED´s
    P1OUT &= ~(BIT0);

    P2DIR &= ~(BIT1);
    P2REN |= BIT1;
    P2OUT |= BIT1;

    P1DIR &= ~(BIT1);
    P1REN |= BIT1;
    P1OUT |= BIT1;

    TA0CTL = TASSEL_2 | MC_1 ;        //Usando smclk - Período 10ms
    TA0CCR0 = 104;  //1048576*0,01 = 10400/100 = 104-1%
    TA0CCTL0 = CCIE;
    __enable_interrupt();

    int velho1,velho2;

    while(1){
        velho1=x1;
        velho2=x2;
        check_S1();
        check_S2();
        if(x1==1){
            if(pwm>=10)
                pwm-=10;
            else
                pwm=100;
        }
        if(x2==1){
            if(pwm<=90)
                pwm+=10;
            else
                pwm=0;
        }
        if(velho1!=x1)
            debounce();
        if(velho2!=x2)
            debounce();
    }

    return 0;
}
