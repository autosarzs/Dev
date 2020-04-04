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
typedef uint8 CanIfTxPduUserTxConfirmationULType;
#define CAN_NM							((CanIfTxPduUserTxConfirmationULType)0x00U)
#define CAN_TP							((CanIfTxPduUserTxConfirmationULType)0x01U)
#define CAN_TSYN						((CanIfTxPduUserTxConfirmationULType)0x02U)
#define CDD								((CanIfTxPduUserTxConfirmationULType)0x03U)
#define J1939NM							((CanIfTxPduUserTxConfirmationULType)0x04U)
#define J1939TP							((CanIfTxPduUserTxConfirmationULType)0x05U)
#define PDUR							((CanIfTxPduUserTxConfirmationULType)0x06U)
#define XCP								((CanIfTxPduUserTxConfirmationULType)0x07U)

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

/*
	CanIf_PduModeType
	[SWS_CANIF_00137] 
	The PduMode of a channel defines its transmit or receive activity.
	Communication direction (transmission and/or reception) of the channel can
	be controlled separately or together by upper layers.
*/
typedef uint8 CanIf_PduModeType;
#define CANIF_OFFLINE                                       ((CanIf_PduModeType)0x00)
#define CANIF_TX_OFFLINE                                    ((CanIf_PduModeType)0x01)
#if (CANIF_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
	#define CANIF_TX_OFFLINE_ACTIVE                         ((CanIf_PduModeType)0x02)
#endif /* CanIfTxOfflineActiveSupport = TRUE */
#define CANIF_ONLINE                                        ((CanIf_PduModeType)0x03)

