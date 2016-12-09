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
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

#define SIZE_DLOG_BUFFER        96
#define LOG_MAX_CLASS_LENGTH    8


VOID _port_log_printf(CONST CHAR *p_class, CONST CHAR *p_format, ...)
{
    va_list     args;
    INT         size, count;
    CHAR        _log_buffer[SIZE_DLOG_BUFFER];
    
    {
        size = 0;

        {
            //size += sprintf(&_log_buffer[size], " %08X ", co_get_tick_count());
            size += sprintf(&_log_buffer[size], " %08X ", 0); 
        }

        {
            CHAR        *pdest;
            CONST CHAR  *psrc;
            int         i;

            psrc  = p_class;
            pdest = &_log_buffer[size];

            for (i = 0; i < LOG_MAX_CLASS_LENGTH; i++)
            {
                if (*psrc)
                    *pdest++ = *psrc++;
                else
                    *pdest++ = ' ';
            }

            size += LOG_MAX_CLASS_LENGTH;
            _log_buffer[size++] = ' ';
        }

        // add message
        {
            va_start(args, p_format);

            count = vsnprintf(&_log_buffer[size], (SIZE_DLOG_BUFFER-2-size), p_format, args);

            if ((count > 0) && (count < (SIZE_DLOG_BUFFER-size-2)))
            {
                size += count;
                _log_buffer[size++] = 0x0A;
                _log_buffer[size++] = 0x0D;
                //            size++;
            }
            else
            {
                size = SIZE_DLOG_BUFFER;
                _log_buffer[SIZE_DLOG_BUFFER-2] = 0x0A;
                _log_buffer[SIZE_DLOG_BUFFER-1] = 0x0D;
            }

            va_end(args);
        }

        _log_buffer[size] = 0x00;
    }

    {
        printf("%s", _log_buffer);
    }

}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

