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

#include "count_lead_zero.h"


#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

#ifdef __IMPLE_CLZ_SW__

/*
------------------------------------------------------------------------------------------
  return               8 bit value
------------------------------------------------------------------------------------------
    0       1000 0000 
    1       0100 0000 
    2       0010 0000 
    3       0001 0000 
    4       0000 1000 
    5       0000 0100 
    6       0000 0010 
    7       0000 0001 
------------------------------------------------------------------------------------------
*/

CONST INT8  g_byte_clz_table[256] =
{
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3,	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

INT  count_lead_zero(UINT32 value)
{
    INT     byte_value, i, add;

#if 1
    for (i = 24, add = 0; i >= 0; i -= 8, add += 8)
    {
        byte_value = ((value >> i) & 0x000000FF);
        if (byte_value)
            return (g_byte_clz_table[byte_value] + add);
    }
#else
    //
    // check 0xFF000000
    //
    byte_value = ((value >> 24) & 0xFF);
    if (byte_value)
        return (g_byte_clz_table[byte_value]);

    //
    // check 0x00FF0000
    //
    byte_value = ((value >> 16) & 0xFF);
    if (byte_value)
        return (g_byte_clz_table[byte_value] + 8);

    //
    // check 0x0000FF00
    //
    byte_value = ((value >>  8) & 0xFF);
    if (byte_value)
        return (g_byte_clz_table[byte_value] + 16);

    //
    // check 0x000000FF
    //
    byte_value = ((value      ) & 0xFF);
    if (byte_value)
        return (g_byte_clz_table[byte_value] + 24);
#endif

    return 32;
}

#endif //__IMPLE_CLZ_SW__

#ifdef __IMPLE_CLZ_ARM__

INT  count_lead_zero(UINT32 value)
{
    return (INT)__clz(value);
}

#endif // __IMPLE_CLZ_ARM__


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

