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

				CanIfDispatchConfig CanIfDispatchCfg;
				
				/*Configuration parameters for all the underlying CAN drivers are aggregated under this container*/
				
				CanIfDriverConfig  CanIfDriverCfg;
				
				/*This container contains the init parameters of the CAN Interface.*/
				
				CanIfInitConfiguration  CanIfInitCfg;
				
				/*This container contains the private configuration (parameters) of the CAN Interface.*/
				
				CanIfPrivateConfiguration   	CanIfPrivateCfg;
				
				/*This container contains the public configuration (parameters) of the CAN Interface.*/
				
				CanIfPublicConfiguration     CanIfPublicCfg;
				
				/*This container contains the configuration (parameters) of all addressed CAN transceivers by each underlying 
				CAN Transceiver Driver*/
				
				CanIfTransceiverDrvConfig   CanIfTransceiverDrvCfg;

}CanIf;


typedef struct {
				/*Selects whether the DLC check is supported.
					True: Enabled False: Disabled*/
		
				bool						CanIfDlcCheck;
	
				/*Description : Defined the number of L-PDU elements for the transmit buffering.
				The Tx L-PDU buffers shall be used to store an L-PDU once for each different L-PDU handle.
				Range: 0..max. number of Tx L-PDUs to be used.
				Default Value: NUMBER_OF_TX_PDUS*/
				
				uint8					CanIfNumberOfTxBuffers;                                       
				
				/*Selects the desired software filter mechanism for reception only. 
				Each implemented software filtering method is identified by this enumeration number.
				Range: Types implemented software filtering methods*/
				
				CanIfSoftwareFilterType  CanIfSoftwareFilter;
				
}CanIfPrivateConfiguration;

typedef struct {
	
	
				/*Enables and disables the development error detection and notification mechanism.
					True: Enabled False: Disabled*/
				bool CanIfDevErrorDetect;
	
	
				/*Selects support for multiple CAN Drivers.
				True: Enabled False: Disabled*/
				bool CanIfMultipleDriverSupport;
				/*Number of served CAN hardware units.
				Range: 1..max. number of underlying supported CAN Hardware units*/

				unit8 CanIfNumberOfCanHwUnits;
	
				/*Configuration parameter to enable/disable the API to poll for Tx Confirmation state.*/
	
				bool CanIfPublicTxConfirmPollingSupport;
	
				/*Enables / Disables the API CanIf_ReadRxPduData() for reading received L-PDU data.
				True: Enabled False: Disabled*/	
				bool CanIfReadRxPduDataApi;
	
				/*Enables and disables the API for reading the received L-PDU data.
				True: Enabled False: Disabled
				Default value :false*/
				
				bool CanIfReadRxPduNotifyStatusApi;
	
	
				/*Enables and disables the API for reading the notification status of transmit and receive L-PDUs.
				True: Enabled False: Disabled*/
				
				bool CanIfReadTxPduNotifyStatusApi;
	
				/*Enables and disables the API for reconfiguration of the CAN Identifier for each Transmit L-PDU.
				True: Enabled False: Disabled*/
	
				bool	CanIfSetDynamicTxIdApi;

				/*Enables and disables the API for reading the version information about the CAN Interface.
				True: Enabled False: Disabled*/
	
				bool CanIfVersionInfoApi;
	
}CanIfPublicConfiguration;
 
typedef struct {
	
	
	
				/*	Selects the CAN Interface specific configuration setup. This type of the external data structure shall 
				contain the post build initialization data for the CAN Interface for all underlying CAN Dirvers.
				constant to CanIf_ConfigType*/
				uint8 CanIfConfigSet[32];
	
	
				/*Total number of CanRxPduIds to be handled. Range: 0..max number of defined CanRxPduIds*/

				uint8 CanIfNumberOfCanRxPduIds;
	
				/*Total number of CanTxPduIds to be handled. Range: 0..max number of defined CanTxPduIds*/
					uint8CanIfNumberOfCanTXPduIds;
	
				/*Total number of dynamic CanTxPduIds to be handled. Range: 0..max. nember of defined CanTxPduIds*/
	
				uint8 CanIfNumberOfDynamicCanTXPduIds;
	
	/***************************************************************************************************************************
	*															Included Containers 
	****************************************************************************************************************************/
				/*This container contains the references to the configuration setup of each underlying CAN driver.*/
				
				CanIfInitControllerConfig CanIfInitControllerCfg; 
				
				/*This container contains the references to the configuration setup of each underlying CAN Driver.*/
				
				CanIfInitHohConfig CanIfInitHohCfg;
				
				/*This container contains the configuration (parameters) of each receive CAN L-PDU.
				The SHORT-NAME of "CanIfRxPduConfig" container itself represents the symolic name of Receive L-PDU.*/
				
				CanIfRxPduConfig CanIfRxPduCfg;
				
				/*This container contains the configuration (parameters) of each transmit CAN L-PDU. 
				The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic name of Transmit L-PDU*/
				
				CanIfTxPduConfig	CanIfTxPduCfg;

}CanIfInitConfiguration;

typedef struct {
				
				/*Name of target BusOff notification services to target upper layers (PduRouter, CanNm, CanTp and ComplexDeviceDrivers).*/

				//FunctionNameDef CanIfBusOffNotification
				

				/*Name of target wakeup notification services to target upper layers (PduRouter, CanNm, CanTp and ComplexDeviceDrivers). 
				If parameter is 0 no call-out function is configured.*/
				
				// FunctionNameDef CanIfWakeupNotification


				/*Name of target wakeup validation notification services to target upper layers (ECU State Manager).
				If parameter is 0 no call-out function is configured.*/

				//FunctionNameDef CanIfWakeupValidNotification
				
}CanIfDispatchConfig;
 

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