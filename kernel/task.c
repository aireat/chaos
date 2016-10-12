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

RESULT_t task_create(P_TASK_t       p_task,
                     P_TASK_PROC_t  entry_point,
                     VOID          *p_arg,
                     TASK_OPT_t     option_flag)
{
    // check priority
    p_task->priority = (INT8)(_CO_MIN((p_task->priority), 
                                      (_MAXIMUM_PRIORITY)) - 1);

    // make specific pattern in stack for traceing
#if (_ENABLE_STACK_TRACE)
    {
        _co_memset(p_task->stack_size_trace, 0xCC, p_task->scratch);

    #if (_STACK_GROWS_DOWN)
        {
            p_task->stack_size_trace += (p_task->scratch >> 2);
        }
    #endif
    }
#endif

    // set-up initial stack
    _port_stack_set_up(p_task, entry_point, p_arg);

    return _knl_task_create(p_task, option_flag);
}


RESULT_t task_delete(P_TASK_t p_task)
{
    return _knl_task_delete(p_task);
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

    return _knl_task_block(p_task, NULL, TASK_TIME_INFINITE);
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

    return _knl_task_ready(p_task, p_task->priority);
}

RESULT_t task_yield(VOID)
{
    P_TASK_t p_task = g_kernel.task_curr_running;

    return _knl_task_block(p_task, NULL, 0);
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

    return _knl_task_block(p_task, NULL, millisecond);
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

