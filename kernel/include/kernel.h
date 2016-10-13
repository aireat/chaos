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

#ifndef __KERNEL_H__
#define __KERNEL_H__


#include "type.h"
#include "chaos.h"

#include "k_log.h"
#include "clz_func.h"
#include "scheduler.h"
#include "utility.h"

#include "handler.h"
#include "switcher.h"
#include "task_entry.h"
#include "task_idle.h"


#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

typedef struct _KERNEL_
{
    P_TASK_t        task_curr_running;
    P_TASK_t        task_next_running;
    P_TASK_t        task_idle;
    
    UINT            system_tick;
    UINT            system_tick_check;
#if (_ENABLE_STACK_TRACE)
    UINT            system_tick_stack_trace;
#endif
    
    UINT            idle_stay_ms;

    SLIST_t         slist_task;
    SLIST_t         slist_resource;

    SCHEDULER_t     sch;

} KERNEL_t, *P_KERNEL_t;


extern KERNEL_t     g_kernel;

VOID     __knl_init(VOID);
RESULT_t __knl_task_create(P_TASK_t p_task, TASK_OPT_t option_flag);
RESULT_t __knl_task_delete(P_TASK_t p_task);
RESULT_t __knl_task_ready(P_TASK_t p_task, INT priority);
RESULT_t __knl_task_block(P_TASK_t p_task, VOID *wait_obj, UINT time_ms);

#if (_ENABLE_USE_SVC_CALL)
RESULT_t __svc(0x00) _knl_task_create(P_TASK_t p_task, TASK_OPT_t option_flag);
RESULT_t __svc(0x00) _knl_task_delete(P_TASK_t p_task);
RESULT_t __svc(0x00) _knl_task_ready(P_TASK_t p_task, INT priority);
RESULT_t __svc(0x00) _knl_task_block(P_TASK_t p_task, VOID *wait_obj, UINT time_ms);
#else
#define _knl_task_create    __knl_task_create
#define _knl_task_delete    __knl_task_delete
#define _knl_task_ready     __knl_task_ready
#define _knl_task_block     __knl_task_block
#endif





//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__KERNEL_H__

