#include "catch.hpp"
#include "platform.h"
#include "Types/Real.h"

TEST_CASE("ieee754 tests")
{
	SECTION("Get Float")
	{
		FloatIEEE754 fp1(12883.1882f);
		FloatIEEE754 fp2(-12883.1882f);

		REQUIRE(fp1.GetSign() == 0u);
		REQUIRE(fp1.GetExponent() == 140u);
		REQUIRE(fp1.GetSignificand() == 4803777u);

		REQUIRE(fp2.GetSign() == 1u);
		REQUIRE(fp2.GetExponent() == 140u);
		REQUIRE(fp2.GetSignificand() == 4803777u);
	}

	SECTION("Set Float")
	{
		FloatIEEE754 fp;
		fp.SetSign(0u);
		fp.SetExponent(161u);
		fp.SetSignificand(5372589u);

		REQUIRE(*reinterpret_cast<uint32*>(&fp.fp) == 0x50d1faad);
	}

	SECTION("Get Double")
	{
		DoubleIEEE754 fp1(12883.1882);
		DoubleIEEE754 fp2(-12883.1882);

		REQUIRE(fp1.GetSign() == 0u);
		REQUIRE(fp1.GetExponent() == 0b10000001100u);
		REQUIRE(fp1.GetSignificand() == 0b1001001010011001100000010110111100000000011010001101u);

		REQUIRE(fp2.GetSign() == 1u);
		REQUIRE(fp2.GetExponent() == 140u);
		REQUIRE(fp2.GetSignificand() == 4803777u);
	}

	SECTION("Set Double")
	{
		//
	}
}