#include <msp430.h> 

void debounce(void){
    volatile int x = 1000;
    for(x;x>=0;x--);
    return;
}

int check_S1(int x1){               //x1=0 :abriu ; x1=1 :fechou ;x1=2 :continuou fechada
    if( ((P2IN & BIT1) == 0) && (x1==0) )  //chave está fechada e estava aberta
        x1=1;
    else if( ((P2IN & BIT1) == 0) && (x1==1))  //chave está fechada e estava fechada
        x1=2;
    else if( ((P2IN & BIT1) == 0) && (x1==2))  //chave está fechada e estava fechada
        x1=2;
    else                         //demais casos da chave
        x1=0;
    return x1;
}

int check_S2(int x2){               //x2=0 :abriu ; x2=1 :fechou ;x2=2 :continuou fechada
    if( ((P1IN & BIT1) == 0) && (x2==0) )  //chave está fechada e estava aberta
        x2=1;
    else if( ((P1IN & BIT1) == 0) && (x2==1))  //chave está fechada e estava fechada
        x2=2;
    else if( ((P1IN & BIT1) == 0) && (x2==2))  //chave está fechada e estava fechada
        x2=2;
    else                         //demais casos da chave
        x2=0;
    return x2;
}

unsigned char rand() {
static unsigned char num = 5;
num = (num * 17) % 7;
return num;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P2DIR &= ~(BIT1);   //CHAVE S1
	P2REN |= BIT1;
	P2OUT |= BIT1;

	P1DIR &= ~(BIT1);  //CHAVE S2
	P1REN |= BIT1;
	P1OUT |= BIT1;

	P1DIR |= BIT0;

	P4DIR |= BIT7;

	int x1,x2,cont,num,tempo3s;

	while(1){
	    P1OUT &= ~(BIT0);
	    P4OUT &= ~(BIT7);
	    cont=x1=x2=0;
	    num = rand();
	    while(x2!=1){
	        x1=check_S1(x1);
	        debounce();
	        x2=check_S2(x2);
	        debounce();
	        if(x1==1)
	            cont++;
	        if(cont==6)
	            x2=1;
	    }
	    if(num==cont)
	        P4OUT |= BIT7;
	    else
	        P1OUT |= BIT0;

	    tempo3s = 200;
	    for(tempo3s;tempo3s>=0;tempo3s--)
	        debounce();
	}

	return 0;
}
