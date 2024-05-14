/***************************************************************************//**
* \file UART_GPS.h
* \version 2.0
*
*  This file provides constants and parameter values for the UART component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(UART_GPS_CY_SCB_UART_PDL_H)
#define UART_GPS_CY_SCB_UART_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define UART_GPS_DIRECTION  (1U)
#define UART_GPS_ENABLE_RTS (0U)
#define UART_GPS_ENABLE_CTS (0U)

/* UART direction enum */
#define UART_GPS_RX    (0x1U)
#define UART_GPS_TX    (0x2U)

#define UART_GPS_ENABLE_RX  (0UL != (UART_GPS_DIRECTION & UART_GPS_RX))
#define UART_GPS_ENABLE_TX  (0UL != (UART_GPS_DIRECTION & UART_GPS_TX))


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component specific functions. */
void UART_GPS_Start(void);

/* Basic functions */
__STATIC_INLINE cy_en_scb_uart_status_t UART_GPS_Init(cy_stc_scb_uart_config_t const *config);
__STATIC_INLINE void UART_GPS_DeInit(void);
__STATIC_INLINE void UART_GPS_Enable(void);
__STATIC_INLINE void UART_GPS_Disable(void);

/* Register callback. */
__STATIC_INLINE void UART_GPS_RegisterCallback(cy_cb_scb_uart_handle_events_t callback);

/* Configuration change. */
#if (UART_GPS_ENABLE_CTS)
__STATIC_INLINE void UART_GPS_EnableCts(void);
__STATIC_INLINE void UART_GPS_DisableCts(void);
#endif /* (UART_GPS_ENABLE_CTS) */

#if (UART_GPS_ENABLE_RTS)
__STATIC_INLINE void     UART_GPS_SetRtsFifoLevel(uint32_t level);
__STATIC_INLINE uint32_t UART_GPS_GetRtsFifoLevel(void);
#endif /* (UART_GPS_ENABLE_RTS) */

__STATIC_INLINE void UART_GPS_EnableSkipStart(void);
__STATIC_INLINE void UART_GPS_DisableSkipStart(void);

