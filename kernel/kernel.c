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


VOID __knl_init(VOID)
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

    _knl_do_context_switch();

    return RESULT_SUCCESS;
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

