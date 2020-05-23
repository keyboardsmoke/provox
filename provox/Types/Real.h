#pragma once

#include "IEEE754.h"
#include <cmath>
#include <exception>

class Double;

class RealException : public std::exception
{
public:
    RealException() = delete;
    RealException(const char* msg) : std::exception(msg) {}
};

class Float
{
public:
    Float() : m_value(0.0f) {}
    Float(const float value) : m_value(value) {}
    Float(const double value) : m_value(static_cast<float>(value)) {}
    Float(const Double& value);
    Float(const uint8 value) : m_value(static_cast<float>(value)) {}
    Float(const uint16 value) : m_value(static_cast<float>(value)) {}
    Float(const uint32 value) : m_value(static_cast<float>(value)) {}
    Float(const uint64 value) : m_value(static_cast<float>(value)) {}
    Float(const int8 value) : m_value(static_cast<float>(value)) {}
    Float(const int16 value) : m_value(static_cast<float>(value)) {}
    Float(const int32 value) : m_value(static_cast<float>(value)) {}
    Float(const int64 value) : m_value(static_cast<float>(value)) {}

    // Getters
    float GetFP() const
    {
        return m_value.fp;
    }

    uint32 GetInteger() const
    {
        return m_value.integer;
    }

    // Math
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

    Float Clamp(Float hi, Float lo)
    {
        if (hi.GetFP() < lo.GetFP())
            throw RealException("High value must be greater than low value for clamp.");

        return (m_value.fp < lo.GetFP()) ? lo.GetFP() : (hi.GetFP() < m_value.fp) ? hi.GetFP() : m_value.fp;
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

    // Operators
    operator float()
    {
        return m_value.fp;
    }

    Float operator=(const Float v)
    {
        m_value.integer = v.m_value.integer;

        return *this;
    }

    Float operator+= (const Float v)
    {
        m_value.fp += v.m_value.fp;

        return *this;
    }

    Float operator-= (const Float v)
    {
        m_value.fp -= v.m_value.fp;

        return *this;
    }

    Float operator*= (const Float v)
    {
        m_value.fp *= v.m_value.fp;

        return *this;
    }

    Float operator/= (const Float v)
    {
        m_value.fp /= v.m_value.fp;

        return *this;
    }

    const Float operator+(const Float v) const
    {
        return Float(*this) += v;
    }

    const Float operator-(const Float v) const
    {
        return Float(*this) -= v;
    }

    const Float operator*(const Float v) const
    {
        return Float(*this) *= v;
    }

    const Float operator/(const Float v) const
    {
        return Float(*this) /= v;
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
    IEEE754::Binary32 m_value;
};

class Double
{
public:
    Double() : m_value(0.0) {}
    Double(const double value) : m_value(value) {}
    Double(const float value) : m_value(static_cast<double>(value)) {}
    Double(const Float& value) : m_value(static_cast<double>(value.GetFP())) {}
    Double(const uint8 value) : m_value(static_cast<double>(value)) {}
    Double(const uint16 value) : m_value(static_cast<double>(value)) {}
    Double(const uint32 value) : m_value(static_cast<double>(value)) {}
    Double(const uint64 value) : m_value(static_cast<double>(value)) {}
    Double(const int8 value) : m_value(static_cast<double>(value)) {}
    Double(const int16 value) : m_value(static_cast<double>(value)) {}
    Double(const int32 value) : m_value(static_cast<double>(value)) {}
    Double(const int64 value) : m_value(static_cast<double>(value)) {}

    // Getters
    double GetFP() const
    {
        return m_value.fp;
    }

    uint64 GetInteger() const
    {
        return m_value.integer;
    }

    // Math
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

    Double Clamp(Double hi, Double lo)
    {
        if (hi.GetFP() < lo.GetFP())
            throw RealException("High value must be greater than low value for clamp.");

        return (m_value.fp < lo.GetFP()) ? lo.GetFP() : (hi.GetFP() < m_value.fp) ? hi.GetFP() : m_value.fp;
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

    Double operator=(const Double& v)
    {
        m_value.integer = v.m_value.integer;

        return *this;
    }

    Double operator=(const Float& v)
    {
        m_value.fp = static_cast<double>(v.GetFP());

        return *this;
    }

    Double operator=(const double v)
    {
        m_value.fp = v;

        return *this;
    }

    Double operator=(const float v)
    {
        m_value.fp = static_cast<double>(v);

        return *this;
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
    IEEE754::Binary64 m_value;
};
