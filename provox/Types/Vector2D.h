#pragma once

#include "Real.h"

template<typename T>
class Vector2D
{
public:
    Vector2D() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
    Vector2D(T x, T y) : x(x), y(y) {}
    Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}

    // Common functions
    T LengthSq() const
    {
        return x * x + y * y;
    }

    T Length() const
    {
        return Length().Sqrt();
    }

    T Magnitude() const
    {
        return (x * x + y * y).Sqrt();
    }

    T Normalize()
    {
        T mag = Magnitude();

        if (mag != static_cast<T>(0))
        {
            x /= mag;
            y /= mag;
        }

        return mag;
    }

    T ScaleToLength(T len)
    {
        T length = LengthSq();
        
        if (length < static_cast<T>(1e-6))
        {
            return static_cast<T>(0);
        }

        length = length.Sqrt();

        T scalar = len / length;

        x *= scalar;
        y *= scalar;

        return length;
    }

    T DotProduct(const Vector2D<T>& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y);
    }

    T CrossProduct(const Vector2D<T>& rhs) const
    {
        return (x * rhs.y) - (y * rhs.x);
    }

    T DistanceSq(const Vector2D<T>& rhs) const
    {
        T dx = x - rhs.x;
        T dy = y - rhs.y;

        return dx * dx + dy * dy;
    }

    T Distance(const Vector2D<T>& rhs) const
    {
        return DistanceSq(rhs).Sqrt();
    }

    // Operators
    Vector2D& operator=(const Vector2D& v)
    {
        if (this == &v)
            return *this;

        x = v.x;
        y = v.y;

        return *this;
    }


    Vector2D& operator+= (const Vector2D& v)
    {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vector2D& operator-= (const Vector2D& v)
    {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    Vector2D& operator*= (const float scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    Vector2D& operator*= (const Vector2D& v)
    {
        x *= v.x;
        y *= v.y;

        return *this;
    }

    Vector2D& operator/= (const float scalar)
    {
        x /= scalar;
        y /= scalar;

        return *this;
    }

    Vector2D& operator/= (const Vector2D& v)
    {
        x /= v.x;
        y /= v.y;

        return *this;
    }

    const Vector2D operator+(const Vector2D& v) const
    {
        return Vector2D(*this) += v;
    }

    const Vector2D operator-(const Vector2D& v) const
    {
        return Vector2D(*this) -= v;
    }

    const Vector2D operator*(const float scalar) const
    {
        return Vector2D(*this) *= scalar;
    }

    const Vector2D operator*(const Vector2D& v) const
    {
        return Vector2D(*this) *= v;
    }

    const Vector2D operator/(const float scalar) const
    {
        return Vector2D(*this) /= scalar;
    }

    const Vector2D operator/(const Vector2D& v) const
    {
        return Vector2D(*this) /= v;
    }

    bool operator== (const Vector2D& v) const
    {
        return ((x == v.x) && (y == v.y));
    }

    bool operator!= (const Vector2D& v) const
    {
        return !((x == v.x) && (y == v.y));
    }

    T x, y;
};