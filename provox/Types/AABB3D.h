#pragma once

#include "Vector3D.h"

// https://github.com/juj/MathGeoLib/blob/master/src/Geometry/AABB.h
// https://github.com/juj/MathGeoLib/blob/master/src/Geometry/AABB.cpp

template<typename T>
class AABB3D
{
public:
	AABB3D() : m_min(0.0F, 0.0F, 0.0F), m_max(0.0F, 0.0F, 0.0F) {}
	AABB3D(const Vector3D<T>& min, const Vector3D<T>& max) : m_min(min), m_max(max) {}

	Vector3D<T>& Center()
	{
		return (m_min + m_max) * 0.5f;
	}

	Vector3D<T>& Min()
	{
		return m_min;
	}

	Vector3D<T>& Max()
	{
		return m_max;
	}

private:
	Vector3D<T> m_min;
	Vector3D<T> m_max;
};