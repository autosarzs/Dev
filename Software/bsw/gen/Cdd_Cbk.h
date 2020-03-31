#ifndef __CDD_CBK_H__
#define __CDD_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void Cdd_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void Cdd_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__CDD_CBK_H__
