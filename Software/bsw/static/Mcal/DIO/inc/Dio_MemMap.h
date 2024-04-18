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
**  FILENAME     : Dio_MemMap.h                                               **
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
**  DESCRIPTION  : DIO Memory Mapping for Tiva C                              **
**                                                                            **
**  SPECIFICATION(S) : Specification of DIO Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DIO_MEM_MAP_H_
#define DIO_MEM_MAP_H_

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

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
{ /*DIO Structure*/
  __I uint32 RESERVED0[255];
  __IO uint32 DATA;  /*DIO Data*/
  __IO uint32 DIR;   /*DIO Direction*/
  __IO uint32 IS;    /*DIO Interrupt Sense*/
  __IO uint32 IBE;   /*DIO Interrupt Both Edges*/
  __IO uint32 IEV;   /*DIO Interrupt Event*/
  __IO uint32 IM;    /*DIO Interrupt Mask*/
  __IO uint32 RIS;   /*DIO Raw Interrupt Status*/
  __IO uint32 MIS;   /*DIO Masked Interrupt Status*/
  __O uint32 ICR;    /*DIO Interrupt Clear*/
  __IO uint32 AFSEL; /*DIO Alternate Function Select*/
  __I uint32 RESERVED1[55];
  __IO uint32 DR2R;   /*DIO 2-mA Drive Select*/
  __IO uint32 DR4R;   /*DIO 4-mA Drive Select*/
  __IO uint32 DR8R;   /*DIO 8-mA Drive Select*/
  __IO uint32 ODR;    /*DIO Open Drain Select*/
  __IO uint32 PUR;    /*DIO Pull-Up Select*/
  __IO uint32 PDR;    /*DIO Pull-Down Select*/
  __IO uint32 SLR;    /*DIO Slew Rate Control Select*/
  __IO uint32 DEN;    /*DIO Digital Enable*/
  __IO uint32 LOCK;   /*DIO Lock*/
  __I uint32 CR;      /*DIO Commit*/
  __IO uint32 AMSEL;  /*DIO Analog Mode Select*/
  __IO uint32 PCTL;   /*DIO Port Control*/
  __IO uint32 ADCCTL; /*DIO ADC Control*/
  __IO uint32 DMACTL; /*DIO DMA Control*/
} Dio_Type;

/*Base Addresses of Ports*/
#define PORTA ((Dio_Type *)0x40004000)
#define PORTB ((Dio_Type *)0x40005000)
#define PORTC ((Dio_Type *)0x40006000)
#define PORTD ((Dio_Type *)0x40007000)
#define PORTE ((Dio_Type *)0x40024000)
#define PORTF ((Dio_Type *)0x40025000)


#endif /* DIO_MEM_MAP_H_ */
