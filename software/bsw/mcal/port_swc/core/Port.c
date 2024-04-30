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
**  FILENAME     : Port.c                                                     **
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
**  VENDOR       : AUTOSarZs OL                                               **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : Port Driver source file                                    **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.3.1    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

#include "Port.h"
#include "Port_MemMap.h"
#include "SchM_Port.h"

#ifdef PORT_DEV_ERROR_DETECT
#include "Det.h"
#endif

/* Optional */
#include "Port_Cbkh.h"

/*******************************************************************************/
/*                              Global variables                               */
/*******************************************************************************/

static uint8 Port_Status = PORT_NOT_INITIALIZED;

/* Holds the pointer of the Port_PinConfig */
static const Port_ConfigType *Port_ConfigPtr = NULL_PTR;

/* Define the base addresses of the ports */
volatile Port_Type *portBaseAddresses[] = {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF};

/*******************************************************************************/
/*                       Static Functions                                      */
/*******************************************************************************/

/**
 * @brief Retrieves the base address of a port.
 *
 * This function retrieves the base address of the port corresponding to the given port ID.
 *
 * @param PortId The ID of the port.
 * @return The base address of the port, or NULL if the port ID is invalid.
 */
inline volatile Port_Type *getPortBaseAddress(Port_AvailablePorts PortId)
{
  if (PortId >= PORTA_ID && PortId <= PORTF_ID)
  {
    return portBaseAddresses[PortId];
  }
  else
  {
    // Handle invalid port ID (optional)
    return NULL;
  }
}

/*******************************************************************************/
/*                              Module Interfaces                              */
/*******************************************************************************/

void Port_Init(const Port_ConfigType *ConfigPtr)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* check if the input configuration pointer is not a NULL_PTR */
  if (ConfigPtr == NULL_PTR)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_INIT_SID,
                    PORT_E_PARAM_POINTER);
  }
  else
  {
    /* Do Nothing */
  }
