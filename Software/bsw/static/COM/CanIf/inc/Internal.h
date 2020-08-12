/*
 * Internal.h
 * include all global variables used among functions
 */

#ifndef BSW_STATIC_COM_CANIF_INC_INTERNAL_H_
#define BSW_STATIC_COM_CANIF_INC_INTERNAL_H_


#include "CanIf.h"
/*
 *  Type Description : Struct to map CanIds to a specific L-PDU of type dynamic  .
 */
typedef struct
{
   Can_IdType     CanId;
   PduIdType      PduId;
}str_MapCanIdToPdu ;

/*
 *  Type Description : Struct to help in sorting CanId according to smaller ranges  .
 */
typedef struct
{
    uint32 CanIdStart ;
    uint32 PduId      ;
    uint32 CanIdEnd   ;
}PduSCanIdRangesType;

/*
 *  Type Description : Struct to Buffer received PDUs .
 */
#if(CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
typedef struct
{
    uint8 Data[CANFD_DATA_LENGTH] ;
    uint8* MetaDataPtr            ;
    PduLengthType   SduLength ;
}RxBufferType;

extern RxBufferType RxBuffer[RX_CAN_L_PDU_NUM];

#endif

/*
 *  Struct to help in sorting CanId according to smaller ranges  .
 */
extern PduSCanIdRangesType PduSCanIdRanges[RX_CAN_L_PDU_NUM] ;

/*Array of struct to map CanIds to a specific L-PDU of type dynamic*/
extern str_MapCanIdToPdu  MapCanIdToPdu[TX_CAN_L_PDU_NUM] ;

/*Array to save each logical controller PDUs mode */
extern CanIf_PduModeType CanIf_PduMode[CANIF_CONTROLLERS_NUM] ;

/* a pointer to the CanIf_ConfigType main Structure for the module to work on */
extern CanIf_ConfigType* CanIf_ConfigPtr;

/* Holding the CanIf module current state. Initially, CANIF_UNINT. */
extern CanIf_ModuleStateType CanIf_ModuleState ;

/* Holding the CanIf controller current state. Initially, CAN_CS_STOPPED. */
Can_ControllerStateType CanIf_ControllerState[CANIF_CONTROLLERS_NUM];

 extern CanIfCtrlCfgType CanIfCtrlCfgObj[];


#endif /* BSW_STATIC_COM_CANIF_INC_INTERNAL_H_ */
