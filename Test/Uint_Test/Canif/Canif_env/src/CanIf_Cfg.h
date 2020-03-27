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
**  FILENAME     : CanIf_Cfg			                                      **
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
#ifndef __CANIF_CFG_H__
#define __CANIF_CFG_H__

//*****************************************************************************
//  This parameter defines if the buffer element length shall be fixed to 8
//  Bytes for buffers to which only PDUs < 8 Bytes are assigned.
//  TRUE: Minimum buffer element length is fixed to 8 Bytes. FALSE:
//  Buffer element length depends on the size of the referencing PDUs
//  Default Value: false
//*****************************************************************************
#define CANIF_FIXED_BUFFER                		STD_OFF

//*****************************************************************************
//  Selects whether Data Length Check is supported.
//  True: Enabled False: Disabled
//  Default Value: true
//*****************************************************************************
#define CANIF_PRIVATE_DATA_LENGTH_CHECK    		STD_ON

//*****************************************************************************
//  Defines whether TTCAN is supported.
//  TRUE: TTCAN is supported. FALSE: TTCAN is not supported, only
//  normal CAN communication is possible.
//  Default Value: false
//*****************************************************************************
#define CANIF_SUPPORT_TTCAN                    	STD_OFF

//*****************************************************************************
//  Switches the development error detection and notification on or off.
//  true: detection and notification is enabled.
//  false: detection and notification is disabled.
//  Default Value: false
//*****************************************************************************
#define CANIF_DEV_ERROR_DETECT                 	STD_ON

//*****************************************************************************
//  Enable support for dynamic ID handling using L-SDU MetaData.
//  Default Value: false
//*****************************************************************************
#define CANIF_META_DATA_SUPPORT                	STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable dummy API for upper layer
//  modules which allows to request the cancellation of an I-PDU.
//*****************************************************************************
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT   	STD_OFF

//*****************************************************************************
//  Defines header files for callback functions which shall be included in
//	case of CDDs. Range of characters is 1.. 32.
//	Type: EcucStringParamDef
//*****************************************************************************
#define CANIF_PUBLIC_CDD_HEADER_FILE   			32

//*****************************************************************************
//  Selects support of Pretended Network features in CanIf.
//  True: Enabled False: Disabled
//  Default Value: false
//*****************************************************************************
#define CANIF_PUBLIC_ICOM_SUPPORT              	STD_OFF

//*****************************************************************************
//  Selects support for multiple CAN Drivers.
//  True: Enabled False: Disabled
//  Default Value: True
//*****************************************************************************
#define CANIF_PUBLIC_MULTIPLE_DRV_SUPPORT      	STD_ON

//*****************************************************************************
//  Selects support of Partial Network features in CanIf.
//  True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_PN_SUPPORT                	STD_OFF

//*****************************************************************************
//  Enables / Disables the API CanIf_ReadRxPduData() for reading
//  received L-SDU data.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_READ_RX_PDU_DATA_API     	STD_ON


//*****************************************************************************
//  Enables and disables the API for reading the notification status of
//  receive L-PDU.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS_API 	STD_OFF

//*****************************************************************************
//  Enables and disables the API for reading the notification status of
//  transmit L-PDUs.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS_API 	STD_OFF

//*****************************************************************************
//  Enables and disables the API for reconfiguration of the CAN Identifier
//  for each Transmit L-PDU.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_SET_DYNAMIC_TX_ID_API     	STD_OFF

//*****************************************************************************
//  Enables and disables the buffering of transmit L-PDUs (rejected by the
//  CanDrv) within the CAN Interface module.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_TX_BUFFERING             	STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable the API to poll for Tx
//  Confirmation state.
//	dependency: CAN State Manager module
//*****************************************************************************
#define CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT		STD_OFF

//*****************************************************************************
//  Selects support for wake up validation. True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT		STD_OFF

