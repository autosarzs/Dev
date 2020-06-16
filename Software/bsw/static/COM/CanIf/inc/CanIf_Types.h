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

/* PDU Type */
typedef uint8 Can_TypeType;
#define PDU_STATIC	((Can_TypeType)0x00)
#define PDU_DYNAMIC	((Can_TypeType)0x01)

/* CanIf Users Enum */
typedef uint8 CanIf_UserType;
#define	CANIF_USER_CAN_NM		((CanIf_UserType)0x00)
#define	CANIF_USER_CAN_TP		((CanIf_UserType)0x01)
#define	CANIF_USER_CAN_TSyn 	((CanIf_UserType)0x02)
#define	CANIF_USER_CDD 			((CanIf_UserType)0x03)
#define	CANIF_USER_J1939NM 		((CanIf_UserType)0x04)
#define	CANIF_USER_J1939TP	 	((CanIf_UserType)0x05)
#define	CANIF_USER_PDUR			((CanIf_UserType)0x06)
#define	CANIF_USER_XCP 			((CanIf_UserType)0x07)

/* software filtering methods */
typedef uint8 CanIf_SwFilterType;
#define	CANIF_SW_FILTER_BINARY	((CanIf_SwFilterType)0x00)
#define	CANIF_SW_FILTER_INDEX	((CanIf_SwFilterType)0x01)
#define	CANIF_SW_FILTER_LINEAR	((CanIf_SwFilterType)0x02)
#define	CANIF_SW_FILTER_TABLE	((CanIf_SwFilterType)0x03)


/*****************************************************************************************/
/*             			 Containers and configuration parameters	   	                 */
/*****************************************************************************************/


//****************************************************************************************
//						CanIfCtrlCfg
//	[ECUC_CanIf_00546]
//  This container contains the configuration (parameters) of an adressed CAN controller
//	by an underlying CAN Driver module. This container is configurable per CAN controller.
//****************************************************************************************
typedef struct{
	//************************************************************************************
	//					CanIfCtrlId   [ECUC_CanIf_00647]
	//
	//	This parameter abstracts from the CAN Driver specific parameter Controller. Each
	//	controller of all connected CAN Driver modules shall be assigned to one specific
	//	ControllerId of the CanIf. Range: 0..number of configured controllers of all CAN
	//	Driver modules
	//************************************************************************************
	uint8 CanIfCtrlId;
	//************************************************************************************
	//					CanIfCtrlWakeupSupport   [ECUC_CanIf_00637]
	//
	//	This parameter defines if a respective controller of the referenced CAN Driver
	//	modules is queriable for wake up events.
	//************************************************************************************
	boolean CanIfCtrlWakeupSupport;
	//************************************************************************************
	//					CanIfCtrlCanCtrlRef   [ECUC_CanIf_00636]
	//
	//	This parameter references to the logical handle of the underlying CAN controller
	//	from the CAN Driver module to be served by the CAN Interface module. The following
	//	parameters of CanController config container shall be referenced by this link:
	//	CanControllerId, CanWakeupSourceRef
	//	Range: 0..max. number of underlying supported CAN controllers
	//************************************************************************************
	CanController* CanIfCtrlCanCtrlRef;
}CanIfCtrlCfg;



/*****************************************************************************************/
/*              Configurating multiple CANID ranges for a given same HRH.                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfHrhRangeCfg
//	[ECUC_CanIf_00628]
//  Defines the parameters required for configurating multiple CANID ranges for a given
//	same HRH.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHrhRangeBaseId    [ECUC_CanIf_00825]
	//
	//	CAN Identifier used as base value in combination with CanIfHrhRangeMask for a masked
	//	ID range in which all CAN Ids shall pass the software filtering. The size of this
	//	parameter is limited by CanIfHrhRangeRxPduRangeCanIdType.
	uint32 CanIfHrhRangeBaseId;
	//************************************************************************************
	//					CanIfHrhRangeMask   [ECUC_CanIf_00826]
	//
	//	Used as mask value in combination with CanIfHrhRangeBaseId for a masked ID range in
	//	which all CAN Ids shall pass the software filtering. The size of this parameter is
	//	limited by CanIfHrhRangeRxPduRangeCanIdType.
	uint32 CanIfHrhRangeMask;
	//************************************************************************************
	//					CanIfHrhRangeRxPduLowerCanId   [ECUC_CanIf_00629]
	//
	//	Lower CAN Identifier of a receive CAN L-PDU for identifier range definition, in
	//	which all CAN Ids shall pass the software filtering.
	uint32 CanIfHrhRangeRxPduLowerCanId;
	//************************************************************************************
	//					CanIfHrhRangeRxPduRangeCanIdType   [ECUC_CanIf_00644]
	//
	//	Specifies whether a configured Range of CAN Ids shall only consider standard CAN Ids
	//	or extended CAN Ids.
	CanIdTypeType CanIfHrhRangeRxPduRangeCanIdType;
	//************************************************************************************
	//					CanIfHrhRangeRxPduUpperCanId    [ECUC_CanIf_00630]
	//
	//	Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in
	//	which all CAN Ids shall pass the software filtering.
	uint32 CanIfHrhRangeRxPduUpperCanId;
}CanIfHrhRangeCfg;

/*****************************************************************************************/
/*                                    HRH configuration                                  */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfHrhCfg
//	[ECUC_CanIf_00259]
//  This container contains configuration parameters for each hardware receive object (HRH).
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHrhSoftwareFilter    [ECUC_CanIf_00630]
	//
	//	Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in
	//	which all CAN Ids shall pass the software filtering.
	boolean CanIfHrhSoftwareFilter;
	//************************************************************************************
	//					CanIfHrhCanCtrlIdRef    [ECUC_CanIf_00632]
	//
	//	Selects the hardware receive objects by using the HRH range/list from CAN Driver
	//	configuration to define, for which HRH a software filtering has to be performed at
	//	during receive processing.
	CanIfCtrlCfg* CanIfHrhCanCtrlIdRef;
	//************************************************************************************
	//					CanIfHrhIdSymRef    [ECUC_CanIf_00631]
	//
	//	Reference to controller Id to which the HRH belongs to. A controller can contain
	//	one or more HRHs.
	CanHardwareObject* CanIfHrhIdSymRef;
	//************************************************************************************
	//					CanIfHrhRangeConfig    [ECUC_CanIf_00634]
	//
	//	The parameter refers to a particular HRH object in the CanDrv configuration .
	//	CanIf receives the following information of the CanDrv module by this reference:
	//		� CanHandleType (see ECUC_Can_00323)
	//		� CanObjectId (see ECUC_Can_00326)
	CanIfHrhRangeCfg* CanIfHrhRangeConfig;
}CanIfHrhCfg;




