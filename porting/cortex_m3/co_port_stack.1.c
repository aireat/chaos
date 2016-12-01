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
    INT *p_top;

    // make growing down initial stack

    // move to top of stack
    {
        p_top  = (INT*)p_task->stack_addr;
        p_top += (p_task->scratch >> 2) - 1;
    }

    // Initialize register
    {
        p_top[  0] = (INT) 0xAA;                    // 01. TOP
        p_top[ -1] = (INT) 0x01000000;              // 02. PSR
#if 1
        p_top[ -2] = (INT) _task_entry_point;       // 03. PC

        p_top[ -5] = (INT) 0x00;                    // 06. R3
        p_top[ -6] = (INT) p_arg;                   // 07. R2
        p_top[ -7] = (INT) entry_point;             // 08. R1
        p_top[ -8] = (INT) p_task;                  // 09. R0
#else
        p_top[ -2] = (INT) 0x15;       // 03. PC

        p_top[ -5] = (INT) 0x03;                    // 06. R3
        p_top[ -6] = (INT) 0x02;                   // 07. R2
        p_top[ -7] = (INT) 0x01;             // 08. R1
        p_top[ -8] = (INT) 0x00;                  // 09. R0
#endif

#if (_ENABLE_STACK_TRACE)
#if 0
        p_top[ -3] = (INT) 0x00;                    // 04. LR
        p_top[ -4] = (INT) 0x00;                    // 05. R12

        p_top[ -9] = (INT) 0x00;                    // 10. R11
        p_top[-10] = (INT) 0x00;                    // 11. R10
        p_top[-11] = (INT) 0x00;                    // 12. R9
        p_top[-12] = (INT) 0x00;                    // 13. R8
        p_top[-13] = (INT) 0x00;                    // 14. R7
        p_top[-14] = (INT) 0x00;                    // 15. R6
        p_top[-15] = (INT) 0x00;                    // 16. R5
        p_top[-16] = (INT) 0x00;                    // 17. R4
#else        
        p_top[ -3] = (INT) 0x14;                    // 04. LR
        p_top[ -4] = (INT) 0x12;                    // 05. R12

        p_top[ -9] = (INT) 0x11;                    // 10. R11
        p_top[-10] = (INT) 0x10;                    // 11. R10
        p_top[-11] = (INT) 0x09;                    // 12. R9
        p_top[-12] = (INT) 0x08;                    // 13. R8
        p_top[-13] = (INT) 0x07;                    // 14. R7
        p_top[-14] = (INT) 0x06;                    // 15. R6
        p_top[-15] = (INT) 0x05;                    // 16. R5
        p_top[-16] = (INT) 0x04;                    // 17. R4
#endif
#endif
    }

    p_task->stack_addr = &(p_top[-16]);
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

