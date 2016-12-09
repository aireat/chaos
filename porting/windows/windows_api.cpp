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

#include "stdafx.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

extern BOOL g_thread_created;

extern VOID _windows_thread_entry(VOID *p_arg);

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    _windows_thread_entry(lpParameter);
    
    return 0;
}

void* _windows_thread_create(void *p_arg, const char *p_name)
{
    HANDLE  h_thread;
    DWORD   threadID;

    g_thread_created = FALSE;

    // create thread as suspend
    h_thread = CreateThread(NULL,                   /* lpThreadAttributes   */
                            0,                      /* dwStackSize          */
                            ThreadProc,             /* lpStartAddress       */
                            (LPVOID)p_arg,          /* lpParameter          */
                            0,       /* dwCreationFlags      */
                            &threadID);             /* lpThreadId           */

    // waiting until creating thread
    {
        while (g_thread_created == FALSE)
        {
            Sleep(100);
        }
    }

    // set thread name
    {
        const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
        typedef struct tagTHREADNAME_INFO
        {
           DWORD dwType;        // Must be 0x1000.
           LPCSTR szName;       // Pointer to name (in user addr space).
           DWORD dwThreadID;    // Thread ID (-1=caller thread).
           DWORD dwFlags;       // Reserved for future use, must be zero.
        } THREADNAME_INFO;
#pragma pack(pop)

        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = p_name;
        info.dwThreadID = threadID;
        info.dwFlags = 0;

#pragma warning(push)
#pragma warning(disable: 6320 6322)

        Sleep(10);

        __try
        {
           RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
        }

        Sleep(10);

#pragma warning(pop)
    }

    return (VOID*) h_thread;
}

void* _windows_event_create(int bManualReset)
{
    HANDLE  h_event;

    h_event = CreateEvent(NULL, bManualReset, FALSE, NULL);

    return (void*) h_event;
}

void _windows_event_set(void *handle)
{
    SetEvent((HANDLE)handle);
}

int _windows_event_wait(void *handle, unsigned int m_seconds)
{
    DWORD   result;

    {
        result = WaitForSingleObject((HANDLE)handle, m_seconds);
        if (result == WAIT_OBJECT_0)
            return 1;

        if (result == WAIT_TIMEOUT)
            return 0;

        return -1;
    }
}

unsigned long _windows_get_tickcount(void)
{
    return (unsigned long) GetTickCount();
}

//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

