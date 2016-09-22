

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
    LONGS_EQUAL(32, count_lead_zero(0x00000000));
    LONGS_EQUAL( 0, count_lead_zero(0xFFFFFFFF));
    LONGS_EQUAL(31, count_lead_zero(0x00000001));

    LONGS_EQUAL( 0, count_lead_zero(0x80000000));
    LONGS_EQUAL( 0, count_lead_zero(0xC0000000));
    LONGS_EQUAL( 0, count_lead_zero(0x81000000));
    LONGS_EQUAL( 0, count_lead_zero(0x80010001));
    LONGS_EQUAL( 0, count_lead_zero(0x80010101));
    LONGS_EQUAL( 0, count_lead_zero(0x80000001));

    LONGS_EQUAL( 8, count_lead_zero(0x00800000));
    LONGS_EQUAL( 8, count_lead_zero(0x00C00000));
    LONGS_EQUAL( 8, count_lead_zero(0x00C00100));
    LONGS_EQUAL( 8, count_lead_zero(0x00801010));
    LONGS_EQUAL( 8, count_lead_zero(0x00800001));

    LONGS_EQUAL(12, count_lead_zero(0x00080000));
    LONGS_EQUAL(12, count_lead_zero(0x000C0000));
    LONGS_EQUAL(12, count_lead_zero(0x000C0100));
    LONGS_EQUAL(12, count_lead_zero(0x00080101));
    LONGS_EQUAL(12, count_lead_zero(0x00080001));

    LONGS_EQUAL(20, count_lead_zero(0x00000800));
    LONGS_EQUAL(20, count_lead_zero(0x00000C00));
    LONGS_EQUAL(20, count_lead_zero(0x00000C11));
    LONGS_EQUAL(20, count_lead_zero(0x00000811));
    LONGS_EQUAL(20, count_lead_zero(0x00000801));
}
