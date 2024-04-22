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
**  FILENAME     : Port_PBcfg.c                                               **
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
**  DESCRIPTION  : Port Driver config source file                             **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.3.1    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

#include "Port.h"
#include "Port_MemMap.h"

/* Optional */
#include "Port_Cbkh.h"

/* PB structure used with Port_Init API */
const Port_ConfigType Port_PinConfig =
    {{{PORTA_ID, PA0, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA1, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA2, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA3, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA4, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA5, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA6, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTA_ID, PA7, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB0, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB1, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB2, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB3, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB4, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB5, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB6, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTB_ID, PB7, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC0, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_OFF, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC1, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC2, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC3, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_OFF, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC4, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC5, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC6, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTC_ID, PC7, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD0, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD1, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD2, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD3, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD4, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD5, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD6, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTD_ID, PD7, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_ON, STD_ON, STD_ON},
      {PORTE_ID, PE0, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTE_ID, PE1, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTE_ID, PE2, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTE_ID, PE3, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTE_ID, PE4, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTE_ID, PE5, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTF_ID, PF0, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_ON, STD_ON, STD_ON},
      {PORTF_ID, PF1, PORT_PIN_OUT, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTF_ID, PF2, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTF_ID, PF3, PORT_PIN_IN, OFF, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON},
      {PORTF_ID, PF4, PORT_PIN_IN, PULL_UP, PORT_PIN_LEVEL_LOW, PORT_PIN_MODE_DIO, STD_ON, STD_OFF, STD_ON, STD_ON}}};