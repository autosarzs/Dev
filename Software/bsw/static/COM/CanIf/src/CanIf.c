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
//#include "CanIf_Types.h"
#include "Det.h"
/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/
/*
 *  Type Description : Struct to map CanIds to a specific L-PDU of type dynamic  .
 */
typedef struct
{
   Can_IdType     CanId;
   PduIdType      PduId;
}str_MapCanIdToPdu ;


/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
/*    Type Description        :                                                          */
/*    Type range              :                                                          */

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/

/*Array of struct to map CanIds to a specific L-PDU of type dynamic*/
static str_MapCanIdToPdu  MapCanIdToPdu[TX_CAN_L_PDU_NUM] = {0};




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

Std_ReturnType CanIf_GetControllerMode(
uint8 ControllerId,
Can_ControllerStateType* ControllerModePtr
)
{
	/* [SWS_CANIF_00313] d If parameter ControllerId of
	CanIf_GetControllerMode() has an invalid, the CanIf shall report development
	error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
	of the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
	if (ControllerId != 0 || ControllerId != 1){
	  	  Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CanIf_GetControllerMode_Id, CANIF_E_PARAM_CONTROLLERID);

	  	  return E_NOT_OK;
	}

	/*[SWS_CANIF_00656] d If parameter ControllerModePtr of
	CanIf_GetControllerMode() has an invalid value, the CanIf shall report development
	error code CANIF_E_PARAM_POINTER to the Det_ReportError service of
	the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
	if(ControllerModePtr == 0){
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_GetControllerMode_Id, CANIF_E_PARAM_POINTER);

		return E_NOT_OK;
	}

	Can_GetControllerMode(ControllerId, ControllerModePtr);

	return E_OK;
}

/*************************************************************************************************/
/*    Function Description    : Requests cancellation of an ongoing transmission of a PDU in
                                a lower layer communication module                               */
/*    Parameter in            : TxPduId Identification of the PDU to be cancelled.               */
/*    Parameter INOUT         : none                                                             */
/*    Parameter out           : ControllerModePtr Pointer to a memory location, where the
                                mode of the CAN controller will be stored.                       */
/*    Return value            : Std_ReturnType
 *                              E_OK: Cancellation was executed successfully
                                      by the destination module
                                E_NOT_OK: Cancellation was rejected by the destination module    */
/*    Requirement             : SWS_CANIF_00520                                                  */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/

#ifdef CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT
Std_ReturnType CanIf_CancelTransmit(
PduIdType TxPduId
)
{
    uint8 pduid_counter = 0;
    Std_ReturnType  RET_Status = E_NOT_OK ;
    /*
     * check the TxPduId is in the MapCanIdToPdu to complete the cancellation process
     */
    for(pduid_counter = 0 ; pduid_counter < TX_CAN_L_PDU_NUM ; pduid_counter++ )
    {
        // check the PDU ID
        if (MapCanIdToPdu[pduid_counter].PduId == TxPduId)
        {
            RET_Status = E_OK;
            break;
        }
    }
    // Report the DET Error
    if (RET_Status != E_OK )
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_CancelTransmit_Id, CANIF_E_PARAM_POINTER);
    }
    return RET_Status;

}
#endif

