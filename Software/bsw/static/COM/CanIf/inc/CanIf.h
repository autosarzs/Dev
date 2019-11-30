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


typedef uint8 CanIfWakeupSupportType;
#define CONTROLLER    ((CanIfWakeupSupportType)0x0)
#define NO_WAKEUP     ((CanIfWakeupSupportType)0x1)
#define TRANSCEIVER   ((CanIfWakeupSupportType)0x2)

typedef uint8 CanIfSoftwareFilterType;
#define BINARY    ((CanIfSoftwareFilterType)0x0)
#define INDEX     ((CanIfSoftwareFilterType)0x1)
#define LINEAR    ((CanIfSoftwareFilterType)0x2)
#define TABLE     ((CanIfSoftwareFilterType)0x3)

typedef uint8 CanIfCanTxPduType;
#define DYNAMIC    ((CanIfCanTxPduType)0x0)
#define STATIC     ((CanIfCanTxPduType)0x1)

typedef uint8 CanIfTxPduIdCanIdType
#define EXTENDED_CAN    ((CanIfTxPduIdCanIdType)0x0)
#define STANDARD_CAN    ((CanIfTxPduIdCanIdType)0x1)

typedef uint8 CanIfTxUserType
#define CAN_NM     ((CanIfTxUserType)0x0)
#define CAN_TP     ((CanIfTxUserType)0x1)
#define PDUR       ((CanIfTxUserType)0x2)

typedef uint8 CanIfRxPduIdCanIdType
#define EXTENDED_CAN    ((CanIfRxPduIdCanIdType)0x0)
#define STANDARD_CAN    ((CanIfRxPduIdCanIdType)0x1)

typedef uint8 CanIfRxUserType
#define CAN_NM     ((CanIfRxUserType)0x0)
#define CAN_TP     ((CanIfRxUserType)0x1)
#define PDUR       ((CanIfRxUserType)0x2)

typedef uint8 CanIfHthType
#define BASIC_CAN    ((CanIfHthType)0x0)
#define FULL_CAN     ((CanIfHthType)0x1)

typedef uint8 CanIfHrhType
#define BASIC_CAN     ((CanIfHrhType)0x0)
#define FULL_CAN      ((CanIfHrhType)0x1)

typedef uint8 CanIfRxPduRangeCanIdType
#define EXTENDED_CAN    ((CanIfRxPduRangeCanIdType)0x0)
#define STANDARD_CAN    ((CanIfRxPduRangeCanIdType)0x1)


typedef struct {
	
	/***************************************************************************************************************************
	*															Included Containers 
	****************************************************************************************************************************/
				
				/*This container contains the configuration (parameters) of all addressed CAN controllers by each underlying CAN driver.*/
				CanIfControllerConfig CanIfControllerCfg;
				
				/*Callout functions with respect to the upper layers. This callout functions
				defined in this container are common to all configured underlying CAN Drivers / CAN Transceiver Drivers.*/

				CanIfDispatchCfg CanIfDispatchConfig;
				
				/*Configuration parameters for all the underlying CAN drivers are aggregated under this container*/
				
				CanIfDriverConfig  CanIfDriverCfg;
				
				/*This container contains the init parameters of the CAN Interface.*/
				
				CanIfInitCfg	CanIfInitConfiguration;
				
				/*This container contains the private configuration (parameters) of the CAN Interface.*/
				
				CanIfPrivateCfg   	CanIfPrivateConfiguration;
				
				/*This container contains the public configuration (parameters) of the CAN Interface.*/
				
				CanIfPublicCfg		CanIfPublicConfiguration;
				
				/*This container contains the configuration (parameters) of all addressed CAN transceivers by each underlying 
				CAN Transceiver Driver*/
				
				CanIfPublicCfg      CanIfTransceiverDrvConfig;

}CanIf;


