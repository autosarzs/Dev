/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)		                                  **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Det.h 					                                  **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-09-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C		                                              **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam	                                      **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC	                                          **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : CAN Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
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

/* AUTOSAR checking between Std Types and CAN Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DET_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


/*****************************************************************************************/
/*                                    Function Declaration                               */
/*****************************************************************************************/

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


#endif
