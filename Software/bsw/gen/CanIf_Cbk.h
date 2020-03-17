#ifndef __CANIF_CBK_H__
#define __CANIF_CBK_H__

#include "Can_GeneralTypes.h"
#include "CanIf_Cfg.h"

/* Module Version 1.0.0 */
#define CAN_IF_TYPES_SW_MAJOR_VERSION           (1U)
#define CAN_IF_TYPES_SW_MINOR_VERSION           (0U)
#define CAN_IF_TYPES_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CAN_IF_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define CAN_IF_TYPES_AR_RELEASE_MINOR_VERSION   (3U)
#define CAN_IF_TYPES_AR_RELEASE_PATCH_VERSION   (1U)


#include "Std_Types.h"
/* AUTOSAR checking between Std Types and CAN Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CAN_IF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CAN_IF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CAN_IF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


//typedef uint32 PduIdType;

void CanIf_TxConfirmation(PduIdType CanTxPduId);

/*apply the cnhages */
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode );
void CanIf_ControllerBusOff(uint8 ControllerId);
/**
 * \brief This callout function is called whenever a CAN message is
 *  received in CAN driver.
 */
extern void CanIf_RxIndication
(
    const Can_HwType * Mailbox,
    const PduInfoType * PduInfoPtr
);

#if(CanIfTriggerTransmitSupport==STD_ON)
/******************************************************************************************/
/*    Function name           : CanIf_TriggerTransmit                                     */
/*    Function Description    :Within this API, the upper layer module (called module)    */
/*                             shall check whether the available data fits into the buffer*/
/*                             size reported by PduInfoPtr->SduLength. If it fits, it     */
/*                             shall copy its data into the buffer provided by            */
/*                             PduInfoPtr->SduDataPtr and update the length of the actual */
/*                             copied data PduInfoPtr->SduLength. If not, it returns      */
/*                              E_NOT_OK without changing PduInfoPtr                      */
/*    Parameter in            : PduIdType TxPduId, PduInfoType* PduInfoPtr                */
/*    Parameter inout         : none                                                      */
/*    Parameter out           : none                                                      */
/*    Return value            : Std_ReturnType                                            */
/*    Requirment              : SWS_CANIF_00883                                           */
/******************************************************************************************/
Std_ReturnType CanIf_TriggerTransmit( PduIdType TxPduId, PduInfoType* PduInfoPtr);
#endif

#endif //__CANIF_CBK_H__