//*****************************************************************************
//  If enabled, only NM messages shall validate a detected wake-up event
//  in CanIf. If disabled, all received messages corresponding to a
//  configured Rx PDU shall validate such a wake-up event. This
//  parameter depends on CanIfPublicWakeupCheckValidSupport and
//  shall only be configurable, if it is enabled.
//	True: Enabled False: Disabled
//	dependency: CanIfPublicWakeupCheckValidSupport
//*****************************************************************************
#if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT==STD_ON)
	#define CANIF_PUBLIC_WAKEUP_CHECK_VALID_BY_NM	STD_OFF
#endif

//*****************************************************************************
//  Configuration parameter to enable/disable the CanIf_SetBaudrate API
//  to change the baud rate of a CAN Controller. If this parameter is set to
//  true the CanIf_SetBaudrate API shall be supported. Otherwise the API
//  is not supported
//  Default Value: False
//*****************************************************************************
#define CANIF_SET_BAUDRATE_API                 	STD_ON

//*****************************************************************************
//  Enables the CanIf_TriggerTransmit API at Pre-Compile-Time.
//  Therefore, this parameter defines if there shall be support for trigger
//  transmit transmissions. TRUE: Enabled FALSE: Disabled
//  Default Value: True
//*****************************************************************************
#define CANIF_TRIGGER_TRANSMIT_SUPPORT         	STD_ON

//*****************************************************************************
//	Determines wether TxOffLineActive feature (see SWS_CANIF_00072)
//	is supported by CanIf. True: Enabled False: Disabled
//	Default value: False
//*****************************************************************************
#define CANIF_TX_OFFLINE_ACTIVE_SUPPORT		  	STD_OFF

//*****************************************************************************
//	Enables and disables the API for reading the version information about
//	the CAN Interface.
//	True: Enabled False: Disabled
//	Default value: False
//*****************************************************************************
#define CANIF_VERSION_INFO_API				  	STD_OFF

//*****************************************************************************
//	Enables the CanIf_CheckWakeup API at Pre-Compile-Time.
//	Therefore, this parameter defines if there shall be support for wake-up.
//	True: Enabled False: Disabled
//	Default value: True
//*****************************************************************************
#define CANIF_WAKEUP_SUPPORT					STD_ON

//*****************************************************************************
//	Selects the CAN Interface specific configuration setup. This type of the
//	external data structure shall contain the post build initialization data for
//	the CAN Interface for all underlying CAN Drivers.
//	constant to CanIf_ConfigType
//	Type: EcucStringParamDef
//  Length: 1 - 32
//*****************************************************************************
#define CANIF_INIT_CFG_SET						(32U)

/* Maximum total size of all Tx buffers. This parameter is needed only in
case of post-build loadable implementation using static memory
allocation.
Range: 0..18446744073709551615 */
#define CANIF_MAX_BUFFER_SIZE					(18446744073709551615)

/* Maximum number of Pdus. This parameter is needed only in case of
post-build loadable implementation using static memory allocation.
Range: 0..18446744073709551615 */
#define CANIF_MAX_RX_PDU_CFG					(18446744073709551615)

/* Maximum number of Pdus. This parameter is needed only in case of
post-build loadable implementation using static memory allocation.
Range: 0..18446744073709551615 */
#define CANIF_MAX_TX_PDU_CFG					(18446744073709551615)

/* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for
CAN L-PDU transmission. Range: 11 Bit For Standard CAN Identifier
... 29 Bit For Extended CAN identifier
The CAN Identifier may be omitted for dynamic transmit L-PDUs. */
#define CANIF_TX_PDU_CAN_ID0					(0U)
#define CANIF_TX_PDU_CAN_ID1					(1U)

/* Identifier mask which denotes relevant bits in the CAN Identifier. This
parameter may be used to keep parts of the CAN Identifier of dynamic
transmit L-PDUs static. Range: 11 bits for Standard CAN Identifier, 29
bits for Extended CAN Identifier.
Range: 0 .. 536870911 */
#define CANIF_TX_PDU_CAN_ID_MASK0				(1<<(uint32)0)
#define CANIF_TX_PDU_CAN_ID_MASK1				(1<<(uint32)1)

