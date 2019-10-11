#include  <msp430x14x.h>
#define B1 P4IN&BIT4
#define B2 P4IN&BIT5
#define B3 P4IN&BIT6
#define B4 P4IN&BIT7

enum DIODA_ {LED1, LED2, LED3, LED4, LED5};
typedef enum DIODA_ DIODA;

//Zadanie 1
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

void Migaj(unsigned long int czas,DIODA d){
    volatile unsigned int i;
    for(i=0;i<czas;i++)
        ZapalDiode(d);
    for(i=0;i<czas;i++)
        ZgasDiode(d);
}

//Zadanie 3
void UstawPortyDlaPrzycisku(){
            P4DIR &= ~BIT4;
            P4DIR &= ~BIT5;
            P4DIR &= ~BIT6;
            P4DIR &= ~BIT7;
}

void ZmienStanDiody(DIODA d){
    switch(d){
        case(LED1):
            P2OUT ^= BIT1;
            break;
        case(LED2):
            P1OUT ^= BIT5;
            break;
        case(LED3):
            P1OUT ^= BIT6;
            break;
    }
}




void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // zatrzymanie watchdog'a
  UstawPortyDlaDiod();
  UstawPortyDlaPrzycisku();
  int StanDiody = 0;
  int freq = 3000;

  while(1)
  {
     Migaj(freq,LED2);


   if(!(B2))
     freq = freq + 500;

   if(!(B3))
     freq = freq - 500;

   if(!(B4))
     ZgasDiode(LED2);

  }



}
