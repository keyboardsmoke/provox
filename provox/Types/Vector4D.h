#pragma once

template<typename T>
class Vector4D
{
public:

    Vector4D() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0)) {}
    Vector4D(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    Vector4D(const Vector4D& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

    T x, y, z, w;
};
