#ifndef __DET_H__
#define __DET_H__

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



Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


#endif