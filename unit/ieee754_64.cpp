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

TEST_CASE("ieee754_64")
{
    SUBCASE("Get Double")
    {
        IEEE754::Binary64 fp1(12883.1882);
        IEEE754::Binary64 fp2(-12883.1882);

        REQUIRE(fp1.GetSign() == 0u);
        REQUIRE(fp1.GetExponent() == 1036u);
        REQUIRE(fp1.GetSignificand() == 0x9299816f0068e);

        REQUIRE(fp2.GetSign() == 1u);
        REQUIRE(fp2.GetExponent() == 1036u);
        REQUIRE(fp2.GetSignificand() == 0x9299816f0068e);
    }

    SUBCASE("Set Double")
    {
        IEEE754::Binary64 fp;
        fp.SetSign(0u);
        fp.SetExponent(1039u);
        fp.SetSignificand(0x83321f8b91f8e);

        REQUIRE(fp.integer == 0x40f83321f8b91f8e);
    }

    SUBCASE("Test ClassificationDP")
    {
        IEEE754::Binary64 zerofp = IEEE754::Binary64::GetZero();
        IEEE754::Binary64 negzerofp = IEEE754::Binary64::GetNegativeZero();
        IEEE754::Binary64 nanfp = IEEE754::Binary64::GetNaN();
        IEEE754::Binary64 negnanfp = IEEE754::Binary64::GetNegativeNaN();
        IEEE754::Binary64 inffp = IEEE754::Binary64::GetInfinte();
        IEEE754::Binary64 neginffp = IEEE754::Binary64::GetNegativeInfinite();
        IEEE754::Binary64 rn(2.0);

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

    SUBCASE("Test NaN")
    {
        IEEE754::Binary64 fp1(std::numeric_limits<double>::quiet_NaN());
        IEEE754::Binary64 fp2(-std::numeric_limits<double>::quiet_NaN());
        IEEE754::Binary64 fp3(IEEE754::Binary64::GetNaN());
        IEEE754::Binary64 fp4(IEEE754::Binary64::GetNegativeNaN());

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
        IEEE754::Binary64 fp1(std::numeric_limits<double>::infinity());
        IEEE754::Binary64 fp2(-std::numeric_limits<double>::infinity());
        IEEE754::Binary64 fp3(IEEE754::Binary64::GetInfinte());
        IEEE754::Binary64 fp4(IEEE754::Binary64::GetNegativeInfinite());

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
