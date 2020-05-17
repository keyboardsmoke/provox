#include "pch.h"
#include "types.h"
#include <algorithm>

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

void Color::ColorToHSL(Color& color, uint8* hue, uint8* saturation, uint8* luminance)
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
        
        h.Divide(6.0);
    }

    *hue = static_cast<uint8>(h * 255.0);
    *saturation = static_cast<uint8>(s * 255.0);
    *luminance = static_cast<uint8>(l * 255.0);
}

Color Color::ColorFromHSL(uint8 hue, uint8 saturation, uint8 luminance, uint8 alpha)
{
    Double r, g, b;
    Double h = Color::DoubleValueFromByte(hue);
    Double s = Color::DoubleValueFromByte(saturation);
    Double l = Color::DoubleValueFromByte(luminance);

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

    return Color(r, g, b, Color::DoubleValueFromByte(alpha));
}

void Color::ColorToHSV(Color& color, uint8* hue, uint8* saturation, uint8* value)
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

        h.Divide(6.0);
    }

    *hue = static_cast<uint8>(h * 255.0);
    *saturation = static_cast<uint8>(s * 255.0);
    *value = static_cast<uint8>(v * 255.0);
}

Color Color::ColorFromHSV(uint8 hue, uint8 saturation, uint8 value, uint8 alpha)
{
    Double r, g, b;
    Double h = Color::DoubleValueFromByte(hue);
    Double s = Color::DoubleValueFromByte(saturation);
    Double v = Color::DoubleValueFromByte(value);

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

    return Color(r, g, b, Color::DoubleValueFromByte(alpha));
}