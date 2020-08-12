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
#include "Internal.h"



/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/


/****************************************************************************/
//    Function Name           : CanIf_SW_Filter
//    Function Description    : To Check software filter for a basic HRH
//    Parameter in            : HrhId , CanId
//    Parameter inout         : none
//    Parameter out           : none
//    Return value            : Std_ReturnType
/****************************************************************************/
static Std_ReturnType CanIf_SW_Filter(Can_HwHandleType HrhId,Can_IdType CanId)
{
    Std_ReturnType ret_val = E_NOT_OK ;
    uint32 UpperRange = 0;
    uint32 LowerRange = 0;
    uint32 BaseId = 0 ;
    uint32 MaskId = 0 ;

    UpperRange  = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhRangeCfgRef->CanIfHrhRangeRxPduUpperCanId;
    LowerRange  = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhRangeCfgRef->CanIfHrhRangeRxPduLowerCanId;
    BaseId      = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhRangeCfgRef->CanIfHrhRangeBaseId ;
    MaskId      = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhRangeCfgRef->CanIfHrhRangeMask ;

    /*[SWS_CANIF_00389] d If the function CanIf_RxIndication() is called, the CanIf
      shall process the Software Filtering on the received L-PDU as specified in 7.20, if
      configured (see multiplicity of ECUC_CanIf_00628 equals 0::*) If Software Filtering
      rejects the received L-PDU, the CanIf shall end the receive indication for that call of
      CanIf_RxIndication().
      */
    if( CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhRangeCfgRef!= NULL_PTR &&
        CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].\
        CanIfHrhIdSymRef->CanHandleType == BASIC &&
        CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhSoftwareFilter == TRUE)
    {
        /*Check if the CanId is within configured range of this HRH
         *[SWS_CANIF_00645] A range of CanIds which shall pass the software receive filter
          shall either be defined by its upper limit (see CANIF_HRHRANGE_UPPER_CANID,
          ECUC_CanIf_00630) and lower limit (see CANIF_HRHRANGE_LOWER_CANID,
          ECUC_CanIf_00629) CanId, or by a base ID (see CANIF_HRHRANGE_BASEID) and
          a mask that defines the relevant bits of the base ID (see CANIF_HRHRANGE_MASK).
         */
        if((CanId>=LowerRange && CanId<= UpperRange)||((CanId & MaskId) == BaseId))
        {
            ret_val = E_OK;
        }
    }
    else
    {
        /*return OK if HRH is not of type BASIC ,so no need for SW filtering */
        ret_val = E_OK;
    }
	return ret_val;
}

/****************************************************************************/
//    Function Name           : CanIf_PDULinearSearch
//    Function Description    : Search a specific PDU that has the required CanId range
//    Parameter in            : HrhId , CanId
//    Parameter inout         : none
//    Parameter out           : PduId
//    Return value            : Std_ReturnType
/****************************************************************************/
static Std_ReturnType CanIf_PDULinearSearch(Can_HwHandleType HrhId,Can_IdType CanId,uint32*PduId)
{
    uint32 counter = 0 ;
    Std_ReturnType ret_val = E_NOT_OK ;
    CanHardwareObjectType* PduHrh     ;
    CanHardwareObjectType*  CurrentHrh ;

    CurrentHrh = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[HrhId].CanIfHrhIdSymRef ;

    for(counter=0;counter<RX_CAN_L_PDU_NUM;counter++)
    {
        PduHrh = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[counter].CanIfRxPduHrhIdRef->CanIfHrhIdSymRef;

        /*search only inside the PDUs of the current HRH*/
        if(CurrentHrh == PduHrh)
        {
            if(PduSCanIdRanges[counter].CanIdStart<=CanId && PduSCanIdRanges[counter].CanIdEnd>=CanId)
            {
                /*PDUId found*/
                ret_val = E_OK ;
                *PduId  = PduSCanIdRanges[counter].PduId ;
                break;
            }
        }
    }
    return ret_val ;
}


