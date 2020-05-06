/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2020)                                        **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : CanIf.c                                                        **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-26                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C                                                         **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam                                            **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC                                                **
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
#include "Internal.h"
/*****************************************************************************************/
/*                                   Local Functions prototypes                          */
/*****************************************************************************************/
 #if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
static Std_ReturnType BufferTxPdus(Can_HwHandleType Hth ,PduIdType TxPduId,const PduInfoType*\
                                   PduInfoPtr,Can_IdType DynamicTxPduCanId);
#endif

/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
/*    Type Description        :                                                          */
/*    Type range              :                                                          */

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/




/********************************************************************************************/
/*    Function Description    : This service calls the corresponding CAN Driver service
                                for obtaining the current status of the CAN controller.     */
/*    Parameter in            : uint8 ControllerId,Can_ControllerStateType ControllerModePtr*/
/*    Parameter INOUT         : none                                                        */
/*    Parameter out           : ControllerModePtr Pointer to a memory location, where the
                                mode of the CAN controller will be stored.                  */
/*    Return value            : Std_ReturnType
 *                              E_OK: Controller mode request has been accepted.
                                E_NOT_OK: Controller mode request has not been accepted.    */
/*    Requirement             : SWS_CANIF_00229                                             */
/*                                                                                          */
/*                                                                                          */
/********************************************************************************************/
Std_ReturnType CanIf_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType state, RET_Status = E_OK ;
    CanIfTxPduCanIdTypeType IdType ;
    Can_HwHandleType Hth;
    Can_PduType TX_message;
    boolean TriggerTransmitEnable ;
    CanIfCtrlCfgType* CanIfController ;
    uint8 ControllerId =0,counter ;
    Can_IdType TxPduCanId =0 ;
    CanIfTxPduTypeType PduType ;


    /*Save CanId type to be used later*/
    IdType = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[TxPduId].CanIfTxPduCanIdType ;

    /*Save TriggerTransmitEnable for current PDU*/
    TriggerTransmitEnable = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[TxPduId].CanIfTxPduTriggerTransmit ;

    /*Get TxPduId assigned Controller*/
    CanIfController = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[TxPduId].\
            CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthCanCtrlIdRef;

    /* Loop to Get CanIf Controller Id
     * Note: The corresponding CAN Controller and HTH have to be resolved by the TxPduId.
     * [SWS_CANIF_00005]*/
    for(counter =0 ; counter< CANIF_CONTROLLERS_NUM; counter++)
    {
        if(&CanIfCtrlCfgObj[counter] == CanIfController)
        {
            ControllerId = counter ;
        }
    }

    /*Check if Module initialized */
    if(CanIf_ModuleState == CANIF_UNINT)
    {
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TRANSMIT_ID,CANIF_E_UNINIT);
        #endif
       RET_Status = E_NOT_OK ;
    }
    /* [SWS_CANIF_00320] d If parameter PduInfoPtr of CanIf_Transmit()
     * has an invalid value, CanIf shall report development error code CANIF_E_PARAM_POINTER
     * */
    else if(PduInfoPtr == NULL_PTR)
    {
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TRANSMIT_ID,CANIF_E_PARAM_POINTER);
        #endif
        RET_Status = E_NOT_OK ;
    }

    /* [SWS_CANIF_00319]dIf parameter TxPduId of CanIf_Transmit() has an invalid value,
     * CanIf shall report development error code CANIF_E_INVALID_TXPDUID
     * to the Det_ReportError service
     */
    else if(TxPduId >= TX_CAN_L_PDU_NUM)
    {
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TRANSMIT_ID,CANIF_E_INVALID_TXPDUID );
       #endif
       RET_Status = E_NOT_OK ;
    }

    /*[SWS_CANIF_00893] d When CanIf_Transmit() is called with PduInfoPtr>SduLength exceeding
     *the maximum length of the PDU referenced by TxPduId: • SduLength > 8 if the Can_IdType
     *indicates a classic CAN frame • SduLength > 64 if the Can_IdType indicates a CAN FD frame
     *CanIf shall report runtime error code CANIF_E_DATA_LENGTH_MISMATCH to the Det_ReportRuntimeError()
     *service of the DET
     */
    else if((PduInfoPtr->SduLength > CLASSIC_CAN_DATA_LENGTH ) && ((IdType==EXTENDED_CAN_TX) || (IdType == STANDARD_CAN_TX)))
    {
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TRANSMIT_ID,CANIF_E_DATA_LENGTH_MISMATCH );
        #endif
      RET_Status = E_NOT_OK ;
    }

    else if((PduInfoPtr->SduLength > CANFD_DATA_LENGTH ) && ((IdType==EXTENDED_FD_CAN_TX) || (IdType == STANDARD_FD_CAN_TX)))
    {
         #if(CANIF_DEV_ERROR_DETECT == STD_ON)
             Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TRANSMIT_ID,CANIF_E_DATA_LENGTH_MISMATCH );
         #endif
       RET_Status = E_NOT_OK ;
     }

    /*Check data pointer not NULL
     *[SWS_CANIF_00882] d CanIf_Transmit() shall accept a NULL pointer as PduInfoPtr->SduDataPtr,
     *if the PDU is configured for triggered transmission: CanIfTxPduTriggerTransmit = TRUE.
     */
    else if(PduInfoPtr->SduDataPtr == NULL_PTR && TriggerTransmitEnable == FALSE)
    {
        #if(CANIF_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_TRANSMIT_ID,CANIF_E_PARAM_POINTER);
        #endif
        RET_Status = E_NOT_OK ;
    }
    /*[SWS_CANIF_00677] If a controller mode referenced by ControllerId is in state CAN_CS_STOPPED
     * and if the PduIdType parameter in a call of CanIf_Transmit() is assigned to that CAN Controller,
     * then the call of CanIf_Transmit() does not result in a call of Can_Write() (see [SWS_CANIF_00317])
     * and returns E_NOT_OK. */
    else if(CanIf_ControllerState[ControllerId] != CAN_CS_STARTED)
    {
        RET_Status = E_NOT_OK ;
    }

    /*[SWS_CANIF_00073]  For Physical Channels switching to CANIF_OFFLINE mode CanIf shall:
     * prevent forwarding of transmit requests CanIf_Transmit() of associated LPDUs to CanDrv
     * (return E_NOT_OK to the calling upper layer modules)
     */
    else if(CanIf_PduMode[ControllerId] == CANIF_OFFLINE)
    {
        RET_Status = E_NOT_OK ;
    }
    /*TODO :[SWS_CANIF_00900]*/

    /*No error proceed transmitting*/
    else
    {
        /*[SWS_CANIF_00188]dCanIfshallprocessthetwomostsignificantbitsoftheCanId (see[1, SpecificationofCANDriver],
         * definition of Can_IdType [SWS_Can_00416])to determine which type of CanId is used
         *
         * Represents the Identifier of an L-PDU. The two most significant bits specify the frame type:
         *  00 CAN message with Standard  CAN ID
         *  01 CAN FD frame with Standard CAN ID
         *  10 CAN message with Extended  CAN ID
         *  11 CAN FD frame with Extended CAN ID
         */
        /*STANDARD_CAN_TX*/


        if(IdType ==STANDARD_CAN_TX)
        {
            TxPduCanId |=(STANDARD_CAN_TX<<30);
        }
        /*EXTENDED_CAN_TX*/
        else if(IdType ==EXTENDED_CAN_TX)
        {
            TxPduCanId |=(EXTENDED_CAN_TX<<30);
        }
        /*STANDARD_FD_CAN_TX*/
        else if(IdType ==STANDARD_FD_CAN_TX)
        {
            TxPduCanId |=(STANDARD_FD_CAN_TX<<30);
        }
        /*EXTENDED_FD_CAN_TX*/
        else
        {
            TxPduCanId |=(EXTENDED_FD_CAN_TX<<30);
        }

        /*Check PDU type Dynamic or static*/
        PduType = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[TxPduId].CanIfTxPduType ;

        /*Dynamic type*/
        if(PduType == DYNAMIC_TX_PDU)
        {
        for(counter =0 ;counter <TX_CAN_L_PDU_NUM; counter++)
        {
            if(MapCanIdToPdu[counter].PduId ==TxPduId)
            {
                TxPduCanId |= (0x3FFFFFFF & MapCanIdToPdu[counter].CanId);
            }
        }
        }
        /*Static type*/
        else
        {
        TxPduCanId |=( 0x3FFFFFFF & CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[TxPduId].CanIfTxPduCanId);
        }
        /*Save physical CAN ID*/
        TX_message.id = TxPduCanId;

        /*Save Data Length*/
        TX_message.length = PduInfoPtr->SduLength ;

        /*[SWS_CANIF_00882] d CanIf_Transmit() shall accept a NULL pointer as PduInfoPtr->SduDataPtr,
         *if the PDU is configured for triggered transmission: CanIfTxPduTriggerTransmit = TRUE.
         */
        if(TriggerTransmitEnable == TRUE)
        {
            TX_message.sdu = NULL_PTR ;
        }
        else
        {
            /*Save data buffer*/
            TX_message.sdu = PduInfoPtr->SduDataPtr ;
        }

        /*Save PDU ID*/
        TX_message.swPduHandle = TxPduId;
        Hth = CanIf_ConfigPtr->CanIfInitCfgRef->CanIfTxPduCfgRef[TxPduId].\
            CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthIdSymRef->CanObjectId ;

        /*Call can Write*/
        state = Can_write(Hth ,( const Can_PduType * )&TX_message);

        /*if Can_write returns E_NOT_OK
         *check if TX Buffering is enable to store buffer
         */
        if(state == E_NOT_OK)
        {
        #if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
            /*Buffer PDU,
             *BufferTxPdus returns E_OK     -> if found empty place or overwrites same PDU
             *BufferTxPdus returns E_NOT_OK -> if didn't find empty place
             *
             *[SWS_CANIF_00837] d If the buffer size is greater zero, all buffer elements are busy
             *and CanIf_Transmit() is called with a new L-PDU (no other instance of the same L-PDU
             *is already stored in the buffer), then the new L-PDU or its Transmit Request shall
             *not be stored and CanIf_Transmit() shall return E_NOT_OK
             */
            RET_Status= BufferTxPdus(Hth,TxPduId,PduInfoPtr,TxPduCanId);
        #else
        RET_Status = state ;
        #endif
        }
        else
        {
            RET_Status = state ;
        }
    }
    return  RET_Status ;
}

