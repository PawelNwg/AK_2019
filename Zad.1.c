#include  <msp430x14x.h>

enum DIODA_ {LED1, LED2, LED3, LED4, LED5};
typedef enum DIODA_ DIODA;

void ZapalDiode(DIODA d){
    switch(d){
        case(LED1):
            P2OUT &= ~BIT1;
            break;
        case(LED2):
            P1OUT |= BIT5;
            break;
        case(LED3):
            P1OUT |= BIT6;
            break;
    }
}

void ZgasDiode(DIODA d){
    switch(d){
        case(LED1):
            P2OUT |= BIT1;
            break;
        case(LED2):
            P1OUT &= ~BIT5;
            break;
        case(LED3):
            P1OUT &= ~BIT6;
            break;
    }
}

void UstawPortyDlaDiod(){
    P2DIR |= BIT1;
    P1DIR |= BIT5;
    P1DIR |= BIT6;
    ZgasDiode(LED1);
    ZgasDiode(LED2);
    ZgasDiode(LED3);
}


void Migaj(unsigned long int czas,DIODA d){
    volatile unsigned int i;
    for(i=0;i<czas;i++)
        ZapalDiode(d);
    for(i=0;i<czas;i++)
        ZgasDiode(d);
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // zatrzymanie watchdog'a
  UstawPortyDlaDiod();

  while(1){

    Migaj(30000,LED1);
  }
}
