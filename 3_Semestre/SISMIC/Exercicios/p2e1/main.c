#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	TA0CTL = TASSEL_1 | MC_1 ;   //ACLK = 3276;8
	TA0CCR0 = 6553;     //0,2s

	P1DIR |= BIT0;
	P1OUT |= BIT0;
	P4DIR |= BIT7;
	P4OUT |= BIT7;

	//int x1=0,x2=0;
	//int ctl1=1,ctl2=1;

	int cont1 = 0, cont2 = 0;
	while(1){
	    while((TA0CCTL0 & CCIFG) == 0);
	    TA0CCTL0 &= ~CCIFG;
	    //LED1
	    cont1++;
	    cont2++;
	    if(cont1==4)
	        P1OUT ^= BIT0;
	    if(cont2==6)
	        P4OUT ^= BIT7;
	    if(cont1==9){
	        P1OUT ^= BIT0;
	        cont1=0;
	    }
	    if(cont2==16){
	        P4OUT ^= BIT7;
	        cont2=0;
	    }
	}
	
	return 0;
}

/*
if(ctl1==1){
    if(x1<4)
        x1++;
    else{
        P1OUT &= ~BIT0;
        ctl1=0;
        x1=0;
    }
}
else{
    if(x1<5)
        x1++;
    else{
        P1OUT |= BIT0;
        ctl1=1;
        x1=0;
    }
}
//LED2
if(ctl2==1){
    if(x2<6)
        x2++;
    else{
        P4OUT &= ~BIT7;
        ctl2=0;
        x2=0;
    }
}
else{
    if(x2<10)
        x2++;
    else{
        P4OUT |= BIT7;
        ctl2=1;
        x2=0;
    }
}*/

