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


/*extern CANDrv HOH configurations*/
extern CanIfInitHohCfgType CanIfInitHohCfgObj[] ;
/*extern CANDrv Controllers configurations*/
extern CanControllerType CanControllerCfg[];

/*To be initialized in CanI_Init() */
CanIfTxPduCfgType* CanIfTxPduCfgPtr = NULL_PTR ;
CanIfRxPduCfgType* CanIfRxPduCfgPtr = NULL_PTR ;
CanIfHrhCfgType*   CanIfHrhCfgPtr   = NULL_PTR ;
CanIfHthCfgType*   CanIfHthCfgPtr   = NULL_PTR ;

void CanSM_CheckTrcvWakeFlagIndication(uint8 TransceiverId);
void CanSM_ClearTrcvWufFlagIndication(uint8 TransceiverId);
void CanSM_ConfirmPnAvailability(uint8 TransceiverId);
void CanSM_ControllerBusOff(uint8 ControllerId);
void CanSM_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode);
void CanSM_TransceiverModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources);

/* [ECUC_CanIf_00546]
 * This container contains the configuration (parameters) of an adressed
 * CAN controller by an underlying CAN Driver module. This container
 * is configurable per CAN controller.
 */
CanIfCtrlCfgType CanIfCtrlCfgObj[CANIF_CONTROLLERS_NUM] =
{
	{
		STD_OFF,			/* Wakeup Support enabled or disabled */
		CanControllerCfg	/* Reference to CanController Configuration */
	},
};


/*
 *  [ECUC_CanIf_00253]
 *  Configuration parameters for all the underlying CAN Driver modules are
 *  aggregated under this container. For each CAN Driver module a seperate
 *  instance of this container has to be provided.
 */
CanIfCtrlDrvCfgType CanIfCtrlDrvCfgObj[CAN_DRIVER_NUM] =
{
    {
        &CanIfInitHohCfgObj[0],        /*Reference to the Init Hoh Configuration*/
        &CanIfCtrlCfgObj[0]            /*Reference to the configuration (parameters) of adressed CAN controllers*/
    }
};

CanIfDispatchCfgType CanIfDispatchCfgObj =
{
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
     /* [ECUC_CanIf_00791] */
     CanSM_CheckTrcvWakeFlagIndication,     /* This parameter defines the name of <User_CheckTrcvWakeFlagIndication>. */
#endif

#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
     CAN_SM_DISPATCH_CHECK_TRCV_WAKE_FLAG,  /* This parameter defines the upper layer module to which the CheckTrcvWakeFlagIndication from the Driver modules have to be routed. */
#endif

#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
     /* [ECUC_CanIf_00789] */
     CanSM_ClearTrcvWufFlagIndication,      /* This parameter defines the name of <User_ClearTrcvWufFlagIndication>. */
#endif

#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
     CAN_SM_DISPATCH_CLEAR_TRCV_WUF_FLAG,   /* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication from the Driver modules have to be routed. */
#endif

     /* [ECUC_CanIf_00819] */
#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
     CanSM_ConfirmPnAvailability,           /*This parameter defines the name of <User_ConfirmPnAvailability>. */
#endif

#if(CANIF_PUBLIC_PN_SUPPORT==STD_ON)
     CAN_SM_DISPATCH_CONFIRM_PN,            /* This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication from the Driver modules have to be routed. */
#endif

     /* [ECUC_CanIf_00525] */
     CanSM_ControllerBusOff,                /* This parameter defines the name of <User_ControllerBusOff>. */

     CAN_SM_DISPATCH_CTRL_BUS_OFF,          /* This parameter defines the upper layer (UL) module to which the notifications of all ControllerBusOff events from the CAN Driver modules have to be routed via <User_ControllerBusOff>. */

     /* [ECUC_CanIf_00683] */
     CanSM_ControllerModeIndication,        /* This parameter defines the name of <User_ControllerModeIndication>. */

     CAN_SM_DISPATCH_CTRL_MODE,             /* This parameter defines the upper layer (UL) module to which the notifications of all ControllerTransition events from the CAN Driver modules have to be routed via <User_ControllerModeIndication>. */

     /* [ECUC_CanIf_00685] */
     CanSM_TransceiverModeIndication,       /* This parameter defines the name of <User_TrcvModeIndication>. */

     CAN_SM_DISPATCH_TRCV_MODE,             /* This parameter defines the upper layer (UL) module to which the notifications of all TransceiverTransition events from the CAN Transceiver Driver modules have to be routed via <User_TrcvModeIndication>. */

     /* [ECUC_CanIf_00531] */
#if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT == STD_ON)
     EcuM_ValidateWakeupEvent,              /* This parameter defines the name of <User_ValidateWakeupEvent>. */
#endif

#if(CANIF_PUBLIC_WAKEUP_CHECK_VALID_SUPPORT==STD_ON)
     ECUM_DISPATCH_VALIDATE_WAKEUP_EVENT    /* This parameter defines the upper layer (UL) module to which the notifications about positive former requested wake up sources have to be routed via <User_ValidateWakeupEvent>. */
#endif

};

