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

#ifndef __CO_LINKED_LIST_H__
#define __CO_LINKED_LIST_H__

#include "type.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


/*======================================================================================*/
/*
    Single linked list (not circle)
*/
/*======================================================================================*/

typedef struct _SNODE_
{
    struct _SNODE_         *p_next;

} SNODE_t, *P_SNODE_t;


typedef struct _SLIST_
{
    P_SNODE_t               p_head;
    P_SNODE_t               p_tail;

} SLIST_t, *P_SLIST_t;


VOID slist_init_list(P_SLIST_t p_list);
VOID slist_init_node(P_SNODE_t p_init_node);
VOID slist_add_node_at_head(P_SLIST_t p_list, P_SNODE_t p_add_node);
VOID slist_add_node_at_tail(P_SLIST_t p_list, P_SNODE_t p_add_node);
VOID slist_cut_node(P_SLIST_t p_list, P_SNODE_t p_cut_node);


/*======================================================================================*/
/*
    Double linked list (not circle)
*/
/*======================================================================================*/

typedef struct _DNODE_
{
    struct _DNODE_         *p_next;
    struct _DNODE_         *p_prev;

    struct _DLIST_         *p_list;

} DNODE_t, *P_DNODE_t;


typedef struct _DLIST_
{
    struct _DNODE_         *p_head;
    struct _DNODE_         *p_tail;

} DLIST_t, *P_DLIST_t;


VOID dlist_init_list(P_DLIST_t p_list);
VOID dlist_init_node(P_DNODE_t p_init_node);
VOID dlist_add_node_at_head(P_DLIST_t p_list, P_DNODE_t p_add_node);
VOID dlist_add_node_at_tail(P_DLIST_t p_list, P_DNODE_t p_add_node);
VOID dlist_cut_node(P_DNODE_t p_cut_node);


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif //__CO_LINKED_LIST_H__