#if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
static Std_ReturnType BufferTxPdus(Can_HwHandleType Hth ,PduIdType TxPduId,const PduInfoType* PduInfoPtr,Can_IdType DynamicTxPduCanId)
{
    uint8 BufferCounter =0 , PduCounter =0, BufferSize = 0, BufferPlace =0;
    boolean FoundPlace = FALSE ;
    Can_HwHandleType BufferHth =0 ;
    PduIdType BufferPdu = 0 ;
    PduLengthType   DataLength = 0 ;
    Std_ReturnType rtn_val = E_NOT_OK ;

    /* Get the right buffer to use . PDU must be save in the buffer that uses
     * the same HTH configured for that PDU
     */
      for(BufferCounter =0; BufferCounter < BUFFERS_NUM ;BufferCounter++)
      {
          /*Get this buffer assigned HTH*/
          BufferHth =  CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].\
                  CanIfBufferRef->CanIfBufferHthRef->CanIfHthIdSymRef->CanObjectId ;

          /*If HTH for the requested PDU found , Find Empty place in the buffer*/
          if(Hth == BufferHth)
          {
              /*Get buffer size*/
              BufferSize = CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfBufferRef->CanIfBufferSize ;

              for(PduCounter= 0 ; PduCounter < BufferSize ;PduCounter++)
              {
                  /* Check if PDU was buffered before ,
                   * only one instance per TX L-PDU can be buffered in the over all amount of CanIfBufferCfg.
                   * [SWS_CANIF_00068] CanIf shall overwrite direct transmitted CanIf TX L-PDU in the assigned
                   * CanIfTxBuffer, if the CanIf TX L-PDU is already buffered in the CanIfTxBuffe
                   */
                  BufferPdu = CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].\
                              CanIfPduInfoRef[PduCounter].TxPduId ;

                  if(BufferPdu == TxPduId)
                  {
                      FoundPlace = TRUE ;
                      BufferPlace = PduCounter ;
                      break;
                  }
                  /*Save  Empty place in the buffer */
                  else if( CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfPduInfoRef[PduCounter].Empty == TRUE)
                  {
                      FoundPlace = TRUE ;
                      BufferPlace = PduCounter ;
                  }
                  else
                  {

                  }
              }
              if(FoundPlace == TRUE)
              {
                  break;
              }
          }
      }
      /*Save PDU in buer as we found place whether it's empty place or overwrite the same PDU*/
      if(FoundPlace == TRUE)
      {
          /*Save data length*/
          DataLength = PduInfoPtr->SduLength ;
          CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfPduInfoRef[PduCounter].SduLength = DataLength ;

          /*Save SDU */
          for(uint32 Datacounter =0 ;Datacounter< DataLength; Datacounter++)
          {
              CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfPduInfoRef[BufferPlace].\
              SduDatabuffer[Datacounter] = PduInfoPtr->SduDataPtr[Datacounter] ;
          }
          /*Save DynamicTxPduCanId*/
          CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfPduInfoRef[BufferPlace].DynamicCanId = DynamicTxPduCanId;

          /*save PDU ID*/
          CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfPduInfoRef[BufferPlace].TxPduId = TxPduId ;
          /*Save place as not empty*/
          CanIf_ConfigPtr->CanIfPduTxBufferCfgRef[BufferCounter].CanIfPduInfoRef[BufferPlace].Empty = FALSE ;
          rtn_val = E_OK ;
      }

      return rtn_val ;
}
#endif
