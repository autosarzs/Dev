/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)		                                    **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Stub			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C		                                                  **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam	                                        **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC	                                            **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef __STUB_H__
#define __STUB_H__

typedef struct {
	
}CanTrcvChannelType;

typedef uint32 EcuM_WakeupSourceType;
#define ECUM_WKSOURCE_POWER                 ((EcuM_WakeupSourceType)0x00)
#define ECUM_WKSOURCE_RESET                 ((EcuM_WakeupSourceType)0x01)
#define ECUM_WKSOURCE_INTERNAL_RESET        ((EcuM_WakeupSourceType)0x02)
#define ECUM_WKSOURCE_INTERNAL_WDG          ((EcuM_WakeupSourceType)0x03)
#define ECUM_WKSOURCE_EXTERNAL_WDG          ((EcuM_WakeupSourceType)0x04)

#endif /* STUB_H_ */
