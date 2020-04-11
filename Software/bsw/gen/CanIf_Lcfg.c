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
extern  CanControllerType     CanControllerCfg[]  ;

/*To be initialized in CanI_Init() */
CanIfTxPduCfgType* CanIfTxPduCfgPtr = NULL_PTR ;
CanIfRxPduCfgType* CanIfRxPduCfgPtr = NULL_PTR ;
CanIfHrhCfgType*   CanIfHrhCfgPtr   = NULL_PTR ;
CanIfHthCfgType*   CanIfHthCfgPtr   = NULL_PTR ;

/* [ECUC_CanIf_00546]
 * This container contains the configuration (parameters) of an adressed
 * CAN controller by an underlying CAN Driver module. This container
 * is configurable per CAN controller.
 */
CanIfCtrlCfgType CanIfCtrlCfgObj[CANIF_CONTROLLERS_NUM] =
{
	{
		STD_OFF,						/* Wakeup Support enabled or disabled */
		&CanControllerCfg[0]            /* Reference to CanController Configuration */
	}
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

