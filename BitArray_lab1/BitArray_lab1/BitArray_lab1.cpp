#include <iostream>
#include "BitArray_lab1.h"

BitArray::BitArray() : bit_count(0) {}

BitArray::~BitArray() = default;

explicit BitArray::BitArray(int num_bits, unsigned long value = 0) : bit_count(num_bits){
	bit_array.resize(BYTE_SIZE + bit_count);
	if (bit_count != 0 && bit_array.empty())
		bit_array[0] = value;
}