/* ECU wide unique, symbolic handle for transmit CAN L-SDU.
Range: 0..max. number of CantTxPduIds. Range: 0 - 4294967295*/
#define CANIF_TX_PDU_ID							(4294967295U)

/* If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
could be configured which will pass the CanIfPnFilter.
If there is no CanIfTxPduPnFilterPdu configured per controller,
the corresponding controller applies no CanIfPnFilter.
dependency: This parameter shall only be configurable if CanIfPublicPnSupport equals True. */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	#define CANIF_TX_PDU_PN_FILTER_PDU			STD_OFF
#endif

/* Enables and disables transmit confirmation for each transmit CAN
L-SDU for reading its notification status.
True: Enabled False: Disabled
dependency: CANIF_READTXPDU_NOTIFY_STATUS_API must be enabled.*/
#if(CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS_API==STD_ON)
	#define CANIF_TX_PDU_READ_NOTIFY_STATUS		STD_OFF
#endif

/* Determines if or if not CanIf shall use the trigger transmit API for this PDU.
dependency: If CanIfTxPduTriggerTransmit is TRUE then CanIfTxPduUserTxConfirmationUL 
has to be either PDUR or CDD and CanIfTxPduUserTriggerTransmitName has to be specified accordingly */
#define CANIF_TX_PDU_TRIGGER_TRANSMIT			STD_OFF

/* Enables/disables truncation of PDUs that exceed the configured size. */
#define CANIF_TX_PDU_TRUNCATION					STD_ON

/* This parameter defines the name of the <User_TriggerTransmit>. This parameter depends on the parameter
CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL equals CAN_TP, CAN_NM, PDUR,
XCP, CAN_TSYN, J1939NM or J1939TP, the name of the <User_TriggerTransmit> is fixed. If CanIfTxPduUserTxConfirmationUL
equals CDD, the name of the <User_TxConfirmation> is selectable. Please be aware that this parameter depends on the same
parameter as CanIfTxPduUserTxConfirmationName. It shall be clear which upper layer is responsible for that PDU.
dependency: CanIfTxPduUserTriggerTransmitName requires CanIfTxPduUserTxConfirmationUL to be either PDUR or CDD.

Note: If CanIfTxPduTriggerTransmit is not specified or FALSE, no upper layer modules have to be configured for
Trigger Transmit. Therefore, <User_TriggerTransmit>() will not be called and CanIfTxPduUserTxConfirmationUL
as well as CanIfTxPduUserTriggerTransmitName need not to be configured.

[SWS_CANIF_00890] Configuration of <User_TriggerTransmit>(): If CanIfTxPduUserTxConfirmationUL is set to PDUR,
CanIfTxPduUserTrigger- TransmitName must be PduR_CanIfTriggerTransmit.

[SWS_CANIF_00891] Configuration of <User_TriggerTransmit>(): If CanIfTxPduUserTxConfirmationUL is set to CDD,
the name of the API <User_TriggerTransmit>() has to be configured via parameter CanIfTxPdu- UserTriggerTransmitName. */
#if(CANIF_TX_PDU_TRIGGER_TRANSMIT==STD_ON)
	#if(CanIfTxPduUserTxConfirmationUL==PDUR)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	PduR_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==CAN_NM)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	CanNm_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==J1939NM)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	J1939Nm_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==J1939TP)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	J1939Tp_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==CAN_TP)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	CanTp_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==XCP)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	Xcp_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==CAN_TSYN)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	CanTSyn_CanIfTriggerTransmit
	#elif(CanIfTxPduUserTxConfirmationUL==CDD)
		#define CANIF_TX_PDU_USER_TRIGGER_TRANSMIT_NAME	Cdd_CanIfTriggerTransmit /* Selectable */
	#endif	
