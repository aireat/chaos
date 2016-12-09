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

#include "chaos.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

DEF_TASK(task_main, 1, 64);
DEF_TASK(task_test, 1, 64);

INT task_main_proc(VOID *p_arg);
INT task_test_proc(VOID *p_arg);

#if   defined (WIN32)
    int win_main(void)
#else
    int main(void)
#endif
{
    chaos_start(&task_main,
                task_main_proc,
                NULL);

    return 0;
}

#define TEST_API_BLOCK          0
#define TEST_API_YIELD          0
#define TEST_API_SLEEP          1

INT task_main_proc(VOID *p_arg)
{
    task_create(&task_test, task_test_proc, NULL);

    while (1)
    {
#if     (TEST_API_BLOCK)
        {
            task_ready(&task_test);
            task_block(&task_main);
        }
#elif   (TEST_API_YIELD)
        {
            task_yield();
        }
#elif   (TEST_API_SLEEP)
        {
            task_sleep(500);
        }
#endif
    }
}

INT task_test_proc(VOID *p_arg)
{
    while(1)
    {
#if     (TEST_API_BLOCK)
        {
            task_ready(&task_main);
            task_block(&task_test);
        }
#elif   (TEST_API_YIELD)
        {
            task_yield();
        }
#elif   (TEST_API_SLEEP)
        {
            task_sleep(600);
        }
#endif
    }
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

