#include <msp430.h> 

volatile int pwm = 50; //20%
volatile int cont=0;
volatile unsigned int cont1;

#pragma vector = 53;
__interrupt void pisca(void){
    if(cont<pwm)
        P1OUT |= BIT0;
    else
        P1OUT &= ~(BIT0);
    if(cont<=99)
        cont++;
    else
        cont=0;
    cont1++;
}
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0;
	P1OUT |= BIT0;

	TA0CTL = TASSEL_2 | MC_1 ;        //Usando smclk - Período 10ms
	TA0CCR0 = 104;  //1048576*0,01 = 10400/100 = 104=1%
	TA0CCTL0 = CCIE;
	__enable_interrupt();

	while(1){
	    if(cont1==10000){
	        cont1=0;
	        if(pwm<100)
	            pwm+=10;
	        else
	            pwm=0;
	    }
	}
	return 0;
}