typedef struct {
				/*Selects the desired software filter mechanism for reception only. 
				Each implemented software filtering method is identified by this enumeration number.
				Range: Types implemented software filtering methods
				Range: 	BINARY 	Selects Binary Filter method.
						INDEX 	Selects Index Filter method.
						LINEAR 	Selects Linear Filter method.
						TABLE 	Selects Table Filter method.*/
				CanIfPrivateSoftwareFilterType  CanIfPrivateSoftwareFilter;
}CanIfPrivateCfg;

typedef struct {
				/* Defines header files for callback functions which shall be included in
				case of CDDs. Range of characters is 1.. 32. 
				Type: EcucStringParamDef*/
				uint8 CanIfPublicCddHeaderFileStr[CanIfPublicCddHeaderFile];
}CanIfPublicCfg;
 
typedef struct {
				/* Check with the Author the change i have made before comitting */
				/*	Selects the CAN Interface specific configuration setup. This type of the external data structure shall 
				contain the post build initialization data for the CAN Interface for all underlying CAN Dirvers.
				constant to CanIf_ConfigType*/
				uint8 CanIfInitCfgSetStr[CanIfInitCfgSet];
				
				/* Maximum total size of all Tx buffers. This parameter is needed only in
				case of post-build loadable implementation using static memory
				allocation.
				Range: 0..18446744073709551615 */
				uint64 CanIfMaxBufferSize;
				
				/* Maximum number of Pdus. This parameter is needed only in case of
				post-build loadable implementation using static memory allocation.
				Range: 0..18446744073709551615 */
				uint64 CanIfMaxRxPduCfg;
				
				/* Maximum number of Pdus. This parameter is needed only in case of
				post-build loadable implementation using static memory allocation.
				Range: 0..18446744073709551615 */
				uint64 CanIfMaxTxPduCfg;
				
				/**************************************************************************************************************
																Included Containers 
				**************************************************************************************************************/
				
				/* This container contains the Txbuffer configuration.
				Multiple buffers with different sizes could be configured.
				If CanIfBufferSize (ECUC_CanIf_00834) equals 0, the
				CanIf Tx L-PDU only refers via this CanIfBufferCfg the
				corresponding CanIfHthCfg. */
				CanIfBufferCfg	CanIfBufferConfig;
				
				/* This container contains the references to the
				configuration setup of each underlying CAN Driver. */
				CanIfInitHohCfg	CanIfInitHohConfig;
				
				/* This container contains the configuration (parameters)
				of each receive CAN L-PDU.
				The SHORT-NAME of "CanIfRxPduConfig" container
				itself represents the symolic name of Receive L-PDU.
				This L-SDU produces a meta data item of type
				CAN_ID_32. */
				CanIfRxPduCfg	CanIfRxPduConfig;
				
				/* This container contains the configuration (parameters)
				of a transmit CAN L-PDU. It has to be configured as
				often as a transmit CAN L-PDU is needed.
				The SHORT-NAME of "CanIfTxPduConfig" container
				represents the symolic name of Transmit L-PDU.
				This L-SDU consumes a meta data item of type
				CAN_ID_32. */
				CanIfTxPduCfg	CanIfTxPduConfig;
				
}CanIfInitCfg;

