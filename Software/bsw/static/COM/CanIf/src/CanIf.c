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
/*	Headers of Callback Functions	*/
#include "CanTp_Cbk.h"
#include "CanNm_Cbk.h"
#include "CanTSyn_Cbk.h"
#include "Cdd_Cbk.h"
#include "J1939NM_Cbk.h"
#include "J1939TP_Cbk.h"
#include "PduR_Cbk.h"
#include "XCP_Cbk.h"

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

/*Pointer to save configuration parameters set */
static CanIf_ConfigType*    CanIf_ConfigPtr = NULL_PTR;

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
/*    Requirment              : SWS_CANIF_00007                                         */
/*    Function Description    : This service confirms a previously successfully 		*/
/*								processed transmission of a CAN TxPDU                   */
/*    Parameter in            : CanTxPduId					                            */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/*    Reentrancy              : Reentrant Function                                      */
/*                                                                                      */
/****************************************************************************************/
void CanIf_TxConfirmation(PduIdType CanTxPduId)
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
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TXCONFIRMATION_API_ID,CANIF_E_UNINIT);
	}
	else
	{
		/*
		 * [SWS_CANIF_00410] If parameter CanTxPduId of CanIf_TxConfirmation() has an invalid value,
		 * CanIf shall report development error code CANIF_E_PARAM_LPDU to the Det_ReportError service of the DET module,
		 * when CanIf_TxConfirmation() is called.
		 */
		for(uint8 PduId= 0; PduId < CAN_HTH_NUMBER ; PduId++)
		{
			if(CanTxPduId != CanIf_ConfigPtr->CanIfInitCfgObj.CanIfTxPduCfgObj[PduId].CanIfTxPduId\
			&& CAN_HTH_NUMBER-1 == PduId)
			{
				Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TXCONFIRMATION_API_ID,CANIF_E_PARAM_LPDU);
			}
		}
	}
	
#if(CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON && CANIF_TXPDU_READ_NOTIFYSTATUS == STD_ON)
		/*
		 * [SWS_CANIF_00391] If configuration parameters CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API (ECUC_CanIf_00609)
		 * and CANIF_TXPDU_READ_NOTIFYSTATUS (ECUC_CanIf_00589) for the Transmitted L-PDU are set to TRUE,
		 * and if CanIf_TxConfirmation() is called, CanIf shall set the notification status for the Transmitted L-PDU.
		 */
		CanIf_ConfigPtr->CanIfInitCfgObj.CanIfTxPduCfgObj[CanTxPduId].CanIfTxPduReadNotifyStatus = TRUE;
#endif

	/*
	 * [SWS_CANIF_00414] Configuration of CanIf_TxConfirmation():
	 * Each Tx LPDU (see ECUC_CanIf_00248) has to be configured with a corresponding transmit
	 * confirmation service of an upper layer module (see [SWS_CANIF_00011]) which is called in CanIf_TxConfirmation().
	 */
	CanIfTxPduUserTxConfirmationULType PduUser;
	PduUser = CanIf_ConfigPtr->CanIfInitCfgObj.CanIfTxPduCfgObj[CanTxPduId].CanIfTxPduUserTxConfirmationUL;
	if(CAN_NM == PduUser)
	{
		CanNm_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(CAN_TP == PduUser)
	{
		CanTp_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(CAN_TSYN == PduUser)
	{
		CanTSyn_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(CDD == PduUser)
	{
		Cdd_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(J1939NM == PduUser)
	{
		J1939Nm_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(J1939TP == PduUser)
	{
		J1939TP_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(PDUR == PduUser)
	{
		PduR_TxConfirmation(CanTxPduId , E_OK);
	}
	else if(XCP == PduUser)
	{
		XCP_TxConfirmation(CanTxPduId , E_OK);
	}
	else
	{
		/*
		 * [SWS_CANIF_00438] d Configuration of <User_TxConfirmation>(): The upper layer module,
		 * which provides this callback service, has to be configured by CanIfTxPduUserTxConfirmationUL(see ECUC_CanIf_00527).
		 * If no upper layer modules are configured for transmit confirmation using <User_TxConfirmation>(),
		 * no transmit confirmation is executed.
		 */
	}
	
	/* End of Critical Section */
	irq_Enable();
}
