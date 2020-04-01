#ifndef __CAN_TSYN_CBK_H__
#define __CAN_TSYN_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void CanTSyn_CanIfTxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void CanTSyn_CanIfRxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__CAN_TSYN_CBK_H__
