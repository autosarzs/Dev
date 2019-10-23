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
//*****************************************************************************
#define BINARY
#define INDEX
#define LINEAR
#define TABLE
#define CanIfPrivateSoftwareFilterType  BINARY

//*****************************************************************************
//  Defines whether TTCAN is supported.
//  TRUE: TTCAN is supported. FALSE: TTCAN is not supported, only
//  normal CAN communication is possible.
//  Default Value: false
//*****************************************************************************
#define CanIfSupportTTCAN                    STD_OFF

//*****************************************************************************
//  Switches the development error detection and notification on or off.
//  true: detection and notification is enabled.
//  false: detection and notification is disabled.
//  Default Value: false
//*****************************************************************************
#define CanIfDevErrorDetect                 STD_OFF

//*****************************************************************************
//  Enable support for dynamic ID handling using L-SDU MetaData.
//  Default Value: false
//*****************************************************************************
#define CanIfMetaDataSupport                STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable dummy API for upper layer
//  modules which allows to request the cancellation of an I-PDU.
//*****************************************************************************
#define CanIfPublicCancelTransmitSupport    STD_OFF

//*****************************************************************************
//  Selects support of Pretended Network features in CanIf.
//  True: Enabled False: Disabled
//  Default Value: false
//*****************************************************************************
#define CanIfPublicIcomSupport              STD_OFF

//*****************************************************************************
//  Selects support for multiple CAN Drivers.
//  True: Enabled False: Disabled
//  Default Value: True
//*****************************************************************************
#define CanIfPublicMultipleDrvSupport       STD_ON

//*****************************************************************************
//  Selects support of Partial Network features in CanIf.
//  True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicPnSupport                STD_OFF

//*****************************************************************************
//  Enables / Disables the API CanIf_ReadRxPduData() for reading
//  received L-SDU data.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicReadRxPduDataApi           STD_OFF

//*****************************************************************************
//  Enables and disables the API for reading the notification status of
//  receive L-PDU.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicReadRxPduNotifyStatusApi   STD_OFF

//*****************************************************************************
//  Enables and disables the API for reading the notification status of
//  transmit L-PDUs.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicReadTxPduNotifyStatusApi   STD_OFF

//*****************************************************************************
//  Enables and disables the API for reconfiguration of the CAN Identifier
//  for each Transmit L-PDU.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicSetDynamicTxIdApi          STD_OFF

//*****************************************************************************
//  Enables and disables the buffering of transmit L-PDUs (rejected by the
//  CanDrv) within the CAN Interface module.True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicTxBuffering                STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable the API to poll for Tx
//  Confirmation state.
//*****************************************************************************
#define CanIfPublicTxConfirmPollingSupport    STD_OFF

//*****************************************************************************
//  If enabled, only NM messages shall validate a detected wake-up event
//  in CanIf. If disabled, all received messages corresponding to a
//  configured Rx PDU shall validate such a wake-up event. This
//  parameter depends on CanIfPublicWakeupCheckValidSupport and
//  shall only be configurable, if it is enabled.
//*****************************************************************************
#define CanIfPublicWakeupCheckValidByNM       STD_OFF

//*****************************************************************************
//  Selects support for wake up validation. True: Enabled False: Disabled
//  Default Value: False
//*****************************************************************************
#define CanIfPublicWakeupCheckValidSupport    STD_OFF

//*****************************************************************************
//  Configuration parameter to enable/disable the CanIf_SetBaudrate API
//  to change the baud rate of a CAN Controller. If this parameter is set to
//  true the CanIf_SetBaudrate API shall be supported. Otherwise the API
//  is not supported
//  Default Value: False
//*****************************************************************************
#define CanIfSetBaudrateApi                   STD_OFF

//*****************************************************************************
//  Enables the CanIf_TriggerTransmit API at Pre-Compile-Time.
//  Therefore, this parameter defines if there shall be support for trigger
//  transmit transmissions. TRUE: Enabled FALSE: Disabled
//  Default Value: True
//*****************************************************************************
#define CanIfTriggerTransmitSupport           STD_OFF


#endif /* __CANIF_CFG_H__ */