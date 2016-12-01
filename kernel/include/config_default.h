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

#ifndef __CONFIG_DEFAULT_H__
#define __CONFIG_DEFAULT_H__

#include "type.h"
#include "config_user.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


/*======================================================================================*/
/*
    Setting for Default
*/
/*======================================================================================*/

#ifndef _MAXIMUM_PRIORITY
#define _MAXIMUM_PRIORITY               1
#endif

#ifndef _ENABLE_FAIR_SCHEDULING
#define _ENABLE_FAIR_SCHEDULING         0
#endif


#ifndef _IMPLEMENT_CLZ_BY_SW
#define _IMPLEMENT_CLZ_BY_SW            1
#endif

#ifndef _ENABLE_STACK_TRACE
#define _ENABLE_STACK_TRACE             1
#endif

#ifndef _ENABLE_USE_SVC_CALL
#define _ENABLE_USE_SVC_CALL            0
#endif

#ifndef _SYSTEM_TICK_TIME
#define _SYSTEM_TICK_TIME               10
#endif

#ifndef _STACK_GROWS_DOWN
#define _STACK_GROWS_DOWN               1
#endif

#ifndef _ENABLE_KERNEL_LOG
#define _ENABLE_KERNEL_LOG              1
#endif

#ifndef _ENABLE_KERNEL_LOG_TASK
#define _ENABLE_KERNEL_LOG_TASK         1
#endif

#ifndef _TASK_IDLE_STACK_SIZE
#define _TASK_IDLE_STACK_SIZE           96
#endif

#ifndef _PORT_TASK_EXTENSION_
#define _PORT_TASK_EXTENSION_
#endif

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__CONFIG_DEFAULT_H__

