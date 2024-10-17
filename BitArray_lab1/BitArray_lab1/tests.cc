#include "BitArray_lab1.h"
#include "gtest/gtest.h"
#include <iostream>


TEST(BitArrayTests, Constructor){

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



TEST(BitArrayTests, CopyConstructor){

    BitArray bitArr(16, 170);
    BitArray b(bitArr);
    ASSERT_EQ(bitArr.size(), b.size());
    ASSERT_EQ(bitArr.to_string(), b.to_string());
}

TEST(BitArrayTests, Swap){

    BitArray bitArr(16, 170);
    BitArray b(8, 128);
    bitArr.swap(b);
    ASSERT_EQ(bitArr.to_string(), "10000000");
    ASSERT_EQ(b.to_string(), "0000000010101010");
}

TEST(BitArrayTests, OperatorEQ){

    BitArray bitArr_1(16, 170);
    BitArray bitArr_2(8, 128);
    bitArr_1 = bitArr_2;
    bitArr_2 = bitArr_1;
    ASSERT_EQ(bitArr_1.to_string(), "10000000");
    ASSERT_EQ(bitArr_2.to_string(), "10000000");
}

TEST(BitArrayTests, ResizeTest){

    BitArray bitArray;
    ASSERT_THROW(bitArray.resize(-5, false), std::invalid_argument);

    BitArray bitArr(8, 170);
    bitArr.resize(16, true);
    ASSERT_EQ(bitArr.size(), 16);
    ASSERT_EQ(bitArr.to_string(), "1010101011111111");
}

TEST(BitArrayTests, to_stringTest){

    BitArray bitArr(16, 170);
    ASSERT_EQ(bitArr.to_string(), "0000000010101010");
}

TEST(BitArrayTests, ClearAndPush){

    BitArray bitArr(8, 170);
    bitArr.clear();

    ASSERT_EQ(bitArr.size(), 0);
    ASSERT_EQ(bitArr.to_string(), "");

    bitArr.push_back(true);
    ASSERT_EQ(bitArr.size(), 1);
    ASSERT_EQ(bitArr.to_string(), "1");

}

TEST(BitArrayTests, OperatorConEQ){

    BitArray bitArr_1(8, 170), bitArr_2(16, 170);
    bitArr_1 &= bitArr_1;
    ASSERT_EQ(bitArr_1.to_string(), "10101010");
    ASSERT_THROW(bitArr_1 &= bitArr_2, std::invalid_argument);
    BitArray bitArr_3(8, 170);
    BitArray bitArr_4(8, 20);
    bitArr_3 &= bitArr_4;
    ASSERT_EQ(bitArr_3.to_string(), "00000000");
}

TEST(BitArrayTests, OperatorDisEQ){

    BitArray bitArr_1(8, 170), bitArr_2(16, 170);
    bitArr_1 |= bitArr_1;
    ASSERT_EQ(bitArr_1.to_string(), "10101010");
    ASSERT_THROW(bitArr_1 |= bitArr_2, std::invalid_argument);
    BitArray bitArr_3(8, 170);
    BitArray bitArr_4(8, 20);
    bitArr_3 |= bitArr_4;
    ASSERT_EQ(bitArr_3.to_string(), "10111110");
}

TEST(BitArrayTests, OperatorXOR){

    BitArray bitArr_1(8, 170), bitArr_2(16, 170);
    ASSERT_THROW(bitArr_1 ^= bitArr_2, std::invalid_argument);
    BitArray bitArr_3(8, 170);
    BitArray bitArr_4(8, 100);
    bitArr_3 ^= bitArr_4;
    ASSERT_EQ(bitArr_3.to_string(), "11001110");
}

TEST(BitArrayTests, OperatorLShiftEQ){

    BitArray bitArr_1(8, 5);
    bitArr_1 <<= 9;
    ASSERT_EQ(bitArr_1.to_string(), "00000000");

    BitArray bitArr_2(16, 170);
    bitArr_2 <<= 8;
    ASSERT_EQ(bitArr_2.to_string(), "1010101000000000");
    BitArray bitArr_3(16, 170);
    bitArr_3 <<= 3;
    ASSERT_EQ(bitArr_3.to_string(), "0000010101010000");
}

TEST(BitArrayTests, OperatorRShiftEQ){

    BitArray bitArr_1(8, 5);
    bitArr_1 >>= 9;
    ASSERT_EQ(bitArr_1.to_string(), "00000000");

    BitArray bitArr_2(16, 170);
    ASSERT_EQ(bitArr_2.to_string(), "0000000010101010");
    bitArr_2 >>= 8;
    ASSERT_EQ(bitArr_2.to_string(), "0000000000000000");
    BitArray bitArr_3(16, 43520);
    ASSERT_EQ(bitArr_3.to_string(), "1010101000000000");
    bitArr_3 >>= 8;
    ASSERT_EQ(bitArr_3.to_string(), "0000000010101010");
}

TEST(BitArrayTests, OperatorLShift) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ((bitArr_1 << 8).to_string(), "1010101000000000");
}

