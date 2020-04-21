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
**  FILENAME     : CanIf_PBcfg			                                      **
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
**  DESCRIPTION  : CAN Interface Post Build Source file                       **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Inteface, AUTOSAR Release 4.3.1   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#include "CanIf.h"


extern  CanHardwareObjectType       HOHObj[]  ;
extern  CanIfCtrlCfgType   CanIfCtrlCfgObj[];

void CanIfRxPduUserRxIndication( PduIdType RxPduId, const PduInfoType* PduInfoPtr ) ;
void CanIfTxPduUserTxConfirmation(PduIdType TxPduId, Std_ReturnType result );


/* [ECUC_CanIf_00628]
 * Defines the parameters required for configurating multiple CANID ranges for a given same HRH.
 */
CanIfHrhRangeCfgType CanIfHrhRangeCfgObj[CANIF_HRH_OBj_NUM] =
{
    {
        0x01,                           /* CAN Identifier used as base value in combination with CanIfHrhRangeMask for a masked ID range*/
        0x7FB,                          /* mask value in combination with CanIfHrhRangeBaseId for a masked ID range */
        0x01,                           /* Lower CAN Identifier of a receive CAN L-PDU*/
        STANDARD,                       /* Specifies whether the Range of CAN Ids is STANDARD or EXTENDED CAN Ids */
        0x03                            /* Upper CAN Identifier of a receive CAN L-PDU */
    }
    ,
    {
        0x05,                           /* CAN Identifier used as base value in combination with CanIfHrhRangeMask for a masked ID range*/
        0x7FF,                          /* mask value in combination with CanIfHrhRangeBaseId for a masked ID range */
        0x05,                           /* Lower CAN Identifier of a receive CAN L-PDU*/
        STANDARD,                       /* Specifies whether the Range of CAN Ids is STANDARD or EXTENDED CAN Ids */
        0x05                            /* Upper CAN Identifier of a receive CAN L-PDU */
    }
};


/* [ECUC_CanIf_00258]
 * This Object contains configuration parameters related to each CanIf_HTH.
 */
CanIfHthCfgType CanIfHthCfgObj[CANIF_HTH_OBj_NUM] = /* array of [HTH_OBJ_NUM] */
{
    {
        &CanIfCtrlCfgObj[0],            /* Reference to controller Id to which the HTH belongs */
        &HOHObj[0]                      /* refers to a particular HTH object in the CanDrv configuration */
    },
    {
        &CanIfCtrlCfgObj[0],            /* Reference to controller Id to which the HTH belongs */
        &HOHObj[2]                      /* refers to a particular HTH object in the CanDrv configuration */
    }
};



/* [ECUC_CanIf_00259]
 * This Object contains configuration parameters related to each CanIf_HRH.
 */
CanIfHrhCfgType CanIfHrhCfgObj[CANIF_HRH_OBj_NUM] =      /* array of [HRH_OBJ_NUM] */
{
    {
        TRUE,                           /* Software filtering is enabled False: Software filtering is enabled*/
        &CanIfCtrlCfgObj[0],            /* Reference to controller Id to which the HTH belongs */
        &HOHObj[0],                     /* refers to a particular HTH object in the CanDrv configuration */
        &CanIfHrhRangeCfgObj[0]         /* Defines the parameters required for configurating multiple CANID ranges for a given same HRH. */
    },
    {
        TRUE,                           /* Software filtering is enabled False: Software filtering is enabled*/
        &CanIfCtrlCfgObj[0],            /* Reference to controller Id to which the HTH belongs */
        &HOHObj[2],                     /* refers to a particular HTH object in the CanDrv configuration */
        &CanIfHrhRangeCfgObj[1]         /* Defines the parameters required for configurating multiple CANID ranges for a given same HRH.*/
    }
};

/*[ECUC_CanIf_00257]
 * This container contains the references to the configuration setup of each underlying CAN Driver. */
CanIfInitHohCfgType CanIfInitHohCfgObj[CAN_DRIVER_NUM] =
{
    {
        CanIfHrhCfgObj,         /*Reference contains configuration parameters for each hardware receive object (HRH).*/
        CanIfHthCfgObj          /*Reference contains parameters related to each HTH. */
    }
};



/* [ECUC_CanIf_00832]
 * This container contains the Txbuffer configuration.
 * Multiple buffers with different sizes could be configured
 */
CanIfBufferCfgType CanIfBufferCfgObj[BUFFERS_NUM] = /* Multiplicity: 0..BUFFERS_NUM */
{
    {
#if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
        1,                         /*[ECUC_CanIf_00834] BufferSize*/
#else
        0,                         /* If CanIfPublicTxBuffering equals False, this parameter equals 0 for all TxBuffer */
#endif
        &CanIfHthCfgObj[0]         /* Reference to HTH, that defines the hardware object configured for transmission */
    },
    {
#if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
        1,                         /*[ECUC_CanIf_00834] BufferSize*/
#else
        0,                         /* If CanIfPublicTxBuffering equals False, this parameter equals 0 for all TxBuffer */
#endif
        &CanIfHthCfgObj[1]         /* Reference to HTH, that defines the hardware object configured for transmission */
    }
};


