#ifndef __XCP_CBK_H__
#define __XCP_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void Xcp_CanIfTxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void Xcp_CanIfRxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__XCP_CBK_H__
