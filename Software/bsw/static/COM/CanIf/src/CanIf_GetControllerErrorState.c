/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2020)		                                  **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : CanIf.c         			                                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-26                                                 **
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
**  SPECIFICATION(S) : Specification of CAN Interface, AUTOSAR Release 4.3.1  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#include "CanIf.h"
#include "CanIf_Cbk.h"

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
/* AUTOSAR version checking */
#if ((DET_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION)\
 ||  (DET_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_RELEASE_PATCH_VERSION != CANIF_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif /* AUTOSAR version checking */

/* SW module version checking */
#if ((DET_MAJOR_VERSION != CANIF_SW_MAJOR_VERSION)\
 ||  (DET_MINOR_VERSION != CANIF_SW_MINOR_VERSION)\
 ||  (DET_PATCH_VERSION != CANIF_SW_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif /* SW module version checking */
#endif 

#include "Dem.h"
#include "MemMap.h"

extern CanIfCtrlCfgType CanIfCtrlCfgObj[];

/*
    Private global variables
*/
/******************************************************************************
 CanIf_ModuleState: it's a variable to store the CanIf module state
 CanIf_ModuleStateType: a Data Type that can be one of the following
 CANIF_UNINIT : After power-up/reset, the Can module shall be in the state CAN_UNINIT 
 and also CANIF will be in CANIF_UNINT.
 CANIF_READY  : The function CanIf_Init shall change the module state to CANIF_READY
******************************************************************************/


/* a pointer to the CanIf_ConfigType main Structure for the module to work on */
extern CanIf_ConfigType* CanIf_ConfigPtr;

/********************************************************************************
                            Functions Definitions
********************************************************************************/


/********************************************************************************/
/*             CanIf_GetControllerErrorState service definition                 */
/********************************************************************************/
Std_ReturnType 
CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr)
{
    Std_ReturnType ret_status = E_OK;
	uint8 CanCtrlId = 0;

    /* Report errors */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)

    /* [SWS_CANIF_00661] */
    if (CanIf_ModuleState == CANIF_UNINT)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,
            CANIF_GET_CONTROLLER_ERROR_STATE_SID, CANIF_E_UNINIT);
		ret_status= E_NOT_OK;
    }
    /* [SWS_CANIF_00898] */
    if (ControllerId >= CANIF_CONTROLLERS_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,
            CANIF_GET_CONTROLLER_ERROR_STATE_SID, CANIF_E_PARAM_CONTROLLERID);
		ret_status= E_NOT_OK;
    }
    /* [SWS_CANIF_00899] */
    if (ErrorStatePtr == NULL_PTR)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,
            CANIF_GET_CONTROLLER_ERROR_STATE_SID, CANIF_E_PARAM_POINTER);
		ret_status= E_NOT_OK;
    }
#endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */

    if (ret_status == E_OK)
    {
		/* Get equivalent physical CanControllerId to the logical CanControllerId */
		CanCtrlId = CanIfCtrlCfgObj[ControllerId].CanIfCtrlCanCtrlRef->CanControllerId;
        ret_status = Can_GetControllerErrorState(CanCtrlId, ErrorStatePtr);
    }
    return ret_status;
}
