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
VOID _knl_stack_usage(P_TASK_t p_task);
#endif

VOID _knl_init(VOID)
{
    _co_memset(&g_kernel, 0x00, sizeof(g_kernel));

    g_kernel.sch.p_ready0 = g_kernel.sch.ready;
}

VOID _knl_task_create(P_TASK_t p_task, P_TASK_PROC_t entry_point, VOID *p_arg)
{
    entry_point = 0;
    p_arg = NULL;
    
    slist_add_node_at_tail(&(g_kernel.slist_task), &(p_task->snode_create));

    _sch_make_ready(p_task, p_task->priority);
}

VOID _knl_task_delete(P_TASK_t p_task)
{
    _sch_make_free(p_task);
    
    slist_cut_node(&(g_kernel.slist_task), &(p_task->snode_create));
}

#if (_ENABLE_STACK_TRACE)
VOID _knl_stack_usage(P_TASK_t p_task)
{
//#if (_STACK_GROWS == GROW_DOWN)
    {
        while (*(p_task->stack_size_trace)-- != 0xCCCCCCCC)
            p_task->stack_size_usage += 4;
    }
//#else
    {
        while (*(p_task->stack_size_trace)++ != 0xCCCCCCCC)
            p_task->stack_size_usage += 4;
    }    
//#endif

}
#endif

VOID _knl_check_changes(VOID)
{
    // check timeout node
    if (g_kernel.system_tick != g_kernel.system_tick_check)
    {
        P_TASK_t    p_task;
        P_DNODE_t   p_dnoe_timeout = g_kernel.sch.timeout.p_head;

        while (p_dnode_timeout)
        {
            p_task = _CO_TYPE(TASK_t, dnode_timeout, p_dnode_timeout);
            p_dnode_timeout = p_dnode_timeout->p_next;

            
        }

        g_kernel.system_tick_check = g_kernel.system_tick;
    }

    // check resources
    // TODO : ring-buffer machanism
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

