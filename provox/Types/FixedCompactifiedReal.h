#pragma once

#include "Bit.h"
#include "Real.h"

// This class minimizes data usage for a floating point value
// Typically, many of the operations here are reserved for fixed-width floating point precision
// but this will be dynamic width, expanding and compacting as needed
// It is designed to store the _minimum_ number of integer and fractional bits
// Ideally, we end up using less than 32-bits by the end, but it's entirely possible to utilize more.
// Most cases, I would hope, utilize much less than the required 32-bits, and those that would use the maximum amount of bits
// under typical floating point precision, are the outliers.

template<size_t IntegerBits, size_t FractionalBits>
class FixedCompactifiedReal
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

    Float GetFloat()
    {
        //
    }

private:
    uint8 m_value[TotalByteSize];
};