/*****************************************************************************************/
/*                                    HTH configuration                                  */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfHrhCfg
//	[ECUC_CanIf_00258]
//  This container contains parameters related to each HTH.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHthCanCtrlIdRef    [ECUC_CanIf_00625]
	//
	//	Reference to controller Id to which the HTH belongs to. A controller can contain
	//	one or more HTHs.
	CanIfCtrlCfg* CanIfHthCanCtrlIdRef;
	//************************************************************************************
	//					CanIfHthIdSymRef    [ECUC_CanIf_00627]
	//
	//	The parameter refers to a particular HTH object in the CanDrv configuration.
	//	CanIf receives the following information of the CanDrv module by this reference:
	//		� CanHandleType (see ECUC_Can_00323)
	//		� CanObjectId (see ECUC_Can_00326)
	CanHardwareObject* CanIfHthIdSymRef;
}CanIfHthCfg;



/*****************************************************************************************/
/*                                    HOH configuration                                  */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfInitHohCfg
//	[ECUC_CanIf_00257]
//  This container contains the references to the configuration setup of each underlying
//	CAN Driver.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHrhCfgRef
	//
	//	This container contains configuration parameters for each hardware receive object
	//	(HRH).
	CanIfHrhCfg* CanIfHrhCfgRef;
	//************************************************************************************
	//					CanIfHthCfgRef
	//
	//	This container contains configuration parameters for each hardware transmit object
	//	(HTH).
	CanIfHthCfg* CanIfHthCfgRef;
}CanIfInitHohCfg;



