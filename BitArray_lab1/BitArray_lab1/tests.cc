#include "BitArray_lab1.h"
#include "gtest/gtest.h"

TEST(BitArrayTest, BitArrayConstructorTest) {
	BitArray bitArray = BitArray();

	ASSERT_EQ(bitArray.size(), 0);
	ASSERT_ANY_THROW(bitArray[0]);
}

TEST(BitArrayTest, BitArrayDestructorTest) {
	BitArray* bitArray = new BitArray(1, 1);

	delete bitArray;
	ASSERT_ANY_THROW((*bitArray)[0]);
}

TEST(BitArrayTest, BitArraySpecifiedConstructorTest) {
	BitArray bitArray = BitArray(8, 255);
	ASSERT_EQ(bitArray.size(), 8);
	for (int32_t i = 0; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 1);
	}

	BitArray bitArray2 = BitArray(8, 0);
	ASSERT_EQ(bitArray2.size(), 8);
	for (int32_t i = 0; i < bitArray2.size(); i++) {
		ASSERT_EQ(bitArray2[i], 0);
	}

	BitArray bitArray3 = BitArray(8, 1023);
	ASSERT_EQ(bitArray3.size(), 8);
	for (int32_t i = 0; i < bitArray3.size(); i++) {
		ASSERT_EQ(bitArray3[i], 1);
	}
}

TEST(BitArrayTest, BitArrayCopyConstructorTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(bitArray);

	ASSERT_EQ(bitArray2.size(), 8);
	for (int32_t i = 0; i < bitArray2.size(); i++) {
		ASSERT_EQ(bitArray2[i], 1);
	}
}


TEST(BitArrayTest, BitArraySwapTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(6, 0);

	bitArray.swap(bitArray2);
	ASSERT_EQ(bitArray.size(), 6);
	for (int32_t i = 0; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 0);
	}

	ASSERT_EQ(bitArray2.size(), 8);
	for (int32_t i = 0; i < bitArray2.size(); i++) {
		ASSERT_EQ(bitArray2[i], 1);
	}
}

TEST(BitArrayTest, BitArrayDeclarationTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(6, 0);

	bitArray = bitArray2;
	ASSERT_EQ(bitArray.size(), 6);
	for (int32_t i = 0; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

TEST(BitArrayTest, BitArrayResizeTest) {
	BitArray bitArray = BitArray(8, 255);

	ASSERT_ANY_THROW(bitArray.resize(-1));

	bitArray.resize(10, 1);
	ASSERT_EQ(bitArray.size(), 10);
	for (int32_t i = 0; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 1);
	}

	bitArray.resize(15, 0);
	ASSERT_EQ(bitArray.size(), 15);
	for (int32_t i = 10; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 0);
	}

	bitArray.clear();
	bitArray.resize(15, 0);
	ASSERT_EQ(bitArray.size(), 15);
	for (int32_t i = 0; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 0);
	}

	bitArray.resize(10, 0);
	ASSERT_EQ(bitArray.size(), 10);
	for (int32_t i = 0; i < bitArray.size(); i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

TEST(BitArrayTest, BitArrayClearTest) {
	BitArray bitArray = BitArray(8, 255);

	bitArray.clear();
	ASSERT_ANY_THROW(bitArray[0]);
}

TEST(BitArrayTest, BitArrayPushTest) {
	BitArray bitArray = BitArray(8, 255);

	bitArray.push_back(1);
	ASSERT_EQ(bitArray.size(), 9);
	ASSERT_EQ(bitArray[0], 1);

	for (int32_t i = 1; i < 100; i++) {
		bitArray.push_back(0);
		ASSERT_EQ(bitArray.size(), 9 + i);
		ASSERT_EQ(bitArray[0], 0);
	}

	for (int32_t i = 1; i < 100; i++) {
		bitArray.push_back(1);
		ASSERT_EQ(bitArray.size(), 9 + 99 + i);
		ASSERT_EQ(bitArray[0], 1);
	}
}

TEST(BitArrayTest, BitArrayBitwiseAndTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(7, 0);

	ASSERT_ANY_THROW(bitArray &= bitArray2);

	bitArray2 = BitArray(8, 0);

	bitArray &= bitArray2;

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

TEST(BitArrayTest, BitArrayBitwiseOrTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(7, 0);

	ASSERT_ANY_THROW(bitArray |= bitArray2);

	bitArray2 = BitArray(8, 0);

	bitArray |= bitArray2;

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 1);
	}
}

TEST(BitArrayTest, BitArrayBitwiseXorTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(7, 0);

	ASSERT_ANY_THROW(bitArray ^= bitArray2);

	bitArray2 = BitArray(8, 255);

	bitArray ^= bitArray2;

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

TEST(BitArrayTest, BitArrayBitwiseLeftShiftTest) {
	BitArray bitArray = BitArray(8, 255);

	bitArray <<= 1;

	ASSERT_EQ(bitArray[0], 0);
}

TEST(BitArrayTest, BitArrayBitwiseLeftShiftExplicitTest) {
	BitArray bitArray = BitArray(8, 255);

	bitArray = bitArray << 1;

	ASSERT_EQ(bitArray[0], 0);
}

TEST(BitArrayTest, BitArrayBitwiseRightShiftTest) {
	BitArray bitArray = BitArray(8, 254);

	bitArray >>= 1;

	ASSERT_EQ(bitArray[0], 1);
}

TEST(BitArrayTest, BitArrayBitwiseRightShiftExplicitTest) {
	BitArray bitArray = BitArray(8, 254);

	bitArray = bitArray >> 1;

	ASSERT_EQ(bitArray[0], 1);
}

TEST(BitArrayTest, BitArraySetByIndexTest) {
	BitArray bitArray = BitArray(8, 254);

	bitArray.set(0, 1);

	ASSERT_EQ(bitArray[0], 1);

	bitArray.set(0, 0);

	ASSERT_EQ(bitArray[0], 0);
}

TEST(BitArrayTest, BitArraySetTest) {
	BitArray bitArray = BitArray(8, 0);

	bitArray.set();

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 1);
	}
}

