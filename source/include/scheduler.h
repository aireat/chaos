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

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "config.h"
#include "chaos.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


typedef struct _READY_
{
    INT             flag;
    DLIST_t         list[_MAXIMUM_PRIORITY];

} READY_t, *P_READY_t;

typedef struct _SCHEDULER_
{
    DLIST_t         timeout;

#if (_ENABLE_FAIR_SCHEDULING)
    READY_t         ready[2];
    P_READY_t       p_ready0, p_ready1;
#else
    READY_t         ready[1];
    P_READY_t       p_ready0;
#endif


} SCHEDULER_t, *P_SCHEDULER_t;


UINT _sch_get_next_task(VOID);
VOID _sch_make_ready(P_TASK_t p_task);
//VOID _sch_make_block(P_TASK_t p_task, UINT wait_obj, UINT time_ms);
VOID _sch_make_free(P_TASK_t p_task);
VOID _sch_change_priority(P_TASK_t p_task);


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__SCHEDULER_H__

