/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)                                        **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Port.h                                                     **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2024-04-17                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C                                                     **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam                                          **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC                                              **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : Port Driver header file                                    **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.3.1    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

#include "Std_Types.h"
#include "Port_Cfg.h"
#include "BitHelper.h"
#include "tm4c123gh6pm.h"

/*******************************************************************************/
/*                              Macro Definition                               */
/*******************************************************************************/

#define PORT_MODULE_ID (124U)
#define PORT_INSTANCE_ID (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION (1U)
#define PORT_SW_MINOR_VERSION (0U)
#define PORT_SW_PATCH_VERSION (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_AR_RELEASE_MINOR_VERSION (3U)
#define PORT_AR_RELEASE_PATCH_VERSION (1U)

#define PORT_INIT_SID (uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIR_SID (uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIR_SID (uint8)0x02

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID (uint8)0x03

/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID (uint8)0x04

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED (1U)
#define PORT_NOT_INITIALIZED (0U)

#define NULL_PTR ((void *)0)

/*******************************************************************************
 *                              Module Data Types                              *
********************************************************************************/

/* Description: Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Description: Different port pin modes */
typedef uint8 Port_PinModeType;

/* Description: Possible directions of a port pin */
typedef enum
{
  PORT_PIN_IN,
  PORT_PIN_OUT
} Port_PinDirectionType;

typedef enum
{
  PORT_PIN_LEVEL_LOW,
  PORT_PIN_LEVEL_HIGH
} Port_PinLevelValue;

typedef enum
{
  OFF,
  PULL_UP,
  PULL_DOWN
} Port_InternalResistor;

typedef enum
{
  PORT_PIN_MODE_ADC,
  PORT_PIN_MODE_DIO,
} Port_PinInitialMode;

/*Defines Available Ports*/
typedef enum
{
  PORTA_ID = 0,
  PORTB_ID,
  PORTC_ID,
  PORTD_ID,
  PORTE_ID,
  PORTF_ID
} Port_AvailablePorts;

/*Defines Available Pins*/
typedef enum
{
  PA0 = (0U),
  PA1 = (1U),
  PA2 = (2U),
  PA3 = (3U),
  PA4 = (4U),
  PA5 = (5U),
  PA6 = (6U),
  PA7 = (7U),
  PB0 = (0U),
  PB1 = (1U),
  PB2 = (2U),
  PB3 = (3U),
  PB4 = (4U),
  PB5 = (5U),
  PB6 = (6U),
  PB7 = (7U),
  PC0 = (0U),
  PC1 = (1U),
  PC2 = (2U),
  PC3 = (3U),
  PC4 = (4U),
  PC5 = (5U),
  PC6 = (6U),
  PC7 = (7U),
  PD0 = (0U),
  PD1 = (1U),
  PD2 = (2U),
  PD3 = (3U),
  PD4 = (4U),
  PD5 = (5U),
  PD6 = (6U),
  PD7 = (7U),
  PE0 = (0U),
  PE1 = (1U),
  PE2 = (2U),
  PE3 = (3U),
  PE4 = (4U),
  PE5 = (5U),
  PE6 = (6U),
  PE7 = (7U),
  PF0 = (0U),
  PF1 = (1U),
  PF2 = (2U),
  PF3 = (3U),
  PF4 = (4U),
  PF5 = (5U),
  PF6 = (6U),
  PF7 = (7U),
} Port_AvailablePins;

typedef struct
{
  Port_AvailablePorts port_num;     /* PortA, PortB, PortC, .. */
  Port_AvailablePins pin_num;       /* PA0, PA1, ... , PF3, PF4 */
  Port_PinDirectionType direction;  /* PORT_PIN_IN, PORT_PIN_OUT */
  Port_InternalResistor resistor;   /* OFF,PULL_UP,PULL_DOWN */
  Port_PinLevelValue initial_value; /* PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH */
  Port_PinInitialMode initial_mode; /* e.g. PORT_PIN_MODE_DIO */
  uint8 pin_configure;              /* STD_ON,STD_OFF */
  uint8 pin_unlock;                 /* STD_ON,STD_OFF */
  uint8 pin_dir_changeable;         /* STD_ON,STD_OFF */
  uint8 pin_mode_changeable;        /* STD_ON,STD_OFF */
} Port_ConfigPin;

/* Array of Port_ConfigPin */
typedef struct
{
  Port_ConfigPin Pin[PORT_CONFIGURED_PINS];
} Port_ConfigType;

typedef enum
{
  PORT_E_PARAM_PIN = 0x0A,              /* Invalid Port Pin ID requested */
  PORT_E_DIRECTION_UNCHANGEABLE = 0x0B, /* Port Pin not configured as changeable */
  PORT_E_INIT_FAILED = 0x0C,            /* API Port_Init service called with wrong parameter */
  PORT_E_PARAM_INVALID_MODE = 0x0D,     /* API Port_SetPinMode service called when mode is unchangeable */
  PORT_E_MODE_UNCHANGEABLE = 0x0E,      /* API Port_SetPinMode service called when mode is unchangeable */
  PORT_E_UNINIT = 0x0F,                 /* API service called without module initialization*/
  PORT_E_PARAM_POINTER = 0x10,          /*APIs called with a Null Pointer*/
} Port_DetErrors;



/*******************************************************************************
 *                             Global Variables                                *
********************************************************************************/

// extern volatile Port_Type *portBaseAddresses[];

/*******************************************************************************
 *                            Function Prototypes                              *
********************************************************************************/

/**
 * @brief Initializes the specified port with the given configuration.
 *
 * This function initializes the specified port according to the provided configuration.
 *
 * @param ConfigPtr Pointer to the configuration structure for port initialization.
 */
void Port_Init(const Port_ConfigType *ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/**
 * @brief Sets the direction of the specified pin within a port.
 *
 * This function sets the direction (input or output) of the specified pin within a port.
 *
 * @param Pin The pin number to set the direction for.
 * @param Direction The direction to set for the pin (PORT_PIN_IN or PORT_PIN_OUT).
 */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/**
 * @brief Refreshes the direction of all pins within a port.
 *
 * This function refreshes the direction (input or output) of all pins within a port based on the current configuration.
 */
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/**
 * @brief Retrieves the version information of the Port module.
 *
 * This function retrieves the version information of the Port module if the version information API is enabled.
 *
 * @param versioninfo Pointer to a structure where the version information will be stored.
 */
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/**
 * @brief Sets the mode of operation for the specified pin within a port.
 *
 * This function sets the mode of operation for the specified pin within a port if the set pin mode API is enabled.
 *
 * @param Pin The pin number to set the mode for.
 * @param Mode The mode to set for the pin.
 */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#endif /* PORT_H_ */
