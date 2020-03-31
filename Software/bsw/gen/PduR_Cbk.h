#ifndef __PDUR_CBK_H__
#define __PDUR_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void PduR_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void PduR_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__PDUR_CBK_H__
