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
#include "../inc/CanIf.h"
//#include "CanIf_Types.h"
#include "Det.h"
/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
/*    Type Description        :                                                          */
/*    Type range              :                                                          */

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/

/*Array of struct to map CanIds to a specific L-PDU of type dynamic*/
//extern str_MapCanIdToPdu  MapCanIdToPdu[];

/*Pointer to save configuration parameters set */
extern CanIf_ConfigType* CanIf_ConfigPtr;


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
          Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLERID);

          return E_NOT_OK;
    }

    /*[SWS_CANIF_00656] d If parameter ControllerModePtr of
    CanIf_GetControllerMode() has an invalid value, the CanIf shall report development
    error code CANIF_E_PARAM_POINTER to the Det_ReportError service of
    the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
    if(ControllerModePtr == 0){
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_POINTER);

        return E_NOT_OK;
    }

    return Can_GetControllerMode(ControllerId, ControllerModePtr);
}
