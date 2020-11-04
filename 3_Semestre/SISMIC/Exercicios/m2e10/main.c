#include <msp430.h> 

#pragma vector = 53;
__interrupt void pisca(void){   //Esta interrupção zera automaticamente o CCIFG
    P1OUT ^= BIT0;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;
	TA0CTL = MC_1 | TASSEL_1 ;
	TA0CCR0 = 16383;      //32768 * 0,5s = 16384
	TA0CCTL0 = CCIE;
	__enable_interrupt();

	while(1);

	return 0;
}
