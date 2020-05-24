#pragma once

#include "Vector3D.h"
#include "Matrix.h"

class Frustum
{
public:
    enum class Type
    {
        /// Set the Frustum type to this value to define the orthographic projection formula. In orthographic projection,
        /// 3D images are projected onto a 2D plane essentially by flattening the object along one direction (the plane normal).
        /// The size of the projected images appear the same independent of their distance to the camera, and distant objects will 
        /// not appear smaller. The shape of the Frustum is identical to an oriented bounding box (OBB).
        Orthographic,

        /// Set the Frustum type to this value to use the perspective projection formula. With perspective projection, the 2D
        /// image is formed by projecting 3D points towards a single point (the eye point/tip) of the Frustum, and computing the
        /// point of intersection of the line of the projection and the near plane of the Frustum.
        /// This corresponds to the optics in the real-world, and objects become smaller as they move to the distance.
        /// The shape of the Frustum is a rectangular pyramid capped from the tip.
        Perspective
    };

    enum class ProjectiveSpace
    {
        /// If this option is chosen, the post-projective unit cube of the Frustum
        /// is modelled after the OpenGL API convention, meaning that in projected space,
        /// points inside the Frustum have the X and Y range in [-1, 1], and Z ranges in [-1, 1],
        /// where the near plane maps to Z=-1, and the far plane maps to Z=1.
        /// @note If you are submitting projection matrices to GPU hardware using the OpenGL API, you *must*
        ///       use this convention. (or otherwise more than half of the precision of the GL depth buffer is wasted)
        GL,

        /// If this option is chosen, the post-projective unit cube is modelled after the
        /// Direct3D API convention, which differs from the GL convention that Z ranges in [0, 1] instead.
        /// Near plane maps to Z=0, and far plane maps to Z=1. The X and Y range in [-1, 1] as is with GL.
        /// @note If you are submitting projection matrices to GPU hardware using the Direct3D API, you *must*
        ///       use this convention. (or otherwise objects will clip too near of the camera)
        D3D
    };

    enum class Handedness
    {
        /// If a Frustum is left-handed, then in the local space of the Frustum (the view space), the camera looks towards +Z,
        /// while +Y goes towards up, and +X goes towards right.
        /// @note The fixed-pipeline D3D9 API traditionally used the FrustumLeftHanded convention.
        Left,

        /// If a Frustum is right-handed, then the camera looks towards -Z, +Y is up, and +X is right.
        /// @note The fixed-pipeline OpenGL API traditionally used the FrustumRightHanded convention.
        Right
    };

private:
    Type m_type;
    ProjectiveSpace m_projSpace;
    Handedness m_handedness;
};
