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
**  FILENAME     : Can.c         			                                  **
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


/*****************************************************************************************/
/*                                   Include Common headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Other  headres                              */
/*****************************************************************************************/

#include "Det.h"

/*****************************************************************************************/
/*                                   Include Component headres                           */
/*****************************************************************************************/
#include "hw_can.h"
#include "Can_lib.h"
#include "Can.h"
/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/

#define valid      1
#define invalid    0

/*****************************************************************************************/
/*                                   Local Definition                                    */
/*****************************************************************************************/
/*    Description        :   
 */

/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/
/*    Type Description        : variable define can controller state                     */
/*    Type range              :  0->255                                                  */
/*    Requirment              : SWS                                                      */
typedef uint8 Can_ControllerStateType;

/*    Type Description      : 	Struct to map each software meesage object with the number
 its configured hardware message objects in the HW FIFO
 HOHId     	: 	SW meesage objectId from CANIF
 StartMessageId  : 	ID of the first hardware meesage object in the HW FIFO
 StartMessageId  : 	ID of the last  hardware meesage object in the HW FIFO    */
typedef struct {
	uint8 HOHId;
	uint8 StartMessageId;
	uint8 EndMessageId;
} str_MessageObjAssignedToHOH;

/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
/*    Type Description        :                                                          */
/*    Type range              :                                                          */

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/
/*    Type Description       : variable to save Module state                             */
/*                             After power-up/reset, the Can module shall be in the state*/
/*                                CAN_UNINIT.   (SRS_BSW_00406)                          */
/*    Requirment              : SRS                                                      */
static Can_ModuleStateType ModuleState = CAN_UNINIT;

/*    Type Description        : array to save Controllers state                          */
/*    Requirment              : SWS                                                      */
static Can_ControllerStateType ControllerState[MAX_CONTROLLERS_NUMBER] = {
		CAN_CS_UNINIT, CAN_CS_UNINIT };

/*    Type Description        : array to save times of Disabling Controller Interrupts   */
/*    Requirment              : SWS                                                      */
static uint8 DisableCnt[MAX_CONTROLLERS_NUMBER];

/*    Type Description        : Pointer to save Module configration parameters           */
/*    Requirment              : SWS                                                      */
static Can_ConfigType* Global_ConfigType = NULL_PTR;

/*    Type Description        : array to save Number of poosible baudrate configration 
 for each controllers                                     */
static uint8 ControllerBaudrateConfigNum[MAX_CONTROLLERS_NUMBER] = {
		MAX_BAUDRATE_CONFIGS_CONTROLLER_0, MAX_BAUDRATE_CONFIGS_CONTROLLER_1 };

/* Type Description  :    Struct                                                          */
/* to save each start and end Hardware message object ID                                  */
/* of a specific software HOH(message object)                                             */
/* in case of HRH the number of  Hardware message objects >= 1                            */
/* in case of HTH the number of  Hardware message objects  = 1                            */
/* as tm4c123gh6pm microcontroller doesn't support multiplexed transmission               */
static str_MessageObjAssignedToHOH MessageObjAssignedToHOH[CAN_HOH_NUMBER];

/** ***************************************************************************************/

static tCANMsgObject *psMsgObject[CAN_HWOBJECT_COUNT];
static uint8 bClrPendingInt;
static Can_ErrorStateType Can_ErrorStateType_0;

/*

 STATIC Can_HwType MsgObject [MAX_NO_OF_OBJECTS] ;
 /*
 *
 but if init function did its job we can use it from the configurations itself
 */
static Can_ConfigType * g_Config_Ptr;
static uint8 Can_DriverState = CAN_INITIALIZED; /// assume that init function has initialized it !

static PduIdType Saved_swPduHandle;

uint8 HTH_Semaphore[MAX_NO_OF_OBJECTS] = 0; //// simulation of a semaphore by a sad global variable to protect HTH or generally all tha HOH


/*Description :  variable to contain the CAN Controller Mode (UNINIT,STARTED,STOPPED,SLEEP)*/
static Can_ControllerStateType Can_ControllerMode [NUM_OF_CAN_CONTROLLERS];
/*Description :  variable for interrupt Enable in start mode */
static uint8 uint8_uint8_InterruptEnableInStartMode[NUM_OF_CAN_CONTROLLERS];
/*Description :  variable for interrupt Disable in stop mode */
static uint8 uint8_InterruptDisableInStoptMode[NUM_OF_CAN_CONTROLLERS];
/*Description :  variable for interrupt Disable counter */
static uint8 uint8_InterruptDisableCounter[NUM_OF_CAN_CONTROLLERS];
/* This is a mapping between interrupt number (for the peripheral interrupts
   only) and the register that contains the interrupt enable for that interrupt.*/
static const uint32 g_pui32EnRegs[] =
{
		NVIC_EN0, NVIC_EN1, NVIC_EN2, NVIC_EN3, NVIC_EN4
};


/*****************************************************************************************/
/*                                   Local Function Declaration                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/

/*****************************************************************************************/
/*    Function Description    :                                                          */
/*    Parameter in            :                                                          */
/*    Parameter inout         :                                                          */
/*    Parameter out           :                                                          */
/*    Return value            :                                                          */
/*    Requirment              : SWS_Can_                                                 */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Global Function Definition                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*    Function Description    : This function initializes the module                     */
/*    Parameter in            : const Can_ConfigType* Config                             */
/*    Parameter inout         : none                                                     */
/*    Parameter out           : none                                                     */
/*    Return value            : none                                                     */
/*    Requirment              : SWS_Can_00223                                            */
/*    Notes                   : Can_Init() dosn't set  clock for controllers according   */
/*                                to [SWS_Can_00407] 									 */
/*								#If the register can affect several hardware modules and */
/*								if it is not an I/O register it shall be initialized by  */
/*								the MCU driver. 										 */
/*                              #One-time writable registers that require initialization */
/*								directly after reset shall be initialized by the startup */
/*								code #Tm4c123gh microcontroller doesn't support			 */
/*								Multiplexed Transmission So it's not configured          */
/*				  			                                                             */
/*																                         */
/*****************************************************************************************/
void Can_Init(const Can_ConfigType* Config) {
	uint8 controllerId; /*variable to count controllers number                          */
	uint8 HOHCount; /*variable to count SW HOH number                               */
	uint32 BaseAddress; /*variable to save controller BaseAddres                        */
	uint8 HwObjectCount; /*variable to save the number of hardware messages n each SW HOH*/
	uint8 HardwareMessageObjCount = 0; /*variable to count the used hardware messages
	 can't exceed 32 "Hardware specification"                       */

#if(CanDevErrorDetect==STD_ON)
	/*  Report error CAN_E_PARAM_POINTER API called with wrong parameter */
	if (Config == NULL_PTR)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID,
				CAN_E_PARAM_POINTER);
	}

	/*   The function Can_Init shall raise the error CAN_E_TRANSITION if the driver is not in
	 *   state CAN_UNINIT  [SWS_Can_00174]
	 */
	if (ModuleState != CAN_UNINIT)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID,
				CAN_E_TRANSITION);
	}
