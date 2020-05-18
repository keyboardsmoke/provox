#include "catch.hpp"
#include "platform.h"
#include "Types/Real.h"
#include "Types/Vector2D.h"
#include "Types/Vector3D.h"
#include "Types/Vector4D.h"

TEST_CASE("Vector tests")
{
    Vector2D<Float> a1;
    Vector2D<Float> a2;

    REQUIRE(a1 == a2);
}
