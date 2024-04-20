/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)                                        **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Port_MemMap.h                                              **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-04-17                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C                                                     **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam                                          **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC                                              **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : Port Memory Mapping for Tiva C                             **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.3.1    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef PORT_MEM_MAP_H_
#define PORT_MEM_MAP_H_

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

#include "hw_memmap.h"
#include "hw_sysctl.h"
#include "Std_Types.h"

/*******************************************************************************/
/*                              Macro Definition                               */
/*******************************************************************************/

#define __I volatile const /*!< Defines 'read only' permissions                 */
#define __O volatile       /*!< Defines 'write only' permissions                */
#define __IO volatile      /*!< Defines 'read / write' permissions              */

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

typedef struct
{ /*port Structure*/
  __I uint32 RESERVED0[255];
  __IO uint32 DATA;  /*port Data*/
  __IO uint32 DIR;   /*port Direction*/
  __IO uint32 IS;    /*port Interrupt Sense*/
  __IO uint32 IBE;   /*port Interrupt Both Edges*/
  __IO uint32 IEV;   /*port Interrupt Event*/
  __IO uint32 IM;    /*port Interrupt Mask*/
  __IO uint32 RIS;   /*port Raw Interrupt Status*/
  __IO uint32 MIS;   /*port Masked Interrupt Status*/
  __O uint32 ICR;    /*port Interrupt Clear*/
  __IO uint32 AFSEL; /*port Alternate Function Select*/
  __I uint32 RESERVED1[55];
  __IO uint32 DR2R;   /*port 2-mA Drive Select*/
  __IO uint32 DR4R;   /*port 4-mA Drive Select*/
  __IO uint32 DR8R;   /*port 8-mA Drive Select*/
  __IO uint32 ODR;    /*port Open Drain Select*/
  __IO uint32 PUR;    /*port Pull-Up Select*/
  __IO uint32 PDR;    /*port Pull-Down Select*/
  __IO uint32 SLR;    /*port Slew Rate Control Select*/
  __IO uint32 DEN;    /*port Digital Enable*/
  __IO uint32 LOCK;   /*port Lock*/
  __I uint32 CR;      /*port Commit*/
  __IO uint32 AMSEL;  /*port Analog Mode Select*/
  __IO uint32 PCTL;   /*port Port Control*/
  __IO uint32 ADCCTL; /*port ADC Control*/
  __IO uint32 DMACTL; /*port DMA Control*/
} Port_Type;

/*Base Addresses of Ports*/
#define PORTA ((Port_Type *)GPIO_PORTA_BASE)
#define PORTB ((Port_Type *)GPIO_PORTB_BASE)
#define PORTC ((Port_Type *)GPIO_PORTC_BASE)
#define PORTD ((Port_Type *)GPIO_PORTD_BASE)
#define PORTE ((Port_Type *)GPIO_PORTE_BASE)
#define PORTF ((Port_Type *)GPIO_PORTF_BASE)

/* RCC Registers */
#define SYSCTL_REGCGC2_REG (*((volatile uint32 *)SYSCTL_RCGC2))

#endif /* PORT_MEM_MAP_H_ */
