#pragma once

#include "Vector3D.h"

// https://github.com/juj/MathGeoLib/blob/master/src/Geometry/OBB.h
// https://github.com/juj/MathGeoLib/blob/master/src/Geometry/OBB.cpp
// Good lib :)

template<typename T>
class OBB3D
{
public:
	//

private:
	// In the local space of the OBB, the center of this OBB is at (r.x,r.y,r.z), and the OBB is an AABB with size 2 * r.
	Vector3D<T> m_pos;

	// Stores half-sizes to x, y and z directions in the local space of this OBB.
	// These members should be positive to represent a non-degenerate OBB.
	Vector3D<T> m_r;

	// Specifies normalized direction vectors for the local axes.
	/*
		m_axis[0] specifies the +X direction in the local space of this OBB, m_axis[1] the +Y direction and m_axis[2] the +Z direction.
		The scale of these vectors is always normalized. The half-length of the OBB along its local axes is specified by the vector r.
		The axis vectors must always be orthonormal. Be sure to guarantee that condition holds if you directly set to this member variable.
	*/
	Vector3D<T> m_axis[3];
};