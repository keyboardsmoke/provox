#pragma once

template<typename T>
class Vector3D
{
public:

    Vector3D() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}
    Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z) {}

    // Common functions
    T Magnitude() const
    {
        return (x * x + y * y + z * z).Sqrt();
    }

    T Normalize()
    {
        T mag = Magnitude();

        if (mag != static_cast<T>(0))
        {
            x /= mag;
            y /= mag;
            z /= mag;
        }

        return mag;
    }

    T DotProduct(const Vector3D<T>& v) const
    {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    T CrossProduct(const Vector3D<T>& v) const
    {
        return (x * v.y) - (y * v.x) - (z * v.z);
    }

    T Distance(const Vector3D<T>& v) const
    {
        return (v.x - x).Pow(T(2)) + (v.y - y).Pow(T(2)) + (v.z - z).Pow(T(2));
    }

    // Operators
    Vector3D& operator=(const Vector3D& v)
    {
        if (this == &v)
            return *this;

        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }


    Vector3D& operator+= (const Vector3D& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }

    Vector3D& operator-= (const Vector3D& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    Vector3D& operator*= (const float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    Vector3D& operator*= (const Vector3D& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return *this;
    }

    Vector3D& operator/= (const float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    Vector3D& operator/= (const Vector3D& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return *this;
    }

    const Vector3D operator+(const Vector3D& v) const
    {
        return Vector3D(*this) += v;
    }

    const Vector3D operator-(const Vector3D& v) const
    {
        return Vector3D(*this) -= v;
    }

    const Vector3D operator*(const float scalar) const
    {
        return Vector3D(*this) *= scalar;
    }

    const Vector3D operator*(const Vector3D& v) const
    {
        return Vector3D(*this) *= v;
    }

    const Vector3D operator/(const float scalar) const
    {
        return Vector3D(*this) /= scalar;
    }

    const Vector3D operator/(const Vector3D& v) const
    {
        return Vector3D(*this) /= v;
    }

    bool operator== (const Vector3D& v) const
    {
        return ((x == v.x) && (y == v.y) && (z == v.z));
    }

    bool operator!= (const Vector3D& v) const
    {
        return !((x == v.x) && (y == v.y) && (z == v.z));
    }

    T x, y, z;
};