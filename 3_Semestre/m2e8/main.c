#include <msp430.h> 

void debounce(void){
    volatile int x = 1000;
    for(x;x>=0;x--);
    return;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;
	while(1){
	    P1OUT ^= BIT0;
	    volatile int x1=50;
	    for(x1;x1>=0;x1--)
	        debounce();
	}
	return 0;
}
