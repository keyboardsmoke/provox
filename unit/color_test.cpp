#include "catch.hpp"
#include "types.h"

static double nearestFP(const double& v)
{
    // Was * 100.0 / 100.0, but we want _less_ precision thanks to the weird
    // online converter we are using
    return round(v * 10.0) / 10.0;
}

static double roundDegree(const double& v)
{
    // Degrees won't usually be partial...
    return round(v);
}

static double HueToDegree(const double& hue)
{
    return roundDegree(hue * 360.0);
}

static double ValueToPercent(const double& v)
{
    return nearestFP(v * 100.0);
}

static bool ConversionTestHSL(const Color& col)
{
    Double h, s, l;
    col.ToHSL(&h, &s, &l);
    Color cb = Color::ColorFromHSL(h, s, l);
    return (col == cb);
}

static bool ConversionTestHSV(const Color& col)
{
    Double h, s, v;
    col.ToHSL(&h, &s, &v);
    Color cb = Color::ColorFromHSV(h, s, v);
    return (col == cb);
}

static void PrintValues(const Color& col)
{
    Double h, s, l, v;
    col.ToHSL(&h, &s, &l);
    printf("HSL [%f (%f), %f (%f), %f (%f)]\n", HueToDegree(h.GetFP()), h.GetFP(), ValueToPercent(s.GetFP()), s.GetFP(), ValueToPercent(l.GetFP()), l.GetFP());

    col.ToHSV(&h, &s, &v);
    printf("HSV [%f (%f), %f (%f), %f (%f)]\n", HueToDegree(h.GetFP()), h.GetFP(), ValueToPercent(s.GetFP()), s.GetFP(), ValueToPercent(v.GetFP()), v.GetFP());
}

static bool TestHSV(const Color& col, double eh, double es, double ev)
{
    Double h, s, v;
    col.ToHSV(&h, &s, &v);
    // PrintValues(col);
    return (HueToDegree(h) == eh) && (ValueToPercent(s) == es) && (ValueToPercent(v) == ev);
}

static bool TestHSL(const Color& col, double eh, double es, double el)
{
    Double h, s, l;
    col.ToHSL(&h, &s, &l);
    // PrintValues(col);
    return (HueToDegree(h) == eh) && (ValueToPercent(s) == es) && (ValueToPercent(l) == el);
}

