#include <msp430.h>

volatile int x1=0,x2=0,estado=0;

void check_S1(void){
    if( ((P2IN & BIT1)==0) && (x1==0) )
        x1=1;  //fechou
    else if( ((P2IN & BIT1)==0) && (x1==1) )
        x1=2;  //continuou fechada
    else if( ((P2IN & BIT1)==0) && (x1==2) )
        x1=2;  //continou fechada
    else
        x1=0;   //aberta
}

void check_S2(void){
    if( ((P1IN & BIT1)==0) && (x2==0))
        x2=1; //fechou
    else if( ((P1IN & BIT1)==0) && (x2==1))
        x2=2;  //continuou fechada
    else if( ((P1IN & BIT1)==0) && (x2==2))
        x2=2;  //continuou fechada
    else
        x2=0;  //aberta
}

char chaves(void){
    if (estado!=1){
        check_S1();
        check_S2();
        if(x1==0 && x2==0)
            return 0;
        else if(x2==0){
            rebote();
            return 1;
        }
        else if(x1==0){
            rebote();
            return 2;
        }
        else{
            rebote();
            estado=1;
            return 1;
        }
    }
    else{
        estado=0;
        return 2;
    }
}

void config_timer(void){
    TA2CTL = TASSEL_2 | MC_1;
    TA2CCR0 =  17476;//usando smclk : 1048576/60Hz = 17476
    TA2CCTL2 = OUTMOD_6;
    TA2CCR2 = 0;
}

void servo(char ang){
    TA2CCR2 = (17476*ang)/180
}

void teste(void){

}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	config_pinos();
	return 0;
}