#endif

  Port_ConfigPtr = ConfigPtr;

  for (Port_PinType index = 0; index < PORT_CONFIGURED_PINS; index++)
  {
    volatile Port_Type *portBase = getPortBaseAddress(Port_ConfigPtr->Pin[index].port_num);

    /* Enable clock for PORT and allow time for clock to start*/
    SET_BIT(SYSCTL_REGCGC2_REG, Port_ConfigPtr->Pin[index].port_num);

    /*Todo: Introduce system delay at least of 3 system clocks*/

    /* if pin needed to be configured (avoiding configuring pins like JTAG)*/
    if (Port_ConfigPtr->Pin[index].pin_configure)
    {
      /*If GPIO requires unlock, please refer to datasheet register GPIOCR */
      if (Port_ConfigPtr->Pin[index].pin_unlock)
      {
        /* Unlock the GPIOCR register */
        portBase->LOCK = GPIO_LOCK_KEY;

        /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        SET_BIT(portBase->LOCK, Port_ConfigPtr->Pin[index].pin_num);
      }

      if (Port_ConfigPtr->Pin[index].initial_mode == PORT_PIN_MODE_DIO)
      {
        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLR_BIT(portBase->AMSEL, Port_ConfigPtr->Pin[index].pin_num);

        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        CLR_BIT(portBase->AFSEL, Port_ConfigPtr->Pin[index].pin_num);

        /* Clear the PMCx bits for this pin, each 4 bits represnet one GPIO */
        CLR_BITS(portBase->PCTL, Port_ConfigPtr->Pin[index].pin_num * 4, 0x0000000F);

        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        SET_BIT(portBase->DEN, Port_ConfigPtr->Pin[index].pin_num);
      }
      else if (Port_ConfigPtr->Pin[index].initial_mode == PORT_PIN_MODE_ADC)
      {
        /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
        CLR_BIT(portBase->DEN, Port_ConfigPtr->Pin[index].pin_num);

        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        CLR_BIT(portBase->AFSEL, Port_ConfigPtr->Pin[index].pin_num);

        /* Clear the PMCx bits for this pin, each 4 bits represnet one GPIO */
        CLR_BITS(portBase->PCTL, Port_ConfigPtr->Pin[index].pin_num * 4, 0x0000000F);

        /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
        SET_BIT(portBase->AMSEL, Port_ConfigPtr->Pin[index].pin_num);
      }
      else /* Another mode */
      {
        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        SET_BIT(portBase->DEN, Port_ConfigPtr->Pin[index].pin_num);

        /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        SET_BIT(portBase->AFSEL, Port_ConfigPtr->Pin[index].pin_num);

        /* Set the PMCx bits for this pin */
        SET_BITS(portBase->PCTL, Port_ConfigPtr->Pin[index].pin_num * 4, 0x0000000F);

        /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
        CLR_BIT(portBase->AMSEL, Port_ConfigPtr->Pin[index].pin_num);
      }

      if (Port_ConfigPtr->Pin[index].direction == PORT_PIN_OUT)
      {
        /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        SET_BIT(portBase->DIR, Port_ConfigPtr->Pin[index].pin_num);

        if (Port_ConfigPtr->Pin[index].initial_value == PORT_PIN_LEVEL_HIGH)
        {
          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
          SET_BIT(portBase->DATA, Port_ConfigPtr->Pin[index].pin_num);
        }
        else
        {
          /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
          CLR_BIT(portBase->DATA, Port_ConfigPtr->Pin[index].pin_num);
        }
      }
      else if (Port_ConfigPtr->Pin[index].direction == PORT_PIN_IN)
      {
        /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        CLR_BIT(portBase->DIR, Port_ConfigPtr->Pin[index].pin_num);

        if (Port_ConfigPtr->Pin[index].resistor == PULL_UP)
        {
          /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
          SET_BIT(portBase->PUR, Port_ConfigPtr->Pin[index].pin_num);
        }
        else if (Port_ConfigPtr->Pin[index].resistor == PULL_DOWN)
        {
          /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
          SET_BIT(portBase->PDR, Port_ConfigPtr->Pin[index].pin_num);
        }
        else
        {
          /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
          CLR_BIT(portBase->PUR, Port_ConfigPtr->Pin[index].pin_num);

          /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
          CLR_BIT(portBase->PDR, Port_ConfigPtr->Pin[index].pin_num);
        }
      }
      else
      {
        /* Do Nothing */
      }
    }
  }
  Port_Status = PORT_INITIALIZED;
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
  if (Port_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_DIR_SID,
                    PORT_E_UNINIT);
  }
  else
  {
    /* Do Nothing */
  }

  /* check if incorrect Port Pin ID passed */
  if (Pin >= PORT_CONFIGURED_PINS)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_DIR_SID,
                    PORT_E_PARAM_PIN);
  }
  else
  {
    /* Do Nothing */
  }

  /* check if Port Pin not configured as changeable */
  if (Port_ConfigPtr->Pin[Pin].pin_dir_changeable == STD_OFF)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_DIR_SID,
                    PORT_E_DIRECTION_UNCHANGEABLE);
  }
  else
  {
    /* Do Nothing */
  }
#endif

  volatile Port_Type *portBase = getPortBaseAddress(Port_ConfigPtr->Pin[Pin].port_num);

  /* if pin needed to be configured (avoiding configuring pins like JTAG)*/
  if (Port_ConfigPtr->Pin[Pin].pin_configure)
  {
    if (Direction == PORT_PIN_OUT)
    {
      /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
      SET_BIT(portBase->DIR, Port_ConfigPtr->Pin[Pin].pin_num);
    }
    else if (Direction == PORT_PIN_IN)
    {
      /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
      CLR_BIT(portBase->DIR, Port_ConfigPtr->Pin[Pin].pin_num);
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
#endif

void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
  if (Port_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_REFRESH_PORT_DIR_SID,
                    PORT_E_UNINIT);
  }
  else
  {
    /* Do Nothing */
  }
#endif

  for (Port_PinType index = 0; index < PORT_CONFIGURED_PINS; index++)
  {
    volatile Port_Type *portBase = getPortBaseAddress(Port_ConfigPtr->Pin[index].port_num);

    if (Port_ConfigPtr->Pin[index].pin_configure)
    {
      if (Port_ConfigPtr->Pin[index].pin_dir_changeable == STD_OFF)
      {
        if (Port_ConfigPtr->Pin[index].direction == PORT_PIN_OUT)
        {
          /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
          SET_BIT(portBase->DIR, Port_ConfigPtr->Pin[index].pin_num);
        }
        else if (Port_ConfigPtr->Pin[index].direction == PORT_PIN_IN)
        {
          /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
          CLR_BIT(portBase->DIR, Port_ConfigPtr->Pin[index].pin_num);
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
    else
    {
      /* Do Nothing */
    }
  }
}

#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
  if (Port_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_UNINIT);
  }
  else
  {
    /* Do Nothing */
  }

  /* check if incorrect Port Pin ID passed */
  if (Pin >= PORT_CONFIGURED_PINS)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_PARAM_PIN);
  }
  else
  {
    /* Do Nothing */
  }

  /* check if the Port Pin Mode passed not valid */
  if (Mode > PORT_PIN_MODE_DIO)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_PARAM_INVALID_MODE);
  }
  else
  {
    /* Do Nothing */
  }

  /* check if the API called when the mode is unchangeable */
  if (Port_ConfigPtr->Pin[Pin].pin_mode_changeable == STD_OFF)
  {
    Det_ReportError(PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_MODE_UNCHANGEABLE);
  }
  else
  {
  }
