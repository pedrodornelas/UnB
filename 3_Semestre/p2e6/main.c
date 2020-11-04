#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// a + b + c + d + e + f + g + dp = 255
	//128+ 64+ 32+ 16+ 8 + 4 + 2 + 1
	// 0 = g+dp

	volatile int num[7]= [3,159,37,13,153,73,65]
	config_pinos();
	
	TA0CTL = TASSEL_1 | MC_1 ;
	TA0CCR0 = 32767;
	TA0CCTL0;

	int cont = 0;

	while(1){
	    while((TA0CCTL0 & CCIFG) == 0);
	    P1OUT = num[cont];

	    if (cont == 6)
	        cont = 0;
	    else
	        cont++;

	    TAOCCTL0 &= ~CCIFG;
	}
	return 0;
}
