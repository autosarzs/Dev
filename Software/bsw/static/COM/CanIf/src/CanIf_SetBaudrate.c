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
**  FILENAME     : CanIf.c         			                                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-26                                                 **
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
**  SPECIFICATION(S) : Specification of CAN Interface, AUTOSAR Release 4.3.1  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#include "../inc/CanIf.h"
#include "Det.h"
#include "MemMap.h"
#include "CanIf_Cbk.h"


#if (CANIF_SET_BAUDRATE_API == STD_ON)
Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID)
{
	static uint8 current_ControllerId = -1;
	uint8 return_val;

#if (CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */

	/*  [SWS_CANIF_00869] d If CanIf_SetBaudrate() is called with invalid ControllerId, 
		CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID
		to the Det_ReportError service of the DET module. c(SRS_BSW_00323)*/

	if (ControllerId > USED_CONTROLLERS_NUMBER)
	{
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_SETBAUDRATE_API_ID,
						CANIF_E_PARAM_CONTROLLERID);
		return_val = E_NOT_OK;
	}
	else
	{
	}
#endif
	/*  Reentrant for different ControllerIds. Non reentrant for the same ControllerId.
	*/
	if (ControllerId == current_ControllerId)
	{
		/* E_NOT_OK: Service request not accepted */
		return_val = E_NOT_OK;
	}
	else
	{
		current_ControllerId = ControllerId;

		Can_SetBaudrate(ControllerId, BaudRateConfigID);
		/* E_OK: Service request accepted, setting of (new) baud rate started */
		return_val = E_OK;
	}
	return return_val;
}
#endif

