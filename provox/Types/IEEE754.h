#pragma once

#include "platform.h"

#pragma pack(push, 1)

// TODO: Float16, not really.... needed
// https://github.com/facebookincubator/gloo/blob/master/gloo/types.h

namespace IEEE754
{

    enum class Class
    {
        Zero,
        Subnormal,
        Infinite,
        NaN,
        Normal
    };

    // See: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
    struct Binary32
    {
        typedef uint32 SignificandType;
        typedef int16 ExponentType;
        typedef uint8 SignType;

    private:
        // the term significand was introduced by George Forsythe and Cleve Moler in 1967,
        // and the use of mantissa for this purpose is discouraged by the IEEE floating-point standard committee
        // wowsers
        static const uint32 SignificandMask = 0b00000000011111111111111111111111u; // 23 bits
        static const uint32 SignificandHighBit = 0b00000000010000000000000000000000u;
        static const uint32 ExponentMask = 0b01111111100000000000000000000000u; // 8 bits
        static const uint32 SignMask = 0b10000000000000000000000000000000u; // 1 bit
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
        Binary32() : Binary32(static_cast<uint32>(0u)) {}; // no bits set
        Binary32(uint32 value) : integer(value) {}
        Binary32(float value) : fp(value) {}
        Binary32(SignificandType significand, ExponentType exponent, SignType sign) :
            integer(CreateBinary32(significand, exponent, sign)) {}

        static uint32 CreateBinary32(SignificandType significand, ExponentType exponent, SignType sign)
        {
            Binary32 p;
            p.SetSignificand(significand);
            p.SetExponent(exponent);
            p.SetSign(sign);
            return p.integer;
        }

        static Binary32 GetNaN()
        {
            return Binary32(Indeterminate);
        }

        static Binary32 GetNegativeNaN()
        {
            return Binary32(NegativeIndeterminate);
        }

        static Binary32 GetInfinte()
        {
            return Binary32(0, 0xFF, 0);
        }

        static Binary32 GetNegativeInfinite()
        {
            return Binary32(0, 0xFF, 1);
        }

        static Binary32 GetZero()
        {
            return Binary32(0, 0, 0);
        }

        static Binary32 GetNegativeZero()
        {
            return Binary32(0, 0, 1);
        }

        // Getters
        SignificandType GetSignificand() const
        {
            return (integer & SignificandMask);
        }

        ExponentType GetExponent() const
        {
            return static_cast<ExponentType>((integer & ExponentMask) >> 23);
        }

        SignType GetSign() const
        {
            return (integer & SignMask) >> 31;
        }

        // Setters
        void SetSignificand(SignificandType significand)
        {
            integer = (static_cast<uint32>(GetSign()) << 31) | (static_cast<uint32>(GetExponent()) << 23) | significand;
        }

        void SetExponent(ExponentType exponent)
        {
            integer = (static_cast<uint32>(GetSign()) << 31) | (static_cast<uint32>(exponent) << 23) | GetSignificand();
        }

        void SetSign(SignType sign)
        {
            integer = (static_cast<uint32>(sign) << 31) | (static_cast<uint32>(GetExponent()) << 23) | GetSignificand();
        }

        // 
        Class GetClassification() const
        {
            const ExponentType exp = GetExponent();
            const SignificandType sig = GetSignificand();

            if (exp == 0)
            {
                if (sig == 0)
                {
                    return Class::Zero;
                }

                return Class::Subnormal;
            }

            if (exp == 0xFF)
            {
                if (sig == 0)
                {
                    return Class::Infinite;
                }

                return Class::NaN;
            }

            return Class::Normal;
        }

        bool IsZero() const
        {
            return (GetSignificand() == 0 && GetExponent() == 0);
        }

        bool IsNormal() const
        {
            // The quick way
            const ExponentType exp = GetExponent();

            return (exp != 0 && exp != 0xFF);
        }

        bool IsSubnormal() const
        {
            return (GetExponent() == 0 && GetSignificand() != 0);
        }

        bool IsNaN() const
        {
            // (integer == Indeterminate || integer == NegativeIndeterminate)

            return (GetExponent() == 0xFF && GetSignificand() != 0);
        }

        bool IsInf() const
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

    // See: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
    struct Binary64
    {
        typedef uint64 SignificandType;
        typedef int16 ExponentType;
        typedef uint8 SignType;

    private:
        static const uint64 SignificandMask = 0b0000000000001111111111111111111111111111111111111111111111111111u; // 52 bits
        static const uint64 SignificandHighBit = 0b0000000000001000000000000000000000000000000000000000000000000000u;
        static const uint64 ExponentMask = 0b0111111111110000000000000000000000000000000000000000000000000000u; // 11 bits
        static const uint64 SignMask = 0b1000000000000000000000000000000000000000000000000000000000000000u; // 1 bit

        static const uint64 Infinity = ExponentMask; // 1.#INF (0x7FF0000000000000u)
        static const uint64 NegativeInfinity = SignMask | Infinity; // -1.#INF (0xFFF0000000000000u)
        static const uint64 Indeterminate = ExponentMask | SignificandHighBit; // 1.#IND (0x7FF8000000000000u)
        static const uint64 NegativeIndeterminate = SignMask | ExponentMask | SignificandHighBit; // -1.#IND (0xFFF8000000000000u)

