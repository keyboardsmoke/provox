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
    void Rotate(const T angle)
    {
        T xt = (x * angle.Cos()) - (y * angle.Sin());
        T yt = (y * angle.Cos()) + (x * angle.Sin());

        x = xt;
        y = yt;
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

    T DotProduct(const Vector2D<T>& v) const
    {
        return (x * v.x) + (y * v.y);
    }

    T CrossProduct(const Vector2D<T>& v) const
    {
        return (x * v.y) - (y * v.x);
    }

    T Distance(const Vector2D<T>& v) const
    {
        return (v.x - x).Pow(T(2)) + (v.y - y).Pow(T(2));
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