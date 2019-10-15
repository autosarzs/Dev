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

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId,
		uint8 ErrorId) {
	return 0;
}

void CanIf_TxConfirmation(PduIdType CanTxPduId) {

}
