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


#define READY_FLAG_SET(p_ready, priority)                                                \
        {                                                                                \
            (p_ready)->flag |= (UINT32)(1 << (31 - priority));                                   \
        }

#define READY_FLAG_CLEAR(p_ready, priority)                                              \
        {                                                                                \
            if (!(p_ready)->list[priority].p_head)                                       \
                (p_ready)->flag &= (UINT32)~(1 << (31 - priority));                              \
        }


UINT _sch_get_next_task(VOID)
{
    P_TASK_t    p_task;

    // exist ready task
    if (g_kernel.sch.p_ready0->flag)
    {
        INT         priority;
        P_DLIST_t   p_list;

        priority = count_lead_zero(g_kernel.sch.p_ready0->flag);
        p_list   = &(g_kernel.sch.p_ready0->list[priority]);

        p_task = _CO_TYPE(TASK_t, node_task, p_list->p_head);
        dlist_cut_node(&(p_task->node_task));
        READY_FLAG_CLEAR(g_kernel.sch.p_ready0, priority);

        dlist_add_node_at_tail(&(g_kernel.sch.p_ready1->list[priority]),
                               &(p_task->node_task));
        READY_FLAG_SET(g_kernel.sch.p_ready1, priority);

        if (g_kernel.sch.p_ready0 == &(g_kernel.sch.ready[0]))
            p_task->flag &= ~(TASK_FLAG_READY1);
        else
            p_task->flag |= TASK_FLAG_READY1;

        // TODO: switch pready0/pready1
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
    //
    // make a task free
    //
    _sch_make_free(p_task);

    //
    // add task in ready list
    //
    {
        // add task into list
        dlist_add_node_at_tail(&(g_kernel.sch.p_ready0->list[p_task->priority]), 
                               &(p_task->node_task));

        // set flag to indicate added task
        READY_FLAG_SET(g_kernel.sch.p_ready0, p_task->priority);
    }

    if (g_kernel.sch.p_ready0 == &(g_kernel.sch.ready[0]))
        p_task->flag |= (TASK_FLAG_READY | TASK_FLAG_READY1);
    else
        p_task->flag |= TASK_FLAG_READY;
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
    if (p_task->node_task.p_list)
    {
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

        dlist_cut_node(&(p_task->node_task));
    }

    // cut node_timeout of task
    if (p_task->node_timeout.p_list)
    {
        dlist_cut_node(&(p_task->node_timeout));
    }

    p_task->flag = TASK_FLAG_NONE;
}

VOID _sch_change_priority(P_TASK_t p_task)
{
    INT         priority;
    P_READY_t   p_ready;

    if (p_task->flag & TASK_FLAG_CHANGED_PRIORITY)
        return;

    // get ready list
    p_ready  = &(g_kernel.sch.ready[0]);
    if (p_task->flag & TASK_FLAG_READY1)
        p_ready++;

    // get priority
    priority = p_task->priority;

    // remove task in previous priority list
    dlist_cut_node(&(p_task->node_task));
    READY_FLAG_CLEAR(p_ready, priority);

    // add task at new priority list
    dlist_add_node_at_tail(&(p_ready->list[0]),
                           &(p_task->node_task));
    READY_FLAG_SET(p_ready, 0);
    
    // set flag to indicate changed priority
    p_task->flag |= TASK_FLAG_CHANGED_PRIORITY;
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

