#include "catch.hpp"
#include "platform.h"
#include "Types/Real.h"
#include <limits>

// Match our native ordering
static int NativeClasses[] =
{
	FP_ZERO,
	FP_SUBNORMAL,
	FP_INFINITE,
	FP_NAN,
	FP_NORMAL
};

TEST_CASE("ieee754_64")
{
	SECTION("Get Double")
	{
		DoubleIEEE754 fp1(12883.1882);
		DoubleIEEE754 fp2(-12883.1882);

		REQUIRE(fp1.GetSign() == 0u);
		REQUIRE(fp1.GetExponent() == 1036u);
		REQUIRE(fp1.GetSignificand() == 0x9299816f0068e);

		REQUIRE(fp2.GetSign() == 1u);
		REQUIRE(fp2.GetExponent() == 1036u);
		REQUIRE(fp2.GetSignificand() == 0x9299816f0068e);
	}

	SECTION("Set Double")
	{
		DoubleIEEE754 fp;
		fp.SetSign(0u);
		fp.SetExponent(1039u);
		fp.SetSignificand(0x83321f8b91f8e);

		REQUIRE(fp.integer == 0x40f83321f8b91f8e);
	}

	SECTION("Test ClassificationDP")
	{
		DoubleIEEE754 zerofp = DoubleIEEE754::GetZero();
		DoubleIEEE754 negzerofp = DoubleIEEE754::GetNegativeZero();
		DoubleIEEE754 nanfp = DoubleIEEE754::GetNaN();
		DoubleIEEE754 negnanfp = DoubleIEEE754::GetNegativeNaN();
		DoubleIEEE754 inffp = DoubleIEEE754::GetInfinte();
		DoubleIEEE754 neginffp = DoubleIEEE754::GetNegativeInfinite();
		DoubleIEEE754 rn(2.0);

		REQUIRE(NativeClasses[static_cast<uint32>(zerofp.GetClassification())] == fpclassify(zerofp.fp));
		REQUIRE(zerofp.IsZero());
		REQUIRE(zerofp.fp == 0.0);

		REQUIRE(NativeClasses[static_cast<uint32>(negzerofp.GetClassification())] == fpclassify(negzerofp.fp));
		REQUIRE(negzerofp.IsZero());
		REQUIRE(negzerofp.fp == -0.0);

		REQUIRE(NativeClasses[static_cast<uint32>(nanfp.GetClassification())] == fpclassify(nanfp.fp));
		REQUIRE(nanfp.IsNaN());
		REQUIRE(isnan<double>(nanfp.fp));

		REQUIRE(NativeClasses[static_cast<uint32>(negnanfp.GetClassification())] == fpclassify(negnanfp.fp));
		REQUIRE(negnanfp.IsNaN());
		REQUIRE(isnan<double>(negnanfp.fp));

		REQUIRE(NativeClasses[static_cast<uint32>(inffp.GetClassification())] == fpclassify(inffp.fp));
		REQUIRE(inffp.IsInf());
		REQUIRE(isinf<double>(inffp.fp));

		REQUIRE(NativeClasses[static_cast<uint32>(neginffp.GetClassification())] == fpclassify(neginffp.fp));
		REQUIRE(neginffp.IsInf());
		REQUIRE(isinf<double>(neginffp.fp));

		REQUIRE(NativeClasses[static_cast<uint32>(rn.GetClassification())] == fpclassify(rn.fp));
		REQUIRE(rn.IsNormal());
		REQUIRE(!rn.IsSubnormal());
		REQUIRE(isnormal<double>(rn.fp));
	}

	SECTION("Test NaN")
	{
		DoubleIEEE754 fp1(std::numeric_limits<double>::quiet_NaN());
		DoubleIEEE754 fp2(-std::numeric_limits<double>::quiet_NaN());
		DoubleIEEE754 fp3(DoubleIEEE754::GetNaN());
		DoubleIEEE754 fp4(DoubleIEEE754::GetNegativeNaN());

		REQUIRE(fp1.integer == fp3.integer);
		REQUIRE(fp2.integer == fp4.integer);

		REQUIRE(NativeClasses[static_cast<uint32>(fp1.GetClassification())] == fpclassify(fp1.fp));
		REQUIRE(NativeClasses[static_cast<uint32>(fp2.GetClassification())] == fpclassify(fp2.fp));
		REQUIRE(NativeClasses[static_cast<uint32>(fp3.GetClassification())] == fpclassify(fp3.fp));
		REQUIRE(NativeClasses[static_cast<uint32>(fp4.GetClassification())] == fpclassify(fp4.fp));

		bool NaNTest = (fp1.IsNaN() && fp2.IsNaN() && fp3.IsNaN() && fp4.IsNaN());

		REQUIRE(NaNTest);
	}

	SECTION("Test Finite")
	{
		DoubleIEEE754 fp1(std::numeric_limits<double>::infinity());
		DoubleIEEE754 fp2(-std::numeric_limits<double>::infinity());
		DoubleIEEE754 fp3(DoubleIEEE754::GetInfinte());
		DoubleIEEE754 fp4(DoubleIEEE754::GetNegativeInfinite());

		REQUIRE(fp1.integer == fp3.integer);
		REQUIRE(fp2.integer == fp4.integer);

		REQUIRE(NativeClasses[static_cast<uint32>(fp1.GetClassification())] == fpclassify(fp1.fp));
		REQUIRE(NativeClasses[static_cast<uint32>(fp2.GetClassification())] == fpclassify(fp2.fp));
		REQUIRE(NativeClasses[static_cast<uint32>(fp3.GetClassification())] == fpclassify(fp3.fp));
		REQUIRE(NativeClasses[static_cast<uint32>(fp4.GetClassification())] == fpclassify(fp4.fp));

		bool InfTest = (fp1.IsInf() && fp2.IsInf() && fp3.IsInf() && fp4.IsInf());

		REQUIRE(InfTest);
	}
}