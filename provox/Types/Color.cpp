#include "pch.h"
#include "types.h"
#include <algorithm>

const Double Color::MaxHue = 6.0;
const Double Color::MaxSaturation = 1.0;
const Double Color::MaxLuminance = 1.0;
const Double Color::MaxValue = 1.0;

const Double Color::MinHue = 0.0;
const Double Color::MinSaturation = 0.0;
const Double Color::MinLuminance = 0.0;
const Double Color::MinValue = 0.0;

// Color definitions, distastefully stolen from the .NET library
Color Color::Colors::MediumPurple(0xFF9370DBu);
Color Color::Colors::MediumSeaGreen(0x3CB371FFu);
Color Color::Colors::MediumSlateBlue(0x7B68EEFFu);
Color Color::Colors::MediumSpringGreen(0x00FA9AFFu);
Color Color::Colors::MediumTurquoise(0x48D1CCFFu);
Color Color::Colors::MediumVioletRed(0xC71585FFu);
Color Color::Colors::MidnightBlue(0x191970FFu);
Color Color::Colors::MediumOrchid(0xBA55D3FFu);
Color Color::Colors::MintCream(0xF5FFFAFFu);
Color Color::Colors::Moccasin(0xFFE4B5FFu);
Color Color::Colors::NavajoWhite(0xFFDEADFFu);
Color Color::Colors::Navy(0x000080FFu);
Color Color::Colors::OldLace(0xFDF5E6FFu);
Color Color::Colors::Olive(0x808000FFu);
Color Color::Colors::OliveDrab(0x6B8E23FFu);
Color Color::Colors::Orange(0xFFA500FFu);
Color Color::Colors::MistyRose(0xFFE4E1FFu);
Color Color::Colors::OrangeRed(0xFF4500FFu);
Color Color::Colors::MediumBlue(0x0000CDFFu);
Color Color::Colors::Maroon(0x800000FFu);
Color Color::Colors::LightBlue(0xADD8E6FFu);
Color Color::Colors::LightCoral(0xF08080FFu);
Color Color::Colors::LightGoldenrodYellow(0xFAFAD2FFu);
Color Color::Colors::LightGreen(0x90EE90FFu);
Color Color::Colors::LightGray(0xD3D3D3FFu);
Color Color::Colors::LightPink(0xFFB6C1FFu);
Color Color::Colors::LightSalmon(0xFFA07AFFu);
Color Color::Colors::MediumAquamarine(0x66CDAAFFu);
Color Color::Colors::LightSeaGreen(0x20B2AAFFu);
Color Color::Colors::LightSlateGray(0x778899FFu);
Color Color::Colors::LightSteelBlue(0xB0C4DEFFu);
Color Color::Colors::LightYellow(0xFFFFE0FFu);
Color Color::Colors::Lime(0x00FF00FFu);
Color Color::Colors::LimeGreen(0x32CD32FFu);
Color Color::Colors::Linen(0xFAF0E6FFu);
Color Color::Colors::Magenta(0xFF00FFFFu);
Color Color::Colors::LightSkyBlue(0x87CEFAFFu);
Color Color::Colors::LemonChiffon(0xFFFACDFFu);
Color Color::Colors::Orchid(0xDA70D6FFu);
Color Color::Colors::PaleGreen(0x98FB98FFu);
Color Color::Colors::SlateBlue(0x6A5ACDFFu);
Color Color::Colors::SlateGray(0x708090FFu);
Color Color::Colors::Snow(0xFFFAFAFFu);
Color Color::Colors::SpringGreen(0x00FF7FFFu);
Color Color::Colors::SteelBlue(0x4682B4FFu);
Color Color::Colors::Tan(0xD2B48CFFu);
Color Color::Colors::Teal(0x008080FFu);
Color Color::Colors::SkyBlue(0x87CEEBFFu);
Color Color::Colors::Thistle(0xD8BFD8FFu);
Color Color::Colors::Turquoise(0x40E0D0FFu);
Color Color::Colors::Violet(0xEE82EEFFu);
Color Color::Colors::Wheat(0xF5DEB3FFu);
Color Color::Colors::White(0xFFFFFFFFu);
Color Color::Colors::WhiteSmoke(0xF5F5F5FFu);
Color Color::Colors::Yellow(0xFFFF00FFu);
Color Color::Colors::YellowGreen(0x9ACD32FFu);
Color Color::Colors::Tomato(0xFF6347FFu);
Color Color::Colors::PaleGoldenrod(0xEEE8AAFFu);
Color Color::Colors::Silver(0xC0C0C0FFu);
Color Color::Colors::SeaShell(0xFFF5EEFFu);
Color Color::Colors::PaleTurquoise(0xAFEEEEFFu);
Color Color::Colors::PaleVioletRed(0xDB7093FFu);
Color Color::Colors::PapayaWhip(0xFFEFD5FFu);
Color Color::Colors::PeachPuff(0xFFDAB9FFu);
Color Color::Colors::Peru(0xCD853FFFu);
Color Color::Colors::Pink(0xFFC0CBFFu);
Color Color::Colors::Plum(0xDDA0DDFFu);
Color Color::Colors::Sienna(0xA0522DFFu);
Color Color::Colors::PowderBlue(0xB0E0E6FFu);
Color Color::Colors::Red(0xFF0000FFu);
Color Color::Colors::RosyBrown(0xBC8F8FFFu);
Color Color::Colors::RoyalBlue(0x4169E1FFu);
Color Color::Colors::SaddleBrown(0x8B4513FFu);
Color Color::Colors::Salmon(0xFA8072FFu);
Color Color::Colors::SandyBrown(0xF4A460FFu);
Color Color::Colors::SeaGreen(0x2E8B57FFu);
Color Color::Colors::Purple(0x800080FFu);
Color Color::Colors::LawnGreen(0x7CFC00FFu);
Color Color::Colors::LightCyan(0xE0FFFFFFu);
Color Color::Colors::Lavender(0xE6E6FAFFu);
Color Color::Colors::DarkKhaki(0xBDB76BFFu);
Color Color::Colors::DarkGreen(0x006400FFu);
Color Color::Colors::DarkGray(0xA9A9A9FFu);
Color Color::Colors::DarkGoldenrod(0xB8860BFFu);
Color Color::Colors::DarkCyan(0x008B8BFFu);
Color Color::Colors::DarkBlue(0x00008BFFu);
Color Color::Colors::Cyan(0x00FFFFFFu);
Color Color::Colors::Crimson(0xDC143CFFu);
Color Color::Colors::Cornsilk(0xFFF8DCFFu);
Color Color::Colors::LavenderBlush(0xFFF0F5FFu);
Color Color::Colors::Coral(0xFF7F50FFu);
Color Color::Colors::Chocolate(0xD2691EFFu);
Color Color::Colors::Chartreuse(0x7FFF00FFu);
Color Color::Colors::DarkMagenta(0x8B008BFFu);
Color Color::Colors::CadetBlue(0x5F9EA0FFu);
Color Color::Colors::Brown(0xA52A2AFFu);
Color Color::Colors::BlueViolet(0x8A2BE2FFu);
Color Color::Colors::Blue(0x0000FFFFu);
Color Color::Colors::BlanchedAlmond(0xFFEBCDFFu);
Color Color::Colors::Black(0x000000FFu);
Color Color::Colors::Bisque(0xFFE4C4FFu);
Color Color::Colors::Beige(0xF5F5DCFFu);
Color Color::Colors::Azure(0xF0FFFFFFu);
Color Color::Colors::Aquamarine(0x7FFFD4FFu);
Color Color::Colors::Aqua(0x00FFFFFFu);
Color Color::Colors::AntiqueWhite(0xFAEBD7FFu);
Color Color::Colors::AliceBlue(0xF0F8FFFFu);
Color Color::Colors::Transparent(0xFFFFFF00u);
Color Color::Colors::BurlyWood(0xDEB887FFu);
Color Color::Colors::DarkOliveGreen(0x556B2FFFu);
Color Color::Colors::CornflowerBlue(0x6495EDFFu);
Color Color::Colors::DarkOrchid(0x9932CCFFu);
Color Color::Colors::Khaki(0xF0E68CFFu);
Color Color::Colors::Ivory(0xFFFFF0FFu);
Color Color::Colors::DarkOrange(0xFF8C00FFu);
Color Color::Colors::Indigo(0x4B0082FFu);
Color Color::Colors::IndianRed(0xCD5C5CFFu);
Color Color::Colors::HotPink(0xFF69B4FFu);
Color Color::Colors::Honeydew(0xF0FFF0FFu);
Color Color::Colors::GreenYellow(0xADFF2FFFu);
Color Color::Colors::Green(0x008000FFu);
Color Color::Colors::Gray(0x808080FFu);
Color Color::Colors::Goldenrod(0xDAA520FFu);
Color Color::Colors::GhostWhite(0xF8F8FFFFu);
Color Color::Colors::Gainsboro(0xDCDCDCFFu);
Color Color::Colors::Fuchsia(0xFF00FFFFu);
Color Color::Colors::Gold(0xFFD700FFu);
Color Color::Colors::FloralWhite(0xFFFAF0FFu);
Color Color::Colors::DarkRed(0x8B0000FFu);
Color Color::Colors::DarkSalmon(0xE9967AFFu);
Color Color::Colors::DarkSeaGreen(0x8FBC8BFFu);
Color Color::Colors::ForestGreen(0x228B22FFu);
Color Color::Colors::DarkSlateGray(0x2F4F4FFFu);
Color Color::Colors::DarkTurquoise(0x00CED1FFu);
Color Color::Colors::DarkSlateBlue(0x483D8BFFu);
Color Color::Colors::DeepPink(0xFF1493FFu);
Color Color::Colors::DeepSkyBlue(0x00BFFFFFu);
Color Color::Colors::DimGray(0x696969FFu);
Color Color::Colors::DodgerBlue(0x1E90FFFFu);
Color Color::Colors::Firebrick(0xB22222FFu);
Color Color::Colors::DarkViolet(0x9400D3FFu);

