#include <msp430.h> 
volatile int x1=0,x2=0;

void check_S1(void){               //x1=0 :abriu ; x1=1 :fechou ;x1=2 :continuou fechada
    if( ((P2IN & BIT1) == 0) && (x1==0) )  //chave está fechada e estava aberta
        x1=1;
    else if( ((P2IN & BIT1) == 0) && (x1==1))  //chave está fechada e estava fechada
        x1=2;
    else if( ((P2IN & BIT1) == 0) && (x1==2))  //chave está fechada e estava fechada
        x1=2;
    else                         //demais casos da chave
        x1=0;
}

void check_S2(void){               //x2=0 :abriu ; x2=1 :fechou ;x2=2 :continuou fechada
    if( ((P1IN & BIT1) == 0) && (x2==0) )  //chave está fechada e estava aberta
        x2=1;
    else if( ((P1IN & BIT1) == 0) && (x2==1))  //chave está fechada e estava fechada
        x2=2;
    else if( ((P1IN & BIT1) == 0) && (x2==2))  //chave está fechada e estava fechada
        x2=2;
    else                         //demais casos da chave
        x2=0;
}

void debounce(void){
    volatile int x = 1000;
    for(x;x>=0;x--);
    return;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	    P2DIR &= ~(BIT1); //Fazendo configuração das chaves S1 e S2
	    P2REN |= BIT1;
	    P2OUT |= BIT1;

	    P1DIR &= ~(BIT1);
	    P1REN |= BIT1;
	    P1OUT |= BIT1;

	    P1DIR |= BIT0;   //Configurando LED com saída
	    //P1OUT |= BIT0;

	    P1DIR |= BIT2;   //Pino P1.2 para saída do timer
	    P1SEL |= BIT2;

	    TA0CTL = TASSEL_2 | MC_1;
	    TA0CCR0 = 10400;             //1048576*0,01 = 10400
	    TA0CCTL1 = OUTMOD_6;
	    TA0CCR1 = 0;        //Começando com 0%

	    P4DIR |= BIT7;
	    P4SEL |= BIT7;
	    PMAPKEYID = 0X02D52;
	    P4MAP7=PM_TB0CCR1A;

	    TB0CTL = TASSEL_2 | MC_1 | ID_1;
	    TB0CCR0 = 10400;
	    TB0CCTL1 = OUTMOD_6;
	    TB0CCR1 = 0;


	    int aumento1 = 1486;
	    int aumento2 = 2080;

	    int velho1, velho2;

	    while(1){
	        velho1=x1;
	        velho2=x2;
	        check_S1();
	        check_S2();

	        if(x1==1){
	            if(TA0CCR1 < TA0CCR0)
	                TA0CCR1 += aumento1;
	            if(TB0CCR1 > 0)
	                TB0CCR1 -= aumento2;
	        }
	        if(x2==1){
	            if(TB0CCR1 < TB0CCR0)
	                TB0CCR1 += aumento2;
	            if(TA0CCR1 > 0)
	                TA0CCR1 -= aumento1;
	        }

	        if(velho1!=x1)
	            debounce();
	        if(velho2!=x2)
	            debounce();

	    }
	return 0;
}
