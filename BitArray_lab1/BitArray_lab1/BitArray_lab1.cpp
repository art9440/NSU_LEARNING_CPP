#include <iostream>
#include <stdexcept>
#include "BitArray_lab1.h"

BitArray::BitArray() : bit_count(0) {}

BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value = 0) : bit_count(num_bits) {
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

void BitArray::resize(int num_bits, bool value) {
	if (num_bits < 0)
		throw::std::invalid_argument("size must be non negative");
	size_t newSize = (num_bits + BYTE_SIZE - 1) / BYTE_SIZE;
	if (newSize > bit_count)
		bit_array.resize(newSize, value ? ~0 : 0);
	(*this).bit_count = num_bits;
	bit_array.resize(newSize, value ? 1 : 0);
}

void BitArray::clear() {
	bit_array.clear();
	bit_count = 0;
}

void BitArray::push_back(bool bit) {
	resize(bit_count + 1);
	set(bit_count - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
	if (bit_count != b.bit_count)
		throw std::invalid_argument("Must have the same size");
	for (size_t i = 0; i < bit_count; i++) {
		bit_array[i] &= b.bit_array[i];
	}

	return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
	if (bit_count != b.bit_count)
		throw std::invalid_argument("Must have the same size");
	for (size_t i = 0; i < bit_count; i++) {
		bit_array[i] |= b.bit_array[i];
	}

	return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
	if (bit_count != b.bit_count)
		throw std::invalid_argument("Must have the same size");
	for (size_t i = 0; i < bit_count; i++) {
		bit_array[i] ^= b.bit_array[i];
	}

	return *this;
}


BitArray& BitArray::operator<<=(int n) {

}

BitArray& BitArray::operator>>=(int n) {

}

BitArray BitArray::operator<<(int n) const {
	BitArray res(*this);
	return res <<= n;
}

BitArray BitArray::operator>>(int n) const {
	BitArray res(*this);
	return res >>= n;
}

BitArray& BitArray::set(int n, bool val) {
	if (n > bit_count || n < bit_count)
		throw std::invalid_argument("out of range");
	int byte = n / BYTE_SIZE;
	int bit = n % BYTE_SIZE;
	if (val)
		bit_array[byte] = (1 << bit);
	else
		bit_array[byte] = ~(1 << bit);

	return *this;
}

BitArray& BitArray::set() {
	std::fill(bit_array.begin(), bit_array.end(), 0);
	return *this;
}

BitArray& BitArray::reset(int n) {
	if (n > bit_count || n < bit_count)
		throw std::invalid_argument("out of range");
	int byte = n / BYTE_SIZE;
	int bit = n % BYTE_SIZE;
	bit_array[byte] = (0 << bit);

	return *this;
}

BitArray& BitArray::reset() {
	std::fill(bit_array.begin(), bit_array.end(), 0);
	return *this;
}


bool BitArray::any() const {
	for (const char& byte : bit_array) {
		if (byte == 1)
			return true;
		else
			return false;
	}
}

bool BitArray::none() const {
	for (const char& byte : bit_array) {
		if (byte == 1)
			return false;
	}
	return true;
}

BitArray BitArray::operator~() const {
	BitArray res = *this;
	for (char& byte : res.bit_array) {
		byte = ~byte;
	}
	return res;
}
int BitArray::count() const {
	int counting_bits = 0;
	for (size_t i = 0; i < bit_count; i++) {
		int byte = i / BYTE_SIZE;
		int bit = i % BYTE_SIZE;
		if (bit_array[byte] & (1 << bit_array[bit]))
			counting_bits++;
	}
	return counting_bits;
}


bool BitArray::operator[](int i) const {
	int byte = i / BYTE_SIZE;
	int bit = i % BYTE_SIZE;
	return bit_array[byte] & (1 << bit_array[bit]);
}

int BitArray::size() const {
	return bit_count;
}
bool BitArray::empty() const {
	return bit_count == 0;
}

std::string BitArray::to_string() const {

}

bool operator==(const BitArray& a, const BitArray& b) {

}
bool operator!=(const BitArray& a, const BitArray& b) {

}

BitArray operator&(const BitArray& b1, const BitArray& b2) {

}
BitArray operator|(const BitArray& b1, const BitArray& b2) {

}
BitArray operator^(const BitArray& b1, const BitArray& b2) {

}
