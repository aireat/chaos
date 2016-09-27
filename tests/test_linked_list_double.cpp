

#include "CppUTest/TestHarness.h"

#include "linked_list.h"

enum
{
    NODE_TEMP           = 0,
    NODE_FIRST          ,
    NODE_MID_1          ,
    NODE_MID_2          ,
    NODE_LAST           ,
    NODE_COUNT          ,
};

TEST_GROUP(double_linked_list)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(double_linked_list, T01)
{
    DLIST_t     dlist = { (P_DNODE_t)1, };

    dlist_init_list(&dlist);

    LONGS_EQUAL(NULL, dlist.p_head);
    LONGS_EQUAL(NULL, dlist.p_tail);
}

TEST(double_linked_list, T02_00)
{
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);
    dlist_add_node_at_head(&dlist, &nodes[NODE_FIRST]);

    LONGS_EQUAL(NULL, nodes[NODE_FIRST].p_next);
    LONGS_EQUAL(NULL, nodes[NODE_FIRST].p_prev);

    LONGS_EQUAL(&nodes[NODE_FIRST], dlist.p_head);
    LONGS_EQUAL(&nodes[NODE_FIRST], dlist.p_tail);        
}


TEST(double_linked_list, T02_01)
{
    INT         i;
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);
    dlist_add_node_at_head(&dlist, &nodes[NODE_TEMP]);

    // add node at head
    for (i = NODE_FIRST; i < NODE_COUNT; i++)
    {
        dlist_add_node_at_head(&dlist, &nodes[i]);

        LONGS_EQUAL(&nodes[i-1], nodes[i].p_next);
        LONGS_EQUAL(NULL, nodes[i].p_prev);

        LONGS_EQUAL(&nodes[i], dlist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_tail);
    }
}

TEST(double_linked_list, T03_00)
{
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);
    dlist_add_node_at_tail(&dlist, &nodes[NODE_LAST]);

    LONGS_EQUAL(&nodes[NODE_LAST], dlist.p_head);
    LONGS_EQUAL(&nodes[NODE_LAST], dlist.p_tail);        
}


TEST(double_linked_list, T03_01)
{
    INT         i;
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);
    dlist_add_node_at_tail(&dlist, &nodes[NODE_TEMP]);

    // add node at head
    for (i = NODE_FIRST; i < NODE_COUNT; i++)
    {
        dlist_add_node_at_tail(&dlist, &nodes[i]);

        LONGS_EQUAL(NULL, nodes[i].p_next);
        LONGS_EQUAL(&nodes[i-1], nodes[i].p_prev);

        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_head);
        LONGS_EQUAL(&nodes[i], dlist.p_tail);
    }
}


TEST(double_linked_list, T04_00)
{
    INT         i;
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        dlist_add_node_at_head(&dlist, &nodes[i]);
    }

    // cut node forward
    for (i = NODE_COUNT-1; i > 0; i--)
    {
        dlist_cut_node(&dlist, &nodes[i]);

        LONGS_EQUAL(&nodes[i-1], dlist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_tail);
    }
}

TEST(double_linked_list, T04_01)
{
    INT         i;
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        dlist_add_node_at_head(&dlist, &nodes[i]);
    }    

    // cut node backward
    for (i = 1; i < NODE_COUNT-1; i++)
    {
        dlist_cut_node(&dlist, &nodes[i]);

        LONGS_EQUAL(&nodes[NODE_COUNT-1], dlist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_tail);
    }

    // cut last node except temp node
    {
        dlist_cut_node(&dlist, &nodes[NODE_COUNT-1]);    

        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_tail);
    }
}


TEST(double_linked_list, T04_02)
{
    INT         i;
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        dlist_add_node_at_tail(&dlist, &nodes[i]);
    }

    // cut node forward
    for (i = 1; i < NODE_COUNT-1; i++)
    {
        dlist_cut_node(&dlist, &nodes[i]);

        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_head);
        LONGS_EQUAL(&nodes[NODE_COUNT-1], dlist.p_tail);
    }

    // cut last node except temp node
    {
        dlist_cut_node(&dlist, &nodes[NODE_COUNT-1]);    

        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_tail);
    }
}

TEST(double_linked_list, T04_03)
{
    INT         i;
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        dlist_add_node_at_tail(&dlist, &nodes[i]);
    }    

    // cut node backward
    for (i = NODE_COUNT-1; i > 0; i--)
    {
        dlist_cut_node(&dlist, &nodes[i]);

        LONGS_EQUAL(&nodes[NODE_TEMP], dlist.p_head);
        LONGS_EQUAL(&nodes[i-1], dlist.p_tail);
    }
}

TEST(double_linked_list, T05_00)
{
    DLIST_t     dlist;
    DNODE_t     nodes[NODE_COUNT];

    dlist_init_list(&dlist);

    dlist_add_node_at_tail(&dlist, &nodes[NODE_FIRST]);
    dlist_cut_node(&dlist, &nodes[NODE_FIRST]);

    LONGS_EQUAL(NULL, nodes[NODE_FIRST].p_next);
    LONGS_EQUAL(NULL, nodes[NODE_FIRST].p_prev);
}