#endif

	/*
	 *Save the configration pointer to be used in other APIs
	 */
	Global_ConfigType = (Can_ConfigType*) Config;

	/*
	 *   Loop to initialize all controllers configured to be used in the Module
	 */
	for (controllerId = 0; controllerId < CAN_CONTROLLERS_NUMBER;
			controllerId += 1) {
#if(CanDevErrorDetect==STD_ON)
		/*
		 *   The function Can_Init shall raise the error CAN_E_TRANSITION
		 *   if the Can controller is not in state CAN_CS_UNINIT [SWS_Can_00408]
		 */
		if (ControllerState[controllerId] != CAN_CS_UNINIT)
		{
			Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID,
					CAN_E_TRANSITION);
		}
#endif
		/*
		 *    Save Current controller BaseAddress
		 */
		BaseAddress =
				Config->CanConfigSetRef->CanControllerRef[controllerId].CanControllerBaseAddress;

		/*
		 [SWS_Can_00245]   The function Can_Init shall initialize all CAN controllers
		 according to their configuration.
		 */HWREG(BaseAddress + CAN_O_CTL) = (CAN_CTL_INIT);

		/*
		 * Wait for busy bit to clear
		 */
		while (HWREG(BaseAddress + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY) {
		}

		/*[SWS_Can_00259]  The function Can_Init shall set all CAN controllers
		 in the state STOPPED*/
		ControllerState[controllerId] = CAN_CS_STOPPED;
	}

	/*
	 * Loop to Configure Hardware message objects to be Transmit or receive
	 */
	for (HOHCount = 0; HOHCount < CAN_HOH_NUMBER; HOHCount += 1) {
		/*
		 * Save the BaseAddress of the controller this Hardware Object Belongs to
		 */
		BaseAddress =
				Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanControllerRef->CanControllerBaseAddress;
		HWREG(BaseAddress + CAN_O_IF1CMSK) |= (CAN_IF1CMSK_WRNRD
				| CAN_IF1CMSK_ARB | CAN_IF1CMSK_CONTROL );

		/*
		 * Configuration for transmit message object type HTH
		 */
		if (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanObjectType
				== TRANSMIT)
				{
			HWREG(BaseAddress + CAN_O_IF1ARB2) &= ~CAN_IF1ARB2_MSGVAL; /*must be cleared before configuration*/
			HWREG(BaseAddress + CAN_O_IF1MCTL) |= CAN_IF1MCTL_TXRQST;
			HWREG(BaseAddress + CAN_O_IF1ARB2) |= CAN_IF1ARB2_DIR; /*transmit*/
			/*
			 * Configuration for 11-bits Standard ID type
			 */
			if (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanIdType
					== STANDARD)
					{
				HWREG(BaseAddress + CAN_O_IF1ARB2) &= ~CAN_IF1ARB2_XTD; /*Standard*/
			}
			/*
			 * Configuration for 29-bits Extended ID type
			 */
			else if (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanIdType
					== EXTENDED)
					{
				HWREG(BaseAddress + CAN_O_IF1ARB2) |= CAN_IF1ARB2_XTD; /*Extended*/
			}
			HWREG(BaseAddress + CAN_O_IF1ARB2) |= CAN_IF1ARB2_MSGVAL; /*set as valid message object*/

			/*increament to save the number of occupied hardware objects */
			HardwareMessageObjCount++;

#if(CanDevErrorDetect==STD_ON)
			if (HardwareMessageObjCount
					> CAN_CONTROLLER_ALLOWED_MESSAGE_OBJECTS)
					{
				/*Report error as number of used hardware message objects exceeded limit*/
				Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID,
						CAN_E_INIT_FAILED);
			}
#endif
			HWREG(BaseAddress + CAN_O_IF1CRQ) = HardwareMessageObjCount;

			/*
			 * save current HOH ID , its start Hardware messageId and its end Hardware messageId
			 * start = end as tm4c123 MC doesn't support multiplexed transmission
			 */
			MessageObjAssignedToHOH[HOHCount].HOHId =
					Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanObjectId;
			MessageObjAssignedToHOH[HOHCount].StartMessageId =
					HardwareMessageObjCount;
			MessageObjAssignedToHOH[HOHCount].EndMessageId =
					HardwareMessageObjCount;
		}
		/*
		 * Configuration for receive message object type HRH
		 */
		else if (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanObjectType
				== RECEIVE)
				{

			/* [SWS_CAN_00489]  The CAN driver shall support controllers which implement a
			 hardware FIFO. The size of the FIFO is configured via "CanHwObjectCount". */
			/*To prevent loss of received messages, some controllers support a FIFO built
			 from a set of hardware objects, while on other controllers  */
			HwObjectCount =
					Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwObjectCount;

			/*Loop to configure all hardware objects in the FIFO to Configure one HRH*/
			while (HwObjectCount--) {
				HWREG(BaseAddress + CAN_O_IF2CMSK) |= (CAN_IF2CMSK_WRNRD
						| CAN_IF2CMSK_ARB | CAN_IF2CMSK_CONTROL
						| CAN_IF2CMSK_MASK);
				HWREG(BaseAddress + CAN_O_IF2MCTL) |= (CAN_IF2MCTL_UMASK
						| CAN_IF2MCTL_RXIE | CAN_IF2MCTL_DLC_M);
				HWREG(BaseAddress + CAN_O_IF2ARB2) &= ~CAN_IF2ARB2_MSGVAL; /*must be cleared before configuration*/
				HWREG(BaseAddress + CAN_O_IF2ARB2) &= ~CAN_IF1ARB2_DIR; /*Receive*/
				if (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanIdType
						== STANDARD)
						{
					/*   When using an 11-bit identifier, [12:2]bits are used for bits
					 *   [10:0] of the ID.
					 */
					HWREG(BaseAddress + CAN_O_IF2ARB2) &= ~CAN_IF2ARB2_XTD;
					HWREG(BaseAddress + CAN_O_IF2ARB2) |=
							(CAN_IF2ARB2_ID_STANDARD)
									& ((Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterCode)
											<< 2);
					HWREG(BaseAddress + CAN_O_IF2MSK2) =
							(CAN_IF2MSK2_IDMSK_STANDARD)
									& ((Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask)
											<< 2);
				} else if (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanIdType
						== EXTENDED)
						{
					/*
					 *   When using a 29-bit identifier,  12:0 bits are used for bits [28:16] of the
					 *   ID. The field in the CANIFn MSK1&ARB1 register are used for bits [15:0]
					 * */
					HWREG(BaseAddress + CAN_O_IF2ARB2) |= CAN_IF2ARB2_XTD; /*Extended ID*/

					/*
					 * set ID in the arbitration register
					 * */HWREG(BaseAddress + CAN_O_IF2ARB1) |=
							(CAN_IF2ARB1_ID_M)
									& (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterCode);
					HWREG(BaseAddress + CAN_O_IF2ARB2) =
							(CAN_IF2ARB2_ID_M)
									& ((Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask)
											>> 0xF);
					/*Set Mask filter*/HWREG(BaseAddress + CAN_O_IF2MSK1) =
							(CAN_IF2MSK1_IDMSK_M)
									& (Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask);
					HWREG(BaseAddress + CAN_O_IF2MSK2) =
							(CAN_IF2MSK2_IDMSK_M)
									& ((Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask)
											>> 0xF);
				}
				/*set as valid message object*/HWREG(BaseAddress + CAN_O_IF2ARB2) |=
						CAN_IF2ARB2_MSGVAL;

				/*increament to save the number of occupied hardware objects */
				HardwareMessageObjCount++;

#if(CanDevErrorDetect==STD_ON)
				if (HardwareMessageObjCount
						> CAN_CONTROLLER_ALLOWED_MESSAGE_OBJECTS)
						{
					/*Report error as the number of occupied hardware message objects exceeded limit 32*/
					Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID,
							CAN_E_INIT_FAILED);
				}
#endif
				if (HwObjectCount == 0) /*End of FIFO Reached*/
				{
					/*Set cuurent hardware message as the last one in FIFO */
					HWREG(BaseAddress + CAN_O_IF2MCTL) |= CAN_IF2MCTL_EOB;
					/*Map the Current Software HRH with its hardware messages used in the buffer*/
					MessageObjAssignedToHOH[HOHCount].HOHId =
							Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount].CanObjectId;
					/*Save the ID of the first hardware message object used in the FIFO*/
					MessageObjAssignedToHOH[HOHCount].StartMessageId =
							HardwareMessageObjCount
									- Config->CanConfigSetRef->CanHardwareObjectRef[HOHCount]\
.CanHwObjectCount
									+ 1;
					/*Save the ID of the last hardware message object used in the FIFO*/
					MessageObjAssignedToHOH[HOHCount].EndMessageId =
							HardwareMessageObjCount;
				}
				/*Save the ID of the  hardware message object used in the register IF2CRQ*/
				HWREG(BaseAddress + CAN_O_IF2CRQ) = HardwareMessageObjCount;
			}
		}
	}

	/*[SWS_Can_00246]  ? The function Can_Init shall change the module state to 
	 CAN_READY, after initializing all controllers inside  the
	 HWUnit. (SRS_SPAL_12057, SRS_Can_01041) */
	ModuleState = CAN_READY;
}