static Double threeway_max(Double a, Double b, Double c)
{
    return std::max(a.GetFP(), std::max(b.GetFP(), c.GetFP()));
}

static Double threeway_min(Double a, Double b, Double c)
{
    return std::min(a.GetFP(), std::min(b.GetFP(), c.GetFP()));
}

static Double HueToRGB(Double p, Double q, Double t)
{
    if (t < 0) t = t + 1.0;
    if (t > 1) t = t - 1.0;
    if (t < 1 / 6.0) return p + (q - p) * 6 * t;
    if (t < 1 / 2.0) return q;
    if (t < 2 / 3.0) return p + (q - p) * (2 / 3.0 - t) * 6;
    return p;
}

void Color::ColorToHSL(const Color& color, uint8* hue, uint8* saturation, uint8* luminance)
{
    Double h, s, l;
    ColorToHSL(color, &h, &s, &l);

    *hue = ByteValueFromDouble(h);
    *saturation = ByteValueFromDouble(s);
    *luminance = ByteValueFromDouble(l);
}

void Color::ColorToHSL(const Color& color, Float* hue, Float* saturation, Float* luminance)
{
    Double h, s, l;
    ColorToHSL(color, &h, &s, &l);

    *hue = Float(h);
    *saturation = Float(s);
    *luminance = Float(l);
}

