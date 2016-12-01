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

#include "co_kernel.h"
#include "co_port_cmsis_m4.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

extern uint32_t SystemCoreClock;

VOID __start_first_task(VOID);

VOID _port_system_init(VOID)
{
    // nothing
}

VOID _port_system_start(VOID)
{
    __disable_irq();

    SysTick_Config(SystemCoreClock/1000*_SYSTEM_TICK_TIME);

    __start_first_task();
}

__ASM__ VOID __start_first_task(VOID)
{
    IMPORT  __Vectors
    IMPORT  g_kernel

    LDR     R0, =__Vectors
    LDR     R0, [R0] 
    MSR     MSP, R0                 /* Set the msp back to the start of the stack. */

    LDR     R3, =g_kernel           /* Obtain first task */
    LDR     R3, [R3]
    LDR     R1, [R3]                /* Obtain first task's stack */

//    ADDS    R1, #32                 /* Discard everything up to r0. */
    MSR     PSP, R1                 /* This is now the new top of stack to use in the task. */

//    MRS     R0, CONTROL
//    ORR     R0, R0, #2                  /* Switch to the psp stack. */
    MOVS    R0, #2
    MSR     CONTROL, R0

    POP     {R4-R11, R14}
    POP     {R0-R3, R12, R14}                 /* Pop the registers that are saved automatically. */
//    MOV     LR, R5                  /* lr is now in r5. */

    CPSIE   I                       /* Enable Interrupt [__enable_irq()] */

    POP     {PC}                    /* Finally, pop the PC to jump to the user defined task code. */
    ALIGN
}

VOID _port_do_context_switch(VOID)
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    __DSB();
    __ISB();
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