#ifdef CanSetBaudrateApi
/*****************************************************************************************/
/*    Function Description    :The function service shall set the baud rate configuration*/
/*                             of the CAN controller .Depending on necessary baud rate   */
/*                             modifications the controller might have to reset          */
/*    Parameter in            : uint8 Controller, uint16 BaudRateConfigID                */
/*    Parameter inout         : none                                                     */
/*    Parameter out           : none                                                     */
/*    Return value            : Std_ReturnType                                           */
/*    Requirment              : SWS_Can_00491                                            */
/*****************************************************************************************/
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID) {
	/* local variable declarations */
	uint32 ui32BitReg = 0;
	uint32 ui32BaudRatePrescaler;
	uint32 n;
	uint32 ui32Base;
	CanControllerBaudrateConfig* current_baudrate =
			&(Global_ConfigType->CanConfigSetRef->CanControllerRef[Controller].CanControllerDefaultBaudrate[BaudRateConfigID]);

	/* fetch base address */
	ui32Base =
			Global_ConfigType->CanConfigSetRef->CanControllerRef[Controller].CanControllerBaseAddress;

#if(CanDevErrorDetect==STD_ON) /* DET notifications */

	/* [SWS_CAN_00492] If development error detection for the Can module is enabled
	 The function Can_SetBaudrate shall raise the error CAN_E_UNINIT and return
	 E_NOT_OK if the driver is not yet initialized.*/
	if (CAN_E_UNINIT == ControllerState[Controller]
			|| NULL_PTR == Global_ConfigType
			|| (!(HWREG(ui32Base + CAN_O_CTL) & CAN_CTL_INIT))) {
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SETBAUDRATE_API_ID,
				CAN_E_UNINIT);
		return E_NOT_OK;
	}
#endif
	/* [SWS_CAN_00494]If development error detection for the Can module is enabled
	 the function Can_SetBaudrate shall raise the error CAN_E_PARAM_CONTROLLER
	 and return E_NOT_OK if the parameter Controller is out of range. */
#if(CanDevErrorDetect==STD_ON)
	if (Controller > CAN_CONTROLLERS_NUMBER) {
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SETBAUDRATE_API_ID,
				CAN_E_PARAM_CONTROLLER);
		return E_NOT_OK;
	}
#endif

#if(CanDevErrorDetect==STD_ON)	
	/* [SWS_CAN_00493] If development error detection for the Can module is enabled:
	 The function Can_SetBaudrate shall raise the error CAN_E_PARAM_BAUDRATE
	 and return E_NOT_OK if the parameter BaudRateConfigID has an invalid value*/

	if (BaudRateConfigID > ControllerBaudrateConfigNum[Controller]) {
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SETBAUDRATE_API_ID,
				CAN_E_PARAM_BAUDRATE);
		return E_NOT_OK;
	}