TEST(BitArrayTest, BitArrayResetByIndexTest) {
	BitArray bitArray = BitArray(8, 255);

	bitArray.reset(0);

	ASSERT_EQ(bitArray[0], 0);
}

TEST(BitArrayTest, BitArrayResetTest) {
	BitArray bitArray = BitArray(8, 255);

	bitArray.reset();

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

TEST(BitArrayTest, BitArrayAnyTest) {
	BitArray bitArray = BitArray(8, 0);

	ASSERT_EQ(bitArray.any(), 0);

	bitArray.set();

	ASSERT_EQ(bitArray.any(), 1);
}

TEST(BitArrayTest, BitArrayNoneTest) {
	BitArray bitArray = BitArray(8, 0);

	ASSERT_EQ(bitArray.none(), 1);

	bitArray.set();

	ASSERT_EQ(bitArray.none(), 0);
}

TEST(BitArrayTest, BitArrayCountTest) {
	BitArray bitArray = BitArray(8, 0);

	ASSERT_EQ(bitArray.count(), 0);

	bitArray.set();

	ASSERT_EQ(bitArray.count(), 8);
}

TEST(BitArrayTest, BitArrayBitByIndexTest) {
	BitArray bitArray = BitArray(8, 0);

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 0);
	}

	ASSERT_ANY_THROW(bitArray[10000000]);
}

TEST(BitArrayTest, BitArraySizeTest) {
	BitArray bitArray = BitArray(8, 0);

	ASSERT_EQ(bitArray.size(), 8);

	bitArray = BitArray(1453, 0);

	ASSERT_EQ(bitArray.size(), 1453);
}

TEST(BitArrayTest, BitArrayEmptyTest) {
	BitArray bitArray = BitArray(8, 0);

	ASSERT_EQ(bitArray.empty(), 0);

	bitArray.clear();

	ASSERT_EQ(bitArray.empty(), 1);
}

TEST(BitArrayTest, BitArrayToStringTest) {
	BitArray bitArray = BitArray(8, 0);

	ASSERT_EQ(bitArray.to_string(), "00000000");

	bitArray.set();

	ASSERT_EQ(bitArray.to_string(), "11111111");
}

TEST(BitArrayTest, BitArrayEqualsTest) {
	BitArray bitArray = BitArray(8, 0);
	BitArray bitArray2 = BitArray(8, 0);

	ASSERT_EQ(bitArray == bitArray2, 1);

	bitArray2.set();

	ASSERT_EQ(bitArray == bitArray2, 0);

	bitArray.set();

	ASSERT_EQ(bitArray == bitArray2, 1);

	bitArray.push_back(1);

	ASSERT_EQ(bitArray == bitArray2, 0);

	bitArray2.push_back(0);

	ASSERT_EQ(bitArray == bitArray2, 0);
}

TEST(BitArrayTest, BitArrayNotEqualsTest) {
	BitArray bitArray = BitArray(8, 0);
	BitArray bitArray2 = BitArray(8, 0);

	ASSERT_EQ(bitArray != bitArray2, 0);

	bitArray2.set();

	ASSERT_EQ(bitArray != bitArray2, 1);

	bitArray.set();

	ASSERT_EQ(bitArray != bitArray2, 0);

	bitArray.push_back(1);

	ASSERT_EQ(bitArray != bitArray2, 1);

	bitArray2.push_back(0);

	ASSERT_EQ(bitArray != bitArray2, 1);
}

TEST(BitArrayTest, BitArrayExplicitBitwiseAndTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(7, 0);

	ASSERT_ANY_THROW(bitArray &= bitArray2);

	bitArray2 = BitArray(8, 0);

	bitArray = bitArray & bitArray2;

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

TEST(BitArrayTest, BitArrayExplicitBitwiseOrTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(7, 0);

	ASSERT_ANY_THROW(bitArray |= bitArray2);

	bitArray2 = BitArray(8, 0);

	bitArray = bitArray | bitArray2;

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 1);
	}
}

TEST(BitArrayTest, BitArrayExplicitBitwiseXorTest) {
	BitArray bitArray = BitArray(8, 255);
	BitArray bitArray2 = BitArray(7, 0);

	ASSERT_ANY_THROW(bitArray ^= bitArray2);

	bitArray2 = BitArray(8, 255);

	bitArray = bitArray ^ bitArray2;

	for (int32_t i = 0; i < 8; i++) {
		ASSERT_EQ(bitArray[i], 0);
	}
}

//TEST(BitArrayIteratorTest, BitArrayIteratorTest) {
//	BitArray bitArray = BitArray(8, 255);
//
//	for (auto iter = bitArray.begin(); iter != bitArray.end(); iter++) {
//		ASSERT_EQ(*iter, 1);
//	}
//
//	for (auto iter = bitArray.begin(); iter != bitArray.end(); ++iter) {
//		ASSERT_EQ(*iter, 1);
//	}
//
//	ASSERT_EQ(bitArray.begin() == bitArray.begin(), 1);
//	ASSERT_EQ(bitArray.begin() != bitArray.begin(), 0);
//
//	ASSERT_ANY_THROW(bitArray.end()++);
//	ASSERT_ANY_THROW(++bitArray.end());
//}