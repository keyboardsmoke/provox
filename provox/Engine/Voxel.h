#pragma once

// The default voxel size
#define PROVOX_VOXEL_SIZE Float(1.0F)

class Entity;

class Voxel
{
public:
    // +/- from the root entity position
    // Because it isn't a "real" yet, we can't use Vector(x)D
    // Besides building "voxel entities", this may also help with particle emitters
    Vector3D<Float> GetOffsetPosition()
    {
        return Vector3D<Float>(
            Float(xoffset) * PROVOX_VOXEL_SIZE,
            Float(yoffset) * PROVOX_VOXEL_SIZE,
            Float(zoffset) * PROVOX_VOXEL_SIZE);
    }

    Vector3D<Float> GetWorldPosition(Entity* root);

private:
    int16 xoffset;
    int16 yoffset;
    int16 zoffset;
};
