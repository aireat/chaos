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

#include "co_port.h"
#include "co_kernel.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

extern BOOL    g_system_started;
extern VOID  _windows_event_wait(VOID *handle);

RESULT_t _port_svc_task_create(P_TASK_t p_task)
{
    if (g_system_started == TRUE)
    {
        P_TASK_t    p_cur_task = g_kernel.task_curr_running;

        // wait next scheduling
        _windows_event_wait(p_cur_task->_h_thread_event);
    }
    else
    {

    }

    return RESULT_SUCCESS;
}

RESULT_t _port_svc_task_delete(P_TASK_t p_task)
{
    P_TASK_t    p_cur_task = g_kernel.task_curr_running;

    // wait next scheduling
    _windows_event_wait(p_cur_task->_h_thread_event);

    return RESULT_SUCCESS;
}

RESULT_t _port_svc_task_ready(P_TASK_t p_task, INT priority)
{
    P_TASK_t    p_cur_task = g_kernel.task_curr_running;

    // wait next scheduling
    _windows_event_wait(p_cur_task->_h_thread_event);

    return RESULT_SUCCESS;
}

RESULT_t _port_svc_task_block(P_TASK_t p_task, VOID *wait_obj, UINT time_ms)
{
    P_TASK_t    p_cur_task = g_kernel.task_curr_running;

    // wait next scheduling
    _windows_event_wait(p_cur_task->_h_thread_event);

    return RESULT_SUCCESS;
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

