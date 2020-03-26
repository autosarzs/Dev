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
static const CanIf_ConfigType *CanIf_ConfigPtr = &CanIf_ConfigObj[0];

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
static Std_ReturnType CanIf_CheckDLC(const PduInfoType *pPduInfo)
{
    Std_ReturnType return_val = E_OK;
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
    if (CanIf_ConfigPtr->CanIfRxPduDataLength == pPduInfo->SduLength)
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
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_CHECK_DLC_API_ID,
                        CANIF_E_INVALID_DATA_LENGTH);
    }
#endif
#endif
    return return_val;
}

/******************************************************************************/
/*
 * Brief				Performs Software filtering on recieved Pdus.
 *						it is recommended to offer several search algorithms like
 *						linear search, table search and/or hash search variants to provide the most optimal
 *						solution for most use cases.
 * Param-Name[in]      	pPduCfg: Pointer to configured PDU struct.
 * 						Mailbox: Revcieved Pdu from CanDrv.
 * Return              	Std_ReturnType
 *  */
/******************************************************************************/
static Std_ReturnType CanIf_SW_Filter(const Can_HwType *Mailbox, uint32 *CanIfRxPduId_ptr)
{
    // pointer for PBcfg hrh configuration
    CanIfHrhCfgType *Hrhcfg_Ptr = CanIf_ConfigPtr->CanIfInitCfgObj->CanIfInitHohCfgObj->CanIfHrhCfgObj;
    // pointer for PBcfg Rx-pdu configuration
    CanIfRxPduCfgType *PduCfg_ptr = CanIf_ConfigPtr->CanIfInitCfgObj.CanIfRxPduCfgObj;
    // Local variable hold Message type , Extendedd , standard ...
    CanIfHrhRangeRxPduRangeCanIdTypeType temp_canIdType = (Mailbox->CanId) >> 29U;
    // Local variable hold Can message id
    Can_IdType temp_CanId = (Mailbox->CanId) & 0x3FFFFFFF;
    Std_ReturnType ret_val = E_NOT_OK;

    // Loop to find the right hrh , which received this message
    for (uint8 HrhCfg_index = 0; HrhCfg_index < HRH_OBj_NUM; HrhCfg_index++)
    {
        /*
        * search for the hrh ID,controller ID == received Hoh,controller ID  
        * make sure its configured to be receive mood
        */
        if ((Hrhcfg_Ptr[HrhCfg_index].CanIfHrhIdSymRef->CanObjectId == Mailbox->Hoh) &&
            (Hrhcfg_Ptr[HrhCfg_index].CanIfHrhIdSymRef->CanObjectType == RECEIVE) &&
            (Hrhcfg_Ptr[HrhCfg_index].CanIfHrhCanCtrlIdRef->CanIfCtrlId == Mailbox->ControllerId))
        {
            /*
            * check if the received can id in the range of the hrh 
            * The type of the received can equal the type configured to recieve in this hrh 
            */
            if (((temp_CanId & Hrhcfg_Ptr[HrhCfg_index].CanIfHrhRangeCfgObj->CanIfHrhRangeBaseId) ==
                 (temp_CanId & Hrhcfg_Ptr[HrhCfg_index].CanIfHrhRangeCfgObj->CanIfHrhRangeMask)) &&
                (Hrhcfg_Ptr[HrhCfg_index].CanIfHrhRangeCfgObj->CanIfHrhRangeRxPduRangeCanIdType == temp_canIdType))
            {
                /*
                * check if the received can id in the range of the hrh 
                * The type of the received can equal the type configured to recieve in this hrh 
                */
                if ((Hrhcfg_Ptr[HrhCfg_index].CanIfHrhSoftwareFilter == STD_ON) &&
                    (Hrhcfg_Ptr[HrhCfg_index].CanIfHrhIdSymRef->CanHandleType == BASIC))
                {
#if (CanIfPrivateSoftwareFilterValue == LINEAR)
                    //Configured sw algorithm is Linear
                    for (uint64 PduCfg_index = 0; PduCfg_index < RX_CAN_L_PDU_NUM; PduCfg_index++)
                    {
                        if ((PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef == (&Hrhcfg_Ptr[HrhCfg_index]))
                        {
                            if ((temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanId) ==
                                (temp_CanId & PduCfg_ptr[PduCfg_index].CanIfRxPduCanIdMask))
                            {
                                *CanIfRxPduId_ptr = PduCfg_ptr[PduCfg_index].CanIfRxPduId;
                                ret_val = E_OK;
                                break;
                            }
                        }
                    }
#elif (CanIfPrivateSoftwareFilterValue == INDEX)
                    //Configured sw algorithm is Linear

#elif (CanIfPrivateSoftwareFilterValue == TABLE)
                    //Configured sw algorithm is Table

#else(CanIfPrivateSoftwareFilterValue == BINARY)
                    //Configured sw algorithm is binary

#endif
                }
                else
                {
                    /* Filter disabled
                *  Full can
                * Direct map 
                * 
                *temp_CanId >> pduid
                */
                    break;
                }
            }
            else
            {
                /*[SWS_CANIF_00417] d If parameter Mailbox->CanId of
                    CanIf_RxIndication() has an invalid value, CanIf shall report development
                    error code CANIF_E_PARAM_CANID to the Det_ReportError service of the DET
                    module, when CanIf_RxIndication() is called.
                */
#if (CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */
                Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
                                CANIF_E_PARAM_CANID);
#endif
                break;
            }
        }
        else
        {
            // can't find hoh
        }
    }
    return ret_val;
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

/*
	[SWS_CANIF_00415] d Within the service CanIf_RxIndication() the CanIf
	routes this indication to the configured upper layer target service(s). c()
	*/
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
    static CanIf_PduModeType temp_Mode;
    static uint32 temp_CanIfRxPduId;

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /*[SWS_CANIF_00416] d If parameter Mailbox->Hoh of CanIf_RxIndication()
	has an invalid value, CanIf shall report development error code
	CANIF_E_PARAM_HOH to the Det_ReportError service of the DET module,
	when CanIf_RxIndication() is called.*/
    if (Mailbox->Hoh > HRH_OBj_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
                        CANIF_E_PARAM_HOH);
    }
    else
    {
    }

    /*SWS_CANIF_00419] d If parameter PduInfoPtr or Mailbox of
	CanIf_RxIndication() has an invalid value, CanIf shall report development
	error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET
	module, when CanIf_RxIndication() is called.
	*/

    if ((NULL_PTR == Mailbox) || (NULL_PTR == PduInfoPtr))
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
                        CANIF_E_PARAM_POINTER);
    }
    else
    {
    }
