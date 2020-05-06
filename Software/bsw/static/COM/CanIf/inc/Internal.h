/*
 * Internal.h
 * include all global variables used among functions
 */

#ifndef BSW_STATIC_COM_CANIF_INC_INTERNAL_H_
#define BSW_STATIC_COM_CANIF_INC_INTERNAL_H_


/*
 *  Type Description : Struct to map CanIds to a specific L-PDU of type dynamic  .
 */
typedef struct
{
   Can_IdType     CanId;
   PduIdType      PduId;
}str_MapCanIdToPdu ;

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
