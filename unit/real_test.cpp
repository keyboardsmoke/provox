#include "doctest/doctest.h"
#include "platform.h"
#include "Types/Real.h"

TEST_CASE("Real tests")
{
    SUBCASE("Power")
    {
        Float v(10.0F);

        REQUIRE(v.Pow(10.0F) == 10000000000.0F);
    }

    SUBCASE("Sqrt")
    {
        Float v(360.0F);

        REQUIRE(v.Sqrt() == 18.973665961F);
    }
}
