#pragma once

#include <math.h>

#pragma pack(push, 1)

// See: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
struct FloatIEEE754
{
    // the term significand was introduced by George Forsythe and Cleve Moler in 1967,
    // and the use of mantissa for this purpose is discouraged by the IEEE floating-point standard committee
    // wowsers
    static const uint32 SignificandMask = 0b00000000011111111111111111111111u; // 23 bits
    static_assert(SignificandMask == 0x7FFFFFu, "Invalid Significand Mask");

    static const uint32 ExponentMask = 0b01111111100000000000000000000000u; // 8 bits
    static_assert(ExponentMask == 0x7F800000u, "Invalid Exponent Mask");

    static const uint32 SignMask = 0b10000000000000000000000000000000u; // 1 bit
    static_assert(SignMask == 0x80000000u, "Invalid Sign Mask");

    FloatIEEE754() : FloatIEEE754(static_cast<uint32>(0u)) {}; // no bits set
    FloatIEEE754(uint32 value) : integer(value) {}
    FloatIEEE754(float value) : fp(value) {}
    FloatIEEE754(uint32 significand, uint32 exponent, uint32 sign) :
        fp(CreateFloat(significand, exponent, sign)) {}

    static float CreateFloat(uint32 significand, uint32 exponent, uint32 sign)
    {
        FloatIEEE754 p;
        p.SetSignificand(significand);
        p.SetExponent(exponent);
        p.SetSign(sign);
        return p.fp;
    }

    uint32 GetSignificand()
    {
        return (integer & SignificandMask);
    }

    uint32 GetExponent()
    {
        return (integer & ExponentMask) >> 23;
    }

    uint32 GetSign()
    {
        return (integer & SignMask) >> 31;
    }

    void SetSignificand(uint32 significand)
    {
        integer = (GetSign() << 31) | (GetExponent() << 23) | significand;
    }

    void SetExponent(uint32 exponent)
    {
        integer = (GetSign() << 31) | (exponent << 23) | GetSignificand();
    }

    void SetSign(uint32 sign)
    {
        integer = (sign << 31) | (GetExponent() << 23) | GetSignificand();
    }

    bool IsNaN()
    {
        return ((integer & ExponentMask) == ExponentMask) && (integer & SignificandMask);
    }

    bool IsInf()
    {
        return ((integer & ExponentMask) == ExponentMask) && !(integer & SignificandMask);
    }

    union
    {
        float fp;
        uint32 integer;
    };
};

// See: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
struct DoubleIEEE754
{
    static const uint64 SignificandMask = 0b0000000000001111111111111111111111111111111111111111111111111111u; // 52 bits
    static_assert(SignificandMask == 0xFFFFFFFFFFFFFu, "Invalid Significand Mask");

    static const uint64 ExponentMask = 0b0111111111110000000000000000000000000000000000000000000000000000u; // 8 bits
    static_assert(ExponentMask == 0x7FF0000000000000u, "Invalid Exponent Mask");

    static const uint64 ExponentBias = (1023 + 52);

    static const uint64 HiddenMask = 0b0000000000010000000000000000000000000000000000000000000000000000u;
    static_assert(HiddenMask == 0x0010000000000000u, "Invalid Hidden Mask");

    static const uint64 SignMask = 0b1000000000000000000000000000000000000000000000000000000000000000u; // 1 bit
    static_assert(SignMask == 0x8000000000000000u, "Invalid Sign Mask");


    DoubleIEEE754() : DoubleIEEE754(static_cast<uint64>(0u)) {}; // no bits set
    DoubleIEEE754(uint64 value) : integer(value) {}
    DoubleIEEE754(double value) : fp(value) {}
    DoubleIEEE754(uint64 significand, uint64 exponent, uint64 sign) :
        fp(CreateDouble(significand, exponent, sign)) {}

    static double CreateDouble(uint64 significand, uint64 exponent, uint64 sign)
    {
        DoubleIEEE754 p;
        p.SetSignificand(significand);
        p.SetExponent(exponent);
        p.SetSign(sign);
        return p.fp;
    }
    
    // TODO: Stuff below is broken and failing tests
    uint64 GetSignificand()
    {
        uint64 frac = (integer & SignificandMask);
        uint64 uexp = GetExponent();
        int64 iexp = *reinterpret_cast<int64*>(&uexp);

        iexp -= 1023;
        frac += HiddenMask;

        if (!(iexp <= -1))
        {
            frac >>= (static_cast<int64>(52) - iexp);
        }

        return frac;
    }

    uint64 GetExponent()
    {
        return ((integer & ExponentMask) >> 52) - 1023;
    }

    uint64 GetSign()
    {
        return (integer & SignMask) >> 63;
    }

    void SetSignificand(uint64 significand)
    {
        integer = (GetSign() << 63) | (GetExponent() << 52) | significand;
    }

    void SetExponent(uint64 exponent)
    {
        integer = (GetSign() << 63) | (exponent << 52) | GetSignificand();
    }

    void SetSign(uint64 sign)
    {
        integer = (sign << 63) | (GetExponent() << 52) | GetSignificand();
    }

    bool IsNaN()
    {
        return ((integer & ExponentMask) == ExponentMask) && (integer & SignificandMask);
    }

    bool IsInf()
    {
        return ((integer & ExponentMask) == ExponentMask) && !(integer & SignificandMask);
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

class Float
{
public:
    Float() : m_value(0.0f) {}
    Float(const float value) : m_value(value) {}

    static Float Zero()
    {
        return Float();
    }

    Float Cos()
    {
        return Float(cosf(m_value));
    }

    Float Sin()
    {
        return Float(sinf(m_value));
    }

    Float Sqrt()
    {
        return Float(sqrtf(m_value));
    }

    Float Pow(Float power)
    {
        return powf(m_value, power);
    }

    operator float()
    {
        return m_value;
    }

private:

#ifdef _DEBUG
    union
    {
        float m_value;

        struct
        {
            uint32 mantissa : 23;
            uint32 exponent : 8;
            uint32 sign : 1;
        } parts;
    };
#else
    float m_value;
#endif
};

class Double
{
public:
    Double() : m_value(0.0) {}
    Double(const double value) : m_value(value) {}

    static Double Zero()
    {
        return Double();
    }

    Double Cos()
    {
        return Double(cos(m_value));
    }

    Double Sin()
    {
        return Double(sin(m_value));
    }

    Double Sqrt()
    {
        return Double(sqrt(m_value));
    }

    Double Pow(Double power)
    {
        return pow(m_value, power);
    }

    operator double()
    {
        return m_value;
    }

private:
    double m_value;
};

// This class minimizes the data usage for a floating point value
// To be used in place of float, double in vector classes where needed
class CompactifiedReal
{
public:
    //
};


// Functions to ensure cross-compatibility with 