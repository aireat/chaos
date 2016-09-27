

#include "CppUTest/TestHarness.h"

#include "linked_list.h"

enum
{
    NODE_TEMP           = 0,
    NODE_FIRST          ,
    NODE_MID_1          ,
    NODE_MID_2          ,
    NODE_LAST           ,
    NODE_COUNT          
};

TEST_GROUP(single_linked_list)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(single_linked_list, T01)
{
    SLIST_t     slist = { (P_SNODE_t)1, 0 };

    slist_init_list(&slist);

    LONGS_EQUAL(NULL, slist.p_head);
    LONGS_EQUAL(NULL, slist.p_tail);
}

TEST(single_linked_list, T02_00)
{
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);
    slist_add_node_at_head(&slist, &nodes[NODE_FIRST]);

    LONGS_EQUAL(NULL, nodes[NODE_FIRST].p_next);

    LONGS_EQUAL(&nodes[NODE_FIRST], slist.p_head);
    LONGS_EQUAL(&nodes[NODE_FIRST], slist.p_tail);        
}


TEST(single_linked_list, T02_01)
{
    INT         i;
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);
    slist_add_node_at_head(&slist, &nodes[NODE_TEMP]);

    // add node at head
    for (i = NODE_FIRST; i < NODE_COUNT; i++)
    {
        slist_add_node_at_head(&slist, &nodes[i]);

        LONGS_EQUAL(&nodes[i-1], nodes[i].p_next);

        LONGS_EQUAL(&nodes[i], slist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_tail);
    }
}

TEST(single_linked_list, T03_00)
{
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);
    slist_add_node_at_tail(&slist, &nodes[NODE_LAST]);

    LONGS_EQUAL(&nodes[NODE_LAST], slist.p_head);
    LONGS_EQUAL(&nodes[NODE_LAST], slist.p_tail);        
}


TEST(single_linked_list, T03_01)
{
    INT         i;
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);
    slist_add_node_at_tail(&slist, &nodes[NODE_TEMP]);

    // add node at head
    for (i = NODE_FIRST; i < NODE_COUNT; i++)
    {
        slist_add_node_at_tail(&slist, &nodes[i]);

        LONGS_EQUAL(NULL, nodes[i].p_next);

        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_head);
        LONGS_EQUAL(&nodes[i], slist.p_tail);
    }
}


TEST(single_linked_list, T04_00)
{
    INT         i;
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        slist_add_node_at_head(&slist, &nodes[i]);
    }

    // cut node forward
    for (i = NODE_COUNT-1; i > 0; i--)
    {
        slist_cut_node(&slist, &nodes[i]);

        LONGS_EQUAL(&nodes[i-1], slist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_tail);
    }
}

TEST(single_linked_list, T04_01)
{
    INT         i;
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        slist_add_node_at_head(&slist, &nodes[i]);
    }    

    // cut node backward
    for (i = 1; i < NODE_COUNT-1; i++)
    {
        slist_cut_node(&slist, &nodes[i]);

        LONGS_EQUAL(&nodes[NODE_COUNT-1], slist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_tail);
    }

    // cut last node except temp node
    {
        slist_cut_node(&slist, &nodes[NODE_COUNT-1]);    

        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_tail);
    }
}


TEST(single_linked_list, T04_02)
{
    INT         i;
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        slist_add_node_at_tail(&slist, &nodes[i]);
    }

    // cut node forward
    for (i = 1; i < NODE_COUNT-1; i++)
    {
        slist_cut_node(&slist, &nodes[i]);

        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_head);
        LONGS_EQUAL(&nodes[NODE_COUNT-1], slist.p_tail);
    }

    // cut last node except temp node
    {
        slist_cut_node(&slist, &nodes[NODE_COUNT-1]);    

        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_head);
        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_tail);
    }
}

TEST(single_linked_list, T04_03)
{
    INT         i;
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);

    // add node at head
    for (i = 0; i < NODE_COUNT; i++)
    {
        slist_add_node_at_tail(&slist, &nodes[i]);
    }    

    // cut node backward
    for (i = NODE_COUNT-1; i > 0; i--)
    {
        slist_cut_node(&slist, &nodes[i]);

        LONGS_EQUAL(&nodes[NODE_TEMP], slist.p_head);
        LONGS_EQUAL(&nodes[i-1], slist.p_tail);
    }
}

TEST(single_linked_list, T05_00)
{
    SLIST_t     slist;
    SNODE_t     nodes[NODE_COUNT];

    slist_init_list(&slist);

    slist_add_node_at_tail(&slist, &nodes[NODE_FIRST]);
    slist_cut_node(&slist, &nodes[NODE_FIRST]);

    LONGS_EQUAL(NULL, nodes[NODE_FIRST].p_next);
}