/*****************************************************************************************/
/*                                   Buffer configuration                                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfBufferCfg
//	[ECUC_CanIf_00832]
//  This container contains the Txbuffer configuration. Multiple buffers with different sizes
//	could be configured. If CanIfBufferSize (ECUC_CanIf_00834) equals 0, the CanIf Tx L-PDU
//	only refers via this CanIfBufferCfg the corresponding CanIfHthCfg.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfBufferSize    [ECUC_CanIf_00834]
	//
	//	This parameter defines the number of CanIf Tx L-PDUs which can be buffered in one
	//	Txbuffer. If this value equals 0, the CanIf does not perform Txbuffering for the
	//	CanIf Tx L-PDUs which are assigned to this Txbuffer. If CanIfPublicTxBuffering equals
	//	False, this parameter equals 0 for all TxBuffer. If the CanHandleType of the referred
	//	HTH equals FULL, this parameter equals 0 for this TxBuffer.
	uint8 CanIfBufferSize;
	//************************************************************************************
	//					CanIfBufferHthRef    [ECUC_CanIf_00833]
	//
	//	Reference to HTH, that defines the hardware object or the pool of hardware objects
	//	configured for transmission. All the CanIf Tx L-PDUs refer via the CanIfBufferCfg and
	//	this parameter to the HTHs if TxBuffering is enabled, or not.
	//	Each HTH shall not be assigned to more than one buffer.
	CanIfHthCfg* CanIfBufferHthRef;
}CanIfBufferCfg;



/*****************************************************************************************/
/*                                  Tx PDU configuration                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTxPduCfg
//	[ECUC_CanIf_00248]
//  This container contains the configuration (parameters) of a transmit CAN L-PDU. It has to
//	be configured as often as a transmit CAN L-PDU is needed.
//	The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic name of Transmit
//	L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfTxPduCanId    [ECUC_CanIf_00592]
	//
	//	CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission.
	//	Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier
	//	The CAN Identifier may be omitted for dynamic transmit L-PDUs.
	uint32 CanIfTxPduCanId;
	//************************************************************************************
	//					CanIfTxPduCanIdMask    [ECUC_CanIf_00823]
	//
	//	Identifier mask which denotes relevant bits in the CAN Identifier. This parameter may
	//	be used to keep parts of the CAN Identifier of dynamic transmit L-PDUs static.
	//	Range: 11 bits for Standard CAN Identifier, 29 bits for Extended CAN Identifier.
	uint32 CanIfTxPduCanIdMask;
	//************************************************************************************
	//					CanIfTxPduCanIdType    [ECUC_CanIf_00590]
	//
	//	Type of CAN Identifier of the transmit CAN L-PDU used by the CAN Driver module for
	//	CAN L-PDU transmission.
	Can_IdType CanIfTxPduCanIdType;
	//************************************************************************************
	//					CanIfTxPduId    [ECUC_CanIf_00591]
	//
	//	ECU wide unique, symbolic handle for transmit CAN L-SDU.
	//	Range: 0..max. number of CantTxPduIds
	uint32 CanIfTxPduId;
	//************************************************************************************
	//					CanIfTxPduPnFilterPdu    [ECUC_CanIf_00773]
	//
	//	If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs could be configured
	//	which will pass the CanIfPnFilter. If there is no CanIfTxPduPnFilterPdu configured
	//	per controller, the corresponding controller applies no CanIfPnFilter.
	boolean CanIfTxPduPnFilterPdu;
	//************************************************************************************
	//					CanIfTxPduReadNotifyStatus    [ECUC_CanIf_00589]
	//
	//	Enables and disables transmit confirmation for each transmit CAN L-SDU for reading
	//	its notification status.
	boolean CanIfTxPduReadNotifyStatus;
	//************************************************************************************
	//					CanIfTxPduTriggerTransmit    [ECUC_CanIf_00840]
	//
	//	Determines if or if not CanIf shall use the trigger transmit API for this PDU.
	boolean CanIfTxPduTriggerTransmit;
	//************************************************************************************
	//					CanIfTxPduTruncation    [ECUC_CanIf_00845]
	//
	//	Enables/disables truncation of PDUs that exceed the configured size.
	boolean CanIfTxPduTruncation;
	//************************************************************************************
	//					CanIfTxPduType    [ECUC_CanIf_00593]
	//
	//	Defines the type of each transmit CAN L-PDU.
	Can_TypeType CanIfTxPduType;
	//************************************************************************************
	//					CanIfTxPduUserTriggerTransmitName    [ECUC_CanIf_00842]
	//
	//	This parameter defines the name of the <User_TriggerTransmit>. This parameter depends
	//	on the parameter CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL
	//	equals CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the
	//	<User_TriggerTransmit> is fixed. If CanIfTxPduUserTxConfirmationUL equals CDD, the
	//	name of the <User_TxConfirmation> is selectable.
	//	Please be aware that this parameter depends on the same parameter as
	//	CanIfTxPduUserTxConfirmationName. It shall be clear which upper layer is responsible
	//	for that PDU.
	Std_ReturnType(*CanIfTxPduUserTriggerTransmitName)(PduIdType, PduInfoType*);
	//************************************************************************************
	//					CanIfTxPduUserTxConfirmationName    [ECUC_CanIf_00528]
	//
	//	This parameter defines the name of the <User_TxConfirmation>. This parameter depends
	//	on the parameter CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL
	//	equals CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the
	//	<User_TxConfirmation> is fixed. If CanIfTxPduUserTxConfirmationUL equals CDD, the
	//	name of the <User_TxConfirmation> is selectable.
	void(*CanIfTxPduUserTxConfirmationName)(PduIdType, Std_ReturnType);
	//************************************************************************************
	//					CanIfTxPduUserTxConfirmationUL    [ECUC_CanIf_00527]
	//
	//	This parameter defines the upper layer (UL) module to which the confirmation of the
	//	successfully transmitted CanTxPduId has to be routed via the <User_TxConfirmation>.
	//	This <User_TxConfirmation> has to be invoked when the confirmation of the configured
	//	CanTxPduId will be received by a Tx confirmation event from the CAN Driver module.
	//	If no upper layer (UL) module is configured, no <User_TxConfirmation> has to be called
	//	in case of a Tx confirmation event of the CanTxPduId from the CAN Driver module.
	CanIf_UserType CanIfTxPduUserTxConfirmationUL;
	//************************************************************************************
	//					CanIfTxPduBufferRef    [ECUC_CanIf_00831]
	//
	//	Configurable reference to a CanIf buffer configuration.
	CanIfBufferCfg* CanIfTxPduBufferRef;
	//************************************************************************************
	//					CanIfTxPduRef    [ECUC_CanIf_00603]
	//
	//	Reference to the "global" Pdu structure to allow harmonization of handle IDs in the
	//	COM-Stack.
	Can_PduType* CanIfTxPduRef;
}CanIfTxPduCfg;



/*****************************************************************************************/
/*                                  Rx PDU configuration                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTxPduCfg
//	[ECUC_CanIf_00249]
//  This container contains the configuration (parameters) of each receive CAN L-PDU.
//	The SHORT-NAME of "CanIfRxPduConfig" container represents the symolic name of receive
//	L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfRxPduCanId    [ECUC_CanIf_00598]
	//
	//	CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa: Software Filtering.
	//	This parameter is used if exactly one Can Identifier is assigned to the Pdu. If a range
	//	is assigned then the CanIfRxPduCanIdRange parameter shall be used.
	//	Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier
	uint32 CanIfRxPduCanId;
	//************************************************************************************
	//					CanIfRxPduCanIdMask    [ECUC_CanIf_00522]
	//
	//	Identifier mask which denotes relevant bits in the CAN Identifier. This parameter defines
	//	a CAN Identifier range in an alternative way to CanIfRxPduCanIdRange. It identifies the
	//	bits of the configured CAN Identifier that must match the received CAN Identifier.
	//	Range: 11 bits for Standard CAN Identifier, 29 bits for Extended CAN Identifier.
	uint32 CanIfRxPduCanIdMask;
	//************************************************************************************
	//					CanIfRxPduCanIdType    [ECUC_CanIf_00596]
	//
	//	CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CAN L-PDU reception.
	Can_IdType CanIfRxPduCanIdType;
	//************************************************************************************
	//					CanIfRxPduDataLength    [ECUC_CanIf_00599]
	//
	//	Data length of the received CAN L-PDUs used by the CAN Interface. This information is
	//	used for Data Length Check. Additionally it might specify the valid bits in case of the
	//	discrete DLC for CAN FD L-PDUs > 8 bytes.
	//	The data area size of a CAN L-PDU can have a range from 0 to 64 bytes.
	uint8 CanIfRxPduDataLength;
	//************************************************************************************
	//					CanIfRxPduDataLengthCheck    [ECUC_CanIf_00846]
	//
	//	This parameter switches the message specific data length check. True: Data length check
	//	will be executed during the reception of this PDU. False: No data length check will be
	//	executed during the reception of this PDU.
	boolean CanIfRxPduDataLengthCheck;
	//************************************************************************************
	//					CanIfRxPduId    [ECUC_CanIf_00597]
	//
	//	ECU wide unique, symbolic handle for receive CAN L-SDU. It shall fulfill ANSI/AUTOSAR
	//	definitions for constant defines.
	//	Range: 0..max. number of defined CanRxPduIds
	uint32 CanIfRxPduId;
	//************************************************************************************
	//					CanIfRxPduReadData    [ECUC_CanIf_00600]
	//
	//	Enables and disables the Rx buffering for reading of received L-SDU data.
	boolean CanIfRxPduReadData;
	//************************************************************************************
	//					CanIfRxPduReadNotifyStatus    [ECUC_CanIf_00595]
	//
	//	Enables and disables receive indication for each receive CAN L-SDU for reading its
	//	notification status.
	boolean CanIfRxPduReadNotifyStatus;
	//************************************************************************************
	//					CanIfRxPduUserRxIndicationName    [ECUC_CanIf_00530]
	//
	//	This parameter defines the name of the <User_RxIndication>. This parameter depends on
	//	the parameter CanIfRxPduUserRxIndicationUL. If CanIfRxPduUserRxIndicationUL equals
	//	CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the
	//	<User_RxIndication> is fixed. If CanIfRxPduUserRxIndicationUL equals CDD, the name of
	//	the <User_RxIndication> is selectable.
	void (*CanIfRxPduUserRxIndicationName )(PduIdType, const PduInfoType*);
	//************************************************************************************
	//					CanIfRxPduUserRxIndicationUL    [ECUC_CanIf_00829]
	//
	//	This parameter defines the upper layer (UL) module to which the indication of the
	//	successfully received CANRXPDUID has to be routed via <User_RxIndication>. This
	//	<User_RxIndication> has to be invoked when the indication of the configured CANRXPDUID
	//	will be received by an Rx indication event from the CAN Driver module. If no upper
	//	layer (UL) module is configured, no <User_RxIndication> has to be called in case of an
	//	Rx indication event of the CANRXPDUID from the CAN Driver module.
	CanIf_UserType CanIfRxPduUserRxIndicationUL;
	//************************************************************************************
	//					CanIfRxPduHrhIdRef    [ECUC_CanIf_00602]
	//
	//	The HRH to which Rx L-PDU belongs to, is referred through this parameter.
	CanIfHrhCfg* CanIfRxPduHrhIdRef;
	//************************************************************************************
	//					CanIfRxPduRef    [ECUC_CanIf_00601]
	//
	//	Reference to the "global" Pdu structure to allow harmonization of handle IDs in the
	//	COM-Stack.
	Can_PduType* CanIfRxPduRef;
}CanIfRxPduCfg;




/*****************************************************************************************/
/*                              CanIf Public Configuration                               */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfPublicCfg
//	[ECUC_CanIf_00246]
//  This container contains the public configuration (parameters) of the CAN Interface.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfBusMirroringSupport   [ECUC_CanIf_00847]
	//
	//	Enable support for Bus Mirroring.
	boolean CanIfBusMirroringSupport;
	//************************************************************************************
	//					CanIfDevErrorDetect    [ECUC_CanIf_00614]
	//
	//	Switches the development error detection and notification on or off.
	boolean CanIfDevErrorDetect;
	//************************************************************************************
	//					CanIfMetaDataSupport    [ECUC_CanIf_00824]
	//
	//	Enable support for dynamic ID handling using L-SDU MetaData.
	boolean CanIfMetaDataSupport;
	//************************************************************************************
	//					CanIfPublicCddHeaderFile    [ECUC_CanIf_00671]
	//
	//	Defines header files for callback functions which shall be included in case of CDDs.
	//	Range of characters is 1.. 32.
	uint8* CanIfPublicCddHeaderFile;
	//************************************************************************************
	//					CanIfPublicHandleTypeEnum    [ECUC_CanIf_00742]
	//
	//	This parameter is used to configure the Can_HwHandleType. The Can_HwHandleType
	//	represents the hardware object handles of a CAN hardware unit. For CAN hardware units
	//	with more than 255 HW objects the extended range shall be used (UINT16).
	uint8 CanIfPublicHandleTypeEnum;
	//************************************************************************************
	//					CanIfPublicIcomSupport    [ECUC_CanIf_00839]
	//
	//	Selects support of Pretended Network features in CanIf.
	boolean CanIfPublicIcomSupport;
	//************************************************************************************
	//					CanIfPublicMultipleDrvSupport    [ECUC_CanIf_00612]
	//
	//	Selects support for multiple CAN Drivers.
	boolean CanIfPublicMultipleDrvSupport;
	//************************************************************************************
	//					CanIfPublicPnSupport    [ECUC_CanIf_00772]
	//
	//	Selects support of Partial Network features in CanIf.
	boolean CanIfPublicPnSupport;
	//************************************************************************************
	//					CanIfPublicReadRxPduDataApi    [ECUC_CanIf_00607]
	//
	//	Enables / Disables the API CanIf_ReadRxPduData() for reading received L-SDU data.
	boolean CanIfPublicReadRxPduDataApi;
	//************************************************************************************
	//					CanIfPublicReadRxPduNotifyStatusApi    [ECUC_CanIf_00608]
	//
	//	Enables and disables the API for reading the notification status of receive L-PDUs.
	boolean CanIfPublicReadRxPduNotifyStatusApi;
	//************************************************************************************
	//					CanIfPublicReadTxPduNotifyStatusApi    [ECUC_CanIf_00609]
	//
	//	Enables and disables the API for reading the notification status of transmit L-PDUs.
	boolean CanIfPublicReadTxPduNotifyStatusApi;
	//************************************************************************************
	//					CanIfPublicSetDynamicTxIdApi    [ECUC_CanIf_00610]
	//
	//	Enables and disables the API for reconfiguration of the CAN Identifier for each
	//	Transmit L-PDU.
	boolean CanIfPublicSetDynamicTxIdApi;
	//************************************************************************************
	//					CanIfPublicTxBuffering    [ECUC_CanIf_00618]
	//
	//	Enables and disables the buffering of transmit L-PDUs (rejected by the CanDrv) within
	//	the CAN Interface module.
	boolean CanIfPublicTxBuffering;
	//************************************************************************************
	//					CanIfPublicTxConfirmPollingSupport    [ECUC_CanIf_00733]
	//
	//	Configuration parameter to enable/disable the API to poll for Tx Confirmation state.
	boolean CanIfPublicTxConfirmPollingSupport;
	//************************************************************************************
	//					CanIfPublicWakeupCheckValidByNM    [ECUC_CanIf_00741]
	//
	//	If enabled, only NM messages shall validate a detected wake-up event in CanIf. If
	//	disabled, all received messages corresponding to a configured Rx PDU shall validate
	//	such a wake-up event. This parameter depends on CanIfPublicWakeupCheckValidSupport and
	//	shall only be configurable, if it is enabled.
	boolean CanIfPublicWakeupCheckValidByNM;
	//************************************************************************************
	//					CanIfPublicWakeupCheckValidSupport    [ECUC_CanIf_00611]
	//
	//	Selects support for wake up validation
	boolean CanIfPublicWakeupCheckValidSupport;
	//************************************************************************************
	//					CanIfSetBaudrateApi    [ECUC_CanIf_00838]
	//
	//	Configuration parameter to enable/disable the CanIf_SetBaudrate API to change the baud
	//	rate of a CAN Controller. If this parameter is set to true the CanIf_SetBaudrate API
	//	shall be supported. Otherwise the API is not supported.
	boolean CanIfSetBaudrateApi;
	//************************************************************************************
	//					CanIfTriggerTransmitSupport    [ECUC_CanIf_00844]
	//
	//	Enables the CanIf_TriggerTransmit API at Pre-Compile-Time. Therefore, this parameter
	//	defines if there shall be support for trigger transmit transmissions.
	boolean CanIfTriggerTransmitSupport;
	//************************************************************************************
	//					CanIfTxOfflineActiveSupport    [ECUC_CanIf_00837]
	//
	//	Determines wether TxOffLineActive feature (see SWS_CANIF_00072) is supported by CanIf.
	boolean CanIfTxOfflineActiveSupport;
	//************************************************************************************
	//					CanIfVersionInfoApi    [ECUC_CanIf_00613]
	//
	//	Enables and disables the API for reading the version information about the CAN Interface.
	boolean CanIfVersionInfoApi;
	//************************************************************************************
	//					CanIfWakeupSupport    [ECUC_CanIf_00843]
	//
	//	Enables the CanIf_CheckWakeup API at Pre-Compile-Time. Therefore, this parameter defines
	//	if there shall be support for wake-up.
	boolean CanIfWakeupSupport;
}CanIfPublicCfg;




