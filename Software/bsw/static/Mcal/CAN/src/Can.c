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
// core_cm4.h is included to use NVIC_SystemReset Function in Assertion
#include "core_cm4.h"

/*****************************************************************************************/
/*                                   Include Component headres                           */
/*****************************************************************************************/
#include "hw_can.h"
#include "can_lib.h"
#include "Can.h"
#include "irq.h"
#include "Timer0A.h"
#include "Det.h"
#include "CanIf_Cbk.h"
/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/

#define valid                     (1U)
#define invalid                   (0U)
#define MAX_CONTROLLERS_NUMBER    (2U)                  /*Number of controllers in TivaC */
#define CAN0_BASE_ADDRESS         (0x40040000U)
#define CAN1_BASE_ADDRESS         (0x40041000U)

/*****************************************************************************************/
/*                                   Local Definition                                    */
/*****************************************************************************************/
/*    Description        :   
 */

/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/

/*    Type Description      : 	Struct to map each receive software meesage object with the number
 its configured hardware message objects in the HW FIFO
 HRHIndex        : 	HRH index in the CanHardwareObject array
 StartMessageId  : 	ID of the first hardware message object in the HW FIFO
 StartMessageId  : 	ID of the last  hardware message object in the HW FIFO    */
typedef struct {
	uint8 HRHIndex;
	uint8 StartMessageId;
	uint8 EndMessageId;
} str_MessageObjAssignedToHRH;

/*    Type Description      : 	Struct to map each transmit software meesage object with the number
                                its configured hardware message objects in the HW FIFO 
            HTHIndex        :  HTH index in the CanHardwareObject array
		    Tx_Request      :   Flag to indicate transmission request
			StartMessageId  : 	ID of the  hardware meesage object in the HW    */
typedef struct
{
	uint8 HTHIndex;
	uint8 Tx_Request;
	uint8 MessageId;      
}str_MessageObjAssignedToHTH;
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
static Can_ConfigType* Global_Config = NULL_PTR;

/*    Type Description        : array to save Number of poosible baudrate configration 
 for each controllers                                     */
static uint8 ControllerBaudrateConfigNum[MAX_CONTROLLERS_NUMBER] = {
		MAX_BAUDRATE_CONFIGS_CONTROLLER_0, MAX_BAUDRATE_CONFIGS_CONTROLLER_1 };

/* Type Description  :    Struct                                                          */
/* to save each start and end Hardware message object ID                                  */
/* of a specific software HRH(message object)                                             */
/* in case of HRH the number of  Hardware message objects >= 1                            */
static str_MessageObjAssignedToHRH MessageObjAssignedToHRH[CAN_HRH_NUMBER];

/* Type Description  :    Struct                                                          */
/* assign each software HTH to a hardware message object                                  */
static str_MessageObjAssignedToHTH MessageObjAssignedToHTH[CAN_HTH_NUMBER];

/*
 * swPduHandle is a global variable updated in CAN_Write function from PduInfo pointer
 *  and saved to be passed to CanIf_TxConfirmation
 */
static PduIdType swPduHandle[CAN_HTH_NUMBER];

/*
 *  global variable used to protect the Hth in CAN_Write function
 */
static uint8 HTH_Semaphore[MAX_NO_OF_OBJECTS] = {0};

/** ***************************************************************************************/

static uint8 ClrPendingInt = 0;


static tCANMsgObject psMsgObject[CAN_CONTROLLER_ALLOWED_MESSAGE_OBJECTS];


/*****************************************************************************************/
/*                                   Local Function Declaration                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/
static void CANDataRegWrite ( uint8 * pui8Data, uint32 * pui32Register , uint8 ui8Size);


//*****************************************************************************
//
//! \internal
//! Copies data from a buffer to the CAN Data registers.
//!
//! \param pui8Data is a pointer to the location to store the data read from
//! the CAN controller's data registers.
//! \param pui32Register is an uint32 pointer to the first register of the
//! CAN controller's data registers.  For example, in order to use the IF1
//! register set on CAN controller 1, the value would be: \b CAN0_BASE \b +
//! \b CAN_O_IF1DA1.
//! \param iSize is the number of bytes to copy from the CAN controller.
//!
//! This function takes the steps necessary to copy data to a contiguous buffer
//! in memory from the non-contiguous data registers used by the CAN
//! controller.  This function is rarely used outside of the CANMessageGet()
//! function.
//!
//! \return None.
//
//*****************************************************************************
static void
_CANDataRegRead( uint8 *pui8Data, uint32 *pui32Register, uint8 ui32Size)
{
    uint32_t ui32Idx, ui32Value;

    //
    // Loop always copies 1 or 2 bytes per iteration.
    //
    for(ui32Idx = 0; ui32Idx < ui32Size; )
    {
        //
        // Read out the data 16 bits at a time since this is how the registers
        // are aligned in memory.
        //
        ui32Value = HWREG(pui32Register++);

        //
        // Store the first byte.
        //
        pui8Data[ui32Idx++] = (uint8_t)ui32Value;

        //
        // Only read the second byte if needed.
        //
        if(ui32Idx < ui32Size)
        {
            pui8Data[ui32Idx++] = (uint8_t)(ui32Value >> 8);
        }
    }
}
/*****************************************************************************************/
/*    Function Description    :  this function sets the baud rate                        */
/*    Parameter in            :  BaseAddress : required controller base address 
                                 BRConfig    : pointer to baudrate configration  
																 CanCpuClock : Value of CanCpu Clock in Hz               */
/*    Parameter inout         :                                                          */
/*    Parameter out           :                                                          */
/*    Return value            :                                                          */
/*    Requirment              :                                                          */
/*****************************************************************************************/

static void SetControllerBaudrate(uint32 BaseAddress,CanControllerBaudrateConfig* BRConfig,McuClockReferencePoint CanCpuClock)
{
	uint32 ui32BitReg = 0;
	uint32 ui32BaudRatePrescaler;
	uint32 n;
	
			/*
        To set the bit timing register, the controller must be placed in init
        mode (if not already), and also configuration change bit enabled.  State
        of the init bit must be saved so it can be restored at the end.
        Write accesses to the CANBIT register are allowed if the INIT bit is 1.*/
		/* CAN_CTL_CCE     Write accesses to the CANBIT register are allowed if the INIT bit is 1. */
		HWREG(BaseAddress + CAN_O_CTL) |= CAN_CTL_CCE; 	/* set INIT_BIT and CCE */


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
		ui32BitReg  = 	(((((BRConfig->CanControllerSeg2) - 1) << CAN_BIT_TSEG2_S)) & CAN_BIT_TSEG2_M);

		/* Time Segment Before Sample Point (TSEG1)
        0x00-0x0F: The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
        So, for example, the reset value of 0x3 means that 4 (3+1) bit time quanta are defined for Phase1 .
        The bit time quanta is defined by the BRP field. */
		ui32BitReg |= ((((BRConfig->CanControllerPropSeg + BRConfig ->CanControllerSeg1) - 1) <<CAN_BIT_TSEG1_S) & CAN_BIT_TSEG1_M);

		/*(Re)Synchronization Jump Width (SJW) :
        0x00-0x03:The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
        During the start of frame (SOF), if the CAN controller detects a phase error (misalignment), it can adjust the length of TSEG2 or TSEG1 by the
        value in SJW. So the reset value of 0 adjusts the length by 1 bit time quanta*/
		ui32BitReg |= (((BRConfig->CanControllerSyncJumpWidth - 1) << CAN_BIT_SJW_S) & CAN_BIT_SJW_M);


		/*
		 * Baud rate Prescaler = tq * CAN Clock
		 * bit time =  n * tq
		 *          =[Sync + Prop + Phase1 + Phase2] أ— tq
		 *  Syn =1 all the time
		 * 1/Frequency(rate) =n*Tq
		 * 1/Frequency(rate)*n=Tq
		 * Baud rate Prescaler = CAN Clock*(1/(n*baud rate))
		 * Baud rate Prescaler = CAN Clock*(1/(n*baud rate))
		 */
		n = BRConfig->CanControllerSeg2 + BRConfig->CanControllerSeg1 + 1+ BRConfig->CanControllerPropSeg ;

		/*
		 * CanControllerBaudRate :-Specifies the baudrate of the controller in kbps
		 * Baud Rate Prescaler (BRP)
       The value by which the oscillator frequency is divided for generating the bit time quanta. The bit time is built up from a multiple of this quantum.
       0x00-0x03F: The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
       BRP defines the number of CAN clock periods that make up 1 bit time quanta, so the reset value is 2 bit time quanta (1+1).
       The CANBRPE register can be used to further divide the bit time */

		ui32BaudRatePrescaler = ((CanCpuClock)/(((BRConfig->CanControllerBaudRate)*1000)*n));
		ui32BitReg |= ((ui32BaudRatePrescaler) - 1) & CAN_BIT_BRP_M;


		/* Set CANBIT Register */
		/* Register 4: CAN Bit Timing (CANBIT) :-
		 *             This register is used to program the bit width and bit quantum. Values are programmed to the system
                   clock frequency. This register is write-enabled by setting the CCE and INIT bits in the CANCTL register */
		HWREG(BaseAddress + CAN_O_BIT) = ui32BitReg;


		/* Set the divider upper bits in the extension register. */
		/* Baud Rate Prescaler Extension (BRPE)
       0x00-0x0F: Extend the BRP bit in the CANBIT register to values up to
       1023. The actual interpretation by the hardware is one more than the
       value programmed by BRPE (MSBs) and BRP (LSBs). */

		if (ui32BaudRatePrescaler < MaxValue_BRPE  && ui32BaudRatePrescaler > MinValue_BRPE)
		{
			HWREG(BaseAddress + CAN_O_BRPE) =((ui32BaudRatePrescaler - 1) >> 6) & CAN_BRPE_BRPE_M;
		}

		/* reset CCE to disable access to CANBIT register*/
		HWREG(BaseAddress + CAN_O_CTL) &= ~CAN_CTL_CCE;
}	

