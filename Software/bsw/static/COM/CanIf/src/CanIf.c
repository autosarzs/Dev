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
#include "Det.h"
#include "MemMap.h"


/*private function IDs*/
#define CANIF_CHECK_DLC_API_ID	(0xAA)

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/
/******************************************************************************/
/*
 * Brief               	The received Data Length value is compared with the configured
 * 						Data Length value of the received L-PDU.
 * Param-Name[in]      	pPduCfg: Pointer to configured PDU struct.
 * 						pPduInfo: Pointer to recieved L-PDU from lower layer CanDrv.
 * Return              	Std_ReturnType
 *  */
/******************************************************************************/
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
static Std_ReturnType CanIfCheckDLC(const CanIfRxPduCfgType * const pPduCfg, const PduInfoType * pPduInfo)
{
	Std_ReturnType return_val = E_OK;
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
	if((NULL_PTR == pPduCfg) || (NULL_PTR == pPduInfo))
	{
		/*Invalid Pointers*/
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_CHECK_DLC_API_ID,
						CANIF_E_PARAM_POINTER);
		return_val = E_NOT_OK;
	}
	else
	{

	}
#endif
	if(pPduCfg->CanIfRxPduDataLength == pPduInfo->SduLength)
	{
		/*Check success*/
		return_val = E_OK;
	}
	else
	{
		/*[SWS_CANIF_00168] d If the Data Length Check rejects a received LPDU
	 	CanIf shall report runtime error code
		CANIF_E_INVALID_DATA_LENGTH to the Det_ReportRuntimeError() service
		of the DET module.*/
			//TODO:
	}
	return return_val;
}
#endif


#if (CANIF_SET_BAUDRATE_API == STD_ON)

Std_ReturnType CanIf_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID )
{
	static uint8 current_ControllerId = -1;
	uint8 return_val;

#if(CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */

	/*  [SWS_CANIF_00869] d If CanIf_SetBaudrate() is called with invalid ControllerId, 
		CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID
		to the Det_ReportError service of the DET module. c(SRS_BSW_00323)*/

	if (ControllerId > USED_CONTROLLERS_NUMBER) {
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_SETBAUDRATE_API_ID,
				CANIF_E_PARAM_CONTROLLERID);
		return_val = E_NOT_OK;
	}

else
#endif

	/*  Reentrant for different ControllerIds. Non reentrant for the same ControllerId. */
	if ( ControllerId == current_ControllerId )
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



void CanIf_RxIndication( const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr )
{
	
}