/*****************************************************************************************/
/*                             CanIf Private Configuration                               */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfPrivateCfg
//	[ECUC_CanIf_00245]
//  This container contains the private configuration (parameters) of the CAN Interface.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfFixedBuffer    [ECUC_CanIf_00827]
	//
	//	This parameter defines if the buffer element length shall be fixed to 8 Bytes for
	//	buffers to which only PDUs < 8 Bytes are assigned.
	//	TRUE: Minimum buffer element length is fixed to 8 Bytes. FALSE: Buffer element length
	//	depends on the size of the referencing PDUs.
	boolean CanIfFixedBuffer;
	//************************************************************************************
	//					CanIfPrivateDataLengthCheck    [ECUC_CanIf_00617]
	//
	//	Selects whether Data Length Check is supported.
	boolean CanIfPrivateDataLengthCheck;
	//************************************************************************************
	//					CanIfPrivateSoftwareFilterType    [ECUC_CanIf_00619]
	//
	//	Selects the desired software filter mechanism for reception only. Each implemented
	//	software filtering method is identified by this enumeration number.
	CanIf_SwFilterType CanIfPrivateSoftwareFilterType;
	//************************************************************************************
	//					CanIfSupportTTCAN    [ECUC_CanIf_00675]
	//
	//	Defines whether TTCAN is supported.
	boolean CanIfSupportTTCAN;
}CanIfPrivateCfg;

