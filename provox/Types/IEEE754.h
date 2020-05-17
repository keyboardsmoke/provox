#pragma once

#include "platform.h"

#pragma pack(push, 1)

// TODO: Float16, not really.... needed
// https://github.com/facebookincubator/gloo/blob/master/gloo/types.h

enum class IEEEClass
{
    Zero,
    Subnormal,
    Infinite,
    NaN,
    Normal
};

// See: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
struct FloatIEEE754
{
private:

    // the term significand was introduced by George Forsythe and Cleve Moler in 1967,
    // and the use of mantissa for this purpose is discouraged by the IEEE floating-point standard committee
    // wowsers
    static const uint32 SignificandMask         = 0b00000000011111111111111111111111u; // 23 bits
    static const uint32 SignificandHighBit      = 0b00000000010000000000000000000000u;
    static const uint32 ExponentMask            = 0b01111111100000000000000000000000u; // 8 bits
    static const uint32 SignMask                = 0b10000000000000000000000000000000u; // 1 bit
    static const uint32 Infinity = ExponentMask; // 1.#INF (0x7F800000)
    static const uint32 NegativeInfinity = SignMask | Infinity; // -1.#INF (0xFF800000)
    static const uint32 Indeterminate = ExponentMask | SignificandHighBit; // 1.#IND (0x7FC00000)
    static const uint32 NegativeIndeterminate = SignMask | ExponentMask | SignificandHighBit; // -1.#IND (0xFFC00000)

    // Private asserts
    static_assert(SignificandMask == 0x7FFFFFu, "Invalid Significand Mask");
    static_assert(SignificandHighBit == 0x400000u, "Invalid Signficand High bit");
    static_assert(ExponentMask == 0x7F800000u, "Invalid Exponent Mask");
    static_assert(SignMask == 0x80000000u, "Invalid Sign Mask");

public:
    FloatIEEE754() : FloatIEEE754(static_cast<uint32>(0u)) {}; // no bits set
    FloatIEEE754(uint32 value) : integer(value) {}
    FloatIEEE754(float value) : fp(value) {}
    FloatIEEE754(uint32 significand, int16 exponent, uint32 sign) :
        fp(CreateFloat(significand, exponent, sign)) {}

    static float CreateFloat(uint32 significand, int16 exponent, uint32 sign)
    {
        FloatIEEE754 p;
        p.SetSignificand(significand);
        p.SetExponent(exponent);
        p.SetSign(sign);
        return p.fp;
    }

    static FloatIEEE754 GetNaN()
    {
        return FloatIEEE754(Indeterminate);
    }

    static FloatIEEE754 GetNegativeNaN()
    {
        return FloatIEEE754(NegativeIndeterminate);
    }

    static FloatIEEE754 GetInfinte()
    {
        return FloatIEEE754(0, 0xFF, 0);
    }

    static FloatIEEE754 GetNegativeInfinite()
    {
        return FloatIEEE754(0, 0xFF, 1);
    }

    static FloatIEEE754 GetZero()
    {
        return FloatIEEE754(0, 0, 0);
    }

    static FloatIEEE754 GetNegativeZero()
    {
        return FloatIEEE754(0, 0, 1);
    }

    // Getters
    uint32 GetSignificand()
    {
        return (integer & SignificandMask);
    }

    int16 GetExponent()
    {
        return static_cast<int16>((integer & ExponentMask) >> 23);
    }

    uint32 GetSign()
    {
        return (integer & SignMask) >> 31;
    }

    // Setters
    void SetSignificand(uint32 significand)
    {
        integer = (GetSign() << 31) | (static_cast<uint32>(GetExponent()) << 23) | significand;
    }

    void SetExponent(int16 exponent)
    {
        integer = (GetSign() << 31) | (static_cast<uint32>(exponent) << 23) | GetSignificand();
    }

    void SetSign(uint32 sign)
    {
        integer = (sign << 31) | (static_cast<uint32>(GetExponent()) << 23) | GetSignificand();
    }

    // 
    IEEEClass GetClassification()
    {
        const uint32 exp = GetExponent();
        const uint32 sig = GetSignificand();

        if (exp == 0)
        {
            if (sig == 0)
            {
                return IEEEClass::Zero;
            }

            return IEEEClass::Subnormal;
        }

        if (exp == 0xFF)
        {
            if (sig == 0)
            {
                return IEEEClass::Infinite;
            }

            return IEEEClass::NaN;
        }

        return IEEEClass::Normal;
    }

    bool IsZero()
    {
        return (GetSignificand() == 0 && GetExponent() == 0);
    }

    bool IsNormal()
    {
        // The quick way
        const uint32 exp = GetExponent();

        return (exp != 0 && exp != 0xFF);
    }

    bool IsSubnormal()
    {
        return (GetExponent() == 0 && GetSignificand() != 0);
    }

    bool IsNaN()
    {
        // (integer == Indeterminate || integer == NegativeIndeterminate)

        return (GetExponent() == 0xFF && GetSignificand() != 0);
    }

    bool IsInf()
    {
        // (integer == Infinity || integer == NegativeInfinity)

        return (GetExponent() == 0xFF && GetSignificand() == 0);
    }

    union
    {
        float fp;
        uint32 integer;
    };
};

#include <cstdio>

// See: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
struct DoubleIEEE754
{
private:

    static const uint64 SignificandMask     = 0b0000000000001111111111111111111111111111111111111111111111111111u; // 52 bits
    static const uint64 SignificandHighBit  = 0b0000000000001000000000000000000000000000000000000000000000000000u;
    static const uint64 ExponentMask        = 0b0111111111110000000000000000000000000000000000000000000000000000u; // 11 bits
    static const uint64 SignMask            = 0b1000000000000000000000000000000000000000000000000000000000000000u; // 1 bit

    static const uint64 Infinity = ExponentMask; // 1.#INF (0x7FF0000000000000u)
    static const uint64 NegativeInfinity = SignMask | Infinity; // -1.#INF (0xFFF0000000000000u)
    static const uint64 Indeterminate = ExponentMask | SignificandHighBit; // 1.#IND (0x7FF8000000000000u)
    static const uint64 NegativeIndeterminate = SignMask | ExponentMask | SignificandHighBit; // -1.#IND (0xFFF8000000000000u)

    static_assert(SignificandMask       == 0x000FFFFFFFFFFFFFu, "Invalid Significand Mask");
    static_assert(SignificandHighBit    == 0x0008000000000000u, "Invalid High Bit Mask");
    static_assert(ExponentMask          == 0x7FF0000000000000u, "Invalid Exponent Mask");
    static_assert(SignMask              == 0x8000000000000000u, "Invalid Sign Mask");

    static_assert(Infinity              == 0x7FF0000000000000u, "Invalid Infinity");
    static_assert(NegativeInfinity      == 0xFFF0000000000000u, "Invalid Negative Infinity");
    static_assert(Indeterminate         == 0x7FF8000000000000u, "Invalid Indeterminate");
    static_assert(NegativeIndeterminate == 0xFFF8000000000000u, "Invalid Negative Indeterminate");

public:
    DoubleIEEE754() : DoubleIEEE754(static_cast<uint64>(0u)) {}; // no bits set
    DoubleIEEE754(uint64 value) : integer(value) {}
    DoubleIEEE754(double value) : fp(value) {}
    DoubleIEEE754(uint64 significand, int16 exponent, uint64 sign) :
        fp(CreateDouble(significand, exponent, sign)) {}

    static double CreateDouble(uint64 significand, int16 exponent, uint64 sign)
    {
        DoubleIEEE754 p;
        p.SetSignificand(significand);
        p.SetExponent(exponent);
        p.SetSign(sign);
        return p.fp;
    }

    static DoubleIEEE754 GetNaN()
    {
        return DoubleIEEE754(Indeterminate);
    }

    static DoubleIEEE754 GetNegativeNaN()
    {
        return DoubleIEEE754(NegativeIndeterminate);
    }

    static DoubleIEEE754 GetInfinte()
    {
        return DoubleIEEE754(0, -1, 0);
    }

    static DoubleIEEE754 GetNegativeInfinite()
    {
        return DoubleIEEE754(0, -1, 1);
    }

    static DoubleIEEE754 GetZero()
    {
        return DoubleIEEE754(0, 0, 0);
    }

    static DoubleIEEE754 GetNegativeZero()
    {
        return DoubleIEEE754(0, 0, 1);
    }

    uint64 GetSignificand()
    {
        return (integer & SignificandMask);
    }

    int16 GetExponent()
    {
        return (integer & ExponentMask) >> 52;
    }

    uint64 GetSign()
    {
        return (integer & SignMask) >> 63;
    }

    void SetSignificand(uint64 significand)
    {
        integer = (GetSign() << 63) | (static_cast<uint64>(GetExponent()) << 52) | significand;
    }

    void SetExponent(int16 exponent)
    {
        integer = (GetSign() << 63) | (static_cast<uint64>(exponent) << 52) | GetSignificand();
    }

    void SetSign(uint64 sign)
    {
        integer = (sign << 63) | (static_cast<uint64>(GetExponent()) << 52) | GetSignificand();
    }

    // 
    IEEEClass GetClassification()
    {
        const int16 exp = GetExponent();
        const uint64 sig = GetSignificand();

        if (exp == 0)
        {
            if (sig == 0)
            {
                return IEEEClass::Zero;
            }

            return IEEEClass::Subnormal;
        }

        if ((exp & 0x7ff) == 0x7ff)
        {
            if (sig == 0)
            {
                return IEEEClass::Infinite;
            }

            return IEEEClass::NaN;
        }

        return IEEEClass::Normal;
    }

    bool IsZero()
    {
        return (GetSignificand() == 0 && GetExponent() == 0);
    }

    bool IsNormal()
    {
        // The quick way
        const uint64 exp = GetExponent();

        return (exp != 0 && exp != 0xFFF);
    }

    bool IsSubnormal()
    {
        return (GetExponent() == 0 && GetSignificand() != 0);
    }

    bool IsNaN()
    {
        // (integer == Indeterminate || integer == NegativeIndeterminate)

        return ((GetExponent() & 0x7FF) == 0x7FF && GetSignificand() != 0);
    }

    bool IsInf()
    {
        // (integer == Infinity || integer == NegativeInfinity)

        return ((GetExponent() & 0x7FF) && GetSignificand() == 0);
    }

    union
    {
        double fp;
        uint64 integer;
    };
};

#pragma pack(pop)

static_assert(sizeof(float) == sizeof(FloatIEEE754), "Invalid size for basic float type");
static_assert(sizeof(double) == sizeof(DoubleIEEE754), "Invalid size for basic double type");