typedef struct {
				/* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for
				CAN L-PDU transmission. Range: 11 Bit For Standard CAN Identifier
				... 29 Bit For Extended CAN identifier
				The CAN Identifier may be omitted for dynamic transmit L-PDUs.
				Range: 0 .. 536870911 */
				uint32 CanIfTxPduCanId;
				
				/* Identifier mask which denotes relevant bits in the CAN Identifier. This
				parameter may be used to keep parts of the CAN Identifier of dynamic
				transmit L-PDUs static. Range: 11 bits for Standard CAN Identifier, 29
				bits for Extended CAN Identifier.
				Range: 0 .. 536870911 */
				uint32 CanIfTxPduCanIdMask;
				
				/* Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
				Driver module for CAN L-PDU transmission. 
				Range: 	EXTENDED_CAN CAN 		frame with extended identifier (29 bits)
						EXTENDED_FD_CAN CAN FD 	frame with extended identifier (29 bits)
						STANDARD_CAN CAN 		frame with standard identifier (11 bits)
						STANDARD_FD_CAN CAN FD 	frame with standard identifier (11 bits) */
				uint8 CanIfTxPduCanIdType;
				
				/* ECU wide unique, symbolic handle for transmit CAN L-SDU.
				Range: 0..max. number of CantTxPduIds */
				uint32 CanIfTxPduId;
				
				/* If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
				could be configured which will pass the CanIfPnFilter.
				If there is no CanIfTxPduPnFilterPdu configured per controller,
				the corresponding controller applies no CanIfPnFilter.
				dependency: This parameter shall only be configurable if
				CanIfPublicPnSupport equals True. */
				#if(CanIfPublicPnSupport==STD_ON)
					uint8 CanIfTxPduPnFilterPdu;
				#endif
				
				/* Enables and disables transmit confirmation for each transmit CAN
				L-SDU for reading its notification status.
				True: Enabled False: Disabled
				dependency: CANIF_READTXPDU_NOTIFY_STATUS_API must be enabled.*/
				#if(CANIF_READTXPDU_NOTIFY_STATUS_API==STD_ON)
				uint8 CanIfTxPduReadNotifyStatus;
				#endif
				
				/* Determines if or if not CanIf shall use the trigger transmit API for this PDU.
				dependency: If CanIfTxPduTriggerTransmit is TRUE then CanIfTxPduUserTxConfirmationUL 
				has to be either PDUR or CDD and CanIfTxPduUserTriggerTransmitName has to be specified accordingly */
				uint8 CanIfTxPduTriggerTransmit;
				
				/* Enables/disables truncation of PDUs that exceed the configured size. */
				uint8 CanIfTxPduTruncation;
				
				/* Defines the type of each transmit CAN L-PDU.
				Range:	DYNAMIC 	CAN ID is defined at runtime.
						STATIC 		CAN ID is defined at compile-time. */
				uint8 CanIfTxPduType;
				
				/* This parameter defines the upper layer (UL) module to which the confirmation of
				the successfully transmitted CANTXPDUID has to be routed via the <User_TxConfirmation>.
				This <User_TxConfirmation> has to be invoked when the confirmation of the configured CANTXPDUID
				will be received by a Tx confirmation event from the CAN Driver module.
				If no upper layer (UL) module is configured, no <User_TxConfirmation> has to be called in case of
				a Tx confirmation event of the CANTXPDUID from the CAN Driver module.
				Range:	CAN_NM		CAN NM
						CAN_TP 		CAN TP
						CAN_TSYN	Global Time Synchronization over CAN
						CDD 		Complex Driver
						J1939NM 	J1939Nm
						J1939TP 	J1939Tp
						PDUR 		PDU Router
						XCP 		Extended Calibration Protocol 
				Note: If CanIfTxPduTriggerTransmit is not specified or FALSE, no upper
				layer modules have to be configured for Trigger Transmit. Therefore,
				<User_TriggerTransmit>() will not be called and CanIfTxPduUserTxConfirmationUL
				as well as CanIfTxPduUserTriggerTransmitName need not to be configured. */
				#if(CANIF_TXPDU_TRIGGERTRANSMIT==STD_ON)
					uint8 CanIfTxPduUserTxConfirmationUL;
				#endif
				
				/* Configurable reference to a CanIf buffer configuration. CanIfBufferCfg */
				CanIfBufferCfg* CanIfTxPduBufferRef;
				
				/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
				//Pdu* CanIfTxPduRef;
				will be configured in implementation */
}CanIfTxPduCfg;

