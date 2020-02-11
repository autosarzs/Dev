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

typedef struct {
    uint8 transmit_confirmed;
}controllerDataType;

static controllerDataType controllerData[CANIF_CTRL_ID];

CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 ControllerId){
    CanIf_NotifStatusType notify = CANIF_NO_NOTIFICATION ;
    if(ControllerId <= CANIF_CTRL_ID){
         notify = controllerData[ControllerId].transmit_confirmed;/* this value is modified by another func*/
    }else{
        if(CANIF_DEV_ERROR_DETECT == STD_ON){
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_GET_TX_CONFIRMATIONSTATE_ID, CANIF_E_PARAM_CONTROLLERID);
        }
    }
    return notify;
}

















