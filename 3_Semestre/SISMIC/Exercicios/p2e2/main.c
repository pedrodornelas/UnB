#include <msp430.h>
int cont1=0,cont2=0;

#pragma vector=53;
__interrupt void pisca(void){
    cont1++;
    cont2++;
    if(cont1==4)
        P1OUT ^= BIT0;
    if(cont1==9){
        P1OUT ^= BIT0;
        cont1=0;
    }
    if(cont2==6)
        P4OUT ^= BIT7;
    if(cont2==16){
        P4OUT ^= BIT7;
        cont2=0;
    }
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	TA0CTL = TASSEL_1 | MC_1;
	TA0CCR0 = 6553;

	TA0CCTL0 = CCIE;

	P1DIR |= BIT0;
	P1OUT |= BIT0;
	P4DIR |= BIT7;
	P4OUT |= BIT7;

	__enable_interrupt();

	while(1);

	return 0;
}
