#include <msp430.h>
volatile int tecla = 0;
volatile char code[3][4];
code[0][0]=3;code[0][1]=6;code[0][2]=9;code[0][3]=#;
code[1][0]=2;code[1][1]=5;code[1][2]=8;code[1][3]=0;
code[2][0]=1;code[2][1]=4;code[2][2]=7;code[2][3]=*;

#pragma vector=53;
__interrupt void varredura(void){
    P1OUT &= ~(BIT6);
    x = P1IN & BIT3 & BIT2 & BIT1 & BIT0;
    if(x!=15){
        letra = code[0];
    }
    P1OUT |= BIT6;
    P1OUT &= ~(BIT5);
    x = P1IN & BIT3 & BIT2 & BIT1 & BIT0;
    if(x!=15){

    }
    P1OUT |= BIT5;
    P1OUT &= ~(BIT4);
    x = P1IN & BIT3 & BIT2 & BIT1 & BIT0;
    if(x!=15){

    }
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR &= ~(BIT3) & ~(BIT2) & ~(BIT1) & ~(BIT0);
	P1REN |= BIT3 | BIT2 | BIT1 | BIT0;
	P1OUT |= BIT3 | BIT2 | BIT1 | BIT0;

	P1DIR |= BIT6 | BIT5 | BIT4;
	P1OUT |= BIT6 | BIT5 | BIT4;

	TA0CTL = TASSEL_1 | MC_1;
	TA0CCR0 = 327;
	TA0CCTL0 = CCIE;
	__enable_interrupt();

	while(1){

	}

	return 0;
}
