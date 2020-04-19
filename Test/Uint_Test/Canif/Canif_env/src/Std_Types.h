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
**  FILENAME     : Std_Types.h    			                                  **
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
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"

#ifndef NULL
#define	NULL	0
#endif

typedef struct {
	uint16 vendorID;
	uint16 moduleID;
	uint8  instanceID;
/** Vendor numbers */
	uint8 sw_major_version;
	uint8 sw_minor_version;
	uint8 sw_patch_version;
/** Autosar spec. numbers */
	uint8 ar_major_version;
	uint8 ar_minor_version;
	uint8 ar_patch_version;
} Std_VersionInfoType;

/** See AUTOSAR_SWS_CompilerAbstraction-->11.3 Published Information. **/
/** make compare number... #if version > 10203  ( 1.2.3 ) */
#define STD_GET_VERSION (_major,_minor,_patch) (_major * 10000 + _minor * 100 + _patch)

/** Create Std_VersionInfoType */
#define STD_GET_VERSION_INFO(_vi,_module) \
	if(_vi != NULL) {\
		((_vi)->vendorID =  _module ## _VENDOR_ID);\
		((_vi)->moduleID = _module ## _MODULE_ID);\
		((_vi)->sw_major_version = _module ## _SW_MAJOR_VERSION);\
		((_vi)->sw_minor_version =  _module ## _SW_MINOR_VERSION);\
		((_vi)->sw_patch_version =  _module ## _SW_PATCH_VERSION);\
		((_vi)->ar_major_version =  _module ## _AR_MAJOR_VERSION);\
		((_vi)->ar_minor_version =  _module ## _AR_MINOR_VERSION);\
		((_vi)->ar_patch_version =  _module ## _AR_PATCH_VERSION);\
	}


typedef uint8 Std_ReturnType;


#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1


#define STD_HIGH		0x01
#define STD_LOW			0x00

#define STD_ACTIVE		0x01
#define STD_IDLE		0x00

#define STD_ON			0x01
#define STD_OFF			0x00

#define STD_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION   (3U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION   (1U)

#endif
