#pragma once

#include "platform.h"
#include <type_traits>
#include <limits>

template <size_t T>
struct type_from_size {
    static constexpr bool is_specialized = false;
};

template <>
struct type_from_size<64> {
    static constexpr bool   is_specialized = true;
    static constexpr size_t size = sizeof(int64) * 8;

    using value_type = int64;
    using unsigned_type = std::make_unsigned<value_type>::type;
    using signed_type = std::make_signed<value_type>::type;
    using next_size = type_from_size<128>;
};

template <>
struct type_from_size<32> {
    static constexpr bool   is_specialized = true;
    static constexpr size_t size = sizeof(int32) * 8;

    using value_type = int32;
    using unsigned_type = std::make_unsigned<value_type>::type;
    using signed_type = std::make_signed<value_type>::type;
    using next_size = type_from_size<64>;
};

template <>
struct type_from_size<16> {
    static constexpr bool   is_specialized = true;
    static constexpr size_t size = sizeof(int16) * 8;

    using value_type = int16;
    using unsigned_type = std::make_unsigned<value_type>::type;
    using signed_type = std::make_signed<value_type>::type;
    using next_size = type_from_size<32>;
};

template <>
struct type_from_size<8> {
    static constexpr bool   is_specialized = true;
    static constexpr size_t size = sizeof(int8) * 8;

    using value_type = int8;
    using unsigned_type = std::make_unsigned<value_type>::type;
    using signed_type = std::make_signed<value_type>::type;
    using next_size = type_from_size<16>;
};

static constexpr size_t FindNearestByteFromBits(size_t bits)
{
    return ((bits % 8) == 0 ? bits : bits + 8 - (bits % 8));
}

template<typename T, typename N>
static N ExtractNumberFromBits(T target, uint16 bitStart, uint16 bitEnd)
{

}

template <typename T>
static unsigned CountLeadingZeros(T Val)
{
    if (!Val)
        return 0;

    // Bisection method.
    unsigned ZeroBits = 0;

    for (T Shift = std::numeric_limits<T>::digits >> 1; Shift; Shift >>= 1)
    {
        T Tmp = Val >> Shift;
        if (Tmp)
        {
            Val = Tmp;
        }
        else
        {
            ZeroBits |= Shift;
        }
    }

    return ZeroBits;
}