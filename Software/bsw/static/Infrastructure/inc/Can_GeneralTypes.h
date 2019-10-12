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
**  FILENAME     : Can_GeneralTypes			                                  **
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
#ifndef CAN_GENERALTYPE_H
#define CAN_GENERALTYPE_H

#include "Std_Types.h"

/* Can_ErrorStateType ENUM */
/*
   Description : Error states of a CAN controller.
*/
typedef uint8 Can_ErrorStateType ;

#define CAN_ERRORSTATE_ACTIVE  ((Can_ErrorStateType)0x00)  // The CAN controller takes fully part in communication.
#define CAN_ERRORSTATE_PASSIVE ((Can_ErrorStateType)0x01)  // The CAN controller takes part in communication, but does not send active error frames.
#define CAN_ERRORSTATE_BUSOFF  ((Can_ErrorStateType)0x02)  // The CAN controller does not take part in communication.

/*
   type : uint16
   Range : Standard : 0..0x0FF
           Extended : 0..0xFFFF
   Description: Represents the hardware object handles of a CAN hardware unit.
                For CAN hardware units with more than 255 HW objects use extended range.
*/

typedef uint16 Can_HwHandleType ;

/*
  Description : This type defines a data structure which clearly provides an Hardware Object Handle
                including its corresponding CAN Controller and therefore CanDrv as well as the specific CanId.
*/
typedef uint32 Can_IdType ;
typedef uint32 PduIdType ;

typedef struct Can_HwType {
	Can_IdType CanId ; // Standard/Extended CAN ID of CAN L-PDU
	Can_HwHandleType Hoh ; // ID of the corresponding Hardware Object Range
	uint8 ControllerId ; // ControllerId provided by CanIf clearly identify the corresponding controller
}Can_HwType;


/*
   type : uint32
   Range : Standard32Bit : 0..0x400007FF
           Extended32Bit : 0..0xDFFFFFFF
   Description : Represents the Identifier of an L-PDU. The two most significant bits specify the frame type:
                 00 CAN message with Standard CAN ID
				 01 CAN FD frame with Standard CAN ID
				 10 CAN message with Extended CAN ID
				 11 CAN FD frame with Extended CAN ID
*/


/*
   Description : This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and CanId (id) for any CAN L-SDU.
*/
typedef struct Can_PduType{
	PduIdType swPduHandle ;
	uint8 length;
	Can_IdType id ;
	uint8* sdu ;
}Can_PduType;

typedef enum CanObjectType
   {
       /*
        * Receive HOH
        */
       receive,
       /*
        * Transmit HOH
        */
       transmit
   }CanObjectType;

#endif
