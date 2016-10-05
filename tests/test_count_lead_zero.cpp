

#include "CppUTest/TestHarness.h"

#define _IMPLEMENT_CLZ_BY_SW        1
#include "clz_func.h"


TEST_GROUP(clz_func)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(clz_func, T01)
{
    LONGS_EQUAL(32, clz_func(0x00000000));
    LONGS_EQUAL( 0, clz_func(0xFFFFFFFF));
    LONGS_EQUAL(31, clz_func(0x00000001));
}

TEST(clz_func, T02)
{
    LONGS_EQUAL( 0, clz_func(0x80000000));
    LONGS_EQUAL( 0, clz_func(0xC0000000));
    LONGS_EQUAL( 0, clz_func(0x81000000));
    LONGS_EQUAL( 0, clz_func(0x80010001));
    LONGS_EQUAL( 0, clz_func(0x80010101));
    LONGS_EQUAL( 0, clz_func(0x80000001));
}

TEST(clz_func, T03)
{
    LONGS_EQUAL( 8, clz_func(0x00800000));
    LONGS_EQUAL( 8, clz_func(0x00C00000));
    LONGS_EQUAL( 8, clz_func(0x00C00100));
    LONGS_EQUAL( 8, clz_func(0x00801010));
    LONGS_EQUAL( 8, clz_func(0x00800001));
}

TEST(clz_func, T04)
{
    LONGS_EQUAL(12, clz_func(0x00080000));
    LONGS_EQUAL(12, clz_func(0x000C0000));
    LONGS_EQUAL(12, clz_func(0x000C0100));
    LONGS_EQUAL(12, clz_func(0x00080101));
    LONGS_EQUAL(12, clz_func(0x00080001));
}

TEST(clz_func, T05)
{
    LONGS_EQUAL(20, clz_func(0x00000800));
    LONGS_EQUAL(20, clz_func(0x00000C00));
    LONGS_EQUAL(20, clz_func(0x00000C11));
    LONGS_EQUAL(20, clz_func(0x00000811));
    LONGS_EQUAL(20, clz_func(0x00000801));
}