TEST(BitArrayTests, OperatorRShift) {
    BitArray bitArr_1(16, 43520);
    ASSERT_EQ((bitArr_1 >> 8).to_string(), "0000000010101010");
}

TEST(BitArrayTests, SetValue) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ((bitArr_1.set(0, true)).to_string(), "1000000010101010");
    ASSERT_EQ((bitArr_1.set(8, false)).to_string(), "1000000000101010");
}

TEST(BitArrayTests, Set) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ(bitArr_1.set().to_string(), "1111111111111111");
}

TEST(BitArrayTests, AllResets) {
    BitArray bitArr_1(16, 43520);
    ASSERT_EQ(bitArr_1.reset(0).to_string(), "0010101000000000");
    ASSERT_EQ(bitArr_1.reset().to_string(), "0000000000000000");
}

TEST(BitArrayTests, AnyNone) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ(bitArr_1.any(), true);
    ASSERT_EQ(bitArr_1.none(), false);
}

TEST(BitArrayTests, Count) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ(bitArr_1.count(), 4);
}

TEST(BitArrayTests, OperatorSQbrackets) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ(bitArr_1[8], 1);
    ASSERT_EQ(bitArr_1[15], 0);
}

TEST(BitArrayTests, OperatorInversion) {
    BitArray bitArr_1(16, 170);
    ASSERT_EQ((~bitArr_1).to_string(), "1111111101010101");
}

TEST(BitArrayTests, Empty) {
    BitArray bitArr_1;
    ASSERT_EQ(bitArr_1.empty(), true);
}

TEST(BitArrayTests, DoubleEQ) {
    BitArray bitArr_1(16, 170), bitArr_2(8, 170), bitArr_3(16, 43520);
    ASSERT_EQ(bitArr_1 == bitArr_2, false);
    ASSERT_EQ(bitArr_1 == bitArr_3, false);
}

TEST(BitArrayTests, NotEQ) {
    BitArray bitArr_1(16, 170), bitArr_2(16, 43520);
    ASSERT_EQ(bitArr_1 != bitArr_2, true);
}

TEST(BitArrayTests, Conuction) {
    BitArray bitArr_1(16, 170), bitArr_2(16, 43520), bitArr_3(8, 170);
    ASSERT_THROW(bitArr_1 & bitArr_3, std::invalid_argument);
    ASSERT_EQ((bitArr_1 & bitArr_2).to_string(), "0000000000000000");
}

TEST(BitArrayTests, Disunction) {
    BitArray bitArr_1(16, 170), bitArr_2(16, 43520), bitArr_3(8, 170);
    ASSERT_THROW(bitArr_1 | bitArr_3, std::invalid_argument);
    ASSERT_EQ((bitArr_1 | bitArr_2).to_string(), "1010101010101010");
}

TEST(BitArrayTests, XOR) {
    BitArray bitArr_1(16, 170), bitArr_3(8, 170);
    ASSERT_THROW(bitArr_1 ^ bitArr_3, std::invalid_argument);
    ASSERT_EQ((bitArr_1 ^ bitArr_1).to_string(), "0000000000000000");
}

TEST(IteratorTests, ConstructorWithVal) {
    BitArray bitArr_1(16, 170);
    BitArray::Iterator it_1(&bitArr_1, 8);
    ASSERT_TRUE(*it_1);
    BitArray::Iterator it_2(&bitArr_1, -8);
    ASSERT_THROW(*it_2, std::out_of_range);
    BitArray::Iterator it_3(&bitArr_1, 20);
    ASSERT_THROW(*it_3, std::out_of_range);
}

TEST(IteratorTests, Incrementation) {
    BitArray bitArr_1(3, 7);
    BitArray::Iterator it_1 = bitArr_1.begin();
    BitArray::Iterator it_2 = bitArr_1.end();
    ++it_1;
    ++it_1;
    ASSERT_EQ(it_1 != it_2, true);
    ++it_1;
    ASSERT_EQ(it_1 == it_2, true);
}

TEST(IteratorTests, Dicrementation) {
    BitArray bitArr_1(3, 7);
    BitArray::Iterator it_1 = bitArr_1.begin();
    BitArray::Iterator it_2 = bitArr_1.end();
    --it_2;
    --it_2;
    ASSERT_EQ(it_1 != it_2, true);
    --it_2;
    ASSERT_EQ(it_1 == it_2, true);
}

TEST(IteratorTests, Autotest) {
    BitArray ba(8, 255);
    for (int i = 0; i < ba.size(); i++)
        ba[i] = false;
    EXPECT_TRUE(ba.none());
}

