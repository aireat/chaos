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

void* ThreadProc(void *arg);

VOID _port_stack_set_up(P_TASK_t p_task, P_TASK_PROC_t entry_point, VOID *p_arg)
{
    int                 result;
    pthread_attr_t      attr;

    p_task->_p_entry_point = entry_point;
    p_task->_p_arg = p_arg;

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // create thread as suspend
    result = pthread_create(&(p_task->_thread),     /* thread           */
                            NULL,                   /* attr             */
                            ThreadProc,             /* start_routine    */
                            (void*)p_task);         /* arg              */
}

void* ThreadProc(void *arg)
{
    P_TASK_t        p_task = (P_TASK_t) arg;
    P_TASK_PROC_t   entry_point = (P_TASK_PROC_t) p_task->_p_entry_point;

    _task_entry_point(p_task, entry_point, p_task->_p_arg, 0x00);
    
    return NULL;
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

