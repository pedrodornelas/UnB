#include <msp430.h> 
int x1=0,x2=0;

void check_S1(void){
    if( ((P2IN & BIT1)==0) && (x1==0))
        x1=1;
    else if ( ((P2IN & BIT1)==0) && (x1==1))
        x1=2;
    else if ( ((P2IN & BIT1)==0) && (x1==2))
        x1=2;
    else
        x1=0;
}
void check_S2(void){
    if( ((P1IN & BIT1)==0) && (x2==0))
        x2=1;
    else if ( ((P1IN & BIT1)==0) && (x2==1))
        x2=2;
    else if ( ((P1IN & BIT1)==0) && (x2==2))
        x2=2;
    else
        x2=0;
}

void debounce(){

}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    // a + b + c + d + e + f + g + dp = 255
    //128+ 64+ 32+ 16+ 8 + 4 + 2 + 1
    // 0 = g+dp

    volatile int num[7]= [3,159,37,13,153,73,65]
    config_pinos();

    int cont = 0;
    int velho1,velho2;
    P1OUT = num[cont];  //começar com 0

    while(1){
        velho1=x1;
        velho2=x2;
        check_S1();
        check_S1();

        if(x1==1){
            if(cont<6)
                cont++;
            P1OUT = num[cont];
        }
        if(x2==1){
            if(cont>0)
                cont--;
            P1OUT = num[cont];
        }

        if(velho1!=x1)
            debounce();
        if(velho2!=x2)
            debounce();
    }
    return 0;
}