        static_assert(SignificandMask == 0x000FFFFFFFFFFFFFu, "Invalid Significand Mask");
        static_assert(SignificandHighBit == 0x0008000000000000u, "Invalid High Bit Mask");
        static_assert(ExponentMask == 0x7FF0000000000000u, "Invalid Exponent Mask");
        static_assert(SignMask == 0x8000000000000000u, "Invalid Sign Mask");

        static_assert(Infinity == 0x7FF0000000000000u, "Invalid Infinity");
        static_assert(NegativeInfinity == 0xFFF0000000000000u, "Invalid Negative Infinity");
        static_assert(Indeterminate == 0x7FF8000000000000u, "Invalid Indeterminate");
        static_assert(NegativeIndeterminate == 0xFFF8000000000000u, "Invalid Negative Indeterminate");

    public:
        Binary64() : Binary64(static_cast<uint64>(0u)) {}; // no bits set
        Binary64(uint64 value) : integer(value) {}
        Binary64(double value) : fp(value) {}
        Binary64(SignificandType significand, ExponentType exponent, SignType sign) :
            integer(CreateBinary64(significand, exponent, sign)) {}

        static uint64 CreateBinary64(SignificandType significand, ExponentType exponent, SignType sign)
        {
            Binary64 p;
            p.SetSignificand(significand);
            p.SetExponent(exponent);
            p.SetSign(sign);
            return p.integer;
        }

        static Binary64 GetNaN()
        {
            return Binary64(Indeterminate);
        }

        static Binary64 GetNegativeNaN()
        {
            return Binary64(NegativeIndeterminate);
        }

        static Binary64 GetInfinte()
        {
            return Binary64(0, -1, 0);
        }

        static Binary64 GetNegativeInfinite()
        {
            return Binary64(0, -1, 1);
        }

        static Binary64 GetZero()
        {
            return Binary64(0, 0, 0);
        }

        static Binary64 GetNegativeZero()
        {
            return Binary64(0, 0, 1);
        }

        SignificandType GetSignificand() const
        {
            return (integer & SignificandMask);
        }

        ExponentType GetExponent() const
        {
            return (integer & ExponentMask) >> 52;
        }

        SignType GetSign() const
        {
            return (integer & SignMask) >> 63;
        }

        void SetSignificand(SignificandType significand)
        {
            integer = (static_cast<uint64>(GetSign()) << 63) | (static_cast<uint64>(GetExponent()) << 52) | significand;
        }

        void SetExponent(ExponentType exponent)
        {
            integer = (static_cast<uint64>(GetSign()) << 63) | (static_cast<uint64>(exponent) << 52) | GetSignificand();
        }

        void SetSign(SignType sign)
        {
            integer = (static_cast<uint64>(sign) << 63) | (static_cast<uint64>(GetExponent()) << 52) | GetSignificand();
        }

        // 
        Class GetClassification() const
        {
            const ExponentType exp = GetExponent();
            const SignificandType sig = GetSignificand();

            if (exp == 0)
            {
                if (sig == 0)
                {
                    return Class::Zero;
                }

                return Class::Subnormal;
            }

            if ((exp & 0x7ff) == 0x7ff)
            {
                if (sig == 0)
                {
                    return Class::Infinite;
                }

                return Class::NaN;
            }

            return Class::Normal;
        }

        bool IsZero() const
        {
            return (GetSignificand() == 0 && GetExponent() == 0);
        }

        bool IsNormal() const
        {
            // The quick way
            const ExponentType exp = GetExponent();

            return (exp != 0 && exp != 0xFFF);
        }

        bool IsSubnormal() const
        {
            return (GetExponent() == 0 && GetSignificand() != 0);
        }

        bool IsNaN() const
        {
            // (integer == Indeterminate || integer == NegativeIndeterminate)

            return ((GetExponent() & 0x7FF) == 0x7FF && GetSignificand() != 0);
        }

        bool IsInf() const
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

    struct Binary16
    {
        typedef uint16 SignificandType;
        typedef int8 ExponentType;
        typedef uint8 SignType;

    private:
        static const uint16 SignificandMask = 0b0000001111111111u;
        static const uint16 SignificandHighBit = 0b0000001000000000u;
        static const uint16 ExponentMask = 0b0111110000000000u;
        static const uint16 SignMask = 0b1000000000000000u;
        static const uint16 Infinity = ExponentMask;
        static const uint16 NegativeInfinity = SignMask | Infinity;
        static const uint16 Indeterminate = ExponentMask | SignificandHighBit;
        static const uint16 NegativeIndeterminate = SignMask | ExponentMask | SignificandHighBit;

        // Private asserts
        static_assert(SignificandMask == 0x3FFu, "Invalid Significand Mask");
        static_assert(SignificandHighBit == 0x200u, "Invalid Signficand High bit");
        static_assert(ExponentMask == 0x7C00u, "Invalid Exponent Mask");
        static_assert(SignMask == 0x8000u, "Invalid Sign Mask");

