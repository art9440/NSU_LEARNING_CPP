#include <iostream>
#include "BitArray_lab1.h"

BitArray::BitArray() : bit_count(0) {}

BitArray::~BitArray() = default;

explicit BitArray::BitArray(int num_bits, unsigned long value = 0) : bit_count(num_bits){
	bit_array.resize((num_bits + BYTE_SIZE - 1) / BYTE_SIZE, 0);
	if (bit_count != 0 && bit_array.empty())
		bit_array[0] = value;
}


BitArray::BitArray(const BitArray& b): bit_array(b.bit_array), bit_count(b.bit_count){}

void BitArray::swap(BitArray& b) {
	std::swap(bit_array, b.bit_array);
	std::swap(bit_count, b.bit_count);
}

BitArray& BitArray::operator=(const BitArray& b) {
	if (this == &b)
		return *this;
	delete [] &bit_array;
	bit_count = b.bit_count;
	bit_array = b.bit_array;

	return *this;
}

void resize(int num_bits, bool value = false) {

}
