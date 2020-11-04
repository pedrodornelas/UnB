#include <msp430.h> 

#pragma vector=53;
__interrupt void pisca(void){
    P1OUT^=BIT0;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	TA0CTL = TASSEL_1 | MC_2;
	TA0CCTL0 = CCIE;

	P1DIR|=BIT0;
	P1OUT|=BIT0;

	__enable_interrupt();
	
	while(1);
	return 0;
}
