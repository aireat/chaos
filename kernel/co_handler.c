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

typedef INT (*P_SVC_FUNC)(VOID *arg0, VOID *arg1, VOID *arg2, VOID *arg3);


CONST P_SVC_FUNC  g_svc_func_table[] =
{
    (P_SVC_FUNC) _svc_task_create,
    (P_SVC_FUNC) _svc_task_delete,
    (P_SVC_FUNC) _svc_task_ready,
    (P_SVC_FUNC) _svc_task_block,
};

INT _handler_svc(UINT svc_num, VOID *svc_args[4])
{
    // - Stacked R0   = svc_args[0]
    // - Stacked R1   = svc_args[1]
    // - Stacked R2   = svc_args[2]
    // - Stacked R3   = svc_args[3]
    // - Stacked R12  = svc_args[4]
    // - Stacked LR   = svc_args[5]
    // - Stacked PC   = svc_args[6]
    // - Stacked xPSR = svc_args[7]

    if (svc_num < _CO_ARRAY_COUNT(g_svc_func_table))
    {
        INT     result;

        result = g_svc_func_table[svc_num](svc_args[0],
                                           svc_args[1],
                                           svc_args[2],
                                           svc_args[3]);

        if (!(g_kernel.task_curr_running->flag & TASK_FLAG_READY))
        {
            _knl_check_changes();
            _knl_do_context_switch();
        }

        return result;
    }

    return -1;
}



VOID _handler_systick(VOID)
{
    // update system tick count
    g_kernel.system_tick += _SYSTEM_TICK_TIME;

    _knl_check_changes();

    // yield schedule
    if (g_kernel.task_curr_running == g_kernel.task_idle)
    {
        _knl_do_context_switch();
    }
}



//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

