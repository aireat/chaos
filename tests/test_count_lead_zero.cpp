

#include "CppUTest/TestHarness.h"

#include "count_lead_zero.h"


TEST_GROUP(count_lead_zero)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(count_lead_zero, normal)
{
    UINT32  value = 0x80000000;

    LONGS_EQUAL(0, count_lead_zero(value));
}
