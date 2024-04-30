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
**  FILENAME     : CanIf_Types			                                      **
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
#ifndef __CANIF_TYPES_H__
#define __CANIF_TYPES_H__

/* Module Version 1.0.0 */
#define CANIF_TYPES_SW_MAJOR_VERSION           (1U)
#define CANIF_TYPES_SW_MINOR_VERSION           (0U)
#define CANIF_TYPES_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CANIF_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define CANIF_TYPES_AR_RELEASE_MINOR_VERSION   (3U)
#define CANIF_TYPES_AR_RELEASE_PATCH_VERSION   (1U)

#include "ComStack_Types.h"
/* AUTOSAR checking between ComStack_Types and CanIf_Types Modules */
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of ComStack_Types.h does not match the expected version"
#endif

#include "Can_GeneralTypes.h"
/* AUTOSAR checking between Can_GeneralTypes and CanIf_Types Modules */
#if ((CAN_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Can_GeneralTypes.h does not match the expected version"
#endif

#include "Std_Types.h"
/* AUTOSAR checking between Std_Types and CanIf_Types Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/*
	[SWS_CANIF_00144]
	This type defines a data structure for the post build parameters of the CAN
	interface for all underlying CAN drivers. At initialization the CanIf gets a
	pointer to a structure of this type to get access to its configuration data, which
	is necessary for initialization.
	The contents of the initialization data structure are CAN interface specific	
*/
typedef struct CanIf_Config
{

}CanIf_ConfigType;

/*
	[SWS_CANIF_00137]
	The PduMode of a channel defines its transmit or receive activity.
	Communication direction (transmission and/or reception) of the channel can
	be controlled separately or together by upper layers.
	CANIF_OFFLINE: Transmit and receive path of the corresponding channel are disabled => no communication mode
	CANIF_TX_OFFLINE: Transmit path of the corresponding channel is disabled. The receive path is enabled.
	CANIF_TX_OFFLINE_ACTIVE: Transmit path of the corresponding channel is in offline active mode (see SWS_CANIF_00072). 
	                         The receive path is disabled. This mode requires CanIfTxOfflineActiveSupport = TRUE
	CANIF_ONLINE: Transmit and receive path of the corresponding channel are enabled => full operation mode
*/
typedef uint8 CanIf_PduModeType;
#define CANIF_OFFLINE            ((CanIf_PduModeType) 0x00U)
#define CANIF_TX_OFFLINE         ((CanIf_PduModeType) 0x01U)
#define CANIF_TX_OFFLINE_ACTIVE  ((CanIf_PduModeType) 0x02U)
#define CANIF_ONLINE             ((CanIf_PduModeType) 0x03U)

/*
	[SWS_CANIF_00201]
	Return value of CAN L-PDU notification status
	CANIF_NO_NOTIFICATION: No transmit or receive event occurred for the requested L-PDU
	CANIF_TX_RX_NOTIFICATION: The requested Rx/Tx CAN L-PDU was successfully transmitted or received.
*/
typedef uint8 CanIf_NotifStatusType;
#define CANIF_NO_NOTIFICATION    ((CanIf_NotifStatusType) 0x00U)
#define CANIF_TX_RX_NOTIFICATION ((CanIf_NotifStatusType) 0x01U)

#endif /*__CANIF_TYPES_H__*/