/*****************************************************************************************/
/*                                   Global Function Definition                          */
/*****************************************************************************************/

/****************************************************************************************/
/*    Function Description    : This function initializes the module                    */
/*    Parameter in            : const Can_ConfigType* Config                            */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/*    Requirment              : SWS_Can_00223                                           */
/*    Notes                   : Can_Init() dosn't set  clock for controllers according  */
/*                                to [SWS_Can_00407]                                    */
/*                              #If the register can affect several hardware modules and*/
/*                              if it is not an I/O register it shall be initialized by */
/*                              the MCU driver.                                         */
/*                              #One-time writable registers that require initialization*/
/*                              directly after reset shall be initialized by the startup*/
/*                              code #Tm4c123gh microcontroller doesn't support         */
/*                              Multiplexed Transmission So it's not configured         */
/*                                                                                      */
/*                                                                                      */
/*****************************************************************************************/
void Can_Init( const Can_ConfigType* Config)
{
    /* variable to count controllers number                             */
    uint8   controllerId;
    /* variable to count SW HOH number                                  */
    uint8   HOHCount;
    /* variable to count SW HRH number                                  */
    uint8   HRHCount = 0 ;
    /* variable to count SW HRH number                                  */
     uint8  HTHCount = 0 ;
    /* variable to save controller BaseAddres                           */
    uint32  BaseAddress;
    /* variable to save the number of hardware messages n each SW HOH   */
    uint8   HwObjectCount;
    /* array to count the used hardware messages for each controller
       can't exceed 32 "Hardware specification" */
    uint8   UsedHWMessageObjt[MAX_CONTROLLERS_NUMBER] = {0};
    /* pointer to point to the default BaudRate configuration           */
    CanControllerBaudrateConfig* BRConfig;


#if(CanDevErrorDetect == STD_ON)
    /* Report error CAN_E_PARAM_POINTER API called with wrong parameter */
    if(Config == NULL_PTR)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID, CAN_E_PARAM_POINTER);
    }

    /* The function Can_Init shall raise the error CAN_E_TRANSITION if the driver is not in
    *   state CAN_UNINIT  [SWS_Can_00174]
    */
    if(ModuleState != CAN_UNINIT)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID, CAN_E_TRANSITION);
    }
#endif

    /* Save the configration pointer to be used in other APIs            */
    Global_Config = (Can_ConfigType*)Config;

    /* Loop to initialize all controllers configured to be used in the Module   */
    for(controllerId = 0; controllerId < USED_CONTROLLERS_NUMBER; controllerId++)
    {
#if(CanDevErrorDetect == STD_ON)
        /*
        * The function Can_Init shall raise the error CAN_E_TRANSITION
        * if the Can controller is not in state CAN_CS_UNINIT [SWS_Can_00408]
        */
        if(ControllerState[controllerId] != CAN_CS_UNINIT)
        {
            Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID, CAN_E_TRANSITION);
        }
#endif
        /* Save Current controller BaseAddress */
        BaseAddress = Global_Config->CanControllerCfgRef[controllerId].CanControllerBaseAddress;

        /* [SWS_Can_00245]   The function Can_Init shall initialize all CAN controllers 
        * according to their configuration.
        */
        HWREG(BaseAddress + CAN_O_CTL) = (CAN_CTL_INIT);

        /*[SRS_Can_01062] Each possible event of each CAN Controller shall be Pre-Compile-Time
         *  configurable to be in one of the following two modes Polling or Interrupt driven
         */
#if( CanTxProcessing == MIXED_PROCESSING || CanTxProcessing == INTERRUPT_PROCESSING ||\
     CanRxProcessing == MIXED_PROCESSING || CanRxProcessing == INTERRUPT_PROCESSING )
        /*Enable interrupt for the controller*/
        HWREG(BaseAddress + CAN_O_CTL) |= CAN_CTL_IE ;
