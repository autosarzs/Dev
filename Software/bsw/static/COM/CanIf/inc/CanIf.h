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


/*******************************************************************************
 *                           API Service ID Macros                             *
********************************************************************************/
#define CANIF_GET_CONTROLLER_ERROR_STATE_SID                   ((uint8)0x4b)

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


#endif /* __CANIF_H__ */