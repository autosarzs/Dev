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


#include"CanIf.h"
#include"CanIf_Cbk.h"
#include"Det.h"
#include"Dem.h"
#include"MemMap.h"


/********************************************************************************************/
/* Service Name     : CanIf_SetControllerMode                                               */
/* Syntax           : Std_ReturnType CanIf_SetControllerMode                                */
/*                    (uint8 ControllerId, Can_ControllerStateType ControllerMode)          */
/* Service ID[hex]  : 0x03                                                                  */
/* Sync/Async       : Asynchronous                                                          */
/* Reentrancy       : Reentrant (Not for the same controller)                               */
/* Parameters (in)  : ControllerId: Abstracted CanIf ControllerId which is assigned to a 	*/
/*					  CAN controller, which is requested for mode transition.      			*/
/*                    ControllerMode: Requested mode transition 					      	*/
/* Parameters(inout): None                                                                  */
/* Parameters (out) : None                                                                  */
/* Return Value     : Std_ReturnType E_OK    : Controller mode request has been accepted    */
/* E_NOT_OK         : Controller mode request has not been accepted         	           	*/
/* DESCRIPTION      : This service calls the corresponding CAN Driver service for       	*/
/* changing ofthe CAN controller mode.                                                    	*/
/********************************************************************************************/
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
	Std_ReturnType u8CanIFSetControllerModeRet = E_NOT_OK;
	uint8 u8DrvControllerID = 0;
	/**********************************************************************************************************************/
	/*[SWS_CANIF_00311] If parameter ControllerId of CanIf_SetControllerMode() has an invalid value, the CanIf
	/* 	shall report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module,
	/*	when CanIf_SetControllerMode() is called.
	/**********************************************************************************************************************/
	#if(CANIF_DEV_ERROR_DETECT == STD_ON)
		if(ControllerId > CAN_CONTROLLERID_COUNT)
		{
			Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_SETCONTROLLERMODE_API_ID, CANIF_E_PARAM_CONTROLLERID);
		}
		else
		{

		}
	#endif
	/**********************************************************************************************************************/
	/*[SWS_CANIF_00774] If parameter ControllerMode of CanIf_SetControllerMode() has an invalid value (not CAN_CS_STARTED,
	/*	CAN_CS_SLEEP or CAN_CS_STOPPED), the CanIfshall report development error code CANIF_E_PARAM_CTRLMODE 
	/*	to the Det_ReportError service of the DET module, when CanIf_SetControllerMode() is called.
	/**********************************************************************************************************************/
	#if(CANIF_DEV_ERROR_DETECT == STD_ON)
		if(ControllerMode != CAN_CS_STARTED && ControllerMode != CAN_CS_SLEEP && ControllerMode != CAN_CS_STOPPED)
		{
			Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_SETCONTROLLERMODE_API_ID, CANIF_E_PARAM_CTRLMODE);

		}
		else
		{

		}
	#endif
		u8DrvControllerID = CanIfCtrlCanCtrlRef[ControllerId];
		u8CanIFSetControllerModeRet = Can_SetControllerMode( u8DrvControllerID, ControllerMode );
		/*2. Hint: As optimisation to avoid frequent requests to CanDrv for internal
			use, the last state indicated by CanIf_ControllerModeIndication() and
			Can_GetControllerMode() could be stored per controller.*/
	return u8CanIFSetControllerModeRet;
	
}