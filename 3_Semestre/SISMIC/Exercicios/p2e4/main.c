#include <msp430.h>

volatile int x1=0,x2=0;

void check_S1(void){      //Chave S1
    if( ((P2IN & BIT1)==0) && (x1==0))   //Estava aberta e fechou
        x1=1;                       //Fechou
    else if( ((P2IN & BIT1)==0) && (x1==1))   //Estava fechada e continuou fechada
        x1=2;                       //Continou fechada
    else if( ((P2IN & BIT1)==0) && (x1==2))
        x1=2;
    else                            //Demais casos da chave
        x1=0;
}

void check_S2(void){     //Chave S2
    if( ((P1IN & BIT1)==0) && (x2==0))
        x2=1;
    else if( ((P1IN & BIT1)==0) && (x2==1))
        x2=2;
    else if( ((P1IN & BIT1)==0) && (x2==2))
        x2=2;
    else
        x2=0;
}

void debounce(void){
    volatile int i=1000;
    for(i;i!=0;i--);
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P2DIR &= ~BIT1; //Configurando como entrada
	P2REN |= BIT1;  //Habilitando Resistor
	P2OUT |= BIT1;  //Resistor de PULL-UP

	P1DIR &= ~BIT1;
	P1REN |= BIT1;
	P1OUT |= BIT1;

	P4DIR |= BIT7;
	P4SEL |= BIT7;
	PMAPKEYID = 0X02D52;
	P4MAP7=PM_TB0CCR1A;

	TB0CTL = TASSEL_1 | MC_1 ;
	TB0CCR0 = 330;//10ms
	TB0CCTL1 = OUTMOD_6;
	TB0CCR1 = TB0CCR0/2;//PWM 50%

	int passo = 33;
	int velho1,velho2;

	while(1){
	    velho1=x1;
	    velho2=x2;
	    check_S1();
	    check_S2();

	    if(x1==1){
	        if(TB0CCR1 < TB0CCR0)
	            TB0CCR1 += passo;
	    }
	    if(x2==1){
	        if(TB0CCR1 > 0)
	            TB0CCR1 -= passo;
	    }

	    if(velho1!=x1)
	        debounce();
	    if(velho2!=x2)
	        debounce();

	}
	return 0;
}
