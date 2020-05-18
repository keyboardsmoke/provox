#include "catch.hpp"

#include "platform.h"
#include "types.h"

TEST_CASE("Fixed Real tests")
{
    SECTION("Fractional Exponent")
    {
        // 8 bits for significand
        // 7 bits for fractional
        // 1 bit for sign
        // 2 byte floating point!
        FixedFractionalExponentReal<8, 7, 1000> fixed(1, 0);

        REQUIRE(fixed.GetByteSize() == 2);
    }
}