/*
 * [SWS_CANIF_00063]dThe CanIf shall support buffering of a CAN L-PDU for BasicCAN transmission in the CanIf
 * ,if parameter CanIfPublicTxBuffering (see CanIfPublicTxBuffering) is enabled. (SRS_Can_01020)
 * [SWS_CANIF_00849] For dynamic Transmit L-PDUs, also the CanId has to be stored in the CanIfTxBuffer.
 * */
#if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
/*
 *  array_0 to save the L_PDUs  information of Buffer_0
 *  array elements number equals Buffer_0 Size
 */
CanIfPduInfoCfgType CanIfPduInfoCfgObj_0[1];


/*
 *  array_1 to save the L_PDUs  information of Buffer_1
 *  array elements number equals Buffer_0 Size
 */
CanIfPduInfoCfgType CanIfPduInfoCfgObj_1[1];

/*Struct to map each Buffer with the PDUs saved in it*/
CanIfPduTxBufferCfgType CanIfPduTxBufferCfgObj[BUFFERS_NUM]=
{
    {
        CanIfPduInfoCfgObj_0,         /*Reference to PDUsInfo array for buffer_0  */
        &CanIfBufferCfgObj[0]         /*Reference to buffer_0  Info               */
    },
    {
        CanIfPduInfoCfgObj_1,         /*Reference to PDUsInfo array for buffer_0  */
        &CanIfBufferCfgObj[1]         /*Reference to buffer_0  Info               */
    }
};
#endif

/* [ECUC_CanIf_00248]
 * This container contains the configuration (parameters) of a transmit
 * CAN L-PDU. It has to be configured as often as a transmit CAN L-PDU is needed
 * Post-Build Variant Multiplicit : true
 * */
CanIfTxPduCfgType CanIfTxPduCfgObj[TX_CAN_L_PDU_NUM] =
{
    {
        0x1,                            /* CAN ID of transmit CAN L-PDUs used by the CAN Interface (physical) */
        0x7FF,                          /* ID mask which denotes relevant bits in the CAN Identifier */
        STANDARD_CAN,                   /* states if transmitted Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
        TRUE,                           /* If CanIfPublicPnFilterSupport is enabled or disabled */
#endif
#if(CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS_API==STD_ON)
        TRUE,                           /* Enables and disables transmit confirmation for each transmit CAN L-SDU for reading its notification status.*/
#endif
        FALSE,                          /* If trigger transmit API is enabled or disabled */
        FALSE,                          /* Enables/disables truncation of PDUs that exceed the configured size */
        STATIC_TX_PDU,                  /* Defines the type of each transmit CAN L-PDU is DYNAMIC or STATIC */
#if(CANIF_TX_PDU_TRIGGER_TRANSMIT==STD_ON)
        PduR_CanIfTriggerTransmit,/* This parameter defines the name of the <User_TriggerTransmit>.Currently just a stub function */
#endif

      CanIfTxPduUserTxConfirmation ,  /*This parameter defines the name of the <User_TxConfirmation>.Currently just a stub function*/
      CAN_NM_TX_CONFIRMATION,           /* the upper layer module to which the indication of the successfully transmitted CANTXPDUID has to be routed via <User_TxConfirmation> */
        &CanIfBufferCfgObj[0]           /* Object to the CanIf buffer configuration */
    },

    /*Second TxPdu*/
    {
         0x2,                            /* CAN ID of transmit CAN L-PDUs used by the CAN Interface (physical) */
         0x7FF,                          /* ID mask which denotes relevant bits in the CAN Identifier */
         STANDARD_CAN,                   /* states if transmitted Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
    #if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
         TRUE,                           /* If CanIfPublicPnFilterSupport is enabled or disabled */
    #endif
    #if(CANIF_PUBLIC_READ_TX_PDU_NOTIFY_STATUS_API==STD_ON)
         TRUE,                           /* Enables and disables transmit confirmation for each transmit CAN L-SDU for reading its notification status.*/
    #endif
         FALSE,                          /* If trigger transmit API is enabled or disabled */
         FALSE,                          /* Enables/disables truncation of PDUs that exceed the configured size */
         STATIC_TX_PDU,                  /* Defines the type of each transmit CAN L-PDU is DYNAMIC or STATIC */
    #if(CANIF_TX_PDU_TRIGGER_TRANSMIT==STD_ON)
         PduR_CanIfTriggerTransmit,/* This parameter defines the name of the <User_TriggerTransmit>.Currently just a stub function */
    #endif

       CanIfTxPduUserTxConfirmation,  /*This parameter defines the name of the <User_TxConfirmation>.Currently just a stub function*/
       CAN_NM_TX_CONFIRMATION,           /* the upper layer module to which the indication of the successfully transmitted CANTXPDUID has to be routed via <User_TxConfirmation> */
       &CanIfBufferCfgObj[1]           /* Object to the CanIf buffer configuration */
    }
};

/*
 * [ECUC_CanIf_00743]
 *  Optional container that allows to map a range of CAN Ids to one PduId.
 */
