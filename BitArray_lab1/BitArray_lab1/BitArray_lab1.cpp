#include "BitArray_lab1.h"

BitArray::BitArray() : bit_count(0) {};
BitArray::~BitArray() = default;
BitArray::BitArray(const BitArray& b) : bit_array(b.bit_array), bit_count(b.bit_count) {}

BitArray::BitArray(int num_bits, unsigned long value) : bit_count(num_bits)
{
    int size = (num_bits + BYTE_SIZE - 1) / BYTE_SIZE;
    bit_array.resize(size, 0);

    for (int i = 0; i < num_bits && i < sizeof(value) * 8; ++i)
    {
        if (value & (1UL << i))
        {
            int byte = size - 1 - (i / BYTE_SIZE);
            int bit = i % BYTE_SIZE;
            bit_array[byte] |= (1 << bit);
        }
    }
}

void BitArray::swap(BitArray& b)
{
    std::swap(bit_array, b.bit_array);
    std::swap(bit_count, b.bit_count);
}

BitArray& BitArray::operator=(const BitArray& b)
{
    if (&b == this)
    {
        return *this;
    }
    bit_array = b.bit_array;
    bit_count = b.bit_count;
    return *this;
}

void BitArray::resize(int num_bits, bool value)
{
    if (num_bits < 0)
    {
        throw std::invalid_argument("num_bits must be a positive value");
    }
    std::size_t newSize = (static_cast<size_t>(num_bits) + BYTE_SIZE - 1) / BYTE_SIZE;
    bit_count = num_bits;
    bit_array.resize(newSize, value ? 255 : 0);
}

void BitArray::clear()
{
    bit_array.clear();
    bit_count = 0;
}

void BitArray::push_back(bool bit)
{
    
    (*this).resize(bit_count + 1);
   
    bit_array[bit_count / BYTE_SIZE] |= 128 >> ((bit_count - 1) % BYTE_SIZE);
}

BitArray& BitArray::operator&=(const BitArray& b)
{
    if (&b == this)
        return *this;

    if (bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array sizes do not match");
    }

    for (std::size_t i = 0; i < bit_array.size(); ++i)
    {
        bit_array[i] &= b.bit_array[i];
    }

    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b)
{
    if (&b == this)
        return *this;

    if (bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array sizes do not match");
    }

    for (std::size_t i = 0; i < bit_array.size(); ++i)
    {
        bit_array[i] |= b.bit_array[i];
    }

    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b)
{
    if (&b == this)
        return *this;

    if (bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array sizes do not match");
    }

    for (std::size_t i = 0; i < bit_array.size(); ++i)
    {
        bit_array[i] ^= b.bit_array[i];
    }

    return *this;
}

