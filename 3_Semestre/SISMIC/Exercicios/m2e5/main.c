#include <msp430.h> 

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

void debounce(void){
    volatile int x = 1000;
    for(x;x>=0;x--);
    return;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
//Habilitando pinos
	P2DIR &= ~(BIT1);      //Chave s1 como entrada
	P2REN |= BIT1;
	P2OUT |= BIT1;

	P1DIR &= ~(BIT1);     //Chave s2 como entrada
	P1REN |= BIT1;        //Habilitando resistores
	P1OUT |= BIT1;        //Habilitando pullup

	P1DIR |= BIT0;     //LED VERMELHO COMO SAÍDA
	P1OUT &= ~(BIT0);  //Desligando

	P4DIR |= BIT7;
	P4OUT &= ~(BIT7);


	int x1,x2,velho1,velho2;    //x1&x2 :variáveis de controle  velho1&velho2: estado anterior para retirar rebote

	while(1){
	    x1=check_S1(x1);
	    debounce();
	    x2=check_S2(x2);
	    debounce();
	    if(x1==1 && x2==1){
	        P1OUT &= ~(BIT0);
	        P4OUT &= ~(BIT7);
	    }
	    else if(x1==1 && x2==0){
	        P1OUT ^= BIT0;
	        P4OUT ^= BIT7;
	    }
	    else if(x1==0 && x2==1){
	        P4OUT ^= BIT7;
	    }
	}
	
	return 0;
}
