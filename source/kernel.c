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

#include "kernel.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


/*======================================================================================*/
/*
    Global variable
*/
/*======================================================================================*/
KERNEL_t     g_kernel;

#if (_ENABLE_STACK_TRACE)
INT _knl_stack_usage(P_TASK_t p_task);
#endif

VOID _knl_init(VOID)
{
    _co_memset(&g_kernel, 0x00, sizeof(g_kernel));

    g_kernel.sch.p_ready0 = g_kernel.sch.ready;
}

RESULT_t _knl_task_create(P_TASK_t p_task, TASK_OPT_t option_flag)
{
    // Add task in creation list
    slist_add_node_at_tail(&(g_kernel.slist_task), &(p_task->snode_create));

    // Make task as ready state
    if (!(option_flag & TASK_OPT_BLOCKED))
    {
        _sch_make_ready(p_task, p_task->priority);
    }

    return RESULT_SUCCESS;
}

RESULT_t _knl_task_delete(P_TASK_t p_task)
{
    // Make task as free state
    _sch_make_free(p_task);

    // Delete task from creation list
    slist_cut_node(&(g_kernel.slist_task), &(p_task->snode_create));

    _knl_do_context_switch();

    return RESULT_SUCCESS;
}

RESULT_t _knl_task_ready(P_TASK_t p_task, INT priority)
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

RESULT_t _knl_task_block(P_TASK_t p_task, VOID *wait_obj, UINT time_ms)
{


    _sch_make_block(p_task, (P_OBJ_HEAD_t)wait_obj, time_ms);

    return RESULT_SUCCESS;
}

VOID _knl_systick_handler(VOID)
{
    g_kernel.system_tick += _MS_VALUE_PER_A_TICK;

    if (g_kernel.task_curr_running == g_kernel.task_idle)
        _knl_do_context_switch();
}

VOID _knl_do_context_switch(VOID)
{
    _knl_check_changes();

    g_kernel.task_next_running = _sch_get_next_task();
    if (g_kernel.task_next_running != g_kernel.task_curr_running)
    {
        g_kernel.task_next_running = g_kernel.task_curr_running;

        _PORT_DO_CONTEXT_SWITCH();
    }
}

#if (_ENABLE_STACK_TRACE)
INT _knl_stack_usage(P_TASK_t p_task)
{
    if (!(p_task->flag & TASK_FLAG_ERROR))
    {
        if (*(p_task->stack_size_trace) == 0xCCCCCCCC)
            return 0;

#if (_STACK_GROWS_DOWN)
        {
            while ((*(p_task->stack_size_trace)-- != 0xCCCCCCCC) &&
                (p_task->stack_size_usage < p_task->stack_size_total))
            {
                p_task->stack_size_usage += 4;
            }
        }
#else
        {
            while ((*(p_task->stack_size_trace)++ != 0xCCCCCCCC) &&
                (p_task->stack_size_usage < p_task->stack_size_total))
            {
                p_task->stack_size_usage += 4;
            }
        }    
#endif

        _K_LOG_TASK("[%s] task's stack report : use(%4d)/max(%4d)",
                    p_task->name,
                    p_task->stack_size_usage,
                    p_task->stack_size_total);
    }

    if (p_task->stack_size_total >= p_task->stack_size_usage)
    {
        _K_LOG_ERR("!!! [%s] task stack overflow use(%4d)/max(%4d) !!!",
                    p_task->name,
                    p_task->stack_size_usage,
                    p_task->stack_size_total);

        // Make task as free state
        _sch_make_free(p_task);

        // set error flag
        p_task->flag = TASK_FLAG_ERROR;
    }

    if (p_task->flag & TASK_FLAG_ERROR)
        return 1;

    return 0;
}
#endif

VOID _knl_check_changes(VOID)
{
    P_TASK_t        p_task;
    P_SNODE_t       p_snode = g_kernel.slist_task.p_head;
    P_OBJ_HEAD_t    p_object;

    while (p_snode)
    {
        p_task = _CO_TYPE(TASK_t, snode_create, p_snode);
        p_snode = p_snode->p_next;

#if (_ENABLE_STACK_TRACE)
        if (g_kernel.system_tick >= (g_kernel.system_tick_stack_trace + 10000))
        {
            if (p_task != g_kernel.task_curr_running)
            {
                if (_knl_stack_usage(p_task))
                    continue;
            }
        }
#endif

        // If task is ready, go next item
        if (p_task->flag & TASK_FLAG_READY)
            continue;

        // check wait object's changes
        if (p_task->flag & TASK_FALG_WAIT_OBJECT)
        {
            p_object = (P_OBJ_HEAD_t) p_task->dnode_task.p_list;
            if (p_object->change_count > 0)
            {
                if (p_object->change_callback())
                    continue;
            }
        }

        // if system tick is not chagne, go next item
        if (g_kernel.system_tick == g_kernel.system_tick_check)
            continue;

        // check timeout
        if (p_task->flag & TASK_FLAG_TIMEOUT)
        {
            if (p_task->scratch <= _MS_VALUE_PER_A_TICK)
            {
                _sch_make_ready(p_task, p_task->priority);

                // TODO: need to define timeout-value
                p_task->scratch = 0;

                continue;
            }

            p_task->scratch -= _MS_VALUE_PER_A_TICK;
        }
    }
}



//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

