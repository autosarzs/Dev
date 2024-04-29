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
**  FILENAME     : Dio_Lcfg.c                                                 **
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
**  DESCRIPTION  : DIO Driver config source file                              **
**                                                                            **
**  SPECIFICATION(S) : Specification of DIO Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/
#include "Dio.h"
#include "Port_MemMap.h"

/*******************************************************************************/
/*                              Static Configurations                          */
/*******************************************************************************/

/*Array Of Channels Defined By User*/
Dio_ConfiguredChannel channels[DIO_CONFIGURED_CHANNLES] = {
    {CHANNEL_39, PORTA_ID, 1, OUTPUT},
    {CHANNEL_35, PORTE_ID, 3, OUTPUT}
};
