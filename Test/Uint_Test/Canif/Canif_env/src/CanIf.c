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
#include "CanIf_Types.h"

/*private function IDs*/
#define CANIF_CHECK_DLC_API_ID (0xAA)

//Temp canif config variable.
static CanIf_ModuleStateType CanIf_ModuleState = CANIF_UNINT;
static CanIf_ConfigType*  CanIf_ConfigPtr = &CanIf_ConfigObj;

static Std_ReturnType CanIf_SW_Filter(const Can_HwType *Mailbox, uint32 *CanIfRxPduId_ptr)
{
    // pointer for PBcfg hrh configuration
    CanIfHrhCfgType *Hrhcfg_Ptr = CanIf_ConfigPtr->CanIfInitCfgObj.CanIfInitHohCfgObj->CanIfHrhCfgObj;
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
                    //Configured sw algorithm is Linear
                    for (uint64 PduCfg_index = 0; PduCfg_index < RX_CAN_L_PDU_NUM; PduCfg_index++)
                    {
                        if ((PduCfg_ptr[PduCfg_index].CanIfRxPduHrhIdRef == (&Hrhcfg_Ptr[HrhCfg_index])))
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