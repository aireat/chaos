

#include "CppUTest/TestHarness.h"

#include "task.h"


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
    TASK_DEF(task, 0, 10);
    //TASK_t      task;

    LONGS_EQUAL(task_create(&task, 0, 0), RESULT_SUCCESS);
}

TEST(task, T02)
{
    TASK_t      task;

    LONGS_EQUAL(task_delete(&task), RESULT_SUCCESS);
}
