#include "doctest/doctest.h"
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

TEST_CASE("ieee754_32")
{
    SUBCASE("Get Float")
    {
        IEEE754::Binary32 fp1(12883.1882f);
        IEEE754::Binary32 fp2(-12883.1882f);

        REQUIRE(fp1.GetSign() == 0u);
        REQUIRE(fp1.GetExponent() == 140u);
        REQUIRE(fp1.GetSignificand() == 4803777u);

        REQUIRE(fp2.GetSign() == 1u);
        REQUIRE(fp2.GetExponent() == 140u);
        REQUIRE(fp2.GetSignificand() == 4803777u);
    }

    SUBCASE("Set Float")
    {
        IEEE754::Binary32 fp;
        fp.SetSign(0u);
        fp.SetExponent(161u);
        fp.SetSignificand(5372589u);

        REQUIRE(fp.integer == 0x50d1faad);
    }

    SUBCASE("Test ClassificationFP")
    {
        IEEE754::Binary32 zerofp = IEEE754::Binary32::GetZero();
        IEEE754::Binary32 negzerofp = IEEE754::Binary32::GetNegativeZero();
        IEEE754::Binary32 nanfp = IEEE754::Binary32::GetNaN();
        IEEE754::Binary32 negnanfp = IEEE754::Binary32::GetNegativeNaN();
        IEEE754::Binary32 inffp = IEEE754::Binary32::GetInfinte();
        IEEE754::Binary32 neginffp = IEEE754::Binary32::GetNegativeInfinite();
        IEEE754::Binary32 rn(2.0f);

        REQUIRE(NativeClasses[static_cast<uint32>(zerofp.GetClassification())] == fpclassify(zerofp.fp));
        REQUIRE(zerofp.IsZero());
        REQUIRE(zerofp.fp == 0.0f);

        REQUIRE(NativeClasses[static_cast<uint32>(negzerofp.GetClassification())] == fpclassify(negzerofp.fp));
        REQUIRE(negzerofp.IsZero());
        REQUIRE(negzerofp.fp == -0.0f);

        REQUIRE(NativeClasses[static_cast<uint32>(nanfp.GetClassification())] == fpclassify(nanfp.fp));
        REQUIRE(nanfp.IsNaN());
        REQUIRE(isnan<float>(nanfp.fp));

        REQUIRE(NativeClasses[static_cast<uint32>(negnanfp.GetClassification())] == fpclassify(negnanfp.fp));
        REQUIRE(negnanfp.IsNaN());
        REQUIRE(isnan<float>(negnanfp.fp));

        REQUIRE(NativeClasses[static_cast<uint32>(inffp.GetClassification())] == fpclassify(inffp.fp));
        REQUIRE(inffp.IsInf());
        REQUIRE(isinf<float>(inffp.fp));

        REQUIRE(NativeClasses[static_cast<uint32>(neginffp.GetClassification())] == fpclassify(neginffp.fp));
        REQUIRE(neginffp.IsInf());
        REQUIRE(isinf<float>(neginffp.fp));

        REQUIRE(NativeClasses[static_cast<uint32>(rn.GetClassification())] == fpclassify(rn.fp));
        REQUIRE(rn.IsNormal());
        REQUIRE(!rn.IsSubnormal());
        REQUIRE(isnormal<float>(rn.fp));
    }

    SUBCASE("Test NaN")
    {
        IEEE754::Binary32 fp1(std::numeric_limits<float>::quiet_NaN());
        IEEE754::Binary32 fp2(-std::numeric_limits<float>::quiet_NaN());
        IEEE754::Binary32 fp3(IEEE754::Binary32::GetNaN());
        IEEE754::Binary32 fp4(IEEE754::Binary32::GetNegativeNaN());

        REQUIRE(fp1.integer == fp3.integer);
        REQUIRE(fp2.integer == fp4.integer);

        REQUIRE(NativeClasses[static_cast<uint32>(fp1.GetClassification())] == fpclassify(fp1.fp));
        REQUIRE(NativeClasses[static_cast<uint32>(fp2.GetClassification())] == fpclassify(fp2.fp));
        REQUIRE(NativeClasses[static_cast<uint32>(fp3.GetClassification())] == fpclassify(fp3.fp));
        REQUIRE(NativeClasses[static_cast<uint32>(fp4.GetClassification())] == fpclassify(fp4.fp));

        bool NaNTest = (fp1.IsNaN() && fp2.IsNaN() && fp3.IsNaN() && fp4.IsNaN());

        REQUIRE(NaNTest);
    }

    SUBCASE("Test Finite")
    {
        IEEE754::Binary32 fp1(std::numeric_limits<float>::infinity());
        IEEE754::Binary32 fp2(-std::numeric_limits<float>::infinity());
        IEEE754::Binary32 fp3(IEEE754::Binary32::GetInfinte());
        IEEE754::Binary32 fp4(IEEE754::Binary32::GetNegativeInfinite());

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