typedef struct {
				
				/* This parameter defines if a respective controller of the referenced CAN 
				Driver modules is queriable for wake up events (Supports Wakeup Event or not). For Each CanIf Controller */
				boolean CanIfCtrlWakeupSupport;
				
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

/* [ECUC_CanIf_00832]
 * This container contains the Txbuffer configuration.
 * Multiple buffers with different sizes could be configured
 */
typedef struct {
			  /*[ECUC_CanIf_00834]
				This parameter defines the number of CanIf Tx L-PDUs which can be buffered in one Txbuffer. If this value
				equals 0, the CanIf does not perform Txbuffering for the CanIf Tx L-PDUs which are assigned to this
				Txbuffer. If CanIfPublicTxBuffering equals False, this parameter equals 0 for all TxBuffer. If the CanHandleType
				of the referred HTH equals FULL, this parameter equals 0 for this TxBuffer. Range: 0 .. 255
				dependency: CanIfPublicTxBuffering, CanHandleType */
				uint8 CanIfBufferSize;
	
			  /*[ECUC_CanIf_00833]
				Reference to HTH, that defines the hardware object or the pool of hardware objects configured for transmission.
				All the CanIf Tx L-PDUs refer via the CanIfBufferCfg and this parameter to the HTHs if TxBuffering is enabled, or
				not. Each HTH shall not be assigned to more than one buffer*/
				CanIfHthCfgType* CanIfBufferHthRef;
}CanIfBufferCfgType;

/*
 * [SWS_CANIF_00063]dThe CanIf shall support buffering of a CAN L-PDU for BasicCAN transmission in the CanIf
 * ,if parameter CanIfPublicTxBuffering (see CanIfPublicTxBuffering) is enabled. (SRS_Can_01020)
 * [SWS_CANIF_00849] For dynamic Transmit L-PDUs, also the CanId has to be stored in the CanIfTxBuffer.
 * */
#if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
/*
 *  Type Description : Struct to save the L-PDU information in a TxBuffer
 */
typedef struct
{
              /*Buffer To save PDU data with the max Can message data size */
               uint8       SduDatabuffer[MAX_DATA_LENGTH]    ;
              /*PDU Data length*/
               uint8       SduLength   ;
              /*Id of this L-PDU*/
               PduIdType   TxPduId;
              /*[SWS_CANIF_00849]  For dynamic Transmit L-PDUs,
                 also the CanId has to be stored in the CanIfTxBuffer.
               */
               Can_IdType  CanId  ;

}CanIfPduInfoCfgType;

/*Struct to map each TxBuffer with the PDUs saved in it*/
typedef struct
{
   /*
    * Pointer to all Pdus saved in this buffer
    */
    CanIfPduInfoCfgType* CanIfPduInfoRef;
   /*
    * Pointer to Txbuffer configurations
    */
    CanIfBufferCfgType* CanIfBufferRef ;
}CanIfPduTxBufferCfgType;
#endif

/* [ECUC_CanIf_00248]
 * This container contains the configuration (parameters) of a transmit
 * CAN L-PDU. It has to be configured as often as a transmit CAN L-PDU is needed
 * Post-Build Variant Multiplicit : true
 * */
typedef struct
{
			  /*[ECUC_CanIf_00592]
				CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for
				CAN L-PDU transmission. Range: 11 Bit For Standard CAN Identifier
				29 Bit For Extended CAN identifier
				The CAN Identifier may be omitted for dynamic transmit L-PDUs.
				Range: 0 .. 536870911
				*/
				uint32 CanIfTxPduCanId;
				
			  /*[ECUC_CanIf_00823]
				Identifier mask which denotes relevant bits in the CAN Identifier. This
				parameter may be used to keep parts of the CAN Identifier of dynamic
				transmit L-PDUs static. Range: 11 bits for Standard CAN Identifier, 29
				bits for Extended CAN Identifier.
				Range: 0 .. 536870911 */
				uint32 CanIfTxPduCanIdMask;
				
			  /*[ECUC_CanIf_00590]
				Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
				Driver module for CAN L-PDU transmission. 
				Range: 	EXTENDED_CAN CAN 		frame with extended identifier (29 bits)
						EXTENDED_FD_CAN CAN FD 	frame with extended identifier (29 bits)
						STANDARD_CAN CAN 		frame with standard identifier (11 bits)
						STANDARD_FD_CAN CAN FD 	frame with standard identifier (11 bits)
			   */
				CanIfTxPduCanIdTypeType CanIfTxPduCanIdType;
				
				
				/* If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
				could be configured which will pass the CanIfPnFilter.
				If there is no CanIfTxPduPnFilterPdu configured per controller,
				the corresponding controller applies no CanIfPnFilter.
				dependency: This parameter shall only be configurable if
				CanIfPublicPnSupport equals True. */
				#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
					boolean CanIfTxPduPnFilterPdu;
				#endif
				
				/* Enables and disables transmit confirmation for each transmit CAN
				L-SDU for reading its notification status.
				True: Enabled False: Disabled
				dependency: CANIF_READTXPDU_NOTIFY_STATUS_API must be enabled.*/
				#if(CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API==STD_ON)
					boolean CanIfTxPduReadNotifyStatus;
				#endif
				
				/* Determines if or if not CanIf shall use the trigger transmit API for this PDU.
				dependency: If CanIfTxPduTriggerTransmit is TRUE then CanIfTxPduUserTxConfirmationUL 
				has to be either PDUR or CDD and CanIfTxPduUserTriggerTransmitName has to be specified accordingly */
				boolean CanIfTxPduTriggerTransmit;
				
				/* Enables/disables truncation of PDUs that exceed the configured size. */
				boolean CanIfTxPduTruncation;
				
				/* Defines the type of each transmit CAN L-PDU.
				Range:	DYNAMIC 	CAN ID is defined at runtime.
						STATIC 		CAN ID is defined at compile-time. */
				CanIfTxPduTypeType CanIfTxPduType;
				
               /*[ECUC_CanIf_00842]
                * This parameter defines the name of the <User_TriggerTransmit>.
                * This parameter depends on the parameter CanIfTxPduUserTxConfirmationUL
                * */
				#if(CANIF_TXPDU_TRIGGERTRANSMIT==STD_ON)
					void (*CanIfTxPduUserTriggerTransmitName)(PduIdType, PduInfoType* );
				#endif

			    /*[ECUC_CanIf_00528]
			     * This parameter defines the name of the <User_TxConfirmation>. This parameter depends on the
			     * parameter CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL equals CAN_TP, CAN_NM,
			     * PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the <User_TxConfirmation> is fixed.
			     * If CanIfTxPduUserTxConfirmationUL equals CDD,
			     * the name of the <User_TxConfirmation> is selectable.*/
				void (*CanIfTxPduUserTxConfirmationName)(PduIdType, Std_ReturnType);
				
             /* [ECUC_CanIf_00527]
                This parameter defines the upper layer (UL) module to which the confirmation of
                the successfully transmitted CANTXPDUID has to be routed via the <User_TxConfirmation>.
                This <User_TxConfirmation> has to be invoked when the confirmation of the configured CANTXPDUID
                will be received by a Tx confirmation event from the CAN Driver module.
                If no upper layer (UL) module is configured, no <User_TxConfirmation> has to be called in case of
                a Tx confirmation event of the CANTXPDUID from the CAN Driver module.
                Range:  CAN_NM      CAN NM
                        CAN_TP      CAN TP
                        CAN_TSYN    Global Time Synchronization over CAN
                        CDD         Complex Driver
                        J1939NM     J1939Nm
                        J1939TP     J1939Tp
                        PDUR        PDU Router
                        XCP         Extended Calibration Protocol
                Note: If CanIfTxPduTriggerTransmit is not specified or FALSE, no upper
                layer modules have to be configured for Trigger Transmit. Therefore,
                <User_TriggerTransmit>() will not be called and CanIfTxPduUserTxConfirmationUL
                as well as CanIfTxPduUserTriggerTransmitName need not to be configured.
             */
                CanIfTxPduUserTxConfirmationULType CanIfTxPduUserTxConfirmationUL;

				/* Configurable reference to a CanIf buffer configuration. CanIfBufferCfg */
				CanIfBufferCfgType* CanIfTxPduBufferRef;
				
				/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
				//Pdu* CanIfTxPduRef;
				will be configured in implementation */
}CanIfTxPduCfgType;

/*
 * [ECUC_CanIf_00743]
 *  Optional container that allows to map a range of CAN Ids to one PduId.
 */
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


/* [ECUC_CanIf_00628]
 * Defines the parameters required for configurating multiple CANID ranges for a given same HRH.*/
typedef struct {
				/* [ECUC_CanIf_00825]
				 * CAN Identifier used as base value in combination with CanIfHrhRangeMask for a masked ID range
				 * in which all CAN Ids shall pass the software filtering. The size of this parameter is limited by
				 * CanIfHrhRangeRxPduRangeCanIdType.
			     */
				uint32  CanIfHrhRangeBaseId;
	
				/* [ECUC_CanIf_00826]
				 * Used as mask value in combination with CanIfHrhRangeBaseId for a masked ID range in which all CAN
				 * Ids shall pass the software filtering. The size of this parameter is limited by CanIfHrhRangeRxPduRangeCanIdType.*/
				uint32 CanIfHrhRangeMask;
	
				/* [ECUC_CanIf_00629]
				 * Lower CAN Identifier of a receive CAN L-PDU for identifier range definition, in which all CAN Ids shall
				 *pass the software filtering*/
				uint32 CanIfHrhRangeRxPduLowerCanId;
	
				/* [ECUC_CanIf_00644]
				 * Specifies whether a configured Range of CAN Ids shall only consider standard CAN Ids or extended CAN Id
				 * Range: 		EXTENDED All the CANIDs are of type extended only (29 bit).
							    STANDARD All the CANIDs are of type standard only (11bit). */
				CanIfHrhRangeRxPduRangeCanIdTypeType CanIfHrhRangeRxPduRangeCanIdType;

				/* [ECUC_CanIf_00630]
				 * Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in which all CAN Ids shall
			 	 *pass the software filtering.*/
				uint32 CanIfHrhRangeRxPduUpperCanId;
}CanIfHrhRangeCfgType;

typedef struct {
        /* ECUC_CanIf_00632
         * True: Software filtering is enabled False: Software filtering is enabled*/
        boolean                CanIfHrhSoftwareFilter ;
        /*Reference to controller Id to which the HRH belongs to. A controller can contain one or more HRHs.*/
        CanIfCtrlCfgType*      CanIfHrhCanCtrlIdRef;

        /*The parameter refers to a particular HRH object in the CanDrv configuration*/
        CanHardwareObjectType* CanIfHrhIdSymRef;

        /*Defines the parameters required for configurating multiple CANID ranges for a given same HRH.*/
        CanIfHrhRangeCfgType*  CanIfHrhRangeCfgRef; // will have an Object of [CANID_RANGES_NUM] (multiplicity 0..*) in PBcfg or Lcfg files
}CanIfHrhCfgType;


/* [ECUC_CanIf_00249]
 * This container contains the configuration (parameters) of each receive CAN L-PDU.
 * */
typedef struct{
			/*  [ECUC_CanIf_00598]
			    CAN Identifier of Receive CAN L-PDUs used by the CAN Interface.
				Exa: Software Filtering. This parameter is used if exactly one Can
				Identifier is assigned to the Pdu. If a range is assigned then the
				CanIfRxPduCanIdRange parameter shall be used.
				Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier */
				uint32 CanIfRxPduCanId;
				
			/*  ECUC_CanIf_00822]
				Identifier mask which denotes relevant bits in the CAN Identifier. This
				parameter defines a CAN Identifier range in an alternative way to
				CanIfRxPduCanIdRange. It identifies the bits of the configured CAN
				Identifier that must match the received CAN Identifier. Range: 11 bits
				for Standard CAN Identifier, 29 bits for Extended CAN Identifier. */
				uint32 CanIfRxPduCanIdMask;
				
			 /* ECUC_CanIf_00596]
				CAN Identifier of receive CAN L-PDUs used by the CAN Driver for
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

				
				/* Enables and disables the Rx buffering for reading of received L-SDU
				data. True: Enabled False: Disabled
				dependency: CANIF_CANPDUID_READDATA_API must be enabled */
				#if(CANIF_CAN_PDU_ID_READ_DATA_API==STD_ON)
					boolean CanIfRxPduReadData;
				#endif
				
				/* Enables and disables receive indication for each receive CAN L-SDU
				for reading its notification status.
				True: Enabled False: Disabled
				dependency: CANIF_READRXPDU_NOTIFY_STATUS_API must be enabled. */
				#if(CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API==STD_ON)
					boolean CanIfRxPduReadNotifyStatus;
				#endif

				/*
				 * [ECUC_CanIf_00530]
				 * This parameter defines the name of the <User_RxIndication>.
				 * This parameter depends on the parameter*/
				void (*CanIfRxPduUserRxIndicationName)(PduIdType RxPduId, const PduInfoType* );

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
				
				/* [ECUC_CanIf_00602]
				 * The HRH to which Rx L-PDU belongs to, is referred through this parameter.
				 * dependency: This information has to be derived from the CAN Driver configuration.*/
				CanIfHrhCfgType* CanIfRxPduHrhIdRef;
				
				/* Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
				//Pdu* CanIfRxPduRef;
				  will be configured in implementation */
				
				/* Optional container that allows to map a range of CAN Ids to one PduId. */
				CanIfRxPduCanIdRangeType* CanIfRxPduCanIdRangeRef;
}CanIfRxPduCfgType;

typedef struct{
				/*This container contains configuration parameters for each hardware receive object (HRH).*/
				CanIfHrhCfgType*	CanIfHrhCfgRef; // will have an Object of [HRH_OBj_NUM] in PBcfg or Lcfg files

				/*This container contains parameters related to each HTH.*/
				CanIfHthCfgType*	CanIfHthCfgRef; // will have an Object of [HTH_OBj_NUM] in PBcfg or Lcfg files
}CanIfInitHohCfgType;

typedef struct {
				

				
				/* This container contains the Txbuffer configuration. Multiple buffers with different sizes could be configured.
				If CanIfBufferSize (ECUC_CanIf_00834) equals 0, the CanIf Tx L-PDU only refers via this CanIfBufferCfg the
				corresponding CanIfHthCfg. */
				CanIfBufferCfgType*		CanIfBufferCfgRef; // will have an Object of [BUFFERS_NUM] in PBcfg or Lcfg files
				
				/* This container contains the references to the configuration setup of each underlying CAN Driver. */
				CanIfInitHohCfgType*	CanIfInitHohCfgRef; // will have an Object of [CAN_DRIVER_NUM] in PBcfg or Lcfg files
				
				/* This container contains the configuration (parameters) of each receive CAN L-PDU. The SHORT-NAME of
				"CanIfRxPduConfig" container itself represents the symolic name of Receive L-PDU. This L-SDU produces
				a meta data item of type CAN_ID_32. */
				CanIfRxPduCfgType*	CanIfRxPduCfgRef; // will have an Object of [RX_CAN_L_PDU_NUM] in PBcfg or Lcfg file
				
				/* This container contains the configuration (parameters) of a transmit CAN L-PDU. It has to be configured as
				often as a transmit CAN L-PDU is needed. The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic
				name of Transmit L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32. */
				CanIfTxPduCfgType*	CanIfTxPduCfgRef; // will have an Object of [TX_CAN_L_PDU_NUM] in PBcfg or Lcfg file
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
				CanIfInitHohCfgType* CanIfCtrlInitHohRef;
				
				/*This container contains the configuration (parameters) of an adressed CAN controller by
				an underlying CAN Driver module. This container is configurable per CAN controller.*/	
				CanIfCtrlCfgType*	CanIfCtrlCfgRef; // will have an Object of [CANIF_CONTROLLERS_NUM] in the PBcfg or Lcfg file
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
				CanIfTrcvCfgType*	CanIfTrcvCfgRef; // will have an object of[CAN_TRANSCEIVER_NUM] in PBcfg or Lcfg file
}CanIfTrcvDrvCfgType;


/*[SWS_CANIF_00144]
 * This type defines a data structure for the post build parameters of the CAN interface
 * for all underlying CAN drivers. At initialization the CanIf gets a pointer to a structure
 * of this type to get access to its configuration data, which is necessary for initialization.
 *
 * The contents of the initialization data structure are CAN interface specific .
 */
typedef struct
{
    /*This container contains the init parameters of the CAN Interface.*/
    CanIfInitCfgType*		CanIfInitCfgRef;

    #if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
	/*Struct to map each TxBuffer with the PDUs saved in it*/
	CanIfPduTxBufferCfgType* CanIfPduTxBufferCfgRef;
    #endif
}CanIf_ConfigType;


#endif /*__CANIF_TYPES_H__*/

