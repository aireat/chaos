

#include "CppUTest/TestHarness.h"

#define _ENABLE_STACK_TRACE 1
#include "kernel.h"


TEST_GROUP(task)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(task, T01)
{
    DEF_TASK(task1, 0, 10);
    //TASK_t      task;

    __knl_init();
    LONGS_EQUAL(task_create(&task1, 0, 0, TASK_OPT_NONE), RESULT_SUCCESS);
}


TEST(task, T02)
{
    TASK_t      task;

    LONGS_EQUAL(task_delete(&task), RESULT_SUCCESS);
}
