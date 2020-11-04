#include <msp430.h> 

char leds(char x){
    pcf_wr(~(x<<4));
}

char pcf_chaves(void){

}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	return 0;
}
