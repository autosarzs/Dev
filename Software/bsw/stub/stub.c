/*******************************************************************************
 **                                                                            **
 **  Copyright (C) AUTOSarZs olc (2019)		                                  **
 **                                                                            **
 **  All rights reserved.                                                      **
 **                                                                            **
 **  This document contains proprietary information belonging to AUTOSarZs     **
 **  olc . Passing on and copying of this document, and communication          **
 **  of its contents is not permitted without prior written authorization.     **
 **                                                                            **
 ********************************************************************************
 **                                                                            **
 **  FILENAME     : Stub.c					                                  **
 **                                                                            **
 **  VERSION      : 1.0.0                                                      **
 **                                                                            **
 **  DATE         : 2019-09-22                                                 **
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
 **  DESCRIPTION  : CAN Driver source file                                     **
 **                                                                            **
 **  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.3.1     **
 **                                                                            **
 **  MAY BE CHANGED BY USER : no                                               **
 **                                                                            **
 *******************************************************************************/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "CanIf_Cbk.h"
#include "Stub.h"

uint8 ReadData=0;
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
		uint8 ErrorId)
{
	return 0;
}

// Runtime errors report function
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId){
    return 0;
}

void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{

}

/**
 * \brief This callout function is called whenever a CAN message is
 *  received in CAN driver.
 */
/*void CanIf_RxIndication
(
    const Can_HwType * Mailbox,
    const PduInfoType * PduInfoPtr
)

{
        ReadData= *(PduInfoPtr->SduDataPtr);
}*/

void CanIf_ControllerBusOff(uint8 ControllerId)
{

}

void CanIfTxPduUserTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{

}

void CanIfTxPduUserTriggerTransmitName(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
}

void CanIfTxPduUserTxConfirmation(PduIdType TxPduId, Std_ReturnType result )
{

}

void CanIfRxPduUserRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr )
{

}

void CanNm_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void CanNm_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void Xcp_CanIfTxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void Xcp_CanIfRxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void PduR_CanIfTxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void PduR_CanIfRxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void J1939Tp_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void J1939Tp_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void J1939Nm_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void J1939Nm_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void Cdd_CanIfTxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void Cdd_CanIfRxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void CanTSyn_CanIfTxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void CanTSyn_CanIfRxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}


void CanTp_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
)
{
}

void CanTp_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
)
{
}

Std_ReturnType PduR_CanIfTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
    return 0;
}

void CanSM_CheckTrcvWakeFlagIndication(uint8 TransceiverId)
{

}

void CanSM_ClearTrcvWufFlagIndication(uint8 TransceiverId)
{

}

void CanSM_ConfirmPnAvailability(uint8 TransceiverId)
{

}

void CanSM_ControllerBusOff(uint8 ControllerId)
{

}

void CanSM_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{

}

void CanSM_TransceiverModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{

}

void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources)
{

}
