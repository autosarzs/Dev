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
**  FILENAME     : Dio_Cfg.h                                                  **
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
**  DESCRIPTION  : DIO Driver config header file                              **
**                                                                            **
**  SPECIFICATION(S) : Specification of DIO Driver, AUTOSAR Release 4.3.1     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (2U)

#endif /* DIO_CFG_H_ */



