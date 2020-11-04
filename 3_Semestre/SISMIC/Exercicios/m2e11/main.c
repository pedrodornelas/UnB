#include <msp430.h> 

int cont=0;       //variável global

#pragma vector = 53;
__interrupt void pisca(void){   //Esta interrupção zera automaticamente o CCIFG
    P4OUT ^= BIT7;
    cont++;
    if(cont==2){
        P1OUT ^= BIT0;
        cont=0;
    }
}
/*
#pragma vector = 52;     //Escolhendo outras interrupções do TIMER-A0;
__interrupt void pisca_vermelho(void){
    switch(TA0IV){
    case 0x0:break; //Caso não tenha interrupção
    case 0x2:       //Habilitando interrupção do TA0CCTL1.CCIFG
        P1OUT ^= BIT0;
        break;
    default:break;
    }
}*/

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;
    P4DIR |= BIT7;

    TA0CTL = MC_1 | TASSEL_1 ;

    TA0CCR0 = 8191;      //32768 * 0,25s = 8192
    TA0CCTL0 = CCIE;

    __enable_interrupt();

    while(1);

    return 0;
}