/*****************************************************************************************/
/*                                  CanIf Init Container                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIf_ConfigType
//
//  This container contains the configuration parameters of the CAN
//  interface module.
//****************************************************************************************
//****************************************************************************************
//
//	[SWS_CANIF_00144]
//	This type defines a data structure for the post build parameters
//	of the CAN interface for all underlying CAN drivers.
//	At initialization the CanIf gets a pointer to a structure of this
//	type to get access to its configuration data, which is necessary
//	for initialization.
//
typedef struct
{
	//****************************************************************************************
	//					CanIfInitCfgSet [ECUC_CanIf_00623]
	//
	//	Selects the CAN Interface specific configuration setup. This
	//  type of the external data structure shall contain the post
	//  build initialization data for the CAN Interface for all
	//	underlying CAN Dirvers.
	//	constant to CanIf_ConfigType
	//
	//	Length: 1-32
	//****************************************************************************************
	uint8* CanIfInitCfgSet;
	//****************************************************************************************
	//					CanIfMaxBufferSize  [ECUC_CanIf_00828]
	//
	//	Maximum total size of all Tx buffers.
	//****************************************************************************************
	uint64 CanIfMaxBufferSize;
	//****************************************************************************************
	//					CanIfMaxRxPduCfg   [ECUC_CanIf_00830]
	//
	//	Maximum number of Pdus.
	//****************************************************************************************
	uint64 CanIfMaxRxPduCfg;
	//****************************************************************************************
	//					CanIfMaxTxPduCfg   [ECUC_CanIf_00829]
	//
	//	Maximum number of Pdus.
	//****************************************************************************************
	uint64 CanIfMaxTxPduCfg;
	//****************************************************************************************
	//					CanIfRxPduCfg [ECUC_CanIf_00249]
	//
	//	This container contains the configuration (parameters) of each
	//	receive CAN L-PDU.
	//****************************************************************************************
	CanIfRxPduCfg* CanIfRxPduConfig;
	//****************************************************************************************
	//					CanIfTxPduCfg [ECUC_CanIf_00248]
	//
	//	This container contains the configuration (parameters) of each
	//	transmit receive CAN L-PDU.
	//****************************************************************************************
	CanIfTxPduCfg* CanIfTxPduConfig;
	//****************************************************************************************
	//					CanIfBufferCfg [ECUC_CanIf_00832]
	//
	//	This container contains the Tx buffer configuration. Multiple
	//	buffers with different sizes could be configured
	//****************************************************************************************
	CanIfBufferCfg* CanIfBufferConfig;
	//****************************************************************************************
	//					CanIfInitHohCfg [ECUC_CanIf_00257]
	//
	//	This container contains the references to the configuration
	//	setup of each underlying CAN Driver.
	//****************************************************************************************
	CanIfInitHohCfg* CanIfInitHohConfig;
}CanIfInitCfg;
//************************************************************************



/*****************************************************************************************/
/*                                Callback Configuration                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfDispatchCfg
//	[ECUC_CanIf_00250]
//  Callback functions provided by upper layer modules of the CanIf. The callback functions
//	defined in this container are common to all configured CAN Driver / CAN Transceiver
//	Driver modules.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfDispatchUserCheckTrcvWakeFlagIndicationName [ECUC_CanIf_00791]
	//
	//	This parameter defines the name of <User_CheckTrcvWakeFlagIndication>. If
	//	CanIfDispatchUserCheckTrcvWakeFlagIndicationUL equals CAN_SM the name of
	//	<User_CheckTrcvWakeFlagIndication> is fixed. If it equals CDD, the name is selectable.
	//	If CanIfPublicPnSupport equals False, this parameter shall not be configurable.
	//****************************************************************************************
	void (*CanIfDispatchUserCheckTrcvWakeFlagIndicationName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserCheckTrcvWakeFlagIndicationUL [ECUC_CanIf_00792]
	//
	//	This parameter defines the upper layer module to which the CheckTrcvWakeFlagIndication
	//	from the Driver modules have to be routed. If CanIfPublicPnSupport equals False, this
	//	parameter shall not be configurable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserClearTrcvWufFlagIndicationName [ECUC_CanIf_00789]
	//
	//	This parameter defines the name of <User_ClearTrcvWufFlagIndication>. If
	//	CanIfDispatchUserClearTrcvWufFlagIndicationUL equals CAN_SM the name of
	//	<User_ClearTrcvWufFlagIndication> is fixed. If it equals CDD, the name is selectable.
	//	If CanIfPublicPnSupport equals False, this parameter shall not be configurable.
	//****************************************************************************************
	void (*CanIfDispatchUserClearTrcvWufFlagIndicationName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserClearTrcvWufFlagIndicationUL [ECUC_CanIf_00790]
	//
	//	This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
	//	from the Driver modules have to be routed. If CanIfPublicPnSupport equals False, this
	//	parameter shall not be configurable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserClearTrcvWufFlagIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserConfirmPnAvailabilityName [ECUC_CanIf_00819]
	//
	//	This parameter defines the name of <User_ConfirmPnAvailability>. If
	//	CanIfDispatchUserConfirmPnAvailabilityUL equals CAN_SM the name of
	//	<User_ConfirmPnAvailability> is fixed. If it equals CDD, the name is selectable. If
	//	CanIfPublicPnSupport equals False, this parameter shall not be configurable.
	//****************************************************************************************
	void (*CanIfDispatchUserConfirmPnAvailabilityName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserConfirmPnAvailabilityUL [ECUC_CanIf_00820]
	//
	//	This parameter defines the upper layer module to which the ConfirmPnAvailability
	//	notification from the Driver modules have to be routed. If CanIfPublicPnSupport equals
	//	False, this parameter shall not be configurable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserConfirmPnAvailabilityUL;
	//****************************************************************************************
	//					CanIfDispatchUserCtrlBusOffName [ECUC_CanIf_00257]
	//
	//	This container contains the references to the configuration
	//	setup of each underlying CAN Driver.
	//****************************************************************************************
	void (*CanIfDispatchUserCtrlBusOffName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserCtrlBusOffUL [ECUC_CanIf_00525]
	//
	//	This parameter defines the name of <User_ControllerBusOff>. This parameter depends on
	//	the parameter CanIfDispatchUserCtrlBusOffUL. If CanIfDispatchUserCtrlBusOffUL equals
	//	CAN_SM the name of <User_ControllerBusOff> is fixed. If CanIfDispatchUserCtrlBusOffUL
	//	equals CDD, the name of <User_ControllerBusOff> is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserCtrlBusOffUL;
	//****************************************************************************************
	//					CanIfDispatchUserCtrlModeIndicationName [ECUC_CanIf_00547]
	//
	//	This parameter defines the upper layer (UL) module to which the notifications of all
	//	ControllerBusOff events from the CAN Driver modules have to be routed via
	//	<User_ControllerBusOff>. There is no possibility to configure no upper layer (UL) module
	//	as the provider of <User_ControllerBusOff>.
	//****************************************************************************************
	void (*CanIfDispatchUserCtrlModeIndicationName)(uint8, Can_ControllerStateType);
	//****************************************************************************************
	//					CanIfDispatchUserCtrlModeIndicationUL [ECUC_CanIf_00683]
	//
	//	This parameter defines the name of <User_ControllerModeIndication>. This parameter
	//	depends on the parameter CanIfDispatchUserCtrlModeIndicationUL. If
	//	CanIfDispatchUserCtrlModeIndicationUL equals CAN_SM the name of
	//	<User_ControllerModeIndication> is fixed. If CanIfDispatchUserCtrlModeIndicationUL equals
	//	CDD, the name of <User_ControllerModeIndication> is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserCtrlModeIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserTrcvModeIndicationName [ECUC_CanIf_00684]
	//
	//	This parameter defines the upper layer (UL) module to which the notifications of all
	//	ControllerTransition events from the CAN Driver modules have to be routed via
	//	<User_ControllerModeIndication>.
	//****************************************************************************************
	void (*CanIfDispatchUserTrcvModeIndicationName)(uint8, CanTrcv_TrcvModeType);
	//****************************************************************************************
	//					CanIfDispatchUserTrcvModeIndicationUL [ECUC_CanIf_00685]
	//
	//	This parameter defines the name of <User_TrcvModeIndication>. This parameter depends on
	//	the parameter CanIfDispatchUserTrcvModeIndicationUL. If CanIfDispatchUserTrcvModeIndicationUL
	//	equals CAN_SM the name of <User_TrcvModeIndication> is fixed. If
	//	CanIfDispatchUserTrcvModeIndicationUL equals CDD, the name of <User_TrcvModeIndication>
	//	is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserTrcvModeIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserValidateWakeupEventName [ECUC_CanIf_00686]
	//
	//	This parameter defines the upper layer (UL) module to which the notifications of all
	//	TransceiverTransition events from the CAN Transceiver Driver modules have to be routed
	//	via <User_TrcvModeIndication>. If no UL module is configured, no upper layer callback
	//	function will be called.
	//****************************************************************************************
	void (*CanIfDispatchUserValidateWakeupEventName )(EcuM_WakeupSourceType);
	//****************************************************************************************
	//					CanIfDispatchUserValidateWakeupEventUL [ECUC_CanIf_00531]
	//
	//	This parameter defines the name of <User_ValidateWakeupEvent>. This parameter depends on
	//	the parameter CanIfDispatchUserValidateWakeupEventUL. If CanIfDispatchUserValidateWakeupEventUL
	//	equals ECUM, the name of <User_ValidateWakeupEvent> is fixed. If
	//	CanIfDispatchUserValidateWakeupEventUL equals CDD, the name of <User_ValidateWakeupEvent>
	//	is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserValidateWakeupEventUL;
}CanIfDispatchCfg;


/*****************************************************************************************/
/*                                Can Driver Configuration                               */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfCtrlDrvCfg
//	[ECUC_CanIf_00253]
//  Configuration parameters for all the underlying CAN Driver modules are aggregated under
//	this container. For each CAN Driver module a seperate instance of this container has to
//	be provided.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfCtrlDrvInitHohConfigRef [ECUC_CanIf_00642]
	//
	//	Reference to the Init Hoh Configuration
	//****************************************************************************************
	CanIfInitHohCfg* CanIfCtrlDrvInitHohConfigRef;
	//****************************************************************************************
	//					CanIfCtrlDrvNameRef [ECUC_CanIf_00638]
	//
	//	CAN Interface Driver Reference.
	//	This reference can be used to get any information (Ex. Driver Name, Vendor ID)
	//	from the CAN driver. The CAN Driver name can be derived from the ShortName of the CAN
	//	driver module.
	//****************************************************************************************
