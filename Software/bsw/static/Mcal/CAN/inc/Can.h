/*****************************************************************************************/
/*                                                                                       */
/*    layer              :  MCAL                                                         */
/*                                                                                       */
/*    Component          :  CAN                                                          */
/*    Description        :                                                               */
/*                                                                                       */
/*    Module             :  CAN                                                          */
/*    Description        :  The Can module is part of the lowest layer, performs the     */
/*                          hardware access and offers a hardware independent API to     */
/*                          the upper layer.                                             */
/*                          The only upper layer that has access to the Can module is    */
/*                          the CanIf module (see also SRS_SPAL_12092).                  */
/*                          The Can module provides services for initiating transmissions*/
/*                          and calls the callback functions of the CanIf module for     */
/*                          notifying events, independently from the hardware.           */
/*                          Furthermore, it provides services to control the behavior    */
/*                          and state of the CAN controllers that are belonging to       */
/*                          the same CAN Hardware Unit.                                  */
/*                          Several CAN controllers can be controlled by a single Can    */
/*                          module as long as they belong to the same CAN Hardware Unit  */
/*                                                                                       */
/*    File               :  Can.h                                                        */
/*    HW Target          :  TivaC(TM4C123GH6PM Microcontroller)                       	 */
/*    Team               :  AUTOSAR_NINJA                                                */
/*    Coding languages   :  c                                                            */
/*    Autosar Version    :  4.3.1                                                        */
/*    Sw Version         :  1.0.0                                                        */
/*****************************************************************************************/

#ifndef CAN_H_
#define CAN_H_

/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "ComStack_Types.h"
/*****************************************************************************************/
/*                                    Macro Definition                                   */
/*****************************************************************************************/

/* CAN StatusType ENUM */

typedef uint8 Can_StatusType ;
#define INITIALIZED     1
#define CAN_UNINIT     ((Can_StatusType)0x00)
#define CAN_READY      ((Can_StatusType)0x01)


/* Can_DetErrorType ENUM */
typedef uint8 Can_DetErrorType ;


#define CAN_E_PARAM_DLC             0x03
#define CAN_E_DATALOST              0x07

#define CAN_E_PARAM_POINTER              ((Can_DetErrorType)0x01)
#define CAN_E_PARAM_HANDLE               ((Can_DetErrorType)0x02)
#define CAN_E_PARAM_DATA_LENGTH          ((Can_DetErrorType)0x03)
#define CAN_E_PARAM_CONTROLLER           ((Can_DetErrorType)0x04)
#define CAN_E_UNINIT                     ((Can_DetErrorType)0x05)
#define CAN_E_TRANSITION                 ((Can_DetErrorType)0x06)
#define CAN_E_PARAM_BAUDRATE             ((Can_DetErrorType)0x07)
#define CAN_E_ICOM_CONFIG_INVALID        ((Can_DetErrorType)0x08)
#define CAN_E_INIT_FAILED                ((Can_DetErrorType)0x09)


/* Can_ServiceId ENUM  */
typedef uint8 Can_ServiceId ;

#define  Can_Init_Id                          ((Can_ServiceId)0x00)
#define  Can_GetVersionInfo_Id                ((Can_ServiceId)0x07)
#define  Can_DeInit_Id                        ((Can_ServiceId)0x10)
#define  Can_SetBaudrate_Id                   ((Can_ServiceId)0x0f)
#define  Can_SetControllerMode_Id             ((Can_ServiceId)0x03)
#define  Can_DisableControllerInterrupts_Id   ((Can_ServiceId)0x04)
#define  Can_EnableControllerInterrupts_Id    ((Can_ServiceId)0x05)
#define  Can_CheckWakeup_Id                   ((Can_ServiceId)0x0b)
#define  Can_GetControllerErrorState_Id       ((Can_ServiceId)0x11)
#define  Can_GetControllerMode_Id             ((Can_ServiceId)0x12)
#define  Can_Write_Id                         ((Can_ServiceId)0x06)




#define NULL_PTR  ((void*)0)