#endif

        /* Set Baud rate fo each controller */
        /* Save current baudrate Configurations */
        BRConfig = &(Global_Config->CanControllerCfgRef[controllerId].\
                    CanControllerDefaultBaudrate[DEFAULT_BAUDRATE_CONFIGRATION_ID]);
    /* Call static function SetControllerBaudrate to Set baud rate */
        SetControllerBaudrate(BaseAddress, BRConfig, *(Global_Config->CanControllerCfgRef[controllerId].CanCpuClockRef));
    /* [SWS_Can_00259]  The function Can_Init shall set all CAN controllers in the state STOPPED */
        ControllerState[controllerId] = CAN_CS_STOPPED ;
    }

    /* Loop to Configure Hardware message objects to be Transmit or receive */
    for(HOHCount = 0; HOHCount < CAN_HOH_NUMBER; HOHCount++)
    {
        /* Save the BaseAddress of the controller this Hardware Object Belongs to */
        BaseAddress = Global_Config->CanHardwareObjectRef[HOHCount].CanControllerRef->CanControllerBaseAddress;
        /* Fetch the current HOH Controller ID */
        controllerId = Global_Config->CanHardwareObjectRef[HOHCount].CanControllerRef->CanControllerId;
        HWREG(BaseAddress + CAN_O_IF1CMSK) |= (CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_ARB | CAN_IF1CMSK_CONTROL );
        
        /* Configuration for transmit message object type HTH */
        if(Global_Config->CanHardwareObjectRef[HOHCount].CanObjectType == TRANSMIT)
        {
            HWREG(BaseAddress + CAN_O_IF1ARB2) &= ~CAN_IF1ARB2_MSGVAL;              /* must be cleared before configuration */
            if(Global_Config->CanHardwareObjectRef[HOHCount].CanHardwareObjectUsesPolling == FALSE)
            {
                HWREG(BaseAddress + CAN_O_IF1MCTL) |= (CAN_IF1MCTL_TXIE );          /*Enable transmission interrupt for this HTH*/
            }
            HWREG(BaseAddress + CAN_O_IF1ARB2) |= CAN_IF1ARB2_DIR;                  /* transmit */
            
            /* Configuration for 11-bits Standard ID type */
            if(Global_Config->CanHardwareObjectRef[HOHCount].CanIdType == STANDARD)
            {
                HWREG(BaseAddress + CAN_O_IF1ARB2) &= ~CAN_IF1ARB2_XTD;
            }
            /* Configuration for 29-bits Extended ID type */
            else if(Global_Config->CanHardwareObjectRef[HOHCount].CanIdType == EXTENDED)
            {
                HWREG(BaseAddress + CAN_O_IF1ARB2) |= CAN_IF1ARB2_XTD;
            }
            else
            {
                /* Do Nothing */
            }
            HWREG(BaseAddress + CAN_O_IF1ARB2) |= CAN_IF1ARB2_MSGVAL;           /* set as valid message object */

            /* increament to save the number of occupied hardware objects */
            UsedHWMessageObjt[controllerId]++;

            #if(CanDevErrorDetect == STD_ON)
                if(UsedHWMessageObjt[controllerId] > CAN_HOH_NUMBER)
                {
                   /* Report error as the number of occupied hardware message objects exceeded limit 32 */
                   Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID, CAN_E_INIT_FAILED);
                }
                else
                {
                   /* Do Nothing */
                }
            #endif
            MessageObjAssignedToHTH[HTHCount].HTHIndex = HOHCount;
            MessageObjAssignedToHTH[HTHCount++].MessageId = UsedHWMessageObjt[controllerId];
            HWREG(BaseAddress + CAN_O_IF1CRQ)   = UsedHWMessageObjt[controllerId];
        }
        /* Configuration for receive message object type HRH */
        else if(Global_Config->CanHardwareObjectRef[HOHCount].CanObjectType == RECEIVE)
        {
            /* [SWS_CAN_00489]  The CAN driver shall support controllers which implement 
            * a hardware FIFO. The size of the FIFO is configured via "CanHwObjectCount".
            */
            HwObjectCount = Global_Config->CanHardwareObjectRef[HOHCount].CanHwObjectCount;

            /* Loop to configure all hardware objects in the FIFO to Configure one HRH */
            while(HwObjectCount--)
            {
                HWREG(BaseAddress + CAN_O_IF2CMSK) |= (CAN_IF2CMSK_WRNRD | CAN_IF2CMSK_ARB | CAN_IF2CMSK_CONTROL | CAN_IF2CMSK_MASK);
                HWREG(BaseAddress + CAN_O_IF2MCTL) |= (CAN_IF2MCTL_UMASK |CAN_IF2MCTL_DLC_M);
                if(Global_Config->CanHardwareObjectRef[HOHCount].CanHardwareObjectUsesPolling == FALSE)
                {
                    HWREG(BaseAddress + CAN_O_IF2MCTL) |= (CAN_IF2MCTL_RXIE );          /*Enable transmission interrupt for this HRH*/
                }

                /* must be cleared before configuration */
                HWREG(BaseAddress + CAN_O_IF2ARB2) &= ~CAN_IF2ARB2_MSGVAL;
                /* Receive */
                HWREG(BaseAddress + CAN_O_IF2ARB2) &= ~CAN_IF2ARB2_DIR;
                if(Global_Config->CanHardwareObjectRef[HOHCount].CanIdType == STANDARD)
                {
                    /* When using an 11-bit identifier, [12:2]bits are used for bits [10:0] of the ID. */
                    HWREG(BaseAddress + CAN_O_IF2ARB2) &= ~CAN_IF2ARB2_XTD;
                    HWREG(BaseAddress + CAN_O_IF2ARB2) |= (CAN_IF2ARB2_ID_STANDARD) & ((Global_Config-> \
                            CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterCode) << 2);
                    HWREG(BaseAddress + CAN_O_IF2MSK2) = (CAN_IF2MSK2_IDMSK_STANDARD) & ((Global_Config-> \
                            CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask) << 2);
                }
                else if(Global_Config->CanHardwareObjectRef[HOHCount].CanIdType == EXTENDED)
                {
                    /*
                    * When using a 29-bit identifier,  12:0 bits are used for bits [28:16] of the
                    * ID. The field in the CANIFn MSK1&ARB1 register are used for bits [15:0]
                    */
                    HWREG(BaseAddress + CAN_O_IF2ARB2)|= CAN_IF2ARB2_XTD; /*Extended ID*/

                    /* set ID in the arbitration register */
                    HWREG(BaseAddress + CAN_O_IF2ARB1) |= (CAN_IF2ARB1_ID_M) & (Global_Config-> \
                        CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterCode);
                    HWREG(BaseAddress + CAN_O_IF2ARB2) = (CAN_IF2ARB2_ID_M) & ((Global_Config-> \
                            CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask) >> 0xF);
                    /* Set Mask filter */
                    HWREG(BaseAddress + CAN_O_IF2MSK1) = (CAN_IF2MSK1_IDMSK_M) & (Global_Config-> \
                            CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask);
                    HWREG(BaseAddress + CAN_O_IF2MSK2) = (CAN_IF2MSK2_IDMSK_M) & ((Global_Config-> \
                            CanHardwareObjectRef[HOHCount].CanHwFilterRef->CanHwFilterMask) >> 0xF);
                }
                /* set as valid message object */
                HWREG(BaseAddress + CAN_O_IF2ARB2) |= CAN_IF2ARB2_MSGVAL ;

                /* increament to save the number of occupied hardware objects */
                UsedHWMessageObjt[controllerId]++;

                #if(CanDevErrorDetect == STD_ON)
                    if(UsedHWMessageObjt[controllerId] > CAN_HOH_NUMBER)
                    {
                       /* Report error as the number of occupied hardware message objects exceeded limit 32 */
                       Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_INIT_API_ID, CAN_E_INIT_FAILED);
                    }
                    else
                    {
                       /* Do Nothing */
                    }
                #endif
                if(HwObjectCount == 0)  /* End of FIFO Reached */
                {
                    /* Set cuurent hardware message as the last one in FIFO */
                    HWREG(BaseAddress + CAN_O_IF2MCTL) |= CAN_IF2MCTL_EOB ;
                    /* Map the Current Software HRH with its hardware messages used in the buffer */
                    MessageObjAssignedToHRH[HRHCount].HRHIndex = HOHCount;
                    /*Save the ID of the first hardware message object used in the FIFO*/
                    MessageObjAssignedToHRH[HRHCount].StartMessageId = UsedHWMessageObjt[controllerId] - \
                            Global_Config->CanHardwareObjectRef[HOHCount].CanHwObjectCount + 1;
                    /* Save the ID of the last hardware message object used in the FIFO */
                    MessageObjAssignedToHRH[HRHCount++].EndMessageId = UsedHWMessageObjt[controllerId];
                }
                /* Save the ID of the  hardware message object used in the register IF2CRQ */
                HWREG(BaseAddress + CAN_O_IF2CRQ) = UsedHWMessageObjt[controllerId];

            }
        }
    }

    /* [SWS_Can_00246]  ? The function Can_Init shall change the module state to CAN_READY,
    * after initializing all controllers inside  the HWUnit. (SRS_SPAL_12057, SRS_Can_01041) 
    */
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
			&(Global_Config->CanControllerCfgRef[Controller].CanControllerDefaultBaudrate[BaudRateConfigID]);

	/* fetch base address */
	ui32Base =
			Global_Config->CanControllerCfgRef[Controller].CanControllerBaseAddress;

#if(CanDevErrorDetect == STD_ON) /* DET notifications */

	/* [SWS_CAN_00492] If development error detection for the Can module is enabled
	 The function Can_SetBaudrate shall raise the error CAN_E_UNINIT and return
	 E_NOT_OK if the driver is not yet initialized.*/
	if (CAN_E_UNINIT == ControllerState[Controller]
			|| NULL_PTR == Global_Config) {
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SETBAUDRATE_API_ID,
				CAN_E_UNINIT);
		return E_NOT_OK;
	}

	/* [SWS_CAN_00494]If development error detection for the Can module is enabled
	 the function Can_SetBaudrate shall raise the error CAN_E_PARAM_CONTROLLER
	 and return E_NOT_OK if the parameter Controller is out of range. */

	if (Controller > USED_CONTROLLERS_NUMBER) {
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SETBAUDRATE_API_ID,
				CAN_E_PARAM_CONTROLLER);
		return E_NOT_OK;
	}

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
		 *          =[Sync + Prop + Phase1 + Phase2] أ— tq
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
				((*(Global_Config->CanControllerCfgRef[Controller]).CanCpuClockRef)
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

/*****************************************************************************************/
/*    Requirment              : SWS_Can_00232                                            */
/*    Function Description    : This function enables all allowed interrupts.            */
/*    Parameter in            : Controller                                               */
/*    Parameter inout         : none                                                     */
/*    Parameter out           : none                                                     */
/*    Return value            : none                                                     */
/*    Reentrancy              : Reentrant Function                                       */
/*																                         */
/*****************************************************************************************/
void Can_EnableControllerInterrupts(uint8 Controller) {
	/* Critical Section to protect shared resources in a reentrant Function */
	irq_Disable();
#if(CanDevErrorDetect == STD_ON)
	
	/*  [SWS_Can_00209] The function Can_EnableControllerInterrupts shall raise the error CAN_E_UNINIT if
     *  the driver not yet initialized
     */
	if (CAN_UNINIT == ModuleState)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_EnableControllerInterrupts_Id,
				CAN_E_UNINIT);
    }

    /*  [SWS_Can_00210] The function Can_EnableControllerInterrupts shall raise the error
     *  CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range
     */
	else if (Controller >= USED_CONTROLLERS_NUMBER)
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
    else if (1 == DisableCnt[Controller]) {
        DisableCnt[Controller] = 0;

        /* [SWS_Can_00050] The function Can_EnableControllerInterrupts shall enable all
         * interrupts that must be enabled according the current software status
         */
		/*  Enable the specified CAN Controller Interrupts */
		CANIntEnable(Global_Config->CanHardwareObjectRef[Controller].CanControllerRef->CanControllerBaseAddress,
				 CAN_CTL_IE);
    }
	else
	{
	}
    /* End of Critical Section */
	irq_Enable();
}

