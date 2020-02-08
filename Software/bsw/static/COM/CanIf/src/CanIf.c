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
#include "..\inc\CanIf.h"

static CanIf_ConfigType * Global_Config= NULL ;
CanIf_PduModeType PduMode =CANIF_OFFLINE;

Std_ReturnType CanIf_SetPduMode(uint8 ControllerId,CanIf_PduModeType PduModeRequest)
{
    uint8 counterpduId;
    Can_ControllerStateType Loc_Controller_Mode;
    Std_ReturnType Loc_CanIf_SetPduMode_Ret = E_OK ;

    /*[SWS_CANIF_00341] If CanIf_SetPduMode() is called with invalid
ControllerId, CanIf shall report development error code
CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the
DET module. c(SRS_BSW_00323)*/


    if (ControllerId > 5 )
    {
#if ( DevError == STD_ON )
        Det_ReportError (CANIF_MODULE_ID,CANIF_INSTANSE_ID , CanIf_SetPduMode, CANIF_E_PARAM_CONTROLLERID );
#else
        Loc_CanIf_SetPduMode_Ret = E_NOT_OK;
#endif
    }


    /*[SWS_CANIF_00860]  If CanIf_SetPduMode() is called with invalid PduModeRequest,
CanIf shall report development error code CANIF_E_PARAM_PDU_MODE
to the Det_ReportError service of the DET module. c(SRS_BSW_00323)*/


    if (PduModeRequest >= MAX_PDU_REQUEST  )
    {
#if ( DevError == STD_ON )
        Det_ReportError (CANIF_MODULE_ID,CANIF_INSTANSE_ID , CanIf_SetPduMode, CANIF_E_PARAM_PDU_MODE );
#else
        Loc_CanIf_SetPduMode_Ret = E_NOT_OK;
#endif
    }

    /*[SWS_CANIF_00874] The service CanIf_SetPduMode() shall not accept any request
and shall return E_NOT_OK, if the controller mode referenced by ControllerId
is not in state CAN_CS_STARTED. c()*/

    Loc_CanIf_SetPduMode_Ret==CanIf_GetControllerMode(ControllerId,&Loc_Controller_Mode );  /* To Get The mode of ControllerMode */

    if (Loc_CanIf_SetPduMode_Ret == E_OK )
    {
        if (Loc_Controller_Mode != CAN_CS_STARTED )
            return E_NOT_OK;
    }
    else
    {
        return E_NOT_OK;
    }

    switch(PduModeRequest)
    {

    case CANIF_OFFLINE:
    case CANIF_TX_OFFLINE:
#if (CanIfTxOfflineActiveSupport ==STD_ON)
    case CANIF_TX_OFFLINE_ACTIVE:
#endif

        if(PduMode==CANIF_ONLINE)
        {
            /* [SWS_CANIF_00865] dIf CanIf_SetControllerMode(ControllerId, CAN_-
                     CS_SLEEP)*/
            for(counterpduId=0;counterpduId<TX_CAN_L_PDU_NUM;counterpduId++)
            {
                Global_Config->CanIfInitCfgObj.CanIfTxPduCfgObj[counterpduId].CanIfTxPduBufferRef=NULL;
            }

        }
        switch(PduModeRequest)
        {
        case CANIF_OFFLINE:
            PduMode=CANIF_OFFLINE;
            break;
        case CANIF_TX_OFFLINE:
            PduMode=CANIF_TX_OFFLINE;
            break;
#if (CanIfTxOfflineActiveSupport ==STD_ON)
        case CANIF_TX_OFFLINE_ACTIVE:
            PduMode=CANIF_TX_OFFLINE_ACTIVE;
            break;
#endif
        default:
            break;
        }

        break;

        case CANIF_ONLINE:
            PduMode=CANIF_ONLINE;
            break;
        default:
            break;
    }


}


Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxSduId,PduInfoType*CanIfRxInfoPtr)
{
    Std_ReturnType Loc_CanIf_ReadRxPduData_Ret =E_OK ;
    Can_ControllerStateType Loc_Controller_Mode;
    uint8 Loc_Controller_Id;
    /*[SWS_CANIF_00324] d The function CanIf_ReadRxPduData() shall not accept a
request and return E_NOT_OK, if the corresponding controller mode refrenced by Con�trollerId is different to CAN_CS_STARTED and the channel mode is in the receive
path online.
     */

    Loc_Controller_Id=Global_Config->CanIfInitCfgObj.CanIfRxPduCfgObj[CanIfRxSduId].CanIfRxPduHrhIdRef->CanIfHrhCanCtrlIdRef->CanIfCtrlId;

    Loc_CanIf_ReadRxPduData_Ret=CanIf_GetControllerMode(Loc_Controller_Id,&Loc_Controller_Mode );
    if (Loc_CanIf_ReadRxPduData_Ret==E_OK )
    {
        if (Loc_Controller_Mode != CAN_CS_STARTED )
            return E_NOT_OK;

    }
    else
    {
        return E_NOT_OK;
    }
    /*
[SWS_CANIF_00325] d If parameter CanIfRxSduId of CanIf_ReadRxPduData()
has an invalid value, e.g. not configured to be stored within CanIf via
CANIF_READRXPDU_DATA (ECUC_CanIf_00600), CanIf shall report development
error code CANIF_E_INVALID_RXPDUID to the Det_ReportError service of the
DET, when CanIf_ReadRxPduData() is called
     */
    if (CanIfRxSduId >= RX_CAN_L_PDU_NUM )
    {
#if ( DevError == STD_ON )
        Det_ReportError (CANIF_MODULE_ID,CANIF_INSTANSE_ID , CanIf_ReadRxPduData_Id,CanIF_E_INVALID_RXPDUID );
#else
        Loc_CanIf_ReadRxPduData_Ret=E_NOT_OK;
#endif
    }
    /*[SWS_CANIF_00326] d If parameter CanIfRxInfoPtr of
CanIf_ReadRxPduData() has an invalid value, CanIf shall report develop�ment error code CANIF_E_PARAM_POINTER to the Det_ReportError service of
the DET module, when CanIf_ReadRxPduData() is called*/
    if (CanIfRxInfoPtr== NULL)
    {
#if ( DevError == STD_ON )
        Det_ReportError (CANIF_MODULE_ID,CANIF_INSTANSE_ID , CanIf_ReadRxPduData_Id,CanIF_E_PARAM_POINTER );
#else
        Loc_CanIf_ReadRxPduData_Ret=E_NOT_OK;
#endif
    }
    /* [SWS_CANIF_00329] d CanIf_ReadRxPduData() shall not be used for CanIfRxS�duId, which are defined to receive multiple CAN-Ids (Srange reception). c()
Note: During the call of CanIf_ReadRxPduData() the buffer of CanIfRxInfoPtr is
controlled by CanIf and this buffer should not be accessed for read/write from another
call context. After return of this call the ownership changes to the upper layer*/

    // CanIfRxInfoPtr->SduDataPtr=Global_Config->CanIfInitCfgObj.CanIfRxPduCfgObj[CanIfRxSduId].CanIfRxPduBuf;  //will be defined in

    CanIfRxInfoPtr->SduLength=Global_Config->CanIfInitCfgObj.CanIfRxPduCfgObj[CanIfRxSduId].CanIfRxPduDataLength;
    return Loc_CanIf_ReadRxPduData_Ret;

}
