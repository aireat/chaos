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

#ifndef __MACROS_H__
#define __MACROS_H__

#include "type.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

/*======================================================================================*/
/*
    Get size aligned by boundary
*/
/*======================================================================================*/
#ifndef _CO_ALIGN
#define _CO_ALIGN(value, align)         (((value)+((align)-1))&~((align)-1))
#endif

/*======================================================================================*/
/*
    Get offset from start address of structure
*/
/*======================================================================================*/
#ifndef _CO_OFFSET
#define _CO_OFFSET(type, member)        ((long)&(((type*)0)->member))
#endif


/*======================================================================================*/
/*
    Cast address from a member of type to start of type
*/
/*======================================================================================*/
#ifndef _CO_TYPE
#define _CO_TYPE(type, member, addr)    (type*)(((char*)(addr))-(long)&(((type*)0)->member))
#endif


/*======================================================================================*/
/*
    Get maximum value
*/
/*======================================================================================*/
#ifndef _CO_MAX
#define _CO_MAX(x,y)                    (((UINT)(x)>(UINT)(y))?(x):(y))
#endif


/*======================================================================================*/
/*
    Get minimum value
*/
/*======================================================================================*/
#ifndef _CO_MIN
#define _CO_MIN(x,y)                    (((UINT)(x)>(UINT)(y))?(y):(x))
#endif

/*======================================================================================*/
/*
    Get count of array elements
*/
/*======================================================================================*/
#ifndef _CO_ARRAY_COUNT
#define _CO_ARRAY_COUNT(arr)            (sizeof(arr)/sizeof(arr[0]))
#endif


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__MACROS_H__