#endif

	/*  [SWS_Can_00256] If the call of Can_SetBaudrate() would cause a re-initialization
	 of the CAN Controller and the CAN Controller is not in state STOPPED, it shall return E_NOT_OK.*/
	if (CAN_CS_STOPPED == ControllerState[Controller]) {

		/*
		 To set the bit timing register, the controller must be placed in init
		 mode (if not already), and also configuration change bit enabled.  State
		 of the init bit must be saved so it can be restored at the end.
		 Write accesses to the CANBIT register are allowed if the INIT bit is 1.*/
		/* CAN_CTL_CCE     Write accesses to the CANBIT register are allowed if the INIT bit is 1. */
		HWREG(ui32Base + CAN_O_CTL) |= CAN_CTL_CCE; /* set INIT_BIT and CCE */

		/* 	Set the bit fields of the bit timing register
		 *	according to Tiva C TM4C123GH6PM page 1058
		 * 	TSEG2 		= Phase2 - 1
		 *	TSEG1 		= Prop + Phase1 - 1
		 *	SJW 		= SJW - 1
		 *	BRP =BRP */

		/* 	Time Segment After Sample Point (TSEG2)
		 0x00-0x07: The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
		 So, for example, the reset value of 0x2 means that 3 (2+1) bit time quanta are defined for Phase2
		 The bit time quanta is defined by the BRP field.*/
		ui32BitReg = (((((current_baudrate->CanControllerSeg2) - 1)
				<< CAN_BIT_TSEG2_S)) & CAN_BIT_TSEG2_M);

		/* Time Segment Before Sample Point (TSEG1)
		 0x00-0x0F: The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
		 So, for example, the reset value of 0x3 means that 4 (3+1) bit time quanta are defined for Phase1 .
		 The bit time quanta is defined by the BRP field. */
		ui32BitReg |= ((((current_baudrate->CanControllerPropSeg
				+ current_baudrate->CanControllerSeg1) - 1) << CAN_BIT_TSEG1_S)
				& CAN_BIT_TSEG1_M);

		/*(Re)Synchronization Jump Width (SJW) :
		 0x00-0x03:The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
		 During the start of frame (SOF), if the CAN controller detects a phase error (misalignment), it can adjust the length of TSEG2 or TSEG1 by the
		 value in SJW. So the reset value of 0 adjusts the length by 1 bit time quanta*/
		ui32BitReg |= (((current_baudrate->CanControllerSyncJumpWidth - 1)
				<< CAN_BIT_SJW_S) & CAN_BIT_SJW_M);

		/*
		 * Baud rate Prescaler = tq * CAN Clock
		 * bit time =  n * tq
		 *          =[Sync + Prop + Phase1 + Phase2] � tq
		 *  Syn =1 all the time
		 * 1/Frequency(rate) =n*Tq
		 * 1/Frequency(rate)*n=Tq
		 * Baud rate Prescaler = CAN Clock*(1/(n*baud rate))
		 * Baud rate Prescaler = CAN Clock*(1/(n*baud rate))
		 */
		n = current_baudrate->CanControllerSeg2
				+ current_baudrate->CanControllerSeg1 + 1
				+ current_baudrate->CanControllerPropSeg;

		/*
		 * CanControllerBaudRate :-Specifies the baudrate of the controller in kbps
		 * Baud Rate Prescaler (BRP)
		 The value by which the oscillator frequency is divided for generating the bit time quanta. The bit time is built up from a multiple of this quantum.
		 0x00-0x03F: The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
		 BRP defines the number of CAN clock periods that make up 1 bit time quanta, so the reset value is 2 bit time quanta (1+1).
		 The CANBRPE register can be used to further divide the bit time */

		ui32BaudRatePrescaler =
				((*(Global_ConfigType->CanConfigSetRef->CanControllerRef[Controller]).CanCpuClockRef)
						/ (((current_baudrate->CanControllerBaudRate) * 1000)
								* n));
		ui32BitReg |= ((ui32BaudRatePrescaler) - 1) & CAN_BIT_BRP_M;

		/* Set CANBIT Register */
		/* Register 4: CAN Bit Timing (CANBIT) :-
		 *             This register is used to program the bit width and bit quantum. Values are programmed to the system
		 clock frequency. This register is write-enabled by setting the CCE and INIT bits in the CANCTL register */HWREG(ui32Base + CAN_O_BIT) =
				ui32BitReg;

		/* Set the divider upper bits in the extension register. */
		/* Baud Rate Prescaler Extension (BRPE)
		 0x00-0x0F: Extend the BRP bit in the CANBIT register to values up to
		 1023. The actual interpretation by the hardware is one more than the
		 value programmed by BRPE (MSBs) and BRP (LSBs). */

		if (ui32BaudRatePrescaler < MaxValue_BRPE
				&& ui32BaudRatePrescaler > MinValue_BRPE)
				{
			HWREG(ui32Base + CAN_O_BRPE) = ((ui32BaudRatePrescaler - 1) >> 6)
					& CAN_BRPE_BRPE_M;
		}

		/* reset CCE to disable access to CANBIT register*/HWREG(ui32Base + CAN_O_CTL) &=
				~CAN_CTL_CCE;

		return E_OK; /* Service request accepted, setting of (new) baud rate started */

	} else {
		return E_NOT_OK; /* Service request not accepted*/
	}
}
#endif

// Reentrant Function
void Can_EnableControllerInterrupts(uint8 Controller) {
	irq_Disable();
#if(CanDevErrorDetect==STD_ON)
	if (ModuleState == CAN_UNINIT)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_EnableControllerInterrupts_Id,
				CAN_E_UNINIT);
    }
    /*  [SWS_Can_00210] The function Can_EnableControllerInterrupts shall raise the error
     *  CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range
     */
	else if (Controller > MAX_CONTROLLERS_NUMBER)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_EnableControllerInterrupts_Id,
				CAN_E_PARAM_CONTROLLER);
    }
#endif

    /*  [SWS_Can_00202] When Can_DisableControllerInterrupts has been called
     *  several times, Can_EnableControllerInterrupts must be called as many times before
     *  the interrupts are re-enabled
     */
    if (DisableCnt[Controller] > 1) {
        DisableCnt[Controller]--;
    }

    /*  [SWS_Can_00208] The function Can_EnableControllerInterrupts shall perform no
     *  action when Can_DisableControllerInterrupts has not been called before
     */
    else if (DisableCnt[Controller] == 1) {
        DisableCnt[Controller] = 0;

        /* [SWS_Can_00050] The function Can_EnableControllerInterrupts shall enable all
         * interrupts that must be enabled according the current software status
         */
        if (Controller == 0)
            CANIntEnable(CAN0_BASE,
                    CAN_INT_ERROR | CAN_INT_STATUS | CAN_INT_MASTER);
        else if (Controller == 1)
            CANIntEnable(CAN1_BASE,
                    CAN_INT_ERROR | CAN_INT_STATUS | CAN_INT_MASTER);
        else {
        }
    }
    /* End of Critical Section */
	irq_Enable();
}

/****************************************************************************************/
// Reentrant Function
void Can_DisableControllerInterrupts(uint8 Controller) {
	irq_Disable();
#if(CanDevErrorDetect==STD_ON)

    /*  [SWS_Can_00205] The function Can_DisableControllerInterrupts shall raise the error CAN_E_UNINIT if
     *  the driver not yet initialized
     */
	if (ModuleState == CAN_UNINIT)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DisableControllerInterrupts_Id,
				CAN_E_UNINIT);
    }

    /*  [SWS_Can_00206] The function Can_DisableControllerInterrupts shall raise the error
     *  CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range
     */
	else if (Controller > MAX_CONTROLLERS_NUMBER
		)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DisableControllerInterrupts_Id,
				CAN_E_PARAM_CONTROLLER);
#endif

    /*  [SWS_Can_00202] When Can_DisableControllerInterrupts has been called
     *  several times, Can_EnableControllerInterrupts must be called as many times before
     *  the interrupts are re-enabled
     */
    if (DisableCnt[Controller] == 0)
    {
        /*  [SWS_Can_00049] The function Can_DisableControllerInterrupts shall access the
         *  CAN controller registers to disable all interrupts for that CAN controller only, if
         *  interrupts for that CAN Controller are enabled
         */
        if (Controller == 0)
            CANIntDisable(CAN0_BASE,
                    CAN_INT_ERROR | CAN_INT_STATUS | CAN_INT_MASTER);
        else if (Controller == 1)
            CANIntDisable(CAN1_BASE,
                    CAN_INT_ERROR | CAN_INT_STATUS | CAN_INT_MASTER);
        else {
        }
    }
    DisableCnt[Controller]++;

    /* End of Critical Section */
	irq_Enable();
}

