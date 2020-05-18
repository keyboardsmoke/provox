#include "pch.h"
#include "Voxel.h"
#include "Entity.h"

Vector3D<Float> Voxel::GetWorldPosition(Entity* root)
{
    return root->GetPosition() + GetOffsetPosition();
}
