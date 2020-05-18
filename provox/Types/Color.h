#pragma once

// We're storing Color as AGBR mostly so we can use hex codes (uint32) in a constructor
// I could have done weird bit shifty stuff to avoid this, but I don't see why it matters
// If it ends up mattering later, yeah, bit shifty stuff.
class Color
{
private:
    static constexpr uint8 RED_INDEX = 3;
    static constexpr uint8 GREEN_INDEX = 2;
    static constexpr uint8 BLUE_INDEX = 1;
    static constexpr uint8 ALPHA_INDEX = 0;

public:
    const static Double MaxHue;
    const static Double MaxSaturation;
    const static Double MaxLuminance;
    const static Double MaxValue;

    const static Double MinHue;
    const static Double MinSaturation;
    const static Double MinLuminance;
    const static Double MinValue;

    static Float FloatValueFromByte(uint8 c)
    {
        return Float(c).Divide(255.0f);
    }

    static Double DoubleValueFromByte(uint8 c)
    {
        return Double(c).Divide(255.0);
    }

    static uint8 ByteValueFromFloat(Float f)
    {
        return static_cast<uint8>(f.Multiply(255.0f));
    }

    static uint8 ByteValueFromDouble(Double d)
    {
        return static_cast<uint8>(d.Multiply(255.0));
    }

    // RGB to HSL
    static void ColorToHSL(const Color& color, uint8* hue, uint8* saturation, uint8* luminance);
    static void ColorToHSL(const Color& color, Float* hue, Float* saturation, Float* luminance);
    static void ColorToHSL(const Color& color, Double* hue, Double* saturation, Double* luminance);

    // HSL to RGB
    static Color ColorFromHSL(uint8 hue, uint8 saturation, uint8 luminance, uint8 alpha = 255);
    static Color ColorFromHSL(Float hue, Float saturation, Float luminance, Float alpha = 1.0f);
    static Color ColorFromHSL(Double hue, Double saturation, Double luminance, Double alpha = 1.0);

    // RGB to HSV
    static void ColorToHSV(const Color& color, uint8* hue, uint8* saturation, uint8* value);
    static void ColorToHSV(const Color& color, Float* hue, Float* saturation, Float* value);
    static void ColorToHSV(const Color& color, Double* hue, Double* saturation, Double* value);

    // HSV to RGB
    static Color ColorFromHSV(uint8 hue, uint8 saturation, uint8 value, uint8 alpha = 255);
    static Color ColorFromHSV(Float hue, Float saturation, Float value, Float alpha = 1.0f);
    static Color ColorFromHSV(Double hue, Double saturation, Double value, Double alpha = 1.0);

    Color() : m_abgr{ 0xff, 0, 0, 0 } {}

    Color(uint32 hex) { SetValue(hex); }

    Color(uint8 r, uint8 g, uint8 b, uint8 a) :
        m_abgr{ a, b, g, r } {}

    Color(Float r, Float g, Float b, Float a) :
        m_abgr{
            ByteValueFromFloat(a),
            ByteValueFromFloat(b),
            ByteValueFromFloat(g),
            ByteValueFromFloat(r) } {}

    Color(Double r, Double g, Double b, Double a) :
        m_abgr{
            ByteValueFromDouble(a),
            ByteValueFromDouble(b),
            ByteValueFromDouble(g),
            ByteValueFromDouble(r) } {}

    // Getters
    uint8 GetRed() const { return m_abgr[RED_INDEX]; }
    uint8 GetGreen() const { return m_abgr[GREEN_INDEX]; }
    uint8 GetBlue() const { return m_abgr[BLUE_INDEX]; }
    uint8 GetAlpha() const { return m_abgr[ALPHA_INDEX]; }

    Float GetRedF() const { return FloatValueFromByte(GetRed()); }
    Float GetGreenF() const { return FloatValueFromByte(GetGreen()); }
    Float GetBlueF() const { return FloatValueFromByte(GetBlue()); }
    Float GetAlphaF() const { return FloatValueFromByte(GetAlpha()); }