//*****************************************************************************
//  Enables / disables API Can_MainFunction_BusOff() for
//  handling Busoff events in polling mode.
//*****************************************************************************
typedef uint8 CanBusoffProcessingType;


//*****************************************************************************
//  Enables / disables API Can_MainFunction_Wakeup() for handling wakeup events
//  in polling mode.
//*****************************************************************************
typedef uint8 CanWakeupProcessingType;


//*****************************************************************************
//  Enables / disables API Can_MainFunction_Read() for handling PDU reception
//*****************************************************************************
typedef uint8 CanRxProcessingType;



//*****************************************************************************
//  Enables / disables API Can_MainFunction_Read() for handling PDU transmission
//  events in polling mode.
//*****************************************************************************
typedef uint8 CanTxProcessingType;



//*****************************************************************************
//  Specifies the type (Full-CAN or Basic-CAN) of a hardware object.
//*****************************************************************************
typedef uint8 CanHandleTypeType;
#define BASIC       ((CanHandleTypeType)0x0)
#define FULL        ((CanHandleTypeType)0x1)

//*****************************************************************************
//  Specifies whether the IdValue is of type
//  standard identifier
//  extended identifier
//  mixed mode
//*****************************************************************************

typedef uint8 CanIdTypeType;
#define EXTENDED    ((CanIdTypeType)0x0)
#define MIXED       ((CanIdTypeType)0x1)
#define STANDARD    ((CanIdTypeType)0x2)

//*****************************************************************************
//  Specifies if the HardwareObject is used as Transmit or as Receive object
//*****************************************************************************
typedef uint8 CanObjectTypeType;
#define RECEIVE     ((CanObjectTypeType)0x0)
#define TRANSMIT    ((CanObjectTypeType)0x1)

typedef float64 McuClockReferencePoint;


//*****************************************************************************
//  This container contains bit timing related configuration parameters of the
//  CAN controller(s).
//*****************************************************************************
typedef struct
{

	/* Specifies the baudrate of the controller in kbps */
	uint16  CanControllerBaudRate ;           /* Range min=0 to max=2000 */

	/* Uniquely identifies a specific baud rate configuration. This ID is used by SetBaudrate API*/
	uint16  CanControllerBaudRateConfigID ;  /* Range min=0 to max=65535 */

	/* Specifies propagation delay in time quantas */
	uint8 CanControllerPropSeg;             /* Range min=0 to max=255 */

	/* Specifies phase segment 1 in time quantas*/
	uint8 CanControllerSeg1;               /* Range min=0 to max=255 */

	/* Specifies phase segment 2 in time quantas*/
	uint8 CanControllerSeg2;               /* Range min=0 to max=255 */

	/* Specifies the synchronization jump width for the controller in time quantas*/
	uint8 CanControllerSyncJumpWidth;     /* Range min=0 to max=255 */

}CanControllerBaudrateConfig;
//*****************************************************************************
//  This container contains the configuration parameters of the CAN
//  controller(s).
//*****************************************************************************
typedef struct
{
            /*Enables / disables API Can_MainFunction_BusOff() */
              //  CanBusoffProcessingType     CanBusoffProcessing;

            /*Defines if a CAN controller is used in the configuration. */
                //boolean                     CanControllerActivation;
            /*Specifies the CAN controller base address.*/
                uint32                      CanControllerBaseAddress;

            /*This parameter provides the controller ID which is unique in a given CAN
               Driver. The value for this parameter starts with 0 and continue without any gaps. */
                uint8                       CanControllerId;

            /*Enables / disables API Can_MainFunction_Read() for handling PDU reception */
             //   CanRxProcessingType         CanRxProcessing;

            /*Enables / disables API Can_MainFunction_Read() for handling PDU transmission */
              //  CanTxProcessingType         CanTxProcessing;

            /*Adds / removes the service Can_CheckWakeup() from the code.
              True: Can_CheckWakeup can be used.
              False: Can_CheckWakeup cannot be used. */
              //  boolean                     CanWakeupFunctionalityAPI;

            /*Enables / disables API Can_MainFunction_Wakeup() for handling wakeup events
              in polling mode.*/
             //   CanWakeupProcessingType     CanWakeupProcessing;

            /*CAN driver support for wakeup over CAN Bus. */
              //  boolean                     CanWakeupSupport;

            /*Reference to baudrate configuration container configured for the Can
              Controller. */
                 CanControllerBaudrateConfig* CanControllerDefaultBaudrate;
								 
					  /* CanCpu clock reference 
	           * [ECUC_Mcu_00175]This is the frequency for the specific instance of the McuClockReferencePoint container.
						 *It shall be given in Hz */
	                McuClockReferencePoint 			*CanCpuClockRef;
}CanController;

