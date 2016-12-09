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
#include "svc_ringbuff.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

BOOL        g_system_started = FALSE;
BOOL        g_thread_created = FALSE;
svc_buff_t  g_svcbuff;

extern void  _windows_event_set(void *handle);
extern unsigned long _windows_get_tickcount(void);

VOID _windows_system_main(VOID)
{
    BOOL            svc_called = FALSE;
    int             result;
    int             timeout;
    unsigned long   tick_before, tick_after;
    svc_arg_t       svc_call;

    _svcbuff_init(&g_svcbuff, SVC_ARG_COUNT);

    tick_before = _windows_get_tickcount();
    tick_after  = tick_before;

    while(1)
    {
        // re-calculrate tick timeout
        {
            unsigned long   tick_diff;

            tick_diff = tick_after - tick_before;
            timeout = _SYSTEM_TICK_TIME;

            if ((tick_diff < _SYSTEM_TICK_TIME) &&
                (tick_diff > 0))
            {
                timeout = tick_diff;
            }
            else
            {
                tick_before = _windows_get_tickcount();
            }
        }

        // wait event
        {
            result = _svcbuff_wait(&g_svcbuff, timeout);
            tick_after  = _windows_get_tickcount();
        }
        
        // process svc calls
        if (result > 0)
        {
            while (1)
            {
                if (_svcbuff_pop(&g_svcbuff, &svc_call) == 0)
                    break;

                _handler_svc(svc_call.num, svc_call.args);
                svc_called = TRUE;
            }
        }

        //process sytem tick
        if ((tick_after - tick_before) >= _SYSTEM_TICK_TIME)
        {
            _handler_systick();
        }

        // do context switch
        {
            if (g_kernel.task_curr_running != g_kernel.task_next_running)
            {
                g_kernel.task_curr_running = g_kernel.task_next_running;
                _windows_event_set(g_kernel.task_next_running->_h_thread_event);
            }
            else if (svc_called == TRUE)
            {
                _windows_event_set(g_kernel.task_curr_running->_h_thread_event);
            }

            svc_called = FALSE;
        }
    }
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

