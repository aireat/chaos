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

#include "svc_ringbuff.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


void _svcbuff_init(svc_buff_t *p_cb, int size)
{
    p_cb->head = 0;
    p_cb->tail = 0;
    p_cb->size = size;
}


int  _svcbuff_push(svc_buff_t *p_cb, svc_arg_t *p_data)
{
    int     next;

    // Get next index to store a data
    next = p_cb->head + 1;
    if (next >= p_cb->size)
        next = 0;

    // Check the index is available.
    // (head + 1) is equal to tail ==> the buffer is full
    if (next == p_cb->tail)
        return 0;

    // Store the data and update head value
    p_cb->data[p_cb->head] = *p_data;
    p_cb->head = next;

    return 1;
}


int  _svcbuff_pop(svc_buff_t *p_cb, svc_arg_t *p_data)
{
    int     next;
    
    // Check a data is available
    // Head is equal to head ==> the buffer is empty
    if (p_cb->head == p_cb->tail)
        return 0;

    *p_data = p_cb->data[p_cb->tail];

    // Move next index
    next = p_cb->tail + 1;
    if (next >= p_cb->size)
        next = 0;

    p_cb->tail = next;

    return 1;
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
} /* extern "C" */
#endif