    Double GetRedFD() const { return DoubleValueFromByte(GetRed()); }
    Double GetGreenFD() const { return DoubleValueFromByte(GetGreen()); }
    Double GetBlueFD() const { return DoubleValueFromByte(GetBlue()); }
    Double GetAlphaFD() const { return DoubleValueFromByte(GetAlpha()); }

    uint32 GetValue() const { return *reinterpret_cast<const uint32*>(&m_abgr[0]); }

    // Setters
    void SetRed(uint8 r) { m_abgr[RED_INDEX] = r; }
    void SetGreen(uint8 g) { m_abgr[GREEN_INDEX] = g; }
    void SetBlue(uint8 b) { m_abgr[BLUE_INDEX] = b; }
    void SetAlpha(uint8 a) { m_abgr[ALPHA_INDEX] = a; }

    void SetRedF(Float r) { m_abgr[RED_INDEX] = ByteValueFromFloat(r); }
    void SetGreenF(Float g) { m_abgr[GREEN_INDEX] = ByteValueFromFloat(g); }
    void SetBlueF(Float b) { m_abgr[BLUE_INDEX] = ByteValueFromFloat(b); }
    void SetAlphaF(Float a) { m_abgr[ALPHA_INDEX] = ByteValueFromFloat(a); }

    void SetValue(uint32 value) { *reinterpret_cast<uint32*>(&m_abgr[0]) = value; }

    // Conversion
    void ToHSL(uint8* hue, uint8* saturation, uint8* luminance) const { ColorToHSL(*this, hue, saturation, luminance); }
    void ToHSL(Float* hue, Float* saturation, Float* luminance) const { ColorToHSL(*this, hue, saturation, luminance); }
    void ToHSL(Double* hue, Double* saturation, Double* luminance) const { ColorToHSL(*this, hue, saturation, luminance); }

    void FromHSL(uint8 hue, uint8 saturation, uint8 luminance) { *this = ColorFromHSL(hue, saturation, luminance); }
    void FromHSL(Float hue, Float saturation, Float luminance) { *this = ColorFromHSL(hue, saturation, luminance); }
    void FromHSL(Double hue, Double saturation, Double luminance) { *this = ColorFromHSL(hue, saturation, luminance); }

    void ToHSV(uint8* hue, uint8* saturation, uint8* value) const { ColorToHSV(*this, hue, saturation, value); }
    void ToHSV(Float* hue, Float* saturation, Float* value) const { ColorToHSV(*this, hue, saturation, value); }
    void ToHSV(Double* hue, Double* saturation, Double* value) const { ColorToHSV(*this, hue, saturation, value); }

    void FromHSV(uint8 hue, uint8 saturation, uint8 value) { *this = ColorFromHSL(hue, saturation, value); }
    void FromHSV(Float hue, Float saturation, Float value) { *this = ColorFromHSL(hue, saturation, value); }
    void FromHSV(Double hue, Double saturation, Double value) { *this = ColorFromHSL(hue, saturation, value); }

    // Using HSL/HSV we can change colors, which is a cool feature
    Color GetLighter(Double lighter) const
    {
        Double h, s, l;
        ToHSL(&h, &s, &l);
        l.Add(lighter);
        l.Clamp(1.0);
        return Color::ColorFromHSL(h, s, l, GetAlphaFD());
    }

    Color GetDarker(Double darker) const
    {
        Double h, s, l;
        ToHSL(&h, &s, &l);
        l.Subtract(darker);
        l.Clamp(0.0);
        return Color::ColorFromHSL(h, s, l, GetAlphaFD());
    }

    // operators
    bool operator==(const Color& col) const
    {
        return GetValue() == col.GetValue();
    }

