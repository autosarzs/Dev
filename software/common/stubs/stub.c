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

uint8 ReadData=0;
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
		uint8 ErrorId)
{
	return 0;
}

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{

}

void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{

}

/**
 * \brief This callout function is called whenever a CAN message is
 *  received in CAN driver.
 */
void CanIf_RxIndication
(
    const Can_HwType * Mailbox,
    const PduInfoType * PduInfoPtr
)

{
        ReadData= *(PduInfoPtr->SduDataPtr);
}

void CanIf_ControllerBusOff(uint8 ControllerId)
{

}


