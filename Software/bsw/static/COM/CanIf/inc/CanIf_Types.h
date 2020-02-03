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

#include "Can.h"
#include "CanIf_Cfg.h"
#include "Stub.h"

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

//******************************************************************************
// CanIf_ModuleStateType
// CANIF_UNINIT : After power-up/reset, the Can module shall be in the state CAN_UNINIT and also CANIF will be in CANIF_UNINT.
// CANIF_READY  : The function CanIf_Init shall change the module state to CANIF_READY
//******************************************************************************
typedef uint8 CanIf_ModuleStateType;
#define CANIF_UNINT			((CanIf_ModuleStateType)0x00)
#define CANIF_READY			((CanIf_ModuleStateType)0x01)

//*****************************************************************************
//  Selects the desired software filter mechanism for reception only. Each
//  implemented software filtering method is identified by this enumeration
//  number.
//  Range: 	BINARY Selects Binary Filter method.
//			INDEX Selects Index Filter method.
//			LINEAR Selects Linear Filter method.
//			TABLE Selects Table Filter method.
//	dependency: BasicCAN reception must be enabled by referenced
//	parameter CAN_HANDLE_TYPE of the CAN Driver module via
//	CANIF_HRH_HANDLETYPE_REF for at least one HRH.
//*****************************************************************************
typedef uint8 CanIfPrivateSoftwareFilterTypeType;
#define BINARY									((CanIfPrivateSoftwareFilterTypeType)0x00)
#define INDEX									((CanIfPrivateSoftwareFilterTypeType)0x01)
#define LINEAR									((CanIfPrivateSoftwareFilterTypeType)0x02)
#define TABLE									((CanIfPrivateSoftwareFilterTypeType)0x03)

//*****************************************************************************
//	This parameter is used to configure the Can_HwHandleType. The
//	Can_HwHandleType represents the hardware object handles of a CAN
//	hardware unit. For CAN hardware units with more than 255 HW objects
//	the extended range shall be used (UINT16).
//*****************************************************************************
typedef uint16 CanIfPublicHandleTypeEnumType;
#define UINT16 									((CanIfPublicHandleTypeEnumType)0xFFFF)
#define UINT8									((CanIfPublicHandleTypeEnumType)0x0FF)

/* Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
Driver module for CAN L-PDU transmission. 
Range: 	EXTENDED_CAN CAN 		frame with extended identifier (29 bits)
		EXTENDED_FD_CAN CAN FD 	frame with extended identifier (29 bits)
		STANDARD_CAN CAN 		frame with standard identifier (11 bits)
		STANDARD_FD_CAN CAN FD 	frame with standard identifier (11 bits)*/
typedef uint8 CanIfTxPduCanIdTypeType;
#define EXTENDED_CAN_TX							((CanIfTxPduCanIdTypeType)0x00U)
#define EXTENDED_FD_CAN_TX						((CanIfTxPduCanIdTypeType)0x01U)
#define STANDARD_CAN_TX							((CanIfTxPduCanIdTypeType)0x02U)
#define STANDARD_FD_CAN_TX						((CanIfTxPduCanIdTypeType)0x03U)

/* Defines the type of each transmit CAN L-PDU.
Range:	DYNAMIC 	CAN ID is defined at runtime.
		STATIC 		CAN ID is defined at compile-time. */
