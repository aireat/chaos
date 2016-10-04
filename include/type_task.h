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

#ifndef __TYPE_TASK_H__
#define __TYPE_TASK_H__

#include "type.h"
#include "type_linked_list.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

#define TASK_FLAG_NONE                  0
#define TASK_FLAG_READY                 (1 <<  0)
#define TASK_FLAG_READY1                (1 <<  1)
#define TASK_FLAG_CHANGED_PRIORITY      (1 <<  2) 
#define TASK_FALG_BLOCK                 (1 <<  3)
#define TASK_FLAG_TIMEOUT               (1 <<  4)
#define TASK_FLAG_TIMEOUT_OVEFLOW       (1 <<  5)

typedef struct _TASK_
{
    UINT            stack_pos;          /*!< @brief Stack pointer                       */

    SNODE_t         snode_create;

    DNODE_t         node_task;
    DNODE_t         node_timeout;

    UINT8           priority;

    UINT            result;

    VOID           *p_stack;

} TASK_t, *P_TASK_t;

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__TYPE_TASK_H__

