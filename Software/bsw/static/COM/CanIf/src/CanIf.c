#include "CanIf.h"
//#include "CanIf_Types.h"
#include "Det.h"

Std_ReturnType CanIf_GetControllerMode(
uint8 ControllerId,
Can_ControllerStateType* ControllerModePtr
)
{
	/* [SWS_CANIF_00313] d If parameter ControllerId of
	CanIf_GetControllerMode() has an invalid, the CanIf shall report development
	error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
	of the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
	if (ControllerId != 0 || ControllerId != 1){
	  	  Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CanIf_GetControllerMode_Id, CANIF_E_PARAM_CONTROLLERID);

	  	  return E_NOT_OK;
	}

	/*[SWS_CANIF_00656] d If parameter ControllerModePtr of
	CanIf_GetControllerMode() has an invalid value, the CanIf shall report development
	error code CANIF_E_PARAM_POINTER to the Det_ReportError service of
	the DET, when CanIf_GetControllerMode() is called. c(SRS_BSW_00323)*/
	if(ControllerModePtr == 0){
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CanIf_GetControllerMode_Id, CANIF_E_PARAM_POINTER);

		return E_NOT_OK;
	}

	Can_GetControllerMode(ControllerId, ControllerModePtr);
}