void Color::ColorToHSL(const Color& color, Double* hue, Double* saturation, Double* luminance)
{
    Double rd = color.GetRedFD();
    Double gd = color.GetGreenFD();
    Double bd = color.GetBlueFD();

    Double max = threeway_max(rd, gd, bd);
    Double min = threeway_min(rd, gd, bd);
    Double h = 0.0, s = 0.0, l = (max + min) / 2;

    if (max == min)
    {
        h = s = 0.0; // achromatic
    }
    else
    {
        double d = max - min;

        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);

        if (max == rd)
        {
            h = (gd - bd) / d + (gd < bd ? 6 : 0);
        }
        else if (max == gd)
        {
            h = (bd - rd) / d + 2;
        }
        else if (max == bd)
        {
            h = (rd - gd) / d + 4;
        }

        h = h.Divide(6.0);
    }

    assert(h <= Color::MaxHue.GetFP() && h >= Color::MinHue.GetFP());
    assert(s <= Color::MaxSaturation.GetFP() && s >= Color::MinSaturation.GetFP());
    assert(l <= Color::MaxLuminance.GetFP() && l >= Color::MinLuminance.GetFP());

    *hue = h;
    *saturation = s;
    *luminance = l;
}

Color Color::ColorFromHSL(uint8 hue, uint8 saturation, uint8 luminance, uint8 alpha)
{
    return ColorFromHSL(
        DoubleValueFromByte(hue),
        DoubleValueFromByte(saturation),
        DoubleValueFromByte(luminance),
        DoubleValueFromByte(alpha));
}

Color Color::ColorFromHSL(Float hue, Float saturation, Float luminance, Float alpha)
{
    return ColorFromHSL(Double(hue), Double(saturation), Double(luminance), Double(alpha));
}

