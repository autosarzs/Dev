#ifndef __J1939NM_CBK_H__
#define __J1939NM_CBK_H__

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

void J1939Nm_TxConfirmation(
PduIdType TxPduId,
Std_ReturnType result
);

void J1939Nm_RxIndication(
PduIdType RxPduId,
const PduInfoType* PduInfoPtr
);


#endif //__J1939NM_CBK_H__
