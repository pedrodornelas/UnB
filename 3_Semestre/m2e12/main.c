#include <msp430.h> 

#pragma vector = 49;          //TA1.CCR0 E CCIFG0
__interrupt void pisca_verde(void){
    P4OUT ^= BIT7;
}

#pragma vector = 53    //TA0.CCR0 E CCIFG0
__interrupt void pisca_vermelho(void){
    P1OUT ^= BIT0;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P4DIR |= BIT7;
	P1DIR |= BIT0;

	TA0CTL = MC_1 | TASSEL_1;
	TA0CCR0 = 8191;     //32768 * 0,25 = 8192
	TA0CCTL0 = CCIE;

	TA1CTL = MC_1 | TASSEL_1;
	TA1CCR0 = 3275;   //32768 * 0,1 = 3276,8
	TA1CCTL0 = CCIE;

	__enable_interrupt();

	while(1);
	
	return 0;
}