//	CanGeneral* CanIfCtrlDrvNameRef;

}CanIfCtrlDrvCfg;


/*****************************************************************************************/
/*                                 Can Trcv Configuration                                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTrcvCfg
//	[ECUC_CanIf_00587]
//	This container contains the configuration (parameters) of one addressed CAN transceiver
//	by the underlying CAN Transceiver Driver module. For each CAN transceiver a seperate
//	instance of this container has to be provided.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfTrcvId [ECUC_CanIf_00654]
	//
	//	This parameter abstracts from the CAN Transceiver Driver specific parameter Transceiver.
	//	Each transceiver of all connected CAN Transceiver Driver modules shall be assigned to one
	//	specific TransceiverId of the CanIf.
	//	Range: 0..number of configured transceivers of all CAN Transceiver Driver modules
	//****************************************************************************************
	uint8* CanIfTrcvId;
	//****************************************************************************************
	//					CanIfTrcvWakeupSupport [ECUC_CanIf_00606]
	//
	//	This parameter defines if a respective transceiver of the referenced CAN Transceiver
	//	Driver modules is queriable for wake up events.
	//****************************************************************************************
	boolean CanIfTrcvWakeupSupport;
	//****************************************************************************************
	//					CanIfTrcvCanTrcvRef [ECUC_CanIf_00605]
	//
	//	This parameter references to the logical handle of the underlying CAN transceiver from
	//	the CAN transceiver driver module to be served by the CAN Interface module.
	//	Range: 0..max. number of underlying supported CAN transceivers
	//****************************************************************************************
//	CanTrcvChannel* CanIfTrcvCanTrcvRef;
}CanIfTrcvCfg;


/*****************************************************************************************/
/*                               CanIf Trcv Configuration                                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTrcvDrvCfg
//	[ECUC_CanIf_00273]
//  This container contains the configuration (parameters) of all addressed CAN transceivers
//	by each underlying CAN Transceiver Driver module. For each CAN transceiver Driver a
//	seperate instance of this container shall be provided.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfTrcvCfgRef
	//
	//	This container contains the configuration (parameters) of one addressed CAN transceiver
	//	by the underlying CAN Transceiver Driver module. For each CAN transceiver a seperate
	//	instance of this container has to be provided.
	//****************************************************************************************
	CanIfTrcvCfg* CanIfTrcvCfgRef;
}CanIfTrcvDrvCfg;


/*****************************************************************************************/
/*                                CanIf Config Container                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIf_ConfigType
//	[ECUC_CanIf_00244]
//  This container includes all necessary configuration sub-containers according the CAN
//	Interface configuration structure.
//****************************************************************************************
typedef struct
{
	//****************************************************************************************
	//					CanIfCtrlDrvCfgRef
	//
	//	Configuration parameters for all the underlying CAN Driver modules are aggregated under
	//	this container. For each CAN Driver module a seperate instance of this container has
	//	to be provided.
	//****************************************************************************************
	CanIfCtrlDrvCfg* CanIfCtrlDrvCfgRef;
	//****************************************************************************************
	//					CanIfDispatchCfgRef
	//
	//	Callback functions provided by upper layer modules of the CanIf. The callback functions
	//	defined in this container are common to all configured CAN Driver / CAN Transceiver
	//	Driver modules.
	//****************************************************************************************
	CanIfDispatchCfg* CanIfDispatchCfgRef;
	//****************************************************************************************
	//					CanIfInitCfgRef
	//
	//	This container contains the init parameters of the CAN Interface.
	//****************************************************************************************
	CanIfInitCfg* CanIfInitCfgRef;
	//****************************************************************************************
	//					CanIfPrivateCfgRef
	//
	//	This container contains the private configuration (parameters) of the CAN Interface.
	//****************************************************************************************
	CanIfPrivateCfg* CanIfPrivateCfgRef;
	//****************************************************************************************
	//					CanIfPublicCfgRef
	//
	//	This container contains the public configuration (parameters) of the CAN Interface.
	//****************************************************************************************
	CanIfPublicCfg* CanIfPublicCfgRef;
	//****************************************************************************************
	//					CanIfTrcvDrvCfgRef
	//
	//	This container contains the configuration (parameters) of all addressed CAN transceivers
	//	by each underlying CAN Transceiver Driver module. For each CAN transceiver Driver a
	//	seperate instance of this container shall be provided.
	//****************************************************************************************
	CanIfTrcvDrvCfg* CanIfTrcvDrvCfgRef;
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