/******************************************************************************************/
// Non Reentrant Function
void Can_DeInit(void) {
#if(CanDevErrorDetect==STD_ON)
    /*   The function Can_DeInit shall raise the error CAN_E_TRANSITION if the driver is not
     *   in state CAN_READY [SWS_Can_91011]
     *   [SWS_BSW_00232] Call to De-Initialization functions :
     *   The module De-Initialization function shall be called only if the module was initialized before
	 */
    if (ModuleState != CAN_READY)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DeInit_Id, CAN_E_TRANSITION);
    }
    /*  The function Can_DeInit shall raise the error CAN_E_TRANSITION if any of the CAN
     *  controllers is in state STARTED [SWS_Can_91012]
     */
    if (ControllerState[0] == CAN_CS_STARTED
            || ControllerState[1] == CAN_CS_STARTED)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DeInit_Id,
                CAN_E_TRANSITION);
    }
#endif
    /*  [SWS_Can_ 91009] The function Can_DeInit shall change the module state to
     *  CAN_UNINIT before de-initializing all controllers inside the HW unit
     *  [SWS_BSW_00072] Module state after De-Initialization function
     *  The state of a BSW Module shall be set accordingly at the beginning of the DeInitialization function
     */
    ModuleState = CAN_UNINIT;
    CLR_BITS( HWREG(CAN0_BASE + CAN_O_CTL),0
             , CAN_CTL_INIT | CAN_CTL_IE | CAN_CTL_SIE | CAN_CTL_EIE );   // DeInit CAN controller0
    CLR_BITS( HWREG(CAN1_BASE + CAN_O_CTL),0
             , CAN_CTL_INIT | CAN_CTL_IE | CAN_CTL_SIE | CAN_CTL_EIE );   // DeInit CAN controller1
}

void Can_MainFunction_Read(void) {
#ifdef (CanRxProcessing == POLLING || CanRxProcessing == MIXED)
	Can_HwType Mailbox;
	int index;

	// Check whether we need to check RXready flag or not.
	if ( HWREG(CAN0_BASE + CAN_O_STS) & CAN_STATUS_RXOK)
	{
		// 1. Copy data to temp buffer

		for(index = 0; index < CanHwObjectCount; index++)
		{
			CANMessageGet(CAN0_BASE, index, psMsgObject++, bClrPendingInt);
		}

		Mailbox.CanId = psMsgObject.ui32MsgID;
		//TODO:Check the meaning of this variable
		//Mailbox.Hoh =
		Mailbox.ControllerId = 0;

		// 2. inform CanIf using API below.
		CanIf_RxIndication(Mailbox, PduInfoPtr);//We need to ask how to access these vars
	}
#endif
}

//Can_MainFunction_BusOff_0 or Can_MainFunction_BusOff
void Can_MainFunction_BusOff(void) {
#if CanBusoffProcessing == POLLING
	if(HWREG(CAN0_BASE + CAN_O_STS) & CAN_STATUS_BUS_OFF)
	{
		CanIf_ControllerBusOff(CAN0_ID);
		Can_ErrorStateType_0 = CAN_ERRORSTATE_BUSOFF;
	}
#endif
}

Std_ReturnType Can_Write(

Can_HwHandleType Hth, const Can_PduType* PduInfo) {

	Std_ReturnType returnVal = E_OK;

	/*
	 * check if you left the DevErrorDectect Open ..
	 */
#if (CanDevErrorDetect == TRUE)
	if (Can_DriverState == CAN_NOT_INITIALIZED)
	{
		//// call the DET function .. CAN_E_UNIT
		returnVal = E_NOT_OK;
	}

	else if (Hth > 64)
	{
		//// call the DET .... CAN_E_PARAM_HANDLE
		returnVal = E_NOT_OK;
	}
	else if (PduInfo == NULL_PTR)
	{
		//// call the DET .... CAN_E_PARAM_POINTER
		returnVal = E_NOT_OK;
	}
	else if (PduInfo->length > 64)
	{
		//// call the DET .... CAN_E_PARAM_DATA_LENGTH
		returnVal = E_NOT_OK;
	}
	else

#endif
	{

		/*
		 * if every thing went well after the error detection .. prepare the parameters of CanMessageSet() [search for it]
		 */
		uint32 uiBase;
		uint32 ui32ObjID;
		tCANMsgObject * psMsgObject;
		tMsgObjType eMsgType;

		if (HTH_Semaphore[Hth] == 0) //// 0 : no one uses it at the moment !

				{
			///// start protecting your shared stuff man !
			HTH_Semaphore[Hth] = 1; //// acquire me

			/*
			 * choosing what can controller .. to detect what is the base address
			 */

			/*
			 for (index = 0 ; index < MAX_NO_OF_OBJECTS ; index++ )
			 {
			 if (g_Config_Ptr->HardWareObject[index].CanObjectId == Hth )
			 {
			 switch (g_Config_Ptr->HardWareObject[index].CanContrlloerRef)
			 {
			 case 0 : uiBase = CAN0_BASE ; break ;
			 case 1 : uiBase = CAN1_BASE ; break ;
			 }

			 psMsgObject->ui32Flags = ( g_Config_Ptr->HardWareObject[index].CanIdType == STANDARD )? MSG_OBJ_NO_FLAGS : MSG_OBJ_EXTENDED_ID ; /// flags are not handled in this Api except for stand vs extend

			 }
			 }
			 */

			/*
			 * another method to decide what can controller to use.
			 * if the argument HTH is bigger that 32 .. CAN0 .. else CAN1
			 * and assign the message object id with a proper value
			 */

			if (Hth > 32) {
				uiBase = CAN1_BASE;
				ui32ObjID = Hth - 32;
			} else {
				uiBase = CAN0_BASE;
				ui32ObjID = Hth;
			}

			/// what is the type of the message id ?

			psMsgObject->ui32Flags =
					(g_Config_Ptr->HardWareObject[Hth].CanIdType == STANDARD ) ?
							MSG_OBJ_NO_FLAGS : MSG_OBJ_EXTENDED_ID;

			// also from the can_id_type itself
			/*
			 psMsgObject->ui32Flags = (PduInfo->id & (1<<31))?  MSG_OBJ_EXTENDED_ID  : MSG_OBJ_NO_FLAGS  ;			check the most significant bit
			 */

			/*
			 * PDU .. message object itself
			 */

			psMsgObject->ui32MsgID =
					(PduInfo->id & (1 << 31) ) ?
							(PduInfo->id & 0x1fffffff ) :
							(PduInfo->id & 0x07FF ); //// 11 bits or 29 bits to go
			psMsgObject->ui32MsgLen = PduInfo->length;
			psMsgObject->pui8MsgData = PduInfo->sdu;
			psMsgObject->ui32MsgIDMask = 0; //  no filtering mode .. maybe later

			/*
			 * the type of the CAN_write() function is obviously Tx
			 */
			eMsgType = MSG_OBJ_TYPE_TX;

			/////// stop protecting your stuff man !
			HTH_Semaphore[Hth] = 0; //// release me

			/*
			 * check if the controller is busy
			 */

			if (HWREG(uiBase + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
			{
				returnVal = CAN_BUSY;
			}

			else {

				/*
				 *
				 * call the Tivaware function now !
				 */
				CANMessageSet(uiBase, ui32ObjID, psMsgObject, eMsgType);
				Saved_swPduHandle = PduInfo->swPduHandle; //// save the
				returnVal = E_OK;

			}

		} else /////// CAN Is busy
		{
			returnVal = CAN_BUSY;
		}
	}

	return returnVal;
}

/*---------------------------------------------------------------------
 Function Name:  <Can_MainFunction_Mode>
 Service ID:     <0x0c>
 Description:
 - Scheduled function.
 - This function performs the polling of CAN controller mode transitions.
 - it implements the polling of CAN status register flags to detect transition of CAN Controller state.
 ----------------------------------------------------------------------*/
void Can_MainFunction_Mode(void) {
	uint8 ControllerIndex;
	uint32 ui32Base;

	for (ControllerIndex = 0; ControllerIndex < NO_OF_CONTROLLERS_IN_HW;
			ControllerIndex++) {
		switch (ControllerIndex) {
		case 0:
			ui32Base = CAN0_BASE;
			break;
		case 1:
			ui32Base = CAN1_BASE;
			break;
		}

		if (HWREG(ui32Base + CAN_O_CTL) & CAN_CTL_INIT) ////// the controller is in intialization state
				{
			if (g_Config_Ptr->CanControllers[ControllerIndex].ControllerStatus
					== CAN_CS_SLEEP)
					{
				CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_SLEEP); /// callback function
			} else {
				CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_STOPPED);
			}
		} else {
			if (g_Config_Ptr->CanControllers[ControllerIndex].CanControllerErrorState
					== CAN_ERRORSTATE_BUSOFF)
				CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_UNINIT);

			else
				CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_STARTED);
		}
	}
}

