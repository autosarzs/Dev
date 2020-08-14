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
 **  MAY BE CHANGED BY USER x: no                                               **
 **                                                                            **
 *******************************************************************************/
#include "CanIf.h"
#include "Det.h"
#include "MemMap.h"
#include "CanIf_Cbk.h"
#include "Internal.h"


/*
 * [SWS_CANIF_00330] Configuration of CanIf_ReadRxPduData(): This API can be enabled or disabled at pre-compile time 
 * configuration by the configuration parameter CANIF_PUBLIC_READRXPDU_DATA_API (ECUC_CanIf_00607).
 */

#if(CANIF_PUBLIC_READ_RX_PDU_DATA_API == STD_ON)
Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxSduId,PduInfoType*CanIfRxInfoPtr)
{
    Std_ReturnType Loc_CanIf_ReadRxPduData_Ret =E_OK ;
    Can_ControllerStateType Loc_Controller_Mode=0;
    uint8 Loc_Controller_Id;
    uint8 counter=0;
    
	/*
	 * [SWS_CANIF_00324] The function CanIf_ReadRxPduData() shall not accept a request and return E_NOT_OK, if the 
	 * corresponding controller mode refrenced by ControllerId is different to CAN_CS_STARTED and the channel mode is in the 
	 * receive path online.
     */
	Loc_Controller_Id= CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[CanIfRxSduId].CanIfRxPduHrhIdRef->CanIfHrhCanCtrlIdRef->CanIfCtrlCanCtrlRef->CanControllerId;
    Loc_CanIf_ReadRxPduData_Ret=CanIf_GetControllerMode(Loc_Controller_Id,&Loc_Controller_Mode );
    if (Loc_CanIf_ReadRxPduData_Ret==E_OK )
    {
        if (Loc_Controller_Mode != CAN_CS_STARTED )
		{
            Loc_CanIf_ReadRxPduData_Ret=E_NOT_OK;
		}
		else
		{
			/*
			 * [SWS_CANIF_00325] If parameter CanIfRxSduId of CanIf_ReadRxPduData() has an invalid value, e.g. not configured 
			 * to be stored within CanIf via CANIF_READRXPDU_DATA (ECUC_CanIf_00600), CanIf shall report development error code 
			 * CANIF_E_INVALID_RXPDUID to the Det_ReportError service of the DET, when CanIf_ReadRxPduData() is called. c(SRS_BSW_00323)
			 */
			if (CanIfRxSduId >= RX_CAN_L_PDU_NUM )
			{
			#if ( CANIF_DEV_ERROR_DETECT == STD_ON )
				Det_ReportError(CANIF_MODULE_ID,CANIF_INSTANCE_ID , CANIF_READ_RX_PDU_DATA_API_ID,CANIF_E_INVALID_RXPDUID );
			#endif
				Loc_CanIf_ReadRxPduData_Ret=E_NOT_OK;

			}
			else
			{
				/*
				 * [SWS_CANIF_00326] If parameter CanIfRxInfoPtr of CanIf_ReadRxPduData() has an invalid value, CanIf shall  
				 * report development error code CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET module, when 
				 * CanIf_ReadRxPduData() is called. c(SRS_BSW_00323)
				 */
				if (CanIfRxInfoPtr== NULL)
				{
				#if ( CANIF_DEV_ERROR_DETECT == STD_ON )
				    Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CANIF_RX_INDCIATION_API_ID,CANIF_E_PARAM_POINTER);
				#endif
					Loc_CanIf_ReadRxPduData_Ret=E_NOT_OK;

				}
				else
				{
					/*
					 * [SWS_CANIF_00329] CanIf_ReadRxPduData() shall not be used for CanIfRxSduId, which are defined to receive 
					 * multiple CAN-Ids (range reception). c()
					 * Note: During the call of CanIf_ReadRxPduData() the buffer of CanIfRxInfoPtr is controlled by CanIf and 
					 * this buffer should not be accessed for read/write from another call context. After return of this call  
					 * the ownership changes to the upper layer.
					 */
					if(CanIf_ConfigPtr->CanIfInitCfgRef->CanIfRxPduCfgRef[CanIfRxSduId].CanIfRxPduReadData == TRUE)
				    {
						/*
						 * [SWS_CANIF_00199]  CanIf shall store the received L-SDU in this receive L-SDU buffer. During the 
						 * call of CanIf_ReadRxPduData() the assigned receive L-SDU buffer containing a recently received 
						 * L-SDU, CanIf shall avoid preemptive receive L-SDU buffer access events (refer to [SWS_CANIF_00064]) 
						 * to that receive L-SDU buffer.
						 */
						CanIfRxInfoPtr->MetaDataPtr = RxBuffer[CanIfRxSduId].MetaDataPtr;
						CanIfRxInfoPtr->SduLength   = RxBuffer[CanIfRxSduId].SduLength;
						for(counter=0;counter< RxBuffer[CanIfRxSduId].SduLength;counter++)
						{
							CanIfRxInfoPtr->SduDataPtr[counter] = RxBuffer[CanIfRxSduId].Data[counter];
						}
				    }
					else
					{
					/* Do nothing */
					}
				}
			}
		}
	}
    return Loc_CanIf_ReadRxPduData_Ret;

}
#endif