    public:
        Binary16() : Binary16(static_cast<uint16>(0u)) {}; // no bits set
        Binary16(uint16 value) : integer(value) {}
        Binary16(float value) : integer(CreateBinary16(value)) {}
        Binary16(SignificandType significand, ExponentType exponent, SignType sign) :
            integer(CreateBinary16(significand, exponent, sign)) {}

        static uint16 CreateBinary16(const Binary32& v)
        {
            uint32 exp = v.GetExponent();
            uint32 sig = v.GetSignificand();
            uint8 sign = v.GetSign();

            const uint32 maxExp = (1 << 5) - 1;

            int trueExp = exp - 127;
            int newExp;

            if (v.IsNormal())
            {
                newExp = trueExp + 15;

                if (newExp >= (int)maxExp)
                {
                    newExp = maxExp;
                    sig = 0;
                }

                if (newExp <= 0)
                    newExp = sig = 0;
            }
            else
            {
                newExp = exp;
            }

            uint32 newSignificand = sig >> (23 - 10);

            if (v.IsNaN() && newSignificand == 0)
                newSignificand = 1;

            return CreateBinary16(newSignificand, newExp, sign);
        }

        static uint16 CreateBinary16(SignificandType significand, ExponentType exponent, SignType sign)
        {
            Binary16 p;
            p.SetSignificand(significand);
            p.SetExponent(exponent);
            p.SetSign(sign);
            return p.integer;
        }

        static Binary16 GetNaN()
        {
            return Binary16(Indeterminate);
        }

        static Binary16 GetNegativeNaN()
        {
            return Binary16(NegativeIndeterminate);
        }

        static Binary16 GetInfinte()
        {
            return Binary16(Infinity);
        }

        static Binary16 GetNegativeInfinite()
        {
            return Binary16(NegativeInfinity);
        }

        static Binary16 GetZero()
        {
            return Binary16(0, 0, 0);
        }

        static Binary16 GetNegativeZero()
        {
            return Binary16(0, 0, 1);
        }

        // Getters
        float GetFP() const
        {
            uint32 sign = (integer & SignMask) >> 15;
            uint32 exp = (integer & ExponentMask);
            uint32 sig = (integer & SignificandMask);

            sig <<= 13;

            if (exp == ExponentMask)
            {
                exp = 0xFF;
            }
            else if (exp != 0)
            {
                exp = (exp >> 10) - 15 + 127;
            }

            return Binary32(
                static_cast<Binary32::SignificandType>(sig),
                static_cast<Binary32::ExponentType>(exp),
                static_cast<Binary32::SignType>(sign)).fp;
        }

        SignificandType GetSignificand() const
        {
            return (integer & SignificandMask);
        }

        ExponentType GetExponent() const
        {
            return static_cast<int8>((integer & ExponentMask) >> 10);
        }

        SignType GetSign() const
        {
            return (integer & SignMask) >> 15;
        }

        // Setters
        void SetSignificand(SignificandType significand)
        {
            integer = (static_cast<uint16>(GetSign()) << 15) | (static_cast<uint16>(GetExponent()) << 10) | significand;
        }

        void SetExponent(ExponentType exponent)
        {
            integer = (static_cast<uint16>(GetSign()) << 15) | (static_cast<uint16>(exponent) << 10) | GetSignificand();
        }

        void SetSign(SignType sign)
        {
            integer = (static_cast<uint16>(sign) << 15) | (static_cast<uint16>(GetExponent()) << 10) | GetSignificand();
        }

        // 
        Class GetClassification() const
        {
            const ExponentType exp = GetExponent();
            const SignificandType sig = GetSignificand();

            if (exp == 0)
            {
                if (sig == 0)
                {
                    return Class::Zero;
                }

                return Class::Subnormal;
            }

            if (exp == 0x1F)
            {
                if (sig == 0)
                {
                    return Class::Infinite;
                }

                return Class::NaN;
            }

            return Class::Normal;
        }

        bool IsZero()
        {
            return (GetSignificand() == 0 && GetExponent() == 0);
        }

        bool IsNormal() const
        {
            // The quick way
            const ExponentType exp = GetExponent();

            return (exp != 0 && exp != 0xFF);
        }

        bool IsSubnormal() const
        {
            return (GetExponent() == 0 && GetSignificand() != 0);
        }

        bool IsNaN() const
        {
            // (integer == Indeterminate || integer == NegativeIndeterminate)

            return (GetExponent() == 0x1F && GetSignificand() != 0);
        }

        bool IsInf() const
        {
            // (integer == Infinity || integer == NegativeInfinity)

            return (GetExponent() == 0x1F && GetSignificand() == 0);
        }

        uint16 integer;
    };

}

#pragma pack(pop)

static_assert(sizeof(uint16) == sizeof(IEEE754::Binary16), "Invalid size for IEEE754::Binary16");
static_assert(sizeof(uint32) == sizeof(IEEE754::Binary32), "Invalid size for IEEE754::Binary32");
static_assert(sizeof(uint64) == sizeof(IEEE754::Binary64), "Invalid size for IEEE754::Binary64");