typedef struct{
				/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface.
				Exa: Software Filtering. This parameter is used if exactly one Can
				Identifier is assigned to the Pdu. If a range is assigned then the
				CanIfRxPduCanIdRange parameter shall be used.
				Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier */
				uint32 CanIfRxPduCanId;
				
				/* Identifier mask which denotes relevant bits in the CAN Identifier. This
				parameter defines a CAN Identifier range in an alternative way to
				CanIfRxPduCanIdRange. It identifies the bits of the configured CAN
				Identifier that must match the received CAN Identifier. Range: 11 bits
				for Standard CAN Identifier, 29 bits for Extended CAN Identifier. */
				uint32 CanIfRxPduCanIdMask;
				
				/* CAN Identifier of receive CAN L-PDUs used by the CAN Driver for
				CAN L-PDU reception.
				Range: 	EXTENDED_CAN 			CAN 2.0 or CAN FD frame with extended identifier (29 bits)
						EXTENDED_FD_CAN 		CAN FD frame with extended identifier (29 bits)
						EXTENDED_NO_FD_CAN		CAN 2.0 frame with extended identifier (29 bits)
						STANDARD_CAN 			CAN 2.0 or CAN FD frame with standard identifier (11 bits)
						STANDARD_FD_CAN 		CAN FD frame with standard identifier (11 bits)
						STANDARD_NO_FD_CAN 		CAN 2.0 frame with standard identifier (11 bits) */
				uint8 CanIfRxPduCanIdType;
				
				/* Data length of the received CAN L-PDUs used by the CAN Interface.
				This information is used for Data Length Check. Additionally it might
				specify the valid bits in case of the discrete DLC for CAN FD L-PDUs > 8 bytes.
				The data area size of a CAN L-PDU can have a range from 0 to 64 bytes. */
				uint8 CanIfRxPduDataLength;
				
				/* ECU wide unique, symbolic handle for receive CAN L-SDU. It shall
				fulfill ANSI/AUTOSAR definitions for constant defines. Range: 0..max. number of defined CanRxPduIds
				Range: 0 - 4294967295 */
				uint32 CanIfRxPduId;
				
				/* Enables and disables the Rx buffering for reading of received L-SDU
				data. True: Enabled False: Disabled
				dependency: CANIF_CANPDUID_READDATA_API must be enabled */
				#if(CANIF_CANPDUID_READDATA_API==STD_ON)
					uint8 CanIfRxPduReadData;
				#endif
				
				/* /* Enables and disables receive indication for each receive CAN L-SDU
				for reading its notification status.
				True: Enabled False: Disabled
				dependency: CANIF_READRXPDU_NOTIFY_STATUS_API must be enabled. */ */
				#if(CanIfPublicReadRxPduNotifyStatusApi==STD_ON)
					uint8 CanIfRxPduReadNotifyStatus;
				#endif
				
				/* This parameter defines the upper layer (UL) module to which the indication of
				the successfully received CANRXPDUID has to be routed via <User_RxIndication>.
				This <User_RxIndication> has to be invoked when the indication of the configured CANRXPDUID
				will be received by an Rx indication event from the CAN Driver module.
				If no upper layer (UL) module is configured, no <User_RxIndication> has to be called in case of
				an Rx indication event of the CANRXPDUID from the CAN Driver module.
				Range:	CAN_NM		CAN NM
						CAN_TP 		CAN TP
						CAN_TSYN	Global Time Synchronization over CAN
						CDD 		Complex Driver
						J1939NM 	J1939Nm
						J1939TP 	J1939Tp
						PDUR 		PDU Router
						XCP 		Extended Calibration Protocol 
				Note: If receive indications are not necessary or no upper layer modules
				are configured for receive indications and thus <User_RxIndication>()
				shall not be called, CANIF_RXPDU_USERRXINDICATION_UL and
				CANIF_RXPDU_USERRXINDICATION_NAME need not to be configured. */
				uint8 CanIfRxPduUserRxIndicationUL;
				
				/* The HRH to which Rx L-PDU belongs to, is referred through this parameter.
				dependency: This information has to be derived from the CAN Driver configuration.*/
				CanIfHrhCfg* CanIfRxPduHrhIdRef;
				
				/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
				//Pdu* CanIfRxPduRef;
				will be configured in implementation */
}CanIfRxPduCfg;

typedef struct{
				/* Lower CAN Identifier of a receive CAN L-PDU for identifier range
				definition, in which all CAN Ids are mapped to one PduId.
				Range: 0 - 536870911 */
				uint32 CanIfRxPduCanIdRangeLowerCanId;
				
				/* Upper CAN Identifier of a receive CAN L-PDU for identifier range
				definition, in which all CAN Ids are mapped to one PduId.
				Range: 0 - 536870911 */
				uint32 CanIfRxPduCanIdRangeUpperCanId;
}CanIfRxPduCanIdRange;

typedef struct{
				/* This parameter defines the upper layer module to which the CheckTrcvWakeFlagIndication
				from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
				parameter shall not be configurable. */
				#if(CanIfPublicPnSupport==STD_ON)
					uint8 CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;
				#endif
				
				/* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
				from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
				parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
				#if(CanIfPublicPnSupport==STD_ON)
					uint8 CanIfDispatchUserClearTrcvWufFlagIndicationUL;
				#endif
				
				/* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
				from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
				parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
				#if(CanIfPublicPnSupport==STD_ON)
					uint8 CanIfDispatchUserConfirmPnAvailabilityUL;
				#endif
				
				/* This parameter defines the upper layer (UL) module to which the notifications of all
				ControllerBusOff events from the CAN Driver modules have to be routed via <User_ControllerBusOff>.
				There is no possibility to configure no upper layer (UL) module as the provider of <User_ControllerBusOff>.
				dependency: CANIF_PUBLIC_PN_SUPPORT */
				uint8 CanIfDispatchUserCtrlBusOffUL;
				
				/* This parameter defines the upper layer (UL) module to which the notifications of all ControllerTransition
				events from the CAN Driver modules have to be routed via <User_ControllerModeIndication>. */
				uint8 CanIfDispatchUserCtrlModeIndicationUL;
				
				/* This parameter defines the upper layer (UL) module to which the notifications about positive former requested
				wake up sources have to be routed via <User_ValidateWakeupEvent>. If parameter CANIF_WAKEUP_CHECK_VALIDATION_API is disabled, this parameter cannot be configured. dependency: CANIF_WAKEUP_CHECK_VALIDATION_API */
				#if(CanIfPublicWakeupCheckValidSupport==STD_ON)
					uint8 CanIfDispatchUserValidateWakeupEventUL;
				#endif
}CanIfDispatchCfg;

typedef struct {
				uint8 CanIfDispatchUserCheckTrcvWakeFlagIndicationName;
				
				/* Selects support of Partial Network features in CanIf.
					True: Enabled
					False: Disabled */
				uint8 CanIfPublicPnSupport;
				
				/*Name of target BusOff notification services to target upper layers (PduRouter, CanNm, CanTp and ComplexDeviceDrivers).*/

				//FunctionNameDef CanIfBusOffNotification
				

				/*Name of target wakeup notification services to target upper layers (PduRouter, CanNm, CanTp and ComplexDeviceDrivers). 
				If parameter is 0 no call-out function is configured.*/
				
				// FunctionNameDef CanIfWakeupNotification


				/*Name of target wakeup validation notification services to target upper layers (ECU State Manager).
				If parameter is 0 no call-out function is configured.*/

				//FunctionNameDef CanIfWakeupValidNotification
				
}CanIfDispatchCfg;
 

typedef struct {
	
				/*Enumeration: Enables wakeup support and defines the source device of a wakeup event.*/
				CanIfWakeupSupportType CanIfWakeupSupport;
	
	
				/*Logical handle of the underlying CAN controller to be served by the CAN Interface.
				Range: 0..max. number of underlying supported
				Scope ECU*/
				CanController  *CanIfControllerIdRef;	
	
				/*Refers to the CAN Driver Name to which the controller belongs to. 
				This parameter refers to CanIfDriverConfig container.*/
				CanIfDriverConfig	CanIfDriverNameRef;
	
				/*Reference to the Init Controller Configuration.*/
				CanIfInitControllerConfig * CanIfInitControllerRef ;   
				
}CanIfControllerConfig;
	
	
typedef struct {
	

				/*Selects whether BusOff indication notification is supported. True: Enabled False: Disabled*/
				
				bool CanIfBusoffNotification;


				/*Selects whether receive indication notification is supported. True: Enabled False: Disabled*/
				
				bool CanIfReceiveIndication;
 
				
				/*Selects whether transmit cancellation is supported. True: Enabled False: Disabled*/
				
				bool CanIfTransmitCancellation;


				/*Selects whether transmit confirmation notification is supported.*/
				
				bool CanIfTxConfirmation;

				/*Selects whether wakeup indication notification is supported. True: Enabled False: Disabled time
				 *scope: ECU*/

				bool CanIfWakeupNotification;


				/*CAN Interface Driver Reference. This reference can be used to get any information (Ex. Driver Name, Vendor ID)
				from the CAN driver. The CAN Driver name can be derived from the ShortName of the CAN driver module.*/

				CanGeneral *CanIfDriverNameRef;


				/*Reference to the Init Hoh Configuration*/		
				CanIfInitHohConfig *CanIfInitHohConfigRef;

}CanIfDriverConfig;