//*****************************************************************************
//  This container is only valid for HRHs and contains the configuration
//   (parameters) of one hardware filter.
//*****************************************************************************
typedef struct
{
             /*Specifies (together with the filter mask) the identifiers range that passes
               the hardware filter.*/
                 uint32                         CanHwFilterCode;

             /*Describes a mask for hardware-based filtering of CAN identifiers. The CAN
               identifiers of incoming messages are masked with the appropriate
               CanFilterMaskValue. Bits holding a 0 mean don't care*/
                 uint32                         CanHwFilterMask;
}CanHwFilter;


//*****************************************************************************
//  This container contains the configuration (parameters) of CAN Hardware
//  Objects.
//*****************************************************************************
typedef struct
{
            /*Specifies the value which is used to pad unspecified data in CAN FD
              frames > 8 bytes for transmission*/
           //      uint8                        CanFdPaddingValue;

            /*Specifies the type (Full-CAN or Basic-CAN) of a hardware object. */
                 CanHandleTypeType             CanHandleType;

            /*Number of hardware objects used to implement one HOH. In case of a
              HRH this parameter defines the number of elements in the hardware FIFO
              or the number of shadow buffers, in case of a HTH it defines the number of
              hardware objects used for multiplexed transmission or for a hardware FIFO
              used by a FullCAN HTH. */
                  uint16                      CanHwObjectCount;

            /*Specifies the IdValuetype */
                  CanIdTypeType               CanIdType;

            /*Holds the handle ID of HRH or HTH. The value of this parameter is unique
              in a given CAN Driver, and it should start with 0 and continue without any gaps.
              The HRH and HTH Ids share a common ID range.
              Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3 */
                  uint16                         CanObjectId;

             /*Specifies if the HardwareObject is used as Transmit or as Receive object*/
                  CanObjectTypeType              CanObjectType;

             /*This parameter defines if or if not Can supports the trigger-transmit API for this handle. */
                //  boolean                        CanTriggerTransmitEnable;

             /*Reference to CAN Controller to which the HOH is associated to.*/
                  CanController                  *CanControllerRef;

             /*This container is only valid for HRHs and contains the
               configuration (parameters) of one hardware filter. */
                  CanHwFilter                   *CanHwFilterRef;

}CanHardwareObject;
//*****************************************************************************
//  This container contains the configuration parameters and sub containers of
//  the AUTOSAR Can module.
//*****************************************************************************

typedef struct
{
            /*Reference to CAN Controller to which the HOH is associated to.*/
                CanController                  *CanControllerRef;
            /*This container contains the configuration (parameters) of CAN Hardware Objects. */
                CanHardwareObject              *CanHardwareObjectRef;
}CanConfigSet;


//*****************************************************************************
//  This container holds the configuration of a single CAN Driver.
//*****************************************************************************
typedef struct
{
            /*This container contains the configuration parameters and sub
              containers of the AUTOSAR Can module...Multiplicity =1 */
                CanConfigSet                    *CanConfigSetRef;
}Can_ConfigType;
/* -------------------------------------------------------------------------- */
/*                             Functions Prototype                            */
/* -------------------------------------------------------------------------- */
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
void Can_Init( const Can_ConfigType* Config);

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
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID ) ;

void Can_DeInit(void);
void Can_DisableControllerInterrupts(uint8 Controller);
void Can_EnableControllerInterrupts(uint8 Controller);
void CANDeInit(void);

#endif /* CAN_H_ */