/*[SWS_Can_00230]         */
/*Service name   : Can_SetControllerMode
 Syntax           : Std_ReturnType Can_SetControllerMode(uint8 Controller,Can_ControllerStateType Transition)
 Service ID[hex]  : 0x03
 Sync/Async       : Asynchronous
 Reentrancy       : Non Reentrant
 Parameters (in)  : Controller CAN controller for which the status shall be changed
 Transition Transition value to request new CAN controller state
 Parameters(inout):None
 Parameters (out) : None
 Return value:Std_ReturnType E_OK    : request accepted
 E_NOT_OK: request not accepted, a development error occurred
 Description: This function performs software triggered state transitions of the CAN controller State machine.*/

Std_ReturnType Can_SetControllerMode(uint8 Controller,
		Can_ControllerStateType Transition) {
	/*initialize local variable to return (E_OK,E_NOT_OK) */
	Std_ReturnType ret = E_NOT_OK;

#if (DEVLOPEMENT_ERROR)

	/*[SWS_Can_00198] If development error detection for the Can module is enabled:
	 if the module is not yet initialized, the function Can_SetControllerMode shall raise
	 development error CAN_E_UNINIT and return E_NOT_OK.*/
	if ( CanUnitState == CAN_UNINIT )
	{
		Det_ReportError( CAN_DRIVER_ID ,0 ,CAN_SET_CONTROLLER_MODE ,CAN_E_UNINIT );

		ret = E_NOT_OK;
	}

	/* [SWS_Can_00199] If development error detection for the Can module is enabled:
	 if the parameter Controller is out of range, the function Can_SetControllerMode
	 shall raise development error CAN_E_PARAM_CONTROLLER and return
	 E_NOT_OK.*/
	else if (Controller >= NUM_OF_CAN_CONTROLLERS)
	{
		Det_ReportError( CAN_DRIVER_ID ,0 ,CAN_SET_CONTROLLER_MODE ,CAN_E_PARAM_CONTROLLER );
		ret = E_NOT_OK;
	}

	/* [SWS_Can_00200] If development error detection for the Can module is enabled:
	 if an invalid transition has been requested, the function Can_SetControllerMode shall
	 raise the error CAN_E_TRANSITION and return E_NOT_OK.*/
	else if (((Transition == CAN_CS_STARTED) && ( Can_ControllerMode [Controller]!=CAN_CS_STOPPED))||
			((Transition == CAN_CS_SLEEP) && (Can_ControllerMode [Controller]!= CAN_CS_STOPPED)))
	{
		Det_ReportError( CAN_DRIVER_ID ,0 ,CAN_SET_CONTROLLER_MODE ,CAN_E_TRANSITION );
		ret = E_NOT_OK;
	}

	else

#endif
	{
		switch (Transition) {
		case CAN_CS_STARTED:
			/*[SWS_Can_00261] The function Can_SetControllerMode(CAN_CS_STARTED)
			 shall set the hardware registers in a way that makes the CAN controller participating
			 on the network.*/
			if (Controller == 0U) {
				uint8_InterruptDisableInStoptMode[Controller] = 0U;
				/* [SWS_Can_00384] Each time the CAN controller state machine is triggered with the state
				 transition value CAN_CS_STARTED, the function Can_SetControllerMode shall re-initialise
				 the CAN controller with the same controller configuration set previously used by functions
				 Can_SetBaudrate or Can_Init.*/
				if (uint8_InterruptDisableCounter[0U] == 0U) {
					/* Enables individual CAN controller interrupt sources */
					HWREG(CAN0_BASE + CAN_O_CTL) |= CAN_INT_MASTER
							| CAN_INT_ERROR | CAN_INT_STATUS;
					/* Enable the general interrupt.*/HWREG(g_pui32EnRegs[(INT_CAN0 - 16) / 32]) =
							(1 << ((INT_CAN0 - 16) & 31));
					/* Enables the CAN controller for message processing.  Once enabled, the
					 controller automatically transmits any pending frames, and processes any
					 received frames.*/HWREG(CAN0_BASE + CAN_O_CTL) &=
							~CAN_CTL_INIT;
					/*set the interrupt Enable in start mode flag      */
					uint8_uint8_InterruptEnableInStartMode[Controller] = 1U;
				}

				else {
					/* Enables the CAN controller for message processing.  Once enabled, the
					 controller automatically transmits any pending frames, and processes any
					 received frames.*/
					HWREG(CAN0_BASE + CAN_O_CTL) &= ~CAN_CTL_INIT;
				}

			}

			else if (Controller == 1U) {
				/*SWS_Can_00425] Enabling of CAN interrupts shall not be executed,
				 when CAN interrupts have been disabled by function Can_DisableControllerInterrupts.*/
				uint8_InterruptDisableInStoptMode[Controller] = 0U;

				if (uint8_InterruptDisableCounter[1U] == 0U) {
					/* [SWS_Can_00261]  The function Can_SetControllerMode(CAN_CS_STARTED) shall set
					 the hardware registers in a way that makes the CAN controller participating
					 on the network.*/
					/* Enables individual CAN controller interrupt sources */
					HWREG(CAN1_BASE + CAN_O_CTL) |= CAN_INT_MASTER
							| CAN_INT_ERROR | CAN_INT_STATUS;
					/* Enable the general interrupt.*/HWREG(g_pui32EnRegs[(INT_CAN1 - 16) / 32]) =
							1 << ((INT_CAN1 - 16) & 31);
					/* Enables the CAN controller for message processing.  Once enabled, the
					 controller automatically transmits any pending frames, and processes any
					 received frames.*/HWREG(CAN1_BASE + CAN_O_CTL) &=
							~CAN_CTL_INIT;
					/*set the interrupt Enable in start mode flag      */
					uint8_uint8_InterruptEnableInStartMode[Controller] = 1U;
				}

				else {
					/* Enables the CAN controller for message processing.  Once enabled, the
					 controller automatically transmits any pending frames, and processes any
					 received frames.*/
					HWREG(CAN1_BASE + CAN_O_CTL) &= ~CAN_CTL_INIT;
				}

			} else {

			}
			/* setting the new mode to STARTED */
			Can_ControllerMode[Controller] = CAN_CS_STARTED;
			break;

		case CAN_CS_STOPPED:
			/* [SWS_Can_00197]  The function Can_SetControllerMode shall disable interrupts that are not
			 allowed in the new state. */
			if (Controller == 0U) {
				/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
				 by function Can_disableControllerInterrupts.*/
				if (uint8_InterruptDisableCounter[0U] >= 1U) {
					HWREG(CAN0_BASE + CAN_O_CTL) |= CAN_CTL_INIT;

				} else {
					/* [SWS_Can_00263] The function Can_SetControllerMode(CAN_CS_STOPPED) shall set the
					 bits inside the CAN hardware such that the CAN controller stops participating on the
					 network.*/

					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN0_BASE + CAN_O_CTL) |= CAN_CTL_INIT;
					/* disable the CAN controller Interrupt     */HWREG(CAN0_BASE + CAN_O_CTL) &=
							~(CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
					/* set interrupt disable in stop mode */
					uint8_InterruptDisableInStoptMode[Controller] = 1U;

				}
//							for()
//							{
//								????????????
//								/*[SWS_Can_00282] ⌈The function Can_SetControllerMode(CAN_CS_STOPPED)
//                                 shall cancel pending messages.*/
//
//							}
			}

			else if (Controller == 1U) {
				if (uint8_InterruptDisableCounter[1U] >= 1U) {
					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN1_BASE + CAN_O_CTL) |= CAN_CTL_INIT;

				} else {
					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN1_BASE + CAN_O_CTL) |= CAN_CTL_INIT;

					/* disable the CAN controller Interrupt     */HWREG(CAN1_BASE + CAN_O_CTL) &=
							~(CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
					/* set interrupt disable in stop mode */
					uint8_InterruptDisableInStoptMode[Controller] = 1U;

				}
			}
//							for(  )
//							{
//																????????????
//								/*[SWS_Can_00282] ⌈The function Can_SetControllerMode(CAN_CS_STOPPED)
//                                 shall cancel pending messages.*/
//
//							}

			/* setting the new mode to STOPPED */
			Can_ControllerMode[Controller] = CAN_CS_STOPPED;
			break;
		case CAN_CS_SLEEP:
			/*[SWS_Can_00258] When the CAN hardware does not support sleep mode and is triggered to
			 transition into SLEEP state, the Can module shall emulate a logical SLEEP state from which it
			 returns only, when it is triggered by software to transition into STOPPED state.*/
			/*[SWS_Can_00404] The CAN hardware shall remain in state STOPPED, while the logical SLEEP state is active.
			 [SWS_Can_00290] If the CAN HW does not support a sleep mode, the function
			 Can_SetControllerMode(CAN_CS_SLEEP) shall set the CAN controller to the logical sleep mode.*/
			/*[SWS_Can_00197] The function Can_SetControllerMode shall disable interrupts that are not allowed in the new state. */
			if (Controller == 0U) {
				if (uint8_InterruptDisableCounter[0U] >= 1U) {
					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN0_BASE + CAN_O_CTL) |= CAN_CTL_INIT;

				} else {
					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN0_BASE + CAN_O_CTL) |= CAN_CTL_INIT;

					/* disable the CAN controller Interrupt     */HWREG(CAN0_BASE + CAN_O_CTL) &=
							~(CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
					/* set interrupt disable in stop mode */
					uint8_InterruptDisableInStoptMode[Controller] = 1U;

				}
//							for()
//							{
//																????????????
//								/*[SWS_Can_00282] ⌈The function Can_SetControllerMode(CAN_CS_STOPPED)
//                                 shall cancel pending messages.*/
//
//							}

			} else if (Controller == 1U) {
				if (uint8_InterruptDisableCounter[1U] >= 1U) {
					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN1_BASE + CAN_O_CTL) |= CAN_CTL_INIT;

				} else {
					/*Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
					 by function Can_disableControllerInterrupts.*/
					HWREG(CAN1_BASE + CAN_O_CTL) |= CAN_CTL_INIT;
					/* disable the CAN controller Interrupt     */HWREG(CAN1_BASE + CAN_O_CTL) &=
							~(CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
					/* set interrupt disable in stop mode */
					uint8_InterruptDisableInStoptMode[Controller] = 1U;

				}
			}
//							for(  )
//							{
//																????????????
//								/*[SWS_Can_00282] ⌈The function Can_SetControllerMode(CAN_CS_STOPPED)
//                                 shall cancel pending messages.*/
//
//							}

			/* setting the new mode to SLEEP */
			Can_ControllerMode[Controller] = CAN_CS_SLEEP;
			break;

		}
	}

	/*[SWS_Can_00262] The function Can_SetControllerMode(CAN_CS_STARTED) shall wait for
	 limited time until the CAN controller is fully operational. Compare to SWS_Can_00398.*/

	/*[SWS_Can_00264] The function Can_SetControllerMode(CAN_CS_STOPPED) shall wait for
	 a limited time until the CAN controller is really switched off. Compare to SWS_Can_00398.*/
	Timer0A_Init();
	while ((TIMER0_RIS_R & 0x1) == 0) {

	}
	/*clear TIMER0A timeout flag   */TIMER0_ICR_R = 0x01;
	/* return the value E_OK
	 E_NOT_OK*/
	return ret;
}