TEST_CASE("Color tests")
{
    SECTION("Endianness sanity check")
    {
        REQUIRE((uint32)Color::Colors::Black.GetRed() == 0);
        REQUIRE((uint32)Color::Colors::Black.GetGreen() == 0);
        REQUIRE((uint32)Color::Colors::Black.GetBlue() == 0);
        REQUIRE((uint32)Color::Colors::Black.GetAlpha() == 0xff);
        REQUIRE(Color().GetValue() == Color::Colors::Black.GetValue());
        REQUIRE(Color::Colors::Black.GetValue() == 0x000000FFu);
    }

    SECTION("Conversion EQ")
    {
        // HSL
        ConversionTestHSL(Color::Colors::MediumPurple);
        ConversionTestHSL(Color::Colors::MediumSeaGreen);
        ConversionTestHSL(Color::Colors::MediumSlateBlue);
        ConversionTestHSL(Color::Colors::MediumSpringGreen);
        ConversionTestHSL(Color::Colors::MediumTurquoise);
        ConversionTestHSL(Color::Colors::MediumVioletRed);
        ConversionTestHSL(Color::Colors::MidnightBlue);
        ConversionTestHSL(Color::Colors::MediumOrchid);
        ConversionTestHSL(Color::Colors::MintCream);
        ConversionTestHSL(Color::Colors::Moccasin);
        ConversionTestHSL(Color::Colors::NavajoWhite);
        ConversionTestHSL(Color::Colors::Navy);
        ConversionTestHSL(Color::Colors::OldLace);
        ConversionTestHSL(Color::Colors::Olive);
        ConversionTestHSL(Color::Colors::OliveDrab);
        ConversionTestHSL(Color::Colors::Orange);
        ConversionTestHSL(Color::Colors::MistyRose);
        ConversionTestHSL(Color::Colors::OrangeRed);
        ConversionTestHSL(Color::Colors::MediumBlue);
        ConversionTestHSL(Color::Colors::Maroon);
        ConversionTestHSL(Color::Colors::LightBlue);
        ConversionTestHSL(Color::Colors::LightCoral);
        ConversionTestHSL(Color::Colors::LightGoldenrodYellow);
        ConversionTestHSL(Color::Colors::LightGreen);
        ConversionTestHSL(Color::Colors::LightGray);
        ConversionTestHSL(Color::Colors::LightPink);
        ConversionTestHSL(Color::Colors::LightSalmon);
        ConversionTestHSL(Color::Colors::MediumAquamarine);
        ConversionTestHSL(Color::Colors::LightSeaGreen);
        ConversionTestHSL(Color::Colors::LightSlateGray);
        ConversionTestHSL(Color::Colors::LightSteelBlue);
        ConversionTestHSL(Color::Colors::LightYellow);
        ConversionTestHSL(Color::Colors::Lime);
        ConversionTestHSL(Color::Colors::LimeGreen);
        ConversionTestHSL(Color::Colors::Linen);
        ConversionTestHSL(Color::Colors::Magenta);
        ConversionTestHSL(Color::Colors::LightSkyBlue);
        ConversionTestHSL(Color::Colors::LemonChiffon);
        ConversionTestHSL(Color::Colors::Orchid);
        ConversionTestHSL(Color::Colors::PaleGreen);
        ConversionTestHSL(Color::Colors::SlateBlue);
        ConversionTestHSL(Color::Colors::SlateGray);
        ConversionTestHSL(Color::Colors::Snow);
        ConversionTestHSL(Color::Colors::SpringGreen);
        ConversionTestHSL(Color::Colors::SteelBlue);
        ConversionTestHSL(Color::Colors::Tan);
        ConversionTestHSL(Color::Colors::Teal);
        ConversionTestHSL(Color::Colors::SkyBlue);
        ConversionTestHSL(Color::Colors::Thistle);
        ConversionTestHSL(Color::Colors::Turquoise);
        ConversionTestHSL(Color::Colors::Violet);
        ConversionTestHSL(Color::Colors::Wheat);
        ConversionTestHSL(Color::Colors::White);
        ConversionTestHSL(Color::Colors::WhiteSmoke);
        ConversionTestHSL(Color::Colors::Yellow);
        ConversionTestHSL(Color::Colors::YellowGreen);
        ConversionTestHSL(Color::Colors::Tomato);
        ConversionTestHSL(Color::Colors::PaleGoldenrod);
        ConversionTestHSL(Color::Colors::Silver);
        ConversionTestHSL(Color::Colors::SeaShell);
        ConversionTestHSL(Color::Colors::PaleTurquoise);
        ConversionTestHSL(Color::Colors::PaleVioletRed);
        ConversionTestHSL(Color::Colors::PapayaWhip);
        ConversionTestHSL(Color::Colors::PeachPuff);
        ConversionTestHSL(Color::Colors::Peru);
        ConversionTestHSL(Color::Colors::Pink);
        ConversionTestHSL(Color::Colors::Plum);
        ConversionTestHSL(Color::Colors::Sienna);
        ConversionTestHSL(Color::Colors::PowderBlue);
        ConversionTestHSL(Color::Colors::Red);
        ConversionTestHSL(Color::Colors::RosyBrown);
        ConversionTestHSL(Color::Colors::RoyalBlue);
        ConversionTestHSL(Color::Colors::SaddleBrown);
        ConversionTestHSL(Color::Colors::Salmon);
        ConversionTestHSL(Color::Colors::SandyBrown);
        ConversionTestHSL(Color::Colors::SeaGreen);
        ConversionTestHSL(Color::Colors::Purple);
        ConversionTestHSL(Color::Colors::LawnGreen);
        ConversionTestHSL(Color::Colors::LightCyan);
        ConversionTestHSL(Color::Colors::Lavender);
        ConversionTestHSL(Color::Colors::DarkKhaki);
        ConversionTestHSL(Color::Colors::DarkGreen);
        ConversionTestHSL(Color::Colors::DarkGray);
        ConversionTestHSL(Color::Colors::DarkGoldenrod);
        ConversionTestHSL(Color::Colors::DarkCyan);
        ConversionTestHSL(Color::Colors::DarkBlue);
        ConversionTestHSL(Color::Colors::Cyan);
        ConversionTestHSL(Color::Colors::Crimson);
        ConversionTestHSL(Color::Colors::Cornsilk);
        ConversionTestHSL(Color::Colors::LavenderBlush);
        ConversionTestHSL(Color::Colors::Coral);
        ConversionTestHSL(Color::Colors::Chocolate);
        ConversionTestHSL(Color::Colors::Chartreuse);
        ConversionTestHSL(Color::Colors::DarkMagenta);
        ConversionTestHSL(Color::Colors::CadetBlue);
        ConversionTestHSL(Color::Colors::Brown);
        ConversionTestHSL(Color::Colors::BlueViolet);
        ConversionTestHSL(Color::Colors::Blue);
        ConversionTestHSL(Color::Colors::BlanchedAlmond);
        ConversionTestHSL(Color::Colors::Black);
        ConversionTestHSL(Color::Colors::Bisque);
        ConversionTestHSL(Color::Colors::Beige);
        ConversionTestHSL(Color::Colors::Azure);
        ConversionTestHSL(Color::Colors::Aquamarine);
        ConversionTestHSL(Color::Colors::Aqua);
        ConversionTestHSL(Color::Colors::AntiqueWhite);
        ConversionTestHSL(Color::Colors::AliceBlue);
        ConversionTestHSL(Color::Colors::Transparent);
        ConversionTestHSL(Color::Colors::BurlyWood);
        ConversionTestHSL(Color::Colors::DarkOliveGreen);
        ConversionTestHSL(Color::Colors::CornflowerBlue);
        ConversionTestHSL(Color::Colors::DarkOrchid);
        ConversionTestHSL(Color::Colors::Khaki);
        ConversionTestHSL(Color::Colors::Ivory);
        ConversionTestHSL(Color::Colors::DarkOrange);
        ConversionTestHSL(Color::Colors::Indigo);
        ConversionTestHSL(Color::Colors::IndianRed);
        ConversionTestHSL(Color::Colors::HotPink);
        ConversionTestHSL(Color::Colors::Honeydew);
        ConversionTestHSL(Color::Colors::GreenYellow);
        ConversionTestHSL(Color::Colors::Green);
        ConversionTestHSL(Color::Colors::Gray);
        ConversionTestHSL(Color::Colors::Goldenrod);
        ConversionTestHSL(Color::Colors::GhostWhite);
        ConversionTestHSL(Color::Colors::Gainsboro);
        ConversionTestHSL(Color::Colors::Fuchsia);
        ConversionTestHSL(Color::Colors::Gold);
        ConversionTestHSL(Color::Colors::FloralWhite);
        ConversionTestHSL(Color::Colors::DarkRed);
        ConversionTestHSL(Color::Colors::DarkSalmon);
        ConversionTestHSL(Color::Colors::DarkSeaGreen);
        ConversionTestHSL(Color::Colors::ForestGreen);
        ConversionTestHSL(Color::Colors::DarkSlateGray);
        ConversionTestHSL(Color::Colors::DarkTurquoise);
        ConversionTestHSL(Color::Colors::DarkSlateBlue);
        ConversionTestHSL(Color::Colors::DeepPink);
        ConversionTestHSL(Color::Colors::DeepSkyBlue);
        ConversionTestHSL(Color::Colors::DimGray);
        ConversionTestHSL(Color::Colors::DodgerBlue);
        ConversionTestHSL(Color::Colors::Firebrick);
        ConversionTestHSL(Color::Colors::DarkViolet);

        // HSV
        ConversionTestHSV(Color::Colors::MediumPurple);
        ConversionTestHSV(Color::Colors::MediumSeaGreen);
        ConversionTestHSV(Color::Colors::MediumSlateBlue);
        ConversionTestHSV(Color::Colors::MediumSpringGreen);
        ConversionTestHSV(Color::Colors::MediumTurquoise);
        ConversionTestHSV(Color::Colors::MediumVioletRed);
        ConversionTestHSV(Color::Colors::MidnightBlue);
        ConversionTestHSV(Color::Colors::MediumOrchid);
        ConversionTestHSV(Color::Colors::MintCream);
        ConversionTestHSV(Color::Colors::Moccasin);
        ConversionTestHSV(Color::Colors::NavajoWhite);
        ConversionTestHSV(Color::Colors::Navy);
        ConversionTestHSV(Color::Colors::OldLace);
        ConversionTestHSV(Color::Colors::Olive);
        ConversionTestHSV(Color::Colors::OliveDrab);
        ConversionTestHSV(Color::Colors::Orange);
        ConversionTestHSV(Color::Colors::MistyRose);
        ConversionTestHSV(Color::Colors::OrangeRed);
        ConversionTestHSV(Color::Colors::MediumBlue);
        ConversionTestHSV(Color::Colors::Maroon);
        ConversionTestHSV(Color::Colors::LightBlue);
        ConversionTestHSV(Color::Colors::LightCoral);
        ConversionTestHSV(Color::Colors::LightGoldenrodYellow);
        ConversionTestHSV(Color::Colors::LightGreen);
        ConversionTestHSV(Color::Colors::LightGray);
        ConversionTestHSV(Color::Colors::LightPink);
        ConversionTestHSV(Color::Colors::LightSalmon);
        ConversionTestHSV(Color::Colors::MediumAquamarine);
        ConversionTestHSV(Color::Colors::LightSeaGreen);
        ConversionTestHSV(Color::Colors::LightSlateGray);
        ConversionTestHSV(Color::Colors::LightSteelBlue);
        ConversionTestHSV(Color::Colors::LightYellow);
        ConversionTestHSV(Color::Colors::Lime);
        ConversionTestHSV(Color::Colors::LimeGreen);
        ConversionTestHSV(Color::Colors::Linen);
        ConversionTestHSV(Color::Colors::Magenta);
        ConversionTestHSV(Color::Colors::LightSkyBlue);
        ConversionTestHSV(Color::Colors::LemonChiffon);
        ConversionTestHSV(Color::Colors::Orchid);
        ConversionTestHSV(Color::Colors::PaleGreen);
        ConversionTestHSV(Color::Colors::SlateBlue);
        ConversionTestHSV(Color::Colors::SlateGray);
        ConversionTestHSV(Color::Colors::Snow);
        ConversionTestHSV(Color::Colors::SpringGreen);
        ConversionTestHSV(Color::Colors::SteelBlue);
        ConversionTestHSV(Color::Colors::Tan);
        ConversionTestHSV(Color::Colors::Teal);
        ConversionTestHSV(Color::Colors::SkyBlue);
        ConversionTestHSV(Color::Colors::Thistle);
        ConversionTestHSV(Color::Colors::Turquoise);
        ConversionTestHSV(Color::Colors::Violet);
        ConversionTestHSV(Color::Colors::Wheat);
        ConversionTestHSV(Color::Colors::White);
        ConversionTestHSV(Color::Colors::WhiteSmoke);
        ConversionTestHSV(Color::Colors::Yellow);
        ConversionTestHSV(Color::Colors::YellowGreen);
        ConversionTestHSV(Color::Colors::Tomato);
        ConversionTestHSV(Color::Colors::PaleGoldenrod);
        ConversionTestHSV(Color::Colors::Silver);
        ConversionTestHSV(Color::Colors::SeaShell);
        ConversionTestHSV(Color::Colors::PaleTurquoise);
        ConversionTestHSV(Color::Colors::PaleVioletRed);
        ConversionTestHSV(Color::Colors::PapayaWhip);
        ConversionTestHSV(Color::Colors::PeachPuff);
        ConversionTestHSV(Color::Colors::Peru);
        ConversionTestHSV(Color::Colors::Pink);
        ConversionTestHSV(Color::Colors::Plum);
        ConversionTestHSV(Color::Colors::Sienna);
        ConversionTestHSV(Color::Colors::PowderBlue);
        ConversionTestHSV(Color::Colors::Red);
        ConversionTestHSV(Color::Colors::RosyBrown);
        ConversionTestHSV(Color::Colors::RoyalBlue);
        ConversionTestHSV(Color::Colors::SaddleBrown);
        ConversionTestHSV(Color::Colors::Salmon);
        ConversionTestHSV(Color::Colors::SandyBrown);
        ConversionTestHSV(Color::Colors::SeaGreen);
        ConversionTestHSV(Color::Colors::Purple);
        ConversionTestHSV(Color::Colors::LawnGreen);
        ConversionTestHSV(Color::Colors::LightCyan);
        ConversionTestHSV(Color::Colors::Lavender);
        ConversionTestHSV(Color::Colors::DarkKhaki);
        ConversionTestHSV(Color::Colors::DarkGreen);
        ConversionTestHSV(Color::Colors::DarkGray);
        ConversionTestHSV(Color::Colors::DarkGoldenrod);
        ConversionTestHSV(Color::Colors::DarkCyan);
        ConversionTestHSV(Color::Colors::DarkBlue);
        ConversionTestHSV(Color::Colors::Cyan);
        ConversionTestHSV(Color::Colors::Crimson);
        ConversionTestHSV(Color::Colors::Cornsilk);
        ConversionTestHSV(Color::Colors::LavenderBlush);
        ConversionTestHSV(Color::Colors::Coral);
        ConversionTestHSV(Color::Colors::Chocolate);
        ConversionTestHSV(Color::Colors::Chartreuse);
        ConversionTestHSV(Color::Colors::DarkMagenta);
        ConversionTestHSV(Color::Colors::CadetBlue);
        ConversionTestHSV(Color::Colors::Brown);
        ConversionTestHSV(Color::Colors::BlueViolet);
        ConversionTestHSV(Color::Colors::Blue);
        ConversionTestHSV(Color::Colors::BlanchedAlmond);
        ConversionTestHSV(Color::Colors::Black);
        ConversionTestHSV(Color::Colors::Bisque);
        ConversionTestHSV(Color::Colors::Beige);
        ConversionTestHSV(Color::Colors::Azure);
        ConversionTestHSV(Color::Colors::Aquamarine);
        ConversionTestHSV(Color::Colors::Aqua);
        ConversionTestHSV(Color::Colors::AntiqueWhite);
        ConversionTestHSV(Color::Colors::AliceBlue);
        ConversionTestHSV(Color::Colors::Transparent);
        ConversionTestHSV(Color::Colors::BurlyWood);
        ConversionTestHSV(Color::Colors::DarkOliveGreen);
        ConversionTestHSV(Color::Colors::CornflowerBlue);
        ConversionTestHSV(Color::Colors::DarkOrchid);
        ConversionTestHSV(Color::Colors::Khaki);
        ConversionTestHSV(Color::Colors::Ivory);
        ConversionTestHSV(Color::Colors::DarkOrange);
        ConversionTestHSV(Color::Colors::Indigo);
        ConversionTestHSV(Color::Colors::IndianRed);
        ConversionTestHSV(Color::Colors::HotPink);
        ConversionTestHSV(Color::Colors::Honeydew);
        ConversionTestHSV(Color::Colors::GreenYellow);
        ConversionTestHSV(Color::Colors::Green);
        ConversionTestHSV(Color::Colors::Gray);
        ConversionTestHSV(Color::Colors::Goldenrod);
        ConversionTestHSV(Color::Colors::GhostWhite);
        ConversionTestHSV(Color::Colors::Gainsboro);
        ConversionTestHSV(Color::Colors::Fuchsia);
        ConversionTestHSV(Color::Colors::Gold);
        ConversionTestHSV(Color::Colors::FloralWhite);
        ConversionTestHSV(Color::Colors::DarkRed);
        ConversionTestHSV(Color::Colors::DarkSalmon);
        ConversionTestHSV(Color::Colors::DarkSeaGreen);
        ConversionTestHSV(Color::Colors::ForestGreen);
        ConversionTestHSV(Color::Colors::DarkSlateGray);
        ConversionTestHSV(Color::Colors::DarkTurquoise);
        ConversionTestHSV(Color::Colors::DarkSlateBlue);
        ConversionTestHSV(Color::Colors::DeepPink);
        ConversionTestHSV(Color::Colors::DeepSkyBlue);
        ConversionTestHSV(Color::Colors::DimGray);
        ConversionTestHSV(Color::Colors::DodgerBlue);
        ConversionTestHSV(Color::Colors::Firebrick);
        ConversionTestHSV(Color::Colors::DarkViolet);
    }

    // Been using this to get the numbers
    // https://www.ginifab.com/feeds/pms/rgb_to_hsv_hsl.html
    // Just want to sanity check against other common things easily
    // hence the rounding, multiplication, etc.
    SECTION("RGB to HSL")
    {
        REQUIRE(TestHSL(Color::Colors::Black, 0.0, 0.0, 0.0) == true);
        REQUIRE(TestHSL(Color::Colors::White, 0.0, 0.0, 100.0) == true);
        REQUIRE(TestHSL(Color::Colors::Red, 0.0, 100.0, 50.0) == true);
        REQUIRE(TestHSL(Color::Colors::Magenta, 300.0, 100.0, 50.0) == true);
        REQUIRE(TestHSL(Color::Colors::Blue, 240.0, 100.0, 50.0) == true);
        REQUIRE(TestHSL(Color::Colors::Green, 120.0, 100.0, 25.1) == true);
        REQUIRE(TestHSL(Color::Colors::Indigo, 275.0, 100.0, 25.5) == true);
        REQUIRE(TestHSL(Color::Colors::SlateBlue, 248.0, 53.5, 57.8) == true);
    }

    SECTION("RGB to HSV")
    {
        REQUIRE(TestHSV(Color::Colors::Black, 0.0, 0.0, 0.0) == true);
        REQUIRE(TestHSV(Color::Colors::White, 0.0, 0.0, 100.0) == true);
        REQUIRE(TestHSV(Color::Colors::Red, 0.0, 100.0, 100.0) == true);
        REQUIRE(TestHSV(Color::Colors::Magenta, 300.0, 100.0, 100.0) == true);
        REQUIRE(TestHSV(Color::Colors::Green, 120.0, 100.0, 50.2) == true);
        REQUIRE(TestHSV(Color::Colors::Blue, 240.0, 100.0, 100.0) == true);
        REQUIRE(TestHSV(Color::Colors::Indigo, 275.0, 100.0, 51.0) == true);
        REQUIRE(TestHSV(Color::Colors::SlateBlue, 248.0, 56.1, 80.4) == true);
    }
}
