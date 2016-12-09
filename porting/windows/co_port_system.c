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

extern BOOL        g_system_started;
extern BOOL        g_thread_created;

extern void  _windows_system_main(void);
extern void  _windows_event_set(void *handle);
extern int   _windows_event_wait(void *handle, unsigned int m_seconds);

VOID _port_system_init(VOID)
{
    g_system_started = FALSE;
}

VOID _port_system_start(VOID)
{
    g_system_started = TRUE;

    _windows_system_main();
}

VOID _windows_thread_entry(VOID *p_arg)
{
    P_TASK_t        p_task = (P_TASK_t) p_arg;
    P_TASK_PROC_t   entry_point = (P_TASK_PROC_t) p_task->_p_entry_point;

    // start thread
    _task_entry_point(p_task, entry_point, p_task->_p_arg, 0x00);
}

VOID _port_task_created(P_TASK_t p_task)
{
    g_thread_created = TRUE;

    // wait signal to start thread
    _windows_event_wait(p_task->_h_thread_event, 0xFFFFFFFF);
}

VOID _port_do_context_switch(VOID)
{
    // nothing to do
}

void _windows_do_context_switch(void)
{
    if (g_kernel.task_curr_running != g_kernel.task_next_running)
    {
        _windows_event_set(g_kernel.task_next_running->_h_thread_event);

        g_kernel.task_curr_running = g_kernel.task_next_running;
    }
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

