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
**  FILENAME     : BitHelper.h     			                                  **
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
#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define BITBAND_BASE 0x42000000
#define SET_BIT(x,i) x|=(1<<(i))
#define CLR_BIT(x,i) x&=~(1<<(i))
#define TOGGLE_BIT(x,i) x^=(1<<(i))
#define GET_BIT(x,i) (x>>(i))&1
#define CLR_BITS(x,i,Mask) x&=~(Mask<<(i))
#define SET_BITS(x,i,Mask) x|=(Mask<<(i))

#define BYTE_OFFSET(REG_ADD) (REG_ADD - 0x40000000)
#define BIT_WORD_OFFSET(REG_ADD,BIT_NUM) (( BYTE_OFFSET(REG_ADD)* 32) + (BIT_NUM * 4)) 
#define BIT_WORD_ADDR(REG_ADD,BIT_NUM) (BITBAND_BASE + BIT_WORD_OFFSET(REG_ADD,BIT_NUM))
#define GET_BIT_PERPHBAND(REG_ADD,BIT_NUM) (*((volatile uint32 *)BIT_WORD_ADDR(REG_ADD,BIT_NUM)))
#define SET_BIT_PERPHBAND(REG_ADD,BIT_NUM) (GET_BIT_PERPHBAND(REG_ADD,BIT_NUM) = (uint32)0x01)
#define CLR_BIT_PERPHBAND(REG_ADD,BIT_NUM) (GET_BIT_PERPHBAND(REG_ADD,BIT_NUM) = (uint32)0x00)

#endif
