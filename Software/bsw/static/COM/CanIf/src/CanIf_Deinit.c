/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2020)		                                  **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : CanIf.c         			                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-01-26                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : TIVA C		                                                **
**                                                                            **
**  AUTHOR       : AUTOSarZs-DevTeam	                                       **
**                                                                            **
**  VENDOR       : AUTOSarZs OLC	                                             **
**                                                                            **
**                                                                            **
**  DESCRIPTION  : CAN Interface source file                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Interface, AUTOSAR Release 4.3.1  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


/*****************************************************************************************/
/*                                   Include Common headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Other  headres                              */
/*****************************************************************************************/



/*****************************************************************************************/
/*                                   Include Component headres                           */
/*****************************************************************************************/
#include "../inc/CanIf.h"

/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/


/*****************************************************************************************/
/*                                   Local Definition                                    */
/*****************************************************************************************/
/*    Description        :
 */

/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/
/*
 *  Type Description : Struct to map CanIds to a specific L-PDU of type dynamic  .
 */
typedef struct
{
   Can_IdType     CanId;
   PduIdType      PduId;
}str_MapCanIdToPdu ;


/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
/*    Type Description        :                                                          */
/*    Type range              :                                                          */

/*****************************************************************************************/
/*                                global Variables Definition                            */
/*****************************************************************************************/
extern CanIfTxPduCfgType* CanIfTxPduCfgPtr ;
extern CanIfRxPduCfgType* CanIfRxPduCfgPtr ;
extern CanIfHrhCfgType*   CanIfHrhCfgPtr   ;
extern CanIfHthCfgType*   CanIfHthCfgPtr   ;
/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/

/*Array of struct to map CanIds to a specific L-PDU of type dynamic*/
static str_MapCanIdToPdu  MapCanIdToPdu[TX_CAN_L_PDU_NUM] = {0};


/*Pointer to save configuration parameters set */
extern const CanIf_ConfigType*    CanIf_ConfigPtr;

/*Array to save each logical controller PDUs mode */
static CanIf_PduModeType CanIf_PduMode[CANIF_CONTROLLERS_NUM] ;

/* Holding the CanIf module current state. Initially, CANIF_UNINT. */
extern CanIf_ModuleStateType CanIf_ModuleState;

/*****************************************************************************************/
/*                                   Local Function Declaration                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/




/****************************************************************************************/
/*    Function Description    : This function De-initializes the CanIf module.          */
/*    Parameter in            : none                                                    */
/*    Parameter inout         : none                                                    */
/*    Parameter out           : none                                                    */
/*    Return value            : none                                                    */
/*    Requirement             : SWS_CANIF_91002                                         */
/*    Notes                   : Caller of the CanIf_DeInit() function has to be sure    */
/*                              there are no on-going transmissions/receptions          */
/*                              , nor any pending transmission confirmations.           */
/*                            :[SWS_BSW_00152] Call to De-Initialization functions is   */
/*                             restricted Only the ECU State Manager and                */
/*                             Basic Software Mode Manager are allowed to call          */
/*                            :[SWS_BSW_00072] Module state after De-Initialization     */
/*                             function The state of a BSW Module shall be set          */
/*                             accordingly at the beginning of the DeInitialization     */
/*                             function.                                                */
/*                            :[SWS_BSW_00233] Multiple calls to De-Initialization      */
/*                              functions The module De-Initialization function shall be*/
/*                              called only if the module was initialized before        */
/*                              (initialization function was called)                    */
/*                            :[SWS_BSW_00233] Multiple calls to De-Initialization      */
/*                              functions The module De-Initialization function shall   */
/*                              be called more than one time after the module           */
/*****************************************************************************************/
   void CanIf_DeInit(void){

       /*Report module without initialization parameter error*/
  #if (CANIF_DEV_ERROR_DETECT == STD_ON)
        if (CanIf_ModuleState != CANIF_READY)
           {
           Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID,CANIF_DENIT_API_ID,CANIF_E_UNINIT);
           }

  #endif

        /*Set the Pointer to configuration parameters to null pointer*/
       CanIf_ConfigPtr = NULL_PTR;
       /*Set the module state to uninit state*/
       CanIf_ModuleState = CANIF_UNINT ;

   }


