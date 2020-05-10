#pragma once

#include "IEEE754.h"
#include <cmath>

class Float
{
public:
    Float() : m_value(0.0f) {}
    Float(const float value) : m_value(value) {}

    Float Add(Float v)
    {
        return m_value.fp + v.m_value.fp;
    }

    Float Subtract(Float v)
    {
        return m_value.fp - v.m_value.fp;
    }

    Float Divide(Float v)
    {
        return m_value.fp / v.m_value.fp;
    }

    Float Multiply(Float v)
    {
        return m_value.fp * v.m_value.fp;
    }

    Float Cos()
    {
        return Float(cosf(m_value.fp));
    }

    Float Sin()
    {
        return Float(sinf(m_value.fp));
    }

    Float Sqrt()
    {
        return Float(sqrtf(m_value.fp));
    }

    Float Pow(Float power)
    {
        return powf(m_value.fp, power);
    }

    operator float()
    {
        return m_value.fp;
    }

    bool operator== (const float v) const
    {
        return m_value.fp == v;
    }

    bool operator== (const Float& v) const
    {
        return m_value.fp == v.m_value.fp;
    }

private:
    FloatIEEE754 m_value;
};

class Double
{
public:
    Double() : m_value(0.0) {}
    Double(const double value) : m_value(value) {}

    Double Add(Double v)
    {
        return m_value.fp + v.m_value.fp;
    }

    Double Subtract(Double v)
    {
        return m_value.fp - v.m_value.fp;
    }

    Double Divide(Double v)
    {
        return m_value.fp / v.m_value.fp;
    }

    Double Multiply(Double v)
    {
        return m_value.fp * v.m_value.fp;
    }

    Double Cos()
    {
        return Double(cos(m_value.fp));
    }

    Double Sin()
    {
        return Double(sin(m_value.fp));
    }

    Double Sqrt()
    {
        return Double(sqrt(m_value.fp));
    }

    Double Pow(Double power)
    {
        return pow(m_value.fp, power.m_value.fp);
    }

    operator double()
    {
        return m_value.fp;
    }

    bool operator== (const double v) const
    {
        return m_value.fp == v;
    }

    bool operator== (const Double& v) const
    {
        return m_value.fp == v.m_value.fp;
    }

private:
    DoubleIEEE754 m_value;
};