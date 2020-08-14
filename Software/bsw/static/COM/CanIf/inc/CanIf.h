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

/* CanIf Vendor ID in AUTOSAR */
#define CANIF_VENDOR_ID                    (2020U)

/*
 * SW Module Version is 1.0.0
 */
#define CANIF_SW_MAJOR_VERSION             (1U)
#define CANIF_SW_MINOR_VERSION             (0U)
#define CANIF_SW_PATCH_VERSION             (0U)

/*
 * AUTOSAR Version is 4.3.1 compatible
 */
#define CANIF_AR_RELEASE_MAJOR_VERSION    (4U) 
#define CANIF_AR_RELEASE_MINOR_VERSION    (3U)
#define CANIF_AR_RELEASE_PATCH_VERSION    (1U)

/*
    CanIf initialisation status codes
*/
#define CANIF_INITIALIZED                 (1U)
#define CANIF_NOT_INITIALIZED             (0U)

/******************************************************************************
*                             DET Error Codes                                 *
*******************************************************************************/

#include "CanIf_Types.h"
/* AUTOSAR version checking */
#if ((CANIF_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (CANIF_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (CANIF_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif /* AUTOSAR version checking */

/* SW module version checking */
#if ((CANIF_SW_MAJOR_VERSION != CANIF_TYPES_SW_MAJOR_VERSION)\
 ||  (CANIF_SW_MINOR_VERSION != CANIF_TYPES_SW_MINOR_VERSION)\
 ||  (CANIF_SW_PATCH_VERSION != CANIF_TYPES_SW_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif /* SW module version checking */
#include "CanIf_Cfg.h"
#include "Det.h"

typedef uint8 CanIf_NotifStatusType;
#define CANIF_TX_RX_NOTIFICATION  (CanIf_NotifStatusType)0x01 /*The requested Rx/Tx CAN L-PDU was successfully transmitted orreceived.*/
#define CANIF_NO_NOTIFICATION     (CanIf_NotifStatusType)0x00 /*No transmit or receive event occurred for the requested L-PDU*/

/* CanIf Module Id in AUTOSAR */
#define CANIF_MODULE_ID		((uint16)60U)

/* CanIf Instance Id */
#define CANIF_INSTANCE_ID	((uint8)0U)

/* CanIf Service Id */

#define CANIF_TXCONFIRMATION_API_ID     ((uint8)0x13)

/* CanIf_DetErrorType */
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

typedef uint8 CanIF_ServiceId;
#define CANIF_GET_TX_CONFIRMATIONSTATE_ID  ((CanIF_ServiceId)0x19U)

/* AUTOSAR version checking */
#if ((CANIF_AR_RELEASE_MAJOR_VERSION != CANIF_CFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (CANIF_AR_RELEASE_MINOR_VERSION != CANIF_CFG_AR_RELEASE_MINOR_VERSION)\
 ||  (CANIF_AR_RELEASE_PATCH_VERSION != CANIF_CFG_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif /* AUTOSAR version checking */

/* SW module version checking */
#if ((CANIF_SW_MAJOR_VERSION != CANIF_CFG_SW_MAJOR_VERSION)\
 ||  (CANIF_SW_MINOR_VERSION != CANIF_CFG_SW_MINOR_VERSION)\
 ||  (CANIF_SW_PATCH_VERSION != CANIF_CFG_SW_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif /* SW module version checking */

/* Maximum Pdu Request */
#define MAX_PDU_REQUEST     (04)
/*******************************************************************************
*                           API Service ID Macros                              *
*******************************************************************************/
typedef uint8 CanIf_ServiceId;
#define CANIF_GET_CONTROLLER_ERROR_STATE_SID    ((CanIf_ServiceId)0x4b)
#define CANIF_GET_PDU_MODE_SID                  ((CanIf_ServiceId)0x0a)
#define CANIF_GET_CONTROLLER_MODE_ID            ((CanIf_ServiceId)0x04)
#define CANIF_CANCEL_TRANSMIT_ID                ((CanIf_ServiceId)0x4A)
#define CANIF_TRANSMIT_ID                       ((CanIf_ServiceId)0x49)
#define CANIF_INIT_API_ID                       ((CanIf_ServiceId)0x01)
#define CANIF_DEINIT_API_ID                     ((CanIf_ServiceId)0x02)
#define CANIF_RX_INDCIATION_API_ID              ((CanIf_ServiceId)0x14)
#define CANIF_SET_CONTROLLER_MODE_SID           ((CanIf_ServiceId)0x03)
#define CANIF_SETBAUDRATE_API_ID                ((CanIf_ServiceId)0x27)
#define CANIF_READ_RX_PDU_DATA_API_ID           ((CanIf_ServiceId)0x06)
#define CANIF_SET_PDU_MODE_ID                   ((CanIf_ServiceId)0x09)
/*******************************************************************************
* Service Name:       CanIf_GetControllerErrorState
* Service ID[hex]:    0x4b
* Sync/Async:         Synchronous
* Reentrancy:         Non Reentrant for the same ControllerId
* Parameters (in):    ControllerId Abstracted CanIf ControllerId which is assigned to a
                      CAN controller, which is requested for ErrorState.
* Parameters (inout): None
* Parameters (out):   ErrorStatePtr Pointer to a memory location, where the error state
                      of the CAN controller will be stored.
* Return value:       Std_ReturnType E_OK: Error state request has been accepted.
                      E_NOT_OK: Error state request has not been accepted.
* Description:        This service calls the corresponding CAN Driver service for 
                      obtaining the error state of the CAN controller.
***********************************************************************************/
Std_ReturnType 
CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr);

/*******************************************************************************
* Service Name:       CanIf_GetPduMode
* Service ID[hex]:    0x0a
* Sync/Async:         Synchronous
* Reentrancy:         Reentrant (Not for the same channel)
* Parameters (in):    ControllerId All PDUs of the own ECU connected to the corre-
                      sponding CanIf ControllerId, which is assigned to a physical 
                      CAN controller are addressed.
* Parameters (inout): None
* Parameters (out):   PduModePtr Pointer to a memory location, where the current
                      mode of the logical PDU channel will be stored.                      
* Return value:       Std_ReturnType E_OK: PDU mode request has been accepted
                                     E_NOT_OK: PDU mode request has not been 
                                     ac-cepted.                      
* Description:        This service reports the current mode of a requested PDU channel.
***********************************************************************************/
Std_ReturnType 
CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr);

/********************************************************************************************/
/* Service Name     : CanIf_SetControllerMode                                               */
/* Syntax           : Std_ReturnType CanIf_SetControllerMode                                */
/*                    (uint8 ControllerId, Can_ControllerStateType ControllerMode)          */
/* Service ID[hex]  : 0x03                                                                  */
/* Sync/Async       : Asynchronous                                                          */
/* Reentrancy       : Reentrant (Not for the same controller)                               */
/* Parameters (in)  : ControllerId: Abstracted CanIf ControllerId which is assigned to a    */
/*                    CAN controller, which is requested for mode transition.               */
/*                    ControllerMode: Requested mode transition                             */
/* Parameters(inout): None                                                                  */
/* Parameters (out) : None                                                                  */
/* Return Value     : Std_ReturnType E_OK    : Controller mode request has been accepted    */
/* E_NOT_OK         : Controller mode request has not been accepted                         */
/* DESCRIPTION      : This service calls the corresponding CAN Driver service for           */
/* changing ofthe CAN controller mode.                                                      */
/********************************************************************************************/
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);
void CanIf_TxConfirmation(PduIdType);
CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8);
Std_ReturnType CanIf_GetControllerMode(uint8 ,Can_ControllerStateType*);
#endif /* __CANIF_H__ */