#endif

  volatile Port_Type *portBase = getPortBaseAddress(Port_ConfigPtr->Pin[Pin].port_num);

  if (Port_ConfigPtr->Pin[Pin].pin_configure)
  {
    if (Mode == PORT_PIN_MODE_DIO)
    {
      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      CLR_BIT(portBase->AMSEL, Port_ConfigPtr->Pin[Pin].pin_num);

      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      CLR_BIT(portBase->AFSEL, Port_ConfigPtr->Pin[Pin].pin_num);

      /* Clear the PMCx bits for this pin, each 4 bits represnet one GPIO */
      CLR_BITS(portBase->PCTL, Port_ConfigPtr->Pin[Pin].pin_num * 4, 0x0000000F);

      /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      SET_BIT(portBase->DEN, Port_ConfigPtr->Pin[Pin].pin_num);
    }
    else if (Mode == PORT_PIN_MODE_ADC)
    {
      /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
      CLR_BIT(portBase->DEN, Port_ConfigPtr->Pin[Pin].pin_num);

      /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      CLR_BIT(portBase->AFSEL, Port_ConfigPtr->Pin[Pin].pin_num);

      /* Clear the PMCx bits for this pin, each 4 bits represnet one GPIO */
      CLR_BITS(portBase->PCTL, Port_ConfigPtr->Pin[Pin].pin_num * 4, 0x0000000F);

      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
      SET_BIT(portBase->AMSEL, Port_ConfigPtr->Pin[Pin].pin_num);
    }
    else /* Another mode */
    {
      /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      SET_BIT(portBase->DEN, Port_ConfigPtr->Pin[Pin].pin_num);

      /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      SET_BIT(portBase->AFSEL, Port_ConfigPtr->Pin[Pin].pin_num);

      /* Set the PMCx bits for this pin */
      SET_BITS(portBase->PCTL, Port_ConfigPtr->Pin[Pin].pin_num * 4, 0x0000000F);

      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
      CLR_BIT(portBase->AMSEL, Port_ConfigPtr->Pin[Pin].pin_num);
    }
  }
  else
  {
    /* Do Nothing */
  }
}
#endif

void PORT_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{
  // Check if DET is enabled and if VersionInfo pointer is NULL
#ifdef PORT_DEV_ERROR_DETECT
  if (VersionInfo == NULL)
  {
    // Report error and return without any action
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    return;
  }
#endif

  // Fill the VersionInfo structure with module version information
  VersionInfo->vendorID = 0;
  VersionInfo->moduleID = PORT_MODULE_ID;
  VersionInfo->instanceID = PORT_INSTANCE_ID;
  VersionInfo->sw_major_version = PORT_CFG_SW_MAJOR_VERSION;
  VersionInfo->sw_minor_version = PORT_CFG_SW_MINOR_VERSION;
  VersionInfo->sw_patch_version = PORT_CFG_SW_PATCH_VERSION;
  VersionInfo->ar_major_version = PORT_CFG_AR_RELEASE_MAJOR_VERSION;
  VersionInfo->ar_minor_version = PORT_CFG_AR_RELEASE_MINOR_VERSION;
  VersionInfo->ar_patch_version = PORT_CFG_AR_RELEASE_PATCH_VERSION;
}
