#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT0;

	TA0CTL = TASSEL_1 | MC_1;
	TA0CCTL0 = CM_0;
	TA0CCR0 = 16383;      //Gerando frequência para que o led verde alterne o estado em 500ms , ou 0,5s.

	while(1){
	    while((TA0CCTL0 & CCIFG) == 0);
	    P1OUT ^= BIT0;
	    TA0CCTL0 &= ~CCIFG;
	}

	return 0;
}