#endif
    /*
	[SWS_CANIF_00421] If CanIf was not initialized before calling
	CanIf_RxIndication(), CanIf shall not execute Rx indication handling, when
	CanIf_RxIndication(), is called.
	 */

    if (CanIf_ModuleState == CANIF_READY)
    {
        if (CanIf_GetPduMode(Mailbox->ControllerId, &temp_Mode) == E_OK)
        {
            if (temp_Mode == CANIF_ONLINE)
            {
                if (CanIf_SW_Filter(Mailbox, &temp_CanIfRxPduId) == E_OK)
                {
                    if (CanIf_CheckDLC(PduInfoPtr) == E_OK)
                    {
#if (CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
                        // Call copy_Data
                        //Set flag
#endif
                        // call user
                        switch (Temp_CanIfRxPduConfigPtr->CanIfRxPduUserRxIndicationUL)
                        {
                        case CAN_NM_RX_INDICATION:
                            /* code */
                            break;

                        case CAN_TP_RX_INDICATION:
                            /* code */
                            break;

                        case CAN_TSYN_RX_INDICATION:
                            /* code */
                            break;

                        case CDD_RX_INDICATION:
                            /* code */
                            break;

                        case J1939NM_RX_INDICATION:
                            /* code */
                            break;

                        case J1939TP_RX_INDICATION:
                            /* code */
                            break;

                        case PDUR_RX_INDICATION:
                            /* code */
                            break;

                        case XCP_RX_INDICATION:
                            /* code */
                            break;

                        default:
                            break;
                        }
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
    else
    {
        /* code */
    }
}
