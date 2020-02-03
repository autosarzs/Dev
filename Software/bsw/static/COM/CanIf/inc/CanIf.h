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

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"



/*****************************************************************************************/
/*                                    Macro Definition                                   */
/*****************************************************************************************/
/* CANIF Module Id */
#define CANIF_MODULE_ID    (40U)

/* CANIF Instance Id */
#define CANIF_INSTANCE_ID  (0U)

/* DET Error Codes */
typedef uint8 CanIF_DetErrorType;

#define CANIF_E_PARAM_CONTROLLERID	((CanIF_DetErrorType)015U)
#define CANIF_E_PARAM_CTRLMODE		((CanIF_DetErrorType)021U)
/* CanIF_ServiceId*/
typedef uint8 CanIF_ServiceId;

#define  CANIF_SETCONTROLLERMODE_API_ID	((CanIF_ServiceId)0x03)

Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);


#endif /* __CANIF_H__ */