Std_ReturnType Can_GetControllerMode(uint8 Controller,Can_ControllerStateType* ControllerModePtr) 
{
	Std_ReturnType Loc_Can_GetControllerMode_Ret = E_OK;

#if(CAN_DEV_ERROR_DETECT == STD_ON)
	if (ControllerState[Controller]==CAN_CS_UNINIT)
	{
		Det_ReportError(CAN_MODULE_ID,CAN_INSTANCE_ID,Can_GetControllerMode_Id,CAN_E_UNINIT);
		Loc_Can_GetControllerMode_Ret = E_NOT_OK;
	}
	else
	{
	    /* Do Nothing */
	}

#endif

	if (Controller >= NUM_OF_CAN_CONTROLLERS)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,Can_GetControllerMode_Id, CAN_E_PARAM_CONTROLLER);
		Loc_Can_GetControllerMode_Ret = E_NOT_OK;
	} 
	else 
	{
	    /* Do Nothing */
	}
	if (ControllerModePtr == NULL)
	{
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,Can_GetControllerMode_Id, CAN_E_PARAM_POINTER);
		Loc_Can_GetControllerMode_Ret = E_NOT_OK;
	} 
	else
	{
	    /* Do Nothing */
	}

	if (Loc_Can_GetControllerMode_Ret != E_NOT_OK)
	{

		*ControllerModePtr = ControllerState[Controller];
	}
	else
	{
	    /* Do Nothing */
	}

	return Loc_Can_GetControllerMode_Ret;

}

