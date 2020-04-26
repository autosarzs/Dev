#ifndef __CANTP_CBK_H__
#define __CANTP_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void CanTp_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void CanTp_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__CANTP_CBK_H__
