#ifndef INCLUDES_COM_STACK_H_
#define INCLUDES_COM_STACK_H_

#include "Std_Types.h"

typedef uint8 PduIdType ;


typedef uint8 PduLengthType ;


typedef struct {

	uint8* 			SduDataPtr ;
	uint8* 			MetaDatePtr ;
	PduLengthType 	SduLength ;


}PduInfoType;




#endif