void Can_MainFunction_Write(void) 
{

#if ((CAN_TX_PROCESSING_0==POLLING_PROCESSING) || (CAN_TX_PROCESSING_1==POLLING_PROCESSING)\
	    || (CAN_TX_PROCESSING_0==MIXED_PROCESSING) || (CAN_TX_PROCESSING_1==MIXED_PROCESSING))

	uint8 index;
	PduIdType PduId; /* Stub variable */

	#if (CAN_CONTROLLER_0_ACTIVATION == STD_ON)
	
		/* Transfer the data in the CAN message object specified by
			the MNUM field in the CANIFnCRQ register into the CANIFn
			registers*/
		CLR_BIT_PERPHBAND(CAN0_IF1CMSK_A, CAN_IF1CMSK_WRNRD);
	
	#else 
		/*Do Nothing*/
	
	#endif 

	#if (CAN_CONTROLLER_1_ACTIVATION == STD_ON) 
	
		/* Transfer the data in the CAN message object specified by
			the MNUM field in the CANIFnCRQ register into the CANIFn
			registers*/
		CLR_BIT_PERPHBAND(CAN1_IF1CMSK_A, CAN_IF1CMSK_WRNRD);
	
	#else 
		/*Do Nothing*/
	
	#endif	

	#if (CAN_CONTROLLER_0_ACTIVATION == STD_ON || CAN_CONTROLLER_1_ACTIVATION == STD_ON)
		
		for (index = 0; index < NUM_OF_HOH; index++) 
		{
			if (Global_ConfigType->CanConfigSetRef->CanHardwareObjectRef[index].CanObjectType == TRANSMIT)
			{
				if (Global_ConfigType->CanConfigSetRef->CanHardwareObjectRef[index].CanControllerRef == Global_ConfigType->CanConfigSetRef->CanControllerRef[CONTROLLER_0_ID])
				{
					#if (CAN_TX_PROCESSING_0==POLLING_PROCESSING)

						CAN0_IF1CRQ_R=MessageObjAssignedToHOH[index].StartMessageId;

						if(GET_BIT_PERPHBAND(CAN0_IF1MCTL_A,CAN_IF1MCTL_TXRQST) == (uint32)0)
						{
							CanIf_TxConfirmation(PduId);

							/*The Can module shall call CanIf_TxConfirmation to indicate a
							 successful transmission.It shall either called by the TX-interrupt service routine
							 of the corresponding HW resource or inside the Can_MainFunction_Write in case of
							 polling mode.*/
						}

						else
						{
							/* Do Nothing */
						}
					
					#elif(CAN_TX_PROCESSING_0==MIXED_PROCESSING)

						if (Global_ConfigType->CanConfigSetRef->CanHardwareObjectRef[index].CanHardwareObjectUsesPolling == STD_ON)
						{
														
							CAN0_IF1CRQ_R =	MessageObjAssignedToHOH[index].StartMessageId;

							if (GET_BIT_PERPHBAND(CAN0_IF1MCTL_A,CAN_IF1MCTL_TXRQST) == (uint32) 0) 
							{
								CanIf_TxConfirmation(PduId);

								/*The Can module shall call CanIf_TxConfirmation to indicate a
								 successful transmission.It shall either called by the TX-interrupt service routine
								 of the corresponding HW resource or inside the Can_MainFunction_Write in case of
								 polling mode.*/
							}

							else 
							{
								/* Do Nothing */
							}
						}

						else 
						{
							/*Do Nothing */
						}	

					#else
					
					/*Do Nothing */
					#endif
				}

				else if (Global_ConfigType->CanConfigSetRef->CanHardwareObjectRef[index].CanControllerRef== Global_ConfigType->CanConfigSetRef->CanControllerRef[CONTROLLER_1_ID])
				{
					#if (CAN_TX_PROCESSING_1==POLLING_PROCESSING)
				
						CAN1_IF1CRQ_R=MessageObjAssignedToHOH[index].StartMessageId;

						if(GET_BIT_PERPHBAND(CAN1_IF1MCTL_A,CAN_IF1MCTL_TXRQST) == (uint32)0)
						{
							CanIf_TxConfirmation(PduId);

							/*The Can module shall call CanIf_TxConfirmation to indicate a
							 successful transmission.It shall either called by the TX-interrupt service routine
							 of the corresponding HW resource or inside the Can_MainFunction_Write in case of
							 polling mode.*/
						}

						else
						{
							/* Do Nothing */
						}
					
					#elif(CAN_TX_PROCESSING_1==MIXED_PROCESSING)

						if (Global_ConfigType->CanConfigSetRef->CanHardwareObjectRef[index].CanHardwareObjectUsesPolling== STD_ON)
						{
							
							CAN1_IF1CRQ_R =MessageObjAssignedToHOH[index].StartMessageId;

							if (GET_BIT_PERPHBAND(CAN1_IF1MCTL_A,CAN_IF1MCTL_TXRQST) == (uint32) 0) 
							{
								
								CanIf_TxConfirmation(PduId);

								/*The Can module shall call CanIf_TxConfirmation to indicate a
								 successful transmission.It shall either called by the TX-interrupt service routine
								 of the corresponding HW resource or inside the Can_MainFunction_Write in case of
								 polling mode.*/
							}

							else 
							{
								/* Do Nothing */
							}
						
						}

						else 
						{
							/*Do Nothing */
						}	

					#else
						/*Do Nothing */
					#endif
                }

                else
                {
						/* Do Nothing */
                }
            }

            else
            {
                /* Do Nothing */
            }
		}

	#else
			/* Do Nothing */
	#endif

#else
		/* Do Nothing */
#endif
}

