#pragma once

#include <math.h>

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