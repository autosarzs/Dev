#ifndef __CANNM_CBK_H__
#define __CANNM_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void CanNm_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void CanNm_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__CANNM_CBK_H__
