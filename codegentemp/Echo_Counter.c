/*******************************************************************************
* File Name: Echo_Counter.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the Echo_Counter
*  component
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Echo_Counter.h"

/** Indicates whether or not the Echo_Counter has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  Echo_Counter_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the Echo_Counter_Start() routine.
*/
uint8_t Echo_Counter_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated Echo_Counter_Init() function.
*/ 
cy_stc_tcpwm_counter_config_t const Echo_Counter_config =
{
        .period = 50000UL,
        .clockPrescaler = 0UL,
        .runMode = 0UL,
        .countDirection = 0UL,
        .compareOrCapture = 2UL,
        .compare0 = 16384UL,
        .compare1 = 16384UL,
        .enableCompareSwap = false,
        .interruptSources = 2UL,
        .captureInputMode = 1UL,
        .captureInput = CY_TCPWM_INPUT_CREATOR,
        .reloadInputMode = 0UL,
        .reloadInput = CY_TCPWM_INPUT_CREATOR,
        .startInputMode = 0UL,
        .startInput = CY_TCPWM_INPUT_CREATOR,
        .stopInputMode = 1UL,
        .stopInput = CY_TCPWM_INPUT_CREATOR,
        .countInputMode = 3UL,
        .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: Echo_Counter_Start
****************************************************************************//**
*
*  Calls the Echo_Counter_Init() when called the first time and enables 
*  the Echo_Counter. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref Echo_Counter_initVar
*
*******************************************************************************/
void Echo_Counter_Start(void)
{
    if (0U == Echo_Counter_initVar)
    {
        (void)Cy_TCPWM_Counter_Init(Echo_Counter_HW, Echo_Counter_CNT_NUM, &Echo_Counter_config); 

        Echo_Counter_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(Echo_Counter_HW, Echo_Counter_CNT_MASK);
    
    #if (Echo_Counter_INPUT_DISABLED == 0UL)
        Cy_TCPWM_TriggerStart(Echo_Counter_HW, Echo_Counter_CNT_MASK);
    #endif /* (Echo_Counter_INPUT_DISABLED == 0UL) */    
}


/* [] END OF FILE */