#endif

/* This parameter defines the name of the <User_TxConfirmation>. This parameter depends
on the parameter CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL equals
CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the <User_TxConfirmation> is fixed.
If CanIfTxPduUserTxConfirmationUL equals CDD, the name of the <User_TxConfirmation> is selectable.

Note: If transmit confirmations are not necessary or no upper layer modules are configured
for transmit confirmations and thus <User_TxConfirmation>() shall not be called, CanIfTxPduUserTxConfirmationUL
and CanIfTxPduUserTxConfirmationName need not to be configured.

[SWS_CANIF_00890] Configuration of <User_TriggerTransmit>(): If CanIfTxPduUserTxConfirmationUL
is set to PDUR, CanIfTxPduUserTriggerTransmitName must be PduR_CanIfTriggerTransmit.

[SWS_CANIF_00891] Configuration of <User_TriggerTransmit>(): If CanIfTxPduUserTxConfirmationUL
is set to CDD, the name of the API <User_TriggerTransmit>() has to be configured via parameter CanIfTxPduUserTriggerTransmitName. */
#if(CANIF_TX_PDU_TRIGGER_TRANSMIT==STD_ON)
	#if(CanIfTxPduUserTxConfirmationUL==PDUR)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	PduR_CanIfTxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==CAN_NM)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	CanNm_TxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==J1939NM)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	J1939Nm_TxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==J1939TP)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	J1939Tp_TxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==CAN_TP)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	CanTp_TxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==XCP)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	Xcp_CanIfTxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==CAN_TSYN)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	CanTSyn_CanIfTxConfirmation
	#elif(CanIfTxPduUserTxConfirmationUL==CDD)
		#define CANIF_TX_PDU_USER_TX_CONFIRMATION_NAME	Cdd_CanIfTxConfirmation /* Selectable */
	#endif	
#endif


/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface.
Exa: Software Filtering. This parameter is used if exactly one Can
Identifier is assigned to the Pdu. If a range is assigned then the
CanIfRxPduCanIdRange parameter shall be used.
Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier */
#define CANIF_RX_PDU_CAN_ID0					(0U)
#define CANIF_RX_PDU_CAN_ID1					(1U)

/* Identifier mask which denotes relevant bits in the CAN Identifier. This
parameter defines a CAN Identifier range in an alternative way to
CanIfRxPduCanIdRange. It identifies the bits of the configured CAN
Identifier that must match the received CAN Identifier. Range: 11 bits
for Standard CAN Identifier, 29 bits for Extended CAN Identifier. */
#define CANIF_RX_PDU_CAN_ID_MASK0				(1<<(uint32)0)
#define CANIF_RX_PDU_CAN_ID_MASK1				(1<<(uint32)1)

/* Data length of the received CAN L-PDUs used by the CAN Interface. This information is
used for Data Length Check. Additionally it might specify the valid bits in case of the 
discrete DLC for CAN FD L-PDUs > 8 bytes. The data area size of a CAN L-PDU can have a range from 0 to 64 bytes. */
#define CANIF_RX_PDU_DATA_LENGTH				(8U)

/* ECU wide unique, symbolic handle for receive CAN L-SDU. It shall
fulfill ANSI/AUTOSAR definitions for constant defines. Range: 0..max. number of defined CanRxPduIds
Range: 0 - 4294967295 */
#define CANIF_RX_PDU_ID							(4294967295U)

/* Enables and disables the Rx buffering for reading of received L-SDU
data. True: Enabled False: Disabled
dependency: CANIF_CANPDUID_READDATA_API must be enabled */
#define CANIF_CAN_PDU_ID_READ_DATA_API			(STD_ON)

/* Enables and disables the Rx buffering for reading of received L-SDU
data. True: Enabled False: Disabled
dependency: CANIF_CANPDUID_READDATA_API must be enabled */
#if(CANIF_CAN_PDU_ID_READ_DATA_API==STD_ON)
	#define CANIF_RX_PDU_READ_DATA				(STD_OFF)