BitArray& BitArray::operator<<=(int n)
{
    int shiftBytes = n / BYTE_SIZE;
    int shiftBits = n % BYTE_SIZE;
    int numBytes = (bit_count + BYTE_SIZE - 1) / BYTE_SIZE;
    if (n >= bit_count)
    {
        reset();
        return *this;
    }
    if (shiftBytes > 0)
    {
        std::move(bit_array.begin() + shiftBytes, bit_array.end(), bit_array.begin());
        std::fill(bit_array.end() - shiftBytes, bit_array.end(), 0);
    }
    
    if (shiftBits > 0)
    {

        char overflow = 0;
        for (int i = numBytes - 1; i >= 0; i--)
        {
            char current = bit_array[i];
            bit_array[i] = (current << shiftBits) | overflow;
            overflow = (current >> (BYTE_SIZE - shiftBits)) & (255 >> (BYTE_SIZE - shiftBits));
        }
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n)
{
    int shiftBytes = n / BYTE_SIZE;
    int shiftBits = n % BYTE_SIZE;
    int numBytes = (bit_count + BYTE_SIZE - 1) / BYTE_SIZE;
    

    if (n >= bit_count)
    {
        reset();
        return *this;
    }

    if (shiftBits == 0)
    {
        std::move(bit_array.begin(), bit_array.end() - shiftBytes, bit_array.begin() + shiftBytes);
        std::fill(bit_array.begin(), bit_array.begin() + shiftBytes, 0);
    }
    else
    {
        std::move(bit_array.begin(), bit_array.end() - shiftBytes, bit_array.begin() + shiftBytes);
        std::fill(bit_array.begin(), bit_array.begin() + shiftBytes, 0);

        char overflow = 0;
        for (int i = 0; i < numBytes; i++)
        {
            char current = bit_array[i];
            bit_array[i] = ((current >> shiftBits) & (255 >> (shiftBits)) | overflow);
            overflow = (current << (BYTE_SIZE - shiftBits));
        }
    }

    return *this;
}








BitArray BitArray::operator<<(int n) const
{
    BitArray res = (*this);
    return res <<= n;
}

BitArray BitArray::operator>>(int n) const
{
    BitArray res = (*this);
    return res >>= n;
}

BitArray& BitArray::set(int n, bool val)
{
    int byte = n / BYTE_SIZE;
    int bit = n % BYTE_SIZE;
    if (val)
    {
        bit_array[byte] |= (128 >> bit);
    }
    else
    {
        bit_array[byte] &= ~(128 >> bit);
    }
    return *this;
}

BitArray& BitArray::set()
{
    std::fill(bit_array.begin(), bit_array.end(), 255);
    return *this;
}

BitArray& BitArray::reset(int n)
{
    int byte = n / BYTE_SIZE;
    int bit = n % BYTE_SIZE;
    bit_array[byte] &= ~(128 >> bit);
    return *this;
}

BitArray& BitArray::reset()
{
    std::fill(bit_array.begin(), bit_array.end(), 0);
    return *this;
}

bool BitArray::any() const
{
    for (const char& byte : bit_array)
    {
        if (byte != 0)
        {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const
{
    return !any();
}

BitArray BitArray::operator~() const
{
    BitArray res = *this;
    for (char& byte : res.bit_array)
    {
        byte = ~byte;
    }
    return res;
}

int BitArray::count() const
{
    int countOneBits = 0;
    for (std::size_t i = 0; i < bit_count; ++i)
    {
        int byte = i / BYTE_SIZE;
        int bit = i % BYTE_SIZE;
        if (bit_array[byte] & (1 << bit))
        {
            countOneBits++;
        }
    }
    return countOneBits;
}

bool BitArray::operator[](int i) const
{
    if (i < 0 || i >= bit_count)
    {
        throw std::out_of_range("Index out of range");
    }
    int byte = i / BYTE_SIZE;
    int bit = i % BYTE_SIZE;
    return (bit_array[byte] & (128 >> bit));
}

BitArray::BitReference BitArray::operator[](int i) {
    if (i < 0 || i >= bit_count)
    {
        throw std::out_of_range("Index out of range");
    }
    int byte = i / BYTE_SIZE;
    int bit = i % BYTE_SIZE;
    return BitReference(bit_array[byte], bit);
}

int BitArray::size() const
{
    return bit_count;
}

bool BitArray::empty() const
{
    return bit_count == 0;
}

std::string BitArray::to_string() const
{
    std::string res;
    for (std::size_t i = 0; i < bit_count; i++)
    {
        res.push_back((*this)[i] ? '1' : '0');
    }

    return res;
}

bool operator==(const BitArray& a, const BitArray& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (std::size_t i = 0; i < a.size(); ++i)
    {
        if (a.operator[](i) != b.operator[](i))
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b)
{
    return !(operator==(a, b));
}

BitArray operator&(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b1.size())
    {
        throw std::invalid_argument("sizes do not match");
    }
    BitArray result = b1;
    return result.operator&=(b2);
}

BitArray operator|(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b1.size())
    {
        throw std::invalid_argument("sizes do not match");
    }
    BitArray result = b1;
    return result.operator|=(b2);
}

BitArray operator^(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b1.size())
    {
        throw std::invalid_argument("sizes do not match");
    }
    BitArray result = b1;
    return result.operator^=(b2);
}

BitArray::Iterator::Iterator(const BitArray* bArr, int idx) : bitarr(bArr), index(idx){}

BitArray::Iterator::~Iterator() = default;

BitArray::BitReference BitArray::Iterator::operator*() const {
    if (index < 0 || index >= (*bitarr).size())
        throw std::out_of_range("out of range");

    
    return const_cast<BitArray&>(*bitarr)[index];
}


BitArray::Iterator& BitArray::Iterator::operator++()
{
    index++;
    return *this;
}

BitArray::Iterator& BitArray::Iterator::operator--()
{
    index--;
    return *this;
}

bool BitArray::Iterator::operator==(const Iterator& iterator) const
{
    return index == iterator.index;
}

bool BitArray::Iterator::operator!=(const Iterator& iterator) const
{
    return index != iterator.index;
}

BitArray::Iterator BitArray::begin() { return Iterator(this, 0); }

BitArray::Iterator BitArray::end() { return Iterator(this, bit_count); };

BitArray::BitReference& BitArray::BitReference::operator=(bool val) {
    if (val)
        ref |= (1 << bit_position);  
    else
        ref &= ~(1 << bit_position); 
    return *this;
}

BitArray::BitReference::BitReference(const char& ref, int bit_pos)
    : ref(const_cast<char&>(ref)), bit_position(bit_pos) {}

BitArray::BitReference::operator bool() const
{
    return (ref & (128 >> bit_position)) != 0;
}
