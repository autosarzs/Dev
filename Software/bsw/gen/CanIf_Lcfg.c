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
#include "CanIf_Lcfg.h"


/*To be initialized in CanI_Init() */
CanIfTxPduCfgType* CanIfTxPduCfgPtr = NULL_PTR ;
CanIfRxPduCfgType* CanIfRxPduCfgPtr = NULL_PTR ;
CanIfHrhCfgType*   CanIfHrhCfgPtr   = NULL_PTR ;
CanIfHthCfgType*   CanIfHthCfgPtr   = NULL_PTR ;

extern  CanHardwareObjectType           HOHObj[]  ;
extern  CanIfHrhRangeCfgType CanIfHrhRangeCfgObj[];

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

