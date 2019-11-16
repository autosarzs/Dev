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
#define CanIfFixedBuffer                STD_OFF

//*****************************************************************************
//  Selects whether Data Length Check is supported.
//  True: Enabled False: Disabled
//  Default Value: true
//*****************************************************************************
#define CanIfPrivateDataLengthCheck     STD_ON

//*****************************************************************************
//  Selects the desired software filter mechanism for reception only. Each
//  implemented software filtering method is identified by this enumeration
//  number.
//  Range: BINARY
//         INDEX
//         LINEAR
//         TABLE
//	dependency: BasicCAN reception must be enabled by referenced
//	parameter CAN_HANDLE_TYPE of the CAN Driver module via
//	CANIF_HRH_HANDLETYPE_REF for at least one HRH.
//*****************************************************************************
typedef uint8 CanIfPrivateSoftwareFilterType;
#define BINARY	((CanIfPrivateSoftwareFilterType)0x00)
#define INDEX	((CanIfPrivateSoftwareFilterType)0x01)
#define LINEAR	((CanIfPrivateSoftwareFilterType)0x02)
#define TABLE	((CanIfPrivateSoftwareFilterType)0x03)

//*****************************************************************************
//  Defines whether TTCAN is supported.
//  TRUE: TTCAN is supported. FALSE: TTCAN is not supported, only
//  normal CAN communication is possible.
//  Default Value: false
//*****************************************************************************
#define CanIfSupportTTCAN                    	STD_OFF

//*****************************************************************************
//  Switches the development error detection and notification on or off.
//  true: detection and notification is enabled.
//  false: detection and notification is disabled.
//  Default Value: false
//*****************************************************************************
#define CanIfDevErrorDetect                 	STD_OFF

//*****************************************************************************
//  Enable support for dynamic ID handling using L-SDU MetaData.
//  Default Value: false
//*****************************************************************************
#define CanIfMetaDataSupport                	STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable dummy API for upper layer
//  modules which allows to request the cancellation of an I-PDU.
//*****************************************************************************
#define CanIfPublicCancelTransmitSupport    	STD_OFF

//*****************************************************************************
//  Defines header files for callback functions which shall be included in
//	case of CDDs. Range of characters is 1.. 32.
//	Type: EcucStringParamDef
//*****************************************************************************
#define CanIfPublicCddHeaderFile    			32

//*****************************************************************************
//	This parameter is used to configure the Can_HwHandleType. The
//	Can_HwHandleType represents the hardware object handles of a CAN
//	hardware unit. For CAN hardware units with more than 255 HW objects
//	the extended range shall be used (UINT16).
//*****************************************************************************
typedef uint16 CanIfPublicHandleTypeEnum;
#define UINT16 	((CanIfPublicHandleTypeEnum)0xFFFF)
#define UINT8	((CanIfPublicHandleTypeEnum)0x0FF)

//*****************************************************************************
//  Selects support of Pretended Network features in CanIf.
//  True: Enabled False: Disabled
//  Default Value: false
//*****************************************************************************
#define CanIfPublicIcomSupport              	STD_OFF

//*****************************************************************************
//  Selects support for multiple CAN Drivers.
//  True: Enabled False: Disabled
//  Default Value: True
//*****************************************************************************
#define CanIfPublicMultipleDrvSupport       	STD_ON

//*****************************************************************************
//  Selects support of Partial Network features in CanIf.
//  True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicPnSupport                	STD_OFF

//*****************************************************************************
//  Enables / Disables the API CanIf_ReadRxPduData() for reading
//  received L-SDU data.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicReadRxPduDataApi           	STD_OFF

//*****************************************************************************
//  Enables and disables the API for reading the notification status of
//  receive L-PDU.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicReadRxPduNotifyStatusApi   	STD_OFF

//*****************************************************************************
//  Enables and disables the API for reading the notification status of
//  transmit L-PDUs.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicReadTxPduNotifyStatusApi   	STD_OFF

//*****************************************************************************
//  Enables and disables the API for reconfiguration of the CAN Identifier
//  for each Transmit L-PDU.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicSetDynamicTxIdApi          	STD_OFF

//*****************************************************************************
//  Enables and disables the buffering of transmit L-PDUs (rejected by the
//  CanDrv) within the CAN Interface module.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicTxBuffering                	STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable the API to poll for Tx
//  Confirmation state.
//	dependency: CAN State Manager module
//*****************************************************************************
#define CanIfPublicTxConfirmPollingSupport    	STD_OFF

//*****************************************************************************
//  Selects support for wake up validation. True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicWakeupCheckValidSupport		STD_OFF

//*****************************************************************************
//  If enabled, only NM messages shall validate a detected wake-up event
//  in CanIf. If disabled, all received messages corresponding to a
//  configured Rx PDU shall validate such a wake-up event. This
//  parameter depends on CanIfPublicWakeupCheckValidSupport and
//  shall only be configurable, if it is enabled.
//	True: Enabled False: Disabled
//	dependency: CanIfPublicWakeupCheckValidSupport
//*****************************************************************************
#if(CanIfPublicWakeupCheckValidSupport==STD_ON)
	#define CanIfPublicWakeupCheckValidByNM		STD_OFF
#endif

//*****************************************************************************
//  Configuration parameter to enable/disable the CanIf_SetBaudrate API
//  to change the baud rate of a CAN Controller. If this parameter is set to
//  true the CanIf_SetBaudrate API shall be supported. Otherwise the API
//  is not supported
//  Default Value: False
//*****************************************************************************
#define CanIfSetBaudrateApi                   	STD_OFF

//*****************************************************************************
//  Enables the CanIf_TriggerTransmit API at Pre-Compile-Time.
//  Therefore, this parameter defines if there shall be support for trigger
//  transmit transmissions. TRUE: Enabled FALSE: Disabled
//  Default Value: True
//*****************************************************************************
#define CanIfTriggerTransmitSupport           	STD_ON

//*****************************************************************************
//	Determines wether TxOffLineActive feature (see SWS_CANIF_00072)
//	is supported by CanIf. True: Enabled False: Disabled
//	Default value: False
//*****************************************************************************
#define CanIfTxOfflineActiveSupport			  	STD_OFF

//*****************************************************************************
//	Enables and disables the API for reading the version information about
//	the CAN Interface.
//	True: Enabled False: Disabled
//	Default value: False
//*****************************************************************************
#define CanIfVersionInfoApi					  	STD_OFF

//*****************************************************************************
//	Enables the CanIf_CheckWakeup API at Pre-Compile-Time.
//	Therefore, this parameter defines if there shall be support for wake-up.
//	True: Enabled False: Disabled
//	Default value: True
//*****************************************************************************
#define CanIfWakeupSupport						STD_ON

//*****************************************************************************
//	Selects the CAN Interface specific configuration setup. This type of the
//	external data structure shall contain the post build initialization data for
//	the CAN Interface for all underlying CAN Dirvers.
//	constant to CanIf_ConfigType
//	Type: EcucStringParamDef
//*****************************************************************************
#define CanIfInitCfgSet							32

/* Maximum total size of all Tx buffers. This parameter is needed only in
case of post-build loadable implementation using static memory
allocation.
Range: 0..18446744073709551615 */
#define CanIfMaxBufferSizeValue					18446744073709551615

/* Maximum number of Pdus. This parameter is needed only in case of
post-build loadable implementation using static memory allocation.
Range: 0..18446744073709551615 */
#define CanIfMaxRxPduCfgValue					18446744073709551615

/* Maximum number of Pdus. This parameter is needed only in case of
post-build loadable implementation using static memory allocation.
Range: 0..18446744073709551615 */
#define CanIfMaxTxPduCfgValue					18446744073709551615

/* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for
CAN L-PDU transmission. Range: 11 Bit For Standard CAN Identifier
... 29 Bit For Extended CAN identifier
The CAN Identifier may be omitted for dynamic transmit L-PDUs. */
#define CanIfTxPduCanId0						(0U)
#define CanIfTxPduCanId1						(1U)

/* Identifier mask which denotes relevant bits in the CAN Identifier. This
parameter may be used to keep parts of the CAN Identifier of dynamic
transmit L-PDUs static. Range: 11 bits for Standard CAN Identifier, 29
bits for Extended CAN Identifier.
Range: 0 .. 536870911 */
#define CanIfTxPduCanIdMask0					(1<<(uint32)0)
#define CanIfTxPduCanIdMask1					(1<<(uint32)1)

/* Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
Driver module for CAN L-PDU transmission. */
typedef uint8 CanIfTxPduCanIdTypeConfig;
#define EXTENDED_CAN							((CanIfTxPduCanIdTypeConfig)0x00)
#define EXTENDED_FD_CAN							((CanIfTxPduCanIdTypeConfig)0x01)
#define STANDARD_CAN							((CanIfTxPduCanIdTypeConfig)0x02)
#define STANDARD_FD_CAN							((CanIfTxPduCanIdTypeConfig)0x03)

/* ECU wide unique, symbolic handle for transmit CAN L-SDU.
Range: 0..max. number of CantTxPduIds */
#define CanIfTxPduIdValue						(4294967295)

#define CANIF_PUBLIC_PN_SUPPORT				  	STD_OFF

#endif /* __CANIF_CFG_H__ */