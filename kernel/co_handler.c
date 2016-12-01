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

typedef INT (*P_SVC_FUNC)(UINT arg0, UINT arg1, UINT arg2, UINT arg3);

CONST P_SVC_FUNC  g_svc_func_table[] =
{
    (P_SVC_FUNC) _knl_task_create,
    (P_SVC_FUNC) _knl_task_delete,
    (P_SVC_FUNC) _knl_task_ready,
    (P_SVC_FUNC) _knl_task_block,
};

INT _handler_svc(UINT svc_num, UINT *svc_args)
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
        return g_svc_func_table[svc_num](svc_args[0],
                                         svc_args[1],
                                         svc_args[2],
                                         svc_args[3]);
    }

    return -1;
}

VOID _handler_systick(VOID)
{
    g_kernel.system_tick += _SYSTEM_TICK_TIME;

    //if (g_kernel.task_curr_running == g_kernel.task_idle)
        _knl_do_context_switch();
}



//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

