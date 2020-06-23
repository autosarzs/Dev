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
**  FILENAME     : CanIf_TxConfirmation.c         			                                  **
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
#include "../inc/CanIf.h"
#include "CanIf_Cbk.h"
#include "Can_Cfg.h"
#include "irq.h"
#include "Det.h"
/*	Headers of Callback Functions	*/
#include "CanTp_Cbk.h"
#include "CanNm_Cbk.h"
#include "CanTSyn_Cbk.h"
#include "Cdd_Cbk.h"
#include "J1939Nm_Cbk.h"
#include "J1939Tp_Cbk.h"
#include "PduR_Cbk.h"
#include "Xcp_Cbk.h"

/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Definition                                    */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
extern PduIdType swPduHandle[];

/*Pointer to save configuration parameters set */
extern const CanIf_ConfigType* CanIf_ConfigPtr;

/* Holding the CanIf module current state. Initially, CANIF_UNINT. */
extern CanIf_ModuleStateType CanIf_ModuleState;

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/

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
		#if(CANIF_DEV_ERROR_DETECT == STD_ON)
			Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TXCONFIRMATION_API_ID,CANIF_E_UNINIT);
		#endif
	}
	else	// if it is initialized and ready
	{
		
		boolean PduIdCheck = TRUE;	// TRUE as initialized for checking if CanTxPduId exists
		/*
		 * [SWS_CANIF_00410] If parameter CanTxPduId of CanIf_TxConfirmation() has an invalid value,
		 * CanIf shall report development error code CANIF_E_PARAM_LPDU to the Det_ReportError service of the DET module,
		 * when CanIf_TxConfirmation() is called.
		 */
		for(uint8 PduId= 0; PduId < CAN_HTH_NUMBER ; PduId++)
		{
			// if(CanTxPduId != CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[PduId].CanIfTxPduId
			if(CanTxPduId != swPduHandle[PduId] && CAN_HTH_NUMBER-1 == PduId)
			{
				PduIdCheck = FALSE ;		// Not found , CanTxPduId does not exist
				#if(CANIF_DEV_ERROR_DETECT == STD_ON)
					Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TXCONFIRMATION_API_ID,CANIF_E_PARAM_LPDU);
				#endif
			}
		}
		
		// if CanTxPduId is found
		if(TRUE == PduIdCheck)
		{
			#if(CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS_API == STD_ON)
				/*
				 * [SWS_CANIF_00391] If configuration parameters CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API (ECUC_CanIf_00609)
				 * and CANIF_TXPDU_READ_NOTIFYSTATUS (ECUC_CanIf_00589) for the Transmitted L-PDU are set to TRUE,
				 * and if CanIf_TxConfirmation() is called, CanIf shall set the notification status for the Transmitted L-PDU.
				 */
				// CANIF_TXPDU_READ_NOTIFYSTATUS is implemented as CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS_API 
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduReadNotifyStatus = TRUE;
			#endif
			
			// for checking if there is an upper layer or not
			boolean UserNotFound = FALSE;
			/*
			 * [SWS_CANIF_00414] Configuration of CanIf_TxConfirmation():
			 * Each Tx LPDU (see ECUC_CanIf_00248) has to be configured with a corresponding transmit
			 * confirmation service of an upper layer module (see [SWS_CANIF_00011]) which is called in CanIf_TxConfirmation().
			 */
			CanIfTxPduUserTxConfirmationULType PduUser;
			PduUser = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationUL;
			if(CAN_NM_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &CanNm_TxConfirmation;
			}
			else if(CAN_TP_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &CanTp_TxConfirmation;
			}
			else if(CAN_TSYN_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &CanTSyn_CanIfTxConfirmation;
			}
			else if(CDD_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &Cdd_CanIfTxConfirmation;
			}
			else if(J1939NM_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &J1939Nm_TxConfirmation;
			}
			else if(J1939TP_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &J1939Tp_TxConfirmation;
			}
			else if(PDUR_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &PduR_CanIfTxConfirmation;
			}
			else if(XCP_TX_CONFIRMATION == PduUser)
			{
				CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName = &Xcp_CanIfTxConfirmation;
			}
			else
			{
				UserNotFound = TRUE;	// There is no Upper layer found
				/*
				 * [SWS_CANIF_00438] Configuration of <User_TxConfirmation>(): The upper layer module,
				 * which provides this callback service, has to be configured by CanIfTxPduUserTxConfirmationUL(see ECUC_CanIf_00527).
				 * If no upper layer modules are configured for transmit confirmation using <User_TxConfirmation>(),
				 * no transmit confirmation is executed.
				 */
			}
			
			// if there is an upper layer found
			if(FALSE == UserNotFound)
			{
				/*
				 * [SWS_CANIF_00542] d Configuration of <User_TxConfirmation>(): The name of the API 
				 * <User_TxConfirmation>() which is called by CanIf shall be configured for CanIf by parameter
				 * CanIfTxPduUserTxConfirmationName (see ECUC_CanIf_00528).
				 */
			    CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[CanTxPduId].CanIfTxPduUserTxConfirmationName(CanTxPduId , E_OK);
			}
		}
	}
	
	/* End of Critical Section */
	irq_Enable();
}