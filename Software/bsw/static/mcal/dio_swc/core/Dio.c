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
**  FILENAME     : Dio.c                                                      **
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
**  DESCRIPTION  : DIO Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of DIO Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

#include "Dio.h"
#include "Port_MemMap.h"
#include "SchM_Dio.h"
#ifdef DIO_DEV_ERROR_DETECT
#include "Det.h"
#endif

/*******************************************************************************/
/*                       global variables                                      */
/*******************************************************************************/

/*Extern Channel Array Of Structure*/
extern Dio_ConfiguredChannel channels[DIO_CONFIGURED_CHANNLES];

/* will be defined in Port driver */
extern volatile Port_Type *portBaseAddresses[];
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
/*                       Module Interfaces                                     */
/*******************************************************************************/

/**
 * @brief Reads the level of the specified DIO channel.
 *
 * This function reads the current level of the specified DIO channel.
 *
 * @param ChannelId The ID of the DIO channel to read.
 * @return The level of the specified DIO channel (STD_LOW or STD_HIGH).
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
  Dio_LevelType Pin_Level = STD_OFF;

  if (ChannelId <= 0 || ChannelId >= DIO_CONFIGURED_CHANNLES)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_CHANNEL_SID,
                    DIO_E_PARAM_INVALID_CHANNEL_ID);
#endif
  }
  else
  {
    Port_AvailablePorts PortId = channels[ChannelId].Port;
    const volatile Port_Type *portBase = getPortBaseAddress(PortId);
    if (portBase == NULL)
    {
      /* Do Nothing */
    }
    else
    {
      Pin_Level = GET_BIT(portBase->DATA, channels[ChannelId].Channel);
    }
  }
  return Pin_Level;
}

/**
 * @brief Writes the specified level to the specified DIO channel.
 *
 * This function sets the level of the specified DIO channel to the
 * specified value.
 *
 * @param ChannelId The ID of the DIO channel to write to.
 * @param Level The level to set the DIO channel to (STD_LOW or STD_HIGH).
 * @return None.
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  if (ChannelId <= 0 || ChannelId >= DIO_CONFIGURED_CHANNLES)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_WRITE_CHANNEL_SID,
                    DIO_E_PARAM_INVALID_CHANNEL_ID);
#endif
  }
  else
  {
    Port_AvailablePorts PortId = channels[ChannelId].Port;
    volatile Port_Type *portBase = getPortBaseAddress(PortId);
    if (portBase == NULL)
    {
      /* Do Nothing */
    }
    else
    {
      if (channels[ChannelId].Dir != OUTPUT)
      {
        /* Do Nothing */
      }
      else
      {
        if (Level == STD_HIGH)
        {
          SET_BIT(portBase->DATA, channels[ChannelId].Channel);
        }
        /*Set Bit STD_LOW*/
        else
        {
          CLR_BIT(portBase->DATA, channels[ChannelId].Channel);
        }
      }
    }
  }
}

/**
 * @brief Reads the level of all channels in the specified DIO port.
 *
 * This function reads the current levels of all channels in the specified DIO port.
 *
 * @param PortId The ID of the DIO port to read.
 * @return The level of all channels in the specified DIO port.
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
  Dio_PortLevelType portData = 0;

  if (PortId >= PORTA_ID && PortId <= PORTF_ID)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_PORT_SID,
                    DIO_E_PARAM_INVALID_PORT_ID);
#endif
  }
  else
  {
    const volatile Port_Type *portBase = getPortBaseAddress(PortId);
    portData = portBase->DATA;
  }

  return portData;
}

/**
 * @brief Writes the specified levels to all channels in the specified DIO port.
 *
 * This function sets the levels of all channels in the specified DIO port to the
 * specified values.
 *
 * @param PortId The ID of the DIO port to write to.
 * @param Level The levels to set the channels in the DIO port to.
 * @return None.
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
  if (PortId >= PORTA_ID && PortId <= PORTF_ID)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_PORT_SID,
                    DIO_E_PARAM_INVALID_PORT_ID);
#endif
  }
  else
  {
    volatile Port_Type *portBase = getPortBaseAddress(PortId);
    portBase->DATA = Level;
  }
}

/**
 * @brief Reads the levels of channels in the specified channel group.
 *
 * This function reads the current levels of channels specified by the given channel group.
 *
 * @param ChannelGroupIdPtr Pointer to the structure containing information about the channel group.
 * @return The levels of channels in the specified channel group.
 */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
  Dio_PortLevelType maskedData = 0;

  // Check if the pointer is valid
  if (ChannelGroupIdPtr == NULL)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_CHANNEL_GROUP_SID,
                    DIO_E_PARAM_POINTER);
#endif
  }
  else if (ChannelGroupIdPtr->port >= PORTA_ID && ChannelGroupIdPtr->port <= PORTF_ID)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_CHANNEL_GROUP_SID,
                    DIO_E_PARAM_INVALID_GROUP);
#endif
  }
  else
  {
    // Read the value from the port
    Dio_PortLevelType portData = Dio_ReadPort(ChannelGroupIdPtr->port);

    // Mask the channel group
    maskedData = (portData >> ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask;
  }

  return maskedData;
}

/**
 * @brief Writes the specified levels to channels in the specified channel group.
 *
 * This function sets the levels of channels specified by the given channel group to the
 * specified values.
 *
 * @param ChannelGroupIdPtr Pointer to the structure containing information about the channel group.
 * @param Level The levels to set the channels in the channel group to.
 * @return None.
 */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level)
{
  // Check if the pointer is valid
  if (ChannelGroupIdPtr == NULL)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_CHANNEL_GROUP_SID,
                    DIO_E_PARAM_POINTER);
#endif
  }
  else if (ChannelGroupIdPtr->port >= PORTA_ID && ChannelGroupIdPtr->port <= PORTF_ID)
  {
#ifdef DIO_DEV_ERROR_DETECT
    Det_ReportError(DIO_MODULE_ID,
                    DIO_INSTANCE_ID,
                    DIO_READ_CHANNEL_GROUP_SID,
                    DIO_E_PARAM_INVALID_GROUP);
#endif
  }
  else
  {
    // Get the base address of the port
    volatile Port_Type *portBase = getPortBaseAddress(ChannelGroupIdPtr->port);

    // Perform masking and shifting to align with LSB
    Dio_PortLevelType maskedData = (Level >> ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask;

    // Write the masked data to the port
    portBase->DATA = maskedData;
  }
}

/**
 * @brief Toggles the level of the specified DIO channel.
 *
 * This function toggles the level of the specified DIO channel.
 *
 * @param ChannelId The ID of the DIO channel to toggle.
 * @return The new level of the specified DIO channel (STD_LOW or STD_HIGH).
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
  // Read the current level of the channel
  Dio_LevelType currentLevel = Dio_ReadChannel(ChannelId);

  // Variable to hold the level to be returned
  Dio_LevelType levelToReturn;

  // Check if the channel is configured as an output channel
  if (channels[ChannelId].Dir == OUTPUT)
  {
    // Invert the level
    Dio_LevelType newLevel = (currentLevel == STD_LOW) ? STD_HIGH : STD_LOW;

    // Write the inverted level to the channel
    Dio_WriteChannel(ChannelId, newLevel);

    // Assign the inverted level to the variable
    levelToReturn = newLevel;
  }
  else
  {
    // If the channel is configured as an input channel, assign the current level to the variable
    levelToReturn = currentLevel;
  }

  // Return the level
  return levelToReturn;
}

/**
 * @brief Retrieves version information of the Dio module.
 *
 * This function retrieves version information of the Dio module and stores it
 * in the provided structure.
 *
 * @param VersionInfo Pointer to the structure to store version information.
 * @return None.
 */
void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{
  // Check if DET is enabled and if VersionInfo pointer is NULL
#ifdef DIO_DEV_ERROR_DETECT
  if (VersionInfo == NULL)
  {
    // Report error and return without any action
    Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
    return;
  }
#endif

  // Fill the VersionInfo structure with module version information
  VersionInfo->vendorID = 0;
  VersionInfo->moduleID = DIO_MODULE_ID;
  VersionInfo->instanceID = DIO_INSTANCE_ID;
  VersionInfo->sw_major_version = DIO_CFG_SW_MAJOR_VERSION;
  VersionInfo->sw_minor_version = DIO_CFG_SW_MINOR_VERSION;
  VersionInfo->sw_patch_version = DIO_CFG_SW_PATCH_VERSION;
  VersionInfo->ar_major_version = DIO_CFG_AR_RELEASE_MAJOR_VERSION;
  VersionInfo->ar_minor_version = DIO_CFG_AR_RELEASE_MINOR_VERSION;
  VersionInfo->ar_patch_version = DIO_CFG_AR_RELEASE_PATCH_VERSION;
}
