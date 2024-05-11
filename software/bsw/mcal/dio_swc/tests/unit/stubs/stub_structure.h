#include "stdint.h"
#include "Port.h"


typedef struct
{ /*port Structure*/
 int32_t RESERVED0[255];
 uint32_t DATA;  /*port Data*/
 uint32_t DIR;   /*port Direction*/
 uint32_t IS;    /*port Interrupt Sense*/
 uint32_t IBE;   /*port Interrupt Both Edges*/
 uint32_t IEV;   /*port Interrupt Event*/
 uint32_t IM;    /*port Interrupt Mask*/
 uint32_t RIS;   /*port Raw Interrupt Status*/
 uint32_t MIS;   /*port Masked Interrupt Status*/
 int32_t ICR;    /*port Interrupt Clear*/
 uint32_t AFSEL; /*port Alternate Function Select*/
 int32_t RESERVED1[55];
 uint32_t DR2R;   /*port 2-mA Drive Select*/
 uint32_t DR4R;   /*port 4-mA Drive Select*/
 uint32_t DR8R;   /*port 8-mA Drive Select*/
 uint32_t ODR;    /*port Open Drain Select*/
 uint32_t PUR;    /*port Pull-Up Select*/
 uint32_t PDR;    /*port Pull-Down Select*/
 uint32_t SLR;    /*port Slew Rate Control Select*/
 uint32_t DEN;    /*port Digital Enable*/
 uint32_t LOCK;   /*port Lock*/
 int32_t CR;      /*port Commit*/
 uint32_t AMSEL;  /*port Analog Mode Select*/
 uint32_t PCTL;   /*port Port Control*/
 uint32_t ADCCTL; /*port ADC Control*/
 uint32_t DMACTL; /*port DMA Control*/
} Port_Type;

uint32_t PORTA_VAR = 0 ;
uint32_t PORTB_VAR = 0 ;
uint32_t PORTC_VAR = 0 ;
uint32_t PORTD_VAR = 0 ;
uint32_t PORTE_VAR = 0 ;
uint32_t PORTF_VAR = 0 ;

#define PORTA &PORTA_VAR
#define PORTB &PORTB_VAR
#define PORTC &PORTC_VAR
#define PORTD &PORTD_VAR
#define PORTE &PORTE_VAR
#define PORTF &PORTF_VAR


/* Define the base addresses of the ports */
Port_Type *portBaseAddresses[] = {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF};
