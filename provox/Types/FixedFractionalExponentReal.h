#pragma once

#include "Bit.h"

// This is an expansion of the concept behind the above class, except
// 

// For reference, these are the maximum sizes per bit for each bit
// 1 = 1
// 2 = 3
// 3 = 7
// 4 = 15
// 5 = 31
// 6 = 63
// 7 = 127
// 8 = 255
// 9 = 511
// 10 = 1023
// 11 = 2047
// 12 = 4095
// 13 = 8191
// 14 = 16383
// 15 = 32767
// 16 = 65535
// and so on, you can calculate the amount of bits you require based on your common min/max for
// significand and fractionals

template<
    size_t SignificandBitSize,  // Maximum bit size for the significand ("whole" number)
    size_t FractionalBitSize,   // Maximum bit size for the fractional value
    size_t FractionalExponent>  // The "step" size
class FixedFractionalExponentReal
{
    static constexpr size_t TotalBitSize = FindNearestByteFromBits(1 + SignificandBitSize + FractionalBitSize);
    static constexpr size_t TotalByteSize = TotalBitSize / 8;

public:
    FixedFractionalExponentReal() : m_value{ 0 } {}
    FixedFractionalExponentReal(uint64 significand, uint64 fractional)
    {
        // 
    }

    constexpr size_t GetByteSize()
    {
        return TotalByteSize;
    }

private:
    uint8 m_value[TotalByteSize];
};