/****************************************************************************/
//    Function Name           : CanIf_RxIndication
//    Function Description    : [SWS_CANIF_00415] Within the service CanIf_RxIndication() the CanIf
//                              routes this indication to the configured upper layer target service(s). c()
//    Overview: CanIf performs the following steps at a call of CanIf_RxIndication():
//                              1- Software Filtering (only BasicCAN), if configured
//                              2- Data Length Check, if configured
//                              3- buffer received L-SDU if configured
//                              4- call upper layer receive indication callback service, if configured.
//
//    Parameter in            : Mailbox , PduInfoPtr
//    Parameter inout         : none
//    Parameter out           : none
//    Return value            : none
/****************************************************************************/
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
	uint32 counter = 0 ;
	uint32 PduId =0;
	Can_HwHandleType  CanIfHrh = 0;
	CanIdTypeType CanIdType = 0;
	CanHandleTypeType CanHandleType = 0 ;
	PduInfoType UpperLayerPduInfo ;
	uint8 Data[CANFD_DATA_LENGTH];

	
	for(counter=0;counter<CANIF_HRH_OBj_NUM;counter++)
	{
	    /*Get CanIf Hrh mapped to the CAN Mail box HOH*/
	    if(Mailbox->Hoh==CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[counter].\
	            CanIfHrhIdSymRef->CanObjectId)
	    {
	        CanIfHrh = counter;

	        /*Get CanId type standard or extended */
	        CanIdType = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[counter].\
	                CanIfHrhIdSymRef->CanIdType ;
	        /*Get HOH type BASIC or FULL*/
	        CanHandleType = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfInitHohCfgRef->CanIfHrhCfgRef[counter].\
                    CanIfHrhIdSymRef->CanHandleType ;
	        break ;
	    }
	}

	/*  [SWS_CANIF_00419]  If parameter PduInfoPtr or Mailbox of
        CanIf_RxIndication() has an invalid value, CanIf shall report development
        error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET
        module, when CanIf_RxIndication() is called.
     */
	if ((NULL_PTR == Mailbox) || (NULL_PTR == PduInfoPtr))
	{
        #if (CANIF_DEV_ERROR_DETECT == STD_ON)
		    Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,CANIF_E_PARAM_POINTER);
        #endif
	}
	/*  [SWS_CANIF_00421] If CanIf was not initialized before calling
        CanIf_RxIndication(), CanIf shall not execute Rx indication handling, when
        CanIf_RxIndication(), is called.
     */
	else if(CanIf_ModuleState == CANIF_UNINT)
	{
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_RX_INDCIATION_API_ID,CANIF_E_UNINIT);
        #endif
	}
	/*  [SWS_CANIF_00416]  If parameter Mailbox->Hoh of CanIf_RxIndication()
        has an invalid value, CanIf shall report development error code
        CANIF_E_PARAM_HOH to the Det_ReportError service of the DET module,
        when CanIf_RxIndication() is called.
     */
	else if(Mailbox->Hoh >= CAN_HRH_NUMBER)
	{
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_RX_INDCIATION_API_ID,CANIF_E_PARAM_HOH);
        #endif
	}
	/*  [SWS_CANIF_00417] If parameter Mailbox->CanId of
        CanIf_RxIndication() has an invalid value, CanIf shall report development
        error code CANIF_E_PARAM_CANID to the Det_ReportError service of the DET
        module, when CanIf_RxIndication() is called.
     */
	else if((Mailbox->CanId > MAX_STANDARD_CAN_ID && CanIdType == STANDARD) ||
	        (Mailbox->CanId > MAX_EXTENDED_CAN_ID && CanIdType == EXTENDED))
	{
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_RX_INDCIATION_API_ID,CANIF_E_PARAM_CANID);
        #endif
	}
    else
    {
        /*1-Software Filtering (only BasicCAN), if configured */
        if(CanIf_SW_Filter(CanIfHrh , Mailbox->CanId)== E_OK || CanHandleType == FULL)
        {
            /*Get PDUId*/
            if(CanIf_PDULinearSearch(CanIfHrh, Mailbox->CanId ,&PduId) == E_OK)
            {
                /*2-Data Length Check, if configured*/

                /*Hint: The Data Length Check can be enabled or disabled globally by CanIf configuration
                  (see CanIfPrivateDataLengthCheck) for all used CanDrvs.
                  [SWS_CANIF_00168] If the Data Length Check rejects a received LPDU
                  (see [SWS_CANIF_00026]), CanIf shall report runtime error code
                  CANIF_E_INVALID_DATA_LENGTH to the Det_ReportRuntimeError() service
                  of the DET module.
                 */
                #if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
                    if(PduInfoPtr->SduLength == CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduDataLength )
                    {
                        /*3- buffer received L-SDU if configured*/
                        #if(CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
                           if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduReadData == TRUE)
                           {
                                RxBuffer[PduId].MetaDataPtr = PduInfoPtr->MetaDataPtr;
                                RxBuffer[PduId].SduLength   = PduInfoPtr->SduLength ;
                                for(counter=0;counter< PduInfoPtr->SduLength;counter++)
                                {
                                    RxBuffer[PduId].Data[counter] = PduInfoPtr->SduDataPtr[counter];
                                }

                                UpperLayerPduInfo.MetaDataPtr   = RxBuffer[PduId].MetaDataPtr;
                                UpperLayerPduInfo.SduLength     = RxBuffer[PduId].SduLength;
                                UpperLayerPduInfo.SduDataPtr    = RxBuffer[PduId].MetaDataPtr;


                           }
                        #endif

                           if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduReadData == FALSE)
                           {
                                UpperLayerPduInfo.MetaDataPtr = PduInfoPtr->MetaDataPtr;
                                UpperLayerPduInfo.SduLength= PduInfoPtr->SduLength ;
                                for(counter=0;counter< PduInfoPtr->SduLength;counter++)
                                {
                                    Data[counter]= PduInfoPtr->SduDataPtr[counter];
                                    UpperLayerPduInfo.SduDataPtr= Data ;
                                }
                           }

                        /*4- call upper layer receive indication callback service, if configured.*/
                        if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduUserRxIndicationName!=NULL_PTR)
                        {
                            CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].\
                            CanIfRxPduUserRxIndicationName(PduId,(const PduInfoType*)&UpperLayerPduInfo);
                        }
                    }
                #else
                    /*3- buffer received L-SDU if configured*/
                    #if(CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
                       if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduReadData == TRUE)
                       {
                            RxBuffer[PduId].MetaDataPtr = PduInfoPtr->MetaDataPtr;
                            RxBuffer[PduId].SduLength   = PduInfoPtr->SduLength ;
                            for(counter=0;counter< PduInfoPtr->SduLength;counter++)
                            {
                                RxBuffer[PduId].Data[counter] = PduInfoPtr->SduDataPtr[counter];
                            }

                            UpperLayerPduInfo = RxBuffer[PduId];
                       }
                    #endif

                       if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduReadData == FALSE)
                       {
                            UpperLayerPduInfo.MetaDataPtr = PduInfoPtr->MetaDataPtr;
                            UpperLayerPduInfo.SduLength PduInfoPtr->SduLength ;
                            for(counter=0;counter< PduInfoPtr->SduLength;counter++)
                            {
                                Data[counter]= PduInfoPtr->SduDataPtr[counter];
                                UpperLayerPduInfo.SduDataPtr= Data ;
                            }
                       }

                    /*4- call upper layer receive indication callback service, if configured.*/
                    if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].CanIfRxPduUserRxIndicationName!=NULL_PTR)
                    {
                        CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[PduId].\
                        CanIfRxPduUserRxIndicationName(PduId,(const PduInfoType*) UpperLayerPduInfo);
                    }
                #endif
            }
        }
    }
}
