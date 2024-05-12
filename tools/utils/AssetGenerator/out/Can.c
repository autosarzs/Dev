
/********************************************************************************************            
**                                    AUTOSarZs olc
**                              ------------------------
**                              AUTOSAR free for learning
** 
**   Copyright (C) 2019 AUTOSarZs olc
**   All rights reserved.                                                   
**                                                                   
**   This document contains proprietary information belonging to AUTOSarZs olc. 
**   Passing on and copying of this document, and communication       
**   of its contents is not permitted without prior written authorization.  
**                                                       
**   This software is licensed under the Mozilla Public License Version 2.0.
**   For details, see the LICENSE.txt file in the root directory of this project.
********************************************************************************************/
/*******************************************************************************************
** FILENAME                : Can.c                                                        **
** AUTHOR                  : AUTOSarZs-DevTeam                                            **
** DATE                    : 2024-5-12                                                    **
** VERSION                 : 1.0.0                                                        **
** PLATFORM                : Tiva C                                                       **
** VENDOR                  : AUTOSarZs OLC                                                **
** SPECIFICATION(S)        : Specification of CAN Driver, AUTOSAR Release 4.3.1           **
** MAY BE CHANGED BY USER  : No                                                           **
** DESCRIPTION             : CAN Driver source file                                       **
** LICENSE                 : MPL 2.0                                                      **
********************************************************************************************/


/*******************************************************************************************
**                                 Include Common Headres                                 **
********************************************************************************************/

#include "default_value_x" 

/*******************************************************************************************
**                                 Include Other Headres                                  **
********************************************************************************************/

#include "default_value_x" 

/*******************************************************************************************
**                               Include Component Headres                                **
********************************************************************************************/

#include "default_value_x" 

/*******************************************************************************************
**                                 Local Macro Definition                                 **
********************************************************************************************/

#define default_value_x

/*******************************************************************************************
**                                 Local Types Definition                                 **
********************************************************************************************/

/*****************************************
Description: 
    x
******************************************/
typedef struct can_rx can_rx_t;
/*****************************************
Description: 
    y
******************************************/
typedef y y y;

/*******************************************************************************************
**                             Exported Variables Definition                              **
********************************************************************************************/

/*****************************************
Description: 
    x
******************************************/
extern x x;

/*******************************************************************************************
**                                 Local Enums Definition                                 **
********************************************************************************************/

enum x {
    mem1 = value,
    mem2 = value,
};

/*******************************************************************************************
**                               Local Variables Definition                               **
********************************************************************************************/

ALIGN(4)
u8 can_rx_buffer[256];

/*******************************************************************************************
**                                Local Structs Definition                                **
********************************************************************************************/

struct default_value_x {
    x x;
    x x;
};

/*******************************************************************************************
**                                Local Unions Definition                                 **
********************************************************************************************/

union default_value_x {
    x x;
    x x;
};

/*******************************************************************************************
**                              Local Functions Declaration                               **
********************************************************************************************/

/***********************************************************************
** Description       : This function sets the baud rate              
** Parameters In     : (BaseAddress, BRConfig, CanCpuClock)
** Parameters In Out : None
** Parameters Out    : None
** Return Value      : None
** Requirement       : SWS_Can_00223                                 
** Notes             :                                               
************************************************************************/
__attribute__((always_inline))
static void SetControllerBaudrate(uint32 BaseAddress, CanControllerBaudrateConfig* BRConfig, McuClockReferencePoint CanCpuClock);

/***********************************************************************
** Service Name      : Can_write                                     
** Service Id        : 0x06                                          
** Sync Async        : Synchronous                                   
** Reentrancy        : Reentrant (Thread-Safe)                       
** Parameters In     : (Hth, PduInfo)
** Parameters In Out : None
** Parameters Out    : None
** Return Value      : None
** Description       : This function is called by CanIf to pass a CAN message to CanDrv for transmission.
************************************************************************/
static Std_ReturnType Can_write(Can_HwHandleType Hth, Can_PduType* PduInfo);


/*******************************************************************************************
**                               Local Functions Definition                               **
********************************************************************************************/

/***********************************************************************
** Description       : This function sets the baud rate              
** Parameters In     : (BaseAddress, BRConfig, CanCpuClock)
** Parameters In Out : None
** Parameters Out    : None
** Return Value      : None
** Requirement       : SWS_Can_00223                                 
** Notes             :                                               
************************************************************************/
__attribute__((always_inline))
static void SetControllerBaudrate(uint32 BaseAddress, CanControllerBaudrateConfig* BRConfig, McuClockReferencePoint CanCpuClock)
{
	UNUSED(BaseAddress);
	UNUSED(BRConfig);
	UNUSED(CanCpuClock);

	return 0xFFFFU; 
}

/***********************************************************************
** Service Name      : Can_write                                     
** Service Id        : 0x06                                          
** Sync Async        : Synchronous                                   
** Reentrancy        : Reentrant (Thread-Safe)                       
** Parameters In     : (Hth, PduInfo)
** Parameters In Out : None
** Parameters Out    : None
** Return Value      : None
** Description       : This function is called by CanIf to pass a CAN message to CanDrv for transmission.
************************************************************************/
static Std_ReturnType Can_write(Can_HwHandleType Hth, Can_PduType* PduInfo)
{
	UNUSED(Hth);
	UNUSED(PduInfo);

	return 0xFFFFU; 
}


/*******************************************************************************************
**                              Global Functions Definition                               **
********************************************************************************************/

/***********************************************************************
** Description       : This function sets the baud rate              
** Parameters In     : (BaseAddress, BRConfig, CanCpuClock)
** Parameters In Out : None
** Parameters Out    : None
** Return Value      : None
** Requirement       : SWS_Can_00223                                 
** Notes             :                                               
************************************************************************/
void SetControllerBaudrate(uint32 BaseAddress, CanControllerBaudrateConfig* BRConfig, McuClockReferencePoint CanCpuClock)
{
	UNUSED(BaseAddress);
	UNUSED(BRConfig);
	UNUSED(CanCpuClock);

	return 0xFFFFU; 
}

/***********************************************************************
** Service Name      : Can_write                                     
** Service Id        : 0x06                                          
** Sync Async        : Synchronous                                   
** Reentrancy        : Reentrant (Thread-Safe)                       
** Parameters In     : (Hth, PduInfo)
** Parameters In Out : None
** Parameters Out    : None
** Return Value      : None
** Description       : This function is called by CanIf to pass a CAN message to CanDrv for transmission.
************************************************************************/
Std_ReturnType Can_write(Can_HwHandleType Hth, Can_PduType* PduInfo)
{
	UNUSED(Hth);
	UNUSED(PduInfo);

	return 0xFFFFU; 
}

