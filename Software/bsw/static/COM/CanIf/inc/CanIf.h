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

/* CanIf Module ID in AUTOSAR */
#define	CANIF_MODULE_ID					   (060U)

/* CanIf Instance ID */
#define CANIF_INSTANCE_ID                  (0U)

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
/*
    Development Errors.
*/
#define CANIF_E_PARAM_CANID                ((uint8)10)
#define CANIF_E_PARAM_HOH                  ((uint8)12)
#define CANIF_E_PARAM_LPDU                 ((uint8)13)
#define CANIF_E_PARAM_CONTROLLERID         ((uint8)15)
#define CANIF_E_PARAM_WAKEUPSOURCE         ((uint8)16)
#define CANIF_E_PARAM_TRCV                 ((uint8)17)
#define CANIF_E_PARAM_TRCVMODE             ((uint8)18)
#define CANIF_E_PARAM_TRCVWAKEUPMODE       ((uint8)19)
#define CANIF_E_PARAM_CTRLMODE             ((uint8)21)
#define CANIF_E_PARAM_PDU_MODE             ((uint8)22)
#define CANIF_E_PARAM_POINTER              ((uint8)20)
#define CANIF_E_UNINIT                     ((uint8)30)
#define CANIF_E_INVALID_TXPDUID            ((uint8)50)
#define CANIF_E_INVALID_RXPDUID            ((uint8)60)
#define CANIF_E_INIT_FAILED                ((uint8)80)
/*
    Runtime Errors.
*/
#define CANIF_E_INVALID_DATA_LENGTH        ((uint8)61)
#define CANIF_E_DATA_LENGTH_MISMATCH       ((uint8)62)
#define CANIF_E_STOPPED                    ((uint8)70)
#define CANIF_E_TXPDU_LENGTH_EXCEEDED      ((uint8)90)

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

/* CanIf Module Id */
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

/* CANIF Module Id */
#define CANIF_MODULE_ID        (60U)

/*******************************************************************************
*                           API Service ID Macros                              *
*******************************************************************************/
typedef uint8 CanIf_ServiceId;
#define CANIF_GET_CONTROLLER_ERROR_STATE_SID     ((CanIf_ServiceId)0x4b)
#define CANIF_GET_PDU_MODE_SID                   ((CanIf_ServiceId)0x0a)
#define CanIf_GetControllerMode_Id               ((Can_ServiceId)0x04)
#define CanIf_CancelTransmit_Id                 ((Can_ServiceId)0x4A)
#define CanIf_TRansmit_Id                       ((Can_ServiceId)0x49)
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

#endif /* __CANIF_H__ */