#endif

/* Enables and disables receive indication for each receive CAN L-SDU
for reading its notification status.
True: Enabled False: Disabled
dependency: CANIF_READRXPDU_NOTIFY_STATUS_API must be enabled. */
#if(CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS_API==STD_ON)
	#define CANIF_RX_PDU_READ_NOTIFY_STATUS		(STD_OFF)
#endif

/* This parameter defines the name of the <User_RxIndication>. This parameter depends
on the parameter CanIfRxPduUserRxIndicationUL. If CanIfRxPduUserRxIndicationUL equals
CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the <User_RxIndication> is fixed.
If CanIfRxPduUserRxIndicationUL equals CDD, the name of the <User_RxIndication> is selectable.

Note: If receive indications are not necessary or no upper layer modules are configured
for receive indications and thus <User_RxIndication>() shall not be called, CANIF_RXPDU_USERRXINDICATION_UL
and CANIF_RXPDU_USERRXINDICATION_NAME need not to be configured. */
#if(CanIfRxPduUserRxIndicationUL==PDUR)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	PduR_CanIfRxIndication
#elif(CanIfRxPduUserRxIndicationUL==CAN_NM)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	CanNm_RxIndication
#elif(CanIfRxPduUserRxIndicationUL==J1939NM)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	J1939Nm_RxIndication
#elif(CanIfRxPduUserRxIndicationUL==J1939TP)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	J1939Tp_RxIndication
#elif(CanIfRxPduUserRxIndicationUL==CAN_TP)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	CanTp_RxIndication
#elif(CanIfRxPduUserRxIndicationUL==XCP)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	Xcp_CanIfRxIndication
#elif(CanIfRxPduUserRxIndicationUL==CAN_TSYN)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	CanTSyn_CanIfRxIndication
#elif(CanIfRxPduUserRxIndicationUL==CDD)
	#define CANIF_RX_PDU_USER_RX_INDICATION_NAME	Cdd_CanIfRxIndication /* Selectable */
#endif	

/* Lower CAN Identifier of a receive CAN L-PDU for identifier range
definition, in which all CAN Ids are mapped to one PduId.
Range: 0 - 536870911 */
#define CANIF_RX_PDU_CAN_ID_RANGE_LOWER_CAN_ID 		(0U)

/* Upper CAN Identifier of a receive CAN L-PDU for identifier range
definition, in which all CAN Ids are mapped to one PduId.
Range: 0 - 536870911 */
#define CANIF_RX_PDU_CAN_ID_RANGE_UPPER_CAN_ID		(536870911U)

/* This parameter defines the name of <User_CheckTrcvWakeFlagIndication>. If
CanIfDispatchUserCheckTrcvWakeFlagIndicationUL equals CAN_SM the name of
<User_CheckTrcvWakeFlagIndication> is fixed. If it equals CDD, the name is selectable.
If CanIfPublicPnSupport equals False, this parameter shall not be configurable.
dependency: CANIF_DISPATCH_USERCHECKTRCVWAKEFLAGINDICATION_UL, CANIF_PUBLIC_PN_SUPPORT */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	#if(CanIfDispatchUserCheckTrcvWakeFlagIndicationUL==CAN_SM)
		#define CANIF_DISPATCH_USER_CHECK_TRCV_WAKE_FLAG_INDICATION_NAME 	CanSM_CheckTrcvWakeFlagIndication
	#elif(CanIfDispatchUserCheckTrcvWakeFlagIndicationUL==CDD)
		#define CANIF_DISPATCH_USER_CHECK_TRCV_WAKE_FLAG_INDICATION_NAME	Cdd_CheckTrcvWakeFlagIndication
	#endif
#endif

