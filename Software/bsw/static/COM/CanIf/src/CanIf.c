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
**  FILENAME     : CanIf.c         			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-26                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C		                                                  **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam	                                        **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC	                                            **
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
#include "Det.h"
#include "MemMap.h"

/*private function IDs*/
#define CANIF_CHECK_DLC_API_ID (0xAA)

//Temp canif config variable.
static CanIf_ConfigType CanIf_Config;
static CanIf_ModuleStateType CanIf_ModuleState = CANIF_UNINT;

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/
/******************************************************************************/
/*
 * Brief               	The received Data Length value is compared with the configured
 * 						Data Length value of the received L-PDU.
 * Param-Name[in]      	pPduCfg: Pointer to configured PDU struct.
 * 						pPduInfo: Pointer to recieved L-PDU from lower layer CanDrv.
 * Return              	Std_ReturnType
 *  */
/******************************************************************************/
static Std_ReturnType CanIf_CheckDLC(const CanIfRxPduCfgType *const pPduCfg, const PduInfoType *pPduInfo)
{
    Std_ReturnType return_val = E_OK;
#if (CANIF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
    if (pPduCfg->CanIfRxPduDataLength == pPduInfo->SduLength)
    {
        /*Check success*/
        return_val = E_OK;
    }
    else
    {
        /*[SWS_CANIF_00168] d If the Data Length Check rejects a received LPDU
	 	CanIf shall report runtime error code
		CANIF_E_INVALID_DATA_LENGTH to the Det_ReportRuntimeError() service
		of the DET module.*/
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_CHECK_DLC_API_ID,
                        CANIF_E_INVALID_DATA_LENGTH);
    }
#endif
    return return_val;
}

/******************************************************************************/
/*
 * Brief				Performs Software filtering on recieved Pdus.
 *						it is recommended to offer several search algorithms like
 *						linear search, table search and/or hash search variants to provide the most optimal
 *						solution for most use cases.
 * Param-Name[in]      	pPduCfg: Pointer to configured PDU struct.
 * 						Mailbox: Revcieved Pdu from CanDrv.
 * Return              	Std_ReturnType
 *  */
/******************************************************************************/
static Std_ReturnType CanIf_SW_Filter(const CanIfRxPduCfgType *const pPduCfg, const Can_HwType *Mailbox)
{
    Std_ReturnType ret_val = E_OK;
#if (CANIF_HRH_SOFTWARE_FILTER == STD_ON)
    //Configured sw algorithm is binary.
    if (BINARY == CanIf_ConfigPtr->CanIfPrivateSoftwareFilterType)
    {
    }
    //Configured sw algorithm is index
    else if (INDEX == CanIf_ConfigPtr->CanIfPrivateSoftwareFilterType)
    {
    }
    //Configured sw algorithm is Linear
    else if (LINEAR == CanIf_ConfigPtr->CanIfPrivateSoftwareFilterType)
    {
    }
    //Configured sw algorithm is Table
    else if (TABLE == CanIf_ConfigPtr->CanIfPrivateSoftwareFilterType)
    {
    }
    else
    {
        ret_val = E_NOT_OK;
    }
#endif
    return ret_val;
}

#if (CANIF_SET_BAUDRATE_API == STD_ON)
Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID)
{
    static uint8 current_ControllerId = -1;
    uint8 return_val;

#if (CANIF_DEV_ERROR_DETECT == STD_ON) /* DET notifications */

    /*  [SWS_CANIF_00869] d If CanIf_SetBaudrate() is called with invalid ControllerId, 
		CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID
		to the Det_ReportError service of the DET module. c(SRS_BSW_00323)*/

    if (ControllerId > USED_CONTROLLERS_NUMBER)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_SETBAUDRATE_API_ID,
                        CANIF_E_PARAM_CONTROLLERID);
        return_val = E_NOT_OK;
    }
    else
    {
    }
#endif

    /*  Reentrant for different ControllerIds. Non reentrant for the same ControllerId.
	*/

    if (ControllerId == current_ControllerId)
    {
        /* E_NOT_OK: Service request not accepted */
        return_val = E_NOT_OK;
    }
    else
    {
        current_ControllerId = ControllerId;

        Can_SetBaudrate(ControllerId, BaudRateConfigID);
        /* E_OK: Service request accepted, setting of (new) baud rate started */
        return_val = E_OK;
    }
    return return_val;
}
#endif
/*
	[SWS_CANIF_00415] d Within the service CanIf_RxIndication() the CanIf
	routes this indication to the configured upper layer target service(s). c()
	*/
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
    CanIfRxPduCfgType *TempCanIfRxPduCfgptr;
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /*[SWS_CANIF_00416] d If parameter Mailbox->Hoh of CanIf_RxIndication()
	has an invalid value, CanIf shall report development error code
	CANIF_E_PARAM_HOH to the Det_ReportError service of the DET module,
	when CanIf_RxIndication() is called.*/
    if (Mailbox->Hoh > HRH_OBj_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
                        CANIF_E_PARAM_HOH);
    }
    else
    {
    }
    /*[SWS_CANIF_00417] d If parameter Mailbox->CanId of
	CanIf_RxIndication() has an invalid value, CanIf shall report development
	error code CANIF_E_PARAM_CANID to the Det_ReportError service of the DET
	module, when CanIf_RxIndication() is called.*/
    if (Mailbox->CanId > 3U)
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
                        CANIF_E_PARAM_CANID);
    }
    else
    {
    }

    /*SWS_CANIF_00419] d If parameter PduInfoPtr or Mailbox of
	CanIf_RxIndication() has an invalid value, CanIf shall report development
	error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET
	module, when CanIf_RxIndication() is called.
	*/

    if ((NULL_PTR == Mailbox) || (NULL_PTR == PduInfoPtr))
    {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,
                        CANIF_E_PARAM_POINTER);
    }
    else
    {
    }
#endif
    /*
	[SWS_CANIF_00421] If CanIf was not initialized before calling
	CanIf_RxIndication(), CanIf shall not execute Rx indication handling, when
	CanIf_RxIndication(), is called.
	 */
    if (CanIf_ModuleState == CANIF_READY) 
    {
        // todo maping ...
        if (CanIf_SW_Filter(Mailbox, PduInfoPtr) == E_OK)
        {
            if (CanIf_CheckDLC(TempCanIfRxPduCfgptr, PduInfoPtr) == E_OK)
            {
                // call user
                switch (TempCanIfRxPduCfgptr->CanIfRxPduUserRxIndicationUL)
                {
                case CAN_NM_RX_INDICATION:
                    /* code */
                    break;

                case CAN_TP_RX_INDICATION:
                    /* code */
                    break;

                case CAN_TSYN_RX_INDICATION:
                    /* code */
                    break;

                case CDD_RX_INDICATION:
                    /* code */
                    break;

                case J1939NM_RX_INDICATION:
                    /* code */
                    break;

                case J1939TP_RX_INDICATION:
                    /* code */
                    break;

                case PDUR_RX_INDICATION:
                    /* code */
                    break;

                case XCP_RX_INDICATION:
                    /* code */
                    break;

                default:
                    break;
                }
            }
            else
            {
                /* code */
            }
        }
        else
        {
            /* code */
        }
    }
    else
    {
    }
}
