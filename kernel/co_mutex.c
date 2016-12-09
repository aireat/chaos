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
#include "co_mutex.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

INT _cb_mutex_change(P_MUTEX_t p_mutex)
{
    return 0;
}

RESULT_t _svc_mutex_enter(P_MUTEX_t p_mutex, P_TASK_t p_task)
{
    if (p_mutex->p_owner_task == NULL)
    {
        p_mutex->p_owner_task = p_task;

        return RESULT_SUCCESS;
    }

    if (p_task->priority_cur > p_mutex->p_owner_task->priority_cur)
    {
        _svc_task_ready(p_mutex->p_owner_task, p_task->priority_cur);
    }

    _svc_task_block(p_task, p_mutex, 0);

    return RESULT_SUCCESS;
}

RESULT_t _svc_mutex_leave(P_MUTEX_t p_mutex)
{
    return RESULT_SUCCESS;
}

RESULT_t co_mutex_create(P_MUTEX_t p_mutex)
{
    // init object head
    {
        dlist_init_list(&(p_mutex->obj_head.dlist_wait_tasks));
        p_mutex->obj_head.change_callback = (P_CHANGE_CALLBACK_t) _cb_mutex_change;
        p_mutex->obj_head.change_count = 0;
    }

    // init mutex
    {
        p_mutex->p_owner_task = NULL;
    }

    return RESULT_SUCCESS;
}

RESULT_t co_mutex_enter(P_MUTEX_t p_mutex)
{
    return RESULT_SUCCESS;
}

RESULT_t co_mutex_leave(P_MUTEX_t p_mutex)
{
    return RESULT_SUCCESS;
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

