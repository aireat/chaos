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

#define READY_FLAG_SET(p_ready, priority)                                               \
        {                                                                               \
            (p_ready)->flag |= (INT32)(1 << (31 - priority));                           \
        }

#define READY_FLAG_CLEAR(p_ready, priority)                                             \
        {                                                                               \
            if (!(p_ready)->list[priority].p_head)                                      \
                (p_ready)->flag &= (INT32)~(1 << (31 - priority));                      \
        }


P_TASK_t _sch_get_next_task(VOID)
{
    P_READY_t   p_ready = g_kernel.sch.p_ready0;

    // exist ready task
    if (p_ready->flag)
    {
        INT         priority;
        P_DNODE_t   p_dnode_task;
        P_TASK_t    p_task;

        priority = clz_func(p_ready->flag);
        p_dnode_task = p_ready->list[priority].p_head;
        p_task = _CO_TYPE(TASK_t, dnode_task, p_dnode_task);

        // cut dnode from head position
        dlist_cut_node(p_dnode_task);

#if (_ENABLE_FAIR_SCHEDULING)
        {
            // clear ready flag at current ready lists
            READY_FLAG_CLEAR(p_ready, priority);

            // move ready position
            if (p_ready == g_kernel.sch.ready)
            {
                p_ready++;
                p_task->flag |= TASK_FLAG_READY1;
            }
            else
            {
                p_ready--;
                p_task->flag &= ~TASK_FLAG_READY1;
            }
            
            // add dnode to tail position
            dlist_add_node_at_tail(&(p_ready->list[priority]), 
                                   p_dnode_task);

            // set ready flag for new ready lists
            READY_FLAG_SET(p_ready, priority);
        }
#else
        {
            // add dnode to tail position
            dlist_add_node_at_tail(&(p_ready->list[priority]), 
                                   p_dnode_task);
        }
#endif

        g_kernel.idle_stay_ms = 0;

        return p_task;
    }
    // no ready task.
    else
    {
        g_kernel.idle_stay_ms += _SYSTEM_TICK_TIME;

        return g_kernel.task_idle;
    }

    return 0;
}

//
// 현제 ready 정보에 task를 설정한다.
//
VOID _sch_make_ready(P_TASK_t p_task, INT priority)
{
    P_READY_t   p_ready = g_kernel.sch.p_ready0;

    // make a task free
    _sch_make_free(p_task);

    // add task in ready list
    {
        // add task into list
        dlist_add_node_at_tail(&(p_ready->list[priority]), 
                               &(p_task->dnode_task));

        // set flag to indicate added task
        READY_FLAG_SET(p_ready, priority);

        // set flag of task
#if (_ENABLE_FAIR_SCHEDULING)
        {
            if (p_ready == g_kernel.sch.ready)
                p_task->flag = (TASK_FLAG_READY);
            else
                p_task->flag = (TASK_FLAG_READY | TASK_FLAG_READY1);
        }
#else
        {
            p_task->flag = (TASK_FLAG_READY);
        }
#endif
        if (priority != p_task->priority)
            p_task->flag |= TASK_FLAG_CHANGED_PRIORITY;
    }
}


VOID _sch_make_block(P_TASK_t p_task, P_OBJ_HEAD_t p_obj_head, UINT time_ms)
{
    // make a task free
    _sch_make_free(p_task);

    // add task in object's block list
    if (p_obj_head)
    {
        dlist_add_node_at_tail(&(p_obj_head->dlist_wait_tasks),
                               &(p_task->dnode_task));

        p_task->flag |= TASK_FALG_WAIT_OBJECT;
    }

    // add task in timeout list
    if (time_ms > 0)
    {
        p_task->scratch = time_ms;

        p_task->flag |= TASK_FLAG_TIMEOUT;
    }
}


VOID _sch_make_free(P_TASK_t p_task)
{
    // cut dnode_task of task
    if (p_task->dnode_task.p_list)
    {
        dlist_cut_node(&(p_task->dnode_task));

        // if task is in ready lists
        if (p_task->flag & TASK_FLAG_READY)
        {
            P_READY_t   p_ready  = g_kernel.sch.ready;
            INT         priority = p_task->priority;

            if (p_task->flag & TASK_FLAG_READY1)
                p_ready++;

            if (p_task->flag & TASK_FLAG_CHANGED_PRIORITY)
                priority = 0;

            READY_FLAG_CLEAR(p_ready, priority);
        }
    }

    p_task->flag = TASK_FLAG_NONE;
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

