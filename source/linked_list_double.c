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

#include "linked_list.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


VOID dlist_init_list(P_DLIST_t p_list)
{
    p_list->p_head = NULL;
    p_list->p_tail = NULL;
}


VOID dlist_add_node_at_head(P_DLIST_t p_list, P_DNODE_t p_add_node)
{
    P_DNODE_t   p_head_node = p_list->p_head;

    if (p_head_node)
    {
        p_add_node->p_next = p_head_node;
        p_add_node->p_prev = NULL;

        p_head_node->p_prev = p_add_node;

        p_list->p_head = p_add_node;
    }
    else
    {
        p_add_node->p_next = NULL;
        p_add_node->p_prev = NULL;

        p_list->p_head = p_add_node;
        p_list->p_tail = p_add_node;
    }

    p_add_node->p_list = p_list;
}


VOID dlist_add_node_at_tail(P_DLIST_t p_list, P_DNODE_t p_add_node)
{
    P_DNODE_t   p_tail_node = p_list->p_tail;

    if (p_tail_node)
    {
        p_add_node->p_next = NULL;
        p_add_node->p_prev = p_tail_node;

        p_tail_node->p_next = p_add_node;

        p_list->p_tail = p_add_node;
    }
    else
    {
        p_add_node->p_next = NULL;
        p_add_node->p_prev = NULL;

        p_list->p_head = p_add_node;
        p_list->p_tail = p_add_node;
    }

    p_add_node->p_list = p_list;
}


VOID dlist_cut_node(P_DNODE_t p_cut_node)
{
    P_DLIST_t   p_list = (P_DLIST_t) p_cut_node->p_list;

    if (p_list)
    {
        P_DNODE_t   p_next_node = p_cut_node->p_next;
        P_DNODE_t   p_prev_node = p_cut_node->p_prev;

        if (p_prev_node)
            p_prev_node->p_next = p_cut_node->p_next;

        if (p_next_node)
            p_next_node->p_prev = p_cut_node->p_prev;

        if (p_cut_node == p_list->p_head)
            p_list->p_head = p_next_node;

        if (p_cut_node == p_list->p_tail)
            p_list->p_tail = p_prev_node;

        p_cut_node->p_next = NULL;
        p_cut_node->p_prev = NULL;
        p_cut_node->p_list = NULL;
    }
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

