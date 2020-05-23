#include "doctest/doctest.h"
#include "platform.h"
#include "Types/Real.h"
#include <limits>

/*
// Match our native ordering
static int NativeClasses[] =
{
    FP_ZERO,
    FP_SUBNORMAL,
    FP_INFINITE,
    FP_NAN,
    FP_NORMAL
};

TEST_CASE("ieee754_16")
{
    SUBCASE("Get Float")
    {
        IEEE754::Binary16 fp1(12883.1882f);
        IEEE754::Binary16 fp2(-12883.1882f);

        printf("fp1 [%d, %d, %d]\n", fp1.GetSignificand(), fp1.GetExponent(), fp1.GetSign());
        printf("fp1 [%f], fp2 [%f]\n", fp1.GetFP(), fp2.GetFP());

        REQUIRE(static_cast<uint32>(fp1.GetSign()) == 0u);
        REQUIRE(static_cast<uint32>(fp1.GetExponent()) == 140u);
        REQUIRE(static_cast<uint32>(fp1.GetSignificand()) == 4803777u);

        REQUIRE(fp2.GetSign() == 1u);
        REQUIRE(fp2.GetExponent() == 140u);
        REQUIRE(fp2.GetSignificand() == 4803777u);
    }

    SUBCASE("Set Float")
    {
        IEEE754::Binary16 fp;
        fp.SetSign(1u);
        fp.SetExponent(0x1f);
        fp.SetSignificand(0x3ff);

        REQUIRE(fp.integer == 0xffff);
    }

    SUBCASE("Test ClassificationFP")
    {
        IEEE754::Binary16 zerofp = IEEE754::Binary16::GetZero();
        IEEE754::Binary16 negzerofp = IEEE754::Binary16::GetNegativeZero();
        IEEE754::Binary16 nanfp = IEEE754::Binary16::GetNaN();
        IEEE754::Binary16 negnanfp = IEEE754::Binary16::GetNegativeNaN();
        IEEE754::Binary16 inffp = IEEE754::Binary16::GetInfinte();
        IEEE754::Binary16 neginffp = IEEE754::Binary16::GetNegativeInfinite();
        IEEE754::Binary16 rn(2.0f);

        REQUIRE(NativeClasses[static_cast<uint32>(zerofp.GetClassification())] == fpclassify(zerofp.GetFP()));
        REQUIRE(zerofp.IsZero());
        REQUIRE(zerofp.GetFP() == 0.0f);

        REQUIRE(NativeClasses[static_cast<uint32>(negzerofp.GetClassification())] == fpclassify(negzerofp.GetFP()));
        REQUIRE(negzerofp.IsZero());
        REQUIRE(negzerofp.GetFP() == -0.0f);

        REQUIRE(NativeClasses[static_cast<uint32>(nanfp.GetClassification())] == fpclassify(nanfp.GetFP()));
        REQUIRE(nanfp.IsNaN());
        REQUIRE(isnan<float>(nanfp.GetFP()));

        REQUIRE(NativeClasses[static_cast<uint32>(negnanfp.GetClassification())] == fpclassify(negnanfp.GetFP()));
        REQUIRE(negnanfp.IsNaN());
        REQUIRE(isnan<float>(negnanfp.GetFP()));

        REQUIRE(NativeClasses[static_cast<uint32>(inffp.GetClassification())] == fpclassify(inffp.GetFP()));
        REQUIRE(inffp.IsInf());
        REQUIRE(isinf<float>(inffp.GetFP()));

        REQUIRE(NativeClasses[static_cast<uint32>(neginffp.GetClassification())] == fpclassify(neginffp.GetFP()));
        REQUIRE(neginffp.IsInf());
        REQUIRE(isinf<float>(neginffp.GetFP()));

        REQUIRE(NativeClasses[static_cast<uint32>(rn.GetClassification())] == fpclassify(rn.GetFP()));
        REQUIRE(rn.IsNormal());
        REQUIRE(!rn.IsSubnormal());
        REQUIRE(isnormal<float>(rn.GetFP()));
    }

    SUBCASE("Test NaN")
    {
        IEEE754::Binary16 fp1(std::numeric_limits<float>::quiet_NaN());
        IEEE754::Binary16 fp2(-std::numeric_limits<float>::quiet_NaN());
        IEEE754::Binary16 fp3(IEEE754::Binary16::GetNaN());
        IEEE754::Binary16 fp4(IEEE754::Binary16::GetNegativeNaN());

        REQUIRE(fp1.integer == fp3.integer);
        REQUIRE(fp2.integer == fp4.integer);

        REQUIRE(NativeClasses[static_cast<uint32>(fp1.GetClassification())] == fpclassify(fp1.GetFP()));
        REQUIRE(NativeClasses[static_cast<uint32>(fp2.GetClassification())] == fpclassify(fp2.GetFP()));
        REQUIRE(NativeClasses[static_cast<uint32>(fp3.GetClassification())] == fpclassify(fp3.GetFP()));
        REQUIRE(NativeClasses[static_cast<uint32>(fp4.GetClassification())] == fpclassify(fp4.GetFP()));

        bool NaNTest = (fp1.IsNaN() && fp2.IsNaN() && fp3.IsNaN() && fp4.IsNaN());

        REQUIRE(NaNTest);
    }

    SUBCASE("Test Finite")
    {
        IEEE754::Binary16 fp1(std::numeric_limits<float>::infinity());
        IEEE754::Binary16 fp2(-std::numeric_limits<float>::infinity());
        IEEE754::Binary16 fp3(IEEE754::Binary16::GetInfinte());
        IEEE754::Binary16 fp4(IEEE754::Binary16::GetNegativeInfinite());

        REQUIRE(fp1.integer == fp3.integer);
        REQUIRE(fp2.integer == fp4.integer);

        REQUIRE(NativeClasses[static_cast<uint32>(fp1.GetClassification())] == fpclassify(fp1.GetFP()));
        REQUIRE(NativeClasses[static_cast<uint32>(fp2.GetClassification())] == fpclassify(fp2.GetFP()));
        REQUIRE(NativeClasses[static_cast<uint32>(fp3.GetClassification())] == fpclassify(fp3.GetFP()));
        REQUIRE(NativeClasses[static_cast<uint32>(fp4.GetClassification())] == fpclassify(fp4.GetFP()));

        bool InfTest = (fp1.IsInf() && fp2.IsInf() && fp3.IsInf() && fp4.IsInf());

        REQUIRE(InfTest);
    }
}
*/
