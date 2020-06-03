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
/*    File               :  Can_Cfg.h                                                    */
/*    HW Target          :  TivaC(TM4C123GH6PM Microcontroller)                       	 */
/*    Team               :  AUTOSAR_NINJA                                                */
/*    Coding languages   :  c                                                            */
/*    Autosar Version    :  4.3.1                                                        */
/*    Sw Version         :  1.0.0                                                        */
/*****************************************************************************************/

#ifndef CAN_CFG_H_
#define CAN_CFG_H_

/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/
#include "Can_PBcfg.h"
/*****************************************************************************************/
/*                                    Macro Definition                                   */
/*****************************************************************************************/



#define MAX_BAUDRATE_CONFIGS_CONTROLLER_0 	     (1U)
#define MAX_BAUDRATE_CONFIGS_CONTROLLER_1	     (1U)
#define USED_CONTROLLERS_NUMBER                  (1U)                /*number of can controllers in the ECU*/
#define CAN_HOH_NUMBER                           (2U)
#define CAN_HRH_NUMBER                           (1U)
#define CAN_HTH_NUMBER                           (1U)
#define CLOCK                                    (80000000)            /*Can Clock in Hz*/
#define CONTROLLER_0_BDR_ID                      (0U)
#define CONTROLLER0_ID                           (0U)
#define DEFAULT_BAUDRATE_CONFIGRATION_ID         (0U)

/*Define HOH for Can module */
#define HTH0_0                                   (0U)
#define HRH0_0                                   (1U)
#define HTH0_1                                   (2U)
#define HRH0_1                                   (3U)


// ECUC_Can_00317
#define POLLING 2
#define INTERRUPT 0

#define CAN_polling_timout 300

#define CanRxProcessing     MIXED_PROCESSING

#define CanTxProcessing     MIXED_PROCESSING

#define CAN_HWOBJECT_COUNT 12

#define CanBusoffProcessing POLLING

#define CanDevErrorDetect   STD_ON

#define CanSetBaudrateApi   STD_ON

#define INTERRUPT_MODE 		(0x00)

#define CanTriggerTransmitEnable    FALSE




#define CanControllerActivation


#define CAN0_ID				(0u)
#define CAN1_ID				(1u)

/* Module Version 1.0.0 */
#define CAN_CFG_SW_MAJOR_VERSION           (1U)
#define CAN_CFG_SW_MINOR_VERSION           (0U)
#define CAN_CFG_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CAN_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define CAN_CFG_AR_RELEASE_MINOR_VERSION   (3U)
#define CAN_CFG_AR_RELEASE_PATCH_VERSION   (1U)

/*Non-Autosar file*/
#include "tm4c123gh6pm.h"

#include "Std_Types.h"
/* AUTOSAR checking between Std Types and Can_Cfg Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CAN_CFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CAN_CFG_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CAN_CFG_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


/* Specifies the InstanceId of this module instance. If only one instance is
present it shall have the Id 0.*/
#define CAN_INDEX  								(uint8)(0U)

/* Specifies if multiplexed transmission shall be supported.ON or OFF */
#define CAN_MULTIPLEXED_TRANSMISSION 			STD_OFF

/* Selects support of Pretended Network features in Can driver. */
#define CAN_PUBLIC_ICOM_SUPPORT 				STD_OFF


#define INTERRUPT_PROCESSING 0U   /* Interrupt Mode of operation*/
#define MIXED_PROCESSING     1U   /* Mixed Mode of operation  */
#define POLLING_PROCESSING   2U   /* Polling Mode of operation*/

#define CAN_CONTROLLER_0_ACTIVATION STD_ON
#define CAN_CONTROLLER_1_ACTIVATION STD_ON

/*Specifies the type (Full-CAN or Basic-CAN) of a hardware object*/
#define CAN_HANDLE_TYPE BASIC_CAN

#define BASIC_CAN  0U /* For several L-PDUs are hadled by the hardware object */
#define FULL_CAN 1U /* For only one L-PDU (identifier) is handled by the hardware object */

/* Specifies whether the IdValue is of type
- standard identifier
- extended identifier
- mixed mode
ImplementationType: Can_IdType*/
#define CAN_ID_TYPE STANDARD_CAN

#define EXTENDED_CAN  0U /* All the CANIDs are of type extended only(29 bit).*/
#define MIXED_CAN     1U /* The type of CANIDs can be both Standard or Extended.*/
#define STANDARD_CAN  2U /* All the CANIDs are of type standard only(11bit).*/

/*Holds the handle ID of HRH or HTH. The value of this parameter is unique
in a given CAN Driver, and it should start with 0 and continue without any
gaps.
The HRH and HTH Ids share a common ID range.
Example: HRH0-0, HRH1-1, HTH0-2, HTH1-3*/
#define CAN_OBJ_ID 0U

/* This parameter defines if or if not Can supports the trigger-transmit API for this handle*/
#define CAN_TRIGGER_TRANSMIT_ENABLE STD_OFF

#define MAX_NO_OF_OBJECTS 			(65u)
#define NO_OF_CONTROLLERS_IN_HW 	(2u)

#define CAN_INITIALIZED 			(1u)
#define CAN_NOT_INITIALIZED 			(0u)

#define NUM_OF_CAN_CONTROLLERS 2U
#define CONTROLLER_0_ID 0U
#define CONTROLLER_1_ID 1U





#define MAX_HW_OBJ_COUNT_PER_HOH 1U

#define MSG_OBJ_0_ID 1U
#define MSG_OBJ_1_ID 2U

#define PDU_0_ID 13U
#define PDU_1_ID 23U

#define NUM_OF_MAIN_RW_PERSIODS 2U
#define PERIOD_0 (float32) 0.001
#define PERIOD_1 (float32) 0.005

#define  DEVLOPEMENT_ERROR      STD_OFF
#define  CanTimeoutDuration     0.5

#endif /* CAN_CFG_H_ */
