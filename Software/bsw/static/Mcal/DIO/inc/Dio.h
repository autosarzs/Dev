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
**  FILENAME     : Dio.h                                                      **
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
**  DESCRIPTION  : DIO Driver header file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of DIO Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

/*******************************************************************************/
/*                              Include headers                                */
/*******************************************************************************/

#include "Std_Types.h"
#include "Port.h"
#include "Dio_Cfg.h"
#include "BitHelper.h"

/*******************************************************************************/
/*                              Macro Definition                               */
/*******************************************************************************/

#define DIO_MODULE_ID (120)
#define DIO_INSTANCE_ID (0)

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (3U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (1U)


/* Service ID for DIO read Channel */
#define DIO_READ_CHANNEL_SID (uint8)0x00

/* Service ID for DIO write Channel */
#define DIO_WRITE_CHANNEL_SID (uint8)0x01

/* Service ID for DIO read Port */
#define DIO_READ_PORT_SID (uint8)0x02

/* Service ID for DIO write Port */
#define DIO_WRITE_PORT_SID (uint8)0x03

/* Service ID for DIO read Channel Group */
#define DIO_READ_CHANNEL_GROUP_SID (uint8)0x04

/* Service ID for DIO write Channel Group */
#define DIO_WRITE_CHANNEL_GROUP_SID (uint8)0x05

/* Service ID for DIO GetVersionInfo */
#define DIO_GET_VERSION_INFO_SID (uint8)0x12

/* Service ID for DIO Init Channel */
#define DIO_INIT_SID (uint8)0x10

/* Service ID for DIO flip Channel */
#define DIO_FLIP_CHANNEL_SID (uint8)0x11

#define NULL_PTR ((void *)0)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* type Dio_ChannelType contain the numeric ID of a DIO channel */
typedef uint8 Dio_ChannelType;

/* type for the definition of a channel group, which consists of several adjoining channels within a port */
typedef uint8 Dio_PortType;

/* type for the possible levels that a DIO channel can have (input or output) */
typedef uint8 Dio_LevelType;

/* Type for Dio_PortLevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;

/*Dio Direction Type*/
typedef uint8 Dio_DirectionType;

/*DIO ID Number*/
typedef uint8 Dio_IdType;

/* Type for the definition of a channel group, which consists of several adjoining channels within a port*/
typedef struct
{
  /* This element mask which defines the positions of the channel group */
  uint8 mask;
  /* This element shall be the position of the Channel Group on the port,
     counted from the LSB */
  uint8 offset;
  /* This shall be the port on which the Channel group is defined */
  Dio_PortType port;
} Dio_ChannelGroupType;

/* Type for defining Pin Mode*/
typedef enum
{
  OUTPUT = (uint8)0U,
  INPUT = (uint8)1U
} Dio_PinMode;

typedef enum
{
  /*PORTA Channels*/
  CHANNEL_0,
  CHANNEL_1,
  CHANNEL_2,
  CHANNEL_3,
  CHANNEL_4,
  CHANNEL_5,
  CHANNEL_6,
  CHANNEL_7,
  /*PORTB Channels*/
  CHANNEL_8,
  CHANNEL_9,
  CHANNEL_10,
  CHANNEL_11,
  CHANNEL_12,
  CHANNEL_13,
  CHANNEL_14,
  CHANNEL_15,
  /*PORTC Channels*/
  CHANNEL_16,
  CHANNEL_17,
  CHANNEL_18,
  CHANNEL_19,
  CHANNEL_20,
  CHANNEL_21,
  CHANNEL_22,
  CHANNEL_23,
  /*PORTD Channels*/
  CHANNEL_24,
  CHANNEL_25,
  CHANNEL_26,
  CHANNEL_27,
  CHANNEL_28,
  CHANNEL_29,
  CHANNEL_30,
  CHANNEL_31,
  /*PORTE Channels*/
  CHANNEL_32,
  CHANNEL_33,
  CHANNEL_34,
  CHANNEL_35,
  CHANNEL_36,
  CHANNEL_37,
  /*PORTF Channels*/
  CHANNEL_38,
  CHANNEL_39,
  CHANNEL_40,
  CHANNEL_41,
  CHANNEL_42,
  CHANNEL_43,
} Dio_AvailableChannels;


/*Struct To Represent channel configuration*/
typedef struct
{
  /*Defines ID Of Channel*/
  Dio_AvailableChannels Channel_ID;
  /*Defines Which Port*/
  Port_AvailablePorts Port;
  /*Which pin in port*/
  Dio_ChannelType Channel;
  /*input or Output*/
  Dio_PinMode Dir;
} Dio_ConfiguredChannel;

typedef enum
{
  DIO_E_PARAM_INVALID_CHANNEL_ID = 0x0A, /* User  passed invalid channel ID */
  DIO_E_PARAM_INVALID_PORT_ID = 0x14,    /* User  passed invalid Port ID */
  DIO_E_PARAM_INVALID_GROUP = 0x1F,      /* User  passed invalid group of channels */
  DIO_E_PARAM_POINTER = 0x20,            /* User passed Null Pointer */
} DIO_DetErrors;

/*******************************************************************************
 *                            Function Prototypes                              *
 *******************************************************************************/

/**
 * @brief Reads the level of the specified DIO channel.
 *
 * This function reads the current level of the specified DIO channel.
 *
 * @param ChannelId The ID of the DIO channel to read.
 * @return The level of the specified DIO channel (STD_LOW or STD_HIGH).
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

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
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/**
 * @brief Reads the level of all channels in the specified DIO port.
 *
 * This function reads the current levels of all channels in the specified DIO port.
 *
 * @param PortId The ID of the DIO port to read.
 * @return The level of all channels in the specified DIO port.
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

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
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/**
 * @brief Reads the levels of channels in the specified channel group.
 *
 * This function reads the current levels of channels specified by the given channel group.
 *
 * @param ChannelGroupIdPtr Pointer to the structure containing information about the channel group.
 * @return The levels of channels in the specified channel group.
 */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr);

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
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level);

/**
 * @brief Toggles the level of the specified DIO channel.
 *
 * This function toggles the level of the specified DIO channel.
 *
 * @param ChannelId The ID of the DIO channel to toggle.
 * @return The new level of the specified DIO channel (STD_LOW or STD_HIGH).
 */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

/**
 * @brief Retrieves version information of the Dio module.
 *
 * This function retrieves version information of the Dio module and stores it
 * in the provided structure.
 *
 * @param VersionInfo Pointer to the structure to store version information.
 * @return None.
 */
void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo);

#endif /* DIO_H_ */
