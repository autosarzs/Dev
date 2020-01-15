/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)		                                    **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Can_GeneralTypes			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-09-22                                                 **
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
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef __CAN_GENERAL_TYPES_H__
#define __CAN_GENERAL_TYPES_H__

 /* Module Version 1.0.0 */
#define CAN_GENERAL_TYPES_SW_MAJOR_VERSION           (1U)
#define CAN_GENERAL_TYPES_SW_MINOR_VERSION           (0U)
#define CAN_GENERAL_TYPES_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CAN_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define CAN_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION   (3U)
#define CAN_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION   (1U)

#include "Std_Types.h"
/* AUTOSAR checking between Std_Types and Can_GeneralTypes Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CAN_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CAN_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CAN_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* 
  [SWS_Can_91013]
  States that are used by the several ControllerMode functions.
*/  
typedef uint8 Can_ControllerStateType;
#define CAN_CS_UNINIT  ((Can_ControllerStateType) 0x00U)
#define CAN_CS_STARTED ((Can_ControllerStateType) 0x01U)
#define CAN_CS_STOPPED ((Can_ControllerStateType) 0x02U)
#define CAN_CS_SLEEP   ((Can_ControllerStateType) 0x03U)

/*
  [SWS_Can_91003]
  Error states of a CAN controller.
  The CAN controller takes fully part in communication.
  The CAN controller takes part in communication, but does not send active error frames.
  The CAN controller does not take part in communication
*/
typedef uint8 Can_ErrorStateType ;
#define CAN_ERRORSTATE_ACTIVE  ((Can_ErrorStateType) 0x00U)  
#define CAN_ERRORSTATE_PASSIVE ((Can_ErrorStateType) 0x20U)
#define CAN_ERRORSTATE_BUSOFF  ((Can_ErrorStateType) 0xA0U)


/*
  [SWS_Can_00429]
  Range : Standard : 0..0x0FF
          Extended : 0..0xFFFF
  Represents the hardware object handles of a CAN hardware unit.
  For CAN hardware units with more than 255 HW objects use extended range.
*/
typedef uint16 Can_HwHandleType ;

/*
  [SWS_Can_00416]
  Range : Standard32Bit : 0..0x400007FF
          Extended32Bit : 0..0xDFFFFFFF
  Represents the Identifier of an L-PDU. The two most significant bits specify the frame type:
  00 CAN message with Standard CAN ID
  01 CAN FD frame with Standard CAN ID
  10 CAN message with Extended CAN ID
  11 CAN FD frame with Extended CAN ID
*/
typedef uint32 Can_IdType ;

/*
  [SWS_CAN_00496]
  This type defines a data structure which clearly provides an Hardware Object 
  Handle including its corresponding CAN Controller and therefore CanDrv as well as the specific CanId
  1-CanId: Standard/Extended CAN ID of CAN LPDU
  2-Hoh: ID of the corresponding Hardware Object Range
  3-ControllerId: ControllerId provided by CanIf clearly identify the corresponding controller
*/
typedef struct Can_Hw 
{
  Can_IdType CanId ; // Standard/Extended CAN ID of CAN L-PDU
  Can_HwHandleType Hoh ; // ID of the corresponding Hardware Object Range
  uint8 ControllerId ; // ControllerId provided by CanIf clearly identify the corresponding controller
}Can_HwType;



/* 
  [SWS_CanTrcv_00163]
  Operating modes of the CAN Transceiver Driver
*/
typedef uint8 CanTrcv_TrcvModeType;
#define CANTRCV_TRCVMODE_NORMAL   ((CanTrcv_TrcvModeType) 0x00U)
#define CANTRCV_TRCVMODE_SLEEP    ((CanTrcv_TrcvModeType) 0x01U)
#define CANTRCV_TRCVMODE_STANDBY  ((CanTrcv_TrcvModeType) 0x02U)

/*
  [SWS_CanTrcv_00164]
  This type shall be used to control the CAN transceiver concerning wake up events and wake up notifications.
  1-The notification for wakeup events is enabled on the addressed transceiver
  2-The notification for wakeup events is disabled on the addressed transceive
  3-A stored wakeup event is cleared on the addressed transceiver
*/
typedef uint8 CanTrcv_TrcvWakeupModeType;
#define CANTRCV_WUMODE_ENABLE   ((CanTrcv_TrcvWakeupModeType)0x00U) 
#define CANTRCV_WUMODE_DISABLE  ((CanTrcv_TrcvWakeupModeType)0x01U)
#define CANTRCV_WUMODE_CLEAR    ((CanTrcv_TrcvWakeupModeType)0x02U)

/*
  [SWS_CanTrcv_00165]
  This type denotes the wake up reason detected by the CAN transceiver in detail.
  1-Due to an error wake up reason was not detected. This value may only be reported when error was reported to DEM before.
  2-The transceiver does not support any information for the wake up reason
  3-The transceiver has detected, that the network has caused the wake up of the ECU
  4-The transceiver has detected, that the network has woken up by the ECU via a request to NORMAL mode
  5-The transceiver has detected, that the "wake up" is due to an ECU reset.
  6-The transceiver has detected, that the "wake up" is due to an ECU reset after power on
  7-The transceiver has detected a wake-up event at one of the transceiver's pins (not at the CAN bus).
  8-The transceiver has detected, that the wake up of the ECU was caused by a HW related device failure
*/
typedef uint8 CanTrcv_TrcvWakeupReasonType;
#define CANTRCV_WU_ERROR          ((CanTrcv_TrcvWakeupReasonType)0x00U)
#define CANTRCV_WU_NOT_SUPPORTED  ((CanTrcv_TrcvWakeupReasonType)0x01U)
#define CANTRCV_WU_BY_BUS         ((CanTrcv_TrcvWakeupReasonType)0x02U)
#define CANTRCV_WU_INTERNALLY     ((CanTrcv_TrcvWakeupReasonType)0x03U)
#define CANTRCV_WU_RESET          ((CanTrcv_TrcvWakeupReasonType)0x04U)
#define CANTRCV_WU_POWER_ON       ((CanTrcv_TrcvWakeupReasonType)0x05U)
#define CANTRCV_WU_BY_PIN         ((CanTrcv_TrcvWakeupReasonType)0x06U)
#define CANTRCV_WU_BY_SYSERR      ((CanTrcv_TrcvWakeupReasonType)0x07U)

typedef uint8 CanObjectType;
/**
  Receive HOH  */
#define receive      ((CanObjectType)0x00U)
/**
  Transmit HOH  */
#define transmit     ((CanObjectType)0x01U)


#endif /* __CAN_GENERAL_TYPES_H__ */
