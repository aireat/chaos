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

#include "co_linked_list.h"

#ifdef __cplusplus
    extern "C" {
#endif

//////////////////////////////////////  < BEGIN >  ///////////////////////////////////////


VOID slist_init_list(P_SLIST_t p_list)
{
    p_list->p_head = NULL;
    p_list->p_tail = NULL;
}


VOID slist_add_node_at_head(P_SLIST_t p_list, P_SNODE_t p_add_node)
{
    P_SNODE_t   p_head_node = p_list->p_head;

    if (p_head_node)
    {
        p_add_node->p_next = p_head_node;

        p_list->p_head = p_add_node;
    }
    else
    {
        p_add_node->p_next = NULL;

        p_list->p_head = p_add_node;
        p_list->p_tail = p_add_node;
    }
}


VOID slist_add_node_at_tail(P_SLIST_t p_list, P_SNODE_t p_add_node)
{
    P_SNODE_t   p_tail_node = p_list->p_tail;

    p_add_node->p_next = NULL;

    if (p_tail_node)
    {
        p_tail_node->p_next = p_add_node;

        p_list->p_tail = p_add_node;
    }
    else
    {
        p_list->p_head = p_add_node;
        p_list->p_tail = p_add_node;
    }
}


VOID slist_cut_node(P_SLIST_t p_list, P_SNODE_t p_cut_node)
{
    P_SNODE_t   p_curr_node = p_list->p_head;
    P_SNODE_t   p_prev_node = NULL;

    while (p_curr_node)
    {
        if (p_curr_node == p_cut_node)
        {
            if (p_prev_node)
                p_prev_node->p_next = p_cut_node->p_next;

            if (p_cut_node == p_list->p_head)
                p_list->p_head = p_cut_node->p_next;

            if (p_cut_node == p_list->p_tail)
                p_list->p_tail = p_prev_node;

            break;
        }
        else
        {
            p_prev_node = p_curr_node;
            p_curr_node = p_curr_node->p_next;
        }
    }

    p_cut_node->p_next = NULL;
}


//////////////////////////////////////  <  END  >  ///////////////////////////////////////

#ifdef __cplusplus
    } /* extern "C" */
#endif

