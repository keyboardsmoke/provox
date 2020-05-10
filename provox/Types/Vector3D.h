#pragma once

template<typename T>
class Vector3D
{
public:

    Vector3D() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}
    Vector3D(T x, T y, T z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z) {}

    T x, y, z;
};