typedef struct {
	
				/*Selects whether wakeup indication notification is supported. True: Enabled*/
					
				bool 	CanIfTrcvWakeupNotification;
	
				/*Logical handle of the underlying CAN transceiver to be served by the CAN Interface.*/
	
				CanTrcvChannel *CanIfTrcvIdRef;
	
}CanIfTransceiverDrvConfig;

typedef struct {
	
				/*ECU wide unique, symbolic handle for transmit CAN L-PDU. 
				*The CanIfCanTxPduId is configurable at pre-compile and post-built time.
				*Range: 0..max. number of CantTxPduIds
				scope: ECU */
				
				unit8	CanIfCanTxPduId;  															/*Symbolic Name generated for this parameter*/


				/*CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission.
				*Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier*/
				
				uint8 CanIfCanTxPduIdCanId;
	
	
				/*Data length code (in bytes) of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission. 
				The data area size of a CAN L-Pdu can 
					have a range from 0 to 8 bytes.*/
	
				float64 CanIfCanTxPduIdDlc;
	
				/*Defines the type of each transmit CAN L-PDU.*/
				
				CanIfCanTxPduType CanIfCanTxPdu;
	
	
				/*Enables and disables transmit confirmation for each transmit CAN L-PDU for reading its notification status. 
				True: Enabled False: Disabled*/
				
				bool 	CanIfReadTxPduNotifyStatus;
	
				/*CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission.*/
	
				CanIfTxPduIdCanIdType CanIfTxPduIdCanId;
	
				/*This parameter defines the type of the transmit confirmation call-out called to the corresponding 
				upper layer the used TargetTxPduId belongs to.*/
	
				CanIfTxUserType CanIfTxUser;
	
	
				
				
				/* Name of target confirmation services totarget upper layers (PduR, CanNm and CanTp.
				If parameter is not configured then no call-out function is provided by the upper layer for this Tx L-PDU.*/
				
				// FunctionNameDef CanIfUserTxConfirmation      
			
			
				
				/*Handle, that defines the hardware object or the pool of hardware objects configured for transmission.
				The parameter refers HTH Id, to which the L-PDU belongs to.*/
	
				CanIfHthConfig * CanIfCanTxPduHthRef;
	
	
				/*Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.*/
				
				Pdu *PduIdRef;
	
	
	
}CanIfTxPduConfig;

