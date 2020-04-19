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
#include "CanIf_Cbk.h"

/*private function IDs*/
#define CANIF_CHECK_DLC_API_ID (0xAA)

//Temp canif config variable.
static CanIf_ModuleStateType CanIf_ModuleState = CANIF_UNINT;

//const CanIf_ConfigType *CanIf_ConfigPtr = &CanIf_ConfigObj;

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
<<<<<<< HEAD
static Std_ReturnType CanIf_CheckDLC(const CanIfRxPduCfgType *const ConfigPdu_Ptr, const PduInfoType *pPduInfo)
{
	Std_ReturnType return_val = E_NOT_OK;

	/*
=======
static Std_ReturnType CanIf_CheckDLC(const CanIfRxPduCfgType * const ConfigPdu_Ptr, const PduInfoType *pPduInfo)
{
    Std_ReturnType return_val = E_NOT_OK;

    /*
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6
     * [SWS_CANIF_00026] d CanIf shall accept all received L-PDUs
		(see [SWS_CANIF_00390]) with a Data Length value equal or greater then the
		configured Data Length value (see ECUC_CanIf_00599). c(SRS_Can_01005)
     */
<<<<<<< HEAD
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
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
						CANIF_E_INVALID_DATA_LENGTH);
#endif
	}

	return return_val;
=======
    if (ConfigPdu_Ptr->CanIfRxPduDataLength <= pPduInfo->SduLength)
    {
        /*Check success*/
        return_val = E_OK;
    }

    return return_val;
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6
}
#endif

/******************************************************************************/
/*
<<<<<<< HEAD
 * Brief				 The approach of software filter mechanisms is to find out the corresponding L-PDU from the
						 HRH and CanId currently being processed. After the L-PDU is found.
 * Param-Name[in]      	Mailbox: Revcieved Pdu from CanDrv.
 * Return              	index of configured recieve pdu
 *  */
/*******************************************************************************/