/*****************************************************************************************/
/*    Requirement             : SWS_Can_00231                                            */
/*    Function Description    : This function disables all interrupts                    */
/*                            : for this CAN controller                                  */
/*    Parameter in            : Controller                                               */
/*    Parameter inout         : none                                                     */
/*    Parameter out           : none                                                     */
/*    Return value            : none                                                     */
/*    Reentrancy              : Reentrant Function                                       */
/*****************************************************************************************/
void Can_DisableControllerInterrupts(uint8 Controller) {
	/* Critical Section to protect shared resources in a reentrant Function */
	irq_Disable();
#if(CanDevErrorDetect == STD_ON)

    /*  [SWS_Can_00205] The function Can_DisableControllerInterrupts shall raise the error CAN_E_UNINIT if
     *  the driver not yet initialized
     */
	if (CAN_UNINIT == ModuleState)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DisableControllerInterrupts_Id,
				CAN_E_UNINIT);
    }

    /*  [SWS_Can_00206] The function Can_DisableControllerInterrupts shall raise the error
     *  CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range
     */
	else if (Controller >= USED_CONTROLLERS_NUMBER)
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DisableControllerInterrupts_Id,
				CAN_E_PARAM_CONTROLLER);
#endif

    /*  [SWS_Can_00202] When Can_DisableControllerInterrupts has been called
     *  several times, Can_EnableControllerInterrupts must be called as many times before
     *  the interrupts are re-enabled
     */
    if (0 == DisableCnt[Controller])
    {
        /*  [SWS_Can_00049] The function Can_DisableControllerInterrupts shall access the
         *  CAN controller registers to disable all interrupts for that CAN controller only, if
         *  interrupts for that CAN Controller are enabled
         */
        /*  Disable the specified CAN Controller Interrupts */
		CANIntDisable(Global_Config->CanHardwareObjectRef[Controller].CanControllerRef->CanControllerBaseAddress,
				 CAN_CTL_IE);
    }
    DisableCnt[Controller]++;

    /* End of Critical Section */
	irq_Enable();
}

/*****************************************************************************************/
/*    Requirement             : SWS_Can_91002                                            */
/*    Function Description    : This function de-initializes the module                  */
/*    Parameter in            : none                                                     */
/*    Parameter inout         : none                                                     */
/*    Parameter out           : none                                                     */
/*    Return value            : none                                                     */
/*    Reentrancy              : Non Reentrant Function                                   */
/*****************************************************************************************/
void Can_DeInit(void) 
{
	uint8 ControllerIndex = 0 ;
	
#if(CanDevErrorDetect == STD_ON)
    /*   The function Can_DeInit shall raise the error CAN_E_TRANSITION if the driver is not
     *   in state CAN_READY [SWS_Can_91011]
     *   [SWS_BSW_00232] Call to De-Initialization functions :
     *   The module De-Initialization function shall be called only if the module was initialized before
	 */
    if (ModuleState != CAN_READY)
    {
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DeInit_Id, CAN_E_TRANSITION);
    }

	for(ControllerIndex = 0; ControllerIndex < USED_CONTROLLERS_NUMBER; ControllerIndex++)
	{
		/*  The function Can_DeInit shall raise the error CAN_E_TRANSITION if any of the CAN
		 *  controllers is in state STARTED [SWS_Can_91012]
		 */
		if (CAN_CS_STARTED == ControllerState[ControllerIndex])
		{
			Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_DeInit_Id,
					CAN_E_TRANSITION);
		}
	}

#endif
    /*  [SWS_Can_ 91009] The function Can_DeInit shall change the module state to
     *  CAN_UNINIT before de-initializing all controllers inside the HW unit
     *  [SWS_BSW_00072] Module state after De-Initialization function
     *  The state of a BSW Module shall be set accordingly at the beginning of the DeInitialization function
     */
    ModuleState = CAN_UNINIT;

	for(ControllerIndex = 0; ControllerIndex < USED_CONTROLLERS_NUMBER; ControllerIndex++)
	{
		/*	Disable the first four bits in CAN Control Register in both controllers */
		CLR_BITS( HWREG(Global_Config->CanHardwareObjectRef[ControllerIndex].CanControllerRef->CanControllerBaseAddress + CAN_O_CTL),0
				 , CAN_CTL_INIT | CAN_CTL_IE | CAN_CTL_SIE | CAN_CTL_EIE );   // DeInit CAN controller of ControllerIndex
	}
}

/****************************************************************************************/
/*    Function Description    : This function performs the polling of RX indications    */
/*                              when CAN_RX_PROCESSING is set to POLLING.               */
/*    Parameter in            : none                                                    */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/*    Requirment              : SWS_Can_00226                                           */
/*    Notes                   :                                                        */
/*                                                                                      */
/*                                                                                      */
/*****************************************************************************************/
void Can_MainFunction_Read(void) 
{

/*variable to get HRH index in the HWObject array */
 uint8 index = 0 ;
/*array to save received data*/
 uint8 data[MAX_DATA_LENGTH] ;

    /*
     * loop for all the hardware object to get the only new avialables data in this object
     */

    for(uint8 obj_index = 0; obj_index < CAN_HRH_NUMBER; obj_index++)
    {
        index = MessageObjAssignedToHRH[obj_index].HRHIndex ;
       if(TRUE == Global_Config->CanHardwareObjectRef[index].CanHardwareObjectUsesPolling)
       {
            for(uint8 HW_Obj_Index = MessageObjAssignedToHRH[obj_index].StartMessageId;
                HW_Obj_Index <= MessageObjAssignedToHRH[obj_index].EndMessageId ; HW_Obj_Index++)
            {
                /*Initialize data pointer */
                 psMsgObject[HW_Obj_Index].pui8MsgData = data;

                /*
                 * Reads a CAN message from one of the message object buffers.
                 */
                    CANMessageGet(Global_Config->CanHardwareObjectRef[obj_index].CanControllerRef->CanControllerBaseAddress,
                                  HW_Obj_Index, &psMsgObject[HW_Obj_Index], ClrPendingInt);
                // check if this object have new data available
                if(( psMsgObject[HW_Obj_Index].ui32Flags & MSG_OBJ_NEW_DATA) == MSG_OBJ_NEW_DATA)
                {
                    // mailbox for Callback function RxIndication
                    Can_HwType Mailbox;
                    PduInfoType PduInfo;
                    //message ID
                    Mailbox.CanId = psMsgObject[HW_Obj_Index].ui32MsgID;
                    //hardware object that has new data
                    Mailbox.Hoh = obj_index;
                    // controller ID
                    Mailbox.ControllerId = Global_Config->CanHardwareObjectRef[index].CanControllerRef->CanControllerId;
                    //Save data length
                    PduInfo.SduLength = psMsgObject[HW_Obj_Index].ui32MsgLen;
                    //Save data
                    PduInfo.SduDataPtr = psMsgObject[HW_Obj_Index].pui8MsgData;
                    // 2. inform CanIf using API below.
                    CanIf_RxIndication(&Mailbox, &PduInfo);
                }

            }
       }
    }
}

/****************************************************************************************/
/*    Function Description    : This scheduled function performs the polling of bus-off */
/*                              events that are configured statically as 'to be polled'.*/
/*    Parameter in            : none                                                    */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/*    Requirment              : SWS_Can_00227                                           */
/*    Notes                   :                                                        */
/*                                                                                      */
/*                                                                                      */
/*****************************************************************************************/
void Can_MainFunction_BusOff(void) {
uint8 controllerId; /*variable to count controllers number*/
#if(CanBusoffProcessing == POLLING)
    /*
     *   Loop all controllers to get the new data
     */
    for (controllerId = 0; controllerId < USED_CONTROLLERS_NUMBER;controllerId += 1)
    {
#if (CanDevErrorDetect == STD_ON)
        if (ControllerState[controllerId] == CAN_CS_UNINIT)
        {
            Det_ReportError( CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_MAIN_FUNCTION_BUS_OFF_ID, CAN_E_UNINIT);

        }// end if
#endif //CanDevErrorDetect
        /*
         * Reads one of the controller status registers. and get bus off status
         */
        if(CANStatusGet(Global_Config->CanControllerCfgRef[controllerId].CanControllerBaseAddress,
                        CAN_STS_CONTROL) == CAN_STATUS_BUS_OFF)
        {
            // the call back function in CANIF that report the bus of state
            CanIf_ControllerBusOff(controllerId);
            // raise the BUS_OFF flag to upper Layer
            //TODO raising this error
            // Can_ErrorStateType[controllerId]= CAN_ERRORSTATE_BUSOFF;
        }// End bus_off state If
    }// End Loop
#endif
}

