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

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"
#include "Det.h"

typedef uint8 CanIf_NotifStatusType;
#define CANIF_TX_RX_NOTIFICATION  (CanIf_NotifStatusType)0x01 /*The requested Rx/Tx CAN L-PDU was successfully transmitted orreceived.*/
#define CANIF_NO_NOTIFICATION     (CanIf_NotifStatusType)0x00 /*No transmit or receive event occurred for the requested L-PDU*/

typedef uint8 CanIF_DetErrorType;
/** Development Errors*/
#define CANIF_E_PARAM_CANID            ((CanIF_DetErrorType)0x10U)
#define CANIF_E_PARAM_HOH              ((CanIF_DetErrorType)0x12U)
#define CANIF_E_PARAM_LPDU             ((CanIF_DetErrorType)0x13U)
#define CANIF_E_PARAM_CONTROLLERID     ((CanIF_DetErrorType)0x15U)
#define CANIF_E_PARAM_WAKEUPSOURCE     ((CanIF_DetErrorType)0x16U)
#define CANIF_E_PARAM_TRCV             ((CanIF_DetErrorType)0x17U)
#define CANIF_E_PARAM_TRCVMODE         ((CanIF_DetErrorType)0x18U)
#define CANIF_E_PARAM_TRCVWAKEUPMODE   ((CanIF_DetErrorType)0x19U)
#define CANIF_E_PARAM_CTRLMODE         ((CanIF_DetErrorType)0x21U)
#define CANIF_E_PARAM_PDU_MODE         ((CanIF_DetErrorType)0x22U)
#define CANIF_E_PARAM_POINTER          ((CanIF_DetErrorType)0x20U)
#define CANIF_E_UNINIT                 ((CanIF_DetErrorType)0x30U)
#define CANIF_E_INVALID_TXPDUID        ((CanIF_DetErrorType)0x50U)
#define CANIF_E_INVALID_RXPDUID        ((CanIF_DetErrorType)0x60U)
#define CANIF_E_INIT_FAILED            ((CanIF_DetErrorType)0x80U)
/* Runtime Errors*/
#define CANIF_E_INVALID_DATA_LENGTH    ((CanIF_DetErrorType)0x61U)
#define CANIF_E_DATA_LENGTH_MISMATCH   ((CanIF_DetErrorType)0x62U)
#define CANIF_E_STOPPED                ((CanIF_DetErrorType)0x70U)
#define CANIF_E_TXPDU_LENGTH_EXCEEDED  ((CanIF_DetErrorType)0x90U)

/* CANIF Module Id */
#define CANIF_MODULE_ID  0 /*  ID  not added*/

/* CANIF Instance Id */
#define CANIF_INSTANCE_ID 0 /*  ID  not added*/

typedef uint8 CanIF_ServiceId;
#define CANIF_GET_TX_CONFIRMATIONSTATE_ID  ((CanIF_ServiceId)0x19U)

#endif /* __CANIF_H__ */