static Std_ReturnType CanIf_SW_Filter(const Can_HwType *Mailbox, uint64 *tempPtr_PduID)
{
	CanIfRxPduCfgType *PduCfg_ptr = CanIf_ConfigObj.CanIfInitCfgRef->CanIfRxPduCfgRef;
	// Local variable hold Message type , Extended , standard ...CanIfHrhIdSymRef->CanObjectId
	CanIfHrhRangeRxPduRangeCanIdTypeType temp_canIdType = (Mailbox->CanId) >> 29U;
	Std_ReturnType ret_val = E_NOT_OK;
	// Local variable hold Message ID  ...
	Can_IdType temp_CanId = (Mailbox->CanId) & 0x3FFFFFFF;

	for (uint64 PduCfg_index = 0; PduCfg_index < RX_CAN_L_PDU_NUM; PduCfg_index++)
	{
		if ((PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef->CanIfHrhIdSymRef->CanObjectId == Mailbox->Hoh) &&
			/*
			 [SWS_CANIF_00030] d If the CanId of the received L-PDU in the HRH is configured to be RECEIVED, then CanIf shall accept this L-PDU and the software filtering
			 algorithm shall derive the corresponding Receive L-PDU from the found CanId. (SRS_Can_01018)
			*/
			(PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef->CanIfHrhIdSymRef->CanObjectType == RECEIVE) &&
			(PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef->CanIfHrhCanCtrlIdRef->CanIfCtrlCanCtrlRef->CanControllerId == Mailbox->ControllerId) &&
			(PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef->CanIfHrhRangeCfgRef->CanIfHrhRangeRxPduRangeCanIdType == temp_canIdType))
		{
			/*
			// TODO Range
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
			if (PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef->CanIfHrhSoftwareFilter == STD_ON)
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
=======
 * Brief				Performs Software filtering on recieved Pdus.
 *						it is recommended to offer several search algorithms like
 *						linear search, table search and/or hash search variants to provide the most optimal
 *						solution for most use cases.
 * Param-Name[in]      	pPduCfg: Pointer to configured PDU struct.
 * 						Mailbox: Revcieved Pdu from CanDrv.
 * Return              	index of configured recieve pdu
 *  */
/******************************************************************************/
static sint64 CanIf_SW_Filter(const Can_HwType *Mailbox, const CanIfHrhCfgType * const Hrhcfg_Ptr)
{
    CanIfRxPduCfgType *PduCfg_ptr = CanIf_ConfigObj.CanIfInitCfgRef->CanIfRxPduCfgRef;
    sint64 ret_val = -1;
    Can_IdType temp_CanId = (Mailbox->CanId) & 0x3FFFFFFF;
    // Local variable hold Message type , Extended , standard ...
#if (CANIF_PRIVATE_SOFTWARE_FILTER_TYPE == LINEAR)
    //Configured sw algorithm is Linear
    for (uint64 PduCfg_index = 0; PduCfg_index < RX_CAN_L_PDU_NUM; PduCfg_index++)
    	{
    		//configured recieve pdu has same reference to hrh
    		if (PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef == Hrhcfg_Ptr)
    		{
    			//check mask
    			if ((temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanId) ==
                   (temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanIdMask))
    			{
    				ret_val = (sint64)PduCfg_index;
    				break;
    			}
    			else
    			{

    			}
    		}
    	}
#endif
    return ret_val;
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6
}

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

<<<<<<< HEAD
/*[SWS_CANIF_00415] Within the service CanIf_RxIndication() the CanIf
=======
/*
	[SWS_CANIF_00415] Within the service CanIf_RxIndication() the CanIf
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6
	routes this indication to the configured upper layer target service(s). c()
	*/

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
<<<<<<< HEAD

	static CanIf_PduModeType temp_Mode;
	static uint64 temp_CanIfRxPduindex;
	CanIfRxPduCfgType *PduCfg_ptr = CanIf_ConfigObj.CanIfInitCfgRef->CanIfRxPduCfgRef;

=======
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6
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
			//if the current Pdu is (tx & rx) or (rx only)
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
<<<<<<< HEAD
=======
    static CanIf_PduModeType temp_Mode;
    static sint64 temp_CanIfRxPduindex = -1;
    static uint32 temp_CanifHrhindex = 0;

	/*[SWS_CANIF_00421] If CanIf was not initialized before calling
		CanIf_RxIndication(), CanIf shall not execute Rx indication handling, when
		CanIf_RxIndication(), is called.
	*/
    /*
     * The PduMode of a channel defines its transmit or receive activity.
		Communication direction (transmission and/or reception) of the channel can
		be controlled separately or together by upper layers.
     */

    if (CanIf_ModuleState == CANIF_READY && CanIf_GetPduMode(Mailbox->ControllerId, &temp_Mode) == E_OK )
    {
    	//if the current Pdu is (tx & rx) or (rx only)
    	if (temp_Mode == CANIF_ONLINE || temp_Mode == CANIF_TX_OFFLINE)
    	{
    			// pointer for PBcfg hrh configuration
    		    CanIfHrhCfgType *Hrhcfg_Ptr = CanIf_ConfigObj.CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef;
    		    // pointer for PBcfg Rx-pdu configuration
    		    CanIfRxPduCfgType *PduCfg_ptr = CanIf_ConfigObj.CanIfInitCfgRef->CanIfRxPduCfgRef;
    		    // Local variable hold Message type , Extended , standard ...
    		    CanIfHrhRangeRxPduRangeCanIdTypeType temp_canIdType = (Mailbox->CanId) >> 29U;
    		    // Local variable hold Can message id
    		    Can_IdType temp_CanId = (Mailbox->CanId) & 0x3FFFFFFF;

    		    // Search for the hrh , which received this message
    		    for (temp_CanifHrhindex = 0; temp_CanifHrhindex < CANIF_HRH_OBj_NUM; temp_CanifHrhindex++)
    		    {
    		        /*
    		        * search for the hrh ID,controller ID == received Hoh,controller ID, type of can msg
    		        * make sure its configured to be receive mode
    		        */
    		        if ((Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhIdSymRef->CanObjectId == Mailbox->Hoh) &&
    		            (Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhIdSymRef->CanObjectType == RECEIVE) &&
    		            (Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhCanCtrlIdRef->CanIfCtrlCanCtrlRef->CanControllerId == Mailbox->ControllerId) &&
						(Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhRangeCfgRef->CanIfHrhRangeRxPduRangeCanIdType == temp_canIdType))
    		        {
    		            /*
    		            * check if the received can id in the range of the hrh
    		            * The type of the received can equal the type configured to recieve in this hrh (extended , standard..)
    		            */
    		            if ((temp_CanId & Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhRangeCfgRef->CanIfHrhRangeBaseId) ==
    		                 (temp_CanId & Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhRangeCfgRef->CanIfHrhRangeMask))
    		            {
    		                /*
    		                * S/w filter is enabled and pdu is basic
    		                */
    		                if ((Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhSoftwareFilter == STD_ON) &&
    		                    (Hrhcfg_Ptr[temp_CanifHrhindex].CanIfHrhIdSymRef->CanHandleType == BASIC))
    		                {
    		                	//perform sw filter and get the index if passed (-1 is invalid)
    		                	temp_CanIfRxPduindex = CanIf_SW_Filter(Mailbox, &Hrhcfg_Ptr[temp_CanifHrhindex]);
    		                	//if recieve pdu exists
    		                	if (temp_CanIfRxPduindex > (sint64)-1)
    		                	{

    		                		 /* [SWS_CANIF_00390] d If CanIf accepts an L-PDU received via
										CanIf_RxIndication() during Software Filtering (see [SWS_CANIF_00389]),
										CanIf shall process the Data Length check afterwards, if configured
										(see ECUC_CanIf_00617). c()
    		                		 */
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
    		                		if (CanIf_CheckDLC(&PduCfg_ptr[temp_CanIfRxPduindex], PduInfoPtr) == E_NOT_OK)
    		                		{
    		                	        /*[SWS_CANIF_00168] d If the Data Length Check rejects a received LPDU
    		                		 	CanIf shall report runtime error code
    		                			CANIF_E_INVALID_DATA_LENGTH to the Det_ReportRuntimeError() service
    		                			of the DET module.*/
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    		                	        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
    		                	                        CANIF_E_INVALID_DATA_LENGTH);
#endif
    		                		}
    		                		else
    		                		{
    		                			//misra
    		                		}
#endif
    		                	}
    		                	//Software filter failed
    		                	else
    		                	{
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    		                	        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
														CANIF_E_PARAM_CANID);
#endif
    		                	}
    		                }
    		                //not basic or sw filter is disabled
    		                else
    		                {
    		                	//search for the configured pdu
    		                	for (uint64 PduCfg_index = 0; PduCfg_index < RX_CAN_L_PDU_NUM; PduCfg_index++)
    		                	    {
    		                	    	//configured recieve pdu has same reference to hrh
    		                	    	if (PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef == Hrhcfg_Ptr)
    		                	    	{
    		                	    		//check mask
    		                	    		if ((temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanId) ==
    		                	                   (temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanIdMask))
    		                	    		{
    		                	    			temp_CanIfRxPduindex = (sint64)PduCfg_index;
    		                	   				break;
    		                	   			}
    		                	   			else
    		                	   			{
    		                	   				//misra
    		                	    		}
    		                	    	}
    		                	    }
    		                	//if pdu is not found
    		                	if(temp_CanIfRxPduindex == (sint64)-1)
    		                	{
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    		                	        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
														CANIF_E_PARAM_CANID);
#endif
    		                	}
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6

#if (CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
						// Call copy_Data
						/*						
					[SWS_CANIF_00199] d After call of CanIf_RxIndication() and passing of software filtering and Data Length Check, CanIf shall store the received L-SDU in this
					receive L-SDU buffer. During the call of CanIf_ReadRxPduData() the assigned
					receive L-SDU buffer containing a recently received L-SDU, CanIf shall avoid preemptive receive L-SDU buffer access events (refer to [SWS_CANIF_00064]) to that
					receive L-SDU buffer. c()
					*/
						//Set flag
#endif

<<<<<<< HEAD
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
						switch (PduCfg_ptr[temp_CanIfRxPduindex].CanIfRxPduUserRxIndicationUL)
						{
						case CAN_NM_RX_INDICATION:
							CanNm_RxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case CAN_TP_RX_INDICATION:
							CanTp_RxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case CAN_TSYN_RX_INDICATION:
							CanTSyn_CanIfRxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case CDD_RX_INDICATION:
							CanIfRxPduUserRxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case J1939NM_RX_INDICATION:
							J1939Nm_RxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case J1939TP_RX_INDICATION:
							J1939Tp_RxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case PDUR_RX_INDICATION:
							PduR_CanIfRxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						case XCP_RX_INDICATION:
							Xcp_CanIfRxIndication(temp_CanIfRxPduindex, PduInfoPtr);
							break;

						default:
							PduCfg_ptr[temp_CanIfRxPduindex].CanIfRxPduUserRxIndicationName(temp_CanIfRxPduindex, PduInfoPtr);
							break;
						}
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
					}
					else
					{
						//misra
					}
#endif
				}
				else
				{
					/* code */
				}
			}
			else
			{
				/* code */
			}
		}
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
	}
#endif
}
=======
    		                	/*
    		                	 * [SWS_CANIF_00135] d If a target upper layer module was configured to be called
									with its providing receive indication service (see [SWS_CANIF_00056]), the CanIf shall
									call this configured receive indication callback service (see ECUC_CanIf_00530) and
									shall provide the parameters required for upper layer notification callback functions
									(see [SWS_CANIF_00012]) based on the parameters of CanIf_RxIndication(). c
									(SRS_BSW_00325)
								*/
    	                        switch (PduCfg_ptr[temp_CanIfRxPduindex].CanIfRxPduUserRxIndicationUL)
    	                        {
    	                        case CAN_NM_RX_INDICATION:
    	                        	CanNm_RxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case CAN_TP_RX_INDICATION:
    	                        	CanTp_RxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case CAN_TSYN_RX_INDICATION:
    	                        	CanTSyn_CanIfRxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case CDD_RX_INDICATION:
    	                        	CanIfRxPduUserRxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case J1939NM_RX_INDICATION:
    	                        	J1939Nm_RxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case J1939TP_RX_INDICATION:
    	                        	J1939Tp_RxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case PDUR_RX_INDICATION:
    	                        	PduR_CanIfRxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        case XCP_RX_INDICATION:
    	                        	Xcp_CanIfRxIndication(Mailbox->CanId, PduInfoPtr);
    	                            break;

    	                        default:
    	                            break;
    	                        }
    		                }
    		            }
    		            else
    		            {
    		                /*[SWS_CANIF_00416] d If parameter Mailbox->Hoh of CanIf_RxIndication()
							has an invalid value, CanIf shall report development error code
							CANIF_E_PARAM_HOH to the Det_ReportError service of the DET module,
						when CanIf_RxIndication() is called. c(SRS_BSW_00323)
    		                */
#if (CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */
    		                Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
											CANIF_E_PARAM_HOH);
#endif
    		            }

                    }
                    else
                    {
                        //misra
                    }
                }
    		    //if no HRH is found
    		    if(temp_CanifHrhindex == 0)
    		    {
#if (CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */
    		                Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
											CANIF_E_PARAM_HOH);
#endif
    		    }

            }
    	else
    	{
    		/*[SWS_CANIF_00421] d If CanIf was not initialized before calling
    		CanIf_RxIndication(), CanIf shall not execute Rx indication handling, when
    		CanIf_RxIndication(), is called. c()*/
    	}
    }
}
>>>>>>> 3ba795987bbe5623d8ff09eff6e274ff654f03f6