/************************************************************************************
* Service Name: Can_write
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Reentrant (Thread-safe)
* Parameters (in): Hth      :   information which HW-transmit handle shall be used for transmit.
*                               Implicitly this is also the information about the controller to use
*                               because the Hth numbers are unique inside one hardware unit.
*                  PduInfo  :   Pointer to SDU user memory, Data Length and Identifier.
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType
* Description: This function is called by CanIf to pass a CAN message to CanDrv for transmission.
************************************************************************************/
Std_ReturnType Can_write (
        Can_HwHandleType Hth,
        const Can_PduType * PduInfo
)
{
    Std_ReturnType returnVal = E_NOT_OK ;
	

    if (CAN_UNINIT == ModuleState)
    {

        #if (CanDevErrorDetect == STD_ON)
            // call Det function CAN_E_UNINIT
            Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_Write_Id, CAN_E_UNINIT);
        #else
            returnVal = E_NOT_OK ;
        #endif
    }
    else if (NULL_PTR == PduInfo)
    {
        /*
         * [SWS_CAN_00219] ⌈ If development error detection for CanDrv is enabled:
         * Can_Write() shall raise CAN_E_PARAM_POINTER and shall return E_NOT_OK if the
         * parameter PduInfo is a null pointer.⌋
         */
        #if (CanDevErrorDetect == STD_ON)
		    Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_Write_Id, CAN_E_PARAM_POINTER);
        #else
		    returnVal = E_NOT_OK ;
        #endif
    }
    else if (PduInfo->length > 8 )
    {
        /*
         * [SWS_Can_00218] ⌈ The function Can_Write shall return E_NOT_OK and if
         * development error detection for the CAN module is enabled shall raise the error
         * CAN_E_PARAM_DATA_LENGTH : if length is more that 8 bytes and Can controller is not CAN FD
         */
        #if (CanDevErrorDetect == STD_ON)
		Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_Write_Id, CAN_E_PARAM_DATA_LENGTH);
        #else
            returnVal = E_NOT_OK ;
        #endif
    }
    else if (FALSE == CanTriggerTransmitEnable)
    {
        /*
         * [SWS_CAN_00505] ⌈ If development error detection for CanDrv is enabled:
         * Can_Write() shall raise CAN_E_PARAM_POINTER and shall return E_NOT_OK if the
         * trigger transmit API is disabled for this hardware object (CanTriggerTransmitEnable =
         * FALSE) and the SDU pointer inside PduInfo is a null pointer.
         */
        if (PduInfo->sdu == NULL_PTR)
        {
            returnVal = E_NOT_OK ;
			Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_Write_Id, CAN_E_PARAM_POINTER);
        }
    }
    else
	{
	}
	/* end of CanDevErrorDetect */
	/*
	 * [SWS_Can_00212] ⌈ The function Can_Write shall perform following actions if the
	 * hardware transmit object is free:
	 * The mutex for that HTH is set to ‘signaled’
	 * The ID, Data Length and SDU are put in a format appropriate for the hardware
	 * (if necessary) and copied in the appropriate hardware registers/buffers.
	 * All necessary control operations to initiate the transmit are done
	 * The mutex for that HTH is released
	 * The function returns with E_OK⌋ (SRS_Can_01049)
	 */

	/*
	 * Prepare the variables to be put in the following registers:
	 * * Command Mask
	 * * Mask 1
	 * * Mask 2
	 * * Arbitration 1
	 * * Arbitration 2
	 * * Message Control
	 *
	 * All 16 bits
	 */

	uint16 ui16CmdMaskReg   = 0 ;
	uint16 ui16MaskReg_1    = 0 ;
	uint16 ui16MaskReg_2    = 0 ;
	uint16 ui16ArbReg_1     = 0 ;
	uint16 ui16ArbReg_2     = 0 ;
	uint16 ui16MsgCtrl      = 0 ;

	/*
	 *  variable to hold the base address of a can controller
	 */
	uint32 ui32Base = 0 ;

	/*
	 * local variable points to the transmit HW object that the interface wants to use.
	 */
	uint8 hth_index = 0 ;

	/*
	 *  local variable used as a counter to loop on MessageObjAssignedToHTH[] array
	 */
	uint8 Hth_count = 0 ;

	/*
	 * local variable used as a counter to loop on CanHardwareObjectRef elements to detect info about the Hw object needed.
	 */
	uint8 Hoh_count = 0 ;

	/*
	 *      local variable to hold the data
	 */
	uint8 real_hwObjectId = 0 ;

	for (Hoh_count = 0 ; Hoh_count < CAN_HOH_NUMBER  ; Hoh_count++)
	{
	    if (Hth == Global_Config->CanHardwareObjectRef[Hoh_count].CanObjectId)
		{
			hth_index = Hoh_count ;
			break ;
		}
	}
        #if (CanDevErrorDetect == STD_ON)
            /*
             * [SWS_Can_00217] If development error detection for the Can module is enabled:
             * The function Can_Write shall raise the error CAN_E_PARAM_HANDLE and shall
             * return E_NOT_OK if the parameter Hth is not a configured Hardware Transmit
             * Handle.⌋
             */
            if (Global_Config->CanHardwareObjectRef[hth_index].CanObjectType != TRANSMIT)
            {
                returnVal = E_NOT_OK ;
                //det error CAN_E_PARAM_HANDLE
                Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_Write_Id, CAN_E_PARAM_HANDLE);
            }
            else
            {
                /*MISRA Rule*/
            }
        #endif
        if (0 == HTH_Semaphore[hth_index])
        {
            HTH_Semaphore[hth_index] = 1 ;

            ui32Base = Global_Config->CanHardwareObjectRef[hth_index].CanControllerRef->CanControllerBaseAddress ;
            /*
             * check if hardware is busy
             */
            if(HWREG(ui32Base + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
            {
                /*
                 * the hardware transmit object is busy
                 * [SWS_Can_00213] ⌈ The function Can_Write shall perform no actions if the
                 * hardware transmit object is busy with another transmit request for an L-PDU:
                 * 1. The transmission of the other L-PDU shall not be cancelled and the function
                 * Can_Write is left without any actions.
                 * 2. The function Can_Write shall return CAN_BUSY. (SRS_Can_01049).
                 */
                returnVal = CAN_BUSY ;
            }
            else
            {
                ui16CmdMaskReg |= CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_DATAA |
                                  CAN_IF1CMSK_DATAB | CAN_IF1CMSK_CONTROL|
                                  CAN_IF1CMSK_ARB ;

                ui16ArbReg_2 = CAN_IF1ARB2_DIR;             /// transmit M.O.

                if (Global_Config->CanHardwareObjectRef[hth_index].CanIdType == EXTENDED)
                {
                    ui16ArbReg_1 |= PduInfo->id & CAN_IF1ARB1_ID_M ;
                    ui16ArbReg_2 |= (PduInfo->id >> 16 ) & CAN_IF1ARB2_ID_M ;
                    ui16ArbReg_2 |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD ;
                }
                else if (Global_Config->CanHardwareObjectRef[hth_index].CanIdType == STANDARD)
                {
                    ui16ArbReg_1 &=~ CAN_IF1ARB2_MSGVAL ;
                    ui16ArbReg_2 |= (  PduInfo->id  << 2 ) & CAN_IF1ARB2_ID_STAND ;

                }
                else
                {
                }
                ui16MsgCtrl |=  ( ( PduInfo->length ) & CAN_IF1MCTL_DLC_M ) ;
                ui16MsgCtrl |= CAN_IF1MCTL_EOB  | CAN_IF1MCTL_TXRQST ;

                CANDataRegWrite (
                        PduInfo->sdu,
                        (uint32 *)( ui32Base + CAN_O_IF1DA1 ),
                        PduInfo->length
                );

                HWREG(ui32Base + CAN_O_IF1CMSK) = ui16CmdMaskReg;
                HWREG(ui32Base + CAN_O_IF1MSK1) = ui16MaskReg_1;
                HWREG(ui32Base + CAN_O_IF1MSK2) = ui16MaskReg_2;
                HWREG(ui32Base + CAN_O_IF1ARB1) = ui16ArbReg_1;
                HWREG(ui32Base + CAN_O_IF1ARB2) = ui16ArbReg_2;
                HWREG(ui32Base + CAN_O_IF1ARB2) |= CAN_IF1ARB2_MSGVAL;
                HWREG(ui32Base + CAN_O_IF1MCTL) |= ui16MsgCtrl;

               for (Hth_count = 0 ; Hth_count < CAN_HTH_NUMBER  ; Hth_count++)
                {
                    uint8 index = MessageObjAssignedToHTH[Hth_count].HTHIndex ;
                    if (Hth ==  Global_Config->CanHardwareObjectRef[index].CanObjectId)
                    {
                        real_hwObjectId = MessageObjAssignedToHTH[Hth_count].MessageId ;
                        MessageObjAssignedToHTH[Hth_count].Tx_Request = TRUE ;
                        break ;
                    }
                }

                HWREG(ui32Base + CAN_O_IF1CRQ) = real_hwObjectId ;
                HTH_Semaphore[hth_index] = 0 ;

                /*
                 *  [SWS_Can_00276] ⌈ The function Can_Write shall store the swPduHandle that is
                    given inside the parameter PduInfo until the Can module calls the
                    CanIf_TxConfirmation for this request where the swPduHandle is given as
                    parameter.()
                 */
                swPduHandle[Hth_count] = PduInfo->swPduHandle ;

                    /*
                     * (SRS_Can_01049)
                     */
                returnVal = E_OK ;
            }
        }
        else
        {
               /*MISRA Rule*/
        }


    return returnVal ;
}

static void CANDataRegWrite ( uint8 * pui8Data, uint32 * pui32Register , uint8 ui8Size)
{

    uint8 index ;
    uint16 ui16DataValue ;


    for (index = 0 ; index < ui8Size;)
    {

        ui16DataValue = pui8Data[index++] ;

        if (index < ui8Size)
        {
            ui16DataValue |= ( pui8Data[index++] << 8 ) ;
        }


        HWREG(pui32Register++) = ui16DataValue;

    }


}

/*---------------------------------------------------------------------
 Function Name:  <Can_MainFunction_Mode>
 Service ID:     <0x0c>
 Description:
 - Scheduled function.
 - This function performs the polling of CAN controller mode transitions.
 - it implements the polling of CAN status register flags to detect transition of CAN Controller state.
 ----------------------------------------------------------------------*/
void Can_MainFunction_Mode(void)
{
    /* counter to loop on controllers         */
    uint8 ControllerIndex  = 0 ;
    /* static variable to save old state      */
    static uint8 Old_State[USED_CONTROLLERS_NUMBER] = {0} ;
    /* variable to read HW status register    */
    uint8  StatusReg_State = 0 ;
    /* variable to save Controller BaseAddress*/
    uint32 ui32Base = 0;
    /*
     *  [SWS_Can_00370] The function Can_Mainfunction_Mode shall poll a flag of the
     *   CAN status register until the flag signals that the change takes effect and
     *   notify the upper layer with function CanIf_ControllerModeIndication about
     *   a successful state transition referring to the corresponding CAN controller
     *   with the abstract CanIf ControllerId .
     */
    for (ControllerIndex = 0; ControllerIndex < USED_CONTROLLERS_NUMBER;ControllerIndex++)
    {
        /*Save current controller BaseAddress*/
        ui32Base        = Global_Config->CanControllerCfgRef[ControllerIndex]\
                                                                 .CanControllerBaseAddress;
        /*Save Current hardware state */
        StatusReg_State = HWREG(ui32Base + CAN_O_CTL) & CAN_CTL_INIT ;  
        /* CAN_CS_STARTED state transition successfully achieved
         * and confirmed from HW register .
         * Send notification to CanIf only if CHANGE in state successfully achieved
         */
        if(ControllerState[ControllerIndex] == CAN_CS_STARTED      &&   \
           StatusReg_State                  != CAN_CTL_INIT        &&   \
           Old_State[ControllerIndex]       != CAN_CS_STARTED  )
        {
           CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_STARTED);
           Old_State[ControllerIndex]  = CAN_CS_STARTED ;
        }
        /* CAN_CS_STOPPED state transition successfully achieved
         * and confirmed from HW register .
         * Send notification to CanIf only if CHANGE in state successfully achieved
         */
        else if(ControllerState[ControllerIndex] == CAN_CS_STOPPED &&   \
                StatusReg_State                  == CAN_CTL_INIT   &&   \
                Old_State[ControllerIndex]       != CAN_CS_STOPPED  )
        {
                CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_STOPPED);
                Old_State[ControllerIndex]  = CAN_CS_STOPPED ;
        }
        /* CAN_CS_SLEEP state transition successfully achieved
         * Sleep mode not supported by HW so no register reading
         * Send notification to CanIf only if CHANGE in state successfully achieved
         */
        else if(ControllerState[ControllerIndex] == CAN_CS_SLEEP   &&  \
                Old_State[ControllerIndex]       != CAN_CS_STOPPED     \
                 )
        {
            CanIf_ControllerModeIndication(ControllerIndex, CAN_CS_SLEEP);
            Old_State[ControllerIndex]  = CAN_CS_SLEEP ;
        }
        else
        {
            /*Do Nothing MISRA rule*/
        }
    }
}

