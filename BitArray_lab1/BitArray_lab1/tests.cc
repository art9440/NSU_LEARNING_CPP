#include "BitArray_lab1.h"
#include "gtest/gtest.h"
#include <iostream>


TEST(BitArrayTests, BasicConstructor)
{
    BitArray bitArr;
    ASSERT_EQ(bitArr.size(), 0);
    ASSERT_TRUE(bitArr.empty());
}

TEST(BitArrayTests, ConstructorWithValues) {
    BitArray bitArr(16, 170);  // 170 = 10101010 (битовое представление)
    ASSERT_EQ(bitArr.size(), 16);

    // Проверьте, что биты правильно распределены по массиву
    ASSERT_EQ(bitArr[0], 0);  // Младший бит в 0 позиции
    ASSERT_EQ(bitArr[1], 0);
    ASSERT_EQ(bitArr[2], 0);
    ASSERT_EQ(bitArr[3], 0);
    ASSERT_EQ(bitArr[4], 0);
    ASSERT_EQ(bitArr[5], 0);
    ASSERT_EQ(bitArr[6], 0);
    ASSERT_EQ(bitArr[7], 0);  // Старший бит в байте (1)
    ASSERT_EQ(bitArr[8], 1);  // Следующий байт (младший бит)
    ASSERT_EQ(bitArr[9], 0);
    ASSERT_EQ(bitArr[10], 1);
    ASSERT_EQ(bitArr[11], 0);
    ASSERT_EQ(bitArr[12], 1);
    ASSERT_EQ(bitArr[13], 0);
    ASSERT_EQ(bitArr[14], 1);
    ASSERT_EQ(bitArr[15], 0);  // Старший бит второго байта (0)
}



TEST(BitArrayTests, CopyConstructor)
{
    BitArray bitArr(16, 170);
    BitArray b(bitArr);
    ASSERT_EQ(bitArr.size(), b.size());
    ASSERT_EQ(bitArr.to_string(), b.to_string());
}

TEST(BitArrayTests, Swap)
{
    BitArray bitArr(16, 170);
    BitArray b(8, 128);
    bitArr.swap(b);
    ASSERT_EQ(bitArr.to_string(), "10000000");
    ASSERT_EQ(b.to_string(), "0000000010101010");
}

TEST(BitArrayTests, OperatorEQ)
{
    BitArray bitArr_1(16, 170);
    BitArray bitArr_2(8, 128);
    bitArr_1 = bitArr_2;
    bitArr_2 = bitArr_1;
    ASSERT_EQ(bitArr_1.to_string(), "10000000");
    ASSERT_EQ(bitArr_2.to_string(), "10000000");
}

TEST(BitArrayTests, ResizeTest)
{
    BitArray bitArray;
    ASSERT_THROW(bitArray.resize(-5, false), std::invalid_argument);

    BitArray bitArr(8, 170);
    bitArr.resize(16, true);
    ASSERT_EQ(bitArr.size(), 16);
    ASSERT_EQ(bitArr.to_string(), "1010101011111111");
}

TEST(BitArrayTests, to_stringTest)
{
    BitArray bitArr(16, 170);
    ASSERT_EQ(bitArr.to_string(), "0000000010101010");
}

TEST(BitArrayTests, ClearAndPush)
{
    BitArray bitArr(8, 170);
    bitArr.clear();

    ASSERT_EQ(bitArr.size(), 0);
    ASSERT_EQ(bitArr.to_string(), "");

    bitArr.push_back(true);
    ASSERT_EQ(bitArr.size(), 1);
    ASSERT_EQ(bitArr.to_string(), "1");

}

TEST(BitArrayTests, OperatorConEQ)
{
    BitArray bitArr_1(8, 170), bitArr_2(16, 170), bitArr_3(8, 20);
    //bitArr_1 &= bitArr_1;
    //ASSERT_EQ(bitArr_1, "10101010");

    ASSERT_THROW(bitArr_1 &= bitArr_2, std::invalid_argument);
    
}