CanIfRxPduCanIdRangeType CanIfRxPduCanIdRangeObj[RX_CAN_L_PDU_NUM] =
{
    {
        0x8,                            /* Lower CAN Identifier of a receive CAN L-PDU for identifier range definition */
        0xA                             /* Upper CAN Identifier of a receive CAN L-PDU for identifier range definition */
    },
    {
        0x4,                            /* Lower CAN Identifier of a receive CAN L-PDU for identifier range definition */
        0x4                             /* Upper CAN Identifier of a receive CAN L-PDU for identifier range definition */
    },

};

/* [ECUC_CanIf_00249]
 * This container contains the configuration (parameters) of each receive CAN L-PDU.
 * */
CanIfRxPduCfgType CanIfRxPduCfgObj[RX_CAN_L_PDU_NUM] =
{
    {
        0x8,                            /* CAN ID of Receive CAN L-PDUs used by the CAN Interface (physical) */
        0x7FC,                          /* ID mask which denotes relevant bits in the CAN Identifier */
        STANDARD_CAN,                   /* states if received Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
        8,                              /* The Data Length of the received CAN L-PDU in Bytes */
#if(CANIF_CAN_PDU_ID_READ_DATA_API==STD_ON)
        TRUE,                           /* Enables and disables the Rx buffering for reading of received L-SDU */
 #endif

#if(CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS_API==STD_ON)
       FALSE,                           /* Enables and disables receive indication for each receive CAN L-SDU */
#endif
        CanIfRxPduUserRxIndication,     /*This parameter defines the name of the <User_RxIndication>. Currently a stub function*/
        CAN_NM_RX_INDICATION,           /* the upper layer module to which the indication of the successfully received CANRXPDUID has to be routed via <User_RxIndication> */
        &CanIfHrhCfgObj[0],             /* The HRH to which Rx L-PDU belongs to */
        &CanIfRxPduCanIdRangeObj[0]     /* Object that allows to map a range of CAN Ids to one PduId */
    },
    /*Second RxPdu*/
    {
     0x4,                            /* CAN ID of Receive CAN L-PDUs used by the CAN Interface (physical) */
     0x7FF,                          /* ID mask which denotes relevant bits in the CAN Identifier */
     STANDARD_CAN,                   /* states if received Pdu Id is of EXTENDED_CAN, EXTENDED_FD_CAN, EXTENDED_NO_FD_CAN, STANDARD_CAN, STANDARD_FD_CAN or STANDARD_NO_FD_CAN */
     8,                              /* The Data Length of the received CAN L-PDU in Bytes */
#if(CANIF_CAN_PDU_ID_READ_DATA_API==STD_ON)
     TRUE,                           /* Enables and disables the Rx buffering for reading of received L-SDU */
#endif

#if(CANIF_PUBLIC_READ_RX_PDU_NOTIFY_STATUS_API==STD_ON)
    FALSE,                           /* Enables and disables receive indication for each receive CAN L-SDU */
#endif
     CanIfRxPduUserRxIndication,     /*This parameter defines the name of the <User_RxIndication>. Currently a stub function*/
     CAN_NM_RX_INDICATION,           /* the upper layer module to which the indication of the successfully received CANRXPDUID has to be routed via <User_RxIndication> */
     &CanIfHrhCfgObj[1],             /* The HRH to which Rx L-PDU belongs to */
     &CanIfRxPduCanIdRangeObj[1]     /* Object that allows to map a range of CAN Ids to one PduId */
    }
};

/*
 *  [ECUC_CanIf_00247]
 *  This container contains the init parameters of the CAN Interface.
 * */
CanIfInitCfgType CanIfInitCfgObj=
{
    /*This container contains the Txbuffer configuration. Multiple buffers with different sizes could be configured. If CanIfBufferSize (ECUC_CanIf_00834) equals 0,
     *the CanIf Tx L-PDU only refers via this CanIfBufferCfg the corresponding CanIfHthCfg.
     *  */
    CanIfBufferCfgObj,
    /*This container contains the references to the configuration setup of each underlying CAN Driver.*/
    CanIfInitHohCfgObj,
    /*This container contains the configuration (parameters) of each receive CAN L-PDU*/
    CanIfRxPduCfgObj,
    /*This container contains the configuration (parameters) of a transmit CAN L-PDU.
     *It has to be configured as often as a transmit CAN L-PDU is needed*/
    CanIfTxPduCfgObj
};

/*[SWS_CANIF_00144]
 * This type defines a data structure for the post build parameters of the CAN interface
 * for all underlying CAN drivers. At initialization the CanIf gets a pointer to a structure
 * of this type to get access to its configuration data, which is necessary for initialization.
 *
 * The contents of the initialization data structure are CAN interface specific .
 */
CanIf_ConfigType  CanIf_ConfigObj =
{
     &CanIfInitCfgObj,                        /*This container contains the init parameters of the CAN Interface.*/
#if(CANIF_PUBLIC_TX_BUFFERING==STD_ON)
     CanIfPduTxBufferCfgObj                   /*Struct to map each TxBuffer with the PDUs saved in it*/
#endif
} ;

