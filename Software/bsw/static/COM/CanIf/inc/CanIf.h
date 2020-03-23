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
**  FILENAME     : CanIf			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-10-20                                                 **
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
**  SPECIFICATION(S) : Specification of CAN Inteface, AUTOSAR Release 4.3.1   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef __CANIF_H__
#define __CANIF_H__

#include "Can.h"
#include "CanIf_Types.h"
#include "CanIf_Cfg.h"

/*****************************************************************************************/
/*                                    Macro Definition                                   */
/*****************************************************************************************/
/* Id for the company in the AUTOSAR
  **/
#define CANIF_VENDOR_ID    	(0x100)

/* CAN Module Id */
#define CANIF_MODULE_ID    	(12U)

/* CAN Instance Id */
#define CANIF_INSTANCE_ID  	(0U)

/* Development Error Macros*/
#define CANIF_E_PARAM_CANID 		(10U)
#define CANIF_E_PARAM_HOH 			(12U)
#define CANIF_E_PARAM_LPDU 			(13U)
#define CANIF_E_PARAM_CONTROLLERID 	(15U)
#define CANIF_E_PARAM_WAKEUPSOURCE 	(16U)
#define CANIF_E_PARAM_TRCV 			(17U)
#define CANIF_E_PARAM_TRCVMODE 		(18U)
#define CANIF_E_PARAM_TRCVWAKEUPMODE (19U)
#define CANIF_E_PARAM_CTRLMODE 		(21U)
#define CANIF_E_PARAM_PDU_MODE 		(22U)
#define CANIF_E_PARAM_POINTER		(20U)
#define CANIF_E_UNINIT 				(30U)
#define CANIF_E_INVALID_TXPDUID 	(50U)
#define CANIF_E_INVALID_RXPDUID		(60U)
#define CANIF_E_INIT_FAILED 		(80U)

/* Runtime Error Macros*/

#define CANIF_E_INVALID_DATA_LENGTH 	(61U)
#define CANIF_E_DATA_LENGTH_MISMATCH 	(62U)
#define CANIF_E_STOPPED 				(70U)
#define CANIF_E_TXPDU_LENGTH_EXCEEDED 	(90U)


#define CANIF_SETBAUDRATE_API_ID		(0x27U)
#define CANIF_RX_INDCIATION_API_ID		(0x14U)


extern Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID);
extern void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr);
Std_ReturnType CanIf_GetPduMode(uint8 ControllerId,CanIf_PduModeType* PduModePtr);
/*******************************************************************************
 * PBconfigs shall be extern'ed here CanIf users are not responsible to extern pbcfgs.
 * CANIF users only need to include Canif.h
 */




#endif /* __CANIF_H__ */
