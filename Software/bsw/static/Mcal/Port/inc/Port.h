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
  PORT_PIN_MODE_ALT1,
  PORT_PIN_MODE_ALT2,
  PORT_PIN_MODE_ALT3,
  PORT_PIN_MODE_ALT4,
  PORT_PIN_MODE_ALT5,
  PORT_PIN_MODE_ALT6,
  PORT_PIN_MODE_ALT7,
  PORT_PIN_MODE_ALT8,
  PORT_PIN_MODE_ALT9,
  PORT_PIN_MODE_DIO,
} Port_PinInitialMode;

typedef struct
{
  uint8 port_num;                   /* PortA, PortB, PortC, .. */
  uint8 pin_num;                    /* PA0, PA1, ... , PF3, PF4 */
  Port_PinDirectionType direction;  /* PORT_PIN_IN, PORT_PIN_OUT */
  Port_InternalResistor resistor;   /* OFF,PULL_UP,PULL_DOWN */
  Port_PinLevelValue initial_value; /* PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH */
  Port_PinInitialMode initial_mode; /* e.g. PORT_PIN_MODE_DIO */
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
} DIO_DetErrors;

#endif /* PORT_H_ */
