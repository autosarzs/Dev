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

#include "CanIf.h"
#include "Det.h"
#include "MemMap.h"
#include "CanIf_Cbk.h"

/*private function IDs*/
#define CANIF_CHECK_DLC_API_ID (0xAA)


static CanIf_ModuleStateType CanIf_ModuleState;
//Temp canif config variable.
extern CanIf_ConfigType *CanIf_ConfigPtr;

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/
/******************************************************************************/
/*-
 * Brief               	The received Data Length value is compared with the configured
 * 						Data Length value of the received L-PDU.
 * Param-Name[in]      	pPduCfg: Pointer to configured PDU struct.
 * 						pPduInfo: Pointer to recieved L-PDU from lower layer CanDrv.
 * Return              	Std_ReturnType
 *  */
/******************************************************************************/
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
static Std_ReturnType CanIf_CheckDLC(const CanIfRxPduCfgType *const ConfigPdu_Ptr, const PduInfoType *pPduInfo)
{
	Std_ReturnType return_val = E_NOT_OK;

	/*
     * [SWS_CANIF_00026] d CanIf shall accept all received L-PDUs
		(see [SWS_CANIF_00390]) with a Data Length value equal or greater then the
		configured Data Length value (see ECUC_CanIf_00599). c(SRS_Can_01005)
     */
	if (ConfigPdu_Ptr->CanIfRxPduDataLength <= pPduInfo->SduLength)
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
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
		Det_ReportRuntimeError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
						CANIF_E_INVALID_DATA_LENGTH);
#endif
	}

	return return_val;
}
#endif

/******************************************************************************/
/*
* Brief				 	The approach of software filter mechanisms is to find out the corresponding L-PDU from the
						HRH and CanId currently being processed.
 * Param-Name[in]      	Mailbox: Revcieved Pdu from CanDrv.
 * Return              	index of configured recieve pdu
 *  */
/*******************************************************************************/
static Std_ReturnType CanIf_SW_Filter(const Can_HwType *Mailbox, uint64 *tempPtr_PduID)
{
	CanIfRxPduCfgType *PduCfg_ptr = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef;
	//local variable hrh configuration
	CanIfHrhCfgType *HrhCfg_ptr;
	//local variable hrh hardware configuration
	CanHardwareObjectType *Hrh_HWcfg_ptr;
	//local variable CanController hardware configuration
	CanControllerType *CanControlle_HWcfg_ptr;
	// Local variable hold Message ID  ...
	Can_IdType temp_CanId = (Mailbox->CanId) & 0x3FFFFFFF;
	// Local variable hold Message type , Extended , standard ...CanIfHrhIdSymRef->CanObjectId
	CanIfHrhRangeRxPduRangeCanIdTypeType temp_canIdType = (Mailbox->CanId) >> 29U;
	//local to hold the reurn value
	Std_ReturnType ret_val = E_NOT_OK;

	for (uint64 PduCfg_index = 0; PduCfg_index < RX_CAN_L_PDU_NUM; PduCfg_index++)
	{
		HrhCfg_ptr = PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef;
		Hrh_HWcfg_ptr = HrhCfg_ptr->CanIfHrhIdSymRef;
		CanControlle_HWcfg_ptr = Hrh_HWcfg_ptr->CanControllerRef; 
		/*
			[SWS_CANIF_00030] d If the CanId of the received L-PDU in the HRH is configured to be RECEIVED,
			 then CanIf shall accept this L-PDU and the software filtering
			algorithm shall derive the corresponding Receive L-PDU from the found CanId. (SRS_Can_01018)
		*/
		if ((CanControlle_HWcfg_ptr->CanControllerId == Mailbox->ControllerId) &&
			(Hrh_HWcfg_ptr->CanObjectType == RECEIVE) &&
			(Hrh_HWcfg_ptr->CanObjectId == Mailbox->Hoh))
		{
			/*
			// TODO Range
			(PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef->CanIfHrhRangeCfgRef->CanIfHrhRangeRxPduRangeCanIdType == temp_canIdType))
			[SWS_CANIF_00852] d If a range is (partly) contained in another range, or a single
			CanId is contained in a range, the software filter shall select the L-PDU based on the
			following assumptions:
				• A single CanId is always more relevant than a range.
				• A smaller range is more relevant than a larger range.
			*/

			/*
				 [SWS_CANIF_00469]  CanIf shall give the possibility to configure and store a
				 software acceptance filter for each HRH of type BasicCAN configured by parameter
				 CANIF_HRH_SOFTWARE_FILTER (see ECUC_CanIf_00632). c()
			*/
			if (HrhCfg_ptr->CanIfHrhSoftwareFilter == STD_ON)
			{

				/*
				[SWS_CANIF_00877] [SWS_CANIF_00645]  d If CanIf receives a L-PDU (see CanIf_RxIndication()),
				it shall perform the following comparisons to select the correct reception L-SDU configured in CanIfRxPduCfg:
				*/
				if ((PduCfg_ptr[PduCfg_index].CanIfRxPduCanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanIdMask) ==
					(temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanIdMask))
				{
					ret_val = E_OK;
					*tempPtr_PduID = PduCfg_index;
				}
				else
				{
					/*
					[SWS_CANIF_00417] d If parameter Mailbox->CanId of
					CanIf_RxIndication() has an invalid value, CanIf shall report development
					error code CANIF_E_PARAM_CANID to the Det_ReportError service of the DET
					module, when CanIf_RxIndication() is called. c(SRS_BSW_00323)
					*/
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
					Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
									CANIF_E_PARAM_CANID);
#endif
				}
			}
			else
			{
				/* TODO static-PDU NOT implemented yet*/
				
			}
			break;
		}
		else
		{
			if (PduCfg_index == (RX_CAN_L_PDU_NUM - 1))
			{
				/*
				[SWS_CANIF_00416] d If parameter Mailbox->Hoh of CanIf_RxIndication()
				has an invalid value, CanIf shall report development error code
				CANIF_E_PARAM_HOH to the Det_ReportError service of the DET module,
				when CanIf_RxIndication() is called. c(SRS_BSW_00323)
				*/
#if (CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */
				Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
								CANIF_E_PARAM_HOH);
#endif
			}
			else
			{
				/* code */
			}
		}
	}
	return ret_val;
}

