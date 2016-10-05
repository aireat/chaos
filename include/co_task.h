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

#ifndef __TASK_H__
#define __TASK_H__

#include "type.h"

#include "co_macros.h"
#include "co_linked_list.h"
#include "co_result.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

/*======================================================================================*/
/*
    Creation Macro of TASK_t
*/
/*======================================================================================*/
#define DEF_TASK(name, priority, stack_size)                                            \
        UINT8   name##_stack[_CO_ALIGN(stack_size, 4)];                                 \
        TASK_t  name =                                                                  \
        {                                                                               \
            0,                          /* stack_pos                */                  \
            #name,                      /* p_name                   */                  \
            { NULL },                   /* snode_create             */                  \
            { NULL, NULL, NULL },       /* dnode_task               */                  \
            { NULL, NULL, NULL },       /* dnode_timeout            */                  \
            0,                          /* flag                     */                  \
            priority,                   /* priority                 */                  \
            0,                          /* result                   */                  \
            _CO_ALIGN(stack_size, 4),   /* stack_size               */                  \
            (UINT*)name##_stack,        /* stack_addr               */                  \
        }


/*======================================================================================*/
/*
    Definition of TASK's flag
*/
/*======================================================================================*/

#define TASK_FLAG_NONE                  0
#define TASK_FLAG_READY                 (1 <<  0)
#define TASK_FLAG_READY1                (1 <<  1)
#define TASK_FLAG_CHANGED_PRIORITY      (1 <<  2) 
#define TASK_FALG_BLOCK                 (1 <<  3)
#define TASK_FLAG_TIMEOUT               (1 <<  4)
#define TASK_FLAG_TIMEOUT_OVEFLOW       (1 <<  5)


/*======================================================================================*/
/*
    Control block of Task 
*/
/*======================================================================================*/

typedef struct _TASK_
{
    UINT            stack_pos;          /*!< @brief Stack pointer                       */

    CHAR           *name;

    SNODE_t         snode_create;
    DNODE_t         dnode_task;
    DNODE_t         dnode_timeout;

    INT             flag;

    UINT8           priority;

    UINT            result;

    INT             stack_size;
    UINT           *stack_addr;

} TASK_t, *P_TASK_t;


/*======================================================================================*/
/*
    The entry point of thread creating
*/
/*======================================================================================*/

typedef INT (*P_TASK_PROC_t)(VOID *p_arg);

RESULT_t task_create(P_TASK_t p_task, P_TASK_PROC_t entry_point, VOID *p_arg);

RESULT_t task_delete(P_TASK_t p_task);

//VOID task_block(P_TASK_t p_task);

//VOID task_ready(P_TASK_t p_task);

//VOID task_sleep(P_TASK_t p_task);


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__TASK_H__

