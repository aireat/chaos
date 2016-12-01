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

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


VOID _port_stack_set_up(P_TASK_t p_task, P_TASK_PROC_t entry_point, VOID *p_arg)
{
    UINT *p_top;

    // make growing down initial stack

    // move to top of stack
    {
        p_top  = (UINT*)p_task->stack_addr;
        p_top += (p_task->scratch >> 2) - 1;
    }

    // Initialize register
    {
        *(--p_top) = (UINT) 0xAA;                   // 01. TOP
        *(--p_top) = (UINT) 0x01000000;             // 02. PSR
        *(--p_top) = (UINT) _task_entry_point;      // 03. PC
        *(--p_top) = (UINT) 0x14;                   // 04. LR
        *(--p_top) = (UINT) 0x12;                   // 05. R12
#if 0
        *(--p_top) = (UINT) 0x00;                   // 06. R3
        *(--p_top) = (UINT) p_arg;                  // 07. R2
        *(--p_top) = (UINT) entry_point;            // 08. R1
        *(--p_top) = (UINT) p_task;                 // 09. R0
#else        
        *(--p_top) = (UINT) 0x03;                   // 06. R3
        *(--p_top) = (UINT) 0x02;                  // 07. R2
        *(--p_top) = (UINT) 0x01;            // 08. R1
        *(--p_top) = (UINT) 0x00;                 // 09. R0
#endif        

        *(--p_top) = (UINT) 0xFFFFFFFDUL;           // 10. LR for FPU

        *(--p_top) = (UINT) 0x11;                   // 11. R11
        *(--p_top) = (UINT) 0x10;                   // 12. R10
        *(--p_top) = (UINT) 0x09;                   // 13. R9
        *(--p_top) = (UINT) 0x08;                   // 14. R8
        *(--p_top) = (UINT) 0x07;                   // 15. R7
        *(--p_top) = (UINT) 0x06;                   // 16. R6
        *(--p_top) = (UINT) 0x05;                   // 17. R5
        *(--p_top) = (UINT) 0x04;                   // 18. R4
    }

    p_task->stack_addr = (INT*)p_top;
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

