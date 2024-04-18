/*******************************************************************************
* File Name: PWM_thrustmotor.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the PWM_thrustmotor
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(PWM_thrustmotor_CY_TCPWM_PWM_PDL_H)
#define PWM_thrustmotor_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  PWM_thrustmotor_initVar;
extern cy_stc_tcpwm_pwm_config_t const PWM_thrustmotor_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void PWM_thrustmotor_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t PWM_thrustmotor_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void PWM_thrustmotor_DeInit(void);
__STATIC_INLINE void PWM_thrustmotor_Enable(void);
__STATIC_INLINE void PWM_thrustmotor_Disable(void);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetStatus(void);
__STATIC_INLINE void PWM_thrustmotor_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetCompare0(void);
__STATIC_INLINE void PWM_thrustmotor_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetCompare1(void);
__STATIC_INLINE void PWM_thrustmotor_EnableCompareSwap(bool enable);
__STATIC_INLINE void PWM_thrustmotor_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetCounter(void);
__STATIC_INLINE void PWM_thrustmotor_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetPeriod0(void);
__STATIC_INLINE void PWM_thrustmotor_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetPeriod1(void);
__STATIC_INLINE void PWM_thrustmotor_EnablePeriodSwap(bool enable);
__STATIC_INLINE void PWM_thrustmotor_TriggerStart(void);
__STATIC_INLINE void PWM_thrustmotor_TriggerReload(void);
__STATIC_INLINE void PWM_thrustmotor_TriggerKill(void);
__STATIC_INLINE void PWM_thrustmotor_TriggerSwap(void);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetInterruptStatus(void);
__STATIC_INLINE void PWM_thrustmotor_ClearInterrupt(uint32_t source);
__STATIC_INLINE void PWM_thrustmotor_SetInterrupt(uint32_t source);
__STATIC_INLINE void PWM_thrustmotor_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetInterruptMask(void);
__STATIC_INLINE uint32_t PWM_thrustmotor_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define PWM_thrustmotor_HW                 (PWM_thrustmotor_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define PWM_thrustmotor_CNT_HW             (PWM_thrustmotor_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define PWM_thrustmotor_CNT_NUM            (PWM_thrustmotor_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define PWM_thrustmotor_CNT_MASK           (1UL << PWM_thrustmotor_CNT_NUM)
/** @} group_macros */

#define PWM_thrustmotor_INPUT_MODE_MASK    (0x3U)
#define PWM_thrustmotor_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: PWM_thrustmotor_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t PWM_thrustmotor_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, &PWM_thrustmotor_config);
}

/*******************************************************************************
* Function Name: PWM_thrustmotor_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_MASK);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void PWM_thrustmotor_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}


/*******************************************************************************
* Function Name: PWM_thrustmotor_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t PWM_thrustmotor_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(PWM_thrustmotor_HW, PWM_thrustmotor_CNT_NUM));
}

#endif /* PWM_thrustmotor_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
