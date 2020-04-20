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
 **  MAY BE CHANGED BY USER x: no                                               **
 **                                                                            **
 *******************************************************************************/
#include "../inc/CanIf.h"

/*
 *  Type Description : Struct to save recieved  PDUs (in case of enable CanIf_ReadRxPduData API un configuration) .
 */
 
/*Pointer to save configuration parameters set */
extern CanIf_ConfigType*    CanIf_ConfigPtr;

CanIf_PduModeType CanIf_PduMode[CANIF_CONTROLLERS_NUM] ;


/*TODO who the one request CANIF to be ONLINE ??? */
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId,CanIf_PduModeType PduModeRequest)
{
    uint8 PduCounter=0;
    uint8 counter=0;
    uint8 TxBufferSize = 0;
    Can_ControllerStateType Loc_Controller_Mode=0;
    Std_ReturnType Loc_CanIf_SetPduMode_Ret = E_OK ;

    /*[SWS_CANIF_00341] If CanIf_SetPduMode() is called with invalid
ControllerId, CanIf shall report development error code
CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the
DET module. c(SRS_BSW_00323)*/


    if (ControllerId >= CANIF_CONTROLLERS_NUM )
    {
#if ( DevError == STD_ON )
        Det_ReportError (CANIF_MODULE_ID,CANIF_INSTANSE_ID , CanIf_SetPduMode, CANIF_E_PARAM_CONTROLLERID );
#endif
        Loc_CanIf_SetPduMode_Ret = E_NOT_OK;
    }


    /*[SWS_CANIF_00860]  If CanIf_SetPduMode() is called with invalid PduModeRequest,
CanIf shall report development error code CANIF_E_PARAM_PDU_MODE
to the Det_ReportError service of the DET module. c(SRS_BSW_00323)*/

        if (PduModeRequest >= MAX_PDU_REQUEST  )
        {
    #if ( DevError == STD_ON )
            Det_ReportError (CANIF_MODULE_ID,CANIF_INSTANSE_ID , CanIf_SetPduMode, CANIF_E_PARAM_PDU_MODE );
    #endif
            Loc_CanIf_SetPduMode_Ret = E_NOT_OK;
        }

/*[SWS_CANIF_00874] The service CanIf_SetPduMode() shall not accept any request
 and shall return E_NOT_OK, if the controller mode referenced by ControllerId
is not in state CAN_CS_STARTED*/
Loc_CanIf_SetPduMode_Ret = CanIf_GetControllerMode(ControllerId,&Loc_Controller_Mode );  /* To Get The mode of ControllerMode */
        if (Loc_CanIf_SetPduMode_Ret == E_OK )
        {
            if (Loc_Controller_Mode != CAN_CS_STARTED )
                Loc_CanIf_SetPduMode_Ret = E_NOT_OK;
        }
        else
        {
            Loc_CanIf_SetPduMode_Ret = E_NOT_OK;
        }
if(Loc_CanIf_SetPduMode_Ret==E_OK)
{


          
              switch(PduModeRequest)
              {
          
              case CANIF_OFFLINE:
              case CANIF_TX_OFFLINE:
          #if (CANIF_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
              case CANIF_TX_OFFLINE_ACTIVE:
          #endif
                  if(CanIf_PduMode[ControllerId]==CANIF_ONLINE)
                  {
                      /* [SWS_CANIF_00865] dIf CanIf_SetControllerMode(ControllerId, CAN_-
                               CS_SLEEP)*/
                     #if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
                     
                     
                          for(counter = 0 ; counter<BUFFERS_NUM;counter++)
                          {
                              /*Get number of PDUs saved in this buffer*/
                               TxBufferSize = CanIf_ConfigPtr->CanIfPduTxBufferCfgRef->CanIfBufferRef->CanIfBufferSize;
                     
                              /*Loop to clear all TX Buffers */
                              for(PduCounter =0;PduCounter<TxBufferSize;PduCounter++)
                              {
                     
                                  CanIf_ConfigPtr->CanIfPduTxBufferCfgRef->CanIfPduInfoRef->SduDatabuffer[PduCounter]=0;
                                  CanIf_ConfigPtr->CanIfPduTxBufferCfgRef->CanIfPduInfoRef->SduLength=0;
                              }
                          }
                      #endif
					  
					   CanIf_PduMode[ControllerId]= PduModeRequest;
          
                  }
                  break;
          
                  case CANIF_ONLINE:
                      CanIf_PduMode[ControllerId] = CANIF_ONLINE;
                      break;
                  default:
                      /* Do nothing */
                      break;
              }
		}
else
 {
   /* Do nothing */
 }
return Loc_CanIf_SetPduMode_Ret;
}