#if (UART_GPS_ENABLE_RX)
/* Low level: Receive direction. */
__STATIC_INLINE uint32_t UART_GPS_Get(void);
__STATIC_INLINE uint32_t UART_GPS_GetArray(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_GPS_GetArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t UART_GPS_GetRxFifoStatus(void);
__STATIC_INLINE void     UART_GPS_ClearRxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t UART_GPS_GetNumInRxFifo(void);
__STATIC_INLINE void     UART_GPS_ClearRxFifo(void);
#endif /* (UART_GPS_ENABLE_RX) */

#if (UART_GPS_ENABLE_TX)
/* Low level: Transmit direction. */
__STATIC_INLINE uint32_t UART_GPS_Put(uint32_t data);
__STATIC_INLINE uint32_t UART_GPS_PutArray(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_GPS_PutArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_GPS_PutString(char_t const string[]);
__STATIC_INLINE void     UART_GPS_SendBreakBlocking(uint32_t breakWidth);
__STATIC_INLINE uint32_t UART_GPS_GetTxFifoStatus(void);
__STATIC_INLINE void     UART_GPS_ClearTxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t UART_GPS_GetNumInTxFifo(void);
__STATIC_INLINE bool     UART_GPS_IsTxComplete(void);
__STATIC_INLINE void     UART_GPS_ClearTxFifo(void);
#endif /* (UART_GPS_ENABLE_TX) */

#if (UART_GPS_ENABLE_RX)
/* High level: Ring buffer functions. */
__STATIC_INLINE void     UART_GPS_StartRingBuffer(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_GPS_StopRingBuffer(void);
__STATIC_INLINE void     UART_GPS_ClearRingBuffer(void);
__STATIC_INLINE uint32_t UART_GPS_GetNumInRingBuffer(void);

/* High level: Receive direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t UART_GPS_Receive(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_GPS_AbortReceive(void);
__STATIC_INLINE uint32_t UART_GPS_GetReceiveStatus(void);
__STATIC_INLINE uint32_t UART_GPS_GetNumReceived(void);
#endif /* (UART_GPS_ENABLE_RX) */

#if (UART_GPS_ENABLE_TX)
/* High level: Transmit direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t UART_GPS_Transmit(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_GPS_AbortTransmit(void);
__STATIC_INLINE uint32_t UART_GPS_GetTransmitStatus(void);
__STATIC_INLINE uint32_t UART_GPS_GetNumLeftToTransmit(void);
#endif /* (UART_GPS_ENABLE_TX) */

/* Interrupt handler */
__STATIC_INLINE void UART_GPS_Interrupt(void);
/** @} group_general */


/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t UART_GPS_initVar;
extern cy_stc_scb_uart_config_t const UART_GPS_config;
extern cy_stc_scb_uart_context_t UART_GPS_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the hardware */
#define UART_GPS_HW     ((CySCB_Type *) UART_GPS_SCB__HW)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: UART_GPS_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART_GPS_Init(cy_stc_scb_uart_config_t const *config)
{
   return Cy_SCB_UART_Init(UART_GPS_HW, config, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_DeInit(void)
{
    Cy_SCB_UART_DeInit(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_Enable(void)
{
    Cy_SCB_UART_Enable(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_Disable(void)
{
    Cy_SCB_UART_Disable(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_RegisterCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_RegisterCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_RegisterCallback(cy_cb_scb_uart_handle_events_t callback)
{
    Cy_SCB_UART_RegisterCallback(UART_GPS_HW, callback, &UART_GPS_context);
}


#if (UART_GPS_ENABLE_CTS)
/*******************************************************************************
* Function Name: UART_GPS_EnableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_EnableCts(void)
{
    Cy_SCB_UART_EnableCts(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_DisableCts(void)
{
    Cy_SCB_UART_DisableCts(UART_GPS_HW);
}
#endif /* (UART_GPS_ENABLE_CTS) */


#if (UART_GPS_ENABLE_RTS)
/*******************************************************************************
* Function Name: UART_GPS_SetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_SetRtsFifoLevel(uint32_t level)
{
    Cy_SCB_UART_SetRtsFifoLevel(UART_GPS_HW, level);
}


/*******************************************************************************
* Function Name: UART_GPS_GetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetRtsFifoLevel(void)
{
    return Cy_SCB_UART_GetRtsFifoLevel(UART_GPS_HW);
}
#endif /* (UART_GPS_ENABLE_RTS) */


/*******************************************************************************
* Function Name: UART_GPS_EnableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_EnableSkipStart(void)
{
    Cy_SCB_UART_EnableSkipStart(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_DisableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_DisableSkipStart(void)
{
    Cy_SCB_UART_DisableSkipStart(UART_GPS_HW);
}


#if (UART_GPS_ENABLE_RX)
/*******************************************************************************
* Function Name: UART_GPS_Get
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Get() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_Get(void)
{
    return Cy_SCB_UART_Get(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_GetArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_GetArray(UART_GPS_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_GPS_GetArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_GetArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_GetArrayBlocking(UART_GPS_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_GPS_GetRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetRxFifoStatus(void)
{
    return Cy_SCB_UART_GetRxFifoStatus(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_ClearRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_ClearRxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearRxFifoStatus(UART_GPS_HW, clearMask);
}


/*******************************************************************************
* Function Name: UART_GPS_GetNumInRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetNumInRxFifo(void)
{
    return Cy_SCB_UART_GetNumInRxFifo(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_ClearRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_ClearRxFifo(void)
{
    Cy_SCB_UART_ClearRxFifo(UART_GPS_HW);
}
#endif /* (UART_GPS_ENABLE_RX) */


#if (UART_GPS_ENABLE_TX)
/*******************************************************************************
* Function Name: UART_GPS_Put
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Put() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_Put(uint32_t data)
{
    return Cy_SCB_UART_Put(UART_GPS_HW,data);
}


/*******************************************************************************
* Function Name: UART_GPS_PutArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_PutArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_PutArray(UART_GPS_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_GPS_PutArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_PutArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_PutArrayBlocking(UART_GPS_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_GPS_PutString
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutString() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_PutString(char_t const string[])
{
    Cy_SCB_UART_PutString(UART_GPS_HW, string);
}


/*******************************************************************************
* Function Name: UART_GPS_SendBreakBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SendBreakBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_SendBreakBlocking(uint32_t breakWidth)
{
    Cy_SCB_UART_SendBreakBlocking(UART_GPS_HW, breakWidth);
}


/*******************************************************************************
* Function Name: UART_GPS_GetTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetTxFifoStatus(void)
{
    return Cy_SCB_UART_GetTxFifoStatus(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_ClearTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_ClearTxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearTxFifoStatus(UART_GPS_HW, clearMask);
}


/*******************************************************************************
* Function Name: UART_GPS_GetNumInTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetNumInTxFifo(void)
{
    return Cy_SCB_UART_GetNumInTxFifo(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_IsTxComplete
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_IsTxComplete() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool UART_GPS_IsTxComplete(void)
{
    return Cy_SCB_UART_IsTxComplete(UART_GPS_HW);
}


/*******************************************************************************
* Function Name: UART_GPS_ClearTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_ClearTxFifo(void)
{
    Cy_SCB_UART_ClearTxFifo(UART_GPS_HW);
}
#endif /* (UART_GPS_ENABLE_TX) */


#if (UART_GPS_ENABLE_RX)
/*******************************************************************************
* Function Name: UART_GPS_StartRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StartRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_StartRingBuffer(void *buffer, uint32_t size)
{
    Cy_SCB_UART_StartRingBuffer(UART_GPS_HW, buffer, size, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_StopRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StopRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_StopRingBuffer(void)
{
    Cy_SCB_UART_StopRingBuffer(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_ClearRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_ClearRingBuffer(void)
{
    Cy_SCB_UART_ClearRingBuffer(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_GetNumInRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetNumInRingBuffer(void)
{
    return Cy_SCB_UART_GetNumInRingBuffer(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_Receive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Receive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART_GPS_Receive(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Receive(UART_GPS_HW, buffer, size, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_GetReceiveStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetReceiveStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetReceiveStatus(void)
{
    return Cy_SCB_UART_GetReceiveStatus(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_AbortReceive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortReceive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_AbortReceive(void)
{
    Cy_SCB_UART_AbortReceive(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_GetNumReceived
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumReceived() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetNumReceived(void)
{
    return Cy_SCB_UART_GetNumReceived(UART_GPS_HW, &UART_GPS_context);
}
#endif /* (UART_GPS_ENABLE_RX) */


#if (UART_GPS_ENABLE_TX)
/*******************************************************************************
* Function Name: UART_GPS_Transmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Transmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART_GPS_Transmit(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Transmit(UART_GPS_HW, buffer, size, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_GetTransmitStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTransmitStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetTransmitStatus(void)
{
    return Cy_SCB_UART_GetTransmitStatus(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_AbortTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_AbortTransmit(void)
{
    Cy_SCB_UART_AbortTransmit(UART_GPS_HW, &UART_GPS_context);
}


/*******************************************************************************
* Function Name: UART_GPS_GetNumLeftToTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumLeftToTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_GPS_GetNumLeftToTransmit(void)
{
    return Cy_SCB_UART_GetNumLeftToTransmit(UART_GPS_HW, &UART_GPS_context);
}
#endif /* (UART_GPS_ENABLE_TX) */


/*******************************************************************************
* Function Name: UART_GPS_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_GPS_Interrupt(void)
{
    Cy_SCB_UART_Interrupt(UART_GPS_HW, &UART_GPS_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* UART_GPS_CY_SCB_UART_PDL_H */


/* [] END OF FILE */
