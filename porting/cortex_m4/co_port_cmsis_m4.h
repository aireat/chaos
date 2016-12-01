/*========================================================================================
*                                                                                      *
*               Copyright(c) 2016, Steve.Cha, All rights reserved.                     *
*                                                                                      *
* Permission to use, copy, modify, and distribute this software in source and binary   *
* forms and its documentation for any purpose and without fee is hereby granted,       *
* provided that the above copyright notice appear in all copies and that both that     *
* copyright notice and this permission notice appear in supporting documentation.      *
*                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE Steve.Cha AND CONTRIBUTORS "AS IS" AND ANY          *
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED            *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
* IN NO EVENT SHALL Steve.Cha OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,      *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,          *
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF            *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE      *
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,                    *
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                   *
*                                                                                      *
========================================================================================*/

#ifndef __CO_PORT_CMSIS_H__
#define __CO_PORT_CMSIS_H__

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

typedef enum IRQn
{
    /* Core interrupts */
    NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
    HardFault_IRQn               = -13,              /**< Cortex-M4 SV Hard Fault Interrupt */
    MemoryManagement_IRQn        = -12,              /**< Cortex-M4 Memory Management Interrupt */
    BusFault_IRQn                = -11,              /**< Cortex-M4 Bus Fault Interrupt */
    UsageFault_IRQn              = -10,              /**< Cortex-M4 Usage Fault Interrupt */
    SVCall_IRQn                  = -5,               /**< Cortex-M4 SV Call Interrupt */
    DebugMonitor_IRQn            = -4,               /**< Cortex-M4 Debug Monitor Interrupt */
    PendSV_IRQn                  = -2,               /**< Cortex-M4 Pend SV Interrupt */
    SysTick_IRQn                 = -1,               /**< Cortex-M4 System Tick Interrupt */

} IRQn_Type;

/*======================================================================================*/
/*
    Setting for Windows system
*/
/*======================================================================================*/

#define __MPU_PRESENT                  0         /**< Defines if an MPU is present or not */
#define __NVIC_PRIO_BITS               4         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */
#define __FPU_PRESENT                  1         /**< Defines if an FPU is present or not */

#include "core_cm4.h"

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__CO_PORT_CMSIS_H__