    bool operator!=(const Color& col) const
    {
        return GetValue() != col.GetValue();
    }

private:
    uint8 m_abgr[4];

public:
    struct Colors
    {
        static Color MediumPurple;
        static Color MediumSeaGreen;
        static Color MediumSlateBlue;
        static Color MediumSpringGreen;
        static Color MediumTurquoise;
        static Color MediumVioletRed;
        static Color MidnightBlue;
        static Color MediumOrchid;
        static Color MintCream;
        static Color Moccasin;
        static Color NavajoWhite;
        static Color Navy;
        static Color OldLace;
        static Color Olive;
        static Color OliveDrab;
        static Color Orange;
        static Color MistyRose;
        static Color OrangeRed;
        static Color MediumBlue;
        static Color Maroon;
        static Color LightBlue;
        static Color LightCoral;
        static Color LightGoldenrodYellow;
        static Color LightGreen;
        static Color LightGray;
        static Color LightPink;
        static Color LightSalmon;
        static Color MediumAquamarine;
        static Color LightSeaGreen;
        static Color LightSlateGray;
        static Color LightSteelBlue;
        static Color LightYellow;
        static Color Lime;
        static Color LimeGreen;
        static Color Linen;
        static Color Magenta;
        static Color LightSkyBlue;
        static Color LemonChiffon;
        static Color Orchid;
        static Color PaleGreen;
        static Color SlateBlue;
        static Color SlateGray;
        static Color Snow;
        static Color SpringGreen;
        static Color SteelBlue;
        static Color Tan;
        static Color Teal;
        static Color SkyBlue;
        static Color Thistle;
        static Color Turquoise;
        static Color Violet;
        static Color Wheat;
        static Color White;
        static Color WhiteSmoke;
        static Color Yellow;
        static Color YellowGreen;
        static Color Tomato;
        static Color PaleGoldenrod;
        static Color Silver;
        static Color SeaShell;
        static Color PaleTurquoise;
        static Color PaleVioletRed;
        static Color PapayaWhip;
        static Color PeachPuff;
        static Color Peru;
        static Color Pink;
        static Color Plum;
        static Color Sienna;
        static Color PowderBlue;
        static Color Red;
        static Color RosyBrown;
        static Color RoyalBlue;
        static Color SaddleBrown;
        static Color Salmon;
        static Color SandyBrown;
        static Color SeaGreen;
        static Color Purple;
        static Color LawnGreen;
        static Color LightCyan;
        static Color Lavender;
        static Color DarkKhaki;
        static Color DarkGreen;
        static Color DarkGray;
        static Color DarkGoldenrod;
        static Color DarkCyan;
        static Color DarkBlue;
        static Color Cyan;
        static Color Crimson;
        static Color Cornsilk;
        static Color LavenderBlush;
        static Color Coral;
        static Color Chocolate;
        static Color Chartreuse;
        static Color DarkMagenta;
        static Color CadetBlue;
        static Color Brown;
        static Color BlueViolet;
        static Color Blue;
        static Color BlanchedAlmond;
        static Color Black;
        static Color Bisque;
        static Color Beige;
        static Color Azure;
        static Color Aquamarine;
        static Color Aqua;
        static Color AntiqueWhite;
        static Color AliceBlue;
        static Color Transparent;
        static Color BurlyWood;
        static Color DarkOliveGreen;
        static Color CornflowerBlue;
        static Color DarkOrchid;
        static Color Khaki;
        static Color Ivory;
        static Color DarkOrange;
        static Color Indigo;
        static Color IndianRed;
        static Color HotPink;
        static Color Honeydew;
        static Color GreenYellow;
        static Color Green;
        static Color Gray;
        static Color Goldenrod;
        static Color GhostWhite;
        static Color Gainsboro;
        static Color Fuchsia;
        static Color Gold;
        static Color FloralWhite;
        static Color DarkRed;
        static Color DarkSalmon;
        static Color DarkSeaGreen;
        static Color ForestGreen;
        static Color DarkSlateGray;
        static Color DarkTurquoise;
        static Color DarkSlateBlue;
        static Color DeepPink;
        static Color DeepSkyBlue;
        static Color DimGray;
        static Color DodgerBlue;
        static Color Firebrick;
        static Color DarkViolet;
    };
};

static_assert(sizeof(Color) == sizeof(uint32), "Invalid size for Color.");
