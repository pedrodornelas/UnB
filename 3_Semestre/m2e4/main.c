#include <msp430.h>

void debounce(void){
    volatile int x=1000;
    for(x;x!=0;x--);
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

/*  if( ((P1IN & BIT1) == BIT1) && (x1==0) )   //chave está aberta e estava aberta
        x1=0;
    else if( ((P1IN & BIT1) == BIT1) && (x1==1) )   //chave está aberta e estava fechada
        x1=0;
    else if( ((P1IN & BIT1) == 0) && (x1==0) )  //chave está fechada e estava aberta
        x1=1;
    else if( ((P1IN & BIT1) == 0) && (x1==1) )  //chave está fechada e estava fechada
        x1=2;
    else if((x1==2) && ((P1IN & BIT1) == 0))
        x1=2;
    else
        x1=0;*/

int check_S2(int x2){               //x1=0 :abriu ; x1=1 :fechou ;x1=2 :continuou fechada
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

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P2DIR &= ~(BIT1);    //Configurando chave como entrada para MSP
	P2REN |= BIT1;       //Habilitando resistor de pullup
	P2OUT |= BIT1;

	P1DIR &= ~(BIT1);
	P1REN |= BIT1;
	P1OUT |= BIT1;

	P1DIR |= BIT0;      //Habilitando LED como saída
	P1OUT &= ~(BIT0);   //Começando apagado;

	int x1=0,x2=0;         //Variáveis de monitoramento de chaves
	int velho1,velho2;     //Verifica se houve uma mudança de estado.
	while(1){
	    velho1=x1;
	    velho2=x2;
	    x1=check_S1(x1);
	    x2=check_S2(x2);
	    if((x1==1) || (x2==1))
	        P1OUT ^= BIT0;
	    if((velho1!=x1) || (velho2!=x2))
	        debounce();
	}

	return 0;
}