typedef struct {
	/*
				CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa: Software Filtering.
				Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier*/
									
				uint32	CanIfCanRxPduCanId;
				
				/*Data Length code of received CAN L-PDUs used by the CAN Interface. Exa: DLC check.	
				The data area size of a CAN L-PDU can have a range from 0 to 8 bytes.*/
	
				float64	CanIfCanRxPduDlc;

				/*ECU wide unique, symbolic handle for receive CAN L-PDU. The CanRxPduId is configurable at pre-compile and	post-built time. 
				It shall fulfillANSI/AUTOSAR definitions for constant defines.
				Range: 0..max. number of defined CanRxPduIds*/	
				
				uint8	CanIfCanRxPduId;
	
				/*Enables and disables the Rx buffering for reading of received L-PDU data.
				True: Enabled False: Disabled*/
				
				bool	CanIfReadRxPduData;
	
				/*Enables and disables receive indication for each receive CAN L-PDU for reading its' notification status. 
				True: Enabled False: Disabled*/
				
				bool CanIfReadRxPduNotifyStatus;
	
				/*CAN Identtifier of receive CAN L-PDUs used by the CAN Driver for CAN L-PDU reception.*/
				
				CanIfRxPduIdCanIdType CanIfRxPduIdCanId;
				
				/*This parameter defines the type of the receive indication 
	     			call-outs called to the corresponding upper layer the used TargetRxPduId belongs to.*/
	
				CanIfRxUserType CanIfRxUser;
	
				
				
				/*Name of target indication services to target 
				upper layers (PduRouter, CanNm, CanTp and ComplexDeviceDrivers). 
				If parameter is 0 no call-out function is configured.*/
				
				//FunctionNameDef CanIfUserRxIndication 

				
				
				/*The HRH to which Rx L-PDU belongs to, is referred through this parameter.*/

				CanIfHrhConfig CanIfCanRxPduHrhRef;
	
	
				/*Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.*/
	
				Pdu PduIdRef;
	
	
}CanIfRxPduConfig;


typedef struct {
				
				/*References the corresponding CAN Controller configuration setup of the corresponding CAN Driver*/
	
				CanController * CanIfControllerRefConfigSet;

}CanIfInitControllerConfig;


typedef struct {
				/*Selects the CAN Interface specific configuration setup. 
				This type of external data structure shall contain the post build initialization data for the CAN Interface
				for all underlying CAN Drivers.*/
				
				CanConfigSet * CanIfRefConfigSet;
				
	/***************************************************************************************************************************
	*															Included Containers 
	****************************************************************************************************************************/
				
				/*This container contains configuration parameters for each hardware receive object (HRH).*/
				
				CanIfHrhConfig  CanIfHrhCfg;
				
				/*This container contains parameters related to each HTH.*/
				
				CanIfHthConfig CanIfHthCfg;
				
}CanIfInitHohConfig;


/*********************************************************************************************************************************/
typedef struct {

				/*Transmission method of the corresponding HTH.*/
				
				CanIfHthType CanIfHth;
				
				/*Reference to controller Id to which the HTH belongs to. A controller can contain one or more HTHs.*/

				CanIfControllerConfig * CanIfCanControllerIdRef;
				
				/*The parameter refers to a particular HTH object in the CAN Driver Module configuration.
				The HTH id is unique in a given CAN Driver.
				The HTH Ids are defined in the CAN Driver Module and hence it is derived from CAN Driver Configuration.*/
				
				CanHardwareObject * CanIfHthIdSymRef

}CanIfHthConfig

typedef struct {
				
				
				/*Defines the HRH type i.e, whether its a BasicCan or FullCan. 
				If BasicCan is configured, software filtering is enabled*/

				CanIfHrhType CanIfHrh;
				
				/*Selects the hardware receive objects by using the HRH range/list from CAN Driver configuration to define,
				for which HRH a software filtering has to be performed at during receive processing. 
				True: Software filtering is enabled False: Software filtering is enabled*/
 
				bool CanIfSoftwareFilterHrh;
 
				/*Reference to controller Id to which the HRH belongs to. A controller can contain one or more HRHs.*/
				
				CanIfControllerConfig *CanIfCanControllerHrhIdRef;
				
				
				/*The parameter refers to a particular HRH object in the CAN Driver Module configuration.
				The HRH id is unique in a given CAN Driver. The HRH Ids are defined in the CAN Driver Module and hence
				it is derived from CAN Driver Configuration.*/
				
				CanHardwareObject *CanIfHrhIdSymRef;
				
	/***************************************************************************************************************************
	*															Included Containers 
	****************************************************************************************************************************/
	
				/*Defines the parameters required for configuraing multiple CANID ranges for a given same HRH.*/
				
				CanIfHrhRangeConfig CanIfHrhRangeCfg;
				
}CanIfHrhConfig;









#endif /* __CANIF_H__ */