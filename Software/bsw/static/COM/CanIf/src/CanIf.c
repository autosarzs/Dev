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

/*
    Private global variables
*/
/******************************************************************************
 CanIf_ModuleState: it's a variable to store the CanIf module state
 CanIf_ModuleStateType:
 CANIF_UNINIT : After power-up/reset, the Can module shall be in the state CAN_UNINIT 
 and also CANIF will be in CANIF_UNINT.
 CANIF_READY  : The function CanIf_Init shall change the module state to CANIF_READY
******************************************************************************/
static CanIf_ModuleStateType CanIf_ModuleState = CANIF_UNINT;

static CanIf_ControllerStateType CanIf_ControllerState[CANIF_CONTROLLERS_NUM];

/* CanIf PDU current mode. Initially, CANIF_OFFLINE [SWS_CANIF_00864]. */
static CanIf_PduModeType CanIf_PduMode[CANIF_CONTROLLERS_NUM] = {CANIF_OFFLINE};// Init them all by CANIF_OFFLINE as default is CANIF_OFFLINE

/* a pointer to the CanIf_ConfigType main Structure for the module to work on */
static CanIf_ConfigType* CanIf_ConfigPtr = NULL_PTR;

/*******************************************************************************
*           CAN, CAN IF Controller ID Mapping Functions Declarations           *
*******************************************************************************/
static uint8 CanIf_GetCanController_Mapping(uint8 CanIfControllerId);
static uint8 Can_GetCanIfController_Mapping(uint8 CanCtrlId, uint8 CanDrvId);

/*******************************************************************************
*           CAN, CAN IF Controller ID Mapping Functions Definitions            *
*******************************************************************************/
static uint8 CanIf_GetCanController_Mapping(uint8 CanIfControllerId)// has CanController logical Id and want to get the physical Id
{
	for(uint8 CanDrvNum = 0; CanDrvNum < CAN_DRIVER_NUM; CanDrvNum++)
	{
		for(uint8 CanIfCtrlNum = 0; CanIfCtrlNum < CANIF_CONTROLLERS_NUM; CanIfCtrlNum++)
		{
			if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CanDrvNum].CanIfCtrlCfgObj[CanIfCtrlNum].CanIfCtrlId) == CanIfControllerId)
			{
				return (CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CanDrvNum].CanIfCtrlCfgObj[CanIfCtrlNum].CanIfCtrlCanCtrlRef->CanControllerId);
			}
		}
	}
	/*
	uint8 ret = 255;
	switch(CanIfControllerId)
	{
		case CANIF_CTRL_ID_0:
		if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlId) == CanIfControllerId)
		{
			ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlCanCtrlRef->CanControllerId;
		}
		else if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlId) == CanIfControllerId)
		{
			ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlCanCtrlRef->CanControllerId;
		}
		else
		{
			
		}
		break;
		case CANIF_CTRL_ID_1:
		if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlId) == CanIfControllerId)
		{
			ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlCanCtrlRef->CanControllerId;
		}
		else if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlId) == CanIfControllerId)
		{
			ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlCanCtrlRef->CanControllerId;
		}
		else
		{
			
		}
		break;
		default:
		break;
	}
	return ret;
	*/
	return 255;
}

/* any Can Driver that uses this Function (Like: CanIf_RxIndication) will have the Can Driver Id that will be passed to this
Mapping function to get the Logical CanIfController Id */
static uint8 Can_GetCanIfController_Mapping(uint8 CanCtrlId, uint8 CanDrvId)// has CanController physical Id and want to get the logical Id
{
	for(uint8 CanIfCtrlNum = 0; CanIfCtrlNum < CANIF_CONTROLLERS_NUM; CanIfCtrlNum++)
	{
		if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CanDrvId].CanIfCtrlCfgObj[CanIfCtrlNum].CanIfCtrlCanCtrlRef->CanControllerId) == CanCtrlId)
		{
			return (CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CanDrvId].CanIfCtrlCfgObj[CanCtrlNum].CanIfCtrlId);
		}
	}
	/*
	uint8 ret = 255;
	switch(CanDrvId)
	{
		case CAN0_ID:
		switch(CanCtrlId)
		{
			case CONTROLLER_0_ID:
			if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_0_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlId;
			}
			else if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_0_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlId;
			}
			break;
			case CONTROLLER_1_ID:
			if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_1_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlId;
			}
			else if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_1_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN0_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlId;
			}
			break;
			default:
			break;
		}
		break;
		case CAN1_ID:
		switch(CanCtrlId)
		{
			case CONTROLLER_0_ID:
			if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_0_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlId;
			}
			else if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_0_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlId;
			}
			break;
			case CONTROLLER_1_ID:
			if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_1_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_0].CanIfCtrlId;
			}
			else if((CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlCanCtrlRef->CanControllerId)==CONTROLLER_1_ID)
			{
				ret = CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[CAN1_ID].CanIfCtrlCfgObj[CANIF_CTRL_ID_1].CanIfCtrlId;
			}
			break;
			default:
			break;
		}
		break;
		default:
		break;
	}
	return ret;
	*/
	return 255;
}

/*******************************************************************************
*                    Functions Definitions                                     *
*******************************************************************************/
/*                  CanIf_SetPduMode service definition                       */
Std_ReturnType
CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest)
{
	uint8 CanCtrlId = CanIf_GetCanController_Mapping(ControllerId);
	if(CanIf_ControllerState[CanCtrlId]==CAN_CS_STARTED)
	{
		/* Implementation here */
		// CanIf_ConfigPtr->CanIfCtrlDrvCfgObj[ControllerId].CanIfCtrlCfgObj[ControllerId].CanIfCtrlCanCtrlRef->CanControllerId;
		// /* Pass the current PDU mode to PduModePtr */
		// *PduModePtr = CanIf_PduMode;
	}
	else
	{
		
	}
	
	
    CanIf_PduMode = PduModeRequest;
    /* Implementation here */
}

/*******************************************************************************/
/*                  CanIf_GetPduMode service definition                        */
Std_ReturnType 
CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr)
{
    Std_ReturnType ret_status = E_OK;

    /* Report errors */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)

    /* [SWS_CANIF_00661] */
    if (CANIF_UNINT == CanIf_ModuleState)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,
            CANIF_GET_PDU_MODE_SID, CANIF_E_UNINIT);
        ret_status = E_NOT_OK;
    }
    /* [SWS_CANIF_00346] */
    if (ControllerId >= USED_CONTROLLERS_NUMBER)// shouldn't it be CANIF_CONTROLLERS_NUM instead of USED_CONTROLLERS_NUMBER
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,
            CANIF_GET_PDU_MODE_SID, CANIF_E_PARAM_CONTROLLERID);
        ret_status = E_NOT_OK;
    }
    /* [SWS_CANIF_00657]  */
    if (NULL_PTR == PduModePtr)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,
            CANIF_GET_PDU_MODE_SID, CANIF_E_PARAM_POINTER);
        ret_status = E_NOT_OK;
    }
#endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
	
    /* Pass the current PDU mode to PduModePtr */
    *PduModePtr = CanIf_PduMode[ControllerId];
    return ret_status;
}