typedef uint8 CanIfTxPduTypeType;
#define DYNAMIC_TX_PDU									((CanIfTxPduTypeType)0x00U)
#define STATIC_TX_PDU									((CanIfTxPduTypeType)0x01U)

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
#if(CANIF_TX_PDU_TRIGGER_TRANSMIT==STD_ON)
	typedef uint8 CanIfTxPduUserTxConfirmationULType;
	#define CAN_NM_TX_CONFIRMATION							((CanIfTxPduUserTxConfirmationULType)0x00U)
	#define CAN_TP_TX_CONFIRMATION							((CanIfTxPduUserTxConfirmationULType)0x01U)
	#define CAN_TSYN_TX_CONFIRMATION						((CanIfTxPduUserTxConfirmationULType)0x02U)
	#define CDD_TX_CONFIRMATION								((CanIfTxPduUserTxConfirmationULType)0x03U)
	#define J1939NM_TX_CONFIRMATION							((CanIfTxPduUserTxConfirmationULType)0x04U)
	#define J1939TP_TX_CONFIRMATION							((CanIfTxPduUserTxConfirmationULType)0x05U)
	#define PDUR_TX_CONFIRMATION							((CanIfTxPduUserTxConfirmationULType)0x06U)
	#define XCP_TX_CONFIRMATION								((CanIfTxPduUserTxConfirmationULType)0x07U)
#endif

/* CAN Identifier of receive CAN L-PDUs used by the CAN Driver for
CAN L-PDU reception.
Range: 	EXTENDED_CAN 			CAN 2.0 or CAN FD frame with extended identifier (29 bits)
		EXTENDED_FD_CAN 		CAN FD frame with extended identifier (29 bits)
		EXTENDED_NO_FD_CAN		CAN 2.0 frame with extended identifier (29 bits)
		STANDARD_CAN 			CAN 2.0 or CAN FD frame with standard identifier (11 bits)
		STANDARD_FD_CAN 		CAN FD frame with standard identifier (11 bits)
		STANDARD_NO_FD_CAN 		CAN 2.0 frame with standard identifier (11 bits)
dependency: If CanIfRxPduDataLength > 8 then CanIfRxPduCanIdType must not be STANDARD_NO_FD_CAN or EXTENDED_NO_FD_CAN */
typedef uint8 CanIfRxPduCanIdTypeType;
#define EXTENDED_CAN_RX										((CanIfRxPduCanIdTypeType)0x00U)
#define EXTENDED_FD_CAN_RX									((CanIfRxPduCanIdTypeType)0x01U)
#if(CanIfRxPduDataLength <= 8)
	#define EXTENDED_NO_FD_CAN_RX							((CanIfRxPduCanIdTypeType)0x02U)
#endif
#define STANDARD_CAN_RX										((CanIfRxPduCanIdTypeType)0x03U)
#define STANDARD_FD_CAN_RX									((CanIfRxPduCanIdTypeType)0x04U)
#if(CanIfRxPduDataLength <= 8)
	#define STANDARD_NO_FD_CAN_RX							((CanIfRxPduCanIdTypeType)0x05U)
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
typedef uint8 CanIfRxPduUserRxIndicationULType;
#define CAN_NM_RX_INDICATION								((CanIfRxPduUserRxIndicationULType)0x00U)
#define CAN_TP_RX_INDICATION								((CanIfRxPduUserRxIndicationULType)0x01U)
#define CAN_TSYN_RX_INDICATION								((CanIfRxPduUserRxIndicationULType)0x02U)
#define CDD_RX_INDICATION									((CanIfRxPduUserRxIndicationULType)0x03U)
#define J1939NM_RX_INDICATION								((CanIfRxPduUserRxIndicationULType)0x04U)
#define J1939TP_RX_INDICATION								((CanIfRxPduUserRxIndicationULType)0x05U)
#define PDUR_RX_INDICATION									((CanIfRxPduUserRxIndicationULType)0x06U)
#define XCP_RX_INDICATION									((CanIfRxPduUserRxIndicationULType)0x07U)

/* This parameter defines the upper layer module to which the CheckTrcvWakeFlagIndication
from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	typedef uint8 CanIfDispatchUserCheckTrcvWakeFlagIndicationULType;
	#define CAN_SM_DISPATCH_CHECK_TRCV_WAKE_FLAG			((CanIfDispatchUserCheckTrcvWakeFlagIndicationULType)0x00)
	#define CDD_DISPATCH_CHECK_TRCV_WAKE_FLAG				((CanIfDispatchUserCheckTrcvWakeFlagIndicationULType)0x01)
#endif

/* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	typedef uint8 CanIfDispatchUserClearTrcvWufFlagIndicationULType;
	#define CAN_SM_DISPATCH_CLEAR_TRCV_WUF_FLAG				((CanIfDispatchUserClearTrcvWufFlagIndicationULType)0x00)
	#define CDD_DISPATCH_CLEAR_TRCV_WUF_FLAG				((CanIfDispatchUserClearTrcvWufFlagIndicationULType)0x01)
#endif

/* This parameter defines the upper layer module to which the ConfirmPnAvailability notification
from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	typedef uint8 CanIfDispatchUserConfirmPnAvailabilityULType;
	#define CAN_SM_DISPATCH_CONFIRM_PN						((CanIfDispatchUserConfirmPnAvailabilityULType)0x00)
	#define CDD_DISPATCH_CONFIRM_PN							((CanIfDispatchUserConfirmPnAvailabilityULType)0x01)
#endif

/* This parameter defines the upper layer (UL) module to which the notifications of all
ControllerBusOff events from the CAN Driver modules have to be routed via <User_ControllerBusOff>.
There is no possibility to configure no upper layer (UL) module as the provider of <User_ControllerBusOff>. */
typedef uint8 CanIfDispatchUserCtrlBusOffULType;
#define CAN_SM_DISPATCH_CTRL_BUS_OFF						((CanIfDispatchUserCtrlBusOffULType)0x00)
#define CDD_DISPATCH_CTRL_BUS_OFF							((CanIfDispatchUserCtrlBusOffULType)0x01)

/* This parameter defines the upper layer (UL) module to which the notifications of all ControllerTransition
events from the CAN Driver modules have to be routed via <User_ControllerModeIndication>. */
typedef uint8 CanIfDispatchUserCtrlModeIndicationULType;
#define CAN_SM_DISPATCH_CTRL_MODE							((CanIfDispatchUserCtrlModeIndicationULType)0x00)
#define CDD_DISPATCH_CTRL_MODE								((CanIfDispatchUserCtrlModeIndicationULType)0x01)

/* This parameter defines the upper layer (UL) module to which the notifications of all TransceiverTransition events from
the CAN Transceiver Driver modules have to be routed via <User_TrcvModeIndication>. If no UL module is configured, no upper
layer callback function will be called. */
typedef uint8 CanIfDispatchUserTrcvModeIndicationULType;
#define CAN_SM_DISPATCH_TRCV_MODE							((CanIfDispatchUserTrcvModeIndicationULType)0x00)
#define CDD_DISPATCH_TRCV_MODE								((CanIfDispatchUserTrcvModeIndicationULType)0x01)

/* This parameter defines the upper layer (UL) module to which the notifications about positive former requested
wake up sources have to be routed via <User_ValidateWakeupEvent>. If parameter CANIF_WAKEUP_CHECK_VALIDATION_API is
disabled, this parameter cannot be configured. dependency: CANIF_WAKEUP_CHECK_VALIDATION_API */
#if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT==STD_ON)
	typedef uint8 CanIfDispatchUserValidateWakeupEventULType;
	#define ECUM_DISPATCH_VALIDATE_WAKEUP_EVENT				((CanIfDispatchUserValidateWakeupEventULType)0x00)
	#define CDD_DISPATCH_VALIDATE_WAKEUP_EVENT				((CanIfDispatchUserValidateWakeupEventULType)0x01)
#endif

/*Used as mask value in combination with CanIfHrhRangeBaseId for a
masked ID range in which all CAN Ids shall pass the software filtering.
The size of this parameter is limited by
CanIfHrhRangeRxPduRangeCanIdType.*/
typedef uint8 CanIfHrhRangeRxPduRangeCanIdTypeType;
#define EXTENDED_HRH_RANGE									((CanIfHrhRangeRxPduRangeCanIdTypeType)0x00)
#define STANDARD_HRH_RANGE									((CanIfHrhRangeRxPduRangeCanIdTypeType)0x01)

typedef struct {
				/*This parameter abstracts from the CAN Driver specific parameter
				Controller. Each controller of all connected CAN Driver modules shall
				be assigned to one specific ControllerId of the CanIf. 
				Range: 0..number of configured controllers of all CAN Driver modules	*/
				uint8 CanIfCtrlId;

				/*This parameter references to the logical handle of the underlying CAN
				controller from the CAN Driver module to be served by the CAN
				Interface module. The following parameters of CanController config
				container shall be referenced by this link: CanControllerId, CanWakeupSourceRef
				Range: 0..max. number of underlying supported CAN controllers*/
				CanControllerType* CanIfCtrlCanCtrlRef;
}CanIfCtrlCfgType;

typedef struct {
				/*Reference to controller Id to which the HTH belongs to. A controller can contain one or more HTHs.*/
				CanIfCtrlCfgType* CanIfHthCanCtrlIdRef;

				/*The parameter refers to a particular HTH object in the CanDrv configuration (see CanHardwareObject 
				ECUC_Can_00324). CanIf receives the following information of the CanDrv module by this reference:
				- CanHandleType (see ECUC_Can_00323)
				- CanObjectId (see ECUC_Can_00326) */
				CanHardwareObjectType* CanIfHthIdSymRef;
}CanIfHthCfgType;

typedef struct {
				/*This parameter defines the number of CanIf Tx L-PDUs which can be buffered in one Txbuffer. If this value
				equals 0, the CanIf does not perform Txbuffering for the CanIf Tx L-PDUs which are assigned to this
				Txbuffer. If CanIfPublicTxBuffering equals False, this parameter equals 0 for all TxBuffer. If the CanHandleType
				of the referred HTH equals FULL, this parameter equals 0 for this TxBuffer. Range: 0 .. 255
				dependency: CanIfPublicTxBuffering, CanHandleType */
				uint8 CanIfBufferSize;
	
				/*Reference to HTH, that defines the hardware object or the pool of hardware objects configured for transmission.
				All the CanIf Tx L-PDUs refer via the CanIfBufferCfg and this parameter to the HTHs if TxBuffering is enabled, or
				not. Each HTH shall not be assigned to more than one buffer*/
				CanIfHthCfgType* CanIfBufferHthRef;
}CanIfBufferCfgType;

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
				CanIfTxPduCanIdTypeType CanIfTxPduCanIdType;
				
				/* ECU wide unique, symbolic handle for transmit CAN L-SDU.
				Range: 0..max. number of CantTxPduIds */
				uint32 CanIfTxPduId;
				
				/* If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
				could be configured which will pass the CanIfPnFilter.
				If there is no CanIfTxPduPnFilterPdu configured per controller,
				the corresponding controller applies no CanIfPnFilter.
				dependency: This parameter shall only be configurable if
				CanIfPublicPnSupport equals True. */
				#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
					uint8 CanIfTxPduPnFilterPdu;
				#endif
				
				/* Enables and disables transmit confirmation for each transmit CAN
				L-SDU for reading its notification status.
				True: Enabled False: Disabled
				dependency: CANIF_READTXPDU_NOTIFY_STATUS_API must be enabled.*/
				#if(CANIF_TX_PDU_READ_NOTIFY_STATUS==STD_ON)
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
				CanIfTxPduTypeType CanIfTxPduType;
				
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
					CanIfTxPduUserTxConfirmationULType CanIfTxPduUserTxConfirmationUL;
				#endif
				
				/* Configurable reference to a CanIf buffer configuration. CanIfBufferCfg */
				CanIfBufferCfgType* CanIfTxPduBufferRef;
				
				/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
				//Pdu* CanIfTxPduRef;
				will be configured in implementation */
}CanIfTxPduCfgType;

typedef struct{
				/* Lower CAN Identifier of a receive CAN L-PDU for identifier range
				definition, in which all CAN Ids are mapped to one PduId.
				Range: 0 - 536870911 */
				uint32 CanIfRxPduCanIdRangeLowerCanId;
				
				/* Upper CAN Identifier of a receive CAN L-PDU for identifier range
				definition, in which all CAN Ids are mapped to one PduId.
				Range: 0 - 536870911 */
				uint32 CanIfRxPduCanIdRangeUpperCanId;
}CanIfRxPduCanIdRangeType;

typedef struct {
				/*CAN Identifier used as base value in combination with CanIfHrhRangeMask for a masked ID range
				in which all CAN Ids shall pass the software filtering. The size of this parameter is limited by
				CanIfHrhRangeRxPduRangeCanIdType. */
				uint32  CanIfHrhRangeBaseId;
	
				/*Used as mask value in combination with CanIfHrhRangeBaseId for a masked ID range in which all CAN
				Ids shall pass the software filtering. The size of this parameter is limited by CanIfHrhRangeRxPduRangeCanIdType.*/
				uint32 CanIfHrhRangeMask;
	
				/*Lower CAN Identifier of a receive CAN L-PDU for identifier range definition, in which all CAN Ids shall
				pass the software filtering*/
				uint32 CanIfHrhRangeRxPduLowerCanId;
	
				/*Specifies whether a configured Range of CAN Ids shall only consider standard CAN Ids or extended CAN Id
				Range: 		EXTENDED All the CANIDs are of type extended only (29 bit).
							STANDARD All the CANIDs are of type standard only (11bit). */
				CanIfHrhRangeRxPduRangeCanIdTypeType CanIfHrhRangeRxPduRangeCanIdType;

				/*Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in which all CAN Ids shall
				pass the software filtering.*/
				uint32 CanIfHrhRangeRxPduUpperCanId;
}CanIfHrhRangeCfgType;

typedef struct {
				/*Reference to controller Id to which the HRH belongs to. A controller can contain one or more HRHs.*/	
				CanIfCtrlCfgType* CanIfHrhCanCtrlIdRef;

				/*The parameter refers to a particular HRH object in the CanDrv configuration*/	
				CanHardwareObjectType* CanIfHrhIdSymRef;
	
				/*Defines the parameters required for configurating multiple CANID ranges for a given same HRH.*/
				CanIfHrhRangeCfgType CanIfHrhRangeCfgObj[CANID_RANGES_NUM];
}CanIfHrhCfgType;

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
				CanIfRxPduCanIdTypeType CanIfRxPduCanIdType;
				
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
				#if(CANIF_CAN_PDU_ID_READ_DATA_API==STD_ON)
					uint8 CanIfRxPduReadData;
				#endif
				
				/* Enables and disables receive indication for each receive CAN L-SDU
				for reading its notification status.
				True: Enabled False: Disabled
				dependency: CANIF_READRXPDU_NOTIFY_STATUS_API must be enabled. */
				#if(CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS_API==STD_ON)
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
				CanIfRxPduUserRxIndicationULType CanIfRxPduUserRxIndicationUL;
				
				/* The HRH to which Rx L-PDU belongs to, is referred through this parameter.
				dependency: This information has to be derived from the CAN Driver configuration.*/
				CanIfHrhCfgType* CanIfRxPduHrhIdRef;
				
				/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
				//Pdu* CanIfRxPduRef;
				will be configured in implementation */
				
				/* Optional container that allows to map a range of CAN Ids to one PduId. */
				CanIfRxPduCanIdRangeType CanIfRxPduCanIdRangeObj;
}CanIfRxPduCfgType;

typedef struct{
				/*This container contains configuration parameters for each hardware receive object (HRH).*/
				CanIfHrhCfgType CanIfHrhCfgObj[HRH_OBj_NUM];

				/*This container contains parameters related to each HTH.*/
				CanIfHthCfgType CanIfHthCfgObj[HTH_OBj_NUM];
}CanIfInitHohCfgType;

typedef struct {
				/* Check with the Author the change i have made before comitting */
				/*	Selects the CAN Interface specific configuration setup. This type of the external data structure shall 
				contain the post build initialization data for the CAN Interface for all underlying CAN Dirvers.
				constant to CanIf_ConfigType*/
				uint8 CanIfInitCfgSet[CANIF_INIT_CFG_SET];
				
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
				
				/* This container contains the Txbuffer configuration. Multiple buffers with different sizes could be configured.
				If CanIfBufferSize (ECUC_CanIf_00834) equals 0, the CanIf Tx L-PDU only refers via this CanIfBufferCfg the
				corresponding CanIfHthCfg. */
				CanIfBufferCfgType	CanIfBufferCfgObj[BUFFERS_NUM];
				
				/* This container contains the references to the configuration setup of each underlying CAN Driver. */
				CanIfInitHohCfgType	CanIfInitHohCfgObj[CAN_DRIVER_NUM];
				
				/* This container contains the configuration (parameters) of each receive CAN L-PDU. The SHORT-NAME of
				"CanIfRxPduConfig" container itself represents the symolic name of Receive L-PDU. This L-SDU produces
				a meta data item of type CAN_ID_32. */
				CanIfRxPduCfgType	CanIfRxPduCfgObj[RX_CAN_L_PDU_NUM];
				
				/* This container contains the configuration (parameters) of a transmit CAN L-PDU. It has to be configured as
				often as a transmit CAN L-PDU is needed. The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic
				name of Transmit L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32. */
				CanIfTxPduCfgType	CanIfTxPduCfgObj[TX_CAN_L_PDU_NUM];
}CanIfInitCfgType;

typedef struct{
				/* This parameter defines the upper layer module to which the CheckTrcvWakeFlagIndication
				from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
				parameter shall not be configurable. */
				#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
					CanIfDispatchUserCheckTrcvWakeFlagIndicationULType CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;
				#endif
				
				/* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
				from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
				parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
				#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
					CanIfDispatchUserClearTrcvWufFlagIndicationULType CanIfDispatchUserClearTrcvWufFlagIndicationUL;
				#endif
				
				/* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
				from the Driver modules have to be routed. If CANIF_PUBLIC_PN_SUPPORT equals False, this
				parameter shall not be configurable. dependency: CANIF_PUBLIC_PN_SUPPORT */
				#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
					CanIfDispatchUserConfirmPnAvailabilityULType CanIfDispatchUserConfirmPnAvailabilityUL;
				#endif
				
				/* This parameter defines the upper layer (UL) module to which the notifications of all
				ControllerBusOff events from the CAN Driver modules have to be routed via <User_ControllerBusOff>.
				There is no possibility to configure no upper layer (UL) module as the provider of <User_ControllerBusOff>.
				dependency: CANIF_PUBLIC_PN_SUPPORT */
				CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserCtrlBusOffUL;
				
				/* This parameter defines the upper layer (UL) module to which the notifications of all ControllerTransition
				events from the CAN Driver modules have to be routed via <User_ControllerModeIndication>. */
				CanIfDispatchUserCtrlModeIndicationULType CanIfDispatchUserCtrlModeIndicationUL;
				
				/* This parameter defines the upper layer (UL) module to which the notifications of all TransceiverTransition
				events from	the CAN Transceiver Driver modules have to be routed via <User_TrcvModeIndication>. If no UL module is configured, no upper	layer callback function will be called. */
				CanIfDispatchUserTrcvModeIndicationULType CanIfDispatchUserTrcvModeIndicationUL;
				
				/* This parameter defines the upper layer (UL) module to which the notifications about positive former requested
				wake up sources have to be routed via <User_ValidateWakeupEvent>. If parameter CANIF_WAKEUP_CHECK_VALIDATION_API is disabled, this parameter cannot be configured. dependency: CANIF_WAKEUP_CHECK_VALIDATION_API */
				#if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT==STD_ON)
					CanIfDispatchUserValidateWakeupEventULType CanIfDispatchUserValidateWakeupEventUL;
				#endif
}CanIfDispatchCfgType;

typedef struct {
				/*Description Reference to the Init Hoh Configuration*/
				CanIfInitHohCfgType* CanIfCtrlDrvInitHohConfigRef;

				/*CAN Interface Driver Reference.
				This reference can be used to get any information (Ex. Driver Name, Vendor ID) from
				the CAN driver. The CAN Driver name can be derived from the ShortName of the CAN driver module.*/
				CanGeneralType* CanIfCtrlDrvNameRef;

				/*This container contains the configuration (parameters) of an adressed CAN controller by
				an underlying CAN Driver module. This container is configurable per CAN controller.*/	
				CanIfCtrlCfgType CanIfCtrlCfgObj;//To Do: It should be CanIfCtrlCfgType CanIfCtrlCfgObj[USED_CONTROLLERS_NUMBER];
}CanIfCtrlDrvCfgType;

typedef struct {
				/*This parameter abstracts from the CAN Transceiver Driver specific parameter Transceiver.
				Each transceiver of all connected CAN Transceiver Driver modules shall be assigned to one
				specific TransceiverId of the CanIf.
				Range: 0..number of configured transceivers of all CAN Transceiver Driver modules*/
				uint8 CanIfTrcvId;

				/*This parameter references to the logical handle of the underlying CAN transceiver from the
				CAN transceiver driver module to be served by the CAN Interface module.
				Range: 0..max. number of underlying supported CAN transceivers*/
				CanTrcvChannelType* CanIfTrcvCanTrcvRef;
}CanIfTrcvCfgType;

typedef struct {
				/*This container contains the configuration (parameters) of one addressed CAN transceiver by the underlying CAN
				Transceiver Driver module. For each CAN transceiver a seperate instance of this container has to be provided. */
				CanIfTrcvCfgType CanIfTrcvCfgObj[CAN_TRANSCEIVER_NUM];
}CanIfTrcvDrvCfgType;

typedef struct {

				/*Configuration parameters for all the underlying CAN Driver modules are aggregated under this container.
				For each CAN Driver module a seperate instance of this container has to be provided.*/
				CanIfCtrlDrvCfgType 	CanIfCtrlDrvCfgObj[CAN_DRIVER_NUM];
				
				/*Callback functions provided by upper layer modules of the CanIf. The callback functions defined in this
				container are common to all configured CAN Driver / CAN Transceiver Driver modules.*/
				CanIfDispatchCfgType	CanIfDispatchCfgObj;
								
				/*This container contains the init parameters of the CAN Interface.*/
				CanIfInitCfgType		CanIfInitCfgObj;
				
				/* This parameter is used to configure the Can_HwHandleType. The
				Can_HwHandleType represents the hardware object handles of a CAN
				hardware unit. For CAN hardware units with more than 255 HW objects
				the extended range shall be used (UINT16). */
				CanIfPublicHandleTypeEnumType CanIfPublicHandleTypeEnum;
				
				/*Selects the desired software filter mechanism for reception only. 
				Each implemented software filtering method is identified by this enumeration number.
				Range: Types implemented software filtering methods
				Range: 	BINARY 	Selects Binary Filter method.
						INDEX 	Selects Index Filter method.
						LINEAR 	Selects Linear Filter method.
						TABLE 	Selects Table Filter method.*/
				CanIfPrivateSoftwareFilterTypeType  CanIfPrivateSoftwareFilterType;

				/*This container contains the configuration (parameters) of all addressed CAN transceivers by each underlying CAN
				Transceiver Driver module. For each CAN transceiver Driver a seperate instance of this container shall be provided.*/            
				CanIfTrcvDrvCfgType		CanIfTrcvDrvCfgObj[CAN_TRANSCEIVER_NUM];   
}CanIf_ConfigType;


#endif /*__CANIF_TYPES_H__*/
