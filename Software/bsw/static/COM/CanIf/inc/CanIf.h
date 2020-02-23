/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)		                                  **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : CanIf			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-10-20                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C		                                              **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam	                                      **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC	                                          **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : CAN Interface source file                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Inteface, AUTOSAR Release 4.3.1   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef __CANIF_H__
#define __CANIF_H__


#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_GeneralTypes.h"
#include "Platform_Types.h"
#include "CanIf_Types.h"
typedef uint8 CanIf_PduModeType;
#define CANIF_OFFLINE           ((CanIf_PduModeType)0x00U)
#define CANIF_TX_OFFLINE        ((CanIf_PduModeType)0x01U)
#define CANIF_TX_OFFLINE_ACTIVE ((CanIf_PduModeType)0x02U)
#define CANIF_ONLINE            ((CanIf_PduModeType)0x03U)

#define MAX_PDU_REQUEST  4
#define CANIF_CONTROLLERS_NUM 10
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId,CanIf_PduModeType PduModeRequest);
Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxSduId,PduInfoType* CanIfRxInfoPtr);

#endif /* __CANIF_H__ */
