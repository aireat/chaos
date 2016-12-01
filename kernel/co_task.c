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


VOID _task_entry_point(P_TASK_t       p_task,
                       P_TASK_PROC_t  entry_point,
                       VOID          *p_arg,
                       INT            result)
{
    INT     i = 0;
	while(1)
    {
        i++;
    }
    _K_LOG_TASK("[%s] task created.", p_task->name);

    // call entry point
    result = entry_point(p_arg);

    _K_LOG_TASK("[%s] task deleted. exit code(%d).", p_task->name, result);

    svc_task_delete(p_task);
}


INT _task_idle(VOID *p_arg)
{
    p_arg = 0x00;
    //_port_user_idle(g_kernel.idle_stay_ms);


    while(1);
}

WEAK VOID _port_user_idle(UINT idle_stay_ms)
{
    //TODO: delete
    idle_stay_ms = 0;
}


RESULT_t _svc_task_create(P_TASK_t p_task)
{
    if (g_kernel.task_curr_running == NULL)
        g_kernel.task_curr_running = p_task;

    // Add task in creation list
    slist_add_node_at_tail(&(g_kernel.slist_task), &(p_task->snode_create));

    _sch_make_ready(p_task, p_task->priority);

    return RESULT_SUCCESS;
}

RESULT_t _svc_task_delete(P_TASK_t p_task)
{
    // Make task as free state
    _sch_make_free(p_task);

    // Delete task from creation list
    slist_cut_node(&(g_kernel.slist_task), &(p_task->snode_create));

    _knl_do_context_switch();

    return RESULT_SUCCESS;
}

RESULT_t _svc_task_ready(P_TASK_t p_task, INT priority)
{
    if (p_task->flag & TASK_FLAG_ERROR)
    {
        _K_LOG_TASK("[%s] task is seted internal error flag and call task_ready()",
                    p_task->name);
        return RESULT_INTERNAL_ERROR;
    }

    _sch_make_ready(p_task, priority);

    return RESULT_SUCCESS;
}

RESULT_t _svc_task_block(P_TASK_t p_task, VOID *wait_obj, UINT time_ms)
{
    _sch_make_block(p_task, (P_OBJ_HEAD_t)wait_obj, time_ms);

    _knl_do_context_switch();

    return RESULT_SUCCESS;
}


RESULT_t task_create(P_TASK_t       p_task,
                     P_TASK_PROC_t  entry_point,
                     VOID          *p_arg)
{
    if (p_task->priority == 0)
        return RESULT_TASK_INVALID_PRIORITY;

    // check priority
    p_task->priority = (INT8)(_CO_MIN((p_task->priority), 
                                      (_MAXIMUM_PRIORITY)) - 1);

    // make specific pattern in stack for traceing
#if (_ENABLE_STACK_TRACE)
    {
        _co_memset(p_task->stack_size_trace, 0xCC, p_task->scratch);

    #if (_STACK_GROWS_DOWN)
        {
            p_task->stack_size_trace += (p_task->scratch >> 2) - 1;
        }
    #endif
    }
#endif

    // set-up initial stack
    _port_stack_set_up(p_task, entry_point, p_arg);

    return svc_task_create(p_task);
}


RESULT_t task_delete(P_TASK_t p_task)
{
    return svc_task_delete(p_task);
}


RESULT_t task_block(P_TASK_t p_task)
{
    if (p_task->flag & TASK_FLAG_ERROR)
    {
        _K_LOG_TASK("[%s] task TASK_FLAG_ERROR[%04X] in task_block()",
                    p_task->name, p_task->flag);

        return RESULT_TASK_FLAG_ERROR;
    }

    if (!(p_task->flag & TASK_FLAG_READY))
        return RESULT_SUCCESS;

    return svc_task_block(p_task, NULL, TASK_TIME_INFINITE);
}

RESULT_t task_ready(P_TASK_t p_task)
{
    if (p_task->flag & TASK_FLAG_ERROR)
    {
        _K_LOG_TASK("[%s] task TASK_FLAG_ERROR[%04X] in task_ready()",
                    p_task->name, p_task->flag);

        return RESULT_TASK_FLAG_ERROR;
    }

    if (p_task->flag & TASK_FLAG_READY)
        return RESULT_SUCCESS;

    return svc_task_ready(p_task, p_task->priority);
}

RESULT_t task_yield(VOID)
{
    P_TASK_t p_task = g_kernel.task_curr_running;

    return svc_task_block(p_task, NULL, 0);
}

RESULT_t task_sleep(UINT millisecond)
{
    P_TASK_t p_task = g_kernel.task_curr_running;

    if (!(p_task->flag & TASK_FLAG_READY))
    {
        if (p_task->flag & TASK_FLAG_ERROR)
        {
            _K_LOG_TASK("[%s] task TASK_FLAG_ERROR[%04X] in task_sleep()",
                        p_task->name, p_task->flag);

            return RESULT_TASK_FLAG_ERROR;
        }

        _K_LOG_TASK("[%s] task INVALID_STATE[%04X] in task_sleep()",
                    p_task->name, p_task->flag);

        return RESULT_INVALID_STATE;
    } 

    return svc_task_block(p_task, NULL, millisecond);
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

