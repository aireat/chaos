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

#ifndef __CO_TASK_H__
#define __CO_TASK_H__

#include "type.h"

#include "co_macros.h"
#include "co_linked_list.h"
#include "co_result.h"

#include "config_user.h"
#include "config_default.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

/*======================================================================================*/
/*
    Creation Macro of TASK_t
*/
/*======================================================================================*/
#if (_ENABLE_STACK_TRACE)
    #define DEF_TASK(name, priority, stack_size)                                        \
            UINT8   name##_stack[_CO_ALIGN(stack_size, 8)];                             \
            TASK_t  name =                                                              \
            {                                                                           \
                (INT*) name##_stack,        /* stack_addr               */              \
                #name,                      /* p_name                   */              \
                { NULL },                   /* snode_create             */              \
                { NULL, NULL, NULL },       /* dnode_task               */              \
                0,                          /* flag                     */              \
                priority,                   /* priority                 */              \
                _CO_ALIGN(stack_size, 8),   /* scratch                  */              \
                _CO_ALIGN(stack_size, 8),   /* stack_size_total         */              \
                0,                          /* stack_size_usage         */              \
                (INT*) name##_stack,        /* stack_size_trace         */              \
            }

#else
    #define DEF_TASK(name, priority, stack_size)                                        \
            UINT8   name##_stack[_CO_ALIGN(stack_size, 8)];                             \
            TASK_t  name =                                                              \
            {                                                                           \
                (INT*) name##_stack,        /* stack_addr               */              \
                #name,                      /* p_name                   */              \
                { NULL },                   /* snode_create             */              \
                { NULL, NULL, NULL },       /* dnode_task               */              \
                0,                          /* flag                     */              \
                priority,                   /* priority                 */              \
                _CO_ALIGN(stack_size, 8),   /* scratch                  */              \
            }

#endif


/*======================================================================================*/
/*
    Definition of TASK's flag
*/
/*======================================================================================*/

#define TASK_FLAG_NONE                  0
#define TASK_FLAG_READY                 (1 <<  0)
#define TASK_FLAG_READY1                (1 <<  1)
#define TASK_FLAG_CHANGED_PRIORITY      (1 <<  2)
#define TASK_FLAG_ERROR                 (1 <<  3)

#define TASK_FALG_WAIT_OBJECT           (1 <<  4)
#define TASK_FLAG_TIMEOUT               (1 <<  5)

#define TASK_TIME_INFINITE              (0xFFFFFFFF)

typedef enum
{
    TASK_OPT_NONE               = (0),
    TASK_OPT_BLOCKED            = (1 << 0),

} TASK_OPT_t;

/*======================================================================================*/
/*
    Control block of Task 
*/
/*======================================================================================*/

typedef struct _TASK_
{
    INT            *stack_addr;             /*!< @brief Stack pointer                   */
    CHAR           *name;

    SNODE_t         snode_create;
    DNODE_t         dnode_task;

    INT16           flag;
    INT16           priority;
    UINT            scratch;                /* [ scratch usage ]                        */
                                            /*   state  |   mean                        */
                                            /* ---------|------------------------------ */
                                            /*   init   | the size of stack             */
                                            /*  running | remain time slice value       */
                                            /*   block  | timeout value                 */
                                            /*  wake-up | the result of waiting action  */

#if (_ENABLE_STACK_TRACE)
    INT16           stack_size_total;
    INT16           stack_size_usage;
    INT            *stack_size_trace;
#endif

    _PORT_TASK_EXTENSION_

} TASK_t, *P_TASK_t;


/*======================================================================================*/
/*
    The entry point of thread creating
*/
/*======================================================================================*/

typedef INT (*P_TASK_PROC_t)(VOID *p_arg);

RESULT_t task_create(P_TASK_t       p_task,
                     P_TASK_PROC_t  entry_point,
                     VOID          *p_arg,
                     TASK_OPT_t     option_flag);

RESULT_t task_delete(P_TASK_t p_task);

RESULT_t task_block(P_TASK_t p_task);

RESULT_t task_ready(P_TASK_t p_task);

RESULT_t task_yield(VOID);

RESULT_t task_sleep(UINT millisecond);


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__CO_TASK_H__

