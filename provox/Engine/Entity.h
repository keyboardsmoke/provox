#pragma once

#include <vector>

#include "Types/Vector3D.h"
#include "Engine/Voxel.h"

// Entity base

class Entity
{
public:
    Vector3D<Float>& GetPosition()
    {
        return m_position;
    }

    Vector3D<Float>& GetAngle()
    {
        return m_angle;
    }

private:
    Vector3D<Float> m_position;
    Vector3D<Float> m_angle;
    
    // Calculated bounding box based on voxels
    // These are calculated only when entities are:
    //        - Created
    //        - Enjoined
    //        - Split
    // These are _not_ sizes of an entity, it is the bounds under which they operate
    // Meaning, these should never be used for collision, they are only used
    // for intersection, and only to retrieve the root entity associated with subentities
    // For example, you do a line trace and intersect an entity's bounds, you may not immediately know
    // what subentity you hit, because subentities do not store their root. But you've found a root,
    // and can now calculate which subentity you have collided with after you enter the bounds space.
    Vector3D<Float> m_minBB;
    Vector3D<Float> m_maxBB;

    // The concept of voxels I want to have here, is a "root" object
    // and each voxel is like a sub-object of that object, relative from the root position
    // This will optimize for limit RAM usage, although complicate mathematical operations...
    // These are filled/reallocated only when entities are:
    //        - Created
    //        - Enjoined
    //        - Split
    std::vector<Voxel> m_voxels;
};
