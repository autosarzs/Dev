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
**  FILENAME     : CanIf_Lcfg			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-03-17                                                 **
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
**  DESCRIPTION  : CAN Interface Link Time Source file                        **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Inteface, AUTOSAR Release 4.3.1   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#include"CanIf.h"

/** datatypes to be extern-ed:
	- CanControllerCfgType CanControllerCfg
	- CanHardwareObjectType HOHObj**/
CanIfCtrlCfgType CanIfCtrlCfgObj[]
{
	{
		0,								/* CanIfController logical ID */
		STD_OFF,						/* Wakeup Support enabled or disabled */
		extern &CanControllerCfg[0]     /* Reference to CanController Configuration */
	},
	{
		1,								/* CanIfController logical ID */
		STD_OFF,						/* Wakeup Support enabled or disabled */
		extern &CanControllerCfg[1]		/* Reference to CanController Configuration */
	}
};

/*This Object contains configuration parameters related to each HTH.*/
CanIfHthCfgType CanIfHthCfgObj[] /* array of [HTH_OBj_NUM] */
{
	{
		&CanIfCtrlCfgObj[0],			/* Reference to controller Id to which the HTH belongs */
		extern &HOHObj[0]				/* refers to a particular HTH object in the CanDrv configuration */
	},
	{
		&CanIfCtrlCfgObj[0],			/* Reference to controller Id to which the HTH belongs */
		extern &HOHObj[2]				/* refers to a particular HTH object in the CanDrv configuration */
	}
};

CanIfBufferCfgType CanIfBufferCfgObj[] /* Multiplicity: 0..BUFFERS_NUM */
{
	{
		100,							/* Buffer Size */
		&CanIfHthCfgObj[0]				/* Reference to HTH, that defines the hardware object configured for transmission */
	},
	{
		255,							/* Buffer Size */
		&CanIfHthCfgObj[1]				/* Reference to HTH, that defines the hardware object configured for transmission */
	}
};

CanIfTxPduCfgType CanIfTxPduCfgObj[]
{
	{
		0,								/* CAN ID of transmit CAN L-PDUs used by the CAN Interface (physical) */
		0,								/* ID mask which denotes relevant bits in the CAN Identifier */
		STANDARD_CAN,					/* states if transmitted Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
		0,								/* CAN Identifier of transmit CAN L-PDUs used by the CAN Interface (logical) */
		STD_OFF,						/* If CanIfPublicPnFilterSupport is enabled or disabled */
		STD_OFF,						/* Enables and disables transmit confirmation for each transmit CAN L-SDU */
		STD_OFF,						/* If trigger transmit API is enabled or disabled */
		STD_ON,							/* Enables/disables truncation of PDUs that exceed the configured size */
		STATIC,							/* Defines the type of each transmit CAN L-PDU is DYNAMIC or STATIC */
		CAN_NM,							/* the upper layer module to which the indication of the successfully transmitted CANTXPDUID has to be routed via <User_TxConfirmation> */
		&CanIfBufferCfgObj[0]			/* Object to the CanIf buffer configuration */
	},
	{
		1,								/* CAN ID of transmit CAN L-PDUs used by the CAN Interface (physical) */
		1,								/* ID mask which denotes relevant bits in the CAN Identifier */
		STANDARD_CAN,					/* states if transmitted Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
		1,								/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface (logical) */
		STD_OFF,						/* If CanIfPublicPnFilterSupport is enabled or disabled */
		STD_OFF,						/* Enables and disables transmit confirmation for each transmit CAN L-SDU */
		STD_OFF,						/* If trigger transmit API is enabled or disabled */
		STD_ON,							/* Enables/disables truncation of PDUs that exceed the configured size */
		STATIC,							/* Defines the type of each transmit CAN L-PDU is DYNAMIC or STATIC */
		CAN_TP,							/* the upper layer module to which the indication of the successfully transmitted CANTXPDUID has to be routed via <User_TxConfirmation> */
		&CanIfBufferCfgObj[1]			/* Object to the CanIf buffer configuration */
	}
};

CanIfRxPduCanIdRangeType CanIfRxPduCanIdRangeObj[]
{
	{
		0,								/* Lower CAN Identifier of a receive CAN L-PDU for identifier range definition */
		0								/* Upper CAN Identifier of a receive CAN L-PDU for identifier range definition */
	}
};

CanIfHrhRangeCfgType CanIfHrhRangeCfgObj[]
{
	{
		0,								/* The size of this parameter is limited by CanIfHrhRangeRxPduRangeCanIdType, weather its STANDARD or EXTENDED */
		0,								/* mask value in combination with CanIfHrhRangeBaseId for a masked ID range */
		0,								/* Can Pdu ID (Logical) */
		STANDARD,						/* Specifies whether the Range of CAN Ids is STANDARD or EXTENDED CAN Ids */
		0								/* Can Pdu ID (physical) */
	}
};

