#pragma once

#include "Vector2D.h"

// https://github.com/juj/MathGeoLib/blob/master/src/Geometry/OBB2D.h
// https://github.com/juj/MathGeoLib/blob/master/src/Geometry/OBB2D.cpp
// Good lib :)

template<typename T>
class OBB2D
{
public:
	//

private:
	// The center position of this OBB.
	// In the local space of the OBB, the center of this OBB is at (r.x,r.y), and the OBB is an AABB with size 2 * r.
	Vector2D<T> m_pos;

	// Stores half-sizes to x and y directions in the local space of this OBB2D.
	// These members should be positive to represent a non-degenerate OBB.
	Vector2D<T> m_r;

	// Specifies normalized direction vectors for the local axes.
	/*
		m_axis specifies the +X direction in the local space of this OBB2D.
		The scale of this vector is always normalized. The half-length of the OBB2D along its local axes is specified by the vector r.
		The axis vectors must always be orthonormal. Be sure to guarantee that condition holds if you directly set to this member variable.
	*/
	Vector2D<T> m_axis;
};