/* This parameter defines the name of <User_ClearTrcvWufFlagIndication>. If
CanIfDispatchUserClearTrcvWufFlagIndicationUL equals CAN_SM the name of
<User_ClearTrcvWufFlagIndication> is fixed. If it equals CDD, the name is selectable.
If CANIF_PUBLIC_PN_SUPPORT equals False, this parameter shall not be configurable. */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	#if(CanIfDispatchUserClearTrcvWufFlagIndicationUL==CAN_SM)
		#define CANIF_DISPATCH_USER_CLEAR_TRCV_WUF_FLAG_INDICATION_NAME		CanSM_ClearTrcvWufFlagIndication
	#elif(CanIfDispatchUserClearTrcvWufFlagIndicationUL==CDD)
		#define CANIF_DISPATCH_USER_CLEAR_TRCV_WUF_FLAG_INDICATION_NAME		Cdd_ClearTrcvWufFlagIndication
	#endif
#endif

/* This parameter defines the name of <User_ConfirmPnAvailability>. If
CanIfDispatchUserConfirmPnAvailabilityUL equals CAN_SM the name of
<User_ConfirmPnAvailability> is fixed. If it equals CDD, the name is selectable.
If CANIF_PUBLIC_PN_SUPPORT equals False, this parameter shall not be configurable. */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
	#if(CanIfDispatchUserConfirmPnAvailabilityUL==CAN_SM)
		#define CANIF_DISPATCH_USER_CONFIRM_PN_AVAILABILITY_NAME		CanSM_ConfirmPnAvailability
	#elif(CanIfDispatchUserConfirmPnAvailabilityUL==CDD)
		#define CANIF_DISPATCH_USER_CONFIRM_PN_AVAILABILITY_NAME		Cdd_ConfirmPnAvailability
	#endif
#endif

/* This parameter defines the name of <User_ControllerBusOff>. This parameter depends on the parameter
CANIF_USERCTRLBUSOFF_UL. If CANIF_USERCTRLBUSOFF_UL equals CAN_SM the name of <User_ControllerBusOff>
is fixed. If CANIF_USERCTRLBUSOFF_UL equals CDD, the name of <User_ControllerBusOff> is selectable. */
#if(CanIfDispatchUserCtrlBusOffUL==CAN_SM)
	#define CANIF_DISPATCH__USER_CTRL_BUS_OFF_NAME					CanSM_ControllerBusOff
#elif(CanIfDispatchUserCtrlBusOffUL==CDD)
	#define CANIF_DISPATCH__USER_CTRL_BUS_OFF_NAME					Cdd_ControllerBusOff
#endif

/* This parameter defines the name of <User_ControllerModeIndication>. This parameter depends on the parameter
CANIF_USERCTRLMODEINDICATION_UL. If CANIF_USERCTRLMODEINDICATION_UL equals CAN_SM the name of <User_ControllerModeIndication>
is fixed. If CANIF_USERCTRLMODEINDICATION_UL equals CDD, the name of <User_ControllerModeIndication> is selectable. */
#if(CanIfDispatchUserCtrlModeIndicationUL==CAN_SM)
	#define CANIF_DISPATCH_USER_CTRL_MODE_INDICATION_NAME			CanSM_ControllerModeIndication
#elif(CanIfDispatchUserCtrlModeIndicationUL==CDD)
	#define CANIF_DISPATCH_USER_CTRL_MODE_INDICATION_NAME			Cdd_ControllerModeIndication
#endif

/* This parameter defines the name of <User_TrcvModeIndication>. This parameter depends on the parameter
CANIF_USERTRCVMODEINDICATION_UL. If CANIF_USERTRCVMODEINDICATION_UL equals CAN_SM the name of <User_TrcvModeIndication>
is fixed. If CANIF_USERTRCVMODEINDICATION_UL equals CDD, the name of <User_TrcvModeIndication> is selectable. */
#if(CanIfDispatchUserTrcvModeIndicationUL==CAN_SM)
	#define CANIF_DISPATCH_USER_TRCV_MODE_INDICATION_NAME			CanSM_TransceiverModeIndication
#elif(CanIfDispatchUserTrcvModeIndicationUL==CDD)
	#define CANIF_DISPATCH_USER_TRCV_MODE_INDICATION_NAME			Cdd_TransceiverModeIndication
#endif

/* This parameter defines the name of <User_ValidateWakeupEvent>. This parameter depends on the parameter
CANIF_USERVALIDATEWAKEUPEVENT_UL. CANIF_USERVALIDATEWAKEUPEVENT_UL equals ECUM the name of <User_ValidateWakeupEvent>
is fixed. CANIF_USERVALIDATEWAKEUPEVENT_UL equals CDD, the name of <User_ValidateWakeupEvent> is selectable. If parameter 
CANIF_WAKEUP_CHECK_VALIDATION_API is disabled, no <User_ValidateWakeupEvent> API can be configured. */
#if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT==STD_ON)
	#if(CanIfDispatchUserValidateWakeupEventUL==ECUM)
		#define CANIF_DISPATCH_USER_VALIDATE_WAKEUP_EVENT_NAME		EcuM_ValidateWakeupEvent
	#elif(CanIfDispatchUserValidateWakeupEventUL==CDD)
		#define CANIF_DISPATCH_USER_VALIDATE_WAKEUP_EVENT_NAME		Cdd_ValidateWakeupEvent
	#endif
#endif

/*This parameter abstracts from the CAN Driver specific parameter
Controller. Each controller of all connected CAN Driver modules shall
be assigned to one specific ControllerId of the CanIf. Range:
0..number of configured controllers of all CAN Driver modules*/
#define CANIF_CTRL_ID							(255U)

/*This parameter defines if a respective controller of the referenced CAN
Driver modules is queriable for wake up events.
True: Enabled False: Disabled*/
#define CANIF_CTRL_WAKEUP_SUPPORT				STD_OFF

/*This parameter abstracts from the CAN Transceiver Driver specific
parameter Transceiver. Each transceiver of all connected CAN
Transceiver Driver modules shall be assigned to one specific
TransceiverId of the CanIf.
Range: 0..number of configured transceivers of all CAN Transceiver
Driver modules*/
#define CANIF_TRCV_ID0							(0U)
#define CANIF_TRCV_ID1							(1U)

/*This parameter defines if a respective transceiver of the referenced
CAN Transceiver Driver modules is queriable for wake up events.
True: Enabled False: Disabled*/
#define CANIF_TRCV_WAKEUP_SUPPORT				STD_OFF

/*Selects the hardware receive objects by using the HRH range/list from
CAN Driver configuration to define, for which HRH a software filtering
has to be performed at during receive processing.
True: Software filtering is enabled False: Software filtering is enabled*/
#define CANIF_HRH_SOFTWARE_FILTER               STD_ON


/*Selects the desired software filter mechanism for reception only. Each
implemented software filtering method is identified by this enumeration
number.*/
#define CanIfPrivateSoftwareFilterValue			(LINEAR)

/*CAN Identifier used as base value in combination with
CanIfHrhRangeMask for a masked ID range in which all CAN Ids shall
pass the software filtering. The size of this parameter is limited by
CanIfHrhRangeRxPduRangeCanIdType*/
#define CANIF_HRH_RANGE_BASE_ID0           		(0U)
#define CANIF_HRH_RANGE_BASE_ID1           		(1U)

/*Used as mask value in combination with CanIfHrhRangeBaseId for a
masked ID range in which all CAN Ids shall pass the software filtering.
The size of this parameter is limited by
CanIfHrhRangeRxPduRangeCanIdType.*/
#define  CANIF_HRH_RANGE_MASK0                	(0U)
#define  CANIF_HRH_RANGE_MASK1                	(1U)

/*Lower CAN Identifier of a receive CAN L-PDU for identifier range
definition, in which all CAN Ids shall pass the software filtering.*/
#define  CANIF_HRH_RANGE_RX_PDU_LOWER_CAN_ID0	     				(0U)
#define  CANIF_HRH_RANGE_RX_PDU_LOWER_CAN_ID1	     				(1U)

/*Upper CAN Identifier of a receive CAN L-PDU for identifier range
definition, in which all CAN Ids shall pass the software filtering.*/
#define CANIF_HRH_RANGE_RX_PDU_UPPER_CAN_ID0			    		(0U)
#define CANIF_HRH_RANGE_RX_PDU_UPPER_CAN_ID1      					(1U)

/*This parameter defines the number of CanIf Tx L-PDUs which can be
buffered in one Txbuffer. If this value equals 0, the CanIf does not
perform Txbuffering for the CanIf Tx L-PDUs which are assigned to this
Txbuffer. If CanIfPublicTxBuffering equals False, this parameter equals
0 for all TxBuffer. If the CanHandleType of the referred HTH equals
FULL, this parameter equals 0 for this TxBuffer.*/
/*TODO check this parameter later */
#if(CANIF_PUBLIC_TX_BUFFERING==STD_OFF)
	#define CANIF_BUFFER_SIZE                  (0U)
//#elif(CanHardwareObject.CanHandleType==FULL)
//	#define CANIF_BUFFER_SIZE                  (1U)
#else	/* any value, implementation dependant */
	#define CANIF_BUFFER_SIZE                  (255U)
#endif


/**************************************************************************************************************
*                                         Sizes of containers muliplicity                                                                  
*************************************************************************************************************/

/* CAN_DRIVER_NUM is a size of array to define the number of underlying CAN Driver modules*/
/* It defines muliplicity of CanIfCtrlDrvCfg & CanIfInitHohCfg containers */
#define  CAN_DRIVER_NUM                             3

/*CAN_TRANSCEIVER_NUM is used to specify the number of containers contains the configuration (parameters)
of all addressed CAN transceivers by each underlying
CAN Transceiver Driver module*/
/*It defines muliplicity of CanIfTrcvDrvCfg & CanIfTrcvCfg containers */
#define CAN_TRANSCEIVER_NUM                         1

/*BUFFERS_NUM is a size of array to define the number of containers contain the Txbuffer configuration.
Multiple buffers with different sizes could be configured.
If CanIfBufferSize (ECUC_CanIf_00834) equals 0, the
CanIf Tx L-PDU only refers via this CanIfBufferCfg the
corresponding CanIfHthCfg.*/
/*It defines muliplicity of CanIfBufferCfg container*/
#define  BUFFERS_NUM                                10

/* RX_CAN_L-PDU_NUM is a size of array to define the number of containers contain the configuration (parameters)
of each receive CAN L-PDU.*/
/*It defines muliplicity of CanIfRxPduCfg container*/
#define RX_CAN_L_PDU_NUM                            10

/*TX_CAN_L-PDU_NUM is a size of array to define the number of containers contain the configuration (parameters)
of each transmit CAN L-PDU.*/
/*It defines muliplicity of CanIfTxPduCfg container*/
#define TX_CAN_L_PDU_NUM                            10 

/*HRH_OBj_NUM is used to specify the number of containers contains configuration parameters for
each hardware receive object (HRH).*/
/*It defines muliplicity of CanIfHrhCfg container*/
#define HRH_OBj_NUM                                 2

/*HTH_OBj_NUM is used to specify the number of containers contains configuration parameters for
each hardware transmit object (HTH).*/
/*It defines muliplicity of CanIfHthCfg container*/
#define HTH_OBj_NUM                                 2

/*CANID_RANGES_NUM is used to specify the number of containers Defines the parameters required for configurating
multiple CANID ranges for a given same HRH*/
/*It defines muliplicity of CanIfHrhRangeCfg container*/
#define CANID_RANGES_NUM                           16    



#endif /* __CANIF_CFG_H__ */