/*This Object contains configuration parameters for each hardware receive object (HRH)
Note: A controller can contain one or more HRHs */
CanIfHrhCfgType CanIfHrhCfgObj[] /* array of [HRH_OBj_NUM] */
{
	{
		&CanIfCtrlCfgObj[0],			/* Reference to controller Id to which the HRH belongs to */
		extern &HOHObj[1],				/* refers to a particular HRH object in the CanDrv configuration*/	
		&CanIfHrhRangeCfgObj[0]			/* Object to the parameters required for configurating multiple CANID ranges for the same HRH */
	},
	{
		&CanIfCtrlCfgObj[0],			/* Reference to controller Id to which the HRH belongs to */
		extern &HOHObj[3],				/* refers to a particular HRH object in the CanDrv configuration*/	
		&CanIfHrhRangeCfgObj[0]			/* Object to the parameters required for configurating multiple CANID ranges for the same HRH */
	}
};

CanIfRxPduCfgType CanIfRxPduCfgObj[]
{
	{
		0,								/* CAN ID of Receive CAN L-PDUs used by the CAN Interface (physical) */
		0,								/* ID mask which denotes relevant bits in the CAN Identifier */
		STANDARD_CAN,					/* states if received Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
		8,								/* The Data Length of the received CAN L-PDU in Bytes */
		0,								/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface (logical) */
		STD_OFF,						/* Enables and disables the Rx buffering for reading of received L-SDU */
		STD_OFF,						/* Enables and disables receive indication for each receive CAN L-SDU */
		CAN_NM,							/* the upper layer module to which the indication of the successfully received CANRXPDUID has to be routed via <User_RxIndication> */
		&CanIfHrhCfgObj[0],				/* The HRH to which Rx L-PDU belongs to */
		&CanIfRxPduCanIdRangeObj[0]		/* Object that allows to map a range of CAN Ids to one PduId */
	},
	{
		1,								/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface (physical) */
		1,								/* ID mask which denotes relevant bits in the CAN Identifier */
		STANDARD_CAN,					/* states if received Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
		8,								/* The Data Length of the received CAN L-PDU in Bytes */
		1,								/* CAN Identifier of Receive CAN L-PDUs used by the CAN Interface (logical) */
		STD_OFF,						/* Enables and disables the Rx buffering for reading of received L-SDU */
		STD_OFF,						/* Enables and disables receive indication for each receive CAN L-SDU */
		CAN_TP,							/* the upper layer module to which the indication of the successfully received CANRXPDUID has to be routed via <User_RxIndication> */
		&CanIfHrhCfgObj[1],				/* The HRH to which Rx L-PDU belongs to */
		&CanIfRxPduCanIdRangeObj[0]		/* Object that allows to map a range of CAN Ids to one PduId */
	}
};

/* This container contains the references to the configuration setup of each underlying CAN Driver.
so it will have an Object of [CAN_DRIVER_NUM], depending on the number of CAN Drivers */
CanIfInitHohCfgType CanIfInitHohCfgObj[]
{
	{
		&CanIfHrhCfgObj[0],
		&CanIfHthCfgObj[0]
	}
};

CanIfCtrlDrvCfgType CanIfCtrlDrvCfgObj[]
{
	{
		&CanIfInitHohCfgObj,
		&CanIfCtrlCfgObj
	}
};

CanIfInitCfgType CanIfInitCfgObj
{
	CanIfInitCfgSet[0],                 ////////////check this Sahar ///////////////
	18446744073709551615,				/* Maximum Buffer size for all Tx Buffers */
	18446744073709551615,				/* Maximum Rx PDUs */
	18446744073709551615,				/* Maximum Tx PDUs */
	&CanIfBufferCfgObj[0],				/* The corresponding Buffer, if Buffering is enabled, to refer to the corresponding CanIfHthCfg */
	&CanIfInitHohCfgObj[0],				/* The corresponding configuration setup of each underlying CAN Driver */
	&CanIfRxPduCfgObj[0],				/* The corresponding configuration (parameters) of each receive CAN L-PDU */
	&CanIfTxPduCfgObj[0]				/* The corresponding configuration (parameters) of each transmit CAN L-PDU */
};

CanIfDispatchCfgType CanIfDispatchCfgObj = NULL_PTR;

CanIfTrcvCfgType CanIfTrcvCfgObj = NULL_PTR;

CanIfTrcvDrvCfgType CanIfTrcvDrvCfgObj[]
{
	{
		CanIfTrcvCfgObj[0]
	}
};

const CanIf_ConfigType CanIf_ConfigObj
{
	&CanIfCtrlDrvCfgObj[0],
	&CanIfDispatchCfgObj[0],
	&CanIfInitCfgObj[0],
	UINT8,
	LINEAR,
	&CanIfTrcvDrvCfgObj[0]
};