/*[SWS_Can_00230]*/
/********************************************************************************************/
/* Service Name     : Can_SetControllerMode                                                 */
/* Syntax           : Std_ReturnType Can_SetControllerMode                                  */
/*                    (uint8 Controller,Can_ControllerStateType Transition)                 */
/* Service ID[hex]  : 0x03                                                                  */
/* Sync/Async       : Asynchronous                                                          */
/* Reentrancy       : Non Reentrant                                                         */
/* Parameters (in)  : Controller CAN controller for which the status shall be changed       */
/*                    Transition Transition value to request new CAN controller state       */
/* Parameters(inout): None                                                                  */
/* Parameters (out) : None                                                                  */
/* Return Value     : Std_ReturnType E_OK    : request accepted                             */
/* E_NOT_OK         : request not accepted, a development error occurred                    */
/* DESCRIPTION      : This function performs software triggered state transitions           */
/* of the CAN controller State machine.                                                     */
/********************************************************************************************/
Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition )
{
    /*initialize local variable to return (E_OK,E_NOT_OK) */
    Std_ReturnType ret = E_OK;
    uint32 ui32BaseAddress = 0;

    /*[SWS_Can_00198] If development error detection for the Can module is enabled:
    if the module is not yet initialized, the function Can_SetControllerMode shall raise
    development error CAN_E_UNINIT and return E_NOT_OK.*/
    if (CAN_UNINIT == ModuleState )
    {
        #if (CanDevErrorDetect == STD_ON)
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SET_CONTROLLER_MODE, CAN_E_UNINIT);
        #endif
        ret = E_NOT_OK;
    }

    /* [SWS_Can_00199] If development error detection for the Can module is enabled:
                   if the parameter Controller is out of range, the function Can_SetControllerMode
                   shall raise development error CAN_E_PARAM_CONTROLLER and return
                   E_NOT_OK.*/
    else if(Controller >= MAX_CONTROLLERS_NUMBER)
    {
        #if (CanDevErrorDetect == STD_ON)
        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_SET_CONTROLLER_MODE, CAN_E_PARAM_CONTROLLER);
        #endif
        ret = E_NOT_OK;
    }

    /* [SWS_Can_00200] If development error detection for the Can module is enabled:
                   if an invalid transition has been requested, the function Can_SetControllerMode shall
                   raise the error CAN_E_TRANSITION and return E_NOT_OK.*/
    else if(((Transition == CAN_CS_STARTED) && ( ControllerState[Controller]!=CAN_CS_STOPPED))  ||
            ((Transition == CAN_CS_SLEEP) &&  (ControllerState[Controller]!= CAN_CS_STOPPED     ||
             ControllerState[Controller]!= CAN_CS_SLEEP)))
    {
        #if (CanDevErrorDetect == STD_ON)
        Det_ReportError( CAN_MODULE_ID ,CAN_INSTANCE_ID ,CAN_SET_CONTROLLER_MODE ,CAN_E_TRANSITION );
        #endif
        ret = E_NOT_OK;
    }
    else
    {
        ui32BaseAddress = Global_Config->CanControllerCfgRef[Controller].CanControllerBaseAddress;
        switch(Transition)
        {
        case CAN_CS_STARTED:
            /*[SWS_Can_00261] The function Can_SetControllerMode(CAN_CS_STARTED)
                  shall set the hardware registers in a way that makes the CAN controller participating
                  on the network.*/

            /* [SWS_Can_00384] Each time the CAN controller state machine is triggered with the state
               transition value CAN_CS_STARTED, the function Can_SetControllerMode shall re-initialise
               the CAN controller with the same controller configuration set previously used by functions
               Can_SetBaudrate or Can_Init.*/


            /* Enables the CAN controller for message processing.  Once enabled, the
               controller automatically transmits any pending frames, and processes any
               received frames.*/
             HWREG(ui32BaseAddress + CAN_O_CTL) &= ~CAN_CTL_INIT;
           /* setting the new mode to STARTED */
             ControllerState[Controller] = CAN_CS_STARTED;
             break;

        case CAN_CS_STOPPED:

            /* STOPPED state in the TivaC CAN Controller is achieved
             * by setting the INIT bit in the CANControl(CANCTL)register
             * While INIT is set,all message transfers to and from the CANbus
             * are stopped and the CANnTX signal is held High. Entering
             * the initialization state does not change the configuration of the CANcontroller,
             * the message objects,or the error counters
             * Check DataSheet section 17.3.1 page 1046
             */

            HWREG(ui32BaseAddress + CAN_O_CTL) |= CAN_CTL_INIT;

            /* setting the new mode to STOPPED */
            ControllerState[Controller] = CAN_CS_STOPPED;
            break;
        case CAN_CS_SLEEP:
            /*[SWS_Can_00258] When the CAN hardware does not support sleep mode and is triggered to
                     transition into SLEEP state, the Can module shall emulate a logical SLEEP state from which it
                     returns only, when it is triggered by software to transition into STOPPED state.*/

            /*[SWS_Can_00404] The CAN hardware shall remain in state STOPPED, while the logical SLEEP state is active.
              [SWS_Can_00290] If the CAN HW does not support a sleep mode, the function
                     Can_SetControllerMode(CAN_CS_SLEEP) shall set the CAN controller to the logical sleep mode.*/

            /*[SWS_Can_00197] The function Can_SetControllerMode shall disable interrupts that are not allowed in the new state. */

            HWREG(ui32BaseAddress + CAN_O_CTL) |= CAN_CTL_INIT;
            /*[SWS_Can_00282] The function Can_SetControllerMode(CAN_CS_STOPPED)
                             shall cancel pending messages.*/

            /* setting the new mode to SLEEP */
            ControllerState[Controller] = CAN_CS_SLEEP;
            break;
        default:
            ret = E_NOT_OK;
        }
    }

    return ret;
}