Color Color::ColorFromHSL(Double hue, Double saturation, Double luminance, Double alpha)
{
    assert(hue <= Color::MaxHue.GetFP() && hue >= Color::MinHue.GetFP());
    assert(saturation <= Color::MaxSaturation.GetFP() && saturation >= Color::MinSaturation.GetFP());
    assert(luminance <= Color::MaxLuminance.GetFP() && luminance >= Color::MinLuminance.GetFP());

    Double r, g, b;
    Double h = hue;
    Double s = saturation;
    Double l = luminance;

    if (s == 0.0)
    {
        r = g = b = l; // achromatic
    }
    else
    {
        Double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        Double p = 2 * l - q;

        r = HueToRGB(p, q, hue + 1 / 3.0);
        g = HueToRGB(p, q, hue);
        b = HueToRGB(p, q, hue - 1 / 3.0);
    }

    return Color(r, g, b, alpha);
}

void Color::ColorToHSV(const Color& color, uint8* hue, uint8* saturation, uint8* value)
{
    Double h, s, v;
    ColorToHSV(color, &h, &s, &v);

    *hue = ByteValueFromDouble(h);
    *saturation = ByteValueFromDouble(s);
    *value = ByteValueFromDouble(v);
}

void Color::ColorToHSV(const Color& color, Float* hue, Float* saturation, Float* value)
{
    Double h, s, v;
    ColorToHSV(color, &h, &s, &v);

    *hue = Float(h);
    *saturation = Float(s);
    *value = Float(v);
}

void Color::ColorToHSV(const Color& color, Double* hue, Double* saturation, Double* value)
{
    Double rd = color.GetRedFD();
    Double gd = color.GetGreenFD();
    Double bd = color.GetBlueFD();

    Double max = threeway_max(rd, gd, bd), min = threeway_min(rd, gd, bd);
    Double h = 0.0, s = 0.0, v = max;

    Double d = max - min;
    s = max == 0.0 ? 0.0 : d / max;

    if (max == min)
    {
        h = 0.0; // achromatic
    }
    else
    {
        if (max == rd)
        {
            h = (gd - bd) / d + (gd < bd ? 6.0 : 0.0);
        }
        else if (max == gd)
        {
            h = (bd - rd) / d + 2.0;
        }
        else if (max == bd)
        {
            h = (rd - gd) / d + 4.0;
        }

        h = h.Divide(6.0);
    }

    assert(h <= Color::MaxHue.GetFP() && h >= Color::MinHue.GetFP());
    assert(s <= Color::MaxSaturation.GetFP() && s >= Color::MinSaturation.GetFP());
    assert(v <= Color::MaxValue.GetFP() && v >= Color::MinValue.GetFP());

    *hue = h;
    *saturation = s;
    *value = v;
}

Color Color::ColorFromHSV(uint8 hue, uint8 saturation, uint8 value, uint8 alpha)
{
    return ColorFromHSV(
        DoubleValueFromByte(hue),
        DoubleValueFromByte(saturation),
        DoubleValueFromByte(value),
        DoubleValueFromByte(alpha));
}

Color Color::ColorFromHSV(Float hue, Float saturation, Float value, Float alpha)
{
    return ColorFromHSV(Double(hue), Double(saturation), Double(value), Double(alpha));
}

Color Color::ColorFromHSV(Double hue, Double saturation, Double value, Double alpha)
{
    assert(hue <= Color::MaxHue.GetFP() && hue >= Color::MinHue.GetFP());
    assert(saturation <= Color::MaxSaturation.GetFP() && saturation >= Color::MinSaturation.GetFP());
    assert(value <= Color::MaxValue.GetFP() && value >= Color::MinValue.GetFP());

    Double r, g, b;
    Double h = hue;
    Double s = saturation;
    Double v = value;

    const int32 i = int32(h * 6);
    Double f = h * 6.0 - i;
    Double p = v * (1.0 - s);
    Double q = v * (1.0 - f * s);
    Double t = v * (1.0 - (1.0 - f) * s);

    // Decided to turn this into a multi-dimensional array over a switch case
    // Seemed faster
    // https://github.com/ratkins/RGBConverter/blob/master/RGBConverter.cpp#L140
    const Double conv[6][3] =
    {
        { v, t, p }, // 0
        { q, v, p }, // 1
        { p, v, t }, // 2
        { p, q, v }, // 3
        { t, p, v }, // 4
        { v, p, q }, // 5
    };

    const uint32 mod = i % 6;

    r = conv[mod][0];
    g = conv[mod][1];
    b = conv[mod][2];

    return Color(r, g, b, alpha);
}
