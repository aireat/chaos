

#include "CppUTest/TestHarness.h"

#include "co_macros.h"

#pragma pack(1)
struct TEMP_STRUCT
{
    INT     temp_var1;
    INT     temp_var2;

    BYTE    temp_var3;

    INT16   temp_var4;
};
#pragma pack()

TEST_GROUP(macros)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};


TEST(macros, offset_of)
{
    LONGS_EQUAL( 0, _CO_OFFSET(TEMP_STRUCT, temp_var1));
    LONGS_EQUAL( 4, _CO_OFFSET(TEMP_STRUCT, temp_var2));
    LONGS_EQUAL( 8, _CO_OFFSET(TEMP_STRUCT, temp_var3));
    LONGS_EQUAL( 9, _CO_OFFSET(TEMP_STRUCT, temp_var4));
}

TEST(macros, get_type)
{
    TEMP_STRUCT     temp_struct;
    UINT8*          test_var1 = (UINT8*)&(temp_struct.temp_var1);
    UINT8*          test_var2 = (UINT8*)&(temp_struct.temp_var2);
    UINT8*          test_var3 = (UINT8*)&(temp_struct.temp_var3);
    UINT8*          test_var4 = (UINT8*)&(temp_struct.temp_var4);

    LONGS_EQUAL(&temp_struct, _CO_TYPE(TEMP_STRUCT, temp_var1, test_var1));
    LONGS_EQUAL(&temp_struct, _CO_TYPE(TEMP_STRUCT, temp_var2, test_var2));
    LONGS_EQUAL(&temp_struct, _CO_TYPE(TEMP_STRUCT, temp_var3, test_var3));
    LONGS_EQUAL(&temp_struct, _CO_TYPE(TEMP_STRUCT, temp_var4, test_var4));
}

TEST(macros, max_min)
{
    LONGS_EQUAL(3, _CO_MAX(2, 3));
    LONGS_EQUAL(3, _CO_MAX(3, 2));
    LONGS_EQUAL(2, _CO_MIN(2, 3));
    LONGS_EQUAL(2, _CO_MIN(3, 2));
}

TEST(macros, array_count)
{
    INT     arr1[10];
    INT     arr2[20][10];
    INT8    arr3[30][5];
    float   arr4[5];

    LONGS_EQUAL(10, _CO_ARRAY_COUNT(arr1));
    LONGS_EQUAL(20, _CO_ARRAY_COUNT(arr2));
    LONGS_EQUAL(30, _CO_ARRAY_COUNT(arr3));
    LONGS_EQUAL( 5, _CO_ARRAY_COUNT(arr4));
}




