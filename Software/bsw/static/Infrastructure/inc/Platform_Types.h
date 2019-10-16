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
**  FILENAME     : Platform_Types.h    			                                  **
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

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H
///[SWS_Platform_00027]

/** CPU Type & CPU_BIT_ORDER & CPU_BYTE_ORDER. **/
#define CPU_TYPE_8 8
#define CPU_TYPE_16 16
#define CPU_TYPE_32 32
#define CPU_TYPE_64 64

#define MSB_FIRST 0
#define LSB_FIRST 1

#define HIGH_BYTE_FIRST 0
#define LOW_BYTE_FIRST 1

#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       MSB_FIRST
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST

typedef _Bool      			boolean;
typedef char         		sint8;
typedef unsigned char   	uint8;
typedef signed short       	sint16;
typedef unsigned short  	uint16;
typedef signed long        	sint32;
typedef unsigned long  		uint32;
typedef signed long long   	sint64;
typedef unsigned long long	uint64;
typedef unsigned long       uint8_least;
typedef unsigned long       uint16_least;
typedef unsigned long       uint32_least;
typedef signed long         sint8_least;
typedef signed long         sint16_least;
typedef signed long         sint32_least;
typedef float               float32;
typedef double              float64;


typedef volatile char vint8_t;
typedef volatile uint8 vuint8_t;

typedef volatile sint16 vint16_t;
typedef volatile uint16 vuint16_t;

typedef volatile sint32 vint32_t;
typedef volatile uint32 vuint32_t;

typedef volatile sint64 vint64_t;
typedef volatile uint64 vuint64_t;


//Optimized integer data types
/** Boolean data type. **/
///[SWS_Platform_00034]
#ifndef FALSE
#define FALSE		(0U)
#endif
#ifndef TRUE
#define TRUE		(1U)
#endif

#ifndef False
#define False		(boolean)0
#endif
#ifndef True
#define True		(boolean)1
#endif

#endif
