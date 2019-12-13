/*
 * Can_PBcfg.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Sad MultiVerse
 */

#include "Can.h"

McuClockReferencePoint Clk = CLOCK;

/*BaudRate Configuration For Controller 0*/
CanControllerBaudrateConfig CanControllerBaudrateConf[] =
{
    {
        100,                                     /* BaudRate in Kbps    */
        CONTROLLER_0_BDR_ID,                     /* Baudrate Configuration ID   */
        1,                                       /* propagation delay   */
        4,                                       /* Phase1  */
        4,                                       /* Phase2  */
        4                                        /* SJW */
    }

};

/*  Controller0 Configuration   */
CanController CanControllerCfg[] =
{
    {
        0,                                  /*  Controller ID   */
        POLLING_PROCESSING,					/*  CanRxProcessing */
		0x40040000,                         /*  BASE Address    */
        &Clk,                               /*  Reference to System clock in Hz */
        &CanControllerBaudrateConf[0]       /*  Reference to Baudrate configuration */
    },
    {
        1,                                  /*  Controller ID   */
        POLLING_PROCESSING,					/*  CanRxProcessing */
		0x40041000,                         /*  BASE Address    */
        &Clk,                               /*  Reference to System clock in Hz */
        &CanControllerBaudrateConf[0]       /*  Reference to Baudrate configuration */
    }
};

/*Filter configuration for HOH0*/
CanHwFilter CanHwFilterHTH[] =
{
    {   
        1,               /* ID  */
        0x7FF            /* Mask.not used as it's TRANSMIT HOH  */
    }
};

/*Filter configuration for HOH1*/
CanHwFilter CanHwFilterHRH[] =
{
    {
        2,               /*  ID  */
        0x7FF               /*  Mask filter */
    }
};

/*Configuration FOR all used Hardware objects*/
CanHardwareObject HOHObj[CAN_HOH_NUMBER] =
{
    {   FULL,                   /*  Can controller type for tm4c123gh6pm    */
        1,                      /*  Number of FIFO elements for this HOH    */
        STANDARD,               /*  Arbitration ID type */
        HTH0_0,                 /*  HOH ID  */
        TRANSMIT,               /*  HOH Type    */
        &CanControllerCfg[0],   /*  Reference to the controller this HOH belongs to */
        &CanHwFilterHTH[0],      /*  Reference to the Filter configuartion   */
        FALSE
    },
    {
        FULL,                   /*  Can controller type for tm4c123gh6pm    */
        1,                      /*  Number of FIFO elements for this HOH    */
        STANDARD,               /*  Arbitration ID type */
        HRH0_1,                 /*  HOH ID  */
        RECEIVE,                /*  HOH Type    */
        &CanControllerCfg[1],   /*  Reference to the controller this HOH belongs to */
        &CanHwFilterHRH[0],      /*  Reference to the Filter configuartion   */
        FALSE
    }
};


/*This is the type of the external data structure containing the overall initialization 
data for the CAN driver and SFR settings affecting all controllers. Furthermore it 
contains pointers to controller configuration structures. The contents of the 
initialization data structure are CAN hardware specific. */
const Can_ConfigType Can_Configurations = 
{
    CanControllerCfg,
    HOHObj
};
