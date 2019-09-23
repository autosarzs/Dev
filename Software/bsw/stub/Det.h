#ifndef __DET_H__
#define __DET_H__

#include "Std_Types.h"
/* Module Version 1.0.0 */
#define DET_MAJOR_VERSION           (1U)
#define DET_MINOR_VERSION           (0U)
#define DET_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define DET_AR_RELEASE_MAJOR_VERSION   (4U)
#define DET_AR_RELEASE_MINOR_VERSION   (3U)
#define DET_AR_RELEASE_PATCH_VERSION   (1U)

#include "../Vertical_Layer/Std_Types.h"
/* AUTOSAR checking between Std Types and CAN Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DET_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/*****************************************************************************************/
/*                                    Macro Definition                                   */
/*****************************************************************************************/
#define CAN_INIT_API_ID                           0x00
#define CAN_SETBAUDRATE_API_ID                    0x0F
#define CAN_INSTANCE                              0x00
#define CAN_MODULE                                80

#define CAN_E_PARAM_POINTER         0x01
#define CAN_E_PARAM_HANDLE          0x02
#define CAN_E_PARAM_DATA_LENGTH     0x03
#define CAN_E_PARAM_CONTROLLER      0x04
#define CAN_E_UNINIT                0x05
#define CAN_E_TRANSITION            0x06
#define CAN_E_PARAM_BAUDRATE        0x07
#define CAN_E_INIT_FAILED           0x09
/*****************************************************************************************/
/*                                    Function Declaration                               */
/*****************************************************************************************/

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


#endif
