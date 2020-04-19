#include "src/CanIf_Cbk.h"
#include "src/BitHelper.h"
#include "src/ComStack_Types.h"
#include "src/Can_Cfg.h"
#include "src/Can_GeneralTypes.h"
typedef uint8 Can_ModuleStateType;

typedef uint8 Can_DetErrorType;

typedef uint8 Can_ServiceId;

typedef uint8 CanBusoffProcessingType;











typedef uint8 CanWakeupProcessingType;









typedef uint8 CanRxProcessingType;











typedef uint8 CanTxProcessingType;









typedef uint8 CanHandleTypeType;

typedef uint8 CanIdTypeType;















typedef uint8 CanObjectTypeType;

typedef uint8 Can_ErrorStateType;



typedef float64 McuClockReferencePoint;











typedef struct {





 uint16 CanControllerBaudRate;





 uint16 CanControllerBaudRateConfigID;





 uint8 CanControllerPropSeg;





 uint8 CanControllerSeg1;





 uint8 CanControllerSeg2;





 uint8 CanControllerSyncJumpWidth;



} CanControllerBaudrateConfig;









typedef struct {









    uint8 CanControllerId;









    uint32 CanControllerBaseAddress;











    McuClockReferencePoint* CanCpuClockRef;









    CanControllerBaudrateConfig* CanControllerDefaultBaudrate;

} CanController;











typedef struct {





 uint32 CanHwFilterCode;









 uint32 CanHwFilterMask;

} CanHwFilter;











typedef struct

{









    CanHandleTypeType CanHandleType;

    uint16 CanHwObjectCount;









    CanIdTypeType CanIdType;















    uint16 CanObjectId;









    CanObjectTypeType CanObjectType;









    CanController* CanControllerRef;











    CanHwFilter* CanHwFilterRef;









    boolean CanHardwareObjectUsesPolling;

} CanHardwareObject;















typedef struct Can_Pdu

{

    PduIdType swPduHandle ;

    uint8 length;

    Can_IdType id ;

    uint8* sdu ;

}Can_PduType;











typedef struct

{



    CanController *CanControllerRef;



    CanHardwareObject *CanHardwareObjectRef;

} CanConfigSet;









typedef struct

{









    CanController* CanControllerCfgRef;

    CanHardwareObject* CanHardwareObjectRef;



} Can_ConfigType;

void Can_Init(const Can_ConfigType* Config);

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);



void Can_DeInit(void);

Std_ReturnType Can_write ( Can_HwHandleType Hth, const Can_PduType * PduInfo) ;

Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition ) ;

void Can_MainFunction_Read(void) ;

void Can_DisableControllerInterrupts(uint8 Controller);

void Can_EnableControllerInterrupts(uint8 Controller);

Std_ReturnType Can_GetControllerMode(uint8 Controller,Can_ControllerStateType* ControllerModePtr);

void Can_MainFunction_Write(void);
