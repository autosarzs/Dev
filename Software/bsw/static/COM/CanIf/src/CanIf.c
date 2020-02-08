/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2020)		                                  **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : CanIf.c         			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-26                                                 **
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
**  DESCRIPTION  : CAN Interface source file                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Interface, AUTOSAR Release 4.3.1  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#include "CanIf.h"
//#include "CanIf_Types.h"
#include "Det.h"

Std_ReturnType CanIf_GetControllerMode(
uint8 ControllerId,
Can_ControllerStateType* ControllerModePtr
)
{
	/* [SWS_CANIF_00313] d If parameter ControllerId of
	CanIf_GetControllerMode() has an invalid, the CanIf shall report development
	error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
	of the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
	if (ControllerId != 0 || ControllerId != 1){
	  	  Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CanIf_GetControllerMode_Id, CANIF_E_PARAM_CONTROLLERID);

	  	  return E_NOT_OK;
	}

	/*[SWS_CANIF_00656] d If parameter ControllerModePtr of
	CanIf_GetControllerMode() has an invalid value, the CanIf shall report development
	error code CANIF_E_PARAM_POINTER to the Det_ReportError service of
	the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
	if(ControllerModePtr == 0){
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CanIf_GetControllerMode_Id, CANIF_E_PARAM_POINTER);

		return E_NOT_OK;
	}

	Can_GetControllerMode(ControllerId, ControllerModePtr);

	return E_OK;
}

