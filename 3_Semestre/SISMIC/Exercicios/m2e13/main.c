#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	TB0CTL = TASSEL_2 | MC_1 | CNTL_0 ;  //Usando SMCLK
	TB0CCR0 = 10484;         // 1048576 * 0,01 = 10485,76

	TB0CCTL0 = OUTMOD_6 | OUT | CM_0;
	TB0CCR1 = 5242;

	P4SEL |= BIT7;

	PMAPKEYID = 0x02D52;    //Liberar mapeamento do led como timer LED_VERDE(P4.7)
	P4MAP7 = PM_TB0CCR0A;   //Colocando saída de TB0 OUT (TB0CCR1)

	while(1){
	}

	return 0;
}