/**
This function checks if a wakeup has occurred for the given controller.
Service ID[hex]:0x11
Parameters (in): Controller --> Abstracted CanIf ControllerId which is assigned to a CAN controller, which is requested for ErrorState.
Parameters (out): ErrorStatePtr --> Pointer to a memory location, where the error state of the CAN controller will be stored
Return value:   Std_ReturnType  -->E_OK: Error state request has been accepted
                                   E_NOT_OK:Error state request has not been accepted
*/
Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId,Can_ErrorStateType* ErrorStatePtr)
{

/*Save Return value*/
Std_ReturnType Return_type =E_OK;
uint32  BaseAddress=0;
/*Variable to read CAN Error state register*/
Can_ErrorStateType   ErrorState = 0;

    /*
     [SWS_Can_91005]  If development error detection for the Can module is enabled: if the module is not yet initialized,
      the function Can_GetControllerErrorState shall raise development error CAN_E_UNINIT and return E_NOT_OK
    */
    if(ModuleState == CAN_UNINIT)
    {
        #if(CanDevErrorDetect == STD_ON)
            Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_GetControllerErrorState_Id, CAN_E_UNINIT);
        #else
            Return_type = E_NOT_OK;
        #endif
    }
    /**
    [SWS_Can_91006]  If development error detection for the Can module is enabled: if the parameter ControllerId is out of range,
    the function Can_GetControllerErrorState shall raise development error CAN_E_PARAM_CONTROLLER and return E_NOT_OK.
    */
    else if(ControllerId >= USED_CONTROLLERS_NUMBER )
    {
        #if(CanDevErrorDetect == STD_ON)
            Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_GetControllerErrorState_Id, CAN_E_PARAM_CONTROLLER);
        #else
            Return_type = E_NOT_OK;
        #endif
    }

    /**
    [SWS_Can_91007]  If development error detection for the Can module is enabled: if the parameter ErrorStatePtr is a null pointer,
     the function Can_GetControllerErrorState shall raise development error  CAN_E_PARAM_POINTER and return E_NOT_OK.
    */
    else if(ErrorStatePtr == NULL_PTR)
    {
        #if(CanDevErrorDetect == STD_ON)
            Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_GetControllerErrorState_Id, CAN_E_PARAM_POINTER);
        #else
            Return_type = E_NOT_OK;
        #endif

    }

/**
[SWS_Can_91008] When the API Can_GetControllerErrorState()  is called with Controller Id as input parameter then Can driver shall read
the error state register of Can Controller and shall return the error status to upper layer
*/

             /* Save Current controller BaseAddress*/
             BaseAddress = Global_Config->CanControllerCfgRef[ControllerId].CanControllerBaseAddress ;
             /* Save Error State it can be
              *BussOff OR Error Active state Or Error Passive state
              */
             ErrorState  = (HWREG(BaseAddress + CAN_O_STS) & CAN_STS_BOFF ) | \
                           (HWREG(BaseAddress + CAN_O_STS) & CAN_STS_EPASS) ;
                  switch (ErrorState)
                  {
                      case CAN_ERRORSTATE_ACTIVE  :
                      *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
                      break;
                      case  CAN_ERRORSTATE_PASSIVE:
                      *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
                      break;
                      case CAN_ERRORSTATE_BUSOFF  :
                      *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF ;
                      default  :
                      Return_type =E_NOT_OK;
                      break;
                  }

  return  Return_type;
}

Std_ReturnType Can_GetControllerMode(uint8 Controller,Can_ControllerStateType* ControllerModePtr) 
{
	Std_ReturnType Loc_Can_GetControllerMode_Ret = E_OK;
    /*  [SWS_Can_91016] If development error detection for the Can module is enabled:
     *  The function Can_GetControllerMode shall raise the error CAN_E_UNINIT and
     *  return E_NOT_OK if the driver is not yet initialized.
     *  ( SRS_BSW_00406,SRS_BSW_00416)
     */
	if(ModuleState == CAN_UNINIT)
	{
        #if(CanDevErrorDetect == STD_ON)
	        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, Can_GetControllerErrorState_Id, CAN_E_UNINIT);
        #else
	        Loc_Can_GetControllerMode_Ret = E_NOT_OK;
        #endif
	}
	/*[SWS_Can_91017] If parameter Controller of Can_GetControllerMode() has an invalid value,
	 *  the CanDrv shall report development error code CAN_E_PARAM_CONTROLLER to the Det_ReportError
	 *  service of the DET.(SRS_BSW_00323)
	 */
	else if(NUM_OF_CAN_CONTROLLERS <= Controller)
	{
        #if(CanDevErrorDetect == STD_ON)
	        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,Can_GetControllerMode_Id, CAN_E_PARAM_CONTROLLER);
        #else
	        Loc_Can_GetControllerMode_Ret = E_NOT_OK;
        #endif
	}
	/*[SWS_Can_91018] If parameter ControllerModePtr of Can_GetControllerMode() has an null pointer,
	 *  the CanDrv shall report development error code CAN_E_PARAM_POINTER to the Det_ReportError
	 *   service of the DET. (SRS_BSW_00323)
	 */
	else if(NULL_PTR == ControllerModePtr)
	{
        #if(CanDevErrorDetect == STD_ON)
	        Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID,Can_GetControllerMode_Id, CAN_E_PARAM_POINTER);
        #else
	        Loc_Can_GetControllerMode_Ret = E_NOT_OK;
        #endif
	}
	/*
	 * [SWS_Can_91015] The service Can_GetControllerMode shall return the mode
	 * of the requested CAN controller.
	 */
	else
	{
	    *ControllerModePtr = ControllerState[Controller];
	}
	return Loc_Can_GetControllerMode_Ret;
}

#if(CanTxProcessing == MIXED_PROCESSING || CanTxProcessing == POLLING_PROCESSING)
/*
 *	[SRS_Can_01051] The CAN Driver shall provide a transmission
 *	confirmation service
 */
