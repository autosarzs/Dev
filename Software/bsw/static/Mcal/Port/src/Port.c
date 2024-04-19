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
**  FILENAME     : Port.c                                                     **
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
**  VENDOR       : AUTOSarZs OL                                               **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : Port Driver source file                                    **
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
#include "SchM_Port.h"

#ifdef DIO_DEV_ERROR_DETECT
#include "Det.h"
#endif

/* Optional */
#include "Port_Cbkh.h"
