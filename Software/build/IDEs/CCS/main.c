
#include "Can.h"


/**
 * main.c
 */
#define LOOPBACK           STD_OFF

void Can_Port_Enable(void);
void PLL_Init(void);
void PortF_Init(void);
void Test1_RxTx_Polling(void) ;
void Test2_TX_2_Objs_RX_2_Objs(void) ;
void Test3_RxTx_Interrupt(void) ;
void irq_Enable(void);

extern uint8 ReadData;
static uint8 WriteData1,WriteData2;
extern const Can_ConfigType Can_Configurations ;

static Can_PduType  PduInfo[]=
{                           {
                             1,     /*SwHandle*/
                             1,     /*Length*/
                             0x5,   /*ID*/
                             &WriteData1
                            },
                            {
                             2,     /*SwHandle*/
                             2,     /*Length*/
                             0x6,   /*ID*/
                             &WriteData2
                            }
};

//static uint8 counter=0;
volatile uint32 SW1=0,SW2=0;
int main(void)
{

    /*Set system clock to 80 MHz*/
    PLL_Init();
    PortF_Init();
    Can_Port_Enable();
    Can_Init(&Can_Configurations) ;
    #if(LOOPBACK==STD_ON)
      CAN0_CTL_R|=0xC0;
      CAN0_TST_R|=0x10;
    #endif
    /*Start Controller 0 */
    Can_SetControllerMode(CONTROLLER0_ID, CAN_CS_STARTED);

    /*Test*/
   Test3_RxTx_Interrupt();
//  Test1_RxTx_Polling();
    return 0;
}


void Can_Port_Enable(void){

    SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R1  ; // port B
    while(!(SYSCTL_PRGPIO_R &SYSCTL_PRGPIO_R1)){};
    SYSCTL_RCGCCAN_R|=SYSCTL_RCGCCAN_R0;
    while(!(SYSCTL_PRCAN_R & SYSCTL_PRCAN_R0)){};
    GPIO_PORTB_LOCK_R|=0x4C4F434B ;
    GPIO_PORTB_CR_R|=0x30 ;
    GPIO_PORTB_DIR_R|=0x20 ;     // output transmit
    GPIO_PORTB_DIR_R&=~0x10 ;    // input receive
    GPIO_PORTB_DEN_R|=0x30 ;
    GPIO_PORTB_AMSEL_R&=~0x30 ;
    GPIO_PORTB_AFSEL_R|=0x30 ;
    GPIO_PORTB_PCTL_R&=~0x00FF0000 ;
    GPIO_PORTB_PCTL_R|=0x00880000 ;
    //NVIC Init
     NVIC_PRI9_R  &=~0XFF000000 ;
     NVIC_PRI9_R  |= 0X20000000 ;  // priority 1
     NVIC_EN1_R|=0x80;      //Enable CAN0 interrupt
}

void PortF_Init(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGCGPIO_R5;                    // 1) F clock
  while(!(SYSCTL_PRGPIO_R &SYSCTL_PRGPIO_R5)){};           // delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0
}

void PLL_Init(void){
  // 0) Use RCC2
  SYSCTL_RCC2_R |=  0x80000000;  // USERCC2
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
                 + 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~0x00002000;
  // 4) set the desired system divider
  SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
                  + (4<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~0x00000800;
}

void Test1_RxTx_Polling(void)
{

    while(1)
    {
        Can_MainFunction_Read() ;
           SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
           SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2

           if(ReadData==2)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
            if(ReadData==4)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
            if(ReadData==8)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
           if(ReadData==0)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }

           if(!SW1 )
           {
              WriteData1 = 0x2 ;
              Can_write(HTH0_0, &PduInfo[0]) ;
           }
            if(!SW2)
           {
               WriteData1 = 0x4 ;
               Can_write(HTH0_0, &PduInfo[0]) ;
           }

           Can_MainFunction_Write() ;

    }
   }

void Test2_TX_2_Objs_RX_2_Objs(void)
{
    while(1)
    {
        Can_MainFunction_Read() ;
           SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
           SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2

           if(ReadData==2)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
            if(ReadData==4)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
            if(ReadData==8)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
           if(ReadData==0)
           {
               GPIO_PORTF_DATA_R &= ~0xF;
               GPIO_PORTF_DATA_R |= ReadData ;
           }
           if(!SW1 )
           {
              WriteData1 = 0x2 ;
              Can_write(HTH0_0, &PduInfo[0]) ;
           }
            if(!SW2)
           {
               WriteData2 = 0x4 ;
               Can_write(HTH0_1, &PduInfo[1]) ;
           }

           if(SW1==0x10 && SW2==0x01)
           {
               WriteData1 = 0x0 ;
               Can_write(HTH0_0, &PduInfo[0]) ;
           }

           Can_MainFunction_Write() ;
    }
}

void Test3_RxTx_Interrupt(void)
{
    irq_Enable();

    while(1)
    {
        SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
        SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2

        if(ReadData==2)
        {
            GPIO_PORTF_DATA_R &= ~0xF;
            GPIO_PORTF_DATA_R |= ReadData ;
        }
         if(ReadData==4)
        {
            GPIO_PORTF_DATA_R &= ~0xF;
            GPIO_PORTF_DATA_R |= ReadData ;
        }
         if(ReadData==8)
        {
            GPIO_PORTF_DATA_R &= ~0xF;
            GPIO_PORTF_DATA_R |= ReadData ;
        }
        if(ReadData==0)
        {
            GPIO_PORTF_DATA_R &= ~0xF;
            GPIO_PORTF_DATA_R |= ReadData ;
        }

        if(!SW1 )
        {
           WriteData1 = 0x2 ;
           Can_write(HTH0_0, &PduInfo[0]) ;
        }
         if(!SW2)
        {
            WriteData1 = 0x4 ;
            Can_write(HTH0_0, &PduInfo[0]) ;
        }


    }
}
