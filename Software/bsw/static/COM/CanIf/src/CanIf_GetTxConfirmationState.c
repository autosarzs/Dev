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
**  FILENAME     : CanIf_GetTxConfirmationState.c         			                                  **
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
/*****************************************************************************************/
/*                                   Include Common headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Other  headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Component headres                           */
/*****************************************************************************************/
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "Can_Cfg.h"
#include "irq.h"
#include "Det.h"
/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/


/*****************************************************************************************/
/*                                   Local Definition                                    */
/*****************************************************************************************/
/*    Description        :
 */

/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/

typedef struct {
    uint8 transmit_confirmed;
}controllerDataType;

static controllerDataType controllerData[CANIF_CTRL_ID];

/* Holding the CanIf module current state. Initially, CANIF_UNINT. */
static CanIf_ModuleStateType CanIf_ModuleState = CANIF_UNINT;

/*****************************************************************************************/
/*                                   Local Function Declaration                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/

/****************************************************************************************/
/*                                   Global Function Definition                         */
/****************************************************************************************/

/****************************************************************************************/
/*    Requirment              : SWS_CANIF_00734                                         */
/*    Function Description    : This service reports, if any TX confirmation has been   */
/*                              done for the whole CAN controller since the last CAN    */
/*								controller start                                        */
/*    Parameter in            : ControllerId					                        */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : CanIf_NotifStatusType                                   */
/*    Reentrancy              : Reentrant Function                                      */
/*                                                                                      */
/****************************************************************************************/

CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 ControllerId)
{
	/* Critical Section to protect shared resources in a reentrant Function */
	irq_Disable();
	
	/*
	 * [SWS_CANIF_00412] If CanIf was not initialized before calling CanIf_TxConfirmation(),
	 * CanIf shall not call the service <User_TxConfirmation>() and shall not set the Tx confirmation status,
	 * when CanIf_TxConfirmation() is called
	 */
	if(CanIf_ModuleState != CANIF_READY)
	{
		#if(CANIF_DEV_ERROR_DETECT == STD_ON)
			Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TXCONFIRMATION_API_ID,CANIF_E_UNINIT);
		#endif
	}
	else	// if it is initialized and ready
	{
		
		/*
		 *	[SWS_CANIF_00736] If parameter ControllerId of
		 *	CanIf_GetTxConfirmationState() has an invalid value, the CanIf
		 *	shall report development error code CANIF_E_PARAM_CONTROLLERID
		 *	to the Det_ReportError service of the DET module, when
		 *	CanIf_GetTxConfirmationState() is called.
		 */
		CanIf_NotifStatusType notify = CANIF_NO_NOTIFICATION ;
		if(ControllerId <= CANIF_CTRL_ID)
		{
			 notify = controllerData[ControllerId].transmit_confirmed;/* this value is modified by another func*/
		}
		else
		{
			#if(CANIF_DEV_ERROR_DETECT == STD_ON)
				Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_GET_TX_CONFIRMATIONSTATE_ID, CANIF_E_PARAM_CONTROLLERID);
			#endif
		}
	}
	
	/* End of Critical Section */
	irq_Enable();
	
    return notify;
}
