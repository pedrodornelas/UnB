#include <msp430.h> 

void debounce(void){
    volatile x = 1000;
    for(x;x!=0;x--);
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P4DIR |= BIT7;
	P4OUT &= ~(BIT7);

	P2DIR &= ~(BIT1);
	P2REN |= BIT1;
	P2OUT |= BIT1;

	while(1){
	    while((P2IN & BIT1) == BIT1);
	    P4OUT ^= BIT7;
	    while((P2IN & BIT1) == 0);
	}
	
	return 0;
}
