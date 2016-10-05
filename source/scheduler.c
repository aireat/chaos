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

#define READY_FLAG_SET(p_ready, priority)                                               \
        {                                                                               \
            (p_ready)->flag |= (INT32)(1 << (31 - priority));                           \
        }

#define READY_FLAG_CLEAR(p_ready, priority)                                             \
        {                                                                               \
            if (!(p_ready)->list[priority].p_head)                                      \
                (p_ready)->flag &= (INT32)~(1 << (31 - priority));                      \
        }


UINT _sch_get_next_task(VOID)
{
    P_TASK_t    p_task;
    P_READY_t   p_ready = g_kernel.sch.p_ready0;

    // exist ready task
    if (p_ready->flag)
    {
        INT         priority;
        P_DNODE_t   p_dnode_task;

        priority = clz_func(p_ready->flag);
        p_dnode_task = p_ready->list[priority].p_head;

        dlist_cut_node(p_dnode_task);
        p_task = _CO_TYPE(TASK_t, dnode_task, p_dnode_task);

#if (_ENABLE_FAIR_SCHEDULING)
        {
            

            READY_FLAG_CLEAR(g_kernel.sch.p_ready0, priority);
p_list   = &(g_kernel.sch.p_ready0->list[priority]);
        dlist_add_node_at_tail(&(g_kernel.sch.p_ready1->list[priority]),
                               &(p_task->node_task));
        READY_FLAG_SET(g_kernel.sch.p_ready1, priority);

        if (g_kernel.sch.p_ready0 == &(g_kernel.sch.ready[0]))
            p_task->flag &= ~(TASK_FLAG_READY1);
        else
            p_task->flag |= TASK_FLAG_READY1;
        }
#else
        {
            dlist_add_node_at_tail(&(p_ready->list[priority]), 
                                   p_dnode_task);
        }
#endif

        return (UINT)p_task;
    }
    // no ready task.
    else
    {

    }

    return 0;
}

//
// 현제 ready 정보에 task를 설정한다.
//
VOID _sch_make_ready(P_TASK_t p_task)
{
    // make a task free
    _sch_make_free(p_task);

    // add task in ready list
    {
        // add task into list
        dlist_add_node_at_tail(&(g_kernel.sch.p_ready0->list[p_task->priority]), 
                               &(p_task->dnode_task));

        // set flag to indicate added task
        READY_FLAG_SET(g_kernel.sch.p_ready0, p_task->priority);
    }

    // set flag of task
#if (_MAXIMUM_PRIORITY > 1)
{
    if (g_kernel.sch.p_ready0 == &(g_kernel.sch.ready[0]))
        p_task->flag = (TASK_FLAG_READY | TASK_FLAG_READY1);
    else
        p_task->flag = (TASK_FLAG_READY);
}
#else
{
    p_task->flag = (TASK_FLAG_READY);
}
#endif
}

/*
VOID _sch_make_block(P_TASK_t p_task, UINT wait_obj, UINT time_ms)
{
    //
    // make a task free
    //
    _sch_make_free(p_task);

    //
    // add task in timeout list
    //
    if (time_ms > 0)
    {
        p_task->result = g_kernel.system_tick + time_ms;

        if (p_task->result <= g_kernel.system_tick)
            p_task->flag |= TASK_FLAG_TIMEOUT_OVEFLOW;

        dlist_add_node_at_tail(&(g_kernel.sch.timeout),
                               &(p_task->node_timeout));

        p_task->flag |= TASK_FLAG_TIMEOUT;
    }

    p_task->flag |= TASK_FALG_BLOCK;
}
*/

VOID _sch_make_free(P_TASK_t p_task)
{
    // cut node_task of task
    if (p_task->dnode_task.p_list)
    {
#if (_MAXIMUM_PRIORITY > 1)        
        if (p_task->flag & TASK_FLAG_READY)
        {
            INT         priority = p_task->priority;
            P_READY_t   p_ready  = &(g_kernel.sch.ready[0]);

            if (p_task->flag & TASK_FLAG_READY1)
                p_ready++;

            if (p_task->flag & TASK_FLAG_CHANGED_PRIORITY)
                priority = 0;

            READY_FLAG_CLEAR(p_ready, priority);
        }
#endif

        dlist_cut_node(&(p_task->dnode_task));
    }

    // cut node_timeout of task
    if (p_task->dnode_timeout.p_list)
    {
        dlist_cut_node(&(p_task->dnode_timeout));
    }

    p_task->flag = TASK_FLAG_NONE;
}

VOID _sch_change_priority(P_TASK_t p_task)
{
    if (p_task->flag & TASK_FLAG_CHANGED_PRIORITY)
        return;

#if (_MAXIMUM_PRIORITY > 1)
{
    P_READY_t   p_ready;
    
    // get ready list
    p_ready  = &(g_kernel.sch.ready[0]);
    if (p_task->flag & TASK_FLAG_READY1)
        p_ready++;

    // remove task in previous priority list
    dlist_cut_node(&(p_task->dnode_task));
    READY_FLAG_CLEAR(p_ready, p_task->priority);

    // add task at new priority list
    dlist_add_node_at_tail(&(p_ready->list[0]),
                           &(p_task->dnode_task));
    READY_FLAG_SET(p_ready, 0);
}
#endif

    // set flag to indicate changed priority
    p_task->flag |= TASK_FLAG_CHANGED_PRIORITY;
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

