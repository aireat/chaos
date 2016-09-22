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

#ifndef __COUNT_LEAD_ZERO_H__
#define __COUNT_LEAD_ZERO_H__

#include "type.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////

#if   defined (__CLZ_ARM__)
#define __IMPLE_CLZ_ARM__
#else
#define __IMPLE_CLZ_SW__
#endif

/*======================================================================================*/
/*
    Count lead zero function
*/
/*======================================================================================*/
/*
------------------------------------------------------------------------------------------
  return               32 bit value
------------------------------------------------------------------------------------------
    0       1000 0000 0000 0000 0000 0000 0000 0000 
    1       0100 0000 0000 0000 0000 0000 0000 0000 
    2       0010 0000 0000 0000 0000 0000 0000 0000 
    3       0001 0000 0000 0000 0000 0000 0000 0000 
    4       0000 1000 0000 0000 0000 0000 0000 0000 
    5       0000 0100 0000 0000 0000 0000 0000 0000 
    6       0000 0010 0000 0000 0000 0000 0000 0000 
    7       0000 0001 0000 0000 0000 0000 0000 0000 
------------------------------------------------------------------------------------------
    8       0000 0000 1000 0000 0000 0000 0000 0000 
    9       0000 0000 0100 0000 0000 0000 0000 0000 
   10       0000 0000 0010 0000 0000 0000 0000 0000 
   11       0000 0000 0001 0000 0000 0000 0000 0000 
   12       0000 0000 0000 1000 0000 0000 0000 0000 
   13       0000 0000 0000 0100 0000 0000 0000 0000 
   14       0000 0000 0000 0010 0000 0000 0000 0000 
   15       0000 0000 0000 0001 0000 0000 0000 0000 
------------------------------------------------------------------------------------------
   16       0000 0000 0000 0000 1000 0000 0000 0000 
   17       0000 0000 0000 0000 0100 0000 0000 0000 
   18       0000 0000 0000 0000 0010 0000 0000 0000 
   19       0000 0000 0000 0000 0001 0000 0000 0000 
   20       0000 0000 0000 0000 0000 1000 0000 0000 
   21       0000 0000 0000 0000 0000 0100 0000 0000 
   22       0000 0000 0000 0000 0000 0010 0000 0000 
   23       0000 0000 0000 0000 0000 0001 0000 0000 
------------------------------------------------------------------------------------------
   24       0000 0000 0000 0000 0000 0000 1000 0000 
   25       0000 0000 0000 0000 0000 0000 0100 0000 
   26       0000 0000 0000 0000 0000 0000 0010 0000 
   27       0000 0000 0000 0000 0000 0000 0001 0000 
   28       0000 0000 0000 0000 0000 0000 0000 1000 
   29       0000 0000 0000 0000 0000 0000 0000 0100 
   30       0000 0000 0000 0000 0000 0000 0000 0010 
   31       0000 0000 0000 0000 0000 0000 0000 0001 
------------------------------------------------------------------------------------------
   32       0000 0000 0000 0000 0000 0000 0000 0000 
------------------------------------------------------------------------------------------
*/

INT  count_lead_zero(UINT32 value);


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__COUNT_LEAD_ZERO_H__