#if (CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
static void Canif_CopyData(uint8 *dest, uint8 *Src, uint8 Len)
{
	uint8 counter_index;
	for (counter_index = 0; counter_index < Len; counter_index++)
	{
		dest[counter_index] = Src[counter_index];
	}
}
#endif

/*[SWS_CANIF_00415] Within the service CanIf_RxIndication() the CanIf
	routes this indication to the configured upper layer target service(s). c()
	*/

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{

	static CanIf_PduModeType temp_Mode;
	static uint64 temp_CanIfRxPduindex;
	CanIfRxPduCfgType *PduCfg_ptr;

#if (CANIF_DEV_ERROR_DETECT == STD_ON)

	if ((NULL_PTR == Mailbox) || (NULL_PTR == PduInfoPtr))
	{
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
						CANIF_E_PARAM_POINTER);
	}
	else
	{
#endif
		/*[SWS_CANIF_00421] If CanIf was not initialized before calling
			CanIf_RxIndication(), CanIf shall not execute Rx indication handling, when
			CanIf_RxIndication(), is called.
	
			* The PduMode of a channel defines its transmit or receive activity.
			Communication direction (transmission and/or reception) of the channel can
			be controlled separately or together by upper layers.
		*/
		if ((CanIf_ModuleState == CANIF_READY) && (CanIf_GetPduMode(Mailbox->ControllerId, &temp_Mode) == E_OK))
		{
			// local variable to the Rx pdu config
			PduCfg_ptr = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef;
			//if the current Pdu is (tx & rx) or (rx only) mode
			if (temp_Mode == CANIF_ONLINE || temp_Mode == CANIF_TX_OFFLINE)
			{
				if (CanIf_SW_Filter(Mailbox, &temp_CanIfRxPduindex) == E_OK)
				{
					/* [SWS_CANIF_00390] d If CanIf accepts an L-PDU received via
				    CanIf_RxIndication() during Software Filtering (see [SWS_CANIF_00389]),
					CanIf shall process the Data Length check afterwards, if configured
			    	 */
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
					if (CanIf_CheckDLC(&PduCfg_ptr[temp_CanIfRxPduindex], PduInfoPtr) == E_OK)
					{
#endif

#if (CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
						// Call copy_Data
						/*						
					[SWS_CANIF_00199] d After call of CanIf_RxIndication() and passing of software filtering and Data Length Check, CanIf shall store the received L-SDU in this
					receive L-SDU buffer. During the call of CanIf_ReadRxPduData() the assigned
					receive L-SDU buffer containing a recently received L-SDU, CanIf shall avoid preemptive receive L-SDU buffer access events (refer to [SWS_CANIF_00064]) to that
					receive L-SDU buffer. c()
					*/
#if (CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS_API == STD_ON)
				/*
				[SWS_CANIF_00392] d If configuration parameters
				CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API (ECUC_CanIf_00608) and
				CANIF_RXPDU_READ_NOTIFYSTATUS (ECUC_CanIf_00595) for the Received
				L-PDU are set to TRUE, and if CanIf_RxIndication() is called, the CanIf shall
				set the notification status for the Received L-PDU. c()
				*/
				//Set flag
#endif
#endif
						/*
				[SWS_CANIF_00135] d If a target upper layer module was configured to be called
				with its providing receive indication service (see [SWS_CANIF_00056]), the CanIf shall
				call this configured receive indication callback service (see ECUC_CanIf_00530) and
				shall provide the parameters required for upper layer notification callback functions
				(see [SWS_CANIF_00012]) based on the parameters of CanIf_RxIndication(). c
				(SRS_BSW_00325)

				[SWS_CANIF_00211] d CanIf shall execute the software acceptance filter from [SWS_CANIF_00469] for the HRH passed by callback function
				CanIf_RxIndication(). c()
				*/
						/*TODO "DONE" remove this switch case and use the array to pointer to function  */
						/*TODO "NOT_Exist" search for CANIF_CHECKSUM_RX_CALLOUT_SUPPORT*/
						if (PduCfg_ptr[temp_CanIfRxPduindex].CanIfRxPduUserRxIndicationName != NULL)
						{
							PduCfg_ptr[temp_CanIfRxPduindex].CanIfRxPduUserRxIndicationName(temp_CanIfRxPduindex, PduInfoPtr);
						}
						else
						{
							/*
							If no upper layer (UL) module is configured, no <User_RxIndication> has to be
							called in case of an Rx indication event of the CANRXPDUID from the
							CAN Driver module.
							*/
						}
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
					}
					else
					{
						/* check Length didn't pass */
					}
#endif
				}
				else
				{
					/* Software filter didn't pass */
				}
			}
			else
			{
				/* Canif module not initatlized or get mood not working */
			}
		}
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
	}
#endif
}