void Can_MainFunction_Write(void) 
{
	uint8  counter= 0;
	uint8  index = 0;
	uint32 BaseAddress = 0 ;
	uint32 Read_TXRQ_register = 0 ;
	uint8  Read_STS_register  = 0 ;

    /*
    * Search only in the Transmit objects array
    * */
    for (counter = 0; counter < CAN_HTH_NUMBER; counter++)
    {

        /*Get HTH index in the CanHardwareObject array */
        index = MessageObjAssignedToHTH[counter].HTHIndex ;

        /*Only check messages that were polling enabled */
        if (TRUE == Global_Config->CanHardwareObjectRef[index].CanHardwareObjectUsesPolling )
        {
            /**Save Message controller BaseAddress */
            BaseAddress = Global_Config->CanHardwareObjectRef[index].CanControllerRef->CanControllerBaseAddress ;
            /*Check if the message had a transmit request */
            if(MessageObjAssignedToHTH[counter].Tx_Request == TRUE)
            {

                /*The CANTXRQ1 and CANTXRQ2 registers hold the TXRQST bits of the 32 message objects.
                 *  By reading out these bits,the CPU can check which message object
                 *  has a transmission request pending.*/

                /*The CANTXRQ1 holds the first 16 messages*/
                if(MessageObjAssignedToHTH[counter].MessageId<= 16 )
                {
                    Read_TXRQ_register = HWREG(BaseAddress + CAN_O_TXRQ1) ;
                }
                /*The CANTXRQ2 holds the last 16 messages*/
                else if(MessageObjAssignedToHTH[counter].MessageId<=32)
                {
                    Read_TXRQ_register = HWREG(BaseAddress + CAN_O_TXRQ2)<<16 ;
                }
                else
                {
                    /**MISRA Rule**/
                }
                /*Read Status register to check TXOK transmitted message successfully*/
                Read_STS_register = HWREG(BaseAddress + CAN_O_STS) & CAN_STS_TXOK;

                /*If TXOK and message request has been cleared and Call Tx_Confirmation*/
                if(!(Read_TXRQ_register &(1<<(MessageObjAssignedToHTH[counter].MessageId-1))))
                {
                    /*Reset Tx_Request flag*/
                    MessageObjAssignedToHTH[counter].Tx_Request = FALSE ;
                    /*Reset TXOK bit*/
                    if(Read_STS_register)
                    {
                    HWREG(BaseAddress + CAN_O_STS) &= ~CAN_STS_TXOK ;
                    }
                    /*Call Tx_Confirmation indication for successful transmission */
                    CanIf_TxConfirmation(swPduHandle[counter]);
                }
            }
        }
    }
}
#endif



#if( CanTxProcessing == MIXED_PROCESSING || CanTxProcessing == INTERRUPT_PROCESSING ||\
     CanRxProcessing == MIXED_PROCESSING || CanRxProcessing == INTERRUPT_PROCESSING )
static void Serve_Interrupts(uint32 BaseAddress)
{
    uint8 count = 0;
    uint8 index = 0;
    uint32 Read_INTPND_Register = 0 ;


    Read_INTPND_Register = HWREG(BaseAddress + CAN_O_MSG1INT ) & CAN_MSG1INT_INTPND_M;
    Read_INTPND_Register |=((HWREG(BaseAddress + CAN_O_MSG2INT )&CAN_MSG1INT_INTPND_M)<<16) ;

    for(count=0 ;count< CAN_HTH_NUMBER ;count++ )
    {
        index = MessageObjAssignedToHTH[count].HTHIndex ;
        if(Global_Config->CanHardwareObjectRef[index].CanHardwareObjectUsesPolling == FALSE)
        {
            if(Read_INTPND_Register &(1<<(MessageObjAssignedToHTH[count].MessageId-1)))
            {
                HWREG(BaseAddress + CAN_O_IF1CMSK) = CAN_IF1CMSK_CLRINTPND ;
                HWREG(BaseAddress + CAN_O_IF1MCTL) &= ~ CAN_IF1MCTL_INTPND ;
                HWREG(BaseAddress + CAN_O_IF1CRQ)   = MessageObjAssignedToHTH[count].MessageId ;
                HWREG(BaseAddress + CAN_O_STS) &=~CAN_STS_TXOK ;
                /*Reset Tx_Request flag*/
                MessageObjAssignedToHTH[count].Tx_Request = FALSE ;
                CanIf_TxConfirmation(swPduHandle[count]);
            }

        }
    }
    for(count=0 ;count< CAN_HRH_NUMBER ;count++ )
    {
        index = MessageObjAssignedToHRH[count].HRHIndex ;
        if(Global_Config->CanHardwareObjectRef[index].CanHardwareObjectUsesPolling == FALSE)
        {
            for(uint8 HW_Obj_Index = MessageObjAssignedToHRH[count].StartMessageId;
                      HW_Obj_Index <= MessageObjAssignedToHRH[count].EndMessageId ; HW_Obj_Index++)
            {
                if(Read_INTPND_Register &(1<<(HW_Obj_Index-1)))
                {
                    HWREG(BaseAddress + CAN_O_IF2CMSK) = (CAN_IF2CMSK_DATAA | CAN_IF1CMSK_DATAB |\
                                                          CAN_IF2CMSK_CONTROL | CAN_IF1CMSK_MASK|\
                                                          CAN_IF2CMSK_ARB);
                    HWREG(BaseAddress + CAN_O_IF2CRQ)   =  HW_Obj_Index ;
                    // mailbox for Callback function RxIndication
                    Can_HwType Mailbox;
                    PduInfoType PduInfo;
                    uint8 Data[MAX_DATA_LENGTH];

                    //message ID
                    if(Global_Config->CanHardwareObjectRef[index].CanIdType == STANDARD)
                    {
                        Mailbox.CanId = (HWREG(BaseAddress + CAN_O_IF2ARB2) & CAN_IF2ARB2_ID_STANDARD) >>2 ;
                    }
                    else
                    {
                        Mailbox.CanId = HWREG(BaseAddress + CAN_O_IF2ARB1) |
                                        ((HWREG(BaseAddress + CAN_O_IF2ARB2) & CAN_IF2ARB2_ID_M)<<16) ;
                    }
                    //hardware object that has new data
                    Mailbox.Hoh = Global_Config->CanHardwareObjectRef[index].CanObjectId;
                    // controller ID
                    Mailbox.ControllerId = Global_Config->CanHardwareObjectRef[index].CanControllerRef->CanControllerId;
                    //Save data length
                    PduInfo.SduLength = HWREG(BaseAddress + CAN_O_IF2MCTL) & CAN_IF2MCTL_DLC_M ;
                    //Save data
                    _CANDataRegRead( Data ,(uint32*)( BaseAddress+CAN_O_IF2DA1), PduInfo.SduLength) ;
                    PduInfo.SduDataPtr = Data;
                    // 2. inform CanIf using API below.
                    CanIf_RxIndication(&Mailbox, &PduInfo);
                    HWREG(BaseAddress + CAN_O_IF2MCTL) &= ~ CAN_IF1MCTL_INTPND ;
                    HWREG(BaseAddress + CAN_O_IF2CMSK) = CAN_IF2CMSK_CLRINTPND ;
                    HWREG(BaseAddress + CAN_O_STS) &=~CAN_STS_RXOK;
                    HWREG(BaseAddress + CAN_O_IF2CRQ)   = HW_Obj_Index ;

                }
            }
        }
    }
}

#endif

void CAN0_Handler(void)
{
#if( CanTxProcessing == MIXED_PROCESSING || CanTxProcessing == INTERRUPT_PROCESSING ||\
     CanRxProcessing == MIXED_PROCESSING || CanRxProcessing == INTERRUPT_PROCESSING )
    Serve_Interrupts(CAN0_BASE_ADDRESS) ;
#endif

}

void CAN1_Handler(void)
{
#if( CanTxProcessing == MIXED_PROCESSING || CanTxProcessing == INTERRUPT_PROCESSING ||\
     CanRxProcessing == MIXED_PROCESSING || CanRxProcessing == INTERRUPT_PROCESSING )
    Serve_Interrupts(CAN1_BASE_ADDRESS) ;
#endif
}





/* Prototype for the function that is called when an invalid argument is passed
 * to an API.  This is only used when doing a DEBUG build.
 */
__attribute__((naked)) void assert_failed (char const *file, int line) {
    (void)file; /* avoid the "unused parameter" compiler warning */
    (void)line;    /* avoid the "unused parameter" compiler warning */
	/* For a production code , I think it is better to reset the system
	 * not to cause an infinite loop which is a denial service
	 * NVIC_SystemReset Function exists in "core_cm4.h" 
	 */
    NVIC_SystemReset(); /* reset the system */
}
