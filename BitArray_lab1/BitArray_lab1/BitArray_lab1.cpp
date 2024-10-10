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
        if (value & (0x80 >> i))
        {
            int byteIndex = (size * 8 - 1 - i) / BYTE_SIZE;
            int bitIndex = i % BYTE_SIZE;
            bit_array[byteIndex] |= (0x80 >> bitIndex);
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
    //std::cout << bit_count << " ";
    (*this).resize(bit_count + 1);
    //std::cout << bit_count << " ";
    bit_array[bit_count / BYTE_SIZE] |= 0x80 >> ((bit_count - 1) % BYTE_SIZE);
}

BitArray& BitArray::operator&=(const BitArray& b)
{
    if (&b == this)
        return *this;

    if (bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array sizes do not match");
    }

    for (std::size_t i = 0; i < bit_count; ++i)
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

    for (std::size_t i = 0; i < bit_count; ++i)
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

    for (std::size_t i = 0; i < bit_count; ++i)
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
    if (shiftBits == 0)
    {
        std::move(bit_array.begin() + shiftBytes, bit_array.end(), bit_array.begin());
        std::fill(bit_array.end() - shiftBytes, bit_array.end(), 0);
    }
    else
    {

        std::move(bit_array.begin() + shiftBytes, bit_array.end(), bit_array.begin());
        std::fill(bit_array.end() - shiftBytes, bit_array.end(), 0);
        char overflow = 0;
        for (std::size_t i = 0; i < numBytes; ++i)
        {
            char current = bit_array[i];
            bit_array[i] = (current << shiftBits) | overflow;
            overflow = (current >> (BYTE_SIZE - shiftBits));
        }
    }
    if (bit_count % BYTE_SIZE != 0)
    {
        char mask = (1 << (bit_count % BYTE_SIZE)) - 1;
        bit_array[numBytes - 1] &= mask;
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
        std::move(bit_array.begin() + shiftBytes, bit_array.end(), bit_array.begin());
        std::fill(bit_array.end() - shiftBytes, bit_array.end(), 0);
    }
    else
    {
        std::move(bit_array.begin() + shiftBytes, bit_array.end(), bit_array.begin());
        std::fill(bit_array.end() - shiftBytes, bit_array.end(), 0);

        char overflow = 0;
        for (int i = numBytes - 1; i >= 0; --i)
        {
            char current = bit_array[i];
            bit_array[i] = (current >> shiftBits) | overflow;
            overflow = (current << (BYTE_SIZE - shiftBits));
        }
    }

    if (bit_count % BYTE_SIZE != 0)
    {
        char mask = (1 << (bit_count % BYTE_SIZE)) - 1;
        bit_array[numBytes - 1] &= mask;
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const
{
    BitArray res = (*this);
    return res << n;
}

BitArray BitArray::operator>>(int n) const
{
    BitArray res = (*this);
    return res >> n;
}

BitArray& BitArray::set(int n, bool val)
{
    int byteIndex = n / BYTE_SIZE;
    int bitIndex = n % BYTE_SIZE;
    if (val)
    {
        bit_array[byteIndex] = (1 << bitIndex);
    }
    else
    {
        bit_array[byteIndex] = ~(1 << bitIndex);
    }
    return *this;
}

BitArray& BitArray::set()
{
    std::fill(bit_array.begin(), bit_array.end(), 1);
    return *this;
}

BitArray& BitArray::reset(int n)
{
    int byteIndex = n / BYTE_SIZE;
    int bitIndex = n % BYTE_SIZE;
    bit_array[byteIndex] = (0 << bitIndex);
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
        int bitIndex = i % BYTE_SIZE;
        if (bit_array[byte] & (1 << bitIndex))
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
    int byteIndex = i / BYTE_SIZE;
    int bitIndex = i % BYTE_SIZE;
    return (bit_array[byteIndex] & (0x80 >> bitIndex));
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
    for (std::size_t i = 0; i < bit_count; ++i)
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
        throw std::invalid_argument("Array sizes do not match");
    }
    BitArray result = b1;
    return result.operator&=(b2);
}

BitArray operator|(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b1.size())
    {
        throw std::invalid_argument("Array sizes do not match");
    }
    BitArray result = b1;
    return result.operator|=(b2);
}

BitArray operator^(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b1.size())
    {
        throw std::invalid_argument("Array sizes do not match");
    }
    BitArray result = b1;
    return result.operator^=(